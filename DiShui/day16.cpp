#include<iostream>
#include<Windows.h>

// ģ��CE�ڴ��������ܣ�����0x64
char data[] = {
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x07,0x09,
	0x00,0x20,0x10,0x03,0x03,0x0C,0x00,0x00,0x44,0x00,
	0x00,0x33,0x00,0x47,0x0C,0x0E,0x00,0x0D,0x00,0x11,
	0x00,0x00,0x00,0x02,0x64,0x00,0x00,0x00,0xAA,0x00,
	0x00,0x00,0x64,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x02,0x00,0x74,0x0F,0x41,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x0A,0x00,
	0x00,0x02,0x74,0x0F,0x41,0x00,0x06,0x08,0x00,0x00,
	0x00,0x00,0x00,0x64,0x00,0x0F,0x00,0x00,0x0D,0x00,
	0x00,0x00,0x23,0x00,0x00,0x64,0x00,0x00,0x64,0x00
};

 char userName[] = {
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x07,0x09,
	0x00,0x20,0x10,0x03,0x03,0x0C,0x00,0x00,0x44,0x00,
	0x00,0x33,0x00,0x47,0x0C,0x0E,0x00,0x0D,0x00,0x11,
	0x00,0x00,0x00,0x02,0x64,0x00,0x00,0x00,0xAA,0x00,
	0x00,0x00,0x64,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x02,0x00,0x74,0x0F,0x41,0x00,0x00,0x00,
	0x01,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x0A,0x00,
	0x00,0x02,0x57,0x4F,0x57,0x00,0x06,0x08,0x00,0x00,
	0x00,0x00,0x00,0x64,0x00,0x0F,0x00,0x00,0x0D,0x00,
	0x00,0x00,0x23,0x00,0x00,0x64,0x00,0x00,0x64,0x00
};

 // �������
void arrayPar(int array[20],int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
}

// strcmp
int strcmp_s(const char* dest, char* src)
{
	int i = 0;

	/*for (int i = 0; i < strlen(src); i++)
	{
		if (*(dest + i) != *(src + i))
		{
			return 1;
		}
	}*/

	while (*(dest + i) != '\0' && * (src + i) != '\0')
	{
		if (*(dest + i) != *(src + i))
		{
			return 1;
		}
		i++;
	}

	if (dest[i] != src[i]) {
		return 1;
	}
	return 0;
}

// strlen
int strlen_s(const char* data)
{
	if (data == NULL)
	{
		return NULL;
	}
	int i = 0;
	int count = 0;
	while (*(data + i) != '\0')
	{
		count++;
		i++;
	}
	return count;
}

// strcat
char* strcat_s(char* dest, char* src)
{
	if (*dest == NULL || *src == NULL)
	{
		return NULL;
	}
	/*char* ptr = dest;
	while (*dest !='\0')
	{
		dest++;
	}
	while (*src!='\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';*/

	char* newarray = new char[strlen(dest) + strlen(src)+1];
	char* ptr = newarray;
	while (*dest != '\0')
	{
		*newarray ++= *dest++;

	}
	while (*src != '\0')
	{
		*newarray++ = *src++;
	}

	*newarray = '\0';
	return ptr;

}

// strcpy
char* strcpy_s(char* dest, char* src)
{
	if (*dest == NULL || *src == NULL)
	{
		return NULL;
	}
	HWND hwnd = GetForegroundWindow();
	if (strlen(src) > strlen(dest))
	{
		MessageBoxA(hwnd, "Ŀ��ռ�̫С", "����", MB_OK);
		return NULL;
	}

	char* ptr = dest;
	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	return ptr;
}

void MoFangCE()
{
	// char�ֽ�
	char* pChar = (char*)data;
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
	{
		if (*(pChar + i) == 0x64)
		{
			printf("Addr-->%p value-->%x index-->%d\n", (pChar + i), *(pChar + i), i);
		}
	}

	printf("\n-------------------------------------------------\n");

	// short�ֽ�
	for (int i = 0; i < sizeof(data) - 1; i++) {
		uint16_t value = (uint16_t)data[i] |
			((uint16_t)data[i + 1] << 8);

		if (value == 0x0064) {
			printf("Addr-->%p value-->%x index-->%d\n", &data[i], data[i], i);
		}
	}

	printf("\n-------------------------------------------------\n");


	// int�ֽ�
	int* p = (int*)data;
	for (int i = 0; i < sizeof(data) - 3; i++) {
		uint32_t value = (uint32_t)data[i] |
			((uint32_t)data[i + 1] << 8) |
			((uint32_t)data[i + 2] << 16) |
			((uint32_t)data[i + 3] << 24);

		if (value == 0x00000064) {
			printf("Addr-->%p value-->%x index-->%d\n", &data[i], data[i], i);
		}
	}
}

// Ѱ�ҽ�ɫ����
char* FindeUserName( char* pData, char* pRoleName)
{
	if (pRoleName == NULL || pData == NULL)
	{
		return NULL;
	}
	
	// ��ȡ���ݳ��Ⱥͽ�ɫ���ֳ���
	size_t dataLength = strlen(pData);
	size_t roleNameLength = strlen(pRoleName);

	// ���������Բ��ҽ�ɫ����
	for (size_t i = 0; i <= dataLength - roleNameLength; i++) {
		// ��鵱ǰλ�ÿ�ʼ�����ַ����Ƿ����ɫ����ƥ��
		if (strncmp(&pData[i], pRoleName, roleNameLength) == 0) {
			// ����ƥ��ĵ�ַ
			return &pData[i];
		}
	}

	

	// ���������Բ��ҽ�ɫ����
	//for (size_t i = 0; i <= dataLength - roleNameLength; i++) {
	//	// ���赱ǰλ���ǽ�ɫ���ֵĿ�ʼ������Ƿ�ƥ��
	//	size_t j;
	//	for (j = 0; j < roleNameLength; j++) {
	//		if (pData[i + j] != pRoleName[j]) {
	//			break;
	//		}
	//	}
	//	// ���������ɫ���ֶ�ƥ����
	//	if (j == roleNameLength) {
	//		// ����ƥ��ĵ�ַ
	//		return &pData[i];
	//	}
	//}

	// ���û���ҵ������� 0
	return 0;
}

void pointerString()
{
	char* data = (char*)"AAAA";
}
int main()
{
	
	// ���鴫��
	/*int arry[] = { 1,2,3 };
	int arrySize = sizeof(arry) / sizeof(arry[0]);
	arrayPar(arry,arrySize);*/

	printf("\n-------------------------------------------------\n");

	// strcmp_s
	char* data1 = (char*)"ABCDAAA";
	char* data2 = (char*)"ABCDAAA";
	int result = strcmp_s(data1,data2);
	printf("%d\n", result);
	printf("\n-------------------------------------------------\n");


	char* res = FindeUserName(userName, (char*)"WOW");

	// ������
	if (res != 0) {
		printf("��ɫ���ֵ�ַ: %p\n", (void*)res);
	}
	else {
		printf("δ�ҵ���ɫ����\n");
	}


	/*pointerString();*/

	/*MoFangCE();*/


	int strlen_length = strlen_s("ABCD");
	printf("%d", strlen_length);

	printf("\n-------------------------------------------------\n");

	char data3[] = "China";
	char data4[] = "Nice";
	
	printf("%s", strcat_s(data3, data4));

	printf("\n-------------------------------------------------\n");
	char data5[] = "ABCD";
	char data6[] = "EFAAA";
	
	printf("%s", strcpy_s(data5, data6));
	return 0;
}

