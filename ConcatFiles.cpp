#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{     
    DWORD dwBytesRead, dwBytesWritten, dwPos;
    BYTE buff[4096] = {};
      
    HANDLE hFile = CreateFile(TEXT("res.txt"), 
        FILE_APPEND_DATA,         
        FILE_SHARE_READ,          
        NULL,                     
        CREATE_ALWAYS,            
        FILE_ATTRIBUTE_NORMAL,    
        NULL);                    

    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("Could not open res.txt.");
        return 0;
    }

    HANDLE hFile1 = CreateFile(TEXT("C:\\tmp\\ConcatFiles\\One.txt"),
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile1 == INVALID_HANDLE_VALUE)
    {
        printf("Could not open One.txt");
        return 0;
    }

    while (ReadFile(hFile1, buff, sizeof(buff), &dwBytesRead, NULL)
        && dwBytesRead > 0)
    {
        dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
        LockFile(hFile, dwPos, 0, dwBytesRead, 0);
        WriteFile(hFile, buff, dwBytesRead, &dwBytesWritten, NULL);
        UnlockFile(hFile, dwPos, 0, dwBytesRead, 0);
    }
    
    HANDLE hFile2 = CreateFile(TEXT("C:\\tmp\\ConcatFiles\\Two.txt"),
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile2 == INVALID_HANDLE_VALUE)
    {
        printf("Could not open Two.txt");
        return 0;
    }

    while (ReadFile(hFile2, buff, sizeof(buff), &dwBytesRead, NULL)
        && dwBytesRead > 0)
    {
        dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
        LockFile(hFile, dwPos, 0, dwBytesRead, 0);
        WriteFile(hFile, buff, dwBytesRead, &dwBytesWritten, NULL);
        UnlockFile(hFile, dwPos, 0, dwBytesRead, 0);
    }

    HANDLE hFile3 = CreateFile(TEXT("C:\\tmp\\ConcatFiles\\Three.txt"),
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile3 == INVALID_HANDLE_VALUE)
    {
        printf("Could not open Three.txt");
        return 0;
    }

    while (ReadFile(hFile3, buff, sizeof(buff), &dwBytesRead, NULL)
        && dwBytesRead > 0)
    {
        dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
        LockFile(hFile, dwPos, 0, dwBytesRead, 0);
        WriteFile(hFile, buff, dwBytesRead, &dwBytesWritten, NULL);
        UnlockFile(hFile, dwPos, 0, dwBytesRead, 0);
    }

    CloseHandle(hFile);
    CloseHandle(hFile1);
    CloseHandle(hFile2);
    CloseHandle(hFile3);

	return 0;
}