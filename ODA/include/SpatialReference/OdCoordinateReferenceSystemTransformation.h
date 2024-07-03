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
#ifndef _ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMTRANSFORMATION_INCLUDED_
#define _ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMTRANSFORMATION_INCLUDED_

#include "OdCoordinateReferenceSystemDefinition.h"
#include "OdDatumShift.h"

namespace OdSpatialReference
{
  class OdCoordinateReferenceSystemTransformation;
  typedef OdSmartPtr<OdCoordinateReferenceSystemTransformation> OdCoordinateReferenceSystemTransformationPtr;

  class OdCoordinateReferenceSystemTransformationImpl;

  /** \details
    This class represents a coordinate reference system (CRS) transformation.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdCoordinateReferenceSystemTransformation : public OdRxObject
  {
    ODSPREF_RX_WITH_IMPL_DECLARE_MEMBERS(OdCoordinateReferenceSystemTransformation);
  public:
    /** \details
      Loads and returns coordinate reference system transformation.

      \param pCsSource [in] Pointer to the source OdCoordinateReferenceSystemDefinition object.
      \param pCsTarget [in] Pointer to the target OdCoordinateReferenceSystemDefinition object.
      \param pTransformation [out] Pointer to an OdCoordinateReferenceSystemTransformation object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdCoordinateReferenceSystemDefinition* pCsSource, const OdCoordinateReferenceSystemDefinition* pCsTarget, OdCoordinateReferenceSystemTransformationPtr & pTransformation);
    
    /** \details
      Loads and returns coordinate reference system transformation.

      \param sCodeSource [in] source code of coordinate reference system definition.
      \param sCodeTarget [in] target code of coordinate reference system definition.
      \param pTransformation [out] Pointer to an OdCoordinateReferenceSystemTransformation object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    static OdResult load(const OdString& sCodeSource, const OdString& sCodeTarget, OdCoordinateReferenceSystemTransformationPtr & pTransformation);

    /** \details
      Transforms (X,Y,Z) coordinate from source to target coordinate reference system definition.

      \param dX [in/out] X - coordinate of source CRS definition as input, X - coordinate of target CRS definition as output.
      \param dY [in/out] Y - coordinate of source CRS definition as input, Y - coordinate of target CRS definition as output.
      \param dZ [in/out] Z - coordinate of source CRS definition as input, Z - coordinate of target CRS definition as output.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult transform(double& dX, double& dY, double& dZ) const;

    /** \details
      Transforms (X,Y) coordinate from source to target coordinate reference system definition.
    
      \param dX [in/out] X - coordinate of source CRS definition as input, X - coordinate of target CRS definition as output.
      \param dY [in/out] Y - coordinate of source CRS definition as input, Y - coordinate of target CRS definition as output.
    
      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult transform(double& dX, double& dY) const;

    /** \details
      Transforms (X,Y,Z,M) coordinate from source to target coordinate reference system definition,
      for M - coordinate scale ratio between source/target CRS definitions is applied.

      \param dX [in/out] X - coordinate of source CRS definition as input, X - coordinate of target CRS definition as output.
      \param dY [in/out] Y - coordinate of source CRS definition as input, Y - coordinate of target CRS definition as output.
      \param dZ [in/out] Z - coordinate of source CRS definition as input, Z - coordinate of target CRS definition as output.
      \param dZ [in/out] M - coordinate of source CRS definition as input, M - coordinate of target CRS definition as output.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult transformM(double& dX, double& dY, double& dZ, double& dM) const;

    /** \details
      Transforms (X,Y,M) coordinate from source to target coordinate reference system definition,
      for M - coordinate scale ratio between source/target CRS definitions is applied.

      \param dX [in/out] X - coordinate of source CRS definition as input, X - coordinate of target CRS definition as output.
      \param dY [in/out] Y - coordinate of source CRS definition as input, Y - coordinate of target CRS definition as output.
      \param dZ [in/out] M - coordinate of source CRS definition as input, M - coordinate of target CRS definition as output.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult transformM(double& dX, double& dY, double& dM) const;

    /** \details
      Returns the source coordinate reference system definition of this coordinate reference system transformation object.

      \param pSource [out] Pointer to an OdCoordinateReferenceSystemDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getSource(OdCoordinateReferenceSystemDefinitionPtr& pSource) const;

    /** \details
      Returns the target coordinate reference system definition of this coordinate reference system transformation object.

      \param pTarget [out] Pointer to an OdCoordinateReferenceSystemDefinition object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getTarget(OdCoordinateReferenceSystemDefinitionPtr& pTarget) const;

    /** \details
      Returns the datum shift of this coordinate reference system transformation object.

      \param pDatumShift [out] Pointer to an OdDatumShift object.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getDatumShift(OdDatumShiftPtr& pDatumShift) const;
  };
}

#endif //_ODSPATIALREFERENCE_ODCOORDINATEREFERENCESYSTEMTRANSFORMATION_INCLUDED_
