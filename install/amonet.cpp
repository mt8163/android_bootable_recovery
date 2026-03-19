/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Ported from chaosmaster/android_bootable_recovery (TWRP amonet branch).
 * Original authors: xyzz <whatever@xyz.is>, Joel Stein <js@funkturm.net>
 */

#ifdef AMONET_SUPPORT

#include "install/amonet.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <string>

#include <android-base/logging.h>

#include "recovery_ui/ui.h"
#include "recovery_utils/roots.h"

#define EXPLOIT_TAG "[amonet] "

static RecoveryUI* s_ui = nullptr;

// 1 KiB microloader image, read from the patched recovery partition at runtime.
static uint8_t microloader_bin[1024];

void amonet_set_ui(RecoveryUI* ui) {
    s_ui = ui;
}

static void amonet_print(const char* fmt, ...) {
    char buf[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    LOG(INFO) << buf;
    if (s_ui) s_ui->Print("%s\n", buf);
}

// Return the block device path for the given recovery fstab mount point
// (e.g. "/boot", "/recovery"), or an empty string on failure.
static std::string block_device_for(const std::string& mount_point) {
    Volume* vol = volume_for_mount_point(mount_point);
    if (!vol || vol->blk_device.empty()) {
        amonet_print(EXPLOIT_TAG "Could not find block device for %s", mount_point.c_str());
        return "";
    }
    return vol->blk_device;
}

// Remove the amonet exploit from `mount_point` (e.g. "/boot").
static int unpatch_part(const std::string& mount_point) {
    const std::string part_name = mount_point.substr(1);
    const std::string blk = block_device_for(mount_point);
    if (blk.empty()) return -1;

    amonet_print(EXPLOIT_TAG "Remove %s patch...", part_name.c_str());

    FILE* fp = fopen(blk.c_str(), "r+b");
    if (!fp) {
        amonet_print(EXPLOIT_TAG "Failed to open %s", blk.c_str());
        return -1;
    }

    int ret = -1;
    uint8_t boot_data[0x800];

    if (fread(boot_data, sizeof(boot_data), 1, fp) != 1) {
        amonet_print(EXPLOIT_TAG "Failed to read data");
        goto cleanup;
    }

    if (memcmp(boot_data + 0x400, "ANDROID!", 8) != 0) {
        amonet_print(EXPLOIT_TAG "NOT_INSTALLED");
        ret = 0;
        goto cleanup;
    }

    memcpy(boot_data, boot_data + 0x400, 0x400);
    memset(boot_data + 0x400, 0, 0x400);

    if (fseek(fp, 0, SEEK_SET) != 0) {
        amonet_print(EXPLOIT_TAG "Failed to seek");
        goto cleanup;
    }

    if (fwrite(boot_data, sizeof(boot_data), 1, fp) != 1) {
        amonet_print(EXPLOIT_TAG "Failed to write data");
        goto cleanup;
    }

    amonet_print(EXPLOIT_TAG "OK");
    ret = 0;

cleanup:
    fclose(fp);
    return ret;
}

// Install the amonet exploit into `mount_point`.
static int patch_part(const std::string& mount_point) {
    const std::string part_name = mount_point.substr(1);
    const std::string blk = block_device_for(mount_point);
    if (blk.empty()) return -1;

    amonet_print(EXPLOIT_TAG "Install %s patch...", part_name.c_str());

    FILE* fp = fopen(blk.c_str(), "r+b");
    if (!fp) {
        amonet_print(EXPLOIT_TAG "Failed to open %s", blk.c_str());
        return -1;
    }

    int ret = -1;
    uint8_t boot_data[0x800];

    if (fread(boot_data, sizeof(boot_data), 1, fp) != 1) {
        amonet_print(EXPLOIT_TAG "Failed to read data");
        goto cleanup;
    }

    if (memcmp(boot_data + 0x400, "ANDROID!", 8) == 0) {
        amonet_print(EXPLOIT_TAG "ALREADY_INSTALLED");
        ret = 0;
        goto cleanup;
    }

    memcpy(boot_data + 0x400, boot_data, 0x400);
    memcpy(boot_data, microloader_bin, 0x400);

    if (fseek(fp, 0, SEEK_SET) != 0) {
        amonet_print(EXPLOIT_TAG "Failed to seek");
        goto cleanup;
    }

    if (fwrite(boot_data, sizeof(boot_data), 1, fp) != 1) {
        amonet_print(EXPLOIT_TAG "Failed to write data");
        goto cleanup;
    }

    amonet_print(EXPLOIT_TAG "OK");
    ret = 0;

cleanup:
    fclose(fp);
    return ret;
}

int amonet_load_microloader() {
    const std::string blk = block_device_for("/recovery");
    if (blk.empty()) return -1;

    amonet_print(EXPLOIT_TAG "Load microloader from recovery...");

    FILE* fp = fopen(blk.c_str(), "r+b");
    if (!fp) {
        amonet_print(EXPLOIT_TAG "Failed to open recovery device");
        return -1;
    }

    int ret = -1;
    uint8_t boot_data[0x800];

    if (fread(boot_data, sizeof(boot_data), 1, fp) != 1) {
        amonet_print(EXPLOIT_TAG "Failed to read data");
        goto cleanup;
    }

    if (memcmp(boot_data + 0x400, "ANDROID!", 8) != 0) {
        amonet_print(EXPLOIT_TAG "No microloader found in recovery");
        ret = 0;
        goto cleanup;
    }

    memcpy(microloader_bin, boot_data, 0x400);
    amonet_print(EXPLOIT_TAG "OK");
    ret = 0;

cleanup:
    fclose(fp);
    return ret;
}

int amonet_unpatch_boot() {
    return unpatch_part("/boot");
}

int amonet_patch_boot() {
    return patch_part("/boot");
}

int amonet_patch_recovery() {
    return patch_part("/recovery");
}

#endif  // AMONET_SUPPORT
