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

#ifndef __ODGIPOSTTRANSFORM_H__
#define __ODGIPOSTTRANSFORM_H__

#include "Gi/GiXform.h"
#include "Ge/GeDoubleArray.h"

#include "TD_PackPush.h"

/** \details

    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiPostTransform : public OdGiXform
{
protected:
  OdGiPostTransform() {}
public:
  ODRX_DECLARE_MEMBERS(OdGiPostTransform);

  /** \details
    Specifies the draw context for this linetyper.

    \param pDrawCtx [in]  Pointer to the drawing context.
  */
  virtual void setDrawContext(OdGiConveyorContext *pDrawCtx) = 0;

  /** \details
    Specifies the deviation for drawing linetypes.

    \param deviations [in]  Array of deviation values for drawing linetypes.
  */
  virtual void setDeviation(const OdGeDoubleArray &deviations) = 0;
  /** \details
    Specifies the deviation for drawing linetypes.

    \param deviation [in]  Deviation for drawing linetypes.
  */
  virtual void setDeviation(const OdGiDeviation *pDeviation) = 0;

  /** \details
    Enables this transform.
  */
  virtual void enable() = 0;
  /** \details
    Disables this transform.
  */
  virtual void disable() = 0;

  /** \details
    Checks whether this transform is enabled.

    \returns
    true if this transform is enabled, false otherwise.
  */
  virtual bool enabled() const = 0;
};

typedef OdSmartPtr<OdGiPostTransform> OdGiPostTransformPtr;

#include "TD_PackPop.h"

#endif //#ifndef __ODGIPOSTTRANSFORM_H__
