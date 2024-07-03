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
#ifndef _ODSPATIALREFERENCE_ODTAGSTRING_INCLUDED_
#define _ODSPATIALREFERENCE_ODTAGSTRING_INCLUDED_

#include "OdSpatialReference.h"

namespace OdSpatialReference
{
  /** \details
    This enumeration represents the projection parameter type.
  */
  enum ParameterType
  {
    kPrmCodeNotUsed = 0,
    kPrmCodeCntMer = 1,
    kPrmCodeNStdPll = 2,
    kPrmCodeSStdPll = 3,
    kPrmCodeStdPll = 4,
    kPrmCodeGCP1Lng = 5,
    kPrmCodeGCP1Lat = 6,
    kPrmCodeGCP2Lng = 7,
    kPrmCodeGCP2Lat = 8,
    kPrmCodeGCPLng = 9,
    kPrmCodeGCPLat = 10,
    kPrmCodeGcAzm = 11,
    kPrmCodeYAxisAz = 12,
    kPrmCodeEStdMer = 13,
    kPrmCodeNParall = 14,
    kPrmCodeSParall = 15,
    kPrmCodeP1Lng = 16,
    kPrmCodeP1Lat = 17,
    kPrmCodeP2Lng = 18,
    kPrmCodeP2Lat = 19,
    kPrmCodeAdP1P2 = 20,
    kPrmCodeAdSp1 = 21,
    kPrmCodeAdSp2 = 22,
    kPrmCodeCmplxAN = 23,
    kPrmCodeCmplxBN = 24,
    kPrmCodeWestLL = 25,
    kPrmCodeEastLL = 26,
    kPrmCodeUtmZN = 27,
    kPrmCodeHsNS = 28,
    kPrmCodeGHgt = 29,
    kPrmCodeAElev = 30,
    kPrmCodePoleLng = 31,
    kPrmCodePoleLat = 32,
    kPrmCodeOStdPll = 33,
    kPrmCodeStdCir = 34,
    kPrmCodeAfA0 = 35,
    kPrmCodeAfB0 = 36,
    kPrmCodeAfA1 = 37,
    kPrmCodeAfA2 = 38,
    kPrmCodeAfB1 = 39,
    kPrmCodeAfB2 = 40,
    kPrmCodeNrmlPll = 41,
    kPrmCodeDenRgn = 42,
    kPrmCodeSkwAzm = 43,
    kPrmCodeSclRotOrgX = 44,
    kPrmCodeSclRotOrgY = 45,
    kPrmCodeNrthScl = 46,
    kPrmCodeNrthRot = 47,
    kPrmCodeElpScl = 48,
    kWktCodeFEast = 101,
    kWktCodeFNorth = 102,
    kWktCodeOrgLng = 103,
    kWktCodeOrgLat = 104,
    kWktCodeSclRed = 105,
    kWktCodeDeltaX = 151,
    kWktCodeDeltaY = 152,
    kWktCodeDeltaZ = 153,
    kWktCodeRotatX = 154,
    kWktCodeRotatY = 155,
    kWktCodeRotatZ = 156,
    kWktCodeBwScal = 157
  };

  namespace Helper
  {
    /** \details
      Converts the unit code enum value to unit code name.

      \param eUnitCode [in] UnitCode enum value.
      \param sName [out] Unit code name.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult getUnitCodeName(UnitCode eUnitCode, OdString& sName);

    /** \details
      Converts the unit code name to unit code enum value.

      \param sName [in] Unit code name.
      \param eUnitCode [out] UnitCode enum value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult getUnitCode(const OdString& sName, UnitCode& eUnitCode);

    /** \details
      Gets the unit code information: unit type and scale.

      \param eUnitCode [in] UnitCode enum value.
      \param eUnitType [out] UnitType enum value.
      \param dScale [out] Scale.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult getUnitCodeInformation(UnitCode eUnitCode, UnitType& eUnitType, double& dScale);

    /** \details
      Converts the projection code enum value to projection code name.

      \param eUnitCode [in] ProjectionCode enum value.
      \param sName [out] Projection code name.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult getProjectionCodeName(ProjectionCode eProjectionCode, OdString& sName);
    
    /** \details
      Converts the projection code name to projection code enum value.

      \param sName [in] Projection code name.
      \param eProjectionCode [out] ProjectionCode enum value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult getProjectionCode(const OdString& sName, ProjectionCode& eProjectionCode);

    /** \details
      Returns the projection flag for input projection.

      \param eProjectionCode [in] ProjectionCode enum value.
      \param uFlags [out] projection flags.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult getProjectionFlags(ProjectionCode eProjectionCode, OdUInt32& uFlags);

    /** \details
      Determines the coordinate reference system type by input projection code.

      \param eProjectionCode [in] ProjectionCode enum value.

      \returns Returns Enum value CoordinateReferenceSystemType.
    */
    TD_SPATIALREFERENCE_API CoordinateReferenceSystemType getCoordinateSystemType(ProjectionCode eProjectionCode);

    /** \details
      Gets parameter code of input projection at specified index.

      \param eProjectionCode [in] ProjectionCode enum value.
      \param uIndex [in] Index of requested parameter (max projection parameters count is 24).

      \returns Returns Enum value ParameterType.
    */
    TD_SPATIALREFERENCE_API ParameterType getParameterCode(ProjectionCode eProjectionCode, OdUInt32 uIndex);

    /** \details
      Gets description of parameter.

      \param ePrmCode [in] ParameterType enum value expected.
      \param uIndex [in] Index of requested parameter (needed for Complex Series Coefficient's).

      \returns Returns Enum value ParameterType.
    */
    TD_SPATIALREFERENCE_API OdString getParameterDescription(OdUInt32 ePrmCode, OdUInt32 uIndex = 0);
  }
}

#endif //_ODSPATIALREFERENCE_ODTAGSTRING_INCLUDED_
