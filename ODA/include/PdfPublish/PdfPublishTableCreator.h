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


///////////////////////////////////////////////////////////////////////////////
//
// OdTableCreator.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_TABLE_CREATOR_INCLUDED_
#define _PDF_PUBLISH_TABLE_CREATOR_INCLUDED_

#include "PdfPublishCommon.h"
#include "PdfPublishTable.h"
#include "UInt32Array.h"
#include "DoubleArray.h"
#include "PdfPublishTilingPattern.h"
#define STL_USING_MAP
#include "OdaSTL.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

  class OdTableCreatorImpl;

/** \details
  This class implements the table creator interface for Publish SDK.
  The table creator is used for creating <link OdPdfPublish::OdTable, tables> with specified parameters.
  \sa 
  <link publish_working_with_tables, Work with Tables>
*/
class PDFPUBLISH_TOOLKIT OdTableCreator : public OdRxObject
{
  
  friend class OdTableCreatorImpl;
  OdTableCreatorImpl* m_pImpl;
protected:
  OdTableCreator();

public:

  ODRX_DECLARE_MEMBERS(OdTableCreator);
  ODRX_HEAP_OPERATORS();
  
  /** \details
    Determines whether the table creator object is empty.
    \returns The true value if the object is empty, otherwise returns false.
  */
  bool isEmpty() const;
  
  /** \details
    Clears the table creator object.
  */
  void clear();
  
  /** \details
    Determines whether the table creator object is valid.
    \returns The true value if the object is valid, otherwise returns false.
  */
  bool isValid() const;

  /** \details
    Destroys the table creator object.
  */
  virtual ~OdTableCreator();

  /** \details
    Sets the column count for the table to be created.
    \param column_count [in] A column count.
    
    \remarks
    By default, all table columns have the same width.
  */
  void setColumnCount(const OdUInt32 column_count);
  
  /** \details
    Sets the row count for the table to be created.
    \param row_count [in] A row count.
    
    \remarks
    By default, all table rows have the same height.
  */
  void setRowCount(const OdUInt32 row_count);

  /** \details
    Sets a new width for a particular table column.
    \param col          [in] A column index (from 0 to column count -1).
    \param column_width [in] A column width value.
  */
  void setParticularColumnWidth(const OdUInt32 col, const OdUInt32 column_width);

  /** \details
    Sets a new height for a particular table row.
    \param row        [in] A row index (from 0 to row count -1).
    \param row_height [in] A row height value.
  */
  void setParticularRowHeight(const OdUInt32 row, const OdUInt32 row_height);

  /** \details
    Sets a new color for a table cell.
    \param row          [in] A row index (from 0 to row count -1).
    \param column       [in] A column index (from 0 to column count -1).
    \param fill_color   [in] A new cell color.
  */
  void setCellFillColor(const OdUInt32 row, const OdUInt32 column, const ODCOLORREF fill_color);

  /** \details
    Sets a new border color for a table cell.
    \param row          [in] A row index (from 0 to row count -1).
    \param column       [in] A column index (from 0 to column count -1).
    \param border_color [in] A new cell border color.
  */
  void setCellBorderColor(const OdUInt32 row, const OdUInt32 column, const ODCOLORREF border_color);
  
  /** \details
    Sets a new border thickness for a table cell.
    \param row              [in] A row index (from 0 to row count -1).
    \param column           [in] A column index (from 0 to column count -1).
    \param border_thickness [in] A new cell border thickness.
  */
  void setCellBorderThickness(const OdUInt32 row, const OdUInt32 column, const Border::Thickness border_thickness);

  /** \details
    Sets a new background image for a table cell.
    \param row              [in] A row index (from 0 to row count -1).
    \param column           [in] A column index (from 0 to column count -1).
    \param background_image [in] A smart pointer to an <link OdPdfPublish::OdImage, OdImage> object that contains the new cell background image.
  */
  void setCellBackgroundImage(const OdUInt32 row, const OdUInt32 column, const OdImagePtr background_image);

  /** \details
    Sets a new tiling pattern for a table cell.
    \param row              [in] A row index (from 0 to row count -1).
    \param column           [in] A column index (from 0 to column count -1).
    \param tiling_pattern   [in] A smart pointer to an <link OdPdfPublish::OdTilingPattern, OdTilingPattern> object that contains the new cell tiling pattern.
  */
  void setCellTilingPattern(const OdUInt32 row, const OdUInt32 column, const OdTilingPatternPtr tiling_pattern);

