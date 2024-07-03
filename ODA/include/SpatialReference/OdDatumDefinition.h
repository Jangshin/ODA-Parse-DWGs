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
#ifndef _ODSPATIALREFERENCE_ODDATUMDEFINITION_INCLUDED_
#define _ODSPATIALREFERENCE_ODDATUMDEFINITION_INCLUDED_

#include "OdEllipsoidDefinition.h"

namespace OdSpatialReference
{
  class OdDatumDefinition;
  typedef OdSmartPtr<OdDatumDefinition> OdDatumDefinitionPtr;
  typedef OdArray<OdDatumDefinitionPtr> OdDatumDefinitionArray;

  class OdDatumDefinitionImpl;
  
  /** \details
    This class represents a datum definition.
    
    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdDatumDefinition : public OdDefinitionBase
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdDatumDefinition);
  public:
    /** \details
      Loads and returns coordinate reference system definition.
    
      \param sCode [in] Datum definition code.
      \param pDatumDefinition [out] Pointer to an OdDatumDefinition object.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString & sCode, OdDatumDefinitionPtr & pDatumDefinition);
    
    /** \details
      Loads and returns all datum definitions.
    
      \param arrDatumDefinition [out] Array of pointers to returned datum definitions.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult loadAll(OdDatumDefinitionArray& arrDatumDefinition);

    /** \details
      Returns the ellipsoid code of this datum definition.

      \param sEllipsoid [out] Ellipsoid code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEllipsoid(OdString& sEllipsoid) const;

    /** \details
      Sets the ellipsoid to this datum definition.

      \param sEllipsoid [in] Ellipsoid code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEllipsoid(const OdString& sEllipsoid);

    /** \details
      Returns the ellipsoid definition of this datum definition.

      \param pEllipsoid [out] Pointer to an OdEllipsoidDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEllipsoidDefinition(OdEllipsoidDefinitionPtr & pEllipsoid) const;

    /** \details
      Sets the ellipsoid to this datum definition.

      \param pEllipsoid [in] Pointer to an OdEllipsoidDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEllipsoidDefinition(const OdEllipsoidDefinition * pEllipsoid);

    /** \details
      Returns the group string of this datum definition.

      \param sGroup [out] Group string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getGroup(OdString& sGroup) const;

    /** \details
      Sets the group string to this datum definition.

      \param sGroup [in] Group string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setGroup(const OdString& sGroup);

    /** \details
      Returns the location string of this datum definition.

      \param sLocation [out] Location code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLocation(OdString& sLocation) const;

    /** \details
      Sets the location string to this datum definition.

      \param sLocation [in] Location string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setLocation(const OdString& sLocation);

    /** \details
      Returns the country or state string of this datum definition.

      \param sCountryOrState [out] Country or state string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCountryOrState(OdString& sCountryOrState) const;

    /** \details
      Sets the country or state string to this datum definition.

      \param sCountryOrState [in] Country or state string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setCountryOrState(const OdString& sCountryOrState);

    /** \details
      Returns the EPSG number of this datum definition.

      \param nEpsgCode [out] EPSG number.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEpsgCode(OdInt16& nEpsgCode) const;

    /** \details
      Sets the EPSG number to this datum definition.

      \param nEpsgCode [in] EPSG number.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEpsgCode(OdInt16 nEpsgCode);

    /** \details
     Returns the datum calculation technique to convert from this datum to WGS84.

     \param uDatumCalcTech [out] datum calculation technique.

     \returns Returns eOK if successful, or an appropriate error code if not.
   */
    OdResult getDatumCalculationTechnique(DatumCalculationTechnique& uDatumCalcTech) const;

    /** \details
      Sets the datum calculation technique to convert from this datum to WGS84.

      \param DatumCalculationTechnique [in] datum calculation technique.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setDatumCalculationTechnique(const DatumCalculationTechnique& uDatumCalcTech);

    /** \details
     Returns components of the vector from the WGS-84 geocenter to the geocenter of this datum.

     \param dXOffset [out] x-component of the vector.
     \param dYOffset [out] y-component of the vector.
     \param dZOffset [out] z-component of the vector.

     \returns Returns eOK if successful, or an appropriate error code if not.
   */
    OdResult getOffset( double& dXOffset, double& dYOffset, double& dZOffset ) const;

    /** \details
      Sets components of the vector from the WGS-84 geocenter to the geocenter of this datum.

      \param dXOffset [in] x-component of the vector.
      \param dYOffset [in] y-component of the vector.
      \param dZOffset [in] z-component of the vector.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setOffset(double dXOffset, double dYOffset, double dZOffset);

    /** \details
     Returns scale factor in parts per million of this datum.

     \param dBWScale [out] scale factor.

     \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getScale(double& dBWScale) const;

    /** \details
      Sets scale factor in parts per million of this datum.

      \param dBWScale [in] scale factor.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setScale(double dBWScale);

    /** \details
     Returns angles from WGS-84 X, Y and Z axis to local geodetic system X, Y and Z axis in arc seconds.

     \param dXRot [out] Angle from WGS-84 X axis to local geodetic system X axis in arc seconds, east is positive.
     \param dYRot [out] Angle from WGS-84 Y axis to local geodetic system Y axis in arc seconds, north is positive.
     \param dZRot [out] Angle from WGS-84 Z axis to local geodetic system Z axis in arc seconds, use right hand rule.

     \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getRotationAngles(double& dXRot, double& dYRot, double& dZRot) const;

    /** \details
      Sets angles from WGS-84 X, Y and Z axis to local geodetic system X, Y and Z axis in arc seconds.

      \param dXRot [in] Angle from WGS-84 X axis to local geodetic system X axis in arc seconds, east is positive.
      \param dYRot [in] Angle from WGS-84 Y axis to local geodetic system Y axis in arc seconds, north is positive.
      \param dZRot [in] Angle from WGS-84 Z axis to local geodetic system Z axis in arc seconds, use right hand rule.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setRotationAngles(double dXRot, double dYRot, double dZRot);

    /** \details
      Checks whether the specified code string is legal for datum definition.

      \param sCode [in] Datum definition code string.

      \returns true - if specified code string is valid.
    */
    static bool isLegalCode(const OdString& sCode);

    /** \details
      Checks whether the specified description string is legal for datum definition.

      \param sDescription [in] Datum definition description string.

      \returns true - if specified description string is valid.
    */
    static bool isLegalDescription(const OdString& sDescription);

    /** \details
      Checks whether the specified source string is legal for datum definition.

      \param sSource [in] Datum definition source string.

      \returns true - if specified source string is valid.
    */
    static bool isLegalSource(const OdString& sSource);

    /** \details
      Checks whether the specified group string is legal for datum definition.

      \param sGroup [in] Datum definition group string.

      \returns true - if specified group string is valid.
    */
    static bool isLegalGroup(const OdString& sGroup);

    /** \details
      Checks whether the specified location string is legal for datum definition.

      \param sLocation [in] Datum definition location string.

      \returns true - if specified location string is valid.
    */
    static bool isLegalLocation(const OdString& sLocation);

    /** \details
      Checks whether the specified country or state string is legal for datum definition.

      \param sCountryOrState [in] Datum definition country or state string.

      \returns true - if specified country or state string is valid.
    */
    static bool isLegalCountryOrState(const OdString& sCountryOrState);
  };
}

#endif //_ODSPATIALREFERENCE_ODDATUMDEFINITION_INCLUDED_
