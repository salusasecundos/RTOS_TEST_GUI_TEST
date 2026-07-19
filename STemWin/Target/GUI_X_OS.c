#include "GUI.h"
    
#include "cmsis_os.h"
    
static osMutexId osMutex;
static osSemaphoreId osSemaphore;

int GUI_X_GetTime(void)
{
  return ((int) osKernelSysTick());
}

void GUI_X_Delay(int ms)
{
  osDelay( ms );
}


void GUI_X_Init(void) {
}

void GUI_X_ExecIdle(void) {}


void GUI_X_InitOS(void)
{ 
  /* Create Mutex lock */
  osMutexDef(MUTEX);
  
  /* Create the Mutex used by the two threads */
  osMutex = osMutexCreate(osMutex(MUTEX));
  
  /* Create Semaphore lock */
  osSemaphoreDef(SEM);
  
  /* Create the Semaphore used by the two threads */
  osSemaphore= osSemaphoreCreate(osSemaphore(SEM), 1);  
}

void GUI_X_Unlock(void)
{ 
  osMutexRelease(osMutex);
}

void GUI_X_Lock(void)
{
  osMutexWait(osMutex , osWaitForever) ;
}

/* Get Task handle */
U32 GUI_X_GetTaskId(void) 
{ 
  return ((U32) osThreadGetId());
}


void GUI_X_WaitEvent (void) 
{
  osSemaphoreWait(osSemaphore , osWaitForever) ;
}


void GUI_X_SignalEvent (void) 
{
  osMutexRelease(osSemaphore);
}

/*********************************************************************
*
* Logging: OS dependent

Note:
Logging is used in higher debug levels only. The typical target
build does not use logging and does therefor not require any of
the logging routines below. For a release build without logging
the routines below may be eliminated to save some space.
(If the linker is not function aware and eliminates unreferenced
functions automatically)

*/

void GUI_X_Log (const char *s) { }
void GUI_X_Warn (const char *s) { }
void GUI_X_ErrorOut(const char *s) { }
