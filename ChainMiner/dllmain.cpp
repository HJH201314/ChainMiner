// dllmain.cpp : 定义 DLL 应用程序的入口点。
#pragma comment(lib, "../SDK/Lib/bedrock_server_api.lib")
#pragma comment(lib, "../SDK/Lib/bedrock_server_var.lib")
#pragma comment(lib, "../SDK/Lib/SymDBHelper.lib")
#pragma comment(lib, "../SDK/Lib/LiteLoader.lib")
#include "pch.h"
#include "LLAPI.h"

#define PLUGIN_NAME "ChainMiner"
#define PLUGIN_INTRO "A plugin enables players to mine quicker."
#define PLUGIN_VER_MAJAR 0
#define PLUGIN_VER_MINOR 0
#define PLUGIN_VER_REVISION 1

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        LL::registerPlugin(PLUGIN_NAME, PLUGIN_INTRO, LL::Version(PLUGIN_VER_MAJAR, PLUGIN_VER_MINOR, PLUGIN_VER_REVISION));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern void PluginInit();

extern "C" {
    _declspec(dllexport) void onPostInit() {
        std::ios::sync_with_stdio(false);
        PluginInit();
    }
}
