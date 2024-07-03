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
#ifndef _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONDEFINITION_INCLUDED_
#define _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONDEFINITION_INCLUDED_

#include "OdDefinitionBase.h"
#include "OdGeodeticTransformationParameters.h"

namespace OdSpatialReference
{
  class OdGeodeticTransformationDefinition;
  typedef OdSmartPtr<OdGeodeticTransformationDefinition> OdGeodeticTransformationDefinitionPtr;
  typedef OdArray<OdGeodeticTransformationDefinitionPtr> OdGeodeticTransformationDefinitionArray;

  class OdGeodeticTransformationDefinitionImpl;
  
  /** \details
    This class represents a geodetic transformation definition.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdGeodeticTransformationDefinition : public OdDefinitionBase
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdGeodeticTransformationDefinition);
  public:
    /** \details
      Loads and returns geodetic transformation definition.

      \param sCode [in] Geodetic transformation code.
      \param pGeodeticTransformationDefinition [out] Pointer to an OdGeodeticTransformationDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString& sCode, OdGeodeticTransformationDefinitionPtr& pGeodeticTransformationDefinition);
    
    /** \details
      Loads and returns all geodetic transformation definitions.

      \param arrGeodeticTransformationDefinition [out] Array of pointers to returned geodetic transformation definitions.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult loadAll(OdGeodeticTransformationDefinitionArray& arrGeodeticTransformationDefinition);

    /** \details
      Returns the source datum code of this geodetic transformation definition.
    
      \param sSourceDatum [out] Source datum code.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getSourceDatum(OdString& sSourceDatum) const;

    /** \details
      Sets the source datum to this geodetic transformation definition.

      \param sSourceDatum [in] Source datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setSourceDatum(const OdString& sSourceDatum);

    /** \details
      Returns the target datum code of this geodetic transformation definition.

      \param sTargetDatum [out] Target datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getTargetDatum(OdString& sTargetDatum) const;

    /** \details
      Sets the target datum to this geodetic transformation definition.

      \param sTargetDatum [in] Target datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setTargetDatum(const OdString& sTargetDatum);

    /** \details
      Returns the group string of this geodetic transformation definition.
    
      \param sGroup [out] Group string.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getGroup(OdString& sGroup) const;

    /** \details
      Sets the group string to this geodetic transformation definition.
    
      \param sGroup [in] Group string.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setGroup(const OdString& sGroup);

    /** \details
      Returns the epsg code of this geodetic transformation definition.

      \param nEpsgCode [out] Epsg code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEpsgCode(OdInt16& nEpsgCode) const;

    /** \details
      Sets the epsg code to this geodetic transformation definition.

      \param nEpsgCode [in] Epsg code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEpsgCode(OdInt16 nEpsgCode);

    /** \details
      Returns the epsg variation of this geodetic transformation definition.

      \param nEpsgVariation [out] Epsg variation.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEpsgVariation(OdInt16& nEpsgVariation) const;

    /** \details
      Sets the epsg variation to this geodetic transformation definition.

      \param nEpsgVariation [in] Epsg variation.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEpsgVariation(OdInt16 nEpsgVariation);

    /** \details
      Checks whether inverse supported for this geodetic transformation definition.

      \param bInverseSupported [out] If true - inverse is supported.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getInverseSupported(bool& bInverseSupported) const;
    
    /** \details
      Sets inverse supported flag for this geodetic transformation definition.

      \param bInverseSupported [in] If true - inverse is supported.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setInverseSupported(bool bInverseSupported);

    /** \details
      Returns the maximum iterations count of this geodetic transformation definition.
    
      \param nMaxIterations [out] Maximum iterations count.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getMaxIterations(OdInt16& nMaxIterations) const;

    /** \details
      Sets the maximum iterations count to this geodetic transformation definition.

      \param nMaxIterations [in] Maximum iterations count.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setMaxIterations(OdInt16 nMaxIterations);

    /** \details
      Returns the convergence value of this geodetic transformation definition.

      \param dConvergenceValue [out] Convergence value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getConvergenceValue(double& dConvergenceValue) const;

    /** \details
      Sets the convergence value to this geodetic transformation definition.

      \param dConvergenceValue [in] Convergence value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setConvergenceValue(double dConvergenceValue);

    /** \details
      Returns the error value of this geodetic transformation definition.

      \param dErrorValue [out] Error value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getErrorValue(double& dErrorValue) const;

    /** \details
      Sets the error value to this geodetic transformation definition.

      \param dErrorValue [in] Error value.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setErrorValue(double dErrorValue);

    /** \details
      Returns the accuracy of this geodetic transformation definition.

      \param dAccuracy [out] Accuracy.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getAccuracy(double& dAccuracy) const;

    /** \details
      Sets the accuracy to this geodetic transformation definition.

      \param dAccuracy [in] Accuracy.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setAccuracy(double dAccuracy);

    /** \details
      Returns the range minimum longitude of this geodetic transformation definition.

      \param dValue [out] Range minimum longitude.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getRangeMinLongitude(double& dValue) const;

    /** \details
      Sets the range minimum longitude to this geodetic transformation definition.
    
      \param dValue [in] Range minimum longitude.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setRangeMinLongitude(double dValue);

    /** \details
      Returns the range maximum longitude of this geodetic transformation definition.

      \param dValue [out] Range maximum longitude.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getRangeMaxLongitude(double& dValue) const;

    /** \details
      Sets the range maximum longitude to this geodetic transformation definition.
    
      \param dValue [in] Range maximum longitude.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setRangeMaxLongitude(double dValue);

    /** \details
      Returns the range minimum latitude of this geodetic transformation definition.

      \param dValue [out] Range minimum latitude.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getRangeMinLatitude(double& dValue) const;

    /** \details
      Sets the range minimum latitude to this geodetic transformation definition.
    
      \param dValue [in] Range minimum latitude.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setRangeMinLatitude(double dValue);

    /** \details
      Returns the range maximum latitude of this geodetic transformation definition.

      \param dValue [out] Range maximum latitude.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getRangeMaxLatitude(double& dValue) const;

    /** \details
      Sets the range maximum latitude to this geodetic transformation definition.

      \param dValue [in] Range maximum latitude.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setRangeMaxLatitude(double dValue);

    /** \details
      Returns the type of this geodetic transformation definition.

      \param eType [out] Transformation definition type.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getTransformationDefType(TransformationDefType& eType) const;

    /** \details
      Returns the geodetic transformation parameters of this geodetic transformation definition.

      \param pParameters [out] Pointer to an OdGeodeticTransformationParameters object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getParameters(OdGeodeticTransformationParametersPtr& pParameters) const;
    
    /** \details
      Sets the geodetic transformation parameters for this geodetic transformation definition.

      \param pParameters [in] Pointer to an OdGeodeticTransformationParameters object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setParameters(const OdGeodeticTransformationParameters* pParameters);

    /** \details
      Checks whether the specified code string is legal for geodetic transformation definition.

      \param sCode [in] Geodetic transformation definition code string.

      \returns true - if specified code string is valid.
    */
    static bool isLegalCode(const OdString& sCode);
    
    /** \details
      Checks whether the specified description string is legal for geodetic transformation definition.

      \param sDescription [in] Geodetic transformation definition description string.

      \returns true - if specified description string is valid.
    */
    static bool isLegalDescription(const OdString& sDescription);

    /** \details
      Checks whether the specified source string is legal for geodetic transformation definition.

      \param sSource [in] Geodetic transformation definition source string.

      \returns true - if specified source string is valid.
    */
    static bool isLegalSource(const OdString& sSource);

    /** \details
      Checks whether the specified group string is legal for geodetic transformation definition.

      \param sGroup [in] Geodetic transformation definition group string.

      \returns true - if specified group string is valid.
    */
    static bool isLegalGroup(const OdString& sGroup);
  };
}

#endif //_ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONDEFINITION_INCLUDED_
