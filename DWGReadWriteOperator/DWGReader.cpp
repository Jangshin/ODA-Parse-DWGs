#include "DWGReader.h"
#include "json/json.h"

// 读取文件
bool DWGReader::ReadFile(const std::string& sFileName)
{
	m_pDb = svcs.readFile(sFileName.c_str());
	if (m_pDb.isNull())
	{
		return false;
	}
	
	return true;
}

// 数据转化
std::string DWGReader::OdString2String(OdString sVal)
{
	std::wstring wsStr = sVal.c_str();

	size_t convertedChars = 0;
	size_t sizeInBytes = ((wsStr.length() + 1) * 2);
	errno_t err = 0;
	char* ch = (char*)malloc(sizeInBytes);

	err = wcstombs_s(&convertedChars, ch, sizeInBytes, wsStr.c_str(), sizeInBytes);
	if (err != 0)
	{
		return "";
	}

	std::string sStr = ch;
	return sStr;
}

// 输出控制台
void DWGReader::OutPutMsg(const std::string& sMsg)
{
	std::cout << sMsg.c_str() << std::endl;
}


// 遍历所有实体
bool DWGReader::VisitEntity()
{
	if (m_pDb.isNull())
	{
		return false;
	}

	OdDbBlockTableRecordPtr pModelSpace = m_pDb->getModelSpaceId().safeOpenObject(OdDb::kForRead);
	if (!pModelSpace.isNull())
	{
		OdDbObjectIteratorPtr iterM = pModelSpace->newIterator();
		for (iterM->start(); !iterM->done(); iterM->step())
		{
			OdDbEntityPtr pEnt = iterM->entity(OdDb::kForRead);
			if (!pEnt.isNull())
			{
				if (pEnt->isKindOf(OdDbPolyline::desc()))
				{
					OdDbPolylinePtr ent = OdDbPolyline::cast(pEnt);

					std::string sObject = OdString2String(ent->objectId().getHandle().ascii());
					if (SaveEntity2File(ent, sObject, UserFiles::enEntityType::kPoly))
					{
						//std::cout << "Save Poly : " << sObject << "Successfully!" << std::endl;
					}
					else
					{
						//std::cout << "Save Poly : " << sObject << "Failed!" << std::endl;
					}
				}
			}
		}
	}

}
// 获取所有图层
bool DWGReader::GetAllLayer()
{
	if (m_pDb.isNull())
	{
		return false;
	}

	OdDbLayerTablePtr pLayers = m_pDb->getLayerTableId().safeOpenObject();
	int i = 0;
	for (OdDbSymbolTableIteratorPtr pIter = pLayers->newIterator(); !pIter->done(); pIter->step())
	{
		OdDbLayerTableRecordPtr layer = pIter->getRecord();
		if (!layer.isNull())
		{
			std::cout << layer->getName() << std::endl;
		}
	}

	return false;
}

// 实体线保存关键数据
bool DWGReader::Poly2dToFile(OdDb2dPolylinePtr line, const std::string& sFile)
{
	if (line.isNull())
	{
		return false;
	}

	if (!UserFiles::FileOperator::FileExist(sFile))
	{
		return false;
	}

	Json::Value root;

	// 点数据
	Json::Value jsPt;
	// 解析坐标点
	OdDbObjectIteratorPtr vertexIterator = line->vertexIterator();
	while (!vertexIterator->done()) {
		OdDb2dVertexPtr vertex = OdDb2dVertex::cast(vertexIterator->entity());
		OdGePoint3d point = vertex->position();
		Json::Value pt;
		pt.append(point.x);
		pt.append(point.y);
		pt.append(point.z);
		jsPt.append(pt);
		vertexIterator->step();
	}
	root["Position"] = jsPt;

	// 是否闭合
	root["Fitting"] = line->isClosed();

	// 线型比例
	root["Scale"] = line->linetypeScale();

	// 线宽
	root["Width"] = line->lineWeight();

	// 线颜色
	OdCmColor stColor = line->color();
	Json::Value jsColor;
	jsColor.append(stColor.red());
	jsColor.append(stColor.green());
	jsColor.append(stColor.blue());
	root["Color"] = jsColor;

	//线索引
	root["ColorIndex"] = line->colorIndex();

	// 图层信息
	OdString layer = line->layer();
	root["Layer"] = OdString2String(layer);

	Json::FastWriter writer;
	std::string strResult = writer.write(root);
	
	if (!UserFiles::FileOperator::SaveFile(sFile, strResult))
	{
		return false;
	}

	return true;
}

