#ifdef TW_AMONET

#include <string.h>

#include "amonet.h"
#include "microloader.h"
#include "twcommon.h"

<<<<<<< HEAD
static const char *ford_boot_part = "/dev/block/platform/mtk-msdc.0/by-name/boot";
static const char *ford_recovery_part = "/dev/block/platform/mtk-msdc.0/by-name/recovery";

static uint8_t microloader_bin[1024] = {
  0x41, 0x4e, 0x44, 0x52, 0x4f, 0x49, 0x44, 0x21, 0x00, 0x10, 0x00, 0x00,
  0xf0, 0xbf, 0xe6, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x40, 0x00, 0x00, 0x00, 0x48,
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x11, 0x04, 0x0e,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x62, 0x6f, 0x6f, 0x74, 0x6f, 0x70, 0x74, 0x3d,
  0x36, 0x34, 0x53, 0x33, 0x2c, 0x33, 0x32, 0x4e, 0x32, 0x2c, 0x33, 0x32,
  0x4e, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x4c, 0xc0, 0xe6, 0x81, 0x18, 0x0f, 0xe4, 0x81,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x5c, 0xc0, 0xe6, 0x81, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xbc, 0xe3, 0x81,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xa4, 0xba, 0xe0, 0x81, 0x00, 0xc1, 0xe6, 0x81,
  0x00, 0x02, 0x00, 0x00, 0xad, 0xde, 0x00, 0x00, 0xd0, 0xbc, 0xe3, 0x81,
  0xad, 0xde, 0x00, 0x00, 0xad, 0xde, 0x00, 0x00, 0xad, 0xde, 0x00, 0x00,
  0xad, 0xde, 0x00, 0x00, 0xad, 0xde, 0x00, 0x00, 0xad, 0xde, 0x00, 0x00,
  0x99, 0x1d, 0xe0, 0x81, 0xad, 0xde, 0x00, 0x00, 0x00, 0xc1, 0xe6, 0x81,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x81, 0xd4, 0xa0, 0xe3, 0x12, 0x00, 0x00, 0xfa, 0x03, 0x4a, 0x13, 0x68,
  0x9b, 0x06, 0xfc, 0xd5, 0x02, 0x4b, 0x18, 0x60, 0x70, 0x47, 0x00, 0xbf,
  0x14, 0x20, 0x00, 0x11, 0x00, 0x20, 0x00, 0x11, 0x0a, 0x28, 0x01, 0x46,
  0x08, 0xb5, 0x02, 0xd1, 0x0d, 0x20, 0xff, 0xf7, 0xed, 0xff, 0x08, 0x46,
  0xff, 0xf7, 0xea, 0xff, 0x08, 0xbd, 0x38, 0xb5, 0x45, 0x1e, 0x15, 0xf8,
  0x01, 0x4f, 0x24, 0xb9, 0x0a, 0x20, 0xff, 0xf7, 0xed, 0xff, 0x20, 0x46,
  0x38, 0xbd, 0x20, 0x46, 0xff, 0xf7, 0xe8, 0xff, 0xf3, 0xe7, 0x00, 0xbf,
  0x7f, 0xb5, 0x4f, 0xf0, 0x01, 0x44, 0x0e, 0x4e, 0x4f, 0xf4, 0x00, 0x15,
  0x0d, 0x48, 0xff, 0xf7, 0xe8, 0xff, 0x33, 0x68, 0x98, 0x47, 0x01, 0x95,
  0x01, 0x23, 0x02, 0x93, 0x4f, 0xf4, 0x00, 0x12, 0x00, 0x94, 0x00, 0x23,
  0x01, 0x69, 0x88, 0x47, 0x73, 0x68, 0x29, 0x46, 0x20, 0x46, 0x98, 0x47,
  0x05, 0x48, 0xff, 0xf7, 0xd6, 0xff, 0xa0, 0x47, 0x04, 0x48, 0xff, 0xf7,
  0xd2, 0xff, 0xfe, 0xe7, 0xfc, 0xc1, 0xe6, 0x81, 0xa4, 0xc1, 0xe6, 0x81,
  0xc8, 0xc1, 0xe6, 0x81, 0xdc, 0xc1, 0xe6, 0x81, 0x6d, 0x69, 0x63, 0x72,
  0x6f, 0x6c, 0x6f, 0x61, 0x64, 0x65, 0x72, 0x20, 0x62, 0x79, 0x20, 0x78,
  0x79, 0x7a, 0x2e, 0x20, 0x43, 0x6f, 0x70, 0x79, 0x72, 0x69, 0x67, 0x68,
  0x74, 0x20, 0x32, 0x30, 0x31, 0x39, 0x2e, 0x00, 0x4a, 0x75, 0x6d, 0x70,
  0x20, 0x74, 0x6f, 0x20, 0x74, 0x68, 0x65, 0x20, 0x70, 0x61, 0x79, 0x6c,
  0x6f, 0x61, 0x64, 0x00, 0x53, 0x6f, 0x6d, 0x65, 0x74, 0x68, 0x69, 0x6e,
  0x67, 0x20, 0x77, 0x65, 0x6e, 0x74, 0x20, 0x68, 0x6f, 0x72, 0x72, 0x69,
  0x62, 0x6c, 0x79, 0x20, 0x77, 0x72, 0x6f, 0x6e, 0x67, 0x21, 0x00, 0x00,
  0xf1, 0x54, 0xe3, 0x81, 0xd0, 0xbc, 0xe3, 0x81, 0x70, 0xd3, 0xe6, 0x81,
  0x89, 0x22, 0xe4, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

=======
>>>>>>> fa181e68 (Make amonet more generic / Move microloader to device tree)
int repatch() {
  return repatch_boot() + repatch_recovery();
}

int repatch_boot() {
  return repatch_part(0);
}

int unpatch_boot() {
  return unpatch_part(0);
}

int repatch_recovery() {
  return repatch_part(1);
}

int unpatch_recovery() {
  return unpatch_part(1);
}

int unpatch_part(uint8_t part) {
  FILE *fp = NULL;
  uint8_t boot_data[0x800];
  int ret = -1;

  static const char *amonet_part;
  static const char *part_name;

  if(part == 1) {
    amonet_part = amonet_recovery_part;
    part_name = "recovery";
  }
  else {
    amonet_part = amonet_boot_part;
    part_name = "boot";
  }
  
  gui_print_color("highlight", EXPLOIT_TAG "Remove %s patch...", part_name);

  fp = fopen(amonet_part, "r+b");
  if (!fp) {
    gui_print_color("highlight", EXPLOIT_TAG "Failed to open the %s device", part_name);
    goto cleanup;
  }

  if (fread(boot_data, sizeof(boot_data), 1, fp) != 1) {
    gui_print_color("highlight", EXPLOIT_TAG "Failed to read data");
    goto cleanup;
  }

  if (memcmp(boot_data + 0x400, "ANDROID!", 8) != 0) {
    // Exploit not installed yet, but that's okay
    gui_print_color("highlight", EXPLOIT_TAG "NOT_INSTALLED");
    ret = 0;
    goto cleanup;
  }

  // Assume exploit is installed. Uninstall it by copying the second 0x400 over the first 0x400
  memcpy(boot_data, boot_data + 0x400, 0x400);
  // and zero out the second 0x400
  memset(boot_data + 0x400, 0, 0x400);

  if (fseek(fp, 0, SEEK_SET) != 0) {
    gui_print_color("highlight", EXPLOIT_TAG "Failed to seek");
    goto cleanup;
  }

  if (fwrite(boot_data, sizeof(boot_data), 1, fp) != 1) {
    gui_print_color("highlight", EXPLOIT_TAG "Failed to write data");
    goto cleanup;
  }

  gui_print_color("highlight", EXPLOIT_TAG "OK");
  ret = 0;

cleanup:
  if (fp) {
    fclose(fp);
    fp = NULL;
  }

  return ret;
}

int repatch_part(uint8_t part) {
  FILE *fp = NULL;
  uint8_t boot_data[0x800];
  int ret = -1;

  static const char *amonet_part;
  static const char *part_name;

  if(part == 1) {
    amonet_part = amonet_recovery_part;
    part_name = "recovery";
  }
  else {
    amonet_part = amonet_boot_part;
    part_name = "boot";
  }

  gui_print_color("highlight", EXPLOIT_TAG "Install %s patch... ", part_name);

  fp = fopen(amonet_part, "r+b");
  if (!fp) {
    gui_print_color("highlight", EXPLOIT_TAG "Failed to open the %s device", part_name);
    goto cleanup;
  }

  if (fread(boot_data, sizeof(boot_data), 1, fp) != 1) {
    gui_print_color("highlight", EXPLOIT_TAG "Failed to read data");
    goto cleanup;
  }

  if (memcmp(boot_data + 0x400, "ANDROID!", 8) == 0) {
    // Exploit not installed yet, but that's okay
    gui_print_color("highlight", EXPLOIT_TAG "ALREADY_INSTALLED"); // If the rom author injected the boot image herself
    ret = 0;
    goto cleanup;
  }

  // Copy first half to the second half, replace first half with the microloader
  memcpy(boot_data + 0x400, boot_data, 0x400);
  memcpy(boot_data, microloader_bin, 0x400);

  if (fseek(fp, 0, SEEK_SET) != 0) {
    gui_print_color("highlight", EXPLOIT_TAG "Failed to seek");
    goto cleanup;
  }

  if (fwrite(boot_data, sizeof(boot_data), 1, fp) != 1) {
    gui_print_color("highlight", EXPLOIT_TAG "Failed to write data");
    goto cleanup;
  }

  gui_print_color("highlight", EXPLOIT_TAG "OK");
  ret = 0;

cleanup:
  if (fp) {
    fclose(fp);
    fp = NULL;
  }

  return ret;
}

#endif
