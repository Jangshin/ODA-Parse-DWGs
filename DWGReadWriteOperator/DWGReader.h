#pragma once

#include "odaInclude.h"
#include "ODAInit.h"
#include "FileOperator.h"
#include <iostream>

class DWGReader
{

public:
	DWGReader()
    {
		m_pDb = NULL;
		// ODA ��ʼ��
		odInitialize(&svcs);
		svcs.disableOutput(true);
	}

	~DWGReader()
	{
		// ж�ط���
		odUninitialize();
	}

	// ��ȡ�ļ�
	bool ReadFile(const std::string& sFileName);

	// ��ȡ����ͼ��
	bool GetAllLayer();

	// ��������ʵ��
	bool VisitEntity();

	/*
	* Commond: ����ʵ�壬���ұ��浽JSON������ߣ���Ҫ���ݽ��
	*/
	bool SaveEntity2File(OdDbEntityPtr pEntity, const std::string& strGUID, UserFiles::enEntityType enType);

private:

	// ��άʵ���߱���ؼ�����
	bool Poly2dToFile(OdDb2dPolylinePtr line, const std::string& sFile);

	// ʵ���߱���ؼ�����
	bool PolyToFile(OdDbPolylinePtr line, const std::string& sFile);

	// ����ת��
	std::string OdString2String(OdString sVal);
    
	// �������̨
	void OutPutMsg(const std::string& sMsg);
private:
	// �����ļ�·��
	std::string m_strRootDir;	
	// �������ݿ�
	OdDbDatabasePtr m_pDb;
	// ��������ע��ͳ�ʼ����
	OdStaticRxObject<MyServices> svcs;

};

