#pragma once
#ifndef TOOLS_H
#define TOOLS_H
#include "lua.h"
#include"Info.h"
void PrintLuaStack(lua_State *L);
void PrintFunctionInfo(FunctionInfo *info, int isPrintChild);
void ERROR(const char *format, ...);
void WARNING(const char *format, ...);
void LOG(const char *format, ...);
#endif