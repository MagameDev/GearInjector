#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

namespace Utils {
	void CreateFileFromBytes(const std::vector<unsigned char>& bytes, const std::string& filename) {
        remove(filename.c_str());
		std::ofstream file(filename, std::ios::out | std::ios::binary);
		if (file.is_open()) {
			file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
			file.close();
		}
	}
    bool GetFileCreationTime(const std::wstring& filePath, SYSTEMTIME* creationTime) {
        HANDLE hFile = CreateFileW(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (hFile == INVALID_HANDLE_VALUE) {
            std::cerr << "Error opening file: " << GetLastError() << std::endl;
            return false;
        }

        FILETIME ftCreate, ftAccess, ftWrite;

        if (GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {
            FileTimeToSystemTime(&ftCreate, creationTime);
            CloseHandle(hFile);
            return true;
        }

        CloseHandle(hFile);
        return false;
    }
    SYSTEMTIME GetSystemTime()
    {
        SYSTEMTIME currentTime;
        GetSystemTime(&currentTime);
        return currentTime;
    }
    bool SetSystemTime(const SYSTEMTIME& newSystemTime)
    {
        if (SetSystemTime(&newSystemTime))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
