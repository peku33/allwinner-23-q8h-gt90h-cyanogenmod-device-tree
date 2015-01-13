#include <stdio.h>
#include <stdlib.h>

#define LOG_TAG "audio_digital"
#define LOG_NDEBUG 0

#include <cutils/log.h>
#include <cutils/properties.h>

#include "ygrilinterface.h"
int  yg_eventfun(PSendATCommand patfun, EYGEVENT event, void* pdata)
{
	ALOGI("%s:%d: event=%d\n", __func__, __LINE__, event);

  switch(event)
  {
     case E_BEFORE_DIAL://拨号前调用
       if(NULL != patfun)
       {
         //patfun("AT+VOCVAL=4,8000,8000,F000");

       }
       break;
    case E_AFTER_CONN://接通后调用
    {
       if(NULL != patfun)
       {
        // patfun("AT+CLVL=3");
       }
       break;
    }
    case E_INIT_CALLBACK://初始化调用
    {
       if(NULL != patfun)
       {
         patfun("AT+VOCVAL=4,8000,8000,F000");
		 //patfun("AT+VTYPE=4");
       }
       break;
    }
    break;
  }
  return 0;
}
