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
// PdfPublishTilingPattern.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_TILING_PATTERN_INCLUDED_
#define _PDF_PUBLISH_TILING_PATTERN_INCLUDED_

#include "PdfPublishBaseObject.h"


/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

  //DOM-IGNORE-BEGIN
  class Od2dGeometryBlock;
/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::Od2dGeometryBlock, Od2dGeometryBlock> object.
*/
  SMARTPTR(Od2dGeometryBlock);
  //DOM-IGNORE-END

  /** \details
     This class implements an tiling pattern entity in .pdf documents created with Publish SDK.
  */
  class PDFPUBLISH_TOOLKIT OdTilingPattern : public OdObject
  {
    //DOM-IGNORE-BEGIN
  protected:
    OdTilingPattern();
    //DOM-IGNORE-END
  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdTilingPattern);
    ODRX_HEAP_OPERATORS();
    //DOM-IGNORE-END

    /** \details
      Destroys an tiling pattern object.
    */
    virtual ~OdTilingPattern();

    /** \details
      Sets a geometry block object as the source for the tiling pattern.

      \param pRasterImage [in] A smart pointer to a geometry block object.
    */
    void setGeometryBlock(const Od2dGeometryBlockPtr& block);

    /** \details
      Sets the tiling pattern size in pixels.

      \param width  [in] A width value in pixels.
      \param height [in] A height value in pixels.
    */
    void setSize(const OdInt32 width, const OdInt32 height);

    /** \details
      Sets the tiling pattern X step in pixels.

      \param x_step  [in] A X step value in pixels.
    */
    void setXStep(const OdInt32 x_step);

    /** \details
      Sets the tiling pattern Y step in pixels.

      \param y_step  [in] A Y step value in pixels.
    */
    void setYStep(const OdInt32 y_step);

    /** \details
      Returns the current geometry block object.
      The method fills a passed geometry block object and returns it to the calling subroutine.

      \param block [out] A placeholder for the geometry block object.
    */
    void getGeometryBlock(Od2dGeometryBlockPtr& block) const;

    /** \details
      Returns the current tiling pattern size (width and height in pixels).
      The method fills the passed integer values representing width and height of the tiling pattern and returns them to the calling subroutine.

      \param width  [out] A placeholder for the width value.
      \param height [out] A placeholder for the height value.
    */
    void getSize(OdInt32& width, OdInt32& height) const;

    /** \details
      Returns the tiling pattern X step in pixels.
      The method fills the passed integer value representing X step of the tiling pattern and returns it to the calling subroutine.

      \param x_step  [out] A placeholder for the X step value.
    */
    void getXStep(OdInt32& x_step) const;

    /** \details
      Returns the tiling pattern Y step in pixels.
      The method fills the passed integer value representing Y step of the tiling pattern and returns it to the calling subroutine.

      \param y_step  [out] A placeholder for the Y step value.
    */
    void getYStep(OdInt32& y_step) const;
  };

  /** \details
    A data type that represents a smart pointer to an <link OdPdfPublish::OdTilingPattern, OdTilingPattern> object.
  */
  SMARTPTR(OdTilingPattern);

}
#endif // _PDF_PUBLISH_TILING_PATTERN_INCLUDED_

