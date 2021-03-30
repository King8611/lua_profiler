#pragma once
#include"Info.h"

#include <string.h>
#include <stdlib.h>
extern FunctionInfo *CreateFunctionInfo(char *fName) {
	FunctionInfo *info = malloc(sizeof(FunctionInfo));
	if (info == NULL) {
		return NULL;
	}
	memset(info, 0, sizeof(*info));
	strcpy_s(info->fName, MAX_FUNCTION_NNAME_SIZE, fName);
	return info;
}

extern FunctionInfo *TryGetChildInfo(FunctionInfo *parent,lua_Debug *ar) {
	if (parent == NULL) {
		return NULL;
	}
	char tmp[MAX_FUNCTION_NNAME_SIZE];
	BuildFunctionName(tmp, ar);
	for (int i = 0; i < parent->fCount; i++) {
		if (strcmp(tmp, parent->infos[i]->fName) == 0) {
			return parent->infos[i];
		}
	}
	FunctionInfo * p = CreateFunctionInfo(tmp);

	AddChild(parent, p);

	return p;
}

extern void AddChild(FunctionInfo *parent, const FunctionInfo *child) {
	if (parent->fCount == MAX_CALL) {
		printf("ERROR FunctionInfo'Call is Max");
		return;
	}
	parent->infos[parent->fCount++] = child;
}

extern void BuildFunctionName(char *s, const lua_Debug *ar) {
	sprintf_s(s, MAX_FUNCTION_NNAME_SIZE, "%s:%d %s", ar->short_src, ar->currentline, ar->name);
}

extern void CountToFunctionInfo(FunctionInfo *info) {
	info->count++;
}

extern void FunctionInfoDestroyed(FunctionInfo *info, int isDestoryChild) {
	if (info == NULL) {
		return;
	}
	if (!isDestoryChild) {
		free(info);
		return;
	}
	for (int i = 0; i < info->fCount; i++) {
		FunctionInfoDestroyed(info->infos[i], isDestoryChild);
	}
	free(info);
}