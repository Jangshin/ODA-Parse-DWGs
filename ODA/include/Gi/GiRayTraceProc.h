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

#ifndef __ODGIRAYTRACEPROC__
#define __ODGIRAYTRACEPROC__

#include "Gi/GiSelectProcBase.h"

class OdGiPathNode;
class OdGsRayTraceReactor;

#include "TD_PackPush.h"

/** \details
  This class implements conveyor nodes performing ray tracing.

  \remarks
  This conveyor node is used for implementation OdGsBaseVectorizeView::rayTrace()
  and does not produce any output.

  <group OdGi_Classes>
*/
class ODGI_EXPORT OdGiRayTraceProc : public OdGiSelectProcBase
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdGiRayTraceProc);
  //DOM-IGNORE-END

  /** \details
    Ray tracing mode.
  */
  enum class RayTracingMode
  {
    kStandardMode = 0, // Standard (unordered) ray tracing.
    kSortedMode   = 1  // Sorted ray tracing.
  };

  /** \details
    Sets the ray tracing query, mode and reactor.

    \param rayOrigin [in]  Ray origin point.
    \param rayDirection [in]  Ray direction vector.
    \param mode [in]  RayTracing mode.
    \param pReactor [in]  Pointer to the ray tracing reactor.
  */
  virtual void set(const OdGePoint3d &rayOrigin, const OdGeVector3d &rayDirection,
                   RayTracingMode mode, OdGsRayTraceReactor* pReactor) = 0;

  /** \details
    Retrieves ray tracing query.

    \param rayOrigin [out]  Ray origin point.
    \param rayDirection [out]  Ray direction vector.
  */
  virtual void get(OdGePoint3d &rayOrigin, OdGeVector3d &rayDirection) const = 0;

  /** \details
    Sets ray tracing filter paths.

    \param pObjectList [in]  Optional list of graphic scene objects participating in ray tracing.
    \param nObjectListSize [in]  Number of objects inside pObjectList.
  */
  virtual void setFilter(OdGiPathNode const* const* pObjectList = NULL, OdUInt32 nObjectListSize = 0) = 0;
};

/** \details
  A data type that represents a smart pointer to an
  <link OdGiSelectProc, OdGiSelectProc> object.
*/
typedef OdSmartPtr<OdGiRayTraceProc> OdGiRayTraceProcPtr;

#include "TD_PackPop.h"

#endif //#ifndef __ODGIRAYTRACEPROC__
