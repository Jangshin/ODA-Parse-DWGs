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
#ifndef _ODSPATIALREFERENCE_ODGEODETICPATHELEMENT_INCLUDED_
#define _ODSPATIALREFERENCE_ODGEODETICPATHELEMENT_INCLUDED_

#include "OdSpatialReference.h"

namespace OdSpatialReference
{
  class OdGeodeticPathElementImpl;

  /** \details
    This class represents a geodetic path element.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdGeodeticPathElement : public OdRxObject
  {
    ODSPREF_RX_WITH_IMPL_DECLARE_MEMBERS(OdGeodeticPathElement);
  public:
    /** \details
      Returns the transformation name of this geodetic path element.

      \param sName [out] Transformation name.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getTransformName(OdString& sName) const;

    /** \details
      Sets the transformation name for this geodetic path element.

      \param sName [in] Transformation name.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setTransformName(const OdString& sName);

    /** \details
      Checks whether this geodetic path element has inversed direction.

      \returns Returns true - if direction iversed.
    */
    bool isInversed() const;
    
    /** \details
      Sets direction for this geodetic path element.

      \param bIsInversed [in] if true - inversed direction, othervise - forward direction.
    */
    void setInversed(bool bIsInversed);
  };
  typedef OdSmartPtr<OdGeodeticPathElement> OdGeodeticPathElementPtr;
  typedef OdArray<OdGeodeticPathElementPtr> OdGeodeticPathElementArray;
}

#endif //_ODSPATIALREFERENCE_ODGEODETICPATHELEMENT_INCLUDED_
