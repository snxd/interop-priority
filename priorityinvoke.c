#include "interoplib.h"
#include "dictionaryi.h"

#include "priority.h"

/*********************************************************************/

int32 Priority_Invoke(echandle PriorityHandle, echandle MethodDictionaryHandle, echandle ReturnDictionaryHandle)
{
    echandle ItemHandle = NULL;
    int32 RetVal = FALSE;
    char *Method = NULL;

    if (IDictionary_GetStringPtrByKey(MethodDictionaryHandle, "method", &Method) == FALSE)
        return FALSE;

    if (String_Compare(Method, "setLow") == TRUE)
        RetVal = Priority_SetLow();
    else if (String_Compare(Method, "setNormal") == TRUE)
        RetVal = Priority_SetNormal();
    else if (String_Compare(Method, "setHigh") == TRUE)
        RetVal = Priority_SetHigh();

    IDictionary_AddBoolean(ReturnDictionaryHandle, "returnValue", RetVal, &ItemHandle);

    return TRUE;
}

/*********************************************************************/
