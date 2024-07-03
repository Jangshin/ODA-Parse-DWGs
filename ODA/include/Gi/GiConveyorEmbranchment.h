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


#ifndef __OD_GI_CONVEYOREMBRANCHMENT__
#define __OD_GI_CONVEYOREMBRANCHMENT__

#include "Gi/GiConveyorNode.h"
#include "Gi/GiDeviation.h"

#include "TD_PackPush.h"

/** \details

    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiConveyorEmbranchment : public OdGiConveyorNode
{
public:
  ODRX_DECLARE_MEMBERS(OdGiConveyorEmbranchment);

  virtual OdGiConveyorOutput& secondOutput() = 0;

  virtual bool isSimplifyOpt(OdUInt32 opt) const = 0;

  virtual void setDrawContext(OdGiConveyorContext* pDrawCtx) = 0;

  virtual void setDeviation(const OdGeDoubleArray& deviations) = 0;
  virtual void setDeviation(const OdGiDeviation* pDeviation) = 0;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGiConveyorEmbranchment object pointers.
*/
typedef OdSmartPtr<OdGiConveyorEmbranchment> OdGiConveyorEmbranchmentPtr;

#include "TD_PackPop.h"

#endif // __OD_GI_CONVEYOREMBRANCHMENT__
