#include "tools.h"
#include "lua.h"
#include <time.h>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
void dfsPirnt(FunctionInfo *info, int t) {
	if (info == NULL) return;
	for (int j = 0; j < t; j++)printf("--");
	printf("%s  %d  %d.%06d\n", info->fName, info->count,info->costTime.tv_sec, info->costTime.tv_usec);
	for (int i = 0; i < info->fCount; i++) {
		dfsPirnt(info->infos[i], t+1);
	}
}
//void PrintFunctionInfo(FunctionInfo *info, int isPrintChild);

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

extern int GetTimeOfDay(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}