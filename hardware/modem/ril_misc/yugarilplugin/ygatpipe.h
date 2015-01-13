#ifndef YGATSERVICE__
#define YGATSERVICE__

#include "audio_ril.h"

#ifdef __cplusplus
extern "C" {
#endif
  int WriteAT(char* patcommand);
  int ril_set_call_volume_yuga_cwm600(enum ril_sound_type sound_type, int volume);
  int ril_set_call_audio_path_yuga_cwm600(enum ril_audio_path path);
#ifdef __cplusplus
}
#endif
#endif