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
// Viewport background definition

#ifndef ODTRVISBACKGROUNDDEF
#define ODTRVISBACKGROUNDDEF

#include "TrVisMetafileDef.h"

#include "TD_PackPush.h"

/** \details
    <group ExRender_Windows_Classes> 
*/
struct OdTrVisBackgroundDef
{
  // Flags
  enum Flags
  {
    // Enable background.
    kEnableBackground = (1 << 0),
    // Link background to camera.
    kCameraBackground = (1 << 1),
    // Background invoke materials.
    kShadedBackground = (1 << 2),
    // Camera angle override enabled.
    kFOVOverride      = (1 << 3)
  };
  // Background flags
  OdUInt16 m_flags;
  // Background stream
  OdTrVisFlatMetafileContainerPtr m_pStream;
  // Background shading program
  OdTrVisProgramId m_baseProgramId;
  // Background rotation (camera backgrounds)
  double m_longRot, m_latRot;
  // Camera field of view (camera backgrounds)
  double m_fovAngle, m_bkgndRad;

  void resetFlags(OdUInt16 nFlags = 0)
  {
    m_flags = nFlags;
  }
  void setDefault()
  {
    resetFlags();
    m_pStream = nullptr;
    m_baseProgramId = kTrVisNegativeId;
    m_longRot = m_latRot = 0.0;
    m_fovAngle = OdaToRadian(45.0);
    m_bkgndRad = 0.0;
  }

  void enableBackground(bool bSet) { SETBIT(m_flags, kEnableBackground, bSet); }
  bool isBackgroundEnabled() const { return GETBIT(m_flags, kEnableBackground); }

  void linkBackgroundToCamera(bool bSet) { SETBIT(m_flags, kCameraBackground, bSet); }
  bool isBackgroundLinkedToCamera() const { return GETBIT(m_flags, kCameraBackground); }

  void setShadedBackground(bool bSet) { SETBIT(m_flags, kShadedBackground, bSet); }
  bool isShadedBackground() const { return GETBIT(m_flags, kShadedBackground); }

  void enableFOVOverride(bool bSet) { SETBIT(m_flags, kFOVOverride, bSet); }
  bool isFOVOverridden() const { return GETBIT(m_flags, kFOVOverride); }

  void setBackgroundStream(const OdTrVisFlatMetafileContainerPtr pStream) { m_pStream = pStream; }
  OdTrVisFlatMetafileContainerPtr backgroundStream() const { return m_pStream; }
  bool hasBackgroundStream() const { return !m_pStream.isNull(); }

  void setBaseProgramId(OdTrVisProgramId baseProgramId) { m_baseProgramId = baseProgramId; }
  OdTrVisProgramId baseProgramId() const { return m_baseProgramId; }
  bool hasBaseProgramId() const { return ::isValidTrVisId(m_baseProgramId); }

  void setCameraRotationAngles(double longRot, double latRot) { m_longRot = longRot; m_latRot = latRot; }
  void cameraRotationAngles(double &longRot, double &latRot) const { longRot = m_longRot; latRot = m_latRot; }
  double longitudeRotationAngle() const { return m_longRot; }
  double latitudeRotationAngle() const { return m_latRot; }

  void setFOVOverrideAngle(double fovAngle) { m_fovAngle = fovAngle; }
  double fovOverrideAngle() const { return m_fovAngle; }

  void setBackgroundRadius(double bkgndRad) { m_bkgndRad = bkgndRad; }
  double backgroundRadius() const { return m_bkgndRad; }

  bool operator ==(const OdTrVisBackgroundDef &bkgnd) const
  {
    if (isBackgroundEnabled() != bkgnd.isBackgroundEnabled())
      return false;
    if (!isBackgroundEnabled())
      return true;
    return (isBackgroundLinkedToCamera() == bkgnd.isBackgroundLinkedToCamera()) &&
           (isShadedBackground() == bkgnd.isShadedBackground()) &&
           (isFOVOverridden() == bkgnd.isFOVOverridden()) &&
           (backgroundStream().get() == bkgnd.backgroundStream().get()) &&
           (baseProgramId() == bkgnd.baseProgramId()) &&
           OdEqual(longitudeRotationAngle(), bkgnd.longitudeRotationAngle()) &&
           OdEqual(latitudeRotationAngle(), bkgnd.latitudeRotationAngle()) &&
           (!isFOVOverridden() || OdEqual(fovOverrideAngle(), bkgnd.fovOverrideAngle())) &&
           OdEqual(backgroundRadius(), bkgnd.backgroundRadius());
  }
  bool operator !=(const OdTrVisBackgroundDef &bkgnd) const
  {
    if (isBackgroundEnabled() != bkgnd.isBackgroundEnabled())
      return true;
    if (!isBackgroundEnabled())
      return false;
    return (isBackgroundLinkedToCamera() != bkgnd.isBackgroundLinkedToCamera()) ||
           (isShadedBackground() != bkgnd.isShadedBackground()) ||
           (isFOVOverridden() != bkgnd.isFOVOverridden()) ||
           (backgroundStream().get() != bkgnd.backgroundStream().get()) ||
           (baseProgramId() != bkgnd.baseProgramId()) ||
           !OdEqual(longitudeRotationAngle(), bkgnd.longitudeRotationAngle()) ||
           !OdEqual(latitudeRotationAngle(), bkgnd.latitudeRotationAngle()) ||
           (isFOVOverridden() && !OdEqual(fovOverrideAngle(), bkgnd.fovOverrideAngle())) ||
           !OdEqual(backgroundRadius(), bkgnd.backgroundRadius());
  }

  static bool compareNoStream(const OdTrVisBackgroundDef &bkgnd1, const OdTrVisBackgroundDef &bkgnd2)
  { OdTrVisFlatMetafileContainerPtr pStream1 = bkgnd1.backgroundStream(), pStream2 = bkgnd2.backgroundStream();
    const_cast<OdTrVisBackgroundDef&>(bkgnd1).setBackgroundStream(NULL); const_cast<OdTrVisBackgroundDef&>(bkgnd2).setBackgroundStream(NULL);
    const bool bRVal = bkgnd1 == bkgnd2;
    const_cast<OdTrVisBackgroundDef&>(bkgnd1).setBackgroundStream(pStream1); const_cast<OdTrVisBackgroundDef&>(bkgnd2).setBackgroundStream(pStream2);
    return bRVal;
  }
};

#include "TD_PackPop.h"

#endif // ODTRVISBACKGROUNDDEF
