#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int activo = atoi(argv[1]); // 1
	int dep_id = atoi(argv[2]); // 1
	int machine = atoi(argv[3]); // 672
	printf("Arguments: %d %d %d", activo, dep_id, machine);
	char *machine_no[900] = {0};
	char command[5];
	machine_no[502] = "\\\\.\\COM25";
	machine_no[508] = "\\\\.\\COM12";
	machine_no[514] = "\\\\.\\COM15";
	machine_no[597] = "\\\\.\\COM11";
	machine_no[598] = "\\\\.\\COM13";
	machine_no[599] = "\\\\.\\COM14";
	machine_no[670] = "\\\\.\\COM24";
	machine_no[795] = "\\\\.\\COM21";
	machine_no[845] = "\\\\.\\COM22";
	machine_no[859] = "\\\\.\\COM23";
	machine_no[564] = "\\\\.\\COM25";
	machine_no[668] = "\\\\.\\COM26";
	machine_no[669] = "\\\\.\\COM18";
	machine_no[671] = "\\\\.\\COM17";
	machine_no[672] = "\\\\.\\COM28";
	machine_no[673] = "\\\\.\\COM27";
	if (activo == 1)
	{
		if(dep_id == 1) {
			command[0] = 'R';
			command[1] = '0';
			command[2] = '6';
			command[3] = '\r';
			command[4] = '\n';
		} 
		else if(dep_id == 2) {
			command[0] = 'R';
			command[1] = '0';
			command[2] = 'A';
			command[3] = '\r';
			command[4] = '\n';
		}
		else if(dep_id == 3) {
			command[0] = 'R';
			command[1] = '1';
			command[2] = '2';
			command[3] = '\r';
			command[4] = '\n';
		}

		else if(dep_id == 4) {
			command[0] = 'R';
			command[1] = '2';
			command[2] = '2';
			command[3] = '\r';
			command[4] = '\n';
		} 
	} else if(activo == 0)
	{
		command[0] = 'R';
		command[1] = '0';
		command[2] = '1';
		command[3] = '\r';
		command[4] = '\n';
	}
	HANDLE hSerial;
	hSerial = CreateFile(machine_no[machine] , GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	//Do some settings
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	GetCommState(hSerial, &dcbSerialParams);
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	SetCommState(hSerial, &dcbSerialParams);
	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(hSerial, &timeout);
	// Send specified text (remaining command line arguments)
	DWORD bytes_written, total_bytes_written = 0;
	fprintf(stderr, "Sending bytes...\n");
	if(!WriteFile(hSerial, command, 5, &bytes_written, NULL)){
	}
	// Close serial port
	fprintf(stderr, "Closing serial port...");
	if (CloseHandle(hSerial) == 0)
	{
		fprintf(stderr, "Error\n");
		return 1;
	}
	fprintf(stderr, "OK\n");
	//system("pause");
	// exit normally
	return 0;
}
