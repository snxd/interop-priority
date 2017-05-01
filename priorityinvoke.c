#include "interoplib.h"

#include "jansson.h"
#include "jansson_private.h"

#include "priority.h"

/*********************************************************************/

int32 Priority_Invoke(echandle PriorityHandle, char *String, char *ResultString, int32 ResultStringLength)
{
    char *MethodName = NULL;
    char MethodResultString[INTEROP_MAXSTRING];
    char *JSONDumpString = NULL;
    json_t *JSON = NULL;
    json_t *JSONReturnRoot = NULL;
    json_t *JSONReturn = NULL;
    json_t *JSONMethod = NULL;
    json_error_t JSONError;
    int32 RetVal = FALSE;

    memset(MethodResultString, 0, INTEROP_MAXSTRING);
    JSON = json_loads(String, 0, &JSONError);
    if (JSON == FALSE)
        return FALSE;

    RetVal = (JSONMethod = json_object_get(JSON, "method")) != NULL;

    if (RetVal == TRUE)
        RetVal = json_is_string(JSONMethod);

    if (RetVal == TRUE)
    {
        MethodName = (char *)json_string_value(JSONMethod);
        RetVal = MethodName != NULL;
    }

    if (RetVal == TRUE && String_Compare(MethodName, "setLow") == TRUE)
        RetVal = (JSONReturn = json_boolean(Priority_SetLow())) != NULL;
    else if (RetVal == TRUE && String_Compare(MethodName, "setNormal") == TRUE)
        RetVal = (JSONReturn = json_boolean(Priority_SetNormal())) != NULL;
    else if (RetVal == TRUE && String_Compare(MethodName, "setHigh") == TRUE)
        RetVal = (JSONReturn = json_boolean(Priority_SetHigh())) != NULL;

    // Set json return value
    if (RetVal == TRUE)
        RetVal = (JSONReturnRoot = json_object()) != NULL;
    if (RetVal == TRUE)
        RetVal = (json_object_set_new(JSONReturnRoot, "returnValue", JSONReturn) == 0);

    if (RetVal == TRUE)
        RetVal = (JSONDumpString = json_dumps(JSONReturnRoot, 0)) != NULL;

    if (RetVal == TRUE)
        RetVal = ((signed)String_Length(JSONDumpString) < ResultStringLength);
    if (RetVal == TRUE)
        String_CopyLength(ResultString, JSONDumpString, ResultStringLength);

    if (JSONDumpString != NULL)
        jsonp_free(JSONDumpString);
    if (JSONReturnRoot != NULL)
        json_decref(JSONReturnRoot);
    if (JSON != NULL)
        json_decref(JSON);

    return RetVal;
}

/*********************************************************************/
