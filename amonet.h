#ifdef TW_AMONET
#ifndef RECOVERY_AMONET_H_
#define RECOVERY_AMONET_H_

#include <unistd.h>

#define EXPLOIT_TAG "[amonet] "
int unpatch_boot();
int repatch_boot();
int repatch_recovery();
int unpatch_recovery();
int repatch();
int unpatch_part(uint8_t part);
int repatch_part(uint8_t part);

#endif  // RECOVERY_AMONET_H_
#endif // TW_AMONET
