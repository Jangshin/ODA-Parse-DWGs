#pragma once

#include <iostream>

namespace UserFiles
{

// ������ļ���׺
#define FILESUFFIX ".json"
// ��Ŀ¼����
#define ROOTDIR "DWG2JSON"
// �����ļ���
#define LINEDIR "Lines"
// tͼ�����ļ���
#define LAYERDIR "Layers"
	

	// ͼ����Ϣ

	// �ı���Ϣ

	// ��ά����Ϣ

	// Բ��

	// ������ʽ

	// ����

	// ʵ������
	enum enEntityType
	{
		kPoly = 0,
		kLayer,
		kText,
		kArc,
		kFontStyle,
		kLineType
	};

	class FileOperator
	{

	public:
		// ��ȡ��Ŀ¼
		static std::string GetGenFilePath();
		// Ŀ¼�Ƿ����
		static bool DirExist(const std::string& strDir);
		// ����Ŀ¼
		static bool CreateDir(const std::string& strDir);
		// �ļ��Ƿ����
		static bool FileExist(const std::string& strFile);
		// �����ļ�
		static bool CreateUserFile(const std::string& strFile);

		// ��ȡ�ļ�
		static bool SaveFile(const std::string& sFile, const std::string& sInfo);
		// ����Ϊ��
		static std::string ReadFile(const std::string& sFile);
	};

}


