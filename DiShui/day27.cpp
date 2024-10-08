#include "day27.h"
#include "My_day23.h"

using namespace std;

bool PritfImport(LPCSTR filePath)
{
	if (!filePath)
	{
		return false;
	}

	LPVOID fileBuffer = nullptr;
	if (!ReadFile(filePath, &fileBuffer))
	{
		return false;
	}

	PEHeaders peheaders{};
	if (!GetPeheadersInfo(fileBuffer, peheaders))
	{
		return false;
	}
	if (peheaders.optionalHeader == nullptr)
	{
		return false;
	}

	PIMAGE_IMPORT_DESCRIPTOR importAddress = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD*)((BYTE*)fileBuffer + RvaToFoa(peheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, fileBuffer)));

	cout << "************************************INT****************************************" << endl;

	// OriginalFirstThunk----INT
	while (importAddress->OriginalFirstThunk != 0)
	{
		DWORD number = 0;
		cout << "************************************DLL Info****************************************************" << endl;
		char* dllName = (char*)((BYTE*)fileBuffer + RvaToFoa(importAddress->Name, fileBuffer));
		cout << "DLL Name: " << (char*)((BYTE*)fileBuffer + RvaToFoa(importAddress->Name, fileBuffer)) << endl;
		cout << hex << uppercase << "Original First Thunk: " << importAddress->OriginalFirstThunk << endl;
		cout << hex << uppercase << "Original First Thunk FOA: " << RvaToFoa(importAddress->OriginalFirstThunk, fileBuffer) << endl;
		cout << hex << uppercase << "TimeDateStamp: " << importAddress->TimeDateStamp << endl;
		cout << hex << uppercase << "Forwarder Chain: " << importAddress->ForwarderChain << endl;
		cout << hex << uppercase << "Name(RVA): " << importAddress->Name << endl;

		DWORD* FunctionAddress = (DWORD*)((BYTE*)fileBuffer + RvaToFoa(importAddress->OriginalFirstThunk, fileBuffer));
		while (*FunctionAddress != 0)
		{
			if ((*FunctionAddress & IMAGE_ORDINAL_FLAG))
			{
				cout << hex << "Thunk RVA: " << importAddress->OriginalFirstThunk << "  ";
				cout << hex << "Thunk FOA: " << RvaToFoa(importAddress->OriginalFirstThunk, fileBuffer) << "  ";
				cout << hex << "Thunk Value: " << uppercase << *FunctionAddress << "  ";
				DWORD ordinal = *FunctionAddress & ~IMAGE_ORDINAL_FLAG32;
				cout << "Ordinal: " << hex << uppercase << ordinal << "   ";
				cout << "API Name: " << "NULL" << endl;
			}
			else {
				PIMAGE_IMPORT_BY_NAME pIMPORT_BY_NAME = (PIMAGE_IMPORT_BY_NAME)(DWORD*)((BYTE*)fileBuffer + RvaToFoa(*FunctionAddress, fileBuffer));
				cout << hex << "Thunk RVA: " << importAddress->OriginalFirstThunk << "   ";
				cout << hex << "Thunk FOA: " << RvaToFoa(importAddress->OriginalFirstThunk, fileBuffer) << "   ";
				cout << hex << "Thunk Value: " << uppercase << *FunctionAddress << "   ";
				cout << hex << "Hint: " << uppercase << pIMPORT_BY_NAME->Hint << "   ";
				cout << "API Name: " << pIMPORT_BY_NAME->Name << endl;
			}
			FunctionAddress++;
			importAddress->OriginalFirstThunk += sizeof(DWORD);
			number++;
		}
		cout << "Number: " << dec << number << endl;
		importAddress++;
	}

	cout << "*********************************IAT****************************************" << endl;
	// FirstThunk-----IAT
	importAddress = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD*)((BYTE*)fileBuffer + RvaToFoa(peheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, fileBuffer)));
	while (importAddress->FirstThunk != 0)
	{
		cout << "*********************************DLL Info****************************************************" << endl;
		cout << "DLL Name: " << (char*)((BYTE*)fileBuffer + RvaToFoa(importAddress->Name, fileBuffer)) << endl;
		cout << hex << uppercase << "First Thunk: " << importAddress->FirstThunk << endl;
		cout << hex << uppercase << "First Thunk FOA: " << RvaToFoa(importAddress->FirstThunk, fileBuffer) << endl;
		cout << hex << uppercase << "TimeDateStamp: " << importAddress->TimeDateStamp << endl;
		cout << hex << uppercase << "Forwarder Chain: " << importAddress->ForwarderChain << endl;
		cout << hex << uppercase << "Name(RVA): " << importAddress->Name << endl;

		DWORD* FunctionAddress = (DWORD*)((BYTE*)fileBuffer + RvaToFoa(importAddress->FirstThunk, fileBuffer));
		while (*FunctionAddress != 0)
		{
			if (*FunctionAddress & IMAGE_ORDINAL_FLAG32)
			{
				cout << hex << "Thunk RVA: " << importAddress->FirstThunk << "   ";
				cout << hex << "Thunk FOA: " << RvaToFoa(importAddress->FirstThunk, fileBuffer) << "   ";
				cout << hex << "Thunk Value: " << uppercase << *FunctionAddress << "   ";
				DWORD ordinal = *FunctionAddress & ~IMAGE_ORDINAL_FLAG32;
				cout << "Ordinal: " << hex << uppercase << ordinal << "    ";
				cout << "API Name: " << "NULL" << endl;
			}
			else {
				PIMAGE_IMPORT_BY_NAME pIMPORT_BY_NAME = (PIMAGE_IMPORT_BY_NAME)(DWORD*)((BYTE*)fileBuffer + RvaToFoa(*FunctionAddress, fileBuffer));
				cout << hex << "Thunk RVA: " << importAddress->FirstThunk << "   ";
				cout << hex << "Thunk FOA: " << RvaToFoa(importAddress->FirstThunk, fileBuffer) << "   ";
				cout << hex << "Thunk Value: " << uppercase << *FunctionAddress << "   ";
				cout << hex << "Hint: " << uppercase << pIMPORT_BY_NAME->Hint << "   ";
				cout << "API Name: " << pIMPORT_BY_NAME->Name << endl;
			}
			FunctionAddress++;
			importAddress->FirstThunk += sizeof(DWORD);
		}
		importAddress++;
	}
	
	return false;
}

