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
// OdIesnaFile.h - interface for .ies file format reader module.

#ifndef _OD_IESNAFILE_H_INCLUDED_
#define _OD_IESNAFILE_H_INCLUDED_

#include "RxModule.h"
#include "RootExport.h"
#include "Gi/GiLightTraits.h"

#include "TD_PackPush.h"

class OdDbBaseHostAppServices;
class OdGiGeometry;

/** \details
  This class defines the interface for .ies file format.

 	Corresponding C++ library: TD_Root
  
  <group Other_Classes>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdIesnaFile : public OdRxObject
{
  public:
    /** \details
      Return vertical angles array.
    */
    virtual double *vertAngles() const = 0;
    /** \details
      Return number of vertical angles in array.
    */
    virtual OdInt32 numVertAngles() const = 0;
    /** \details
      Return horizontal angles array.
    */
    virtual double *horzAngles() const = 0;
    /** \details
      Return number of horizontal angles in array.
    */
    virtual OdInt32 numHorzAngles() const = 0;
    /** \details
      Return candela distribution arrays.
    */
    virtual double **candelaDistribution() const = 0;
    /** \details
      Return maximal candela value.
    */
    virtual double maxCandela() const = 0;
    /** \details
      Return type of .ies file.
    */
    virtual OdGiWebLightTraits::WebFileType fileType() const = 0;
    /** \details
      Return type of .ies file symmetry.
    */
    virtual OdGiWebLightTraits::WebSymmetry fileSymmetry() const = 0;
    /** \details
      Returns horizontal angle rotation flag.
    */
    virtual bool isHorzAng90To270() const = 0;

    /** \details
      Returns Lumens per lamp.
    */
    virtual double getLumensLamp() const = 0;

    /** \details
      Returns Candela multiplying factor.
    */
    virtual double getMultiplier() const = 0;

    /** \details
      Returns non-interpolated candela value for specified angles.
      \param theta [in]  Horizontal angle.
      \param phi [in]  Vertical angle.
    */
    virtual double getValue(double theta, double phi) const = 0;
    /** \details
      Returns interpolated candela value for specified angles.
      \param theta [in]  Horizontal angle.
      \param phi [in]  Vertical angle.
    */
    virtual double getValue_ipl(double theta, double phi) const = 0;

    /** \details
      Vectorize candela distribution as 3d wireframe mesh.
      \param pWD [in]  Geometry interface.
      \param scale [in]  Scaling factor.
      \interpolation [in]  Level of interpolation.
    */
    virtual void render(OdGiGeometry *pWD, double scale, OdInt32 interpolation = 0) const = 0;
};

typedef OdSmartPtr<OdIesnaFile> OdIesnaFilePtr;

/** \details
  This class defines the interface for .ies file format loading.

  Corresponding C++ library: TD_Root

  <group Other_Classes>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdIesnaLoader : public OdRxModule
{
  public:
    /** \details
      Read .ies file.
      \param pFileName [in]  Path to file with file name.
      \param pSvcs [in]  Find file functionality interface.
      \param pDb [in]  Optional database pointer for file finding.
      \returns OdIesnaFile pointer if file read correctly or nullptr if file reading error occurred.
    */
    virtual OdIesnaFilePtr load(const OdChar *pFileName, OdDbBaseHostAppServices *pSvcs, OdDbBaseDatabase *pDb = nullptr) = 0;

    /** \details
      Read stream buffer.
      \param pStreamBuf [in]  Stream buffer pointer.
      \param pSvcs [in]  Find file functionality interface.
      \param pDb [in]  Optional database pointer for file finding.
      \returns OdIesnaFile pointer if stream buffer read correctly or nullptr if file reading error occurred.
    */
    virtual OdIesnaFilePtr load(OdStreamBufPtr& pStreamBuf, OdDbBaseHostAppServices* pSvcs, OdDbBaseDatabase* pDb = nullptr) = 0;
};

typedef OdSmartPtr<OdIesnaLoader> OdIesnaLoaderPtr;

#include "TD_PackPop.h"

#endif // _OD_IESNAFILE_H_INCLUDED_
