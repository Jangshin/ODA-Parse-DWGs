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
#ifndef _ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMDEFINITION_INCLUDED_
#define _ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMDEFINITION_INCLUDED_

#include "OdEllipsoidDefinition.h"
#include "OdDatumDefinition.h"

namespace OdSpatialReference
{
  class OdCoordinateReferenceSystemDefinition;
  typedef OdSmartPtr<OdCoordinateReferenceSystemDefinition> OdCoordinateReferenceSystemDefinitionPtr;
  typedef OdArray<OdCoordinateReferenceSystemDefinitionPtr> OdCoordinateReferenceSystemDefinitionArray;

  class OdCoordinateReferenceSystemDefinitionImpl;
  
  /** \details
    This class represents a coordinate reference system (CRS) definition.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdCoordinateReferenceSystemDefinition : public OdDefinitionBase
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdCoordinateReferenceSystemDefinition);
  public:
    /** \details
      Loads and returns coordinate reference system definition.

      \param sCode [in] Coordinate system code.
      \param pCoordinateReferenceSystemDefinition [out] Pointer to an OdCoordinateReferenceSystemDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString& sCode, OdCoordinateReferenceSystemDefinitionPtr& pCoordinateReferenceSystemDefinition);

    /** \details
      Loads and returns all coordinate reference system definitions.

      \param arrCRSD [out] Array of pointers to returned coordinate reference system definitions.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult loadAll(OdCoordinateReferenceSystemDefinitionArray& arrCRSD);

    /** \details
      Returns this coordinate reference system definition type.
      
      \param eType [out] coordinate reference system definition type.
      
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getType(CoordinateReferenceSystemType& eType) const;
    
    /** \details
      Returns this coordinate reference system definition projection code.

      \param eProjectionCode [out] Projection code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getProjectionCode(ProjectionCode& eProjectionCode) const;
    
    /** \details
      Sets the projection code to this coordinate reference system definition.

      \param eProjectionCode [in] Projection code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setProjectionCode(ProjectionCode eProjectionCode);

    /** \details
      Returns the projection parameters ñount of this coordinate reference system definition.

      \param uCount [out] Count of projection parameters.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getProjectionParameterCount(OdUInt32 & uCount) const;

    /** \details
      Returns the projection parameter value of this coordinate reference system definition.

      \param uIndex [in] Parameter index.
      \param dParameter [out] Parameter value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getProjectionParameter(OdUInt32 uIndex, double & dParameter) const;

    /** \details
      Sets the projection parameter value to this coordinate reference system definition.

      \param uIndex [in] Parameter index.
      \param dParameter [in] Parameter value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setProjectionParameter(OdUInt32 uIndex, double dParameter);

    /** \details
      Returns the origin longtitude of this coordinate reference system definition.
      
      \param dValue [out] Origin longitude in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getOriginLongitude(double & dValue) const;

    /** \details
      Sets the origin longtitude to this coordinate reference system definition.
      
      \param dValue [in] Origin longitude in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setOriginLongitude(double dValue);

    /** \details
      Returns the origin latitude from this coordinate reference system definition.

      \param dValue [out] Origin latitude in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getOriginLatitude(double& dValue) const;

    /** \details
      Sets the origin latitude to this coordinate reference system definition.

      \param dValue [in] Origin latitude in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setOriginLatitude(double dValue);

    /** \details
      Returns the false easting of this coordinate reference system definition to be applied to keep X coordinates positive.

      \param dValue [out] False easting in the units of the resulting coordinates.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getOffsetX(double& dValue) const;

    /** \details
      Sets the false easting of this coordinate reference system definition to be applied to keep X coordinates positive.

      \param dValue [in] False easting in the units of the resulting coordinates.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setOffsetX(double dValue);

    /** \details
      Returns the false northing of this coordinate reference system definition to be applied to keep Y coordinates positive.

      \param dValue [out] False northing in the units of the resulting coordinates.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getOffsetY(double& dValue) const;

    /** \details
      Sets the false northing of this coordinate reference system definition to be applied to keep Y coordinates positive.

      \param dValue [in] False northing in the units of the resulting coordinates.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setOffsetY(double dValue);

    /** \details
      Returns the scale reduction (which is used on some projections to distribute the distortion uniformly across the map)
      of this coordinate reference system definition.

      \param dValue [out] Scale reduction.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getScaleReduction(double & dValue) const;

    /** \details
      Sets the scale reduction (which is used on some projections to distribute the distortion uniformly across the map)
      to this coordinate reference system definition.

      \param dValue [in] Scale reduction.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setScaleReduction(double dValue);

    /** \details
      Returns the unit code of this coordinate reference system definition.

      \param eUnitCode [out] Unit code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getUnitCode(UnitCode& eUnitCode) const;

    /** \details
      Sets the unit code to this coordinate reference system definition.

      \param eUnitCode [in] Unit code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setUnitCode(UnitCode eUnitCode);

    /** \details
      Returns the quadrant of the cartesian coordinates of this coordinate reference system definition.
      Quadrant is used to handle coordinate systems in which X increases to the left, etc.

      \param nQuadrant [out] Quadrant of the cartesian coordinates.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getQuadrant(OdInt16& nQuadrant) const;

    /** \details
      Sets the quadrant of the cartesian coordinates to this coordinate reference system definition.
      Quadrant is used to handle coordinate systems in which X increases to the left, etc.

      \param nQuadrant [in] Quadrant of the cartesian coordinates, allowed value in ranges [-1;-4], [1;4].

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setQuadrant(OdInt16 nQuadrant);

    /** \details
      Returns the datum code of this coordinate reference system definition.
      
      \param sDatum [out] Datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getDatum(OdString& sDatum) const;

    /** \details
      Sets the datum to this coordinate reference system definition.

      \param sDatum [in] Datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setDatum(const OdString& sDatum);

    /** \details
      Returns the datum definition of this coordinate reference system definition.

      \param pDatum [out] Pointer to an OdDatumDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getDatumDefinition(OdDatumDefinitionPtr& pDatum) const;

    /** \details
      Sets the datum to this coordinate reference system definition.

      \param pDatum [in] Pointer to an OdDatumDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setDatumDefinition(const OdDatumDefinition* pDatum);

    /** \details
      Returns the ellipsoid code of this coordinate reference system definition.

      \param sEllipsoid [out] Ellipsoid code.
      \param bFromDatum [in] If there is no ellipsoid and bFromDatum is true - try to get ellipsoid code from datum.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEllipsoid(OdString& sEllipsoid, bool bFromDatum = false) const;

    /** \details
      Sets the ellipsoid to this coordinate reference system definition.

      \param sEllipsoid [in] Ellipsoid code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEllipsoid(const OdString& sEllipsoid);

    /** \details
      Returns the ellipsoid definition of this coordinate reference system definition.

      \param pEllipsoid [out] Pointer to an OdEllipsoidDefinition object.
      \param bFromDatum [in] If there is no ellipsoid and bFromDatum is true - try to get ellipsoid definition from datum.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEllipsoidDefinition(OdEllipsoidDefinitionPtr& pEllipsoid, bool bFromDatum = false) const;

    /** \details
      Sets the ellipsoid to this coordinate reference system definition.

      \param pEllipsoid [in] Pointer to an OdEllipsoidDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEllipsoidDefinition(const OdEllipsoidDefinition* pEllipsoid);

    /** \details
      Sets the longtitude/latitude ranges for this coordinate reference system definition.

      \param dLonMin [in] Minumum longtitude in degrees.
      \param dLatMin [in] Minumum latitude in degrees.
      \param dLonMax [in] Maximum longtitude in degrees.
      \param dLatMax [in] Maximum latitude in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setLonLatBounds(double dLonMin, double dLatMin, double dLonMax, double dLatMax);

    /** \details
      Resets the longtitude/latitude ranges for this coordinate reference system definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult cancelLonLatBounds();

    /** \details
      Returns the minumum longtitude of the range of this coordinate reference system definition.
    
      \param dValue [out] Minumum longtitude in degrees.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLonMin(double& dValue) const;

    /** \details
      Returns the maximum longtitude of the range of this coordinate reference system definition.

      \param dValue [out] Maximum longtitude in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLonMax(double& dValue) const;

    /** \details
      Returns the minumum latitude of the range of this coordinate reference system definition.

      \param dValue [out] Minumum latitude in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLatMin(double& dValue) const;

    /** \details
      Returns the maximum latitude of the range of this coordinate reference system definition.

      \param dValue [out] Maximum latitude in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLatMax(double& dValue) const;

    /** \details
      Sets the X/Y ranges for this coordinate reference system definition.

      \param dMinX [in] Minimum X of the range.
      \param dMinY [in] Minimum Y of the range.
      \param dMaxX [in] Maximum X of the range.
      \param dMaxY [in] Maximum Y of the range.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setXYBounds(double dMinX, double dMinY, double dMaxX, double dMaxY);

    /** \details
      Resets the X/Y ranges for this coordinate reference system definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult cancelXYBounds();

    /** \details
      Returns the minimum X of the range of this coordinate reference system definition.
    
      \param dValue [out] minimum X of the range.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMinX(double& dValue) const;

    /** \details
      Returns the maximum X of the range of this coordinate reference system definition.

      \param dValue [out] maximum X of the range.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMaxX(double& dValue) const;

    /** \details
      Returns the minimum Y of the range of this coordinate reference system definition.

      \param dValue [out] minimum Y of the range.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMinY(double& dValue) const;

    /** \details
      Returns the maximum Y of the range of this coordinate reference system definition.

      \param dValue [out] maximum Y of the range.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMaxY(double& dValue) const;

    /** \details
      Returns the EPSG number of this coordinate reference system definition.

      \param nEpsgCode [out] EPSG number.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEpsgCode(OdInt32& nEpsgCode) const;

    /** \details
      Returns the Oracle SRID number of this coordinate reference system definition.

      \param nSridCode [out] Oracle SRID number.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getSridCode(OdInt32& nSridCode) const;

    /** \details
      Returns the projection code of this coordinate reference system definition.

      \param sProjection [out] Projection code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getProjection(OdString& sProjection) const;

    /** \details
      Sets the projection to this coordinate reference system definition.

      \param sProjection [in] Projection code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setProjection(const OdString& sProjection);

    /** \details
      Returns the unit code of this coordinate reference system definition.

      \param sUnits [out] Unit code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getUnits(OdString& sUnits) const;

    /** \details
      Returns the unit scale factor of this coordinate reference system definition.
      It is required for conversion from coordinate system units to meters by multiplication. 

      \param dUnitScale [out] Unit scale factor.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getUnitScale(double& dUnitScale) const;

    /** \details
      Returns the map scale factor of this coordinate reference system definition.
      It is required to get to the desired map scale by division.

      \param dMapScale [out] Map scale factor.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMapScale(double& dMapScale) const;

    /** \details
      Sets the map scale factor to this coordinate reference system definition.
      It is required to get to the desired map scale by division.

      \param dMapScale [in] Map scale factor.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setMapScale(double dMapScale);

    /** \details
      Returns the absolute X value of this coordinate reference system definition.

      \param dValue [out] absolute X value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getZeroX(double& dValue) const;

    /** \details
      Returns the absolute Y value of this coordinate reference system definition.

      \param dValue [out] absolute Y value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getZeroY(double& dValue) const;

    /** \details
      Sets the absolute X and Y values of this coordinate reference system definition.

      \param dXZero [in] absolute X value.
      \param dYZero [in] absolute Y value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setZeroes(double dXZero, double dYZero);

    /** \details
      Returns the group string of this coordinate reference system definition.

      \param sGroup [out] Group string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getGroup(OdString& sGroup) const;

    /** \details
      Sets the group string to this coordinate reference system definition.

      \param sGroup [in] Group string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setGroup(const OdString& sGroup);

    /** \details
      Returns the location string of this coordinate reference system definition.

      \param sLocation [out] Location code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLocation(OdString& sLocation) const;

    /** \details
      Sets the location string to this coordinate reference system definition.

      \param sLocation [in] Location string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setLocation(const OdString& sLocation);

    /** \details
      Returns the country or state string of this coordinate reference system definition.

      \param sCountryOrState [out] Country or state string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCountryOrState(OdString& sCountryOrState) const;

    /** \details
      Sets the country or state string to this coordinate reference system definition.

      \param sCountryOrState [in] Country or state string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setCountryOrState(const OdString& sCountryOrState);

    /** \details
      Checks whether the specified code string is legal for coordinate reference system definition.

      \param sCode [in] Coordinate reference system definition code string.

      \returns true - if specified code string is valid.
    */
    static bool isLegalCode(const OdString& sCode);

