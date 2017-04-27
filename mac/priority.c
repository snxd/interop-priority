#include "emu-core.h"
#include "emu-str.h"

#include <sys/resource.h>
#include <limits.h>

#include "priority.h"

/*********************************************************************/

// https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man2/setpriority.2.html

#define IDLE_PRIORITY_LOW       (20)
#define IDLE_PRIORITY_NORMAL    (0)
#define IDLE_PRIORITY_HIGH      (-20)

/*********************************************************************/

int32 Priority_SetLow(void)
{
    int32 Result = setpriority(PRIO_PROCESS, 0, IDLE_PRIORITY_LOW);
    Debug_Print("Current process priority set to Low (%d)\n", Result);
    return TRUE;
}

int32 Priority_SetNormal(void)
{
    int32 Result = setpriority(PRIO_PROCESS, 0, IDLE_PRIORITY_NORMAL);
    Debug_Print("Current process priority set to Normal (%d)\n", Result);
    return TRUE;
}

int32 Priority_SetHigh(void)
{
    int32 Result = setpriority(PRIO_PROCESS, 0, IDLE_PRIORITY_HIGH);
    Debug_Print("Current process priority set to High (%d)\n", Result);
    return TRUE;
}

/*********************************************************************/