// 实体线保存关键数据
bool DWGReader::PolyToFile(OdDbPolylinePtr line, const std::string& sFile)
{
	if (line.isNull())
	{
		return false;
	}

	if (!UserFiles::FileOperator::FileExist(sFile))
	{
		return false;
	}

	Json::Value root;

	// 点数据
	Json::Value jsPt;
	// 解析坐标点
	for (int i= 0; i < line->numVerts(); i++)
	{
		OdGePoint2d curPt;
		line->getPointAt(i, curPt);
		Json::Value pt;
		pt.append(curPt.x);
		pt.append(curPt.y);
	    jsPt.append(pt);
	}
	root["Position"] = jsPt;

	// 是否闭合
	root["Fitting"] = line->isClosed();

	// 线型比例
	root["Scale"] = line->linetypeScale();

	// 线宽
	root["Width"] = line->lineWeight();

	// 线颜色
	OdCmColor stColor = line->color();
	Json::Value jsColor;
	jsColor.append(stColor.red());
	jsColor.append(stColor.green());
	jsColor.append(stColor.blue());
	root["Color"] = jsColor;

	//线索引
	root["ColorIndex"] = line->colorIndex();

	// 图层信息
	OdString layer = line->layer();
	root["Layer"] = OdString2String(layer);

	Json::FastWriter writer;
	std::string strResult = writer.write(root);

	if (!UserFiles::FileOperator::SaveFile(sFile, strResult))
	{
		return false;
	}

	return true;
}

bool DWGReader::SaveEntity2File(OdDbEntityPtr pEntity, const std::string& strGUID,UserFiles::enEntityType enType)
{
	if (strGUID.empty())
	{
		return false;
	}

	std::string strRoot = UserFiles::FileOperator::GetGenFilePath() + "..\\" + ROOTDIR + "\\";
	// 创建 目录
	if (!UserFiles::FileOperator::DirExist(strRoot))
	{
		if (!UserFiles::FileOperator::CreateDir(strRoot))
		{
			return false;
		}
	}

	switch (enType)
	{
	case UserFiles::enEntityType::kLayer:
	{
		strRoot += LAYERDIR;
		break;
	}
	case UserFiles::enEntityType::kPoly:
	{
		strRoot += LINEDIR;
		break;
	}
	}

	// 创建 目录
	if (!UserFiles::FileOperator::DirExist(strRoot))
	{
		if (!UserFiles::FileOperator::CreateDir(strRoot))
		{
			return false;
		}
	}

	// 创建文件
	strRoot += "\\";
	strRoot += strGUID + FILESUFFIX;
	if (!UserFiles::FileOperator::FileExist(strRoot))
	{
		if (!UserFiles::FileOperator::CreateUserFile(strRoot))
		{
			return false;
		}
	}

	std::cout << "File: " << strRoot << std::endl;
	if (enType == UserFiles::kPoly)
	{
		if (PolyToFile(OdDbPolyline::cast(pEntity), strRoot))
		{
			std::cerr << "Poly2dToFile :" << strRoot << " Successfully! " << std::endl;
		}
		else
		{
			std::cerr << "Poly2dToFile :" << strRoot << " Failed! " << std::endl;
		}
	}
	return true;
}