  /** \details
    Returns the current column count for the table to be created.
    \param column_count [out] A placeholder for the column count.
    \remarks 
    The method accepts a passed value, fills it and returns it to a calling subroutine.
  */
  void getColumnCount(OdUInt32& column_count) const;
  
  /** \details
    Returns the current row count for the table to be created.
    \param row_count [out] A placeholder for the row count.
    \remarks 
    The method accepts a passed value, fills it and returns it to a calling subroutine.
  */
  void getRowCount(OdUInt32& row_count) const;
  
  /** \details
    Requests the current width for a particular table column.
    \param col          [in] A column index (from 0 to column count -1).
    \param column_width [out] A placeholder for the column width value.

    \returns The true value if the column width value is returned successfully; otherwise, the method returns false.

    \remarks 
    The method accepts a passed value, fills it and returns it to a calling subroutine.
  */
  bool getParticularColumnWidth(const OdUInt32 col, OdUInt32& column_width) const;
  
  /** \details
    Requests the current height for a particular table row.
    \param row        [in] A row index (from 0 to row count -1).
    \param row_height [out] A placeholder for the row height value.

    \returns The true value if the row height value is returned successfully; otherwise, the method returns false.
    
    \remarks 
    The method accepts a passed value, fills it and returns it to a calling subroutine.
  */
  bool getParticularRowHeight(const OdUInt32 row, OdUInt32& row_height) const;
  
  /** \details
    Returns the current color of a table cell.
    \param row          [in] A row index (from 0 to row count -1).
    \param column       [in] A column index (from 0 to column count -1).
    \param fill_color   [out] A placeholder for the cell color.
    \remarks 
    The method accepts a passed color value, fills it and returns it to a calling subroutine.
  */
  void getCellFillColor(const OdUInt32 row, const OdUInt32 column, ODCOLORREF& fill_color) const;
  
  /** \details
    Returns the current border color of a table cell.
    \param row          [in] A row index (from 0 to row count -1).
    \param column       [in] A column index (from 0 to column count -1).
    \param border_color [out] A placeholder for the cell border color.
    \remarks 
    The method accepts a passed color value, fills it and returns it to a calling subroutine.
  */
  void getCellBorderColor(const OdUInt32 row, const OdUInt32 column, ODCOLORREF& border_color) const;
  
  /** \details
    Returns the current border thickness for a table cell.
    \param row              [in] A row index (from 0 to row count -1).
    \param column           [in] A column index (from 0 to column count -1).
    \param border_thickness [out] A placeholder for the cell border thickness.
    \remarks 
    The method accepts a passed border thickness value, fills it and returns it to a calling subroutine.
  */
  void getCellBorderThickness(const OdUInt32 row, const OdUInt32 column, Border::Thickness& border_thickness) const;

  /** \details
    Returns the current background image for a table cell.
    \param row              [in] A row index (from 0 to row count -1).
    \param column           [in] A column index (from 0 to column count -1).
    \param background_image [out] A placeholder for the cell background image.
    \remarks 
    The method accepts a passed smart pointer, fills it with a reference to the <link OdPdfPublish::OdImage, OdImage> object that represents the cell background image, 
    and returns it to a calling subroutine.
  */
  void getCellBackgroundImage(const OdUInt32 row, const OdUInt32 column, OdImagePtr& background_image) const;

  /** \details
    Returns the current tiling pattern for a table cell.
    \param row              [in] A row index (from 0 to row count -1).
    \param column           [in] A column index (from 0 to column count -1).
    \param tiling_pattern [out] A placeholder for the cell tiling pattern.
    \remarks
    The method accepts a passed smart pointer, fills it with a reference to the <link OdPdfPublish::OdTilingPattern, OdTilingPattern> object that represents the cell tiling pattern,
    and returns it to a calling subroutine.
  */
  void getCellTilingPattern(const OdUInt32 row, const OdUInt32 column, OdTilingPatternPtr& tiling_pattern) const;

  /** \details
    Creates a new table according to options of the table creator.
    \returns A smart pointer to an <link OdPdfPublish::OdTable, OdTable> object. 
  */
  OdTablePtr createTable() const;

};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdTableCreator, OdTableCreator> object.
*/
SMARTPTR(OdTableCreator);

}
#endif // _PDF_PUBLISH_TABLE_CREATOR_INCLUDED_

