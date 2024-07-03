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

#ifndef OD_VIEWREPSTANDARD_H
#define OD_VIEWREPSTANDARD_H

#include "DbObject.h"
#include "ModelDocObjExports.h"

#include "TD_PackPush.h"

/** \details

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 
*/
class MODELDOCOBJ_EXPORT OdDbViewRepStandard : public OdDbObject
{
public:
  enum DpiResolutionType {
    k50dpi  =  50,
    k100dpi = 100,
    k150dpi = 150,
    k200dpi = 200,
    k300dpi = 300
  };
  enum ProjectionType {
    kFirstAngle,
    kThirdAngle
  };
  enum SectionThreadEndDisplayType {
    kOpenedThreadEnd,
    kClosedThreadEnd
  };
  enum CircularThreadEdgeDisplayType {
    kOpenedCircularThreadEdge,
    kClosedCircularThreadEdge
  };
  enum PreviewDisplayType {
    kBoundingBox,
    kShadedPreview
  };
  enum SynergyVersion {
    kVersion0 = 0,
    kVersion1 = 1
  };

  ODDB_DECLARE_MEMBERS(OdDbViewRepStandard);

  OdDbViewRepStandard();
  virtual ~OdDbViewRepStandard();

  void initialize(ProjectionType proj,
    SectionThreadEndDisplayType secThread,
    CircularThreadEdgeDisplayType circThread,
    SynergyVersion version = kVersion1,
    PreviewDisplayType preview = kShadedPreview,
    DpiResolutionType dpi = k100dpi);

  SynergyVersion synergyVersion() const;

  PreviewDisplayType previewDisplayType() const;
  void setPreviewDisplayType(PreviewDisplayType pdt);

  CircularThreadEdgeDisplayType circularThreadEdgeDisplayType() const;
  void setCircularThreadEdgeDisplayType(CircularThreadEdgeDisplayType);

  SectionThreadEndDisplayType sectionThreadEndDisplayType() const;
  void setSectionThreadEndDisplayType(SectionThreadEndDisplayType);

  ProjectionType projectionType() const;
  void setProjectionType(ProjectionType prjtyp);

  DpiResolutionType dpiResolutionType() const;
  void setDpiResolutionType(DpiResolutionType);

  // OdDbObject methods :
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbViewRepStandard object pointers.
*/
typedef OdSmartPtr<OdDbViewRepStandard> OdDbViewRepStandardPtr;

#include "TD_PackPop.h"

#endif // OD_VIEWREPSTANDARD_H
