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

#ifndef ODDB_DBSHFILLET_H
#define ODDB_DBSHFILLET_H

#include "TD_PackPush.h"

#include "DbShHistoryNode.h"

/** \details

        <group OdDbSh_Classes> 
*/
class DB3DSOLIDHISTORY_EXPORT OdDbShFillet : public OdDbShHistoryNode
{
public:
  ODDB_DECLARE_MEMBERS(OdDbShFillet);
  OdDbShFillet();

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);  
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;  
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);  
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  int numEdges();
  OdGeDoubleArray& getStartSetbacks();
  OdGeDoubleArray& getEndSetbacks();
  OdGeDoubleArray& getRadiuses();
  OdResult setStartSetbacks(const OdGeDoubleArray& arr);
  OdResult setEndSetbacks(const OdGeDoubleArray& arr);
  OdResult setRadiuses(const OdGeDoubleArray& arr);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbShFillet object pointers.
*/
typedef OdSmartPtr<OdDbShFillet> OdDbShFilletPtr;

#include "TD_PackPop.h"

#endif

