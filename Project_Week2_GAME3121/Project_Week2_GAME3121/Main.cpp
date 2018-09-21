#include <iostream>
#include <windows.h>
#include <direct.h>

using namespace std;



	


int main()
{
	//Check for multiple instances and output a message saying an instance of the game is running or not running.
	HANDLE handle = CreateMutex(NULL, TRUE, "game3121");
	if (GetLastError() != ERROR_SUCCESS)
	{
		cout << "There is another instance running." << endl;
	}

	//Check for 300 MB of available storage and display a message saying if there is enough space or isn’t.
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const neededClusters = (300 * 1024 * 1024) /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters)
	{
		// if you get here you don’t have enough disk space!
		cout << "CheckStorage Failure : Not enough physical storage." << endl;
		return false;
	}
	//Check for available memory and display how much virtual memory is available and how much RAM is available.
	int MB = 1048576; // 1 MB = 1048576 bytes.
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	cout << "Total RAM: " << status.ullTotalPhys / MB << " MB" << endl;
	cout << "Virtual Memory: " << status.ullAvailVirtual / MB << " MB" << endl;



	//return false;




	// Display the CPU speed and architecture.
	
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 4;
	DWORD type = REG_DWORD;
	HKEY hKey;

	char ProcessorName[256];
	DWORD SBufSize = sizeof(ProcessorName);
	unsigned long type2 = REG_SZ;

	// open the key where the proc speed is hidden:
	long Error = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,KEY_READ, &hKey);


	if (Error == ERROR_SUCCESS) {
		// query the key:
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
		RegQueryValueEx(hKey, "ProcessorNameString", NULL,&type2, (LPBYTE)ProcessorName, &SBufSize);

		cout << "CPU Speed: " << dwMHz << "MHz" << endl;
		cout << ProcessorName << endl;
		system("pause");
		
		
	}
}
