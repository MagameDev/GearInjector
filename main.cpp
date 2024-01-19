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

    void (*InjectionCall)(void);
    InjectionCall = (void(*)(void))GetProcAddress(LoadLibraryA(xor_a("D3DGearLoad64.dll")), (LPCSTR)1);
    InjectionCall();

    printf(xor_a("Injection success\n"));
    Sleep(5000);

    return 0;
}