bool PrintfImportdescriptor(LPCSTR filePath)
{
	if (!filePath)
	{
		return false;
	}

	LPVOID fileBuffer = nullptr;
	if (!ReadFile(filePath, &fileBuffer))
	{
		return false;
	}

	PEHeaders peheaders{};
	if (!GetPeheadersInfo(fileBuffer, peheaders))
	{
		return false;
	}
	if (peheaders.optionalHeader == nullptr)
	{
		return false;
	}

	//PIMAGE_IMPORT_DESCRIPTOR importAddress = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD*)((BYTE*)fileBuffer + RvaToFoa(peheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, fileBuffer)));
	PIMAGE_IMPORT_DESCRIPTOR importAddress = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD*)((BYTE*)fileBuffer + RvaToFoa(*(DWORD*)peheaders.importSection, fileBuffer)));

	// 处理绑定导入表
	if (peheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress == 0)
	{
		cout << "VirtualAddress值异常,该程序没有绑定导入表" << endl;
		return false;
	}

	// 当目标文件存在绑定导入表时
	PIMAGE_BOUND_IMPORT_DESCRIPTOR descriptorAddress = (PIMAGE_BOUND_IMPORT_DESCRIPTOR)((DWORD*)((BYTE*)fileBuffer + RvaToFoa(peheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress, fileBuffer)));
	bool isdescriprot = 0;
	while (importAddress->OriginalFirstThunk != 0 && importAddress->FirstThunk != 0)
	{
		char* dllName = (char*)((BYTE*)fileBuffer + RvaToFoa(importAddress->Name, fileBuffer));
		DWORD timeDate = importAddress->TimeDateStamp;
		if (timeDate == 0)
		{
			isdescriprot = 1;
		}
		importAddress->OriginalFirstThunk += sizeof(DWORD);
		importAddress->FirstThunk += sizeof(DWORD);
		importAddress++;
	}	
	if (isdescriprot)
	{
		cout << "该程序没有绑定导入表" << endl;
	}
	else
	{
		DWORD NameBase = (DWORD)descriptorAddress;
		while (peheaders.descriptorSection->OffsetModuleName != 0)
		{
			cout << (char*)(NameBase + peheaders.descriptorSection->OffsetModuleName) << endl;
			cout << peheaders.descriptorSection->TimeDateStamp << endl;
			cout << hex << uppercase << peheaders.descriptorSection->NumberOfModuleForwarderRefs << endl;
			DWORD temp = peheaders.descriptorSection->NumberOfModuleForwarderRefs;
			// 遍历每个引用
			for (DWORD i = 0; i < temp; ++i)
			{
				cout << "**********************REF****************************" << endl;
				PIMAGE_BOUND_FORWARDER_REF refAddress = (PIMAGE_BOUND_FORWARDER_REF)(
					(BYTE*)descriptorAddress + sizeof(IMAGE_BOUND_IMPORT_DESCRIPTOR) + i * sizeof(IMAGE_BOUND_FORWARDER_REF));

				const char* refModuleName = (char*)(NameBase + refAddress->OffsetModuleName);
				cout << "Referenced DLL: " << refModuleName << endl;
				cout << "Forwarder TimeDateStamp: " << refAddress->TimeDateStamp << endl;
			}
			// 获取下一个模块
			descriptorAddress += sizeof(IMAGE_BOUND_IMPORT_DESCRIPTOR) + temp * sizeof(IMAGE_BOUND_FORWARDER_REF);
		}
	}
	return false;
}
