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



#ifndef __ODGIHLREMOVERRESULTS__
#define __ODGIHLREMOVERRESULTS__

#include "RxObject.h"

#include "TD_PackPush.h"

/** \details

    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiHlrResults : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGiHlrResults);

  class Traits {
  public:
    OdDbStub         *plotStyle = NULL;
    OdGsMarker        selMarker = 0;
    OdCmEntityColor   color;
    OdCmEntityColor   obscuredColor;
    OdDb::LineWeight  lineWeight = OdDb::kLnWt000;
  };

  class Data {
  public:
    Traits*           pTraits = NULL;
    OdGePoint3dArray  visible;
    OdGePoint3dArray  hidden;
  };

  /** \details
    Sets this Iterator object to reference the entry following the current entry.

    \returns
    Returns true if and only if not at the end of the list.
  */
  virtual const Data* next() = 0;

  virtual void start() = 0;

  /** \details
    Retrives Gi path of drawable the current Data returned by the most recent call to next() corresponds to.

    \returns
    Returns OdDbStubPtrArray that represents current drawable path.
  */
  virtual OdDbStubPtrArray currentDrawablePath() const = 0;
};

/** \details
  The data type that represents a smart pointer to the <link OdGiHlrResults, OdGiHlrResults> object.
*/
typedef OdSmartPtr<OdGiHlrResults> OdGiHlrResultsPtr;


#include "TD_PackPop.h"

#endif // __ODGIHLREMOVERRESULTS__
