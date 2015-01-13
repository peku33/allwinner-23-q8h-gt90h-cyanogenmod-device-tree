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
#include "audio_digital.h"
#include "audio_ril_modem.h"

#include <cutils/properties.h>

static int get_current_tty_dev(char * tty_dev)
{
    char temp_name[32];
    int no = -1;
    int i = 0;
    int ret = 0;

    if(NULL == tty_dev){
        return -1;
    }

    for(i = 0; i < 20; i++){
    	memset(temp_name, 0, 32);
    	sprintf(temp_name, "/dev/ttyUSB%d", i);

		ret = access(temp_name, F_OK);
		if(ret != 0){
			continue;
		}

		no = i;
    }

	if(no >= 0){
		sprintf(temp_name, "/dev/ttyUSB%d", no);
		strcpy(tty_dev, temp_name);
		ALOGV("get_current_tty_dev_mu509: tty_dev=%s\n", tty_dev);
		return 0;
	}else{
		ALOGV("get_current_tty_dev_mu509: can not find the AT device\n");
		return -1;
	}

	return 0;
}

int ril_set_call_volume_huawei_mu509(enum ril_sound_type sound_type, int volume)
{
	char tty_dev[32];

	memset(tty_dev, 0, 32);
	get_current_tty_dev(tty_dev);

	char cmdline[128];
	memset(cmdline, 0, 128);
	sprintf(cmdline, "/system/bin/busybox echo -e \"AT+CLVL=%d\r\n\" > %s", volume, tty_dev);
	system(cmdline);

    return 0;
}

int ril_set_call_audio_path_huawei_mu509(enum ril_audio_path path)
{
	enum digital_audio_method method = get_digital_audio_method();
	int channel = 0;
    char cmdline[128];
	char tty_dev[32];

    /* select audio channel */
	if(method == DIGITAL_AUDIO_METHOD_2){
		/* modem 纯模拟接入 */
		channel = 0;
	}else if(method == DIGITAL_AUDIO_METHOD_3){
		/* modem 纯数字接入 */
		channel = 2;
	}else if(method == DIGITAL_AUDIO_METHOD_1){
		/* modem 数字和模拟都接入 */
        switch(path) {
            case SOUND_AUDIO_PATH_HANDSET:
                channel = 0;
            break;

            case SOUND_AUDIO_PATH_SPEAKER:
            case SOUND_AUDIO_PATH_HEADSET:
            case SOUND_AUDIO_PATH_HEADPHONE:
                channel = 0;
            break;

            case SOUND_AUDIO_PATH_BLUETOOTH:
            case SOUND_AUDIO_PATH_BLUETOOTH_NO_NR:
                channel = 2;
            break;

            default:
                channel = 0;
                break;
        }
	}else{
	    channel = 0;
	}

    /* set path */
	memset(tty_dev, 0, 32);
    memset(cmdline, 0, 128);

	get_current_tty_dev(tty_dev);

    ALOGI("mu509: channel=%d, at=%s\n", channel, tty_dev);

    sprintf(cmdline, "/system/bin/busybox echo -e \"AT^SWSPATH=%d\r\n\" > %s", channel, tty_dev);
    system(cmdline);

	return 0;
}

