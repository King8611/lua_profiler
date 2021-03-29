#pragma comment(lib, "lua53.lib")
#include"lua.h"
#include"lualib.h"
#include "lauxlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Info.h"
#include "ProfileStruct.h"

void PrintLuaStack(lua_State *L);
static int start(lua_State *L);

struct FcuntionInfo *info;
struct HookStack *hStack;

static void call_hook(lua_State *L, lua_Debug *ar) {
	
}

static void return_hook(lua_State *L, lua_Debug *ar) {
	
}

static void hook(lua_State *L, lua_Debug *ar) {
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

static int start(lua_State *L) {
	printf("start\n");
	/*info = malloc(sizeof(struct Info));
	memset(info, 0, sizeof(info));*/
	lua_sethook(L, hook, LUA_MASKCALL|LUA_MASKRET, 1);

	return 0;
}

static int stop(lua_State *L) {

}

static int logInfo(lua_State *L){
	
}

lua_CFunction get_tab(lua_State *l) {
	printf("get_tab\n");
	const char *t[10] = {"start"};
	const lua_CFunction f[3] = {start};
	lua_newtable(l);

	for (int i = 0; i < 1; i++) {
		lua_pushstring(l, t[i]);
		lua_pushcfunction(l, f[i]);
		lua_settable(l, -3);
	}

	return 1;
}

int main()
{
	char *t = (char*)malloc(20);
	t[0] = 'a';
	printf("%c\n", t[0]);

	lua_State *l = luaL_newstate();
	luaL_openlibs(l);

	lua_pushcfunction(l, get_tab);
	lua_setglobal(l, "profile");

	luaL_dofile(l, "test.lua");
	lua_close(l);
	system("pause");
	return 0;
}

void PrintLuaStack(lua_State *L)
{
	lua_State* pLuaState = L;

	int stackTop = lua_gettop(pLuaState);//获取栈顶的索引值
	int nIdx = 0;
	int nType;

	//printf(" element count: %d\n", stackTop);

	printf("--栈顶(v)(%d)--\n", stackTop);

	//显示栈中的元素
	for (nIdx = stackTop; nIdx > 0; --nIdx)
	{
		nType = lua_type(pLuaState, nIdx);
		printf("(i:%d) %s(%s)\n", nIdx, lua_typename(pLuaState, nType), lua_tostring(pLuaState, nIdx));
	}

	printf("--栈底--\n");
}



//
struct profiler_log { 
	int linedefined;
	char source[LUA_IDSIZE];
};

struct profiler_count {
	int total;
	int index;
};

static void
profiler_hook(lua_State *L, lua_Debug *ar) {
	if (lua_rawgetp(L, LUA_REGISTRYINDEX, L) != LUA_TUSERDATA) {
		lua_pop(L, 1);
		return;
	}
	struct profiler_count * p = lua_touserdata(L, -1);
	lua_pop(L, 1);
	struct profiler_log * log = (struct profiler_log *)(p + 1);
	int index = p->index++;
	while (index >= p->total) {
		index -= p->total;
	}
	if (lua_getinfo(L, "S", ar) != 0) {
		log[index].linedefined = ar->linedefined;
		strcpy_s(log[index].source, sizeof ar->short_src, ar->short_src);
	}
	else {
		log[index].linedefined = 1;
		strcpy_s(log[index].source,sizeof("[unknown]"), "[unknown]");
	}
}

static int
lstart(lua_State *L) {
	printf("lstart\n");
	lua_State *cL = L;
	int args = 0;
	if (lua_isthread(L, 1)) {
		cL = lua_tothread(L, 1);
		args = 1;
	}
	int count = luaL_optinteger(L, args + 1, 1000);
	int interval = luaL_optinteger(L, args + 2, 100);
	struct profiler_count * p = lua_newuserdata(L, sizeof(struct profiler_count) + count * sizeof(struct profiler_log));
	p->total = count;
	p->index = 0;
	lua_pushvalue(L, -1);
	lua_rawsetp(L, LUA_REGISTRYINDEX, cL);
	lua_sethook(cL, profiler_hook, LUA_MASKCOUNT, interval);

	return 0;
}

//
//static int
//lstop(lua_State *L) {
//	printf("stop");
//	lua_State *cL = L;
//	if (lua_isthread(L, 1)) {
//		cL = lua_tothread(L, 1);
//	}
//	if (lua_rawgetp(L, LUA_REGISTRYINDEX, cL) != LUA_TNIL) {
//		lua_pushnil(L);
//		lua_rawsetp(L, LUA_REGISTRYINDEX, cL);
//		lua_sethook(cL, NULL, 0, 0);
//	}
//	else {
//		return luaL_error(L, "thread profiler not begin");
//	}
//
//	return 0;
//}
//
//static int
//linfo(lua_State *L) {
//	printf("linfo\n");
//	lua_State *cL = L;
//	if (lua_isthread(L, 1)) {
//		cL = lua_tothread(L, 1);
//	}
//	if (lua_rawgetp(L, LUA_REGISTRYINDEX, cL) != LUA_TUSERDATA) {
//		return luaL_error(L, "thread profiler not begin");
//	}
//	struct profiler_count * p = lua_touserdata(L, -1);
//	struct profiler_log * log = (struct profiler_log *)(p + 1);
//	lua_newtable(L);
//	int n = (p->index > p->total) ? p->total : p->index;
//	int i;
//	for (i = 0; i < n; i++) {
//		luaL_getsubtable(L, -1, log[i].source);
//		lua_rawgeti(L, -1, log[i].linedefined);
//		int c = lua_tointeger(L, -1);
//		lua_pushinteger(L, c + 1);
//		// subtbl, c, c + 1
//		lua_rawseti(L, -3, log[i].linedefined);
//		lua_pop(L, 2);
//	}
//	lua_pushinteger(L, p->index);
//	return 2;
//}
//
//int get_tab(lua_State *l) {
//	printf("get_tab\n");
//	const char *t[10] = { "start","stop", "info" };
//	const lua_CFunction f [3]= { lstart,lstop,linfo};
//	lua_newtable(l);
//
//	for (int i = 0; i < 3; i++) {
//		lua_pushstring(l, t[i]);
//		lua_pushcfunction(l, f[i]);
//		lua_settable(l, -3);
//	}
//
//	return 1;
//}
//
//LUAMOD_API int
//luaopen_profiler(lua_State *L) {
//	luaL_checkversion(L);
//	luaL_Reg l[] = {
//		{ "start", lstart },
//		{ "stop", lstop },
//		{ "info", linfo },
//		{ NULL, NULL },
//	};
//	luaL_newlib(L, l);
//	return 1;
//}
