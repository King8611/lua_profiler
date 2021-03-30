#pragma once
#include "ProfileStruct.h"
#include"lualib.h"

extern HookStack *CreateHookStack() {
	struct HookStack *p = malloc(sizeof(struct HookStack));
	memset(p, 0, sizeof(*p));
	return p;
}

extern FunctionInfo *HookStackTop(HookStack *hookStack) {
	if (hookStack->size == 0) {
		return NULL;
	}
	return hookStack->info[hookStack->size-1];
}

extern void HookStackPop(HookStack *hookStack) {
	if (hookStack->size == 0)return;
	hookStack->size--;
}

extern void HookStackPush(HookStack *hookStack, FunctionInfo *info) {
	if (hookStack->size == MAX_STACK_SIZE) {
		return;
	}
	hookStack->info[hookStack->size++] = info;
}

void HookStackDestroyed(HookStack *hookStack) {
	free(hookStack);
}