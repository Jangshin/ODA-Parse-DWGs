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
// PdfPublishWatermark.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_WATERMARK_INCLUDED_
#define _PDF_PUBLISH_WATERMARK_INCLUDED_

#include "PdfPublishText.h"
#include "PdfPublishImage.h"
#include "DoubleArray.h"

/** \details
  Namespace that contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements functionality for work with a watermark in a PDF document created with Publish SDK.
*/
class PDFPUBLISH_TOOLKIT OdWatermark : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdWatermark();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdWatermark);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys the watermark object.
  */
  virtual ~OdWatermark();

  /** \details
    Sets the watermark internal size in pixels.

    \param width  [in] A width value in pixels.
    \param height [in] A height value in pixels.
  */
  void setSize(const OdUInt32 width, const OdUInt32 height);

  /** \details
    Sets the opacity for the watermark object.
    \param value [in] A new opacity value.
    \remarks
    The opacity value should be in the range between 0 and 100. Default value is 50.
  */
  void setOpacity(const OdUInt8& value);

  /** \details
    Adds a <link OdPdfPublish::OdText, text> label to the watermark.

    \param text       [in] A smart pointer to a text label that should be added.
    \param location   [in] A <link OdPdfPublish::OdRect, rectangle> that specifies the location of an added text label within the watermark. It determines where the text is placed on the watermark.
    \param rotation   [in] A rotation angle value to be set.

    \remarks
    The location determines the bottom-left position of the bounding box of the text on the watermark.
    \sa
    <link OdPdfPublish::OdText, OdText class>.
  */
  void addText(const OdTextPtr& text, const OdRect& location, const double rotation = 0.);

  /** \details
    Adds an <link OdPdfPublish::OdImage, image> to the watermark.

    \param image      [in] A smart pointer to an image object that should be added.
    \param location   [in] A <link OdPdfPublish::OdRect, rectangle> that specifies the location of an added image within the watermark. It determines where the image is placed on the watermark.
    \param rotation   [in] A rotation angle value to be set.

    \sa
    <link OdPdfPublish::OdImage, OdImage class>.
  */
  void addImage(const OdImagePtr& image, const OdRect& location, const double rotation = 0.);

  /** \details
    Returns the current watermark internal size (width and height in pixels).
    The method fills the passed integer values representing width and height of the watermark and returns them to the calling subroutine.

    \param width  [out] A placeholder for the width value.
    \param height [out] A placeholder for the height value.
  */
  void getSize(OdUInt32& width, OdUInt32& height) const;

  /** \details
    Returns the icon opacity for the watermark object.
    The method fills a passed unsigned 8-bit integer value with the opacity value and returns it to a calling subroutine.
    \param value [in] A placeholder for the opacity value.
    \remarks
    The opacity value should be in the range between 0 and 100. Default value is 50.
  */
  void getOpacity(OdUInt8& value) const;

  /** \details
    Returns all <link OdPdfPublish::OdText, text labels> that the watermark contains and their locations.
    The method fills three passed arrays with text label objects, their locations and rotation angles, then returns these arrays to a calling subroutine.

    \param texts     [out] A placeholder for the watermark text labels array.
    \param locations [out] A placeholder for the text label locations array.
    \param rotations [out] A placeholder for the array of rotation angles for text labels.

    \sa
    <link OdPdfPublish::OdText, OdText class>.
  */
  void getTexts(OdTextPtrArray& texts, OdRectArray& locations, OdDoubleArray& rotations) const;

  /** \details
    Returns all <link OdPdfPublish::OdImage, images> that the watermark contains and their locations.
    The method fills three passed arrays with text label objects, their locations and rotation angles, then returns these arrays to a calling subroutine.

    \param images      [out] A placeholder for the watermark images array.
    \param locations   [out] A placeholder for the image locations array.
    \param rotations   [out] A placeholder for the array of rotation angles for images.

    \sa
    <link OdPdfPublish::OdImage, OdImage class>.
  */
  void getImages(OdImagePtrArray& images, OdRectArray& locations, OdDoubleArray& rotations) const;

};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdWatermark, OdWatermark> object.
*/
SMARTPTR(OdWatermark);

}
#endif // _PDF_PUBLISH_WATERMARK_INCLUDED_

