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
	FunctionInfo *parentInfo = HookStackTop(profile.hStack);
	if (parentInfo == NULL) {
		WARNING("STACK TOP IS NULL");
		return;
	}
	FunctionInfo *info = TryGetChildInfo(parentInfo, ar);
	RefreshFunctionTime(info);
	HookStackPush(profile.hStack, info);
}

void return_hook(lua_State *L, lua_Debug *ar) {
	char s[MAX_NAME_SIZE];
	BuildFunctionName(s, ar);
	FunctionInfo *info = HookStackTop(profile.hStack);
	if (strcmp(info->fName, s)) {
		WARNING("return not match call");
		return;
	}
	CountToFunctionInfo(info);
	HookStackPop(profile.hStack);
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
	profile.info = CreateFunctionInfo(base);
	profile.hStack = CreateHookStack();
	if (profile.info == NULL || profile.hStack == NULL) {
		ERROR("info or hStack is NULL");
	}
	HookStackPush(profile.hStack, profile.info);

	lua_sethook(L, hook, LUA_MASKCALL|LUA_MASKRET, 0);

	return 0;
}

extern lua_CFunction Stop(lua_State *L) {
	void DestroyedData();
	lua_sethook(L, NULL, 0, 0);
}

extern void DestroyedData() {
	HookStackDestroyed(profile.hStack);
	FunctionInfoDestroyed(profile.info, 1);
}

extern lua_CFunction LogInfo(lua_State *L){
	PrintFunctionInfo(profile.info, 1);
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

static void *l_alloc(void *ud, void *ptr, size_t osize, size_t nsize) {
	//(void)ud; (void)osize;  /* not used */
	//lua_State *l = ((struct lua_S *)ud)->l;
	//printf("ud = %p\n", ud);
	//printf("l = %p\n", l);
	if (nsize == 0) {
		free(ptr);
		return NULL;
	}
	else
		return realloc(ptr, nsize);
}

int main()
{
	profile.l = lua_newstate(l_alloc, &profile);
	luaL_openlibs(profile.l);

	lua_pushcfunction(profile.l, push_tab);
	lua_setglobal(profile.l, "profile");

	luaL_dofile(profile.l, "test.lua");
	lua_close(profile.l);
	
	system("pause");
	return 0;
}