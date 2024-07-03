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
#ifndef _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONMULTIPLEREGRESSION_INCLUDED_
#define _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONMULTIPLEREGRESSION_INCLUDED_

#include "OdGeodeticTransformationParameters.h"

namespace OdSpatialReference
{
  class OdGeodeticTransformationMultipleRegressionImpl;

  /** \details
    This class represents a geodetic transformation multiple regression parameters.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdGeodeticTransformationMultipleRegression : public OdGeodeticTransformationParameters
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdGeodeticTransformationMultipleRegression);
  public:
    /** \details
      Returns method code of this geodetic transformation multiple regression parameters.
    
      \returns Returns Method code.
    */
    OdInt16 getMethodCode() const;

    /** \details
      Sets method code for this geodetic transformation multiple regression parameters.

      \param nMethodCode [in] Method code.
    */
    void setMethodCode(OdInt16 nMethodCode);

    /** \details
      Returns delta phi of this geodetic transformation multiple regression parameters.

      \returns Returns Delta phi.
    */
    double getDeltaPhi() const;

    /** \details
      Sets delta phi for this geodetic transformation multiple regression parameters.

      \param dValue [in] Delta phi.
    */
    void setDeltaPhi(double dValue);

    /** \details
      Returns delta lambda of this geodetic transformation multiple regression parameters.

      \returns Returns Delta lambda.
    */
    double getDeltaLambda() const;

    /** \details
      Sets delta lambda for this geodetic transformation multiple regression parameters.

      \param dValue [in] Delta lambda.
    */
    void setDeltaLambda(double dValue);

    /** \details
      Returns delta height of this geodetic transformation multiple regression parameters.

      \returns Returns Delta height.
    */
    double getDeltaHeight() const;

    /** \details
      Sets delta height for this geodetic transformation multiple regression parameters.

      \param dValue [in] Delta height.
    */
    void setDeltaHeight(double dValue);

    /** \details
      Returns phi offset of this geodetic transformation multiple regression parameters.

      \returns Returns Phi offset.
    */
    double getPhiOffset() const;

    /** \details
      Sets phi offset for this geodetic transformation multiple regression parameters.

      \param dValue [in] Phi offset.
    */
    void setPhiOffset(double dValue);

    /** \details
      Returns lambda offset of this geodetic transformation multiple regression parameters.

      \returns Returns lambda offset.
    */
    double getLambdaOffset() const;

    /** \details
      Sets lambda offset for this geodetic transformation multiple regression parameters.

      \param dValue [in] Lambda offset.
    */
    void setLambdaOffset(double dValue);

    /** \details
      Returns normalization scale of this geodetic transformation multiple regression parameters.

      \returns Returns Normalization scale.
    */
    double getNormalizationScale() const;

    /** \details
      Sets normalization scale for this geodetic transformation multiple regression parameters.

      \param dValue [in] Normalization scale.
    */
    void setNormalizationScale(double dValue);

    /** \details
      Returns the coefficient phi value of this geodetic transformation multiple regression parameters.

      \param uIndex [in] Index in coefficient phi array (limited by 105 elements).
      \param dValue [out] Coefficient phi.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCoefficientPhi(OdUInt32 uIndex, double& dValue) const;

    /** \details
      Sets the coefficient phi value to this coordinate reference system definition.

      \param uIndex [in] Index in coefficient phi array (limited by 105 elements).
      \param dValue [in] Coefficient phi.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setCoefficientPhi(OdUInt32 uIndex, double dValue);

    /** \details
      Returns the coefficient lambda value of this geodetic transformation multiple regression parameters.

      \param uIndex [in] Index in coefficient lambda array (limited by 105 elements).
      \param dValue [out] Coefficient lambda.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCoefficientLambda(OdUInt32 uIndex, double& dValue) const;

    /** \details
      Sets the coefficient lambda value to this coordinate reference system definition.

      \param uIndex [in] Index in coefficient lambda array (limited by 105 elements).
      \param dValue [in] Coefficient lambda.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setCoefficientLambda(OdUInt32 uIndex, double dValue);

    /** \details
      Returns the coefficient height value of this geodetic transformation multiple regression parameters.

      \param uIndex [in] Index in coefficient height array (limited by 105 elements).
      \param dValue [out] Coefficient height.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult getCoefficientHeight(OdUInt32 uIndex, double& dValue) const;

    /** \details
      Sets the coefficient height value to this coordinate reference system definition.

      \param uIndex [in] Index in coefficient height array (limited by 105 elements).
      \param dValue [in] Coefficient height.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setCoefficientHeight(OdUInt32 uIndex, double dValue);

    /** \details
      Returns validation of this geodetic transformation multiple regression parameters.

      \returns Returns Validation.
    */
    double getValidation() const;

    /** \details
      Sets validation for this geodetic transformation multiple regression parameters.

      \param dValue [in] Validation.
    */
    void setValidation(double dValue);

    /** \details
      Returns test phi of this geodetic transformation multiple regression parameters.

      \returns Returns Test phi.
    */
    double getTestPhi() const;

    /** \details
      Sets test phi for this geodetic transformation multiple regression parameters.

      \param dValue [in] Test phi.
    */
    void setTestPhi(double dValue);

    /** \details
      Returns test lambda of this geodetic transformation multiple regression parameters.

      \returns Returns Test lambda.
    */
    double getTestLambda() const;

    /** \details
      Sets test lambda for this geodetic transformation multiple regression parameters.

      \param dValue [in] Test lambda.
    */
    void setTestLambda(double dValue);
  };
  typedef OdSmartPtr<OdGeodeticTransformationMultipleRegression> OdGeodeticTransformationMultipleRegressionPtr;
}

#endif //_ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONMULTIPLEREGRESSION_INCLUDED_
