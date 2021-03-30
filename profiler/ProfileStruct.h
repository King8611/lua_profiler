#pragma once
#ifndef info_h
#define info_h
//�����������profile���ݽṹ
#include "info.h"
#include <stdlib.h>
#define MAX_STACK_SIZE (1000)

typedef struct HookStack {
	FunctionInfo *info[MAX_STACK_SIZE];
	int size;
}HookStack;

HookStack *CreateHookStack();
FunctionInfo *HookStackTop(const HookStack *hookStack);
void HookStackPop(HookStack *hookStack);
void HookStackPush(HookStack *hookStack, FunctionInfo *info);
void HookStackDestroyed(HookStack *HookStack);

#endif // !info_h