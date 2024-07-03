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
#ifndef _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONPARAMETERS_INCLUDED_
#define _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONPARAMETERS_INCLUDED_

#include "OdSpatialReference.h"

namespace OdSpatialReference
{
  /** \details
    This enumeration indicates the type of geodetic transformation definition.
  */
  enum TransformationDefType
  {
    kTypeNone = 0,
    kTypeStandalone = 1,
    kTypeAnalytical = 2,
    kTypeInterpolation = 3,
    kTypeMultipleRegression = 4
  };

  class OdGeodeticTransformationParametersImpl;

  /** \details
    This class is the base class for geodetic transformation classes.
  
    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdGeodeticTransformationParameters : public OdRxObject
  {
    ODSPREF_RX_WITH_IMPL_DECLARE_MEMBERS(OdGeodeticTransformationParameters);
  public:
  };
  typedef OdSmartPtr<OdGeodeticTransformationParameters> OdGeodeticTransformationParametersPtr;
}

#endif //_ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONPARAMETERS_INCLUDED_
