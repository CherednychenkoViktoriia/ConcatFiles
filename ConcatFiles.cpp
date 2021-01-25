#include <iostream>
#include <windows.h>

int main(int argc, char** argv)
{
    if (argc <= 2) {
        std::cerr << "Invalid arguments";
        return -1;
    }
    std::string folderPath = argv[1];
    std::string resFilePath = folderPath + "\\res.txt";
    HANDLE resFileHandle = CreateFileA(resFilePath.c_str(),
        FILE_APPEND_DATA,
        FILE_SHARE_READ,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (resFileHandle == INVALID_HANDLE_VALUE)
    {
        std::cout << "Could not open file " << resFilePath;
        return 0;
    }
    for (int i = 2; i < argc; ++i) {
        std::string filePath = folderPath + "\\" + argv[i];
        HANDLE file = CreateFileA(filePath.c_str(),
            GENERIC_READ,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (file == INVALID_HANDLE_VALUE)
        {
            std::cout << "Could not open file " << resFilePath;
            return 0;
        }
        char buf[1000] = {};
        DWORD bytesRes = 0;
        BOOL res = ReadFile(file, buf, sizeof(buf), &bytesRes, NULL);
        if (!res) {
            std::cout << "Could not read file " << resFilePath;
            return 0;
        }
        res = WriteFile(resFileHandle, buf, bytesRes, &bytesRes, NULL);
        if (!res) {
            std::cout << "Could not write file " << resFilePath;
            return 0;
        }
        CloseHandle(file);
    }
    CloseHandle(resFileHandle);
    return 0;
}