#include <filesystem>
#include "utils.hpp"
#include "xorstr.h"

#include "injector.h"
#include "cheat.h"

SYSTEMTIME oSystemTime;

int main(int argc, char* argv[])
{
    std::vector<unsigned char> cheatBytes(std::begin(cheat), std::end(cheat));
    Utils::CreateFileFromBytes(cheatBytes, xor_a("C:\\Windows\\System32\\d3dGear64.dll"));

    std::vector<unsigned char> injectorBytes(std::begin(injector), std::end(injector));
    Utils::CreateFileFromBytes(injectorBytes, xor_a("C:\\Windows\\System32\\d3dGearLoad64.dll"));


    SYSTEMTIME cTime;
    if (!Utils::GetFileCreationTime(xor_w(L"C:\\Windows\\System32\\d3dGear64.dll"), &cTime)) {
        printf("Failed get certificate time\n");
    }

    wchar_t cTimeString[256];
    swprintf_s(
        cTimeString, xor_w(L"%04d-%02d-%02d %02d:%02d:%02d"),
        cTime.wYear, cTime.wMonth, cTime.wDay,
        cTime.wHour, cTime.wMinute, cTime.wSecond);

    printf(xor_a("Certificate time: %ls\n"), cTimeString);

    oSystemTime = Utils::GetSystemTime();

    wchar_t oTimeString[256];
    swprintf_s(
        oTimeString, xor_w(L"%04d-%02d-%02d %02d:%02d:%02d"),
        oSystemTime.wYear, oSystemTime.wMonth, oSystemTime.wDay,
        oSystemTime.wHour, oSystemTime.wMinute, oSystemTime.wSecond);

    printf(xor_a("Old time: %ls\n"), oTimeString);

    if (!Utils::SetSystemTime(cTime)) {
        printf(xor_a("Set certificate time failed\n"));
    }

    void (*InjectionCall)(void);
    InjectionCall = (void(*)(void))GetProcAddress(LoadLibraryA(xor_a("D3DGearLoad64.dll")), (LPCSTR)1);
    InjectionCall();

    printf(xor_a("Injection success\n"));
    Sleep(5000);

    return Utils::SetSystemTime(oSystemTime);
}

// My discord: magamed05
// My discord: magamed05
// My discord: magamed05