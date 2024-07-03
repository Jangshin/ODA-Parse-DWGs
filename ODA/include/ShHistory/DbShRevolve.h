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

#ifndef ODDB_DBSHREVOLVE_H
#define ODDB_DBSHREVOLVE_H

#include "TD_PackPush.h"
#include "DbShPrimitive.h"
#include "DbRevolveOptions.h"

/** \details

        <group OdDbSh_Classes> 
*/
class DB3DSOLIDHISTORY_EXPORT OdDbShRevolve : public OdDbShPrimitive
{
public:
  ODDB_DECLARE_MEMBERS(OdDbShRevolve);
  OdDbShRevolve();

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);  
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;  
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);  
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  OdGePoint3d axisPoint() const;
  OdResult setAxisPoint(OdGePoint3d const& pt);
  OdGeVector3d direction() const;
  OdResult setDirection(OdGeVector3d const& pdir);
  double revolveAngle() const;
  OdResult setRevolveAngle(double val);
  double startAngle() const;
  OdResult setStartAngle(double angle);
  OdResult getRevolveOptions(OdDbRevolveOptions& revOpt) const;
  OdResult setRevolveOptions(OdDbRevolveOptions const& revOpt);
  OdResult setRevolve(OdGePoint3d const& pt, OdGeVector3d const& pdir, double dRevAng, OdDbRevolveOptions const & revOpt);
  OdDbEntityPtr revolveEntity() const;
  OdResult setRevolveEntity(OdDbEntity* pRevolveEnt);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbShRevolve object pointers.
*/
typedef OdSmartPtr<OdDbShRevolve> OdDbShRevolvePtr;

#include "TD_PackPop.h"

#endif

