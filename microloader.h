#ifdef TW_AMONET
#ifndef RECOVERY_AMONET_MICROLOADER_H_
#define RECOVERY_AMONET_MICROLOADER_H_

#include <unistd.h>

<<<<<<< HEAD
#ifdef TW_MICROLOADER
extern uint8_t microloader_bin[1024];
#else
uint8_t microloader_bin[1024];
#endif
=======
extern const char *amonet_boot_part;
extern const char *amonet_recovery_part;
extern uint8_t microloader_bin[1024];
>>>>>>> fa181e68 (Make amonet more generic / Move microloader to device tree)

#endif // RECOVERY_AMONET_MICROLOADER_H
#endif // TW_AMONET

