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
#ifndef _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONINTERPOLATION_INCLUDED_
#define _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONINTERPOLATION_INCLUDED_

#include "OdGeodeticTransformationParameters.h"
#include "OdGridFile.h"

namespace OdSpatialReference
{
  class OdGeodeticTransformationInterpolationImpl;

  /** \details
    This class represents a geodetic transformation interpolation parameters.
    
    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdGeodeticTransformationInterpolation : public OdGeodeticTransformationParameters
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdGeodeticTransformationInterpolation);
  public:
    /** \details
      Returns the grid file array of this geodetic transformation interpolation parameters.

      \param arrGridFiles [out] Array of OdGridFile smartpointer objects.
    */
    void getGridFiles(OdGridFileArray& arrGridFiles) const;

    /** \details
      Sets the grid file array for this geodetic transformation interpolation parameters.
    
      \param arrGridFiles [in] Array of OdGridFile smartpointer objects.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setGridFiles(const OdGridFileArray& arrGridFiles);

    /** \details
      Returns the fallback of this geodetic transformation interpolation parameters.

      \param sFallback [out] Fallback.
    */
    void getFallback(OdString& sFallback) const;

    /** \details
      Sets the fallback for this geodetic transformation interpolation parameters.

      \param sFallback [in] Fallback.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setFallback(const OdString& sFallback);

    /** \details
      Checks whether the specified fallback string is legal for transformation interpolation parameters.
      
      \param sGroup [in] Transformation interpolation parameters fallback string.
      
      \returns true - if specified fallback string is valid.
    */
    static bool isLegalFallback(const OdString& sFallback);
  };
  typedef OdSmartPtr<OdGeodeticTransformationInterpolation> OdGeodeticTransformationInterpolationPtr;
}

#endif //_ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONINTERPOLATION_INCLUDED_
