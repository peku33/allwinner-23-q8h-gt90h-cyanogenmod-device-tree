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

#define LOG_TAG "audio_hw_primary"
#define LOG_NDEBUG 0

#include <stdlib.h>
#include <string.h>
#include <utils/Log.h>
#include "audio_ril.h"
#include "audio_ril_modem.h"
#include "audio_digital.h"

#include <cutils/properties.h>

enum ril_modem_type get_modem_type(void)
{
	int ret = -1;
	char libPath[PROPERTY_VALUE_MAX];
	enum ril_modem_type modem_type = MODEM_TYPE_NULL;

	memset(libPath, 0, PROPERTY_VALUE_MAX);
	ret = property_get("rild.libpath", libPath, "");
    if(ret <= 0){
		modem_type = MODEM_TYPE_NULL;
    }else{
    	if(!strcmp(libPath, LIB_OVIPHONE_EM55)){
			modem_type = MODEM_TYPE_OVIPHONE_EM55;
		}else if(!strcmp(libPath, LIB_HUAWEI_MU509)){
			modem_type = MODEM_TYPE_HUAWEI_MU509;
		}else if(!strcmp(libPath, LIB_YUGA_CWM600)){
			modem_type = MODEM_TYPE_YUGA_CWM600;
		}else if(!strcmp(libPath, LIB_LONGCHEER_WM5608)){
			modem_type = MODEM_TYPE_LONGCHEER_WM5608;
		}else{
			modem_type = MODEM_TYPE_NULL;
		}
    }

    ALOGV("get_modem_type: modem_type=%d\n", modem_type);

	return modem_type;
}

enum digital_audio_method get_digital_audio_method(void)
{
    enum digital_audio_method method;
    char property[PROPERTY_VALUE_MAX];
    int ret = 0;

    memset(property, 0, sizeof(property));
    ret = property_get("ro.sw.audio.method", property, "0");
    if(ret <= 0){
        ALOGE("wrn: get ro.sw.audio.method failed\n");
        return DIGITAL_AUDIO_METHOD_UNKOWN;
    }

    if(!strcmp(property, "1")){
        method = DIGITAL_AUDIO_METHOD_1;
    }else if(!strcmp(property, "2")){
        method = DIGITAL_AUDIO_METHOD_2;
    }else if(!strcmp(property, "3")){
        method = DIGITAL_AUDIO_METHOD_3;
    }else{
        method = DIGITAL_AUDIO_METHOD_UNKOWN;
    }

    return method;
}

/* ÉèÖÃÌýÍ²¡¢À®°È¡¢¶ú»úµÈÒôÁ¿ */
int ril_set_call_volume(enum ril_sound_type sound_type, int volume)
{
	enum ril_modem_type modem_type = MODEM_TYPE_NULL;

	ALOGI("ril_set_call_volume, sound_type=%d, volume=%d\n", sound_type, volume);

	modem_type = get_modem_type();
	if(modem_type == MODEM_TYPE_OVIPHONE_EM55){
		ril_set_call_volume_oviphone_em55(sound_type, volume);
	}else if(modem_type == MODEM_TYPE_HUAWEI_MU509){
		ril_set_call_volume_huawei_mu509(sound_type, volume);
	}else if(modem_type == MODEM_TYPE_YUGA_CWM600){
		ril_set_call_volume_yuga_cwm600(sound_type, volume);
	}else if(modem_type == MODEM_TYPE_LONGCHEER_WM5608){
		ril_set_call_volume_longcheer_wm5608(sound_type, volume);
	}else{
		ALOGE("err: unkown modem_type=%d\n", modem_type);
	}

    return 0;
}

/* ÒôÆµÍ¨µÀÇÐ»» */
int ril_set_call_audio_path(enum ril_audio_path path)
{
	enum ril_modem_type modem_type = MODEM_TYPE_NULL;

	ALOGI("ril_set_call_audio_path, path=%d\n", path);

	modem_type = get_modem_type();
	if(modem_type == MODEM_TYPE_OVIPHONE_EM55){
		ril_set_call_audio_path_oviphone_em55(path);
	}else if(modem_type == MODEM_TYPE_HUAWEI_MU509){
		ril_set_call_audio_path_huawei_mu509(path);
	}else if(modem_type == MODEM_TYPE_YUGA_CWM600){
		ril_set_call_audio_path_yuga_cwm600(path);
	}else if(modem_type == MODEM_TYPE_LONGCHEER_WM5608){
		ril_set_call_audio_path_longcheer_wm5608(path);
	}else{
		ALOGE("err: unkown modem_type=%d\n", modem_type);
	}

    return 0;
}

