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



#ifndef __OD_GI_H_L_REMOVER__
#define __OD_GI_H_L_REMOVER__

#include "Ge/GeDoubleArray.h"
#include "Gi/GiConveyorNode.h"
#include "DbStubPtrArray.h"

class OdGiDeviation;

#include "TD_PackPush.h"

class OdGiHlrResults;
typedef OdSmartPtr<OdGiHlrResults> OdGiHlrResultsPtr;

/** \details
    <group OdGi_Classes>
*/
class ODGI_EXPORT OdGiHLRContext
{
public:
  /** \details
    Gets obscured color.
    \param clr [out] Color.
  */
  virtual void getObscuredColor(OdCmEntityColor& clr) {}

  /** \details
    Sets flag that output hidden lines is in progress.
  */
  virtual void beginHiddenOutput() {}

  /** \details
    Clears flag that output hidden lines is in progress.
  */
  virtual void endHiddenOutput() {}
};

/** \details

    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiHLRemover : public OdGiConveyorNode
{
public:
  ODRX_DECLARE_MEMBERS(OdGiHLRemover);

  /** Sets max deviation for curve tesselation.
  */
  virtual void setDeviation(const OdGeDoubleArray& deviations) = 0;

  /** Sets deviation object to obtain max deviation for curve tesselation.
  */
  virtual void setDeviation(const OdGiDeviation* pDeviation) = 0;

  /** Sets the draw context object (to access to traits, etc).
  */
  virtual void setDrawContext(OdGiConveyorContext* pDrawCtx) = 0;

  /** Computes and pulls scene with hidden lines removed 
  */
  virtual void process() = 0;

  virtual void enable(bool enabled) = 0;

  virtual bool enabled() const = 0;

  virtual void invertZ(bool bDoIt) = 0;

  virtual bool zInverted() const = 0;

  virtual OdGiHlrResultsPtr hlrResults(unsigned int* pNumItems = 0) const = 0;

  virtual void freeResults() = 0;

  virtual void keepHidden(bool bDoIt) = 0;

  virtual bool hiddenKept() const = 0;

  virtual OdDbStubPtrArray currentDrawablePath() const = 0;

  virtual void setCurrentDrawablePath(const OdDbStubPtrArray& path) = 0;

  virtual void setHLRemoverContext(OdGiHLRContext* pCtx) = 0;
};

/** \details
  The data type that represents a smart pointer to the <link OdGiHLRemover, OdGiHLRemover> object.
*/
typedef OdSmartPtr<OdGiHLRemover> OdGiHLRemoverPtr;

#include "TD_PackPop.h"

#endif // __OD_GI_H_L_REMOVER2__
