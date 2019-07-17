#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	char *machine_no[900] = {0};
	machine_no[502] = \\\\.\\COM25;
	HANDLE hSerial;
	//Do some settings
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;
	DWORD bytes_written, total_bytes_written = 0;
	for (int i = 0; i < 900; i++)
	{
		if (machine_no[i] != 0)
		{
			hSerial = CreateFile(machine_no[i] ,GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if (hSerial == INVALID_HANDLE_VALUE)
			{
				printf("Unable to open serial port\n");
			}
			//GetCommState(hSerial, &dcbSerialParams);
			if (SetCommState(hSerial, &dcbSerialParams))
			{
				printf("Unable to configure serial port\n");
			}	 
			if (!SetCommTimeouts(hSerial, &timeout))
			{
				printf("Unable to configure serial timeouts\n");
			}	 
			printf("Sending bytes...\n");
			if(!WriteFile(hSerial, "R01\r\n", 5, &bytes_written, NULL)){
				printf("can't write to serial...\n");
			}
			// Close serial port
			printf("Closing serial port...\n");
			if (CloseHandle(hSerial) == 0)
			{
				printf("Error\n");
			}
			printf("OK\n");
		} 
	}
	return 0;
}
