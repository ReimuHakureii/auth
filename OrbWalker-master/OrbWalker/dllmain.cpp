#include <Windows.h>
#include <thread>
#include <dxgi.h>
#include "../Kiero/kiero.h"
#include "orbwalker.hpp"
#include "offset.hpp"
#include "function.hpp"

using FnPresent = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT);

bool WINAPI HideThread(const HANDLE hThread) noexcept {
    // Implementation...
}

HRESULT WINAPI HKPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    // Implementation...
}

void InitGame() {
    InitOffset();
    InitFunction();
    InitOrb();
    while (GameTime() < 1.f) std::this_thread::sleep_for(std::chrono::seconds(1));
    PrintMessage("#00FFFF", "Noroby's League of Legends OrbWalker");
}

void InitializeKieroAndHook() {
    while (
        kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success ||
        kiero::bind(8, (void**)&oPresent, (void*)HKPresent) != kiero::Status::UnknownError
    );
}

void Start(void*) {
    HideThread(GetCurrentThread());
    // LoadLibrary(L"R3nzSkin.dll");
    InitGame();
    InitializeKieroAndHook();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        std::thread(Start, nullptr).detach();
    }
    return TRUE;
}
