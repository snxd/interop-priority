#include "interoplib.h"
#include "interopstub.h"

#include "taski.h"
#include "workflowi.h"

#include "priority.h"
#include "prioritytask.h"

/*********************************************************************/

int32 Interop_CreateInstance(char *TypeName, char *InstanceId, int32 InstanceIdLength,
                             void *ExecuteUserPtr, Interop_ExecuteCallback Execute,
                             Interop_InvokeInstanceCallback *InvokeInstance,
                             Interop_ReleaseInstanceCallback *ReleaseInstance,
                             Interop_ProcessInstanceCallback *ProcessInstance,
                             void **UserPtr)
{
    if (String_Compare(TypeName, "SSN.Priority") == TRUE)
    {
        *InvokeInstance = Priority_Invoke;
        *ReleaseInstance = NULL;
        *ProcessInstance = NULL;
        *UserPtr = NULL;
        return TRUE;
    }
    return FALSE;
}

/*********************************************************************/

int32 Interop_SetOverride(char *Key, void *Value)
{
    InteropLib_SetOverride(Key, Value);
    return TRUE;
}

int32 Interop_SetOption(char *Key, void *Value)
{
    return TRUE;
}

/*********************************************************************/

static int32 Interop_Notification_OnRegisterTaskHandler(void *UserPtr, char *Type, char *Notification, void *Sender, echandle DictionaryHandle)
{
    echandle WorkflowHandle = NULL;
    WorkflowHandle = Class_ConvertFromInstanceId(Sender);
    if (WorkflowHandle == NULL)
        return FALSE;
    IWorkflow_RegisterTaskHandler(WorkflowHandle, &PriorityTask_INTERFACE);
    return TRUE;
}

/*********************************************************************/

static int32 Interop_Notification_OnUnregisterTaskHandler(void *UserPtr, char *Type, char *Notification, void *Sender, echandle DictionaryHandle)
{
    echandle WorkflowHandle = NULL;
    WorkflowHandle = Class_ConvertFromInstanceId(Sender);
    if (WorkflowHandle == NULL)
        return FALSE;
    IWorkflow_UnregisterTaskHandler(WorkflowHandle, &PriorityTask_INTERFACE);
    return TRUE;
}

/*********************************************************************/

int32 Interop_Load(void)
{
    NotificationCenter_AddObserver("Workflow", "RegisterTaskHandlers", NULL, Interop_Notification_OnRegisterTaskHandler);
    NotificationCenter_AddObserver("Workflow", "UnregisterTaskHandlers", NULL, Interop_Notification_OnUnregisterTaskHandler);
    return TRUE;
}

int32 Interop_Unload(void)
{
    NotificationCenter_RemoveObserver("Workflow", "RegisterTaskHandlers", NULL, Interop_Notification_OnRegisterTaskHandler);
    NotificationCenter_RemoveObserver("Workflow", "UnregisterTaskHandlers", NULL, Interop_Notification_OnUnregisterTaskHandler);
    return TRUE;
}

/*********************************************************************/
