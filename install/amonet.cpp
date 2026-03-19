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

#include "recovery_utils/roots.h"

#define EXPLOIT_TAG "[amonet] "

// 1 KiB microloader image, read from the patched recovery partition at runtime.
static uint8_t microloader_bin[1024];

// Return the block device path for the given recovery fstab mount point
// (e.g. "/boot", "/recovery"), or an empty string on failure.
static std::string block_device_for(const std::string& mount_point) {
    Volume* vol = volume_for_mount_point(mount_point);
    if (!vol || vol->blk_device.empty()) {
        LOG(ERROR) << EXPLOIT_TAG "Could not find block device for " << mount_point;
        return "";
    }
    return vol->blk_device;
}

// Remove the amonet exploit from `part_path` (e.g. "/boot").
// The exploit is present when boot_data[0x400..0x408] == "ANDROID!" — meaning
// the original boot header was saved at offset 0x400 and the microloader was
// placed at offset 0.  Unpatching restores the original header.
static int unpatch_part(const std::string& mount_point) {
    const std::string part_name = mount_point.substr(1);  // strip leading '/'
    const std::string blk = block_device_for(mount_point);
    if (blk.empty()) return -1;

    LOG(INFO) << EXPLOIT_TAG "Remove " << part_name << " patch...";

    FILE* fp = fopen(blk.c_str(), "r+b");
    if (!fp) {
        PLOG(ERROR) << EXPLOIT_TAG "Failed to open " << blk;
        return -1;
    }

    int ret = -1;
    uint8_t boot_data[0x800];

    if (fread(boot_data, sizeof(boot_data), 1, fp) != 1) {
        LOG(ERROR) << EXPLOIT_TAG "Failed to read data";
        goto cleanup;
    }

    if (memcmp(boot_data + 0x400, "ANDROID!", 8) != 0) {
        // Exploit not installed; nothing to do.
        LOG(INFO) << EXPLOIT_TAG "NOT_INSTALLED";
        ret = 0;
        goto cleanup;
    }

    // Restore the original header: copy the saved header back to offset 0,
    // then zero out the saved-header slot.
    memcpy(boot_data, boot_data + 0x400, 0x400);
    memset(boot_data + 0x400, 0, 0x400);

    if (fseek(fp, 0, SEEK_SET) != 0) {
        PLOG(ERROR) << EXPLOIT_TAG "Failed to seek";
        goto cleanup;
    }

    if (fwrite(boot_data, sizeof(boot_data), 1, fp) != 1) {
        PLOG(ERROR) << EXPLOIT_TAG "Failed to write data";
        goto cleanup;
    }

    LOG(INFO) << EXPLOIT_TAG "OK";
    ret = 0;

cleanup:
    fclose(fp);
    return ret;
}

// Install the amonet exploit into `mount_point`.
// The microloader is placed at offset 0; the original boot header is saved
// at offset 0x400.  If boot_data[0x400..0x408] already equals "ANDROID!" the
// exploit is already installed.
static int patch_part(const std::string& mount_point) {
    const std::string part_name = mount_point.substr(1);
    const std::string blk = block_device_for(mount_point);
    if (blk.empty()) return -1;

    LOG(INFO) << EXPLOIT_TAG "Install " << part_name << " patch...";

    FILE* fp = fopen(blk.c_str(), "r+b");
    if (!fp) {
        PLOG(ERROR) << EXPLOIT_TAG "Failed to open " << blk;
        return -1;
    }

    int ret = -1;
    uint8_t boot_data[0x800];

    if (fread(boot_data, sizeof(boot_data), 1, fp) != 1) {
        LOG(ERROR) << EXPLOIT_TAG "Failed to read data";
        goto cleanup;
    }

    if (memcmp(boot_data + 0x400, "ANDROID!", 8) == 0) {
        // The ROM author may have pre-injected the patch; treat as success.
        LOG(INFO) << EXPLOIT_TAG "ALREADY_INSTALLED";
        ret = 0;
        goto cleanup;
    }

    // Save the original header at offset 0x400, then place the microloader
    // at offset 0.
    memcpy(boot_data + 0x400, boot_data, 0x400);
    memcpy(boot_data, microloader_bin, 0x400);

    if (fseek(fp, 0, SEEK_SET) != 0) {
        PLOG(ERROR) << EXPLOIT_TAG "Failed to seek";
        goto cleanup;
    }

    if (fwrite(boot_data, sizeof(boot_data), 1, fp) != 1) {
        PLOG(ERROR) << EXPLOIT_TAG "Failed to write data";
        goto cleanup;
    }

    LOG(INFO) << EXPLOIT_TAG "OK";
    ret = 0;

cleanup:
    fclose(fp);
    return ret;
}

// Load the microloader from the recovery partition.  If the recovery
// partition has been patched with amonet its first 0x400 bytes contain the
// microloader and offset 0x400 contains "ANDROID!".
int amonet_load_microloader() {
    const std::string blk = block_device_for("/recovery");
    if (blk.empty()) return -1;

    LOG(INFO) << EXPLOIT_TAG "Load microloader from recovery...";

    FILE* fp = fopen(blk.c_str(), "r+b");
    if (!fp) {
        PLOG(ERROR) << EXPLOIT_TAG "Failed to open recovery device";
        return -1;
    }

    int ret = -1;
    uint8_t boot_data[0x800];

    if (fread(boot_data, sizeof(boot_data), 1, fp) != 1) {
        LOG(ERROR) << EXPLOIT_TAG "Failed to read data";
        goto cleanup;
    }

    if (memcmp(boot_data + 0x400, "ANDROID!", 8) != 0) {
        // Recovery has not been patched; no microloader to load.
        LOG(INFO) << EXPLOIT_TAG "No microloader found in recovery";
        ret = 0;
        goto cleanup;
    }

    memcpy(microloader_bin, boot_data, 0x400);
    LOG(INFO) << EXPLOIT_TAG "OK";
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
