/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2024, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2024 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef OD_COLOR_BOOK_H_
#define OD_COLOR_BOOK_H_

#include "OdaCommon.h"
#include "OdArray.h"
#include "CmColorBase.h"
#include "SharedPtr.h"
#define STL_USING_MAP
#include "OdaSTL.h"

/** \details
    Contains information about a color from color book.
  */
struct ColorRGB8
{
  /** Object color value. */
  OdCmEntityColor m_cmColor;

  /** The color name. */
  OdString m_name;
};

/** \details
    Contains information about a page from color book.
  */
struct OdColorPageRGB8
{
  /** Object color value. */
  OdCmEntityColor m_pageColor;

  /** An array of colors that contain the page. */
  OdArray<ColorRGB8> m_colors;
};

/** \details
    Contains information about a color book.
  */
struct OdColorBookRGB8
{
  /** Color book name. */
  OdString m_bookName;

  /** An array of pages that contain the color book. */
  OdArray<OdColorPageRGB8> m_pages;
};

//DOM-IGNORE-BEGIN
typedef std::map<OdString, OdSharedPtr<OdColorBookRGB8> > BooksMap;
typedef BooksMap::const_iterator ConstBookIterator;
//DOM-IGNORE-END


#endif
