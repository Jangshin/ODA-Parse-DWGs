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

#include "ModelDocObjExports.h"
#include "DbObjectId.h"
#include "IdArrays.h"
#include "StringArray.h"
#include "Ge/GeDoubleArray.h"

/**
 * <group Other_Classes>
 */
class MODELDOCOBJ_EXPORT OdSyScaleList
{
public:
  OdSyScaleList();
  void init(OdDbDatabase* pDb, const OdDbObjectId* id = NULL, const OdString* name = NULL);

  OdGeDoubleArray::size_type findClosestScaleIdx(double scale) const;
  OdDbObjectId findNextBiggerScaleFactor(const OdDbObjectId& id, double scale) const;
  OdDbObjectId findScaleId(double scale, const OdDbDatabase* pDb) const;
  OdDbObjectId findScaleId(double scale, bool) const;

protected:
  OdDbObjectId findScaleId(double scale, const OdString& name) const;

public:
  OdDbObjectIdArray::size_type findScaleIdx(const OdDbObjectId&) const;
  OdDbObjectIdArray::size_type findScaleIdx(const OdString& name) const;
  int fromParentIdx() const;
  void getLists(OdStringArray& names, OdDbObjectIdArray& ids, OdGeDoubleArray& scales) const;
  bool getScale(OdGeDoubleArray::size_type index, OdDbObjectId & id, double & scale) const;

  static OdResult getScale(double& scale, const OdDbObjectId& id);

private:
  OdStringArray m_aNames;
  OdGeDoubleArray m_aScales;
  OdDbObjectIdArray m_aIds;
};
