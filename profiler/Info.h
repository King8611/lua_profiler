#pragma once
#ifndef Info_H
#define Info_H
//这个类用来定义每个函数的调用信息。
#include "lua.h"

#define MAX_Function_Name_SIZE 50
#define MAX_CALL 100
struct FunctionInfo
{
	const char * fName[MAX_Function_Name_SIZE];			//函数名
	int count;									//本函数被调用次数
	struct FunctionInfo * infos[MAX_CALL];				//调用到的函数信息
	int fCount;									//调用其他函数的个数
};
typedef struct FunctionInfo FunctionInfo;

FunctionInfo *TryGetChildInfo(FunctionInfo *parent, const lua_Debug *ar);
void BuildFunctionName(char *s, const lua_Debug *ar);

//通过functionName创建一个FunctionInfo.
void CreateFunctionInfo(FunctionInfo *info, char *fName);
void AddChild(FunctionInfo *parent, const FunctionInfo *child);

#endif // !1