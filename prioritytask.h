#ifndef _PRIORITYTASK_H_
#define _PRIORITYTASK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

int32 PriorityTask_Create(echandle *PriorityTaskHandle, echandle TaskHandle);
echandle PriorityTask_AddRef(echandle PriorityTaskHandle);
int32 PriorityTask_Release(echandle *PriorityTaskHandle);

ITask_Declare(PriorityTask)

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
