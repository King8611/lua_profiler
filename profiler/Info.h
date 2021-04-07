#pragma once
#ifndef Info_H
#define Info_H
//�������������ÿ�������ĵ�����Ϣ��
#include "lua.h"
#include <windows.h>
#include "tools.h"
#define MAX_FUNCTION_NNAME_SIZE 50
#define MAX_CALL 100
typedef struct FunctionInfo
{
	const char fName[MAX_FUNCTION_NNAME_SIZE];			//������
	int count;											//�����������ô���
	struct FunctionInfo * infos[MAX_CALL];				//���õ��ĺ�����Ϣ
	int fCount;											//�������������ĸ���
	struct timeval lastTime;							//���һ��info��Ϣ����ʱ�䡣
	struct timeval costTime;							//���������ܻ���
}FunctionInfo;

FunctionInfo *TryGetChildInfo(FunctionInfo *parent, lua_Debug *ar);
void BuildFunctionName(char *s, const lua_Debug *ar);

//ͨ��functionName����һ��FunctionInfo.
FunctionInfo *CreateFunctionInfo(char *fName);

void AddChild(FunctionInfo *parent, const FunctionInfo *child);
void CountToFunctionInfo(FunctionInfo *info);

void FunctionInfoDestroyed(FunctionInfo *info, int isDestoryChild);

void RefreshFunctionTime(FunctionInfo *info);

#endif //