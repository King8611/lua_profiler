#pragma once
#ifndef Info_H
#define Info_H
//�������������ÿ�������ĵ�����Ϣ��
#include "lua.h"

#define MAX_FUNCTION_NNAME_SIZE 50
#define MAX_CALL 100
struct FunctionInfo
{
	const char fName[MAX_FUNCTION_NNAME_SIZE];			//������
	int count;									//�����������ô���
	struct FunctionInfo * infos[MAX_CALL];				//���õ��ĺ�����Ϣ
	int fCount;									//�������������ĸ���
};
typedef struct FunctionInfo FunctionInfo;

FunctionInfo *TryGetChildInfo(FunctionInfo *parent, lua_Debug *ar);
void BuildFunctionName(char *s, const lua_Debug *ar);

//ͨ��functionName����һ��FunctionInfo.
FunctionInfo *CreateFunctionInfo(char *fName);

void AddChild(FunctionInfo *parent, const FunctionInfo *child);
void CountToFunctionInfo(FunctionInfo *info);

void FunctionInfoDestroyed(FunctionInfo *info, int isDestoryChild);
#endif // !1