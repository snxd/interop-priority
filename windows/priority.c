#include "interoplib.h"

#include <windows.h>

#include "priority.h"

/*********************************************************************/

int32 Priority_SetLow(void)
{
    SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
    OutputDebugStringA("Current process priority set to Low\n");
    return TRUE;
}

int32 Priority_SetNormal(void)
{
    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    OutputDebugStringA("Current process priority set to Normal\n");
    return TRUE;
}

int32 Priority_SetHigh(void)
{
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    OutputDebugStringA("Current process priority set to High\n");
    return TRUE;
}

/*********************************************************************/
