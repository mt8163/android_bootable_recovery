#ifdef TW_AMONET

#include <string.h>

#include "amonet.h"
#include "microloader.h"
#include "twcommon.h"

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
