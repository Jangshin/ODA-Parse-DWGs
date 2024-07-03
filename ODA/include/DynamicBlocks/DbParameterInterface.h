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

#include <RxObject.h>
#include <OdString.h>
#include <DbEvalVariant.h>
#include "DbParameterValueSet.h"

class OdDbParameterInterfaceImpl;

/** 
  <group OdDb_Classes>
*/
class DYNBLOCKS_EXPORT OdDbParameterInterface : public OdRxObject
{
  friend class OdDbParameterInterfaceImpl;
  OdDbParameterInterfaceImpl* m_pImpl;
public:
  ODRX_DECLARE_MEMBERS(OdDbParameterInterface);
  OdDbParameterInterface();
  virtual ~OdDbParameterInterface();
  virtual OdString getName() const;
  virtual void setName(const OdString&); // not implemented
  virtual bool isNameValid(const OdString&) const;
  virtual bool isNameUnique(const OdString&) const;
  //virtual void getExpression(OdString&, bool&, OdDbEvalVariant&);
  virtual OdString getExpression() const;
  virtual void setExpression(const OdString&);
  virtual OdString getDescription() const;
  virtual void setDescription(const OdString&);
  virtual OdDbEvalVariantPtr getValue() const;
  virtual void setValue(const OdDbEvalVariant&);
  virtual OdDbParameterValueSetPtr getValueSet() const;
  virtual bool getIsReadOnly() const;
  virtual DwgDataType getDataType() const;
  virtual bool isUsedInExpression() const;
  virtual bool isAngular() const;
  virtual bool isRuntimeInterface() const;
  virtual OdDbObjectId parameterObject() const;
};

typedef OdSmartPtr<OdDbParameterInterface> OdDbParameterInterfacePtr;