    /** \details
      Checks whether the specified description string is legal for coordinate reference system definition.

      \param sDescription [in] Coordinate reference system definition description string.

      \returns true - if specified description string is valid.
    */
    static bool isLegalDescription(const OdString& sDescription);

    /** \details
      Checks whether the specified source string is legal for coordinate reference system definition.

      \param sSource [in] Coordinate reference system definition source string.

      \returns true - if specified source string is valid.
    */
    static bool isLegalSource(const OdString& sSource);

    /** \details
      Checks whether the specified group string is legal for coordinate reference system definition.

      \param sGroup [in] Coordinate reference system definition group string.

      \returns true - if specified group string is valid.
    */
    static bool isLegalGroup(const OdString& sGroup);

    /** \details
      Checks whether the specified location string is legal for coordinate reference system definition.

      \param sLocation [in] Coordinate reference system definition location string.

      \returns true - if specified location string is valid.
    */
    static bool isLegalLocation(const OdString& sLocation);

    /** \details
      Checks whether the specified country or state string is legal for coordinate reference system definition.

      \param sCountryOrState [in] Coordinate reference system definition country or state string.

      \returns true - if specified country or state string is valid.
    */
    static bool isLegalCountryOrState(const OdString& sCountryOrState);

    /** \details
      Checks whether the specified projection string is legal for coordinate reference system definition.

      \param sProjection [in] Coordinate reference system definition projection string.

      \returns true - if specified projection string is valid.
    */
    static bool isLegalProjection(const OdString& sProjection);
  };
}

#endif //_ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMDEFINITION_INCLUDED_
