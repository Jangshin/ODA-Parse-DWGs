#include "FileOperator.h"
#include <Windows.h>
#include <io.h>
#include <direct.h>
#include <sstream>
#include <fstream>

namespace UserFiles
{
	std::string FileOperator::GetGenFilePath()
	{
		char szFileName[MAX_PATH] = { '\0' };
		::GetModuleFileNameA(NULL, szFileName, MAX_PATH);

		std::string  strPath = szFileName;
		size_t n = strPath.find_last_of('\\');
		strPath = strPath.substr(0, n + 1);

		return strPath;
	}

	// Ŀ¼�Ƿ����
	bool FileOperator::DirExist(const std::string& strDir)
	{
		if (0 != _mkdir(strDir.c_str()))
		{
			return false;
		}
		return true;
	}
	// ����Ŀ¼
	bool FileOperator::CreateDir(const std::string& strDir)
	{
		DWORD dw = GetFileAttributesA(strDir.c_str());
		if (INVALID_FILE_ATTRIBUTES == dw)
		{
			return false;
		}

		if (dw & FILE_ATTRIBUTE_DIRECTORY)
		{
			return true;
		}

		return false;
	}
	// �ļ��Ƿ����
	bool FileOperator::FileExist(const std::string& strFile)
	{
		if (-1 != _access(strFile.c_str(), 0))
		{
			return true;
		}
		return false;
	}
	// �����ļ�
	bool FileOperator::CreateUserFile(const std::string& strFile)
	{
		HANDLE hFile = CreateFileA(
			strFile.c_str(),                // �ļ���
			GENERIC_WRITE,           // д����
			0,                       // ������
			NULL,                    // Ĭ�ϰ�ȫ����
			CREATE_ALWAYS,           // ���Ǵ������ļ�
			FILE_ATTRIBUTE_NORMAL,   // ��ͨ�ļ�
			NULL                     // û��ģ���ļ�
		);

		// ����ļ��Ƿ�ɹ�����
		if (hFile == INVALID_HANDLE_VALUE) {
			std::cerr << "Could not create file (error code: " << GetLastError() << ")" << std::endl;
			return false;
		}

		// �ر��ļ����
		CloseHandle(hFile);

		return true;
	}

	// ��ȡ�ļ�
	bool FileOperator::SaveFile(const std::string& sFile, const std::string& sInfo)
	{
		if (!FileExist(sFile))
		{
			return false;
		}

		std::ofstream out;
		out.open(sFile.c_str());
		if (out.is_open())
		{
			out << sInfo;
		}
		else
		{
			return false;
		}
		out.close();

		return true;

	}
	// �����ļ�
	std::string FileOperator::ReadFile(const std::string& sFile)
	{
		static std::string strResult("");

		if (!FileExist(sFile))
		{
			return strResult;
		}

		std::ifstream inFile(sFile.c_str());

		// ����ļ��Ƿ�ɹ���
		if (!inFile.is_open()) {
			//std::cerr << "Unable to open file for reading!" << std::endl;
			return strResult;
		}

		// ��ȡ�ļ�����
		std::string line;
		while (std::getline(inFile, line)) {
			strResult += line;
			//std::cout << line << std::endl;
		}

		// �ر��ļ�
		inFile.close();

		return strResult;

	}
}
