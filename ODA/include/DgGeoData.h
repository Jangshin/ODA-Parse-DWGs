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
#ifndef __DG_GEODATA_H__
#define __DG_GEODATA_H__

#include "DgApplicationData.h"
#include "DgElementIterator.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GeExtents2d.h"
#include <map>
#include "DgModel.h"
#include "Gi/GiRasterImage.h"

class OdDgKMLPlacemark2d;
class OdDgKMLPlacemark3d;

typedef OdSmartPtr<OdDgKMLPlacemark2d> OdDgKMLPlacemark2dPtr;
typedef OdSmartPtr<OdDgKMLPlacemark3d> OdDgKMLPlacemark3dPtr;

//=============================================================================
/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataReprojectionSettings
{
public:
  enum OdDgGeoDataReprojectionValue
  {
    kNever = 0,
    kAlways = 1,
    kIfSpatiallyLarge = 2
  };

public:
  OdDgGeoDataReprojectionSettings();

public:
  double                        m_dStrokeTolerance;
  double                        m_dSpatiallyLargeDistance;
  OdDgGeoDataReprojectionValue  m_uReprojectCellComponents;
  OdDgGeoDataReprojectionValue  m_uReprojectMTextComponents;
  bool                          m_bRotateCells;
  bool                          m_bScaleCells;
  bool                          m_bRotateTexts;
  bool                          m_bScaleTexts;
  bool                          m_bReprojectTerrainElementPoints;
  bool                          m_bReprojectMeshPoints;
  bool                          m_bReprojectBSplineSurfacePoints;
  OdDgGeoDataReprojectionValue  m_uStrokeArcsToLineStrings;
  OdDgGeoDataReprojectionValue  m_uStrokeEllipsesToLineStrings;
  OdDgGeoDataReprojectionValue  m_uStrokeCurvesToLineStrings;
  bool                          m_bReprojectEllevations;
  bool                          m_bAddPointsIfNeeded;
};

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataCoordinateSystemParam
{
  public:
    enum OdDgGeoDataCoordinateSystemParamDataType
    {
      kTypeDouble        = 0,
      kTypeInt32         = 1,
      kTypeDoubleArray24 = 2
    };

    enum OdDgDataCoordinateSystemParamType
    {
      kParamNotUsed                     = 0,
      kParamCentralMeredian             = 1,
      kParamNorthernStdParallel         = 2,
      kParamSouthernStdParallel         = 3,
      kParamStandardParallel            = 4,
      kParamFirstPointLongitude         = 5,
      kParamFirstPointLatitude          = 6,
      kParamSecondPointLongitude        = 7,
      kParamSecondPointLatitude         = 8,
      kParamPointLongitude              = 9,
      kParamPointLatitude               = 10,
      kParamAzimuth                     = 11,
      kParamYAxisAzimuth                = 12,
      kParamEasternStandardMeridian     = 13,
      kParamNorthernParallel            = 14,
      kParamSouthernParallel            = 15,
      kParamFirstPoleLongitude          = 16,
      kParamFirstPoleLatitude           = 17,
      kParamSecondPoleLongitude         = 18,
      kParamSecondPoleLatitude          = 19,
      kParamDistanceBetweenPoles        = 20,
      kParamDistanceToFirstStdParallel  = 21,
      kParamDistanceToSecondStdParallel = 22,
      kParamCplxParamA                  = 23,
      kParamCplxParamB                  = 24,
      kParamWesternEndOfLongitudeRange  = 25,
      kParamEasternEndOfLongitudeRange  = 26,
      kParamUTMZoneNumber               = 27,
      kParamNorthSouthHemisphere        = 28,
      kParamAverageGeoidHeight          = 29,
      kParamAverageElevation            = 30,
      kParamObliquePoleLongitude        = 31,
      kParamObliquePoleLatitude         = 32,
      kParamObliqueConeStandardParallel = 33,
      kParamStandardCircleLatitude      = 34,
      kParamAffineTransformA0           = 35,
      kParamAffineTransformB0           = 36,
      kParamAffineTransformA1           = 37,
      kParamAffineTransformA2           = 38,
      kParamAffineTransformB1           = 39,
      kParamAffineTransformB2           = 40,
      kParamNormalParallel              = 41,
      kParamDanishSystem24Region        = 42,
      kParamRectifiedSkewOrthomorphic   = 43,
      kParamXCoordOrigin                = 44,
      kParamYCoordOrigin                = 45,
      kParamScaleFactor                 = 46,
      kParamRotationAngle               = 47,
      kParamEllipsoidScale              = 48,
      kParamFalseEasting                = 101,
      kParamFalseNorthing               = 102,
      kParamOriginLongitude             = 103,
      kParamOriginLatitude              = 104,
      kParamScaleReduction              = 105
    };

    enum OdDgGeoDataCoordSystemQuadrantValue
    {
      kUndefined  = 0,
      kPositiveXY = 1,
      kNegativeXPositiveY = 2,
      kNegativeXY = 3,
      kPositiveXNegativeY = 4,
      kPositiveXYInv = -1,
      kNegativeXPositiveYInv = -2,
      kNegativeXYInv = -3,
      kPositiveXNegativeYInv = -4
    };

    enum OdDgGeoDataCoordSystemHemisphereValue
    {
      kNorthen = 0,
      kSouthen = 1
    };

  public:
    OdDgGeoDataCoordinateSystemParam();
    OdDgGeoDataCoordinateSystemParam(const OdDgDataCoordinateSystemParamType& uType, OdInt32 iValue);
    OdDgGeoDataCoordinateSystemParam(const OdDgDataCoordinateSystemParamType& uType, double  dValue);
    OdDgGeoDataCoordinateSystemParam(const OdDgDataCoordinateSystemParamType& uType, const double arrDblValues[24] );

    void set(const OdDgDataCoordinateSystemParamType& uType, OdInt32 iValue);
    void set(const OdDgDataCoordinateSystemParamType& uType, double  dValue);
    void set(const OdDgDataCoordinateSystemParamType& uType, const double arrDblValues[24] );

    ~OdDgGeoDataCoordinateSystemParam();

    OdDgGeoDataCoordinateSystemParamDataType getDataType() const;
    OdDgDataCoordinateSystemParamType        getType() const;

    OdInt32         getIntegerValue() const;
    double          getDoubleValue() const;
    OdArray<double> getDoubleArrayValue() const;

    OdResult setValue(OdInt32 iValue);
    OdResult setValue(double  dValue);
    OdResult setValue(const double arrDblValues[24]);

    static  OdString getParamTypeString(const OdDgDataCoordinateSystemParamType& uType);

  private:
    OdDgDataCoordinateSystemParamType        m_uType;
    OdDgGeoDataCoordinateSystemParamDataType m_uDataType;
    double                                   m_dValue;
    OdInt32                                  m_iValue;
    OdArray<double>                          m_arrDblValue;
};

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataCoordinateSystemParamArray
{
  public:
    OdDgGeoDataCoordinateSystemParamArray();
    virtual ~OdDgGeoDataCoordinateSystemParamArray();

    OdUInt32 getParamCount() const;
    OdDgGeoDataCoordinateSystemParam getParam(OdUInt32 uIndex) const;
    bool getParam(const OdDgGeoDataCoordinateSystemParam::OdDgDataCoordinateSystemParamType& uParam, OdDgGeoDataCoordinateSystemParam& param) const;
    void setParam(const OdDgGeoDataCoordinateSystemParam& param);
    bool deleteParam(OdUInt32 uIndex);
    bool deleteParam(const OdDgGeoDataCoordinateSystemParam::OdDgDataCoordinateSystemParamType& uParam);
    void clear();

  private:
    std::map<OdDgGeoDataCoordinateSystemParam::OdDgDataCoordinateSystemParamType, OdDgGeoDataCoordinateSystemParam> m_mapParams;
};

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataCoordinateSystemCSMapsData
{
public:
  OdDgGeoDataCoordinateSystemCSMapsData();

public:
  double   m_dOrgLatitude;
  double   m_dOrgLongitude;
  double   m_dScaleReduction;
  double   m_dFalseEasting;
  double   m_dFalseNorthing;
  OdUInt32 m_uRegion;
  OdInt16  m_iQuadrant;
  OdInt32  m_iHemisphere;
  double   m_dParams[24];
};

