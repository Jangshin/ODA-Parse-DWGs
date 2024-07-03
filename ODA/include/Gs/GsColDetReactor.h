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

#ifndef __GS_COLLISION_DETECTION_REACTOR_H_INCLUDED_
#define __GS_COLLISION_DETECTION_REACTOR_H_INCLUDED_

class OdGiPathNode;

#include "TD_PackPush.h"

#include "Ge/GeTol.h"

/** \details
    This class is the base class for custom classes that receive notification
    of OdGs Collision Detection events.
    
    \remarks
    The default implementations of all methods in this class do nothing but return.

    <group OdGs_Classes> 
    \sa
    <link gs_collision_detection, Work with Collision Detection>
*/
class OdGsCollisionDetectionReactor
{
public:
  enum
  {
    kNotImplemented = 0x80000000,
    kContinue       = 0,
    kBreak          = 1
  };
  /** \details
    Notification function called whenever an collision detected.

    \param pPathNode1 [in]  Pointer to the OdGiPathNode object from OdGsView::collide input list
    \param pPathNode2 [in]  Pointer to the OdGiPathNode object that collides with pathNode1

    \remarks
    Returns kContinue if the operation is to continue or kBreak to stop collision detection
  */
  virtual OdUInt32 collisionDetected(const OdGiPathNode* /*pPathNode1*/, const OdGiPathNode* /*pPathNode2*/)
  {
    return OdUInt32(kNotImplemented);
  }

  /** \details
  Notification function called whenever an collision detected if distance calsulation is specified

  \param pPathNode1 [in]  Pointer to the OdGiPathNode object from OdGsView::collide input list
  \param pPathNode2 [in]  Pointer to the OdGiPathNode object that collides with pathNode1
  \param dDistace   [in]  Collision distance. If negative, it is the penetration depth. If positive, it is the clearance.

  \remarks
  Returns kContinue if the operation is to continue or kBreak to stop collision detection
*/
  virtual OdUInt32 collisionDetected( const OdGiPathNode* pPathNode1, const OdGiPathNode* pPathNode2, double dDistance )
  {
    return collisionDetected( pPathNode1, pPathNode2 );
  }
};

/** \details
    This class is the context for Collision Detection
    
    \sa
    TD_Gs
  
    <group OdGs_Classes> 
*/
class OdGsCollisionDetectionContext
{
//DOM-IGNORE-BEGIN
protected:
  OdUInt8 m_flags;
  OdGeTol m_tolerance;
  enum Options
  {
    kIntersectionOnly = 1,
    kIntersectionWithModel = 1 << 1,
    kIgnoreViewExtents = 1 << 2,
    kCombineSubEntities = 1 << 3,
    kOverrideTolerance = 1 << 4,
    kCalculateDistance = 1 << 5,
    kCheckAll = 1 << 6,
    kProcessSingleList = 1 << 7
  };
  double m_clearance;
//DOM-IGNORE-END
public:
  /** \details
    Default constructor for the OdGsCollisionDetectionContext class. Sets default tolerance value for geometric operations.
  */
  OdGsCollisionDetectionContext() : m_flags( kCalculateDistance ) { m_tolerance = OdGeTol(); m_clearance = 0.0; };

  /** \details
    Sets flag that specifies whether collisions are detected only when objects intersect.
    \param bSet    [in]  Flag that specifies whether to detect collisions only when objects intersect. If set to false, collisions can be detected via touches (no intersections).
  */
  void setIntersectionOnly( bool bSet ) { SETBIT( m_flags, kIntersectionOnly, bSet ); }
  
  /** \details
    Retrieves a flag that specifies whether collisions are detected only when objects intersect. 
    \returns
    true if collisions are detected only when objects intersect or false when collisions can be detected via touches.
  */
  bool intersectionOnly() const { return GETBIT( m_flags, kIntersectionOnly ); }

  /** \details
    Sets flag that specifies whether collisions should be detected with a model.
    \param bSet    [in]  Flag that specifies whether to detected collisions with a model.
  */
  void setIntersectionWithModel( bool bSet ) { SETBIT( m_flags, kIntersectionWithModel, bSet ); }
  
