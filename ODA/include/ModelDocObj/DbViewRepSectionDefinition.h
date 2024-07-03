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

#pragma once

#include "DbObject.h"
#include "ModelDocObjExports.h"
#include "DbViewRepCutDefinition.h"

#include "TD_PackPush.h"

/** \details

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 
*/
class MODELDOCOBJ_EXPORT OdDbViewRepSectionDefinition : public OdDbViewRepCutDefinition
{
public:
  ODDB_DECLARE_MEMBERS(OdDbViewRepSectionDefinition);
  OdDbViewRepSectionDefinition();
  ~OdDbViewRepSectionDefinition() ODRX_OVERRIDE_DESTRUCTOR;

  enum ESectionConstrainTo // odiv::ViewEnums::ESectionConstrainTo
  {
    kConstrainUndefined      = 0,
    kConstrainToFirstSegment = 1,
    kConstrainToLastSegment  = 2,
  };
  void setConstrainTo(ESectionConstrainTo value);
  ESectionConstrainTo constrainTo() const;

  enum ESectionParticipation // odiv::ViewEnums::ESectionParticipation
  {

  };
  void setParticipation(ESectionParticipation value);
  ESectionParticipation participation() const;

  void setFullDepth(bool doIt = true);
  bool fullDepth() const;

  void setMethodAligned(bool doIt = true);
  bool methodAligned() const;

  void setDepth(double);
  double depth() const;

  // TODO: Review
  void setSlice(bool doIt = true);
  bool slice() const;

  // OdDbObject methods :
  OdResult dwgInFields(OdDbDwgFiler* pFiler) ODRX_OVERRIDE;
  void dwgOutFields(OdDbDwgFiler* pFiler) const ODRX_OVERRIDE;
  OdResult dxfInFields(OdDbDxfFiler* pFiler) ODRX_OVERRIDE;
  void dxfOutFields(OdDbDxfFiler* pFiler) const ODRX_OVERRIDE;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbViewRepSectionDefinition object pointers.
*/
typedef OdSmartPtr<OdDbViewRepSectionDefinition> OdDbViewRepSectionDefinitionPtr;

#include "TD_PackPop.h"
