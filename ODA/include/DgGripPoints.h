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



#ifndef _ODDGGPIPPOINTS_INCLUDED_
#define _ODDGGPIPPOINTS_INCLUDED_

#include "RxObject.h"
#include "RxModule.h"
#include "IntArray.h"
#include "DgElement.h"
#include "Gi/GiDrawable.h"

class OdDgCommandContext;

/** \details
    This class is the Grip Points Protocol Extension class.
    \sa
    TD_Db

    <group OdDb_Classes> 
*/
class TG_EXPORT OdDgGripPointsPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGripPointsPE);
  
  /** \details
    Returns all grip points of the specified entity.

    \param pEntity [in]  Pointer to the entity.
    \param gripPoints [in/out] Receives an array of WCS grip points.

    \remarks
    Grip points are appended to the specified array.
    
    \returns
    Returns eOk if successful, or an appropriate error code if not.
    The default implementation of this function returns eNotImplemented.
  */
  virtual OdResult getGripPoints(
    const OdDgElement* pEntity,
    OdGePoint3dArray& gripPoints ) const;

  /** \details
    Moves the specified grip points of the specified entity.
    
    \param pEntity [in]  Pointer to the entity.
    \param indices [in]  Array of indicies.
    \param offset [in] The direction and magnitude of the grip points offset (WCS).
    
    \remarks
    Each element in gripPoints has a corresponding entry in indices, which specifies the index of 
    the grip point as returned by getGripPoints.
    
    \returns
    Returns eOk if successful, or an appropriate error code if not.
    The default implementation of this function returns eNotImplemented.
  */
    virtual OdResult moveGripPointsAt(
    OdDgElement* pEntity,
    const OdIntArray& indices,
    const OdGeVector3d& offset );

  /** \details
    Returns OdDbGripData objects for grip points of this entity.

    \param pEntity [in]  Pointer to the entity.
    \param grips [in/out] Receives an array of OdDbGripData objects.

    \remarks
    Grip points are appended to the specified array.
    When eNotImplemented is returned, the application should call the other overload of the getGripPoints() method.
    The default implementation of this function returns eNotImplemented.
  */
  virtual OdResult getGripPoints(
    const OdDgElement* pEntity,
    OdDgGripDataPtrArray& grips,
    const double curViewUnitSize,
    const int gripSize,
    const OdGeVector3d& curViewDir,
    const int bitFlags ) const;

  /** \details
    Moves the specified grip points of this entity.
    
    \param pEntity [in]  Pointer to the entity.
    \param grips [in]  Array of OdDbGripData identifiers.
    \param offset [in] The direction and magnitude of the grip points offset (WCS).

    \remarks
    The default implementation of this function returns eNotImplemented. 
  */
    virtual OdResult moveGripPointsAt(
    OdDgElement* pEntity,
    const OdDgVoidPtrArray& grips,
    const OdGeVector3d& offset,
    int bitFlags );

  /** \details
    Returns all stretch points of the specified entity.

    \param pEntity [in]  Pointer to the entity.
    \param stretchPoints [in/out] Receives an array of WCS stretch points.

    \remarks
    Stretch points are appended to the specified array.
    
    \returns
    Returns eOk if successful, or an appropriate error code if not.
    The default implementation of this function returns eNotImplemented.
  */
  virtual OdResult getStretchPoints(
    const OdDgElement* pEntity,
    OdGePoint3dArray& stretchPoints ) const;
  /** \details
    Moves the specified stretch points of this entity.
    
    \param pEntity [in]  Pointer to the entity.
    \param indices [in]  Array of indicies.
    \param offset [in] The direction and magnitude of the stretch points offset (WCS).
    
    \remarks
    Each element in stretchPoints has a corresponding entry in indices, which specifies the index of 
    the stretch point as returned by getStretchPoints.
    
    \returns
    Returns eOk if successful, or an appropriate error code if not.
    The default implementation of this function returns eNotImplemented.
  */
    virtual OdResult moveStretchPointsAt(
    OdDgElement* pEntity,
    const OdIntArray& indices,
    const OdGeVector3d& offset );

  /** \details
    Returns all appropriate object snap points of the specified entity.
    
    \param pEntity [in]  Pointer to the entity.
    \param osnapMode [in]  The object snap mode being queried.
    \param gsSelectionMark [in]  The GS marker of the subentity being queried.
    \param pickPoint [in]  The WCS point being queried.
    \param lastPoint [in]  The WCS point picked before pickPoint.
    \param viewXform [in]  The WCS->DCS transformation matrix.
    \param ucs [in]  The WCS->UCS transformation matrix.
    \param snapPoints [in/out] Receives an array of UCS object snap points.
    
    \remarks
    Object snap points are appended to the specified array.
    
    osnapMode must be one of the following:
    
    <table>
    Name                      Value   Description 
    OdDb::kOsModeEnd          1       Endpoint
    OdDb::kOsModeMid          2       Midpoint
    OdDb::kOsModeCen          3       Center
    OdDb::kOsModeNode         4       Node
    OdDb::kOsModeQuad         5       Quadrant
    OdDb::kOsModeIntersec     6       Intersection
    OdDb::kOsModeIns          7       Insertion point
    OdDb::kOsModePerp         8       Perpendicular
    OdDb::kOsModeTan          9       Tangent
    OdDb::kOsModeNear         10      Nearest
    OdDb::kOsModeApint        11      Apparent intersection
    OdDb::kOsModePar          12      Parallel
    OdDb::kOsModeStart        13      Unknown 
    </table>
   
    The default implementation of this function returns eNotImplemented.
  */
    virtual OdResult getOsnapPoints( 
    const OdDgElement* pEntity, 
    OdDgElement::OsnapMode osnapMode, 
    OdGsMarker gsSelectionMark, 
    const OdGePoint3d& pickPoint,
    const OdGePoint3d& lastPoint, 
    const OdGeMatrix3d& xWorldToEye, 
    OdGePoint3dArray& snapPoints ) const;

  /** \details
  Returns all appropriate object snap points of the specified entity.

  \param pEntity [in]  Pointer to the entity.
  \param osnapMode [in]  The object snap mode being queried.
  \param gsSelectionMark [in]  The GS marker of the subentity being queried.
  \param pickPoint [in]  The WCS point being queried.
  \param lastPoint [in]  The WCS point picked before pickPoint.
  \param viewXform [in]  The WCS->DCS transformation matrix.
  \param ucs [in]  The WCS->UCS transformation matrix.
  \param snapPoints [in/out] Receives an array of UCS object snap points.
  \param insert [in] Current insertion matrix

  \remarks
  Object snap points are appended to the specified array.

  osnapMode must be one of the following:

  <table>
  Name                      Value   Description 
  OdDb::kOsModeEnd          1       Endpoint
  OdDb::kOsModeMid          2       Midpoint
  OdDb::kOsModeCen          3       Center
  OdDb::kOsModeNode         4       Node
  OdDb::kOsModeQuad         5       Quadrant
  OdDb::kOsModeIntersec     6       Intersection
  OdDb::kOsModeIns          7       Insertion point
  OdDb::kOsModePerp         8       Perpendicular
  OdDb::kOsModeTan          9       Tangent
  OdDb::kOsModeNear         10      Nearest
  OdDb::kOsModeApint        11      Apparent intersection
  OdDb::kOsModePar          12      Parallel
  OdDb::kOsModeStart        13      Unknown 
  </table>

  The default implementation of this function returns eNotImplemented.
  */
    virtual OdResult getOsnapPoints( 
    const OdDgElement* pEntity, 
    OdDgElement::OsnapMode osnapMode, 
    OdGsMarker gsSelectionMark, 
    const OdGePoint3d& pickPoint,
    const OdGePoint3d& lastPoint, 
    const OdGeMatrix3d& xWorldToEye, 
    OdGePoint3dArray& snapPoints,
    const OdGeMatrix3d& insert) const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbGripPointsPE object pointers.
*/
typedef OdSmartPtr<OdDgGripPointsPE> OdDgGripPointsPEPtr;

#endif //_ODDGGPIPPOINTS_INCLUDED_
