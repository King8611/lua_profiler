#pragma comment(lib, "lua53.lib")
#include"lua.h"
#include"lualib.h"
#include "lauxlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "profile.h"
#include "Info.h"
#include "ProfileStruct.h"
#include "tools.h"

void call_hook(lua_State *L, lua_Debug *ar) {
	FunctionInfo *parentInfo = HookStackTop(hStack);
	if (parentInfo == NULL) {
		WARNING("STACK TOP IS NULL");
		return;
	}
	FunctionInfo *info = TryGetChildInfo(parentInfo, ar);
	RefreshFunctionTime(info);
	HookStackPush(hStack, info);
}

void return_hook(lua_State *L, lua_Debug *ar) {
	char s[MAX_FUNCTION_NNAME_SIZE];
	BuildFunctionName(s, ar);
	FunctionInfo *info = HookStackTop(hStack);
	if (strcmp(info->fName, s)) {
		WARNING("return not match call");
		return;
	}
	CountToFunctionInfo(info);
	HookStackPop(hStack);
}

void hook(lua_State *L, lua_Debug *ar) {
	if (lua_getinfo(L, "nSltufL", ar) == 0) {
		return;
	}
	if (ar->what[0] == 'C')return;
	switch (ar->event)
	{
	case LUA_HOOKCALL:call_hook(L, ar); break;
	case LUA_HOOKRET:return_hook(L, ar); break;
	}
}

extern lua_CFunction Start(lua_State *L) {
	printf("start\n");
	info = CreateFunctionInfo(base);
	hStack = CreateHookStack();
	if (info == NULL || hStack == NULL) {
		ERROR("info or hStack is NULL");
	}
	HookStackPush(hStack, info);

	lua_sethook(L, hook, LUA_MASKCALL|LUA_MASKRET, 0);

	return 0;
}

extern lua_CFunction Stop(lua_State *L) {
	void DestroyedData();
	lua_sethook(L, NULL, 0, 0);
}

extern void DestroyedData() {
	HookStackDestroyed(hStack);
	FunctionInfoDestroyed(info, 1);
}

extern lua_CFunction LogInfo(lua_State *L){
	PrintFunctionInfo(info, 1);
}

extern lua_CFunction push_tab(lua_State *l) {
	printf("get_tab\n");
	const char *t[10] = {"start", "stop", "profile_log"};
	const lua_CFunction f[3] = {Start, Stop, LogInfo};
	lua_newtable(l);

	for (int i = 0; i < 3; i++) {
		lua_pushstring(l, t[i]);
		lua_pushcfunction(l, f[i]);
		lua_settable(l, -3);
	}

	return 1;
}

int main()
{
	lua_State *l = luaL_newstate();
	luaL_openlibs(l);

	lua_pushcfunction(l, push_tab);
	lua_setglobal(l, "profile");

	luaL_dofile(l, "test.lua");
	lua_close(l);
	system("pause");
	return 0;
}