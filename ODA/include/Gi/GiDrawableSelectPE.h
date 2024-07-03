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

#ifndef __ODDRAWABLESELECTPE_H__
#define __ODDRAWABLESELECTPE_H__  /* { Secret} **/

#include "RxObject.h"
#include "GiDrawable.h"
#include "GiPathNode.h"
#include "Gs/Gs.h"
#include "Int64Array.h"

#include "TD_PackPush.h"

struct OdSiShape;

/** \details
    This class is the base class for custom classes that receive notification from OdGiDrawableSelectPE
    of Selection events.

    \remarks
    The default implementations of all methods in this class do nothing but return.

    \sa
    TD_Gi

    <group OdGi_Classes>
*/
class OdGiDrawablePESelectionReactor
{
public:
  //DOM-IGNORE-BEGIN
  enum
  {
    kNotImplemented = 0x80000000,
    kContinue = 0,
    kBreak = 1,
  };
  //DOM-IGNORE-END

  /** \details
    Notification function called whenever an sub object inside the drawable has been selected.

    \param offset    [in]  Offset of the selected sub object inside the drawable relative to the base marker
    \param depth     [in]  Depth of the selected sub object in the ECS (eye coordinate system)

    \remarks
    'offset' parameter supposed to be used in the case when each sub object (like face in the shell) inside the drawable has it's own marker.
    In this case the marker of the selected sub entity can be calculated as base marker + offset, where base marker is supposed to be the marker from
    OdGiPathNode object

    \returns
    Returns information about the next actions (continue, break) or informs that the method is not implemented
  */
  virtual OdUInt32 selected(OdGsMarker offset, double depth)
  {
    return OdUInt32(kNotImplemented);
  }

  /** \details
  Notification function called whenever it was discovered that there are sub objects which are out of selection

  \returns
  Returns information about the next actions (continue, break) or informs that the method is not implemented
*/
  virtual OdUInt32 hasOutOfSelection()
  {
    return OdUInt32(kNotImplemented);
  }
};

/** \details
    This class is the protocol extension for all graphical objects, both transient and persistent.
    
    \remarks
    This interface must be implemented in the case of ability to perform selection procedure by drawable itself

    <group OdGi_Classes> 
*/
class FIRSTDLL_EXPORT OdGiDrawableSelectPE : public OdRxObject
{
protected:
  OdGiDrawableSelectPE();
public:

  ODRX_DECLARE_MEMBERS(OdGiDrawableSelectPE);

  /** \details
  Return true if a drawable can perform selection inside 'pathNode' itself.

  \returns
  Returns true if and only if the drawable can perform selection inside 'pathNode' itself

  \remarks
  The default implementation does nothing and return false. This function can be
  overridden in custom classes.

  \param pathNode         [in]   Currently processing GiDrawable objects graph.
  \param nMarkersCovered  [out]  Number of markers which is covered by drawables's own selection procedure 
*/
  virtual bool canSelect(const OdGiPathNode& pathNode, OdGsMarker& nMarkersCovered) const;

  /** \details
  Runs selection procedure inside pathNode.

  \returns
  Returns nothing.

  \remarks
  The default implementation does nothing. This function can be overridden in custom classes.

  \param pathNode             [in]  Currently processing GiDrawable objects graph.
  \param pPoly                [in]  A pointer to an array of selection points in the eye coordinate space.
  \param nbPolyPts            [in]  A quantity of selection points.
  \param tol                  [in]  Tolerance.
  \param transformWorldToEye  [in]  Transformation matrix from world coordinate systen to the eye coordinate system.
  \param bNeedEyeDepth        [in]  Indicates that it is need to calculate the depth of the selected sub object in the ECS (eye coordinate system).
  \param pSelectionReactor    [in]  Selection callback pointer.
  \param pCustomSelectShape   [in]  Custom shape that represents extents of selection (pyramid in perspective case).
  \param pProjectionStartPoint[in]  If specified, detailed objects checking will use vector ( objectPoint - *pProjectionStartPoint) to project objectPoint on selection plane.
*/
  virtual void select(const OdGiPathNode& pathNode, const OdGePoint2d* pPoly, OdUInt32 nbPolyPts, const OdGeTol& tol,
                      const OdGeMatrix3d& transformWorldToEye, bool bNeedEyeDepth, OdGiDrawablePESelectionReactor* pSelectionReactor, 
    const OdSiShape* pCustomSelectShape = nullptr, const OdGePoint3d* pProjectionStartPoint = nullptr ) const;

};

/** \details
  The data type that represents a smart pointer to the <link OdGiDrawableSelectPE, OdGiDrawableSelectPE> object.
*/
typedef OdSmartPtr<OdGiDrawableSelectPE> OdGiDrawableSelectPEPtr;


#include "TD_PackPop.h"

#endif // __ODDRAWABLESELECTPE_H__

