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
#ifndef _ODSPATIALREFERENCE_ODCSDFORMATTER_INCLUDED_
#define _ODSPATIALREFERENCE_ODCSDFORMATTER_INCLUDED_

#include "OdCoordinateReferenceSystemDefinition.h"

namespace OdSpatialReference
{
  namespace OdCsdFormatter
  {
    /** \details
      Creates the dictionary XML string from array of OdDefinitionBase smartpointer objects.
    
      \param arrDefinitionBase [in] Array of OdDefinitionBase smartpointer objects.
      \param sResultXml [out] Resulted xml string.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult createXml(const OdDefinitionBaseArray& arrDefinitionBase, OdString& sResultXml);

    /** \details
      Creates the dictionary XML string from coordinate reference system definition.

      \param pCoordinateReferenceSystemDefinition [in] Pointer to an OdCoordinateReferenceSystemDefinition object.
      \param sResultXml [out] Resulted xml string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult createXml(const OdCoordinateReferenceSystemDefinition* pCoordinateReferenceSystemDefinition, OdString& sResultXml);
    
    /** \details
      Parses dictionary XML string and creates the array of OdDefinitionBase smartpointer objects.

      \param sXml [in] Dictionary XML string.
      \param arrDefinitionBase [out] Array of OdDefinitionBase smartpointer objects.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult parseXml(const OdString& sXml, OdDefinitionBaseArray& arrDefinitionBase);

    /** \details
      Parses dictionary XML string and creates the coordinate reference system definition object.

      \param sXml [in] Dictionary XML string.
      \param pCoordinateReferenceSystemDefinition [out] Pointer to an OdCoordinateReferenceSystemDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult parseXml(const OdString& sXml, OdCoordinateReferenceSystemDefinitionPtr& pCoordinateReferenceSystemDefinition);
  };
}

#endif //_ODSPATIALREFERENCE_ODCSDFORMATTER_INCLUDED_
