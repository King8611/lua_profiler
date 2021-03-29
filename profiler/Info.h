#pragma once
#ifndef Info_H
#define Info_H
//�������������ÿ�������ĵ�����Ϣ��
#include "lua.h"

#define MAX_Function_Name_SIZE 50
#define MAX_CALL 100
struct FunctionInfo
{
	const char * fName[MAX_Function_Name_SIZE];			//������
	int count;									//�����������ô���
	struct FunctionInfo * infos[MAX_CALL];				//���õ��ĺ�����Ϣ
	int fCount;									//�������������ĸ���
};
typedef struct FunctionInfo FunctionInfo;

FunctionInfo *TryGetChildInfo(FunctionInfo *parent, const lua_Debug *ar);
void BuildFunctionName(char *s, const lua_Debug *ar);

//ͨ��functionName����һ��FunctionInfo.
void CreateFunctionInfo(FunctionInfo *info, char *fName);
void AddChild(FunctionInfo *parent, const FunctionInfo *child);

#endif // !1