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
// PdfPublishCollection.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_COLLECTION_INCLUDED_
#define _PDF_PUBLISH_COLLECTION_INCLUDED_

#include "PdfPublishBaseObject.h"
#include "PdfPublishAttachedFile.h"
#include "PdfPublishCollectionFolder.h"
#include "PdfPublishCollectionColumn.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
   This class implements an collection entity in .pdf documents created with Publish SDK.
*/
class PDFPUBLISH_TOOLKIT OdCollection : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdCollection();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdCollection);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys an collection object.
  */
  virtual ~OdCollection();

  /** \details
    Adds the column object for the collection.

    \param column  [in] A smart pointer to a column object.
  */
  void addColumn(const OdCollectionColumnPtr& column);

  /** \details
    Sets the collection of column object for the collection.

    \param columns  [in] A array of smart pointers to a column object.
  */
  void setColumns(const OdCollectionColumnPtrArray& columns);

  /** \details
    Sets the attached file that is displayed when the collection is opened.

    \param file   [in] A smart pointer to a attached file object.
    \remarks
    The file should also be added to the root directory of the Collection.
  */
  void setInitialFile(const OdAttachedFilePtr& file);

  /** \details
    Returns the collection view type.
    The method fills a passed collection view type value and returns it to a calling subroutine.

    \param view_type [out] A placeholder for the collection view type value.

    \sa
    <link OdPdfPublish::CollectionSchema::InitialView, CollectionSchema::InitialView enumeration>.
  */
  void setInitalViewType(const CollectionSchema::InitialView view_type);

  /** \details
    Sets a new background color for the collection object.

    \param color [in] A new color value to be set.
  */
  void setBackgroundColor(const ODCOLORREF color);

  /** \details
    Sets a new card background color for the collection object.

    \param color [in] A new color value to be set.
  */
  void setCardBackgroundColor(const ODCOLORREF color);

  /** \details
    Sets a new card border color for the collection object.

    \param color [in] A new color value to be set.
  */
  void setCardBorderColor(const ODCOLORREF color);

  /** \details
    Sets a new primary text color for the collection object.

    \param color [in] A new color value to be set.
  */
  void setPrimaryTextColor(const ODCOLORREF color);

  /** \details
    Sets a new secondary text color for the collection object.

    \param color [in] A new color value to be set.
  */
  void setSecondaryTextColor(const ODCOLORREF color);

  /** \details
    Sets the root folder object for the collection object.

    \param folder   [in] A smart pointer to a attached folder object.
  */
  void setRootFolder(const OdAttachedFolderPtr& folder);

  /** \details
    Returns a collection of column of the collection object.
    This method fills the passed array of smart pointer to OdCollectionColumn, then returns them to a calling subroutine.

    \param columns  [out] A placeholder for collection of column object.
  */
  void getColumns(OdCollectionColumnPtrArray& columns) const;

  /** \details
    Returns a attached file that is displayed when the collection is opened.
    This method fills the passed smart pointer to OdAttachedFile, then returns them to a calling subroutine.

    \param file  [out] A placeholder for smart pointer to a attached file object.
  */
  void getInitialFile(OdAttachedFilePtr& file) const;

  /** \details
    Returns the collection view type.
    The method fills a passed collection view type value and returns it to a calling subroutine.

    \param view_type [out] A placeholder for the collection view type value.

    \sa
    <link OdPdfPublish::CollectionSchema::InitialView, CollectionSchema::InitialView enumeration>.
  */
  void getInitalViewType(CollectionSchema::InitialView view_type) const;

  /** \details
    Returns the background color for the collection object.
    The method fills a passed ODCOLORREF value and returns it to a calling subroutine.

    \param color [out] A placeholder for the color value.
  */
  void getBackgroundColor(ODCOLORREF& color) const;

  /** \details
    Returns the card background color for the collection object.
    The method fills a passed ODCOLORREF value and returns it to a calling subroutine.

    \param color [out] A placeholder for the color value.
  */
  void getCardBackgroundColor(ODCOLORREF& color) const;

  /** \details
    Returns the card border color for the collection object.
    The method fills a passed ODCOLORREF value and returns it to a calling subroutine.

    \param color [out] A placeholder for the color value.
  */
  void getCardBorderColor(ODCOLORREF& color) const;

  /** \details
    Returns the primary text color for the collection object.
    The method fills a passed ODCOLORREF value and returns it to a calling subroutine.

    \param color [out] A placeholder for the color value.
  */
  void getPrimaryTextColor(ODCOLORREF& color) const;

  /** \details
    Returns the secondary text color for the collection object.
    The method fills a passed ODCOLORREF value and returns it to a calling subroutine.

    \param color [out] A placeholder for the color value.
  */
  void getSecondaryTextColor(ODCOLORREF& color) const;

  /** \details
    Returns a root folder object for the collection object.
    This method fills the passed smart pointer to OdAttachedFolder, then returns them to a calling subroutine.

    \param folder  [out] A placeholder for smart pointer to attached folder.
  */
  void getRootFolder(OdAttachedFolderPtr& folder) const;
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdCollection, OdCollection> object.
*/
SMARTPTR(OdCollection);

}
#endif // _PDF_PUBLISH_COLLECTION_INCLUDED_

