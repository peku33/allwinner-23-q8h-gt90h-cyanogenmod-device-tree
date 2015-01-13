#ifndef YG_INTERFACE_121007
#define YG_INTERFACE_121007
  typedef enum{
     E_BEFORE_DIAL = 0,
     E_AFTER_CONN,
     E_INIT_CALLBACK,
  }EYGEVENT;
  typedef int (*PSendATCommand)(char* pCommand);
  typedef int (*PYGEVENTFUN)(PSendATCommand patfun, EYGEVENT event, void* pdata);
#endif