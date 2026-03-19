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
 */

#pragma once

#ifdef AMONET_SUPPORT

// Load microloader from the patched recovery partition into the in-memory
// microloader_bin buffer.  If the recovery partition has not been patched
// (i.e. no microloader is embedded), returns 0 and leaves microloader_bin
// zeroed.  Returns < 0 on hard failure.
int amonet_load_microloader();

// Remove the amonet exploit from the boot partition so a clean boot image
// is present when the update-binary runs.  Returns 0 on success.
int amonet_unpatch_boot();

// (Re)install the amonet exploit into the boot partition.  Returns 0 on
// success.
int amonet_patch_boot();

// (Re)install the amonet exploit into the recovery partition.  Returns 0
// on success.
int amonet_patch_recovery();

#endif  // AMONET_SUPPORT
