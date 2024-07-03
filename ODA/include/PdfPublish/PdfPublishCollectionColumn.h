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
// PdfPublishCollectionColumn.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_COLLECTION_COLUMN_INCLUDED_
#define _PDF_PUBLISH_COLLECTION_COLUMN_INCLUDED_

#include "PdfPublishBaseObject.h"
#include "PdfPublishAttachedFile.h"
#include "PdfPublishCollectionFolder.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
   This class implements an collection column entity in .pdf documents created with Publish SDK.
*/
class PDFPUBLISH_TOOLKIT OdCollectionColumn : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdCollectionColumn();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdCollectionColumn);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys an collection column object.
  */
  virtual ~OdCollectionColumn();

  /** \details
    Sets the name of the collection column.
    Use IsValid() to check the status of the operation.

    \param name [in] A new name value.
    The name shouldn't contain any special characters or spaces. To display the collection items, the collection should contain a column with the same name.
  */
  void setName(const OdString& name);

  /** \details
    Sets the caption of the collection column.

    \param caption [in] A new name value.
  */
  void setCaption(const OdString& caption);

  /** \details
    Sets the type for the collection column. The  type is represented with one of <link OdPdfPublish::CollectionSchema::ColumnType,  column types>.

    \param type [in] A new column type value.

    \sa
    <link OdPdfPublish::CollectionSchema::ColumnType, CollectionSchema::ColumnType enumeration>.
  */
  void setColumnType(const CollectionSchema::ColumnType& type);

  /** \details
    Sets the visibility on start flag of the collection column.

    \param val [in] A visibility flag value.
  */
  void setVisibleOnStart(const bool val);

  /** \details
    Sets the editability flag of the collection column.

    \param val [in] A editability flag value.
  */
  void setEnableEdit(const bool val);

  /** \details
    Sets the sort type for the collection column. The  type is represented with one of <link OdPdfPublish::CollectionSchema::SortOrder,  column sort types>.

    \param type [in] A new column sort type value.

    \sa
    <link OdPdfPublish::CollectionSchema::SortOrder, CollectionSchema::SortOrder enumeration>.
  */
  void setSortOrder(const CollectionSchema::SortOrder& sort);

  /** \details
    Returns the current name of the collection column.
    The method fills a passed string object and returns it to the calling subroutine.

    \param name [out] A placeholder for name value.
  */
  void getName(OdString& name) const;

  /** \details
    Returns the current caption of the collection column.
    The method fills a passed string object and returns it to the calling subroutine.

    \param caption [out] A placeholder for caption value.
  */
  void getCaption(OdString& caption) const;

  /** \details
    Returns the collection column type.
    The method fills a passed collection column type value and returns it to a calling subroutine.

    \param type [out] A placeholder for the collection column type value.

    \sa
    <link OdPdfPublish::CollectionSchema::ColumnType, CollectionSchema::ColumnType enumeration>.
  */
  void getColumnType(CollectionSchema::ColumnType& type) const;

  /** \details
    Sets the visibility flag of the collection column.

    \param val [in] A visibility flag value.
  */
  void getVisibleOnStart(bool& val) const;

  /** \details
    Sets the editability flag of the collection column.

    \param val [in] A editability flag value.
  */
  void getEnableEdit(bool& val) const;

  /** \details
    Returns the sort type for the collection column type.
    The method fills a passed sort type value and returns it to a calling subroutine.

    \param sort [out] A placeholder for the sort type value.

    \sa
    <link OdPdfPublish::CollectionSchema::SortOrder, CollectionSchema::SortOrder enumeration>.
  */
  void getSortOrder(CollectionSchema::SortOrder& sort) const;

};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdCollectionColumn, OdCollectionColumn> object.
*/
SMARTPTR(OdCollectionColumn);

}
#endif // _PDF_PUBLISH_COLLECTION_COLUMN_INCLUDED_

