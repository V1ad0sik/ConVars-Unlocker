#pragma once
#include "include.h"

HANDLE process;
DWORD clientBase;
//DWORD engineBase;
DWORD procId;

DWORD vstdlibModule;
DWORD vstdlibModule_size;

HWND hwnd;



DWORD getModuleBaseAddress(const char* name)
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);

        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, name)) {
                    CloseHandle(hSnap);
                    return (uintptr_t)modEntry.modBaseAddr;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
}

DWORD getModuleSize(const char* name)
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);

        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, name)) {
                    CloseHandle(hSnap);
                    return (uintptr_t)modEntry.modBaseSize;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
}
template <typename T>
T readMem(DWORD address)
{
    T buffer;
    ReadProcessMemory(process, (LPVOID)address, &buffer, sizeof(buffer), 0);
    return buffer;
}


template <typename T>
void writeMem(DWORD address, T value) { WriteProcessMemory(process, (LPVOID)address, &value, sizeof(value), 0); }



void get_info_game()
{
    hwnd = FindWindowA(0, "Counter-Strike: Global Offensive");
    GetWindowThreadProcessId(hwnd, &procId);

    clientBase = getModuleBaseAddress("client.dll");
    //engineBase = getModuleBaseAddress("engine.dll");

    vstdlibModule = getModuleBaseAddress("vstdlib.dll");
    vstdlibModule_size = getModuleSize("vstdlib.dll");

    process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
}


