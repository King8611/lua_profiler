#pragma once
#ifndef Info_H
#define Info_H
//这个类用来定义每个函数的调用信息。
#include "lua.h"
#include <windows.h>
#include "tools.h"
#define MAX_FUNCTION_NNAME_SIZE 50
#define MAX_CALL 100
typedef struct FunctionInfo
{
	const char fName[MAX_FUNCTION_NNAME_SIZE];			//函数名
	int count;											//本函数被调用次数
	struct FunctionInfo * infos[MAX_CALL];				//调用到的函数信息
	int fCount;											//调用其他函数的个数
	struct timeval lastTime;							//最近一次info信息调用时间。
	struct timeval costTime;							//函数调用总花费
}FunctionInfo;

FunctionInfo *TryGetChildInfo(FunctionInfo *parent, lua_Debug *ar);
void BuildFunctionName(char *s, const lua_Debug *ar);

//通过functionName创建一个FunctionInfo.
FunctionInfo *CreateFunctionInfo(char *fName);

void AddChild(FunctionInfo *parent, const FunctionInfo *child);
void CountToFunctionInfo(FunctionInfo *info);

void FunctionInfoDestroyed(FunctionInfo *info, int isDestoryChild);

void RefreshFunctionTime(FunctionInfo *info);

#endif //