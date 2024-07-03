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
#ifndef _ODSPATIALREFERENCE_ODGEODETICPATHDEFINITION_INCLUDED_
#define _ODSPATIALREFERENCE_ODGEODETICPATHDEFINITION_INCLUDED_

#include "OdDefinitionBase.h"
#include "OdGeodeticPathElement.h"

namespace OdSpatialReference
{
  class OdGeodeticPathDefinition;
  typedef OdSmartPtr<OdGeodeticPathDefinition> OdGeodeticPathDefinitionPtr;
  typedef OdArray<OdGeodeticPathDefinitionPtr> OdGeodeticPathDefinitionArray;

  class OdGeodeticPathDefinitionImpl;
  
  /** \details
    This class represents a geodetic path definition.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdGeodeticPathDefinition : public OdDefinitionBase
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdGeodeticPathDefinition);
  public:
    /** \details
      Loads and returns geodetic path definition.

      \param sCode [in] geodetic path code.
      \param pGeodeticPathDefinition [out] Pointer to an OdGeodeticPathDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString & sCode, OdGeodeticPathDefinitionPtr& pGeodeticPathDefinition);
    
    /** \details
      Loads and returns all geodetic path definitions.

      \param arrGeodeticPathDefinition [out] Array of pointers to returned geodetic path definitions.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult loadAll(OdGeodeticPathDefinitionArray& arrGeodeticPathDefinition);

    /** \details
      Returns the source datum of this geodetic path definition.

      \param sSourceDatum [out] Source datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getSourceDatum(OdString& sSourceDatum) const;

    /** \details
      Sets the source datum to this geodetic path definition.

      \param sSourceDatum [in] Source datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setSourceDatum(const OdString& sSourceDatum);

    /** \details
      Returns the target datum of this geodetic path definition.

      \param sTargetDatum [out] Target datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getTargetDatum(OdString& sTargetDatum) const;

    /** \details
      Sets the target datum to this geodetic path definition.

      \param sTargetDatum [in] Target datum code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setTargetDatum(const OdString& sTargetDatum);

    /** \details
      Returns the reversible flag for this geodetic path definition which if true means that all
      geodetic path elements are reversible.

      \param bIsReversible [out] If true - all geodetic path elements are reversible.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getIsReversible(bool& bIsReversible) const;

    /** \details
      Sets the reversible flag for this geodetic path definition which if true means that all
      geodetic path elements are reversible.

      \param bIsReversible [in] If true - all geodetic path elements are reversible.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setIsReversible(bool bIsReversible);

    /** \details
      Returns the path elements array of this geodetic path definition.

      \param arrPathElements [out] Array of OdGeodeticPathElement smartpointer objects.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getPathElements(OdGeodeticPathElementArray& arrPathElements) const;

    /** \details
      Sets the path elements array for this geodetic path definition.

      \param arrPathElements [in] Array of OdGeodeticPathElement smartpointer objects.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setPathElements(const OdGeodeticPathElementArray& arrPathElements);

    /** \details
      Returns the group string of this geodetic path definition.

      \param sGroup [out] Group string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getGroup(OdString& sGroup) const;

    /** \details
      Sets the group string to this geodetic path definition.

      \param sGroup [in] Group string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setGroup(const OdString& sGroup);

    /** \details
      Returns the accuracy of this geodetic path definition.

      \param dAccuracy [out] Accuracy.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getAccuracy(double& dAccuracy) const;

    /** \details
      Sets the accuracy to this geodetic path definition.

      \param dAccuracy [in] Accuracy.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setAccuracy(double dAccuracy);

    /** \details
      Returns the EPSG number of this geodetic path definition.

      \param nEpsgCode [out] EPSG number.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEpsgCode(OdInt16& nEpsgCode) const;

    /** \details
      Sets the EPSG number to this geodetic path definition.

      \param nEpsgCode [in] EPSG number.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEpsgCode(OdInt16 nEpsgCode);
    
    /** \details
      Returns the EPSG variant of this geodetic path definition.

      \param nEpsgVariant [out] EPSG variant.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getEpsgVariant(OdInt16& nEpsgVariant) const;

    /** \details
      Sets the EPSG variant to this geodetic path definition.

      \param nEpsgVariant [in] EPSG variant.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setEpsgVariant(OdInt16 nEpsgVariant);

    /** \details
      Checks whether the specified code string is legal for geodetic path definition.

      \param sCode [in] Geodetic path definition code string.

      \returns true - if specified code string is valid.
    */
    static bool isLegalCode(const OdString& sCode);

    /** \details
      Checks whether the specified description string is legal for geodetic path definition.

      \param sDescription [in] Geodetic path definition description string.

      \returns true - if specified description string is valid.
    */
    static bool isLegalDescription(const OdString& sDescription);

    /** \details
      Checks whether the specified source string is legal for geodetic path definition.

      \param sSource [in] Geodetic path definition source string.

      \returns true - if specified source string is valid.
    */
    static bool isLegalSource(const OdString& sSource);

    /** \details
      Checks whether the specified group string is legal for geodetic path definition.

      \param sGroup [in] Geodetic path definition group string.

      \returns true - if specified group string is valid.
    */
    static bool isLegalGroup(const OdString& sGroup);
  };
}

#endif //_ODSPATIALREFERENCE_ODGEODETICPATHDEFINITION_INCLUDED_
