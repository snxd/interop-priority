#pragma once

#ifndef _PRIORITY_H_
#define _PRIORITY_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

int32 Priority_SetLow(void);
int32 Priority_SetNormal(void);
int32 Priority_SetHigh(void);

int32 Priority_Invoke(echandle PriorityHandle, char *String, char *ResultString, int32 ResultStringLength);

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
