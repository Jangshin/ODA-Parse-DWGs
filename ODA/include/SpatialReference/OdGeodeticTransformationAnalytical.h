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
#ifndef _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONANALYTICAL_INCLUDED_
#define _ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONANALYTICAL_INCLUDED_

#include "OdGeodeticTransformationParameters.h"

namespace OdSpatialReference
{
  class OdGeodeticTransformationAnalyticalImpl;

  /** \details
    This class represents a geodetic transformation analytical parameters.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdGeodeticTransformationAnalytical : public OdGeodeticTransformationParameters
  {
    ODSPREF_RX_DECLARE_MEMBERS(OdGeodeticTransformationAnalytical);
  public:
    /** \details
      Returns method code of this geodetic transformation analytical parameters.

      \returns Returns Method code.
    */
    OdInt16 getMethodCode() const;

    /** \details
      Sets method code for this geodetic transformation analytical parameters.

      \param nMethodCode [in] Method code.
    */
    void setMethodCode(OdInt16 nMethodCode);

    /** \details
      Returns delta X of this geodetic transformation analytical parameters.

      \returns Returns Delta X.
    */
    double getDeltaX() const;

    /** \details
      Sets delta X for this geodetic transformation analytical parameters.

      \param dValue [in] Delta X.
    */
    void setDeltaX(double dValue);

    /** \details
      Returns delta Y of this geodetic transformation analytical parameters.

      \returns Returns Delta Y.
    */
    double getDeltaY() const;

    /** \details
      Sets delta Y for this geodetic transformation analytical parameters.

      \param dValue [in] Delta Y.
    */
    void setDeltaY(double dValue);

    /** \details
      Returns delta Z of this geodetic transformation analytical parameters.

      \returns Returns Delta Z.
    */
    double getDeltaZ() const;

    /** \details
      Sets delta Z for this geodetic transformation analytical parameters.

      \param dValue [in] Delta Z.
    */
    void setDeltaZ(double dValue);

    /** \details
      Returns rotate X of this geodetic transformation analytical parameters.

      \returns Returns Rotate X.
    */
    double getRotateX() const;

    /** \details
      Sets rotate X for this geodetic transformation analytical parameters.

      \param dValue [in] Rotate X.
    */
    void setRotateX(double dValue);

    /** \details
      Returns rotate Y of this geodetic transformation analytical parameters.

      \returns Returns Rotate Y.
    */
    double getRotateY() const;

    /** \details
      Sets rotate Y for this geodetic transformation analytical parameters.

      \param dValue [in] Rotate Y.
    */
    void setRotateY(double dValue);

    /** \details
      Returns rotate Z of this geodetic transformation analytical parameters.

      \returns Returns Rotate Z.
    */
    double getRotateZ() const;

    /** \details
      Sets rotate Z for this geodetic transformation analytical parameters.

      \param dValue [in] Rotate Z.
    */
    void setRotateZ(double dValue);

    /** \details
      Returns scale of this geodetic transformation analytical parameters.

      \returns Returns Scale.
    */
    double getScale() const;

    /** \details
      Sets scale for this geodetic transformation analytical parameters.

      \param dValue [in] Scale.
    */
    void setScale(double dValue);

    /** \details
      Returns Translate X for this geodetic transformation analytical parameters.

      \returns Returns Translate X.
    */
    double getTranslateX() const;

    /** \details
      Sets translate X for this geodetic transformation analytical parameters.

      \param dValue [in] Translate X.
    */
    void setTranslateX(double dValue);

    /** \details
      Returns Translate Y for this geodetic transformation analytical parameters.

      \returns Returns Translate Y.
    */
    double getTranslateY() const;

    /** \details
      Sets translate Y for this geodetic transformation analytical parameters.

      \param dValue [in] Translate Y.
    */
    void setTranslateY(double dValue);

    /** \details
      Returns Translate Z for this geodetic transformation analytical parameters.

      \returns Returns Translate Z.
    */
    double getTranslateZ() const;

    /** \details
      Sets translate Z for this geodetic transformation analytical parameters.

      \param dValue [in] Translate Z.
    */
    void setTranslateZ(double dValue);
  };
  typedef OdSmartPtr<OdGeodeticTransformationAnalytical> OdGeodeticTransformationAnalyticalPtr;
}

#endif //_ODSPATIALREFERENCE_ODGEODETICTRANSFORMATIONANALYTICAL_INCLUDED_
