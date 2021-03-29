#pragma once
#include"Info.h"

#include <string.h>
#include <stdlib.h>
extern void CreateFunctionInfo(FunctionInfo *info, char *fName) {
	memset(info, 0, sizeof(info));
	strcpy_s(info->fName, sizeof(info->fName), fName);
}

extern FunctionInfo *TryGetChildInfo(FunctionInfo *parent, lua_Debug *ar) {
	char *tmp[MAX_Function_Name_SIZE];
	BuildFunctionName(ar, tmp);
	for (int i = 0; i < parent->fCount; i++) {
		if (strcmp(tmp, parent->infos[i]->fName)) {
			return parent->infos[i];
		}
	}
	FunctionInfo *p = malloc(sizeof(FunctionInfo));
	CreateFunctionInfo(p, tmp);
	AddChild(parent, p);
}

extern void AddChild(FunctionInfo *parent, const FunctionInfo *child) {
	if (parent->fCount == MAX_CALL) {
		printf("ERROR FunctionInfo'Call is Max");
		return;
	}
	parent->infos[parent->fCount++] = child;
}

extern void BuildFunctionName(char *s, const lua_Debug *ar) {
	sprintf_s(s, sizeof(s), "%s:%d %s", ar->short_src, ar->currentline, ar->name);
	
}