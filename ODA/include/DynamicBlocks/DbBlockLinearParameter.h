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

#ifndef _DbBlockLinearParameter_h_Included_
#define _DbBlockLinearParameter_h_Included_

#include "DbBlock2PtParameter.h"
#include "DbBlockParamValueSet.h"

class OdDbBlockLinearGrip;
typedef OdSmartPtr<OdDbBlockLinearGrip> OdDbBlockLinearGripPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockLinearParameter : public OdDbBlock2PtParameter
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockLinearParameter);
  OdDbBlockLinearParameter();
  OdString distanceDescription() const;
  OdString distanceName() const;
  OdDbBlockLinearGripPtr getAssociatedLinearGrip(OdDbBlockParameter::ParameterComponent, OdDb::OpenMode);
  double offset() const;
  void setDistanceDescription(const OdString&);
  void setDistanceName(const OdString&);
  void setOffset(double);
  //void setUpdatedDistance(double);
  void setValueSet(const OdDbBlockParamValueSet&);
  const OdDbBlockParamValueSet& valueSet() const;
  void stretch(const OdGeMatrix3d& m);
};

typedef OdSmartPtr<OdDbBlockLinearParameter> OdDbBlockLinearParameterPtr;

#endif //_DbBlockLinearParameter_h_Included_
