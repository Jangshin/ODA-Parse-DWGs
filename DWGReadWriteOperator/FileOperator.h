#pragma once

#include <iostream>

namespace UserFiles
{

// 保存的文件后缀
#define FILESUFFIX ".json"
// 根目录名称
#define ROOTDIR "DWG2JSON"
// 线子文件夹
#define LINEDIR "Lines"
// t图层子文件夹
#define LAYERDIR "Layers"
	

	// 图层信息

	// 文本信息

	// 二维线信息

	// 圆弧

	// 字体样式

	// 线型

	// 实体类型
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
		// 获取根目录
		static std::string GetGenFilePath();
		// 目录是否存在
		static bool DirExist(const std::string& strDir);
		// 创建目录
		static bool CreateDir(const std::string& strDir);
		// 文件是否存在
		static bool FileExist(const std::string& strFile);
		// 创建文件
		static bool CreateUserFile(const std::string& strFile);

		// 读取文件
		static bool SaveFile(const std::string& sFile, const std::string& sInfo);
		// 保存为念
		static std::string ReadFile(const std::string& sFile);
	};

}


