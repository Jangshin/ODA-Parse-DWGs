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
#ifndef _ODSPATIALREFERENCE_ODCATEGORYDEFINITION_INCLUDED_
#define _ODSPATIALREFERENCE_ODCATEGORYDEFINITION_INCLUDED_

#include "OdDefinitionBase.h"

/**
 * <group TD_Namespaces>
 */
namespace OdSpatialReference
{
  class OdCategoryDefinition;
  typedef OdSmartPtr<OdCategoryDefinition> OdCategoryDefinitionPtr;
  typedef OdArray<OdCategoryDefinitionPtr> OdCategoryDefinitionArray;

  class OdCategoryDefinitionImpl;

  /** \details
    This class represents a category definition which holds string identifiers referring to 
    coordinate reference systems.
    
    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdCategoryDefinition : public OdDefinitionBase
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdCategoryDefinition);
  public:
    /** \details
      Loads and returns coordinate system category definition.

      \param sCode [in] Category definition code.
      \param pCategoryDefinition [out] Pointer to an OdCategoryDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString& sCode, OdCategoryDefinitionPtr& pCategoryDefinition);

    /** \details
      Loads and returns all coordinate system category definitions.

      \param arrCD [out] Array of pointers to returned category definitions.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult loadAll(OdCategoryDefinitionArray& arrCD);

    /** \details
      Loads and returns all coordinate system category definitions that contains specified coordinate system.
    
      \param sCsCode [in] Coordinate system code.
      \param arrCD [out] Array of pointers to returned category definitions.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult loadAll(const OdString& sCsCode, OdCategoryDefinitionArray& arrCD);

    /** \details
      Returns the count of coordinate systems that belong to this category.
    
      \param uCount [out] Count of coordinate systems.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCount(OdUInt32 & uCount) const;

    /** \details
      Returns the coordinate system code at the specified index.
      
      \param uIndex [in] Index.
      \param sCode [out] Coordinate system code.
      
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getAt(OdUInt32 uIndex, OdString& sCode) const;

    /** \details
      Add the coordinate system to current category definition.

      \param sCode [in] Coordinate system code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult add(const OdString& sCode);

    /** \details
      Remove the coordinate system from current category definition.

      \param sCode [in] Coordinate system code.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult remove(const OdString& sCode);

    /** \details
      Clear coordinate system list of current category definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult clear();
    
    /** \details
      Checks whether the coordinate system belongs to current category definition.

      \param sCode [in] Coordinate system code.
      \param bContains [out] True - if category definition contains input coordinate system.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult contains(const OdString& sCode, bool & bContains) const;

    /** \details
      Checks whether the specified code string is legal for category definition.

      \param sCode [in] Category definition code string.

      \returns true - if specified code string is valid.
    */
    static bool isLegalCode(const OdString& sCode);

    using OdDefinitionBase::remove;
  };
}

#endif //_ODSPATIALREFERENCE_ODCATEGORYDEFINITION_INCLUDED_
