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
#ifndef _ODSPATIALREFERENCE_ODFORMATCONVERTER_INCLUDED_
#define _ODSPATIALREFERENCE_ODFORMATCONVERTER_INCLUDED_

#include "OdCoordinateReferenceSystemDefinition.h"

namespace OdSpatialReference
{
  /** \details
    This enumeration represents the coordinate reference system id type.
  */
  enum CodeFormatType
  {
    kCodeFrmtMentor = 0,
    kCodeFrmtEpsg = 1
  };

  /** \details
    This enumeration represents the flavor of WKT string.
  */
  enum WktFlavor
  {
    kWktFlvrNone = 0,
    kWktFlvrOgc,
    kWktFlvrGeoTiff,
    kWktFlvrEsri,
    kWktFlvrOracle,
    kWktFlvrGeoTools,
    kWktFlvrEpsg,
    kWktFlvrOracle9,
    kWktFlvrAutodesk,
    kWktFlvrUnknown,
    kWktFlvrAppAlt,
    kWktFlvrLclAlt,
    kWktFlvrLegacy
  };

  namespace FormatConverter
  {
    /** \details
      Converts the coordinate reference system id to desired format type.

      \param eCodeFormatTypeSource [in] CodeFormatType of input coordinate reference system id.
      \param sIdSource [in] Input source coordinate reference system id.
      \param eCodeFormatType [in] CodeFormatType of result coordinate reference system id.
      \param sId [out] Result coordinate reference system id.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult idToId(CodeFormatType eCodeFormatTypeSource, const OdString& sIdSource, CodeFormatType eCodeFormatType, OdString& sId);
    
    /** \details
      Converts the coordinate reference system id to desired WTK string.

      \param eCodeFormatTypeSource [in] CodeFormatType of input coordinate reference system id.
      \param sIdSource [in] Input source coordinate reference system id.
      \param eWktFlavor [in] WktFlavor of result WKT string.
      \param sWkt [out] Result WKT string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult idToWkt(CodeFormatType eCodeFormatTypeSource, const OdString& sIdSource, WktFlavor eWktFlavor, OdString& sWkt);

    /** \details
      Converts the coordinate reference system definition to desired WTK string.

      \param pCRSD [in] Pointer to an OdCoordinateReferenceSystemDefinition object.
      \param eWktFlavor [in] WktFlavor of result WKT string.
      \param sWkt [out] Result WKT string.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult definitionToWkt(const OdCoordinateReferenceSystemDefinition * pCRSD, WktFlavor eWktFlavor, OdString& sWkt);
    
    /** \details
      Converts the WKT string to coordinate reference system id.

      \param eWktFlavorSource [in] WktFlavor of input WKT string.
      \param sWkt [in] Input WKT string.
      \param eCodeFormatType [in] CodeFormatType of result coordinate reference system id.
      \param sId [out] Result coordinate reference system id.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult wktToId(WktFlavor eWktFlavorSource, const OdString& sWkt, CodeFormatType eCodeFormatType, OdString& sId);

    /** \details
      Converts the WKT string to OdCoordinateReferenceSystemDefinition object.

      \param eWktFlavor [in] WktFlavor of input WKT string.
      \param sWkt [in] Input WKT string.
      \param pCRSD [out] Pointer to an OdCoordinateReferenceSystemDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult wktToDefinition(WktFlavor eWktFlavor, const OdString& sWkt, OdCoordinateReferenceSystemDefinitionPtr& pCRSD);
    
    /** \details
      Converts the coordinate reference system id or WKT string to OdCoordinateReferenceSystemDefinition object.

      \param sIdOrWkt [in] Coordinate reference system id or WKT string.
      \param pCRSD [out] Pointer to an OdCoordinateReferenceSystemDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    TD_SPATIALREFERENCE_API OdResult getCoordinateReferenceSystemDefinition(const OdString& sIdOrWkt, OdCoordinateReferenceSystemDefinitionPtr& pCRSD);
  }
}

#endif //_ODSPATIALREFERENCE_ODFORMATCONVERTER_INCLUDED_
