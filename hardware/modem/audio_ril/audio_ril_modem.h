/*
 * Copyright (C) 2011 The Android Open Source Project
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

#ifndef AUDIO_RIL_MODEM_H
#define AUDIO_RIL_MODEM_H

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

#define  LIB_OVIPHONE_EM55			"libsoftwinner-ril-oviphone-em55.so"
#define  LIB_HUAWEI_MU509			"libsoftwinner-ril-huawei-mu509.so"
#define  LIB_YUGA_CWM600			"libsoftwinner-ril-yuga-cwm600.so"
#define  LIB_LONGCHEER_WM5608		"libsoftwinner-ril-longcheer-wm5608.so"

enum ril_modem_type{
	MODEM_TYPE_NULL = 0,
    MODEM_TYPE_OVIPHONE_EM55,
    MODEM_TYPE_HUAWEI_MU509,
    MODEM_TYPE_YUGA_CWM600,
    MODEM_TYPE_LONGCHEER_WM5608,
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
enum digital_audio_method get_digital_audio_method(void);

int ril_set_call_volume_huawei_mu509(enum ril_sound_type sound_type, int volume);
int ril_set_call_audio_path_huawei_mu509(enum ril_audio_path path);

int ril_set_call_volume_yuga_cwm600(enum ril_sound_type sound_type, int volume);
int ril_set_call_audio_path_yuga_cwm600(enum ril_audio_path path);

int ril_set_call_volume_oviphone_em55(enum ril_sound_type sound_type, int volume);
int ril_set_call_audio_path_oviphone_em55(enum ril_audio_path path);

int ril_set_call_volume_longcheer_wm5608(enum ril_sound_type sound_type, int volume);
int ril_set_call_audio_path_longcheer_wm5608(enum ril_audio_path path);

#endif  //AUDIO_RIL_MODEM_H

