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
		// ODA 初始化
		odInitialize(&svcs);
		svcs.disableOutput(true);
	}

	~DWGReader()
	{
		// 卸载服务
		odUninitialize();
	}

	// 读取文件
	bool ReadFile(const std::string& sFileName);

	// 获取所有图层
	bool GetAllLayer();

	// 遍历所有实体
	bool VisitEntity();

	/*
	* Commond: 解析实体，并且保存到JSON数据里边：主要数据结果
	*/
	bool SaveEntity2File(OdDbEntityPtr pEntity, const std::string& strGUID, UserFiles::enEntityType enType);

private:

	// 二维实体线保存关键数据
	bool Poly2dToFile(OdDb2dPolylinePtr line, const std::string& sFile);

	// 实体线保存关键数据
	bool PolyToFile(OdDbPolylinePtr line, const std::string& sFile);

	// 数据转化
	std::string OdString2String(OdString sVal);
    
	// 输出控制台
	void OutPutMsg(const std::string& sMsg);
private:
	// 保存文件路径
	std::string m_strRootDir;	
	// 操作数据库
	OdDbDatabasePtr m_pDb;
	// 服务：用来注册和初始化过
	OdStaticRxObject<MyServices> svcs;

};

