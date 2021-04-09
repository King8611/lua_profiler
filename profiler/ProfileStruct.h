#pragma once
#ifndef info_h
#define info_h
//这个用来定义profile数据结构
#include "info.h"
#include <stdlib.h>
#define MAX_STACK_SIZE (1000)
#define STRUCT_BASE_SIZE (10)		//容器的基础长度
#define GROWTH_FACTOR (2)			//容器的增长系数
typedef bool(*CmpFunc)(const void*, const void*, size_t);

typedef struct HookStack {
	FunctionInfo *info[MAX_STACK_SIZE];
	size_t size;
}HookStack;

typedef struct ListNode {
	void *value;
	struct ListNode *next;
	struct ListNode *pre;
}ListNode;

typedef struct List{
	ListNode *Top;
	size_t size;
}List;

typedef struct Map {
	ListNode *hasMap;
	size_t size;
}Map;

typedef struct Vector {
	void *dataArr;
	size_t dataSize;		//每个元素的大小
	size_t size;
	size_t capacity;
}Vector;

CmpFunc Cmp(const void*, const void*, size_t);

Vector *CreateVector(size_t dataSize);
void VectorPush(Vector *vector, void *data);
void VectorDestroyed(Vector *vector);
void *VectorGetData(const Vector *vector, const size_t index);
size_t VectorGetSize(const Vector *vector);
int VectorFind(const Vector *vector, void *data, CmpFunc cmp);
void VectorGrow(Vector *vector);
void VectorSetValue(Vector *vector, size_t index, void *data);


HookStack *CreateHookStack();
FunctionInfo *HookStackTop(const HookStack *hookStack);
void HookStackPop(HookStack *hookStack);
void HookStackPush(HookStack *hookStack, FunctionInfo *info);
void HookStackDestroyed(HookStack *HookStack);

#endif // !info_h