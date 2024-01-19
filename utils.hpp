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
}
