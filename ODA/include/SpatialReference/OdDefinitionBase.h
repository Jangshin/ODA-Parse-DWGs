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
#ifndef _ODSPATIALREFERENCE_ODDEFINITIONBASE_INCLUDED_
#define _ODSPATIALREFERENCE_ODDEFINITIONBASE_INCLUDED_

#include "OdSpatialReference.h"

namespace OdSpatialReference
{
  /** \details
    This enumeration indicates the type of a OdDefinitionBase object.
  */
  enum DefinitionType
  {
    kUnknown = 0,
    kEllipsoid,
    kDatum,
    kCoordinateReferenceSystem,
    kGeodeticTransformation,
    kGeodeticPath,
    kCategory
  };

  class OdDefinitionBaseImpl;

  /** \details
    This class is the base class for definition classes.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdDefinitionBase : public OdRxObject
  {
    ODSPREF_RX_WITH_IMPL_DECLARE_MEMBERS(OdDefinitionBase);
  public:
    /** \details
     Initializes or resets definition data to initial values.

     \param bReset [in] If true - the definition data will be reset to initial values regardless of whether this definition data is initialized or not.
   */
    void initialize(bool bReset = false);

    /** \details
      Adds or updates data of this definition in its dictionary.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult update();

    /** \details
      Removes data of this definition from its dictionary.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult remove();

    /** \details
      Returns the type of base definition.

      \returns Returns the DefinitionType of base definition.
    */
    DefinitionType getDefinitionType() const;
    
    /** \details
      Returns the code of base definition.

      \param sCode [out] Code of base definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCode(OdString& sCode) const;

    /** \details
      Sets the code of base definition.

      \param sCode [in] Code of base definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setCode(const OdString & sCode);

    /** \details
      Returns the description of base definition.

      \param sDescription [out] Description of base definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getDescription(OdString& sDescription) const;

    /** \details
      Sets the description of base definition.

      \param sDescription [in] Description of base definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setDescription(const OdString & sDescription);
    
    /** \details
      Returns the source of base definition.

      \param sSource [out] Source of base definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getSource(OdString& sSource) const;

    /** \details
      Sets the source of base definition.

      \param sSource [in] Source of base definition.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setSource(const OdString & sSource);

    virtual void copyFrom(const OdRxObject* pSource) ODRX_OVERRIDE;
  };
  typedef OdSmartPtr<OdDefinitionBase> OdDefinitionBasePtr;
  typedef OdArray<OdDefinitionBasePtr> OdDefinitionBaseArray;
}

#endif //_ODSPATIALREFERENCE_ODDEFINITIONBASE_INCLUDED_
