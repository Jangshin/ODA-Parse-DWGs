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

	// 目录是否存在
	bool FileOperator::DirExist(const std::string& strDir)
	{
		if (0 != _mkdir(strDir.c_str()))
		{
			return false;
		}
		return true;
	}
	// 创建目录
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
	// 文件是否存在
	bool FileOperator::FileExist(const std::string& strFile)
	{
		if (-1 != _access(strFile.c_str(), 0))
		{
			return true;
		}
		return false;
	}
	// 创建文件
	bool FileOperator::CreateUserFile(const std::string& strFile)
	{
		HANDLE hFile = CreateFileA(
			strFile.c_str(),                // 文件名
			GENERIC_WRITE,           // 写访问
			0,                       // 不共享
			NULL,                    // 默认安全属性
			CREATE_ALWAYS,           // 总是创建新文件
			FILE_ATTRIBUTE_NORMAL,   // 普通文件
			NULL                     // 没有模板文件
		);

		// 检查文件是否成功创建
		if (hFile == INVALID_HANDLE_VALUE) {
			std::cerr << "Could not create file (error code: " << GetLastError() << ")" << std::endl;
			return false;
		}

		// 关闭文件句柄
		CloseHandle(hFile);

		return true;
	}

	// 读取文件
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
	// 保存文件
	std::string FileOperator::ReadFile(const std::string& sFile)
	{
		static std::string strResult("");

		if (!FileExist(sFile))
		{
			return strResult;
		}

		std::ifstream inFile(sFile.c_str());

		// 检查文件是否成功打开
		if (!inFile.is_open()) {
			//std::cerr << "Unable to open file for reading!" << std::endl;
			return strResult;
		}

		// 读取文件内容
		std::string line;
		while (std::getline(inFile, line)) {
			strResult += line;
			//std::cout << line << std::endl;
		}

		// 关闭文件
		inFile.close();

		return strResult;

	}
}
