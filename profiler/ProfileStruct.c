#pragma once
#include "ProfileStruct.h"
#include"lualib.h"
#include <string.h>

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

extern void HookStackDestroyed(HookStack *hookStack) {
	free(hookStack);
}

extern Vector *CreateVector(size_t dataSize) {
	Vector *vector = malloc(sizeof(Vector));
	vector->capacity = STRUCT_BASE_SIZE * dataSize;

	vector->dataArr = malloc(vector->capacity);
	vector->size = 0;
	vector->dataSize = dataSize;

	return vector;
}

extern void VectorPush(Vector *vector, void *data) {
	if (vector->size == vector->capacity) {
		VectorGrow(vector);
	}
	VectorSetValue(vector, vector->size, data);
	vector->size++;
}
extern void VectorSetValue(Vector *vector, size_t index, void *data) {
	if (index >= vector->size) {
		ERROR("Vector SetValue Error, index = %d, size = %d", index, vector->size);
		return;
	}
	void *t = (char*)vector->dataArr + index*vector->dataSize;
	memcpy(t, &data, vector->dataSize);
}

extern void VectorDestroyed(Vector *vector) {
	free(vector->dataArr);
	free(vector);
}

extern void *VectorGetData(const Vector *vector, const size_t index) {
	if (index >= vector->size*vector->dataSize) {
		ERROR("Vector GetData Error, index = %d, size = %d", index, vector->size);
		return;
	}
	void *ret = (char*)vector->dataArr + index * vector->dataSize;
	return ret;
}

extern size_t VectorGetSize(const Vector *vector) {
	return vector->size;
}
extern int VectorFind(const Vector *vector, void *data, CmpFunc cmp) {
	if (cmp == NULL) cmp = Cmp;

	for (int i = 0; i < vector->size; i++) {
		void *t = (char*)vector->dataArr + i * vector->dataSize;
		if (Cmp(t, &data, vector->dataSize)) {
			return i;
		}
	}
	return -1;
}

extern CmpFunc Cmp(const void* a1, const void* a2, size_t size) {
	for (int i = 0; i < size; i++) {
		if (*((char*)a1+i) != *((char*)a2+i)) {
			return false;
		}
	}
	return true;
}

void VectorGrow(Vector *vector) {
	vector->capacity *= GROWTH_FACTOR;
	vector->dataArr = realloc(vector->dataArr, vector->capacity);
}