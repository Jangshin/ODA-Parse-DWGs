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
// PdfPublishText.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_TEXT_INCLUDED_
#define _PDF_PUBLISH_TEXT_INCLUDED_

#include "PdfPublishBaseObject.h"
#include "PdfPublish2dGeometryLayer.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements a text label for .pdf documents created with Publish SDK.
  Text label options consist of two parts: text content and formatting parameters (font type, size, color).
*/
class PDFPUBLISH_TOOLKIT OdText : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdText();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdText);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys a text label.
  */
  virtual ~OdText();

  /** \details
    Sets the label text.
    
    \param text [in] New label text.
  */
  void setText(const OdString& text);

  /** \details
    Sets the text label font type from the list of <link OdPdfPublish::Text::StandardFontsType,  predefined fonts>. 
    
    \param fontType [in] A new <link OdPdfPublish::Text::StandardFontsType, font type> value.
    
    \sa 
    <link OdPdfPublish::Text::StandardFontsType, Text::StandardFontsType enumeration>.
  */
  void setFont(Text::StandardFontsType fontType);

  /** \details
    Sets font parameters for the text label. 
    
    \param fontName  [in] A new font name for the text label.
    \param fontStyle [in] A new <link OdPdfPublish::Text::FontStyle, font style>.
    \param language  [in] A new <link OdPdfPublish::Text::Language, font language> for the text label.
    \param embed     [in] A flag that determines whether the font is embedded.
    
    \remarks
    This method can set a font that is not in the list of 
    <link OdPdfPublish::Text::StandardFontsType, standard fonts>.
    By default the <link OdPdfPublish::Text::StandardFontsType::kTimesRoman, normal Times New Roman font> is used.
    
    \sa 
    <link OdPdfPublish::Text::FontStyle, Text::FontStyle enumeration>
    <link OdPdfPublish::Text::Language, Text::Language enumeration>.
  */
  void setFont(const OdString& fontName, Text::FontStyle fontStyle = Text::kRegular, Text::Language language = Text::kDefault, bool embed = false);

  /** \details
    Sets the text label font size.
    
    \param size [in] A new font size value.
  */
  void setSize(OdUInt16 size);
  
  /** \details
    Sets the text label foreground color.
    
    \param color [in] A new color value.
  */
  void setColor(ODCOLORREF color);

  /** \details
    Returns the text label content.
    The method fills a passed string object with label text and returns this string to a calling subroutine.
    
    \param text [out] A placeholder for the label text. 
  */
  void getText(OdString& text) const;

  /** \details
    Returns the text label font type.
    The method fills a passed font type value and returns this string to a calling subroutine.
    
    \param storageType  [out] A placeholder for the <link OdPdfPublish::Text::StorageType, storage type> value.
    \param fontType     [out] A placeholder for the <link OdPdfPublish::Text::StandardFontsType, font type> that should be used for text object.
    \param fontName     [out] A placeholder for the font name that should be used for text object.
    \param fontStyle    [out] A placeholder for the <link OdPdfPublish::Text::FontStyle, font style>.
    \param language     [out] A placeholder for the font <link OdPdfPublish::Text::Language, language> that should be used for text object.
    \param embed        [out] A placeholder for the font embedding flag.
    
    \sa
    <link OdPdfPublish::Text::StorageType, Text::StorageType enumeration>
    <link OdPdfPublish::Text::StandardFontsType, Text::StandardFontsType enumeration>
    <link OdPdfPublish::Text::FontStyle, Text::FontStyle enumeration>
    <link OdPdfPublish::Text::Language, Text::Language enumeration>
  */  
  void getFont(Text::StorageType& storageType, Text::StandardFontsType& fontType, OdString& fontName, Text::FontStyle& fontStyle, Text::Language& language, bool& embed) const;
  
  /** \details
    Returns the text label font size.
    The method fills a passed value and returns it to a calling subroutine.
    
    \param size [out] A placeholder for the font size value.
  */
  void getSize(OdUInt16& size) const;
  
  /** \details
    Returns the text label color.
    The method fills a passed ODCOLORREF value and returns it to a calling subroutine.
    
    \param color [out] A placeholder for the text label color value.
  */
  void getColor(ODCOLORREF& color) const;

  /** \details
  Sets a PDF layer object for the text object.
  \param layer [in] A smart pointer to a PDF layer object.
  \remarks
  If the smart pointer to a PDF layer object is null, it means that the text object doesn't belong to any layer.
  */
  void setLayer(const Od2dGeometryLayerPtr& layer);

  /** \details
    Returns the current PDF layer object for the text object.
    The method fills a passed value and returns it to a calling subroutine.
    \param layer [out] A placeholder for a smart pointer to PDF layer object.
    \remarks
    The method fills a passed value and returns it to a calling subroutine.
  */
  void getLayer(Od2dGeometryLayerPtr& layer) const;

};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdText, OdText> object.
*/
SMARTPTR(OdText);

}
#endif // _PDF_PUBLISH_TEXT_INCLUDED_

