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
#ifndef _ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMOPERATION_INCLUDED_
#define _ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMOPERATION_INCLUDED_

#include "OdCoordinateReferenceSystemDefinition.h"

namespace OdSpatialReference
{
  class OdCoordinateReferenceSystemDefinition;

  class OdCoordinateReferenceSystemOperation;
  typedef OdSmartPtr<OdCoordinateReferenceSystemOperation> OdCoordinateReferenceSystemOperationPtr;

  class OdCoordinateReferenceSystemOperationImpl;

  /** \details
    This class represents a coordinate reference system (CRS) operation.
    
    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdCoordinateReferenceSystemOperation : public OdRxObject
  {
    ODSPREF_RX_WITH_IMPL_DECLARE_MEMBERS(OdCoordinateReferenceSystemOperation);
  public:
    /** \details
      Loads and returns coordinate reference system operation.
    
      \param sCode [in] Coordinate system code.
      \param pCoordinateReferenceSystemOperation [out] Pointer to an OdCoordinateReferenceSystemOperation object.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString& sCode, OdCoordinateReferenceSystemOperationPtr& pCoordinateReferenceSystemOperation);

    /** \details
      Loads and returns coordinate reference system operation.

      \param pCoordinateReferenceSystemDefinition [in] Pointer to an OdCoordinateReferenceSystemDefinition object.
      \param pCoordinateReferenceSystemOperation [out] Pointer to an OdCoordinateReferenceSystemOperation object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdCoordinateReferenceSystemDefinition* pCoordinateReferenceSystemDefinition, OdCoordinateReferenceSystemOperationPtr& pCoordinateReferenceSystemOperation);

    /** \details
      Determines whether current coordinate reference system operation is geodetic.

      \param bIsGeodetic [out] True - if coordinate reference system operation is geodetic.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult isGeodetic(bool& bIsGeodetic) const;

    /** \details
      Converts coordinate (longitude, latitude, height) to (X, Y, Z).

      \param dX [in/out] Longitude - as input, X - as output.
      \param dY [in/out] Latitude - as input, Y - as output.
      \param dZ [in/out] Height - as input, Z - as output.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult convertFromLonLat(double& dX, double& dY, double& dZ) const;

    /** \details
      Converts coordinate (longitude, latitude) to (X, Y).

      \param dX [in/out] Longitude - as input, X - as output.
      \param dY [in/out] Latitude - as input, Y - as output.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult convertFromLonLat(double& dX, double& dY) const;

    /** \details
      Converts coordinate (X, Y, Z) to (longitude, latitude, height).

      \param dX [in/out] X - as input, Longitude - as output.
      \param dY [in/out] Y - as input, Latitude - as output.
      \param dZ [in/out] Z - as input, Height - as output.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult convertToLonLat(double& dX, double& dY, double& dZ) const;

    /** \details
      Converts coordinate (X, Y) to (longitude, latitude).

      \param dX [in/out] X - as input, Longitude - as output.
      \param dY [in/out] Y - as input, Latitude - as output.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult convertToLonLat(double& dX, double& dY) const;

    /** \details
      Computes the coordinate(X, Y) by given distance along a vector
      that is defined by starting coordinate(X, Y) and an azimuth (Angle with respect to North).

      \param dStartX [in] Start X coordinate.
      \param dStartY [in] Start Y coordinate.
      \param dAzimuth [in] Azimuth in degrees.
      \param dDistance [in] Distance in meters.
      \param dX [out] X coordinate.
      \param dY [out] Y coordinate.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCoordinate(double dStartX, double dStartY, double dAzimuth, double dDistance, double& dX, double& dY) const;
    
    /** \details
      Computes the convergence upon coordinate (longitude, latitude).
      
      \param dLongitude [in] Longitude.
      \param dLatitude [in] Latitude.
      \param dConvergence [out] The computed convergence angle at the specified point in degrees east of north.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getConvergence(double dLongitude, double dLatitude, double& dConvergence) const;

    /** \details
      Computes the scale upon coordinate (longitude, latitude).
      This function will compute the difference between true scale and grid scale at the indicated point returning
      the difference as yet another scale factor, i.e. a number close to one. Comparing this value to 1.0 will provide
      a reasonable means of determining one aspect of projection distortion at any given point on the map.
      This function will always return the most meaningful of the two values (K and H) depending upon the projections.

      \param dLongitude [in] Longitude.
      \param dLatitude [in] Latitude.
      \param dScale [out] Computed scale.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getScale(double dLongitude, double dLatitude, double& dScale) const;

    /** \details
      Computes the h-scale upon coordinate (longitude, latitude).
      This function will compute the difference between true scale and grid scale at the indicated point returning
      the difference as yet another scale factor, i.e. a number close to one. Comparing this value to 1.0 will provide
      a reasonable means of determining one aspect of projection distortion at any given point on the map.
      For non-conformal projections:
      the h scale factor measures the scale distortion of the projection along meridians.
      For conformal projection: h and k are essentially equal.
      For equal area projections: h = 1/k.
      For azimuthal projections:
      the k scale factor is a measure of distortion along lines normal to these radial lines.

      \param dLongitude [in] Longitude.
      \param dLatitude [in] Latitude.
      \param dScale [out] Computed h-scale.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getScaleH(double dLongitude, double dLatitude, double& dScale) const;

    /** \details
      Computes the k-scale upon coordinate (longitude, latitude).
      This function will compute the difference between true scale and grid scale at the indicated point returning
      the difference as yet another scale factor, i.e. a number close to one. Comparing this value to 1.0 will provide
      a reasonable means of determining one aspect of projection distortion at any given point on the map.
      For non-conformal projections:
      the k scale factor indicates the scale distortion of the projection as measured along parallels.
      For conformal projection: k and h are essentially equal.
      For equal area projections: k = 1/h.
      For azimuthal projections:
      the h scale factor is a measure of scale distortion along the radial lines from the origin of the projection.

      \param dLongitude [in] Longitude.
      \param dLatitude [in] Latitude.
      \param dScale [out] Computed k-scale.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getScaleK(double dLongitude, double dLatitude, double& dScale) const;

    /** \details
      Checks whether the coordinate(X, Y) within the useful range of this coordinate reference system operation.

      \param dX [in] X coordinate.
      \param dY [in] Y coordinate.
      \param bIsValidXY [out] True - if coordinate is valid.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult isValidXY(double dX, double dY, bool& bIsValidXY) const;

    /** \details
      Checks whether the coordinate(Longitude, Latitude) within the useful range of this coordinate reference system operation.

      \param dLongitude [in] Longitude.
      \param dLatitude [in] Latitude.
      \param bIsValidLonLat [out] True - if coordinate is valid.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult isValidLonLat(double dLongitude, double dLatitude, bool& bIsValidLonLat) const;

    /** \details
      Returns the great circle distance between two coordinates in coordinate system units.

      \param dX1 [in] X coordinate of first point.
      \param dY1 [in] Y coordinate of first point.
      \param dX2 [in] X coordinate of second point.
      \param dY2 [in] Y coordinate of second point.
      \param dDistance [out] Great circle distance in coordinate system units.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult measureGreatCircleDistance(double dX1, double dY1, double dX2, double dY2, double& dDistance) const;
    
    /** \details
      Returns the azimuth with respect to north of a vector formed by two coordinates.

      \param dX1 [in] X coordinate of first point.
      \param dY1 [in] Y coordinate of first point.
      \param dX2 [in] X coordinate of second point.
      \param dY2 [in] Y coordinate of second point.
      \param dAzimuth [out] Azimuth in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getAzimuth(double dX1, double dY1, double dX2, double dY2, double& dAzimuth) const;

    /** \details
      Sets the longtitude/latitude useful ranges for this coordinate reference system operation.
    
      \param dLonMin [in] Minumum longtitude in degrees.
      \param dLatMin [in] Minumum latitude in degrees.
      \param dLonMax [in] Maximum longtitude in degrees.
      \param dLatMax [in] Maximum latitude in degrees.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setLonLatBounds(double dLonMin, double dLatMin, double dLonMax, double dLatMax);

    /** \details
      Resets the longtitude/latitude useful ranges for this coordinate reference system operation.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult cancelLonLatBounds();

    /** \details
      Returns the absolute longtitude of the south western extent of the useful range
      of this coordinate reference system operation.

      \param dValue [out] Absolute longtitude of the south western extent in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLonMin(double& dValue) const;

    /** \details
      Returns the absolute longtitude of the north eastern extent of the useful range
      of this coordinate reference system operation.

      \param dValue [out] Absolute longtitude of the north eastern extent in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLonMax(double& dValue) const;

    /** \details
      Returns the absolute latitude of the south western extent of the useful range
      of this coordinate reference system operation.

      \param dValue [out] Absolute latitude of the south western extent in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLatMin(double& dValue) const;

    /** \details
      Returns the absolute latitude of the north eastern extent of the useful range
      of this coordinate reference system operation.

      \param dValue [out] Absolute latitude of the north eastern extent in degrees.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getLatMax(double& dValue) const;

    /** \details
      Sets the X/Y useful ranges for this coordinate reference system operation.
    
      \param dMinX [in] Minimum X of the range.
      \param dMinY [in] Minimum Y of the range.
      \param dMaxX [in] Maximum X of the range.
      \param dMaxY [in] Maximum Y of the range.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setXYBounds(double dMinX, double dMinY, double dMaxX, double dMaxY);
    
    /** \details
      Resets the X/Y useful ranges for this coordinate reference system operation.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult cancelXYBounds();

    /** \details
      Returns the minimum X of the useful range of this coordinate reference system operation.

      \param dValue [out] minimum X of the useful range.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMinX(double& dValue) const;

    /** \details
      Returns the maximum X of the useful range of this coordinate reference system operation.

      \param dValue [out] maximum X of the useful range.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMaxX(double& dValue) const;

    /** \details
      Returns the minimum Y of the useful range of this coordinate reference system operation.

      \param dValue [out] minimum Y of the useful range.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMinY(double& dValue) const;

    /** \details
      Returns the maximum Y of the useful range of this coordinate reference system operation.

      \param dValue [out] maximum Y of the useful range.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMaxY(double& dValue) const;

    /** \details
      Returns the unit scale factor of this coordinate reference system operation.
      It is required for conversion from coordinate system units to meters by multiplication.

      \param dUnitScale [out] Unit scale factor.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getUnitScale(double& dUnitScale) const;
  };
}

#endif //_ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMOPERATION_INCLUDED_