//=============================================================================

class OdDgGeoDataCoordinateSystem;
typedef OdSmartPtr<OdDgGeoDataCoordinateSystem> OdDgGeoDataCoordinateSystemPtr;

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataCoordinateSystem : public OdRxObject
{
public:
  enum OdDgGeoDataCoordSystemProjectionType
  {
    kUndefined                      = 0   , // No projection type
    kGeographic                     = 1   , // Geographic (Latitude/Longitude).
    kTransverseMercator             = 3   , // Transverse Mercator.
    kAlbersEqualAreaConic           = 4   , // Albers' Equal Area Conic.                      
    kMercator                       = 6   , // Mercator.
    kLambertAzimuthalEquidistant    = 7   , // Lambert Azimuthal Equidistant.
    kLambertTangential              = 8   , // Lambert Tangential.
    kPolyconic                      = 9   , // Polyconic.
    kPolyconicMod                   = 10  , // Lallemand IMW Modified Polyconic.
    kAzimuthalEqualArea             = 11  , // Azimuthal Equal Area.      
    kEquidistantConic               = 12  , // Equidistant Conic.
    kMiller                         = 13  , // Miller.
    kStereographicMod               = 15  , // Modified Stereographic.
    kNewZealand                     = 16  , // New Zealand.
    kSinusoidal                     = 17  , // Sinusoidal.
    kOrthographic                   = 18  , // Orthographic projection.                   
    kGnomonic                       = 19  , // Gnomonic.                                  
    kEquidistantCylindrical         = 20  , // Equidistant Cylindrical. (Spherical only)
    kVanDerGrinten                  = 21  , // Van Der Grinten.
    kCassini                        = 22  , // Cassini.      
    kRobinson                       = 23  , // Robinson.      
    kBonne                          = 24  , // Bonne.
    kEckert4                        = 25  , // Eckert 4.
    kEckert6                        = 26  , // Eckert 6.
    kMollweide                      = 27  , // Mollweide.
    kGoodeHomolosine                = 28  , // Goode Homolosine.
    kEqualAreaCylindricalNA         = 29  , // Equal-area Cylindrical. Normal Aspect.    
    kEqualAreaCylindricalTA         = 30  , // Equal Area Cylindrical. Transverse Aspect. 
    kBipolarObliqueConformalConic   = 31  , // Bipolar Oblique Conformal Conic.           
    kSwissObliqueCylindrical        = 32  , // Swiss Oblique Cylindrical.
    kPolarStereographic             = 33  , // Polar Stereographic.
    kObliqueStereographic           = 34  , // Oblique Stereographic.
    kSnyderObliqueStereographic     = 35  , // Snyder's Oblique Stereographic.           
    kLambertConformalConic1StdLat   = 36  , // Lambert Conformal Conic 1 Standard Latitude.
    kLambertConformalConic          = 37  , // Lambert Conformal Conic.
    kLambertConformalConicBelgian   = 38  , // Belgian Variation of the Lambert Conformal Conic.
    kLambertConformalConicWCCS      = 39  , // Lambert Conformal Conic. Wisconsin County Coordinate System Variation.
    kTransverseMercatorWCCS         = 40  , // Transverse Mercator. Wisconsin County Coordinate System Variation.
    kLambertConformalConicM         = 41  , // Lambert Conformal Conic. Minnesota DOT Variation.
    kTransverseMercatorM            = 42  , // Transverse Mercator. Minnesota DOT Variation.
    kTransverseMercatorRSA          = 43  , // South Orientated Transverse Mercator (RSA).
    kUniversalTransverseMercator    = 44  , // Universe Transverce Mercator.
    kTransverseMercatorSnyder       = 45  , // Transverse Mercator per J. P. Snyder.
    kGaussKruger                    = 46  , // Gauss-Kruger.
    kKrovak                         = 47  , // Krovak (precise origin).
    kMercatorSR                     = 49  , // Mercator with scale reduction.
    kObliqueConformalConic          = 50  , // Oblique conformal conic.
    kKrovak95                       = 51  , // Krovak includes 1995 adjustment.
    kPolarStereographicSL           = 53  , // Polar Stereographic with standard latitude.
    kTransverseMercatorAffine       = 54  , // Transverse Mercator projection with affine post-processor.
    kNonEarth                       = 55  , // Non-Earth.
    kObliqueCylindrical             = 56  , // Oblique Cylindrical.
    kDanishSystemNoKMS              = 57  , // Danish System 1934/1945 (Non-KMS).
    kTransverseMercatorOSTN97       = 58  , // Transverse Mercator with the OSTN97 grid shift tacked on.
    kAzimuthalEquidistant           = 59  , // Azimuthal equidistant (elevated ellipsoid).     
    kTransverseMercatorOSTN02       = 60  , // Transverse Mercator projection with the OSTN02 grid shift tacked on.
    kDanishSystemKMS1999            = 61  , // Danish System 1934/1945 (KMS 1999 Polynomials).
    kTransverseMercatorKF           = 62  , // Transverse Mercator Kruger Formulation.      
    kWinkelTripel                   = 63  , // Winkel-Tripel.
    kNerthSR                        = 64  , // Non-Earth with Scale and Rotation.
    kLambertConformalConicAffine    = 65  , // Lambert Conformal Conic with Affine post-processor.
    kDanishSystemKMS2001            = 66  , // Danish System 1934/1945 (KMS 2001 Polynomials).
    kEquidistantCylindricalE        = 67  , // Equidistant Cylindrical, Ellipsoidal or Spherical.
    kPlateCarree                    = 68  , // Plate Carré.
    kPseudoMercator                 = 69  , // Popular Visualisation Pseudo Mercator (Google Earth).
    kLambertConformalConicMichigan  = 70  , // Lambert Conformal Conic Michigan variation.
    kUniversalTransverseMercatorBF  = 490 , // Universal Transverse Mercator using BF Calculation.
    kTransverseMercatorBF           = 491 , // Transverse Mercator using BF Calculation.
    kObliqueMercator1PtUV           = 1281, // Unrectified Hotine Oblique Mercator. Single point form. 
    kObliqueMercator1PtXY           = 1282, // Rectified Hotine Oblique Mercator. Single point form.
    kObliqueMercator2PtUV           = 1283, // Unrectified Hotine Oblique Mercator. Two point form.
    kObliqueMercator2PtXY           = 1284, // Rectified Hotine Oblique Mercator. Two point form.    
    kRectifiedSkewOrthoIsect        = 1285, // Rectified Skew Orthomorphic (Intersect).            
    kRectifiedSkewOrthoC            = 1286, // Rectified Skew Orthomorphic (Center).
    kRectifiedSkewOrthoAO           = 1287  // Rectified Skew Orthomorphic (Azimuth at Origin).    
  };

  /** \details
    This enumeration represents the linear or angular unit.
  */
  enum OdDgGeoDataCoordSystemUnitType
  {
    kUnitUnknown = 0,
    kUnitMeter = 1,
    kUnitFoot = 2,
    kUnitInch = 3,
    kUnitIFoot = 4,
    kUnitClarkeFoot = 5,
    kUnitIInch = 6,
    kUnitCentimeter = 7,
    kUnitKilometer = 8,
    kUnitYard = 9,
    kUnitSearsYard = 10,
    kUnitMile = 11,
    kUnitIYard = 12,
    kUnitIMile = 13,
    kUnitKnot = 14,
    kUnitNautM = 15,
    kUnitLat66 = 16,
    kUnitLat83 = 17,
    kUnitDecimeter = 18,
    kUnitMillimeter = 19,
    kUnitDekameter = 20,
    kUnitHectometer = 21,
    kUnitGermanMeter = 22,
    kUnitCaGrid = 23,
    kUnitClarkeChain = 24,
    kUnitGunterChain = 25,
    kUnitBenoitChain = 26,
    kUnitSearsChain = 27,
    kUnitClarkeLink = 28,
    kUnitGunterLink = 29,
    kUnitBenoitLink = 30,
    kUnitSearsLink = 31,
    kUnitRod = 32,
    kUnitPerch = 33,
    kUnitPole = 34,
    kUnitFurlong = 35,
    kUnitRood = 36,
    kUnitCapeFoot = 37,
    kUnitBrealey = 38,
    kUnitSearsFoot = 39,
    kUnitGoldCoastFoot = 40,
    kUnitMicroInch = 41,
    kUnitIndianYard = 42,
    kUnitIndianFoot = 43,
    kUnitIndianFt37 = 44,
    kUnitIndianFt62 = 45,
    kUnitIndianFt75 = 46,
    kUnitIndianYd37 = 47,
    kUnitDecameter = 48,
    kUnitInternationalChain = 49,
    kUnitInternationalLink = 50,
    kUnitBrFootTrunc = 51,
    kUnitBrChainTrunc = 52,
    kUnitBrLinkTrunc = 53,
    kUnitDegree = 1001,
    kUnitGrad = 1002,
    kUnitGrade = 1003,
    kUnitMapInfo = 1004,
    kUnitMil = 1005,
    kUnitMinute = 1006,
    kUnitRadian = 1007,
    kUnitSecond = 1008,
    kUnitDecisec = 1009,
    kUnitCentisec = 1010,
    kUnitMillisec = 1011,
  };

public:
  ODRX_DECLARE_MEMBERS(OdDgGeoDataCoordinateSystem);

  virtual OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemProjectionType getProjectionType() const = 0;

  virtual OdString getName() const = 0;
  virtual void     setName(const OdString& strName) = 0;
  
  virtual OdString getGroupName() const = 0;
  virtual void     setGroupName(const OdString& strGrName) = 0;

  virtual OdString getDescription() const = 0;
  virtual void     setDescription(const OdString& strDesc) = 0;

  virtual OdString getSource() const = 0;
  virtual void     setSource(const OdString& strSource) = 0;

  virtual OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemUnitType getUnits() const = 0;
  virtual void setUnits(const OdString& strUnitName) = 0;
  virtual void setUnits(const OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemUnitType& uUnits) = 0;

  virtual OdGeExtents2d getGeodeticExtents() const = 0;
  virtual void          setGeodeticExtents(const OdGeExtents2d& extGeodetic) = 0;

  virtual OdDgGeoDataCoordinateSystemParamArray getParameters() const = 0;
  virtual OdRxObjectPtr clone() const = 0;

  virtual void setFromExternalData(const OdDgGeoDataCoordinateSystemCSMapsData& data) = 0;
  virtual OdDgGeoDataCoordinateSystemCSMapsData getExternalData() const = 0;

  static OdDgGeoDataCoordinateSystemPtr createObject(const OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemProjectionType uProjType);
  static OdString getUnitString(const OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemUnitType uType);
  static OdDgModel::UnitDescription getUnitDescription(const OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemUnitType uType);
  static OdString getProjectionString(const OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemProjectionType uType);
  static OdString getShortProjectionString(const OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemProjectionType uType);
};

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeographicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
  public:
    ODRX_DECLARE_MEMBERS(OdDgGeographicCoordinateSystem);

    virtual double getOriginLongitude() const = 0;
    virtual void   setOriginLongitude(double dValue) = 0;

    virtual double getMinUsefulLongitude() const = 0;
    virtual void   setMinUsefulLongitude(double dValue) = 0;

    virtual double getMaxUsefulLongitude() const = 0;
    virtual void   setMaxUsefulLongitude(double dValue) = 0;
};

