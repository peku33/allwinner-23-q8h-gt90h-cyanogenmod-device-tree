#include "ygatpipe.h"
#include <stdio.h>
#include <stdlib.h>
#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

#include <cutils/log.h>
#include <cutils/properties.h>

#include <private/binder/binder_module.h>

#include "audio_ril.h"
#include "audio_digital.h"
#include "audio_ril_modem.h"

using namespace android;

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "testCallback"

class MySetupCallback : public BBinder
{
public:
    MySetupCallback()
    {
        mydescriptor = String16("android.os.ISetupCallback");
    }
    virtual ~MySetupCallback() {}

    virtual const String16& getInterfaceDescriptor() const
    {
        return mydescriptor;
    }

protected:
    virtual status_t onTransact( uint32_t code,
                                 const Parcel& data,
                                 Parcel* reply,
                                 uint32_t flags = 0)
    {
        ALOGD("enter MySetupCallback onTransact, code=%u", code);
        if (data.checkInterface(this))
            ALOGD("checkInterface OK");
        else
        {
            ALOGW("checkInterface failed");
            return -1;
        }
        switch (code)
        {
        default:
            break;
        }
        return 0;
    }

private:
    String16 mydescriptor;
};
MySetupCallback * pcb = NULL;
sp<IServiceManager> sm = defaultServiceManager();
sp<IBinder> b = sm->getService(String16("ril.at")); //Context.MCU_SERVICE

static pthread_t s_tid_ListenThread = 0;
void*   ListenATCommand(void *arg)
{
   ProcessState::self()->startThreadPool();
   IPCThreadState::self()->joinThreadPool();
   return NULL;
}
int WriteAT(char* patcommand)
{
  int ret = -1;
  Parcel in1,out1;

  ALOGI("%s:%d: \n", __func__, __LINE__);

  if(NULL != patcommand)
  {
     if( NULL == pcb)
     {
           pthread_attr_t attr;
            pthread_attr_init (&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        sm = defaultServiceManager();
        b = sm->getService(String16("ril.at")); //Context.MCU_SERVICE
        pcb = new MySetupCallback();
       // in1.writeStrongBinder(sp<IBinder>(pcb));
        ret = pthread_create(&s_tid_ListenThread, &attr, ListenATCommand, NULL);
     }
     in1.writeStrongBinder(sp<IBinder>(pcb));
     in1.writeString8(String8(patcommand));
     ret = b->transact(5, in1, &out1, 0);
     ALOGD("transact(5) return %d", ret);
     return ret;
  }
  return -1;
}

static enum digital_audio_method yuga_get_digital_audio_method(void)
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

int ril_set_call_volume_yuga_cwm600(enum ril_sound_type sound_type, int volume)
{
	char atcommand[128];

	memset(atcommand, 0, 128);
	sprintf(atcommand, "AT+CLVL=%d\r\n", volume);
	WriteAT(atcommand);

    return 0;
}

int ril_set_call_audio_path_yuga_cwm600(enum ril_audio_path path)
{
	enum digital_audio_method method = yuga_get_digital_audio_method();
	int channel = 0;
    char atcommand[128];

    /* select audio channel */
	if(method == DIGITAL_AUDIO_METHOD_2){
		/* modem 纯模拟接入 */
		channel = 4;
	}else if(method == DIGITAL_AUDIO_METHOD_3){
		/* modem 纯数字接入 */
		channel = 2;
	}else if(method == DIGITAL_AUDIO_METHOD_1){
		/* modem 数字和模拟都接入 */
		switch(path) {
            case SOUND_AUDIO_PATH_HANDSET:
                channel = 4;
            break;

            case SOUND_AUDIO_PATH_SPEAKER:
            case SOUND_AUDIO_PATH_HEADSET:
            case SOUND_AUDIO_PATH_HEADPHONE:
                channel = 4;
            break;

            case SOUND_AUDIO_PATH_BLUETOOTH:
            case SOUND_AUDIO_PATH_BLUETOOTH_NO_NR:
                channel = 2;
            break;

            default:
                channel = 4;
                break;
        }
	}else{
		channel = 4;
	}

	ALOGI("cwm600: method=%d, channel=%d, path=0x%x", method, channel, path);

    /* set path */
	memset(atcommand, 0, 128);
	sprintf(atcommand, "AT+VTYPE=%d\r\n", channel);
	WriteAT(atcommand);

	return 0;
}

int main()
{

  int i = 0;

  ALOGI("%s:%d: \n", __func__, __LINE__);

  for(i = 0; i < 100; ++i)
  {
     char buffer[128] = {0};
     sprintf(buffer, "AT+CLVL=%d\r\n", i % 7);
     WriteAT(buffer);
     sleep(1);

  }
#if 0
    sp<IServiceManager> sm = defaultServiceManager();

    sp<IBinder> b = sm->getService(String16("ril.at")); //Context.MCU_SERVICE

    if (b == NULL)
    {
        ALOGW("Can't find binder service \"ril.at\"");
        return -1;
    }

    Parcel in1,out1;
    MySetupCallback *cb = new MySetupCallback();
    in1.writeStrongBinder(sp<IBinder>(cb));
    int ret = b->transact(4, in1, &out1, 0); //TRANSACTION_registerSetup = 4
    ALOGD("transact(4) return %d", ret);
    in1.writeString8(String8("AT+CGMR\r\n"));
    ret = b->transact(5, in1, &out1, 0);
    ALOGD("transact(4) return %d", ret);
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
#endif

    return 0;
}







