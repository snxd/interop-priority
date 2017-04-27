#include "interoplib.h"


#include <stdlib.h>
#include <string.h>

#include "taski.h"
#include "workflowi.h"

#include "priority.h"

/*********************************************************************/

typedef struct PriorityTaskStruct {
    ClassStruct         Class;
    echandle            TaskHandle;
} PriorityTaskStruct;

Class_Define(PriorityTaskStruct, 0xcd008707)

/*********************************************************************/

static int32 PriorityTask_Notification_OnTaskStart(void *UserPtr, char *Type, char *Notification, void *Sender, echandle DictionaryHandle)
{
    PriorityTaskStruct *PriorityTask = Class_Cast(UserPtr, PriorityTaskStruct);
    char Level[320] = {0};

    if (ITask_GetStringArgument(PriorityTask->TaskHandle, "level", Level, Element_Count(Level)) == FALSE)
        String_CopyLength(Level, "low", Element_Count(Level));

    if (String_CompareWithoutCase(Level, "low") == TRUE)
        Priority_SetLow();
    if (String_CompareWithoutCase(Level, "normal") == TRUE)
        Priority_SetNormal();
    if (String_CompareWithoutCase(Level, "high") == TRUE)
        Priority_SetHigh();

    ITask_Complete(PriorityTask->TaskHandle, NULL);
    return TRUE;
}

/*********************************************************************/

int32 PriorityTask_Create(echandle *PriorityTaskHandle, echandle TaskHandle)
{
    PriorityTaskStruct *PriorityTask = NULL;

    PriorityTask = (PriorityTaskStruct *)malloc(sizeof(PriorityTaskStruct));
    Interop_GenerateInstanceId(PriorityTask->Class.InstanceId, 40);

    PriorityTask->TaskHandle = TaskHandle;
    NotificationCenter_AddInstanceObserver("Task", "Start", PriorityTask->TaskHandle, PriorityTask, PriorityTask_Notification_OnTaskStart);

    *PriorityTaskHandle = PriorityTask;
    return TRUE;
}

echandle PriorityTask_AddRef(echandle PriorityTaskHandle)
{
    PriorityTaskStruct *PriorityTask = (PriorityTaskStruct *)PriorityTaskHandle;
    PriorityTask->Class.RefCount += 1;
    return PriorityTask;
}

int32 PriorityTask_Release(echandle *PriorityTaskHandle)
{
    PriorityTaskStruct *PriorityTask = (PriorityTaskStruct *)*PriorityTaskHandle;

    if (--PriorityTask->Class.RefCount == 0)
    {
        NotificationCenter_RemoveInstanceObserver("Task", "Start", PriorityTask->TaskHandle, PriorityTask, PriorityTask_Notification_OnTaskStart);
        free(PriorityTask);
    }

    *PriorityTaskHandle = NULL;
    return TRUE;
}

/*********************************************************************/

ITask_DefineInt(Priority, PriorityTask)

/*********************************************************************/
