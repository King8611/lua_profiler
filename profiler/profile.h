#pragma once
#ifndef PROFILE_H
#define PROFILE_H
#include "Info.h"
#include "ProfileStruct.h"
typedef struct Profile {
	lua_State *l;
	FunctionInfo *info;
	HookStack *hStack;
	Vector memoryInfos;
}Profile;

Profile profile;

lua_CFunction Start(lua_State *L);
lua_CFunction Stop(lua_State *L);
void DestroyedData();

lua_CFunction LogInfo(lua_State *L);
lua_CFunction push_tab(lua_State *L);
const char *base = "base_info";
#endif // !PROFILE_H
