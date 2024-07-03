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
#ifndef _ODSPATIALREFERENCE_ODDATUMSHIFT_INCLUDED_
#define _ODSPATIALREFERENCE_ODDATUMSHIFT_INCLUDED_

#include "OdGeodeticTransformationDefinition.h"
#include "OdGeodeticPathDefinition.h"
#include "OdDatumDefinition.h"

namespace OdSpatialReference
{
  class OdDatumShift;
  typedef OdSmartPtr<OdDatumShift> OdDatumShiftPtr;

  class OdDatumShiftImpl;

  /** \details
    This class represents a datum shift.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdDatumShift : public OdRxObject
  {
    ODSPREF_RX_WITH_IMPL_DECLARE_MEMBERS(OdDatumShift);
  public:

    /** \details
      Create datum shift by source and target datum definitions.

      \param pDatumSource [in] pointer to source datum definition.
      \param pDatumTarget [in] pointer to target datum definition.
      \param pDatumShift [out] pointer to datum shift, result of loading.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdDatumDefinition* pDatumSource, const OdDatumDefinition* pDatumTarget, OdDatumShiftPtr& pDatumShift);

    /** \details
      Create datum shift by source and target datum names.

      \param strDatumSource [in] name to source datum.
      \param strDatumTarget [in] name to target datum definition.
      \param pDatumShift [out] pointer to datum shift, result of loading.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString& strDatumSource, const OdString& strDatumTarget, OdDatumShiftPtr& pDatumShift);

    /** \details
      Converts coordinate (longitude, latitude, height) using current datum shift.

      \param dLon [in/out] Longitude.
      \param dLat [in/out] Latitude.
      \param dHeight [in/out] Height.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult convert3D(double& dLon, double& dLat, double& dHeight) const;

    /** \details
      Converts coordinate (longitude, latitude) using current datum shift.

      \param dLon [in/out] Longitude.
      \param dLat [in/out] Latitude.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult convert(double& dLon, double& dLat) const;

    /** \details
      Returns the geodetic path definition of this datum shift.

      \param pGeodeticPathDefinition [out] Pointer to an OdGeodeticPathDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getPath(OdGeodeticPathDefinitionPtr& pGeodeticPathDefinition) const;

    /** \details
      Returns the geodetic transformation definition of this datum shift.

      \param uIndex [in] Index of geodetic transformation definition object.
      \param bIsInversed [out] If true - geodetic transformation definition object is used as inversed.
      \param pGeodeticTransformationDefinition [out] Pointer to an OdGeodeticTransformationDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getAt(OdUInt32 uIndex, bool& bIsInversed, OdGeodeticTransformationDefinitionPtr& pGeodeticTransformationDefinition) const;

    /** \details
      Returns the geodetic transformation definitions count of this datum shift.

      \param uCount [out] Count of geodetic transformation definitions.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCount(OdUInt32& uCount) const;

    /** \details
      Determines whether this datum shift has no transformations to be applied.

      \returns true if this datum shift object has no transformations to be applied.
    */
    bool isNullTransformation() const;

    /** \details
      Gets the datum shift object from geodetic transformation definition.

      \param pGeodeticTransformationDefinition [in] Pointer to an OdGeodeticTransformationDefinition object.
      \param bInverse [in] Direction of resulted datum shift: true - inversed, false - forward.
      \param pDatumShift [out] Pointer to an OdDatumShift object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult getDatumShift(const OdGeodeticTransformationDefinition * pGeodeticTransformationDefinition, bool bInverse, OdDatumShiftPtr & pDatumShift);
  };
}

#endif //_ODSPATIALREFERENCE_ODDATUMSHIFT_INCLUDED_
