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




#ifndef OD_DBLYINDX_H
#define OD_DBLYINDX_H

#include "TD_PackPush.h"

#include "DbIndex.h"

class OdDbLayerTable;

/** \details
    This class implements Layer Index objects in an OdDbDatabase instance.

    
    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbLayerIndex: public OdDbIndex
{
public:
  ODDB_DECLARE_MEMBERS(OdDbLayerIndex);

  OdDbLayerIndex();

  OdDbFilteredBlockIteratorPtr newIterator(
    const OdDbFilter* pFilter) const;
  
  virtual void rebuildFull(
    OdDbIndexUpdateData* pIdxData);
  
  //void compute(OdDbLayerTable* pLT, OdDbBlockTableRecord* pBTR);
  
  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);
  
  virtual void dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdDbDxfFiler* pFiler) const;

protected:
  virtual void rebuildModified(
    OdDbBlockChangeIterator* iterator);
};


/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbLayerIndex object pointers.
*/
typedef OdSmartPtr<OdDbLayerIndex> OdDbLayerIndexPtr;

#include "TD_PackPop.h"

#endif // OD_DBLYINDX_H

