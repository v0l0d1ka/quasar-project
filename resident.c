#include <stdio.h>
#include <windows.h>
int main ()
{
	// блок определения переменных
	//------------------------------------------------------
	FILE * pFile; // file handler declaration
	//buffer считывает данные из файла для формирования команды
	char buffer[15] = {0};
	//код символа при последовательном считывании файла
	int c = 0;
	// результат работы операции удаления файла
	int ret;
	//команда для запуска программы ком порта с параметрами 
	char str[50];
	//---------------***********------------------------------
	//стартует зеленую лампу на всех портах
	system("c:\\serial\\start_serial.exe");
	//бесконечный цикл в котором проверяется сущ-ет ли файл с параметрами
	while (1)
	{
		Sleep(5000); //ожидать пять секунд
		pFile=fopen ("c:\\serial.txt","r"); //открыть файл для чтения
		if (pFile==NULL) {perror ("Error opening file"); continue;} //обработать ошибку открытия файла
		else
		{
			int n = 0;
			do {
				c = fgetc (pFile); //считать очередной символ из файла
				buffer[n++] = c;
			} while (c != 'n');  //до тех пор пока не встретим "н"
			fclose (pFile); //закрыть файл
			ret = remove("c:\\serial.txt"); //удалить файл
			if(ret == 0) 
			{
				printf("File deleted successfully\n");
			}
			else 
			{
				printf("Error: unable to delete the file\n");
			}
			//вызвать программу для работы с портом и передать параметры
			strcpy(str, "c:\\serial\\serial.exe ");
			strcat(str, buffer);
			printf("sys command: %s\n", str);
			system(str);
			printf ("The file contains %s string .\n", buffer);
		}
		memset(buffer, 0, sizeof buffer); //сбросить буфер для чтения из файла
	} //end of while
	return 0;
}
