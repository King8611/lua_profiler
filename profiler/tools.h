#pragma once
#ifndef TOOLS_H
#define TOOLS_H
#include "lua.h"
#include"Info.h"
#define ERROR(format, ...) printf("PROFILER ERROR:" format "\n", ##__VA_ARGS__)
#define WARNING(format, ...) printf("PROFILER WARNING:" format "\n", ##__VA_ARGS__)
#define LOG(format, ...) printf("PROFILER LOG:" format "\n", ##__VA_ARGS__)
typedef char bool;

int GetTimeOfDay(struct timeval *tp, void *tzp);
void PrintLuaStack(lua_State *L);
void PrintFunctionInfo(struct FunctionInfo *info, int isPrintChild);
#endif