typedef OdSmartPtr<OdDgGeographicCoordinateSystem> OdDgGeographicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgTransverseMercatorCoordinateSystem> OdDgTransverseMercatorCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgAlbersEqualAreaConicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgAlbersEqualAreaConicCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgAlbersEqualAreaConicCoordinateSystem> OdDgAlbersEqualAreaConicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgMercatorCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgMercatorCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgMercatorCoordinateSystem> OdDgMercatorCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertAzimuthalEquidistantCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertAzimuthalEquidistantCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getYAxisAzimuth() const = 0;
  virtual void   setYAxisAzimuth(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertAzimuthalEquidistantCoordinateSystem> OdDgLambertAzimuthalEquidistantCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertTangentialCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertTangentialCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertTangentialCoordinateSystem> OdDgLambertTangentialCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgPolyconicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgPolyconicCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgPolyconicCoordinateSystem> OdDgPolyconicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgPolyconicModCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgPolyconicModCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getEasternMeredian() const = 0;
  virtual void   setEasternMeredian(double dValue) = 0;

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgPolyconicModCoordinateSystem> OdDgPolyconicModCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgAzimuthalEqualAreaCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgAzimuthalEqualAreaCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getYAxisAzimuth() const = 0;
  virtual void   setYAxisAzimuth(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgAzimuthalEqualAreaCoordinateSystem> OdDgAzimuthalEqualAreaCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgEquidistantConicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgEquidistantConicCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgEquidistantConicCoordinateSystem> OdDgEquidistantConicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgMillerCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgMillerCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgMillerCoordinateSystem> OdDgMillerCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgStereographicModCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgStereographicModCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdArray<double> getCoefficients() const = 0;
  virtual void   setCoefficients(const OdArray<double>& arrValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgStereographicModCoordinateSystem> OdDgStereographicModCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgNewZealandCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgNewZealandCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgNewZealandCoordinateSystem> OdDgNewZealandCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgSinusoidalCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgSinusoidalCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdArray<double> getCoefficients() const = 0;
  virtual void   setCoefficients(const OdArray<double>& arrValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgSinusoidalCoordinateSystem> OdDgSinusoidalCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgOrthographicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgOrthographicCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgOrthographicCoordinateSystem> OdDgOrthographicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGnomonicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGnomonicCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgGnomonicCoordinateSystem> OdDgGnomonicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgEquidistantCylindricalCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgEquidistantCylindricalCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getReferenceParallel() const = 0;
  virtual void   setReferenceParallel(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgEquidistantCylindricalCoordinateSystem> OdDgEquidistantCylindricalCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgVanDerGrintenCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgVanDerGrintenCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgVanDerGrintenCoordinateSystem> OdDgVanDerGrintenCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgCassiniCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgCassiniCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgCassiniCoordinateSystem> OdDgCassiniCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgRobinsonCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgRobinsonCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgRobinsonCoordinateSystem> OdDgRobinsonCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgBonneCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgBonneCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgBonneCoordinateSystem> OdDgBonneCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgEckert4CoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgEckert4CoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgEckert4CoordinateSystem> OdDgEckert4CoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgEckert6CoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgEckert6CoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgEckert6CoordinateSystem> OdDgEckert6CoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgMollweideCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgMollweideCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdArray<double> getCoefficients() const = 0;
  virtual void   setCoefficients(const OdArray<double>& arrValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgMollweideCoordinateSystem> OdDgMollweideCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGoodeHomolosineCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGoodeHomolosineCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdArray<double> getCoefficients() const = 0;
  virtual void   setCoefficients(const OdArray<double>& arrValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgGoodeHomolosineCoordinateSystem> OdDgGoodeHomolosineCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgEqualAreaCylindricalNACoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgEqualAreaCylindricalNACoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgEqualAreaCylindricalNACoordinateSystem> OdDgEqualAreaCylindricalNACoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgEqualAreaCylindricalTACoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgEqualAreaCylindricalTACoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgEqualAreaCylindricalTACoordinateSystem> OdDgEqualAreaCylindricalTACoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgBipolarObliqueConformalConicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgBipolarObliqueConformalConicCoordinateSystem);

  virtual double getFirstPoleLongitude() const = 0;
  virtual void   setFirstPoleLongitude(double dValue) = 0;

  virtual double getFirstPoleLatitude() const = 0;
  virtual void   setFirstPoleLatitude(double dValue) = 0;

  virtual double getSecondPoleLongitude() const = 0;
  virtual void   setSecondPoleLongitude(double dValue) = 0;

  virtual double getSecondPoleLatitude() const = 0;
  virtual void   setSecondPoleLatitude(double dValue) = 0;

  virtual double getDistanceBetweenPoles() const = 0;
  virtual void   setDistanceBetweenPoles(double dValue) = 0;

  virtual double getAngularDistanceToFirstStdParallel() const = 0;
  virtual void   setAngularDistanceToFirstStdParallel(double dValue) = 0;

  virtual double getAngularDistanceToSecondStdParallel() const = 0;
  virtual void   setAngularDistanceToSecondStdParallel(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgBipolarObliqueConformalConicCoordinateSystem> OdDgBipolarObliqueConformalConicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgSwissObliqueCylindricalCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgSwissObliqueCylindricalCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgSwissObliqueCylindricalCoordinateSystem> OdDgSwissObliqueCylindricalCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgPolarStereographicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgPolarStereographicCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgPolarStereographicCoordinateSystem> OdDgPolarStereographicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgObliqueStereographicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgObliqueStereographicCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgObliqueStereographicCoordinateSystem> OdDgObliqueStereographicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgSnyderObliqueStereographicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgSnyderObliqueStereographicCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getYAxisAzimuth() const = 0;
  virtual void   setYAxisAzimuth(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgSnyderObliqueStereographicCoordinateSystem> OdDgSnyderObliqueStereographicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertConformalConic1StdLatCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertConformalConic1StdLatCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertConformalConic1StdLatCoordinateSystem> OdDgLambertConformalConic1StdLatCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertConformalConicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertConformalConicCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertConformalConicCoordinateSystem> OdDgLambertConformalConicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertConformalConicMichiganCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertConformalConicMichiganCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertConformalConicMichiganCoordinateSystem> OdDgLambertConformalConicMichiganCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertConformalConicBelgianCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertConformalConicBelgianCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertConformalConicBelgianCoordinateSystem> OdDgLambertConformalConicBelgianCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertConformalConicWCCSCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertConformalConicWCCSCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getAverageSeparation() const = 0;
  virtual void   setAverageSeparation(double dValue) = 0;

  virtual double getAverageElevation() const = 0;
  virtual void   setAverageElevation(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertConformalConicWCCSCoordinateSystem> OdDgLambertConformalConicWCCSCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorWCCSCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorWCCSCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getAverageSeparation() const = 0;
  virtual void   setAverageSeparation(double dValue) = 0;

  virtual double getAverageElevation() const = 0;
  virtual void   setAverageElevation(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgTransverseMercatorWCCSCoordinateSystem> OdDgTransverseMercatorWCCSCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertConformalConicMCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertConformalConicMCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getAverageHeight() const = 0;
  virtual void   setAverageHeight(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertConformalConicMCoordinateSystem> OdDgLambertConformalConicMCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorMCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorMCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getAverageHeight() const = 0;
  virtual void   setAverageHeight(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgTransverseMercatorMCoordinateSystem> OdDgTransverseMercatorMCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorRSACoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorRSACoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgTransverseMercatorRSACoordinateSystem> OdDgTransverseMercatorRSACoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgUniversalTransverseMercatorCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgUniversalTransverseMercatorCoordinateSystem);

  virtual OdUInt32 getUTMZone() const = 0;
  virtual void     setUTMZone(OdUInt32 uValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemHemisphereValue getHemisphere() const = 0;
  virtual void   setHemisphere(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemHemisphereValue iHemisphere) = 0;
};

typedef OdSmartPtr<OdDgUniversalTransverseMercatorCoordinateSystem> OdDgUniversalTransverseMercatorCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorSnyderCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorSnyderCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgTransverseMercatorSnyderCoordinateSystem> OdDgTransverseMercatorSnyderCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGaussKrugerCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGaussKrugerCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgGaussKrugerCoordinateSystem> OdDgGaussKrugerCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgKrovakCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgKrovakCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getPoleLongitude() const = 0;
  virtual void   setPoleLongitude(double dValue) = 0;

  virtual double getPoleLatitude() const = 0;
  virtual void   setPoleLatitude(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgKrovakCoordinateSystem> OdDgKrovakCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgMercatorSRCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgMercatorSRCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgMercatorSRCoordinateSystem> OdDgMercatorSRCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgObliqueConformalConicCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgObliqueConformalConicCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getPoleLongitude() const = 0;
  virtual void   setPoleLongitude(double dValue) = 0;

  virtual double getPoleLatitude() const = 0;
  virtual void   setPoleLatitude(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgObliqueConformalConicCoordinateSystem> OdDgObliqueConformalConicCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgKrovak95CoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgKrovak95CoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getPoleLongitude() const = 0;
  virtual void   setPoleLongitude(double dValue) = 0;

  virtual double getPoleLatitude() const = 0;
  virtual void   setPoleLatitude(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgKrovak95CoordinateSystem> OdDgKrovak95CoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgPolarStereographicSLCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgPolarStereographicSLCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getStandardCircleLatitude() const = 0;
  virtual void   setStandardCircleLatitude(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgPolarStereographicSLCoordinateSystem> OdDgPolarStereographicSLCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorAffineCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorAffineCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getA0Coefficient() const = 0;
  virtual void   setA0Coefficient(double dValue) = 0;

  virtual double getB0Coefficient() const = 0;
  virtual void   setB0Coefficient(double dValue) = 0;

  virtual double getA1Coefficient() const = 0;
  virtual void   setA1Coefficient(double dValue) = 0;

  virtual double getA2Coefficient() const = 0;
  virtual void   setA2Coefficient(double dValue) = 0;

  virtual double getB1Coefficient() const = 0;
  virtual void   setB1Coefficient(double dValue) = 0;

  virtual double getB2Coefficient() const = 0;
  virtual void   setB2Coefficient(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgTransverseMercatorAffineCoordinateSystem> OdDgTransverseMercatorAffineCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgNonEarthCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgNonEarthCoordinateSystem);

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgNonEarthCoordinateSystem> OdDgNonEarthCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgObliqueCylindricalCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgObliqueCylindricalCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getGaussianParallelPointLatitude() const = 0;
  virtual void   setGaussianParallelPointLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgObliqueCylindricalCoordinateSystem> OdDgObliqueCylindricalCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgDanishSystemKMS2001CoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgDanishSystemKMS2001CoordinateSystem);

  virtual OdUInt32 getRegionNumber() const = 0;
  virtual void     setRegionNumber(OdUInt32 uValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgDanishSystemKMS2001CoordinateSystem> OdDgDanishSystemKMS2001CoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorOSTN97CoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorOSTN97CoordinateSystem);
};

typedef OdSmartPtr<OdDgTransverseMercatorOSTN97CoordinateSystem> OdDgTransverseMercatorOSTN97CoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgAzimuthalEquidistantCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgAzimuthalEquidistantCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getYAxisAzimuth() const = 0;
  virtual void   setYAxisAzimuth(double dValue) = 0;

  virtual double getAverageElevation() const = 0;
  virtual void   setAverageElevation(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgAzimuthalEquidistantCoordinateSystem> OdDgAzimuthalEquidistantCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorOSTN02CoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorOSTN02CoordinateSystem);
};

typedef OdSmartPtr<OdDgTransverseMercatorOSTN02CoordinateSystem> OdDgTransverseMercatorOSTN02CoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgDanishSystemNoKMSCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgDanishSystemNoKMSCoordinateSystem);

  virtual OdUInt32 getRegionNumber() const = 0;
  virtual void     setRegionNumber(OdUInt32 uValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgDanishSystemNoKMSCoordinateSystem> OdDgDanishSystemNoKMSCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorKFCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorKFCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgTransverseMercatorKFCoordinateSystem> OdDgTransverseMercatorKFCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgWinkelTripelCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgWinkelTripelCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getReferenceParallel() const = 0;
  virtual void   setReferenceParallel(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgWinkelTripelCoordinateSystem> OdDgWinkelTripelCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgNerthSRCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgNerthSRCoordinateSystem);

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getRotation() const = 0;
  virtual void   setRotation(double dValue) = 0;

  virtual double getScale() const = 0;
  virtual void   setScale(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgNerthSRCoordinateSystem> OdDgNerthSRCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLambertConformalConicAffineCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgLambertConformalConicAffineCoordinateSystem);

  virtual double getFirstStandardParallel() const = 0;
  virtual void   setFirstStandardParallel(double dValue) = 0;

  virtual double getSecondStandardParallel() const = 0;
  virtual void   setSecondStandardParallel(double dValue) = 0;

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getA0Coefficient() const = 0;
  virtual void   setA0Coefficient(double dValue) = 0;

  virtual double getB0Coefficient() const = 0;
  virtual void   setB0Coefficient(double dValue) = 0;

  virtual double getA1Coefficient() const = 0;
  virtual void   setA1Coefficient(double dValue) = 0;

  virtual double getA2Coefficient() const = 0;
  virtual void   setA2Coefficient(double dValue) = 0;

  virtual double getB1Coefficient() const = 0;
  virtual void   setB1Coefficient(double dValue) = 0;

  virtual double getB2Coefficient() const = 0;
  virtual void   setB2Coefficient(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgLambertConformalConicAffineCoordinateSystem> OdDgLambertConformalConicAffineCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgDanishSystemKMS1999CoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgDanishSystemKMS1999CoordinateSystem);

  virtual OdUInt32 getRegionNumber() const = 0;
  virtual void     setRegionNumber(OdUInt32 uValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgDanishSystemKMS1999CoordinateSystem> OdDgDanishSystemKMS1999CoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgEquidistantCylindricalECoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgEquidistantCylindricalECoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getReferenceParallel() const = 0;
  virtual void   setReferenceParallel(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgEquidistantCylindricalECoordinateSystem> OdDgEquidistantCylindricalECoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgPlateCarreeCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgPlateCarreeCoordinateSystem);

  virtual double getOriginLongitude() const = 0;
  virtual void   setOriginLongitude(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getReferenceParallel() const = 0;
  virtual void   setReferenceParallel(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgPlateCarreeCoordinateSystem> OdDgPlateCarreeCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgPseudoMercatorCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgPseudoMercatorCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgPseudoMercatorCoordinateSystem> OdDgPseudoMercatorCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgUniversalTransverseMercatorBFCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgUniversalTransverseMercatorBFCoordinateSystem);

  virtual OdUInt32 getUTMZone() const = 0;
  virtual void     setUTMZone(OdUInt32 uValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemHemisphereValue getHemisphere() const = 0;
  virtual void   setHemisphere(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemHemisphereValue iHemisphere) = 0;
};

typedef OdSmartPtr<OdDgUniversalTransverseMercatorBFCoordinateSystem> OdDgUniversalTransverseMercatorBFCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgTransverseMercatorBFCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgTransverseMercatorBFCoordinateSystem);

  virtual double getCentralMeredian() const = 0;
  virtual void   setCentralMeredian(double dValue) = 0;

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgTransverseMercatorBFCoordinateSystem> OdDgTransverseMercatorBFCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgObliqueMercator1PtUVCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgObliqueMercator1PtUVCoordinateSystem);

  virtual double getCentralPointLongitude() const = 0;
  virtual void   setCentralPointLongitude(double dValue) = 0;

  virtual double getCentralPointLatitude() const = 0;
  virtual void   setCentralPointLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getAzimuth() const = 0;
  virtual void   setAzimuth(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgObliqueMercator1PtUVCoordinateSystem> OdDgObliqueMercator1PtUVCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgObliqueMercator1PtXYCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgObliqueMercator1PtXYCoordinateSystem);

  virtual double getCentralPointLongitude() const = 0;
  virtual void   setCentralPointLongitude(double dValue) = 0;

  virtual double getCentralPointLatitude() const = 0;
  virtual void   setCentralPointLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getAzimuth() const = 0;
  virtual void   setAzimuth(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgObliqueMercator1PtXYCoordinateSystem> OdDgObliqueMercator1PtXYCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgObliqueMercator2PtUVCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgObliqueMercator2PtUVCoordinateSystem);

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFirstPointLongitude() const = 0;
  virtual void   setFirstPointLongitude(double dValue) = 0;

  virtual double getFirstPointLatitude() const = 0;
  virtual void   setFirstPointLatitude(double dValue) = 0;

  virtual double getSecondPointLongitude() const = 0;
  virtual void   setSecondPointLongitude(double dValue) = 0;

  virtual double getSecondPointLatitude() const = 0;
  virtual void   setSecondPointLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgObliqueMercator2PtUVCoordinateSystem> OdDgObliqueMercator2PtUVCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgObliqueMercator2PtXYCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgObliqueMercator2PtXYCoordinateSystem);

  virtual double getOriginLatitude() const = 0;
  virtual void   setOriginLatitude(double dValue) = 0;

  virtual double getFirstPointLongitude() const = 0;
  virtual void   setFirstPointLongitude(double dValue) = 0;

  virtual double getFirstPointLatitude() const = 0;
  virtual void   setFirstPointLatitude(double dValue) = 0;

  virtual double getSecondPointLongitude() const = 0;
  virtual void   setSecondPointLongitude(double dValue) = 0;

  virtual double getSecondPointLatitude() const = 0;
  virtual void   setSecondPointLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgObliqueMercator2PtXYCoordinateSystem> OdDgObliqueMercator2PtXYCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgRectifiedSkewOrthoAOCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgRectifiedSkewOrthoAOCoordinateSystem);

  virtual double getCentralPointLongitude() const = 0;
  virtual void   setCentralPointLongitude(double dValue) = 0;

  virtual double getCentralPointLatitude() const = 0;
  virtual void   setCentralPointLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getAzimuth() const = 0;
  virtual void   setAzimuth(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgRectifiedSkewOrthoAOCoordinateSystem> OdDgRectifiedSkewOrthoAOCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgRectifiedSkewOrthoCCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgRectifiedSkewOrthoCCoordinateSystem);

  virtual double getCentralPointLongitude() const = 0;
  virtual void   setCentralPointLongitude(double dValue) = 0;

  virtual double getCentralPointLatitude() const = 0;
  virtual void   setCentralPointLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getAzimuth() const = 0;
  virtual void   setAzimuth(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgRectifiedSkewOrthoCCoordinateSystem> OdDgRectifiedSkewOrthoCCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgRectifiedSkewOrthoIsectCoordinateSystem : public OdDgGeoDataCoordinateSystem
{
public:
  ODRX_DECLARE_MEMBERS(OdDgRectifiedSkewOrthoIsectCoordinateSystem);

  virtual double getCentralPointLongitude() const = 0;
  virtual void   setCentralPointLongitude(double dValue) = 0;

  virtual double getCentralPointLatitude() const = 0;
  virtual void   setCentralPointLatitude(double dValue) = 0;

  virtual double getFalseEasting() const = 0;
  virtual void   setFalseEasting(double dValue) = 0;

  virtual double getFalseNorthing() const = 0;
  virtual void   setFalseNorthing(double dValue) = 0;

  virtual double getAzimuth() const = 0;
  virtual void   setAzimuth(double dValue) = 0;

  virtual double getScaleReduction() const = 0;
  virtual void   setScaleReduction(double dValue) = 0;

  virtual OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue getQuadrant() const = 0;
  virtual void   setQuadrant(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue iQuadrant) = 0;
};

typedef OdSmartPtr<OdDgRectifiedSkewOrthoIsectCoordinateSystem> OdDgRectifiedSkewOrthoIsectCoordinateSystemPtr;

//=============================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataDatum
{
  public:

    enum OdDgGeoDataConversionMethod
    {
      kNone               = 0x0,
      kMolodensky         = 0x1,
      kMultipleRegression = 0x2,
      kBursaWolf          = 0x3,
      kNAD27              = 0x4,
      kNAD83              = 0x5,
      kWGS84              = 0x6,
      kWGS72              = 0x7,
      kHARN               = 0x8,
      k7Params            = 0x9,
      kAGD66              = 0xa,
      k3Params            = 0xb,
      k6Params            = 0xc,
      k4Params            = 0xd,
      kAGD84              = 0xe,
      kNZGD4              = 0xf,
      kATS77              = 0x10,
      kGDA94              = 0x11,
      kNZGD2k             = 0x12,
      kCSRS               = 0x13,
      kTOKYO              = 0x14,
      kRGF93              = 0x15,
      kED50               = 0x16,
      kDHDN               = 0x17,
      kETRF89             = 0x18,
      kGeocentric         = 0x19,
      kCHENxy             = 0x1a,
      kPLYNM              = 0x1b
    };

  public:

    OdDgGeoDataDatum();
    ~OdDgGeoDataDatum();

    OdString    getName() const;
    void        setName(const OdString& strName);

    OdString    getDescription() const;
    void        setDescription(const OdString& strDesc);

    OdString    getSource() const;
    void        setSource(const OdString& strSource);

    OdDgGeoDataConversionMethod getDatumConversionMethod() const;
    void setDatumConversionMethod(const OdDgGeoDataConversionMethod& uMethod);

    OdGePoint3d getOffset() const;
    void        setOffset(const OdGePoint3d& ptOffset);

    double      getXRotation() const;
    void        setXRotation(double dAngle);

    double      getYRotation() const;
    void        setYRotation(double dAngle);

    double      getZRotation() const;
    void        setZRotation(double dAngle);

    double      getScale() const;
    void        setScale(double dScale);

    OdGeMatrix3d getTransformMatrix() const;
    void         setTransformMatrix(const OdGeMatrix3d& matTransform);

  private:
    OdString    m_strName;
    OdString    m_strDesc;
    OdString    m_strSource;
    OdGePoint3d m_ptOffset;
    OdDgGeoDataConversionMethod m_uConversionMethod;
    double      m_dXRotation;
    double      m_dYRotation;
    double      m_dZRotation;
    double      m_dScale;
};

//--------------------------------------------------------------

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataEllipsoid
{
public:
  OdDgGeoDataEllipsoid();
  ~OdDgGeoDataEllipsoid();

  OdString    getName() const;
  void        setName(const OdString& strName);

  OdString    getDescription() const;
  void        setDescription(const OdString& strDesc);

  OdString    getSource() const;
  void        setSource(const OdString& strSource);

  double      getPolarRadius() const;
  void        setPolarRadius(double dRadius);

  double      getEquatorialRadius() const;
  void        setEquatorialRadius(double dRadius);

  double      getEccentricity() const;
  void        setEccentricity(double dValue);

private:
  OdString    m_strName;
  OdString    m_strDesc;
  OdString    m_strSource;
  double      m_dPolarRadius;
  double      m_dEquatorialRadius;
  double      m_dEccentricity;
};

//--------------------------------------------------------------

/**
  <group OdDg_Classes>
*/
struct OdDgGeoDataHelmertParams
{
  OdDgGeoDataHelmertParams() { m_dParamA = 1.0; m_dParamB = 0.0; m_ptOffset = OdGePoint3d::kOrigin; }
  double      m_dParamA;
  double      m_dParamB;
  OdGePoint3d m_ptOffset;
};

/** \details
  This abstract class represents a category which holds string identifiers referring to
  a group of coordinate reference systems.

  <group OdDg_Classes>
*/

class OdDgGeoDataCoordinateSystemCategory;
typedef OdSmartPtr<OdDgGeoDataCoordinateSystemCategory> OdDgGeoDataCoordinateSystemCategoryPtr;

//=============================================================================================

/**
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataCoordinateSystemCategory : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGeoDataCoordinateSystemCategory);

  /** \details
    Returns the category's ID.

    \param categoryId [in/out] Category ID.

    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  virtual OdResult getId(OdString& categoryId) const;

  /** \details
    Returns the number of coordinate systems that belong to this category.

    \param num [in/out] Number of coordinate systems.

    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  virtual OdResult getNumOfCoordinateSystem(int& num) const;

  /** \details
    Returns the coordinate system at the specified index.

    \param index [in] Index.
    \param pCoordSys [in/out] Pointer to an OdDbGeoCoordinateSystem object.

    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  virtual OdResult getCoordinateSystemAt(int index, OdDgGeoDataCoordinateSystemPtr& pCoordSys) const;

  /** \details
    Creates and returns all coordinate system categories.

    \param allCategories [in/out] Array of pointers to returned categories.

    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  static OdResult createAll(OdArray<OdDgGeoDataCoordinateSystemCategoryPtr>& allCategories);

  /** \details
  Creates and returns coordinate system category.

  \param strCategoryId [in] Category name.

  \returns Returns pointer to OdDgGeoDataCoordinateSystemCategory object.
*/

  static OdDgGeoDataCoordinateSystemCategoryPtr createObject(const OdString& strCategoryId);
};

//--------------------------------------------------------------

class OdDgGeoDataInfo;
typedef OdSmartPtr<OdDgGeoDataInfo> OdDgGeoDataInfoPtr;

/** \details
   
    Corresponding C++ library: TG_Db

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataInfo : public OdDgElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgGeoDataInfo);

public:

  enum
  {
    kSignature = 0x00B6
  };

  enum OdDgGeoDataVerticalDataType
  {
    kMatchDatum = 0,
    kGeoid      = 1
  };

  enum OdDgGeoDataLocalTransformType
  {
    kNoTransform = 0,
    kHelmertTransform = 1
  };

public:

  /** \details
   Creates and returns a new OdDgGeoDataInfo object from the current virtual catalog.

   \param coordSysIdOrFullDef [in] ID or WKT representation of the CRS definition to load.
   \param pCoordSys [out] New CRS.

   \returns Returns non-null pointer if successful.
 */
  static OdDgGeoDataInfoPtr createObject(const OdString& coordSysIdOrFullDef);

  /** \details
   Creates and returns a new OdDgGeoDataInfo object from the current coordinate system.

   \param pCS [in] pointer to coordinate system.

   \returns Returns non-null pointer if successful.
 */
  static OdDgGeoDataInfoPtr createObject(const OdDgGeoDataCoordinateSystemPtr& pCS);

  /** \details
    Creates and returns a new OdDgGeoDataCoordinateSystem object for every existing,
    persistent projected CRS definition from the current virtual catalog when the passed in
    geodetic point is within the geodetic extents of the CRS.

    \param geoPt [in] Geodetic point (Longitude, Latitude, Altitude).
    \param allCoordSys [out] Array of pointers to the new CRS objects.

    \returns Returns eOK if successful, or an appropriate error code if not.
  */
  static OdResult createAll(const OdGePoint3d& geoPt, OdArray<OdDgGeoDataCoordinateSystemPtr>& allCoordSys);
  /** \details
    Creates and returns a new OdDbGeoCoordinateSystem object for every existing,
    persistent CRS definition from the specified catalog.

    \param allCoordSys [out] Array of pointers to the new CRS objects.
    \param pCategory [in] Category.

    \returns Returns eOK if successful, or an appropriate error code if not.

    \remarks
    If pCategory is NULL, all existing and persistent CRS definitions are returned.
  */
  static OdResult createAll(OdArray<OdDgGeoDataCoordinateSystemPtr>& allCoordSys,
    const OdDgGeoDataCoordinateSystemCategory* pCategory = NULL);

  /** \details
    Returns string representation for input unit type.

    \param eUnit [in] Unit type.

    \returns Returns string representation for input unit type.
  */
  static OdString unitNameToString(OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemUnitType eUnit);

  /** \details
   Creates and returns a new OdDgGeoDataInfo object based on placemarks.
   Coordinate system will be Azimutal Equal Area. First placemark is base of coordinate system. Other placemarks
   are used for azimuth calculation. Coordinates of placemarks for coordinate system offsets will be converted
   from model units to meter. If placemark is non-dbro the coordinate walues will not be converted.

   \param arrPlacemarks [in] array of pointers to kml placemarks.

   \returns Returns non-null pointer if successful.
 */
  static OdDgGeoDataInfoPtr createObject(const OdArray<OdDgKMLPlacemark2dPtr>& arrPlacemarks);
  static OdDgGeoDataInfoPtr createObject(const OdArray<OdDgKMLPlacemark3dPtr>& arrPlacemarks);

  // Coordinate system

  virtual OdDgGeoDataCoordinateSystemPtr getCoordinateSystem() const;
  virtual OdResult setCoordinateSystem( const OdDgGeoDataCoordinateSystemPtr& coordSystem );
  virtual OdResult setCoordinateSystemByName(const OdString& strCSName);

  // Datum

  virtual OdDgGeoDataDatum getDatum() const;
  virtual OdResult         setDatum(const OdString& strName);

  // Ellipsoid

  virtual OdDgGeoDataEllipsoid getEllipsoid() const;

  /** \details
    Returns the string in WKT format that represents this CRS.

    \param strWkt [out] CRS's representation in WKT format.

    \returns eOK if successful, or an appropriate error code otherwise.
  */
  virtual OdResult getWktRepresentation(OdString& strWkt) const;

  // Coordinate system modifiers

  virtual OdDgGeoDataVerticalDataType getVerticalDataType() const;
  virtual void setVerticalDataType(const OdDgGeoDataVerticalDataType& uType);

  virtual OdDgGeoDataLocalTransformType getLocalTransformType() const;
  virtual void setLocalTransformType(const OdDgGeoDataLocalTransformType& uType);

  virtual OdDgGeoDataHelmertParams getHelmertParams() const;
  virtual void                     setHelmertParams(const OdDgGeoDataHelmertParams& params);

  // Units

  virtual OdUInt32 getNumberOfSubUnitsInMasterUnit() const;
  virtual void     setNumberOfSubUnitsInMasterUnit(OdUInt32 nSubUnitsInUnit);

  virtual OdUInt32 getNumberOfUORSInSubUnit() const;
  virtual void     setNumberOfUORSInSubUnit(OdUInt32 nUORsInSubUnit);

  // Other

  virtual bool     getPlacemarkSourceFlag() const;
  virtual void     setPlacemarkSourceFlag(bool bSet);
};


/** \details
An abstract class that represents a point transformer to reproject xyz points from one geo data to another.

<group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataReprojectionCoordinateTransformer : public OdRxObject
{
  ODRX_DECLARE_MEMBERS(OdDgGeoDataReprojectionCoordinateTransformer);

  virtual OdResult transformPoint(OdGePoint3d& point) const = 0;
  virtual OdResult transformPoints(OdGePoint3dArray& arrPoints) const = 0;
  virtual OdResult transformPoint(OdGePoint2d& point) const = 0;
  virtual OdResult transformPoints(OdGePoint2dArray& arrPoints) const = 0;
};

typedef OdSmartPtr<OdDgGeoDataReprojectionCoordinateTransformer> OdDgGeoDataReprojectionCoordinateTransformerPtr;

/** \details
An abstract class that represents a point convertor "xyz" <-> "latitude, longitude".

<group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataCoordinateConverter : public OdRxObject
{
  ODRX_DECLARE_MEMBERS(OdDgGeoDataCoordinateConverter);

  virtual OdResult transformXYZPointLL(const OdGePoint3d& xyzPoint, OdGePoint3d& llPoint ) const = 0;
  virtual OdResult transformXYZPointsLL(const OdGePoint3dArray& arrXYZPoints, OdGePoint3dArray& arrLLPoints ) const = 0;

  virtual OdResult transformLLPointXYZ(const OdGePoint3d& llPoint, OdGePoint3d& xyzPoint) const = 0;
  virtual OdResult transformLLPointsXYZ(const OdGePoint3dArray& arrLLPoints, OdGePoint3dArray& arrXYZPoints) const = 0;
};

typedef OdSmartPtr<OdDgGeoDataCoordinateConverter> OdDgGeoDataCoordinateConverterPtr;

/** \details
An abstract class that represents a protocol extension for an OdDgGeoDataInfo object.

<group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGeoDataPE);

  virtual OdResult getGeoDataByName(const OdString& strName, OdDgGeoDataCoordinateSystemPtr& pCoordSystem, OdDgGeoDataDatum& datum, OdDgGeoDataEllipsoid& ellipsoid );
  virtual OdResult getGeoDataDatumByName(const OdString& strDatumName, OdDgGeoDataDatum& datum, OdDgGeoDataEllipsoid& ellipsoid );
  virtual OdResult getGeoDataEllipsoidByName(const OdString& strDatumName, OdDgGeoDataEllipsoid& ellipsoid);
  virtual OdResult createAll(const OdGePoint3d& geoPt, OdArray<OdDgGeoDataCoordinateSystemPtr>& allCoordSys);
  virtual OdResult createAll(OdArray<OdDgGeoDataCoordinateSystemPtr>& allCoordSys, const OdDgGeoDataCoordinateSystemCategory* pCategory = NULL);
  virtual OdResult transformGeoPointByDatum(const OdString& strDatumNameFrom, const OdString& strDatumNameTo, const OdGePoint3d& ptGeoPoint, OdGePoint3d& ptResult);
  virtual OdResult createGeoPointFromCS(const OdString& strCSFrom, const OdString& strDatumNameTo, const OdGePoint3d& ptXYZPoint, OdGePoint3d& ptResult);
  virtual OdDgGeoDataReprojectionCoordinateTransformerPtr createReprojectionTransformer(const OdDgGeoDataInfo* pGeoDataFrom, const OdDgGeoDataInfo* pGeoDataTo, double dModelScale = 1.0, bool bReprojectEllevation = true);
  virtual OdDgGeoDataCoordinateConverterPtr createGeoDataCoordinateConvertor(const OdDgGeoDataInfo* pGeoData, const OdDgModel* pModel = NULL);
  virtual OdResult getWktRepresentation(const OdDgGeoDataInfo* pGeoData, OdString& strWkt) const;
};

typedef OdSmartPtr<OdDgGeoDataPE> OdDgGeoDataPEPtr;

//--------------------------------------------------------------

/** \details
An abstract class that represents a protocol extension for an OdDgGeoDataInfo object.

<group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataCoordinateSystemCategoryPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGeoDataCoordinateSystemCategoryPE);

  virtual OdResult getNumOfCoordinateSystem(int& num, const OdString& strCategoryId) const;
  virtual OdResult getCoordinateSystemAt(int index, const OdString& strCategoryId, OdDgGeoDataCoordinateSystemPtr& pCoordSys) const;
  virtual OdResult createAll(OdArray<OdDgGeoDataCoordinateSystemCategoryPtr>& allCategories);
};

typedef OdSmartPtr<OdDgGeoDataCoordinateSystemCategoryPE> OdDgGeoDataCoordinateSystemCategoryPEPtr;

//--------------------------------------------------------------

/** \details
An abstract class that represents a protocol extension to reproject dgn objects when geo data is modified.

<group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoDataReprojectionPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDgGeoDataReprojectionPE);

  virtual bool reprojectElementByGeoData(OdDgElement* pElement, const OdDgGeoDataReprojectionCoordinateTransformer* pTransformer, const OdDgGeoDataReprojectionSettings& reprojectionSettings ) const;
};

typedef OdSmartPtr<OdDgGeoDataReprojectionPE> OdDgGeoDataReprojectionPEPtr;

/** \details
An abstract class that represents a protocol extension to create geo map image.

<group OdDg_Classes>
*/
class TG_EXPORT OdDgGeoMapImagePE : public OdRxObject
{
public:

  enum OdDgGeoMapImageType
  {
    kNoMap = 0,
    kAerial = 1,
    kRoad = 2,
    kHybrid = 3
  };

  enum OdDgGeoMapImageResolution
  {
    kCoarse = -1,
    kOptimal = 0,
    kFine = 1,
    kFiner = 2
  };

public:
  ODRX_DECLARE_MEMBERS(OdDgGeoMapImagePE);

  virtual OdGiRasterImagePtr createGeoMapImage(const OdGeExtents3d& extXYZ, const OdDgGeoDataInfo* pGeoDataInfo, const OdDgModel* pBaseModel,
    const OdGeExtents2d& extImage, OdDgGeoMapImageType uType, OdDgGeoMapImageResolution uResolution, int iLOD, 
    const OdDgElementId& idPlacemark ) const;
};

typedef OdSmartPtr<OdDgGeoMapImagePE> OdDgGeoMapImagePEPtr;

//=============================================================================

#endif // __DG_GEODATA_H__
