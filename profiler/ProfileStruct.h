#pragma once
#ifndef info_h
#define info_h
//这个用来定义profile数据结构
#include "info.h"
#include <stdlib.h>
#define MAX_STACK_SIZE (1000)

typedef struct HookStack {
	FunctionInfo *info[MAX_STACK_SIZE];
	int size;
}HookStack;

HookStack *CreateHookStack();
FunctionInfo *Top(const HookStack *hookStack);
void pop(HookStack *hookStack);
void push(HookStack *hookStack, FunctionInfo *info);

#endif // !info_h