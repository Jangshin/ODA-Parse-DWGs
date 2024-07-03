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
// PdfPublishBookmark.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_BOOLMARK_INCLUDED_
#define _PDF_PUBLISH_BOOLMARK_INCLUDED_

#include "PdfPublishPage.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

  //DOM-IGNORE-BEGIN
  class OdBookmark;
  //DOM-IGNORE-END

  /** \details
    A data type that represents a smart pointer to an <link OdPdfPublish::Bookmarks, OdBookmark> object.
  */
  SMARTPTR(OdBookmark);

/** \details
  This class implements working with a bookmark encapsulated in a PDF document created with Publish SDK.
  A bookmark is a kind of link with descriptive text that makes it easy to navigate through a PDF document.
*/
class PDFPUBLISH_TOOLKIT OdBookmark : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdBookmark();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdBookmark);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys the bookmark object.
  */
  virtual ~OdBookmark();

  /** \details
    Sets the bookmark title.
    \param title [in] A <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains the new title text of the bookmark object.
  */
  void setTitle(const OdString& title);

  /** \details
    Sets the <link OdPdfPublish::OdPage, page> the bookmark object refers to.
    \param page [in] A smart pointer to the <link OdPdfPublish::OdPage, OdPage> object that the bookmark object refers to.
    \sa
    <link OdPdfPublish::OdPage, OdPage class>.
  */
  void setPage(OdPagePtr page);

  /** \details
    Sets the bookmark type. Bookmark types are declared in the <link OdPdfPublish::Bookmarks::BookmarkType, Bookmarks::BookmarkType enumeration>.
    \param type [in] A new <<link OdPdfPublish::Bookmarks::BookmarkType, bookmark type> value.

    \sa
    <link OdPdfPublish::Bookmarks::BookmarkType, Bookmarks::BookmarkType enumeration>
  */
  void setBookmarkType(const Bookmarks::BookmarkType type);

  /** \details
    Sets the <link OdPdfPublish::Text::FontStyle, font style> for the bookmark title.
    \param style [in] A new <link OdPdfPublish::Text::FontStyle, font style> to apply for the title.

    \sa
    <link OdPdfPublish::Text::FontStyle, Text::FontStyle enumeration>
  */
  void setTextStyle(const Text::FontStyle style);

  /** \details
    Sets the color for the bookmark title.
    \param color [in] A new text color value.
  */
  void setTextColor(const ODCOLORREF color);

  /** \details
    Appends a new child bookmark to the current bookmark.
    \param child [in] A smart pointer to the descendant <link OdPdfPublish::OdBookmark, OdBookmark> object.
  */
  void appendChild(const OdBookmarkPtr child);

  /** \details
    Sets descendant bookmarks for the current bookmark.
    \param children [in] An array of smart pointers to the descendant <link OdPdfPublish::OdBookmark, OdBookmark> objects.
    \remarks
    If the bookmark object has descendant bookmarks, they are replaced with new bookmarks.
  */
  void setChildren(const OdBookmarkPtrArray& children);

  /** \details
    Sets parameters for the bookmark object.
    \param params [in] A double array that contains parameter values.
    \remarks
    The number of parameters and their values depend on the type of the bookmark object:
    * <link OdPdfPublish::Bookmarks::BookmarkType::kXYZ, BookmarkType::kXYZ>: coordinates (left, top) and the zoom scale factor. 
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFit, BookmarkType::kFit>: parameters are not required.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitH, BookmarkType::kFitH>: top coordinate.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitV, BookmarkType::kFitV>: left coordinate.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitR, BookmarkType::kFitR>: left, bottom, right, and top coordinates.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitB, BookmarkType::kFitB>: parameters are not required.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitBH, BookmarkType::kFitBH>: top coordinate.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitBV, BookmarkType::kFitBV>: left coordinate.
    If not all parameter values required by the bookmark type are passed to the method, the bookmark can't be created.
    \sa
    <link OdPdfPublish::Bookmarks::BookmarkType, Bookmarks::BookmarkType enumeration>
  */
  void setParametrs(const OdArray<double>& params);

  /** \details
    Returns the bookmark title.
    The method fills a passed <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> object with the title text and returns this string to a calling subroutine.
    \param title [out] A placeholder for the bookmark title.
  */
  void getTitle(OdString& title) const;

  /** \details
    Returns the page the bookmark object refers to.
    The method fills a passed parameter with the smart pointer to an <link OdPdfPublish::OdPage, OdPage> object and returns it to a calling subroutine.
    \param page [out] A placeholder for the <link OdPdfPublish::OdPage, page> the bookmark refers to.
    \sa
    <link OdPdfPublish::OdPage, OdPage class>.
  */
  void getPage(OdPagePtr& page) const;

  /** \details
    Returns the type of the bookmark object.
    The method fills a passed <link OdPdfPublish::Bookmarks::BookmarkType, Bookmarks::BookmarkType enumeration> value with the current bookmark type value and returns it to a calling subroutine.
    \param type [out] A placeholder for the <link OdPdfPublish::Bookmarks::BookmarkType, bookmark type> value.

    \sa
    <link OdPdfPublish::Bookmarks::BookmarkType, Bookmarks::BookmarkType enumeration>
  */
  void getBookmarkType(Bookmarks::BookmarkType& type) const;

  /** \details
    Returns the <link OdPdfPublish::Text::FontStyle, font style> of the bookmark title.
    The method fills a passed <link OdPdfPublish::Text::FontStyle, Text::FontStyle enumeration> value and returns it to a calling subroutine.
    \param style [out] A placeholder for the <link OdPdfPublish::Text::FontStyle, font style> of the bookmark title.

    \sa
    <link OdPdfPublish::Text::FontStyle, Text::FontStyle enumeration>
  */
  void getTextStyle(Text::FontStyle& style) const;

  /** \details
    Returns the current color of the bookmark title.
    The method fills a passed ODCOLORREF value with the current bookmark title color and returns it to a calling subroutine.

    \param color [out] A placeholder for the color of the bookmark title.
  */
  void getTextColor(ODCOLORREF& color) const;

  /** \details
    Returns the descendant bookmarks of the bookmark object.
    This method fills the passed array with the set of descendant <link OdPdfPublish::OdBookmark, OdBookmark> objects and returns it to a calling subroutine.
    \param children [out] A placeholder for the array of smart pointers to descendant <link OdPdfPublish::OdBookmark, OdBookmark> objects.
  */
  void getChildren(OdBookmarkPtrArray& children) const;

  /** \details
    Returns parameters of the current bookmark.
    This method fills the passed array of doubles with parameter values and returns it to a calling subroutine.
    \param params [out] A placeholder for the array of parameter values of the current bookmark object.
    \remarks
    The number of parameters and their values depend on the type of the bookmark object:
    * <link OdPdfPublish::Bookmarks::BookmarkType::kXYZ, BookmarkType::kXYZ>: coordinates (left, top) and the zoom scale factor. 
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFit, BookmarkType::kFit>: parameters are not required.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitH, BookmarkType::kFitH>: top coordinate.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitV, BookmarkType::kFitV>: left coordinate.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitR, BookmarkType::kFitR>: left, bottom, right, and top coordinates.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitB, BookmarkType::kFitB>: parameters are not required.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitBH, BookmarkType::kFitBH>: top coordinate.
    * <link OdPdfPublish::Bookmarks::BookmarkType::kFitBV, BookmarkType::kFitBV>: left coordinate.
    \sa
    <link OdPdfPublish::Bookmarks::BookmarkType, Bookmarks::BookmarkType enumeration>
  */
  void getParametrs(OdArray<double>& params) const;
};

}
#endif // _PDF_PUBLISH_BOOLMARK_INCLUDED_

