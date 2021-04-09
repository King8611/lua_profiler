#pragma once
#include"Info.h"

#include <string.h>
#include <stdlib.h>
#include "tools.h"
extern FunctionInfo *CreateFunctionInfo(char *fName) {
	FunctionInfo *info = malloc(sizeof(FunctionInfo));
	if (info == NULL) {
		return NULL;
	}
	memset(info, 0, sizeof(*info));
	strcpy_s(info->fName, MAX_NAME_SIZE, fName);
	return info;
}

extern FunctionInfo *TryGetChildInfo(FunctionInfo *parent,lua_Debug *ar) {
	if (parent == NULL) {
		return NULL;
	}
	char tmp[MAX_NAME_SIZE];
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
	sprintf_s(s, MAX_NAME_SIZE, "%s:%d %s", ar->short_src, ar->linedefined, ar->name);
}

extern void CountToFunctionInfo(FunctionInfo *info) {
	info->count++;
	struct timeval nowTime;
	GetTimeOfDay(&nowTime, NULL);
	info->costTime.tv_sec += (nowTime.tv_sec) - (info->lastTime.tv_sec);
	info->costTime.tv_usec += (nowTime.tv_usec) - (info->lastTime.tv_usec);
	info->costTime.tv_usec += info->costTime.tv_sec * 1000000;
	info->costTime.tv_sec = info->costTime.tv_usec / 1000000;
	info->costTime.tv_usec %= 1000000;
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

extern void RefreshFunctionTime(FunctionInfo *info) {
	GetTimeOfDay(&info->lastTime, NULL);
}
