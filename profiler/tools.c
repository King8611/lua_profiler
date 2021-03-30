#include "tools.h"
#include "lua.h"
void dfsPirnt(FunctionInfo *info, int t) {
	if (info == NULL) return;
	for (int j = 0; j < t; j++)printf("--");
	printf("%s %d\n", info->fName, info->count);
	for (int i = 0; i < info->fCount; i++) {
		dfsPirnt(info->infos[i], t+1);
	}
}
extern void PrintFunctionInfo(FunctionInfo *info, int isPrintChild) {
	if (info == NULL) return;
	if (!isPrintChild) {
		printf("PrintFunctionInfo：%s %d\n", info->fName, info->fCount);
	}
	dfsPirnt(info, 0);
}

extern void PrintLuaStack(lua_State *L)
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

extern void ERROR(const char *format, ...) {
	//printf("PROFILER ERROR ");
	//printf(format, ...);

}
extern void WARNING(const char *format, ...) {

}
extern void LOG(const char *format, ...) {

}
