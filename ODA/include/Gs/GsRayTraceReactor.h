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

#ifndef __ODGSRAYTRACEREACTOR_H_INCLUDED_
#define __ODGSRAYTRACEREACTOR_H_INCLUDED_

#include "TD_PackPush.h"

class OdGePoint3d;
class OdGeVector3d;
class OdGiViewport;
class OdGiPathNode;

/** \details
    This class is the base class for custom classes that receive notification
    of OdGs Ray Trace events.
    
    \remarks
    The default implementations of all methods in this class do nothing but return.

    \sa
    TD_Gs
  
    <group OdGs_Classes> 
*/
class OdGsRayTraceReactor
{
public:
  /** \details
    Container for ray and output result definition.
    \remarks
    Don't use it as data holder, since it store references onto data, but not data itself.
  */
  struct TraceResult
  {
    const OdGePoint3d &m_origin; // Ray origin / intersection point.
    const OdGeVector3d &m_direction; // Ray direction / intersection normal.

    /** \details
      Constructor for TraceResult class.

      \param origin    [in]  Ray origin.
      \param direction [in]  Ray direction.
    */
    TraceResult(const OdGePoint3d &origin, const OdGeVector3d &direction)
      : m_origin(origin), m_direction(direction) { }

    /** \details
      Returns intersection point or ray origin.
      
      \returns
      Ray origin point.
    */
    const OdGePoint3d &point() const { return m_origin; }
    
    /** \details
      Returns intersection normal or ray direction.
      
      \returns
      Ray direction vector.
    */
    const OdGeVector3d &normal() const { return m_direction; }
  };

  enum
  {
    kContinue = 0, // Continue ray tracing operation.
    kBreak    = 1  // Break ray tracing operation.
  };

  /** \details
    Notification function called whenever ray tracing found intersection with object.

    \param pathNode   [in]  Path to intersected object.
    \param intResult  [in]  Point of intersection and normal in World Coordinates System.
    \param ray        [in]  Ray definition in World Coordinates System.
    \param viewInfo   [in]  Viewport in which intersection process was executed.

    \remarks
    Returns code from unnamed enumeration declared in this class.
  */
  virtual OdUInt32 rayIntersection(const OdGiPathNode &pathNode, const TraceResult &intResult,
                                   const TraceResult &ray, const OdGiViewport &viewInfo) = 0;

  /** \details
    Destructor for the OdGsRayTraceReactor class.
  */
  virtual ~OdGsRayTraceReactor() {}
};

#include "TD_PackPop.h"

#endif // __ODGSRAYTRACEREACTOR_H_INCLUDED_
