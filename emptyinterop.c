#include "interoplib.h"
#include "interopstub.h"

/*********************************************************************/

static int32 Interop_Notification_OnRegisterTaskHandler(void *UserPtr, char *Type, char *Notification, void *Sender, echandle JSONHandle)
{
    echandle WorkflowHandle = NULL;
    WorkflowHandle = Class_ConvertFromInstanceId(Sender);
    if (WorkflowHandle == NULL)
        return FALSE;
    IWorkflow_RegisterTaskHandler(WorkflowHandle, &PriorityTask_INTERFACE);
    return TRUE;
}

/*********************************************************************/

static int32 Interop_Notification_OnUnregisterTaskHandler(void *UserPtr, char *Type, char *Notification, void *Sender, echandle JSONHandle)
{
    echandle WorkflowHandle = NULL;
    WorkflowHandle = Class_ConvertFromInstanceId(Sender);
    if (WorkflowHandle == NULL)
        return FALSE;
    IWorkflow_UnregisterTaskHandler(WorkflowHandle, &PriorityTask_INTERFACE);
    return TRUE;
}

/*********************************************************************/

int32 Interop_CreateInstance(char *TypeName, char *InstanceId, int32 InstanceIdLength,
                             void *ExecuteUserPtr, Interop_ExecuteCallback Execute,
                             Interop_InvokeInstanceCallback *InvokeInstance,
                             Interop_ReleaseInstanceCallback *ReleaseInstance,
                             Interop_ProcessInstanceCallback *ProcessInstance,
                             void **UserPtr)
{
    if (strcmp(TypeName, "SSN.Priority") == 0)
    {
        *InvokeInstance = Priority_Invoke;
        *ReleaseInstance = NULL;
        *ProcessInstance = NULL;
        *UserPtr = NULL;
        return TRUE;
    }

    return FALSE;
}

int32 Interop_SetOverride(char *Key, void *Value)
{
    return TRUE;
}

int32 Interop_SetOption(char *Key, void *Value)
{
    return TRUE;
}

int32 Interop_Load()
{
    return TRUE;
}

int32 Interop_Unload()
{
    return TRUE;
}

/*********************************************************************/
