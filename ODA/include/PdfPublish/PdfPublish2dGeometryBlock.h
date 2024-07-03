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
// PdfPublish2dGeometryBlock.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_2DGEOM_BLOCK_INCLUDED_
#define _PDF_PUBLISH_2DGEOM_BLOCK_INCLUDED_

#include "PdfPublishCommon.h"
#include "PdfPublishBaseObject.h"
#include "PdfPublishImage.h"
#include "PdfPublishText.h"
#include "PdfPublish2dGeometryLayer.h"
#include "PdfPublishTilingPattern.h"

#include "Ge/GeEllipArc2d.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

  //DOM-IGNORE-BEGIN
  class OdTilingPattern;
  /** \details
    A data type that represents a smart pointer to an <link OdPdfPublish::OdTilingPattern, OdTilingPattern> object.
  */
  SMARTPTR(OdTilingPattern);
  class Od2dGeometryReference;
  /** \details
    A data type that represents a smart pointer to an <link OdPdfPublish::Od2dGeometryReference, Od2dGeometryReference> object.
  */
  SMARTPTR(Od2dGeometryReference);
  //DOM-IGNORE-END

/** \details
  This class implements two-dimensional geometry data (a geometry block) in PDF documents created with Publish SDK.
*/
class PDFPUBLISH_TOOLKIT Od2dGeometryBlock : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  Od2dGeometryBlock();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(Od2dGeometryBlock);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys the 2D geometry block object.
  */
  virtual ~Od2dGeometryBlock();

  /** \details
    Sets a new origin point for the geometry block object.
    \param origin [in] An OdGePoint class instance that represents the new origin point.
  */
  void setOrigin(const OdGePoint2d& origin);

  /** \details
    Adds a new line to the geometry block object.
    \param points [in] An array of OdGePoint objects that determine the line.
  */
  void addLine(const OdGePoint2dArray& points);

  /** \details
    Adds a new line to the geometry block object.
    \param start  [in] A starting point of the line.
    \param end    [in] An ending point of the line.

    \remarks
    Any line can be defined with its two points (passed through start and end parameters).
  */
  void addLine(const OdGePoint2d& start, const OdGePoint2d& end);

  /** \details
    Adds a new line to the geometry block object.
    \param nPoints [in] A quantity of points in the array.
    \param pPoints [in] A pointer to the point array.
  */
  void addLine(OdUInt32 nPoints, const OdGePoint2d* pPoints);

  /** \details
    Adds a new circle or arc to the geometry block object.
    \param circle [in] A circle that should be added.
  */
  void addCircle(const OdGeCircArc2d& circle);

  /** \details
    Adds a new ellipse to the geometry block object.
    \param ellipse [in] An ellipse that should be added.
  */
  void addEllipse(const OdGeEllipArc2d& ellipse);

  /** \details
    Adds a new NURBS curve to the geometry block object.
    \param nurb [in] A NURBS curve that should be added.
  */
  void addCurve(const OdGeNurbCurve2d& nurb);

  /** \details
    Sets the geometry block object's color.
    \param color [in] A new color value to be set.
  */
  void putColor(ODCOLORREF color);

  /** \details
    Sets the geometry block object's tiling pattern.
    \param pattern [in] A new tiling pattern value to be set.
  */
  void putTilingPattern(OdTilingPatternPtr& pattern);

  /** \details
    Sets the geometry block object's lineweight.
    \param lw [in] A new lineweight value to be set.
  */
  void putLineWeight(double lw);

  /** \details
    Sets the geometry block object's line cap.
    \param lineCap [in] A new line cap value to be set.
  */
  void putLineCap(Geometry::PDFLineCap lineCap);

  /** \details
    Sets the geometry block object's line join value.
    \param lineJoin [in] A new join value to be set.
  */
  void putLineJoin(Geometry::PDFLineJoin lineJoin);

  /** \details
    Sets a new transformation matrix for the geometry block object.
    \param transform [in] A new matrix object represented with an OdGeMatrix2d object.
  */
  void putTransform(const OdGeMatrix2d& transform);
  
  /** \details
    Starts a new drawing contour for the geometry block object.
  */
  void startContour();


  /** \details
    Finishes a new drawing contour for the geometry block object.
    \param rule [in] A finish rule for the contour.
  */
  void finishContour(Geometry::PDFFinishRule rule);

  /** \details
    Adds a new text label to the geometry block object.
    \param text     [in] An instance of a text label.
    \param location [in] A rectangle that specifies the text label location.
  */
  void addText(const OdTextPtr& text, const OdRect& location);

  /** \details
    Adds a new image to the geometry block object.
    \param image    [in] An image that should be added.
    \param location [in] A rectangle that specifies the image location.
  */
  void addImage(const OdImagePtr& image, const OdRect& location);

  /** \details
    Adds a new geometry reference to the geometry block object.
    \param reference [in] An geometry reference that should be added.
    \param location  [in] A rectangle that specifies the image location.
  */
  void addGeometryReference(const Od2dGeometryReferencePtr& reference, const OdRect& location);

  /** \details
    Starts use of a specified PDF layer within the geometry block object.
    \param layer [out] A smart pointer to the layer object that is created by the method.
    \remarks 
    The method accepts a smart pointer object that refers to the layer object to be created. 
  */
  void startLayer(Od2dGeometryLayerPtr& layer);

  /** \details
    Finishes use of the PDF layer previously started with a startLayer() method call for the geometry block object.
  */
  void finishLayer();
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::Od2dGeometryBlock, Od2dGeometryBlock> object.
*/
SMARTPTR(Od2dGeometryBlock);

}
#endif // _PDF_PUBLISH_2DGEOM_BLOCK_INCLUDED_

