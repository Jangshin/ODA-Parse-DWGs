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
// PdfPublish2dGeometryLayer.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_2DGEOM_LAYER_INCLUDED_
#define _PDF_PUBLISH_2DGEOM_LAYER_INCLUDED_

#include "PdfPublishCommon.h"
#include "PdfPublishBaseObject.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements the layer object for the two-dimensional geometry in .pdf documents created with Publish SDK.
  PDF layers can be used when adding objects to an <link OdPdfPublish::Od2dGeometryBlock, Od2dGeometryBlock> object 
  as well as to <link OdPdfPublish::Od2dGeometryReference, Od2dGeometryReference>, <link OdPdfPublish::OdImage, OdImage>, 
  and <link OdPdfPublish::OdText, OdText> objects, which can be added to the document page. 
*/
class PDFPUBLISH_TOOLKIT Od2dGeometryLayer : public OdObject
{
protected:
  //DOM-IGNORE-BEGIN
  Od2dGeometryLayer();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(Od2dGeometryLayer);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys the layer object.
  */
  virtual ~Od2dGeometryLayer();

  /** \details
    Sets the layer name.
    \param name [in] A string that contains the name to be set.
    \remarks
    The name is mandatory and must be unique among the document object names.
  */
  void setName(const OdString& name);

  /** \details
    Sets the visibility flag value for the layer object.
    This flag determines whether objects that belong to the layer are visible (equals true) or invisible (equals false) when the document is opened.
    \param state [in] Visibility flag value to be set.
  */
  void setVisible(const bool state);

  /** \details
    Sets the locked flag value for the layer object.
This flag determines whether visibility of the layer can be changed when the document is viewed. 
If the visibility can be changed, the flag equals true; otherwise, it equals false.
    \param state [out] Locked flag value to be set.
  */
  void setLocked(const bool state);

  /** \details
    Returns the layer name.
    The method fills a passed string object and returns it to a calling subroutine.
    \param name [out] A placeholder for the layer name.
    \remarks
    The method fills a passed string object and returns it to a calling subroutine.
  */
  void getName(OdString& name) const;

  /** \details
    Returns the current value of the visibility flag of the layer.
    The method fills a passed Boolean value and returns it to a calling subroutine.
    \param state [out] A placeholder for the visibility flag value.
    \remarks
    The method fills a passed boolean value and returns it to a calling subroutine.
  */
  void getVisible(bool& state) const;

  /** \details
    Returns the current value of the locked flag of the layer.
    The method fills a passed Boolean value and returns it to a calling subroutine.
    \param state [out] A placeholder for the locked flag value.
    \remarks
    The method fills a passed boolean value and returns it to a calling subroutine.
  */
  void getLocked(bool& state) const;
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::Od2dGeometryLayer, Od2dGeometryLayer> object.
*/
SMARTPTR(Od2dGeometryLayer);

}
#endif // _PDF_PUBLISH_2DGEOM_LAYER_INCLUDED_