  /** \details
    Retrieves a flag that specifies whether collisions are detected only when objects intersect. 
    \returns
    true if collisions are detected only when objects intersect or false when collisions can be detected via touches.
  */
  bool intersectionWithModel() const { return GETBIT( m_flags, kIntersectionWithModel ); }

  /** \details
    Specifies whether collisions should be detected despite objects are outside view extents.
    \param bSet    [in]  Flag that specifies whether to detected collisions even if objects are beyond view extents.
  */
  void setIgnoreViewExtents( bool bSet ) { SETBIT( m_flags, kIgnoreViewExtents, bSet ); }
  
  /** \details
    Checks whether collisions are detected even if objects are outside view extents. 
    \returns
    true if collisions are detected even if objects are beyond view extents, false otherwise.
  */
  bool ignoreViewExtents() const { return GETBIT( m_flags, kIgnoreViewExtents ); }
  /** \details
  Specifies subentity markers ignoring.
  \param bSet [in] If true, subentities markers will be ignored.
  */
  void setCombineSubEntities( bool bSet ) { SETBIT( m_flags, kCombineSubEntities, bSet ); }
  /** \details
  Retrives subentity markers ignoring.
  \returns Returns flag that indicates should subentities markers be ignored or not.
  */
  bool combineSubEntities() const { return GETBIT( m_flags, kCombineSubEntities ); }
  /** \details
  Specifies custom collision tolerance.
  \param tol [in] Collision tolerance
  */
  void setToleranceOverride( const OdGeTol& tol )
  {
    SETBIT_1( m_flags, kOverrideTolerance );
    m_tolerance = tol;
  }
  /** \details
  Checks that collision detection should use custom tolerance.
  \returns Returns flag that indicates should collision detection use custom tolerance or not.
  */
  bool isToleranceOverride() const { return GETBIT( m_flags, kOverrideTolerance ); }
  /** \details
  Retrives custom collision detection tolerance.
  \returns Returns custom collision detection tolerance.
  */
  const OdGeTol& toleranceOverride() const { return m_tolerance; }
  /** \details
  Specifies that collision detection should also calculate distances (penetration depth or distance between objects)
  \param bSet [in] If true, distances will be calculated.
  */
  void setCalculateDistance( bool bSet ) { SETBIT( m_flags, kCalculateDistance, bSet ); }
  /** \details
  Checks should collision detection calculate distances (penetration depth or distance between objects)
  \returns Returns flag that indicates should collision detection calculate distances or not.
  */
  bool getCalculateDistance() const { return GETBIT( m_flags, kCalculateDistance ); }
  /** \details
  Specifies that collision detection should check all faces instead of detecting first collision.
  \param bSet [in] If true, collision detection will check all faces instead of detecting first collision.
  */
  void setCheckAll( bool bSet ) { SETBIT( m_flags, kCheckAll, bSet ); }
  /** \details
  Checks that collision detection should check all faces instead of detecting first collision.
  \returns Returns flag that indicates should collision detection check all faces instead of detecting first collision.
  */
  bool getCheckAll() const { return GETBIT( m_flags, kCheckAll ); }
  /** \details
  Specifies collision detection clearance value.
  \param c [in] Collision detection clearance value.
  */
  void setClearance( double c ) { m_clearance = c; }
  /** \details
  Retrives collision detection clearance value.
  \returns Returns collision detection clearance value.
  */
  double getClearance() const { return m_clearance; }
  /** \details
  Specifies should collision detection detects collisions between list and all other entities (false)
  or it should detect collisions between entities in list (true).
  \param bSet [in] If true, collision detection will detect collisions between entities in list instead of between list and other entities.
  */
  void setProcessSingleList( bool bSet ) { SETBIT( m_flags, kProcessSingleList, bSet ); }
  /** \details
  Checks that collision detection should detects collisions between list and all other entities (false)
  or it should detect collisions between entities in list (true).
  \returns Returns flag that indicates should collision detection detect collisions between entities in list instead of between list and other entities.
  */
  bool getProcessSingleList() const { return GETBIT( m_flags, kProcessSingleList ); }
};

#include "TD_PackPop.h"

#endif // __GS_COLLISION_DETECTION_REACTOR_H_INCLUDED_
