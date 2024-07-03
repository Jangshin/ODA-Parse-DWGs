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
#ifndef _ODSPATIALREFERENCE_ODELLIPSOIDDEFINITION_INCLUDED_
#define _ODSPATIALREFERENCE_ODELLIPSOIDDEFINITION_INCLUDED_

#include "OdDefinitionBase.h"

namespace OdSpatialReference
{
  class OdEllipsoidDefinition;
  typedef OdSmartPtr<OdEllipsoidDefinition> OdEllipsoidDefinitionPtr;
  typedef OdArray<OdEllipsoidDefinitionPtr> OdEllipsoidDefinitionArray;

  class OdEllipsoidDefinitionImpl;
  
  /** \details
    This class represents an ellipsoid definition.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdEllipsoidDefinition : public OdDefinitionBase
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdEllipsoidDefinition);
  public:
    /** \details
      Loads and returns coordinate reference system definition.

      \param sCode [in] Ellipsoid code.
      \param pEllipsoidDefinition [out] Pointer to an OdEllipsoidDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString& sCode, OdEllipsoidDefinitionPtr& pEllipsoidDefinition);

    /** \details
      Loads and returns all ellipsoid definitions.

      \param arrEllipsoidDefinition [out] Array of pointers to returned ellipsoid definitions.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult loadAll(OdEllipsoidDefinitionArray& arrEllipsoidDefinition);

    /** \details
      Minimum ellipsoid radius allowed.
    */
    TD_SPATIALREFERENCE_API_STATIC static const double kdMinEllipsoidRadius;

    /** \details
      Maximum ellipsoid radius allowed.
    */
    TD_SPATIALREFERENCE_API_STATIC static const double kdMaxEllipsoidRadius;

    /** \details
      Minimum ellipsoid flattening allowed.
    */
    TD_SPATIALREFERENCE_API_STATIC static const double kdMinEllipsoidFlat;
    
    /** \details
      Maximum ellipsoid flattening allowed.
    */
    TD_SPATIALREFERENCE_API_STATIC static const double kdMaxEllipsoidFlat;

    /** \details
      Checks ellipsoid radius for validity.

      \param dRadius [in] Equatorial radius.

      \returns true if radius is valid.
    */
    static bool isLegalRadius(double dRadius);
    
    /** \details
      Checks flattening ratio for validity.

      \param dEquatorial [in] Equatorial radius.
      \param dPolar [in] Polar radius.

      \returns true is valid.
    */
    static bool isLegalFlatteningRatio(double dEquatorial, double dPolar);

    /** \details
      Checks flattening ratio for validity.

      \param dFlat [in] Flattening ratio.

      \returns true is valid.
    */
    static bool isLegalFlatteningRatio(double dFlat);

    /** \details
      Calculates flattening ratio.

      \param dEquatorial [in] Equatorial radius.
      \param dPolar [in] Polar radius.

      \returns Flattening ratio.
    */
    static double flatteningRatio(double dEquatorial, double dPolar);

    /** \details
      Calculates flattening ratio.

      \param dEccentricity [in] Eccentricity.

      \returns Flattening ratio.
    */
    static double flatteningRatio(double dEccentricity);

    /** \details
      Calculates eccentricity.

      \param dFlat [in] Flattening ratio.

      \returns Eccentricity.
    */
    static double eccentricity(double dFlat);

    /** \details
      Returns the equatorial radius of this ellipsoid definition.

      \param dRadius [out] Equatorial radius.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEquatorialRadius(double& dRadius) const;

    /** \details
      Sets the equatorial radius of this ellipsoid definition.

      \param dRadius [in] Equatorial radius.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEquatorialRadius(double dRadius);

    /** \details
      Returns the polar radius of this ellipsoid definition.

      \param dRadius [out] Polar radius.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getPolarRadius(double& dRadius) const;

    /** \details
      Sets the polar radius of this ellipsoid definition.

      \param dRadius [in] Polar radius.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setPolarRadius(double dRadius);

    /** \details
      Returns the flattening ratio of this ellipsoid definition.

      \param dFlatteningRatio [out] Flattening ratio.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getFlatteningRatio(double& dFlatteningRatio) const;

    /** \details
      Returns the eccentricity of this ellipsoid definition.

      \param dEccentricity [out] Eccentricity.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEccentricity(double& dEccentricity) const;

    /** \details
      Returns great circle distance and azimuth between two coordinates.

      \param dLongitude1 [in] Longitude coordinate of first point.
      \param dLatitude1 [in] Latitude coordinate of first point.
      \param dLongitude2 [in] Longitude coordinate of second point.
      \param dLatitude2 [in] Latitude coordinate of second point.
      \param dDistance [out] Distance in meters.
      \param dAzimuth [out] Azimuth in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getGreatCircle(double dLongitude1, double dLatitude1, double dLongitude2, double dLatitude2, double& dDistance, double& dAzimuth) const;

    /** \details
      Returns the group string of this ellipsoid definition.

      \param sGroup [out] Group string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getGroup(OdString& sGroup) const;

    /** \details
      Sets the group string to this ellipsoid definition.

      \param sGroup [in] Group string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setGroup(const OdString& sGroup);

    /** \details
      Returns the EPSG number of this ellipsoid definition.

      \param nEpsgCode [out] EPSG number.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEpsgCode(OdInt16& nEpsgCode) const;

    /** \details
      Sets the EPSG number to this ellipsoid definition.

      \param nEpsgCode [in] EPSG number.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEpsgCode(OdInt16 nEpsgCode);

    /** \details
      Checks whether the specified code string is legal for ellipsoid definition.

      \param sCode [in] Ellipsoid definition code string.

      \returns true - if specified code string is valid.
    */
    static bool isLegalCode(const OdString& sCode);

    /** \details
      Checks whether the specified description string is legal for ellipsoid definition.

      \param sDescription [in] Ellipsoid definition description string.

      \returns true - if specified description string is valid.
    */
    static bool isLegalDescription(const OdString& sDescription);

    /** \details
      Checks whether the specified source string is legal for ellipsoid definition.

      \param sSource [in] Ellipsoid definition source string.

      \returns true - if specified source string is valid.
    */
    static bool isLegalSource(const OdString& sSource);

    /** \details
      Checks whether the specified group string is legal for ellipsoid definition.

      \param sGroup [in] Ellipsoid definition group string.

      \returns true - if specified group string is valid.
    */
    static bool isLegalGroup(const OdString& sGroup);
  };
}

#endif //_ODSPATIALREFERENCE_ODELLIPSOIDDEFINITION_INCLUDED_
