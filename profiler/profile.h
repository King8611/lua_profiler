#pragma once
#ifndef PROFILE_H
#define PROFILE_H
#include "Info.h"
#include "ProfileStruct.h"
FunctionInfo *info;
HookStack *hStack;

void PrintLuaStack(lua_State *L);
lua_CFunction Start(lua_State *L);
lua_CFunction Stop(lua_State *L);
void DestroyedData();

lua_CFunction LogInfo(lua_State *L);
lua_CFunction push_tab(lua_State *L);
const char *base = "base_info";
#endif // !PROFILE_H
