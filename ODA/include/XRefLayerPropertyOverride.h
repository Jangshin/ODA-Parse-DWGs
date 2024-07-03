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

#pragma once
#include "DbObjectId.h"
class OdDbBlockReference;

/** \details
    Helper class to get/set xref layer overrides
    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdXRefLayerPropertyOverride
{
public:

  /** \details
     This enum type indicates which xref layer property is overridden in the host drawing
     It can be used to get/set specific property override of xref layer
     (The order corresponds to VISRETAINMODE control bits)
  */
  enum XRefLayerPropertyOverrideType
  {
    On = 0,
    Freeze,
    Lock,
    Plot,
    Color,
    Linetype,
    Lineweight,
    Transparency,
    PlotStyle,
    NewVPFreeze,
    Description
  };

  /** \details
   This function is to check whether the xref layer property is overridden or not in host drawing.
   If xdata flag is not found in the xref layer, we will use xref cache to compare the layer property from xref and current layer property in host drawing,
   and take it as overridden if they are different.
   If xdata is already added, then the bit coded data in xdata will be parsed to check whether the specified property is overridden or not
   \param hostLayerId [in] The xref layer record id in host drawing
   \param p [in] the enum value specifying which property to query
   \returns Returns true if the given property is overridden in xref layer (in host drawing)
   */
  static bool hasXRefLayerOverride(OdDbObjectId hostLayerId, XRefLayerPropertyOverrideType p);

  /** \details
   Shortcut of hasXrefLayerOverride, return true if any xref layer property override found in the xref layer
  \param hostLayerId [in] The xref layer id in the host drawing
  \returns returns true if any xref layer property override found in the layer
  */
  static bool hasAnyXRefLayerOverrides(OdDbObjectId hostLayerId);

  /** \details
  Shortcut of hasXrefLayerOverride, return true if any xref layer property override found in the host drawing
  \param pHostDb [in] The pointer to host drawing's database
  \returns return true if any xref layer property override found in the host drawing
  */
  static bool hasAnyXRefLayerOverrides(OdDbDatabase* pHostDb);

  /** \details
  Check whether the external reference has layer overrides
  \param pRef [in] The pointer to xref block reference
  \returns return true if the external reference has layer overrides
  */
  static bool hasXRefLayerOverride(OdDbBlockReference* pRef);

  /** \details
  This function is set which layer property is overridden in a xref layer (in host drawing)
  the flag is saved in xdata of xref layer with in the host drawing
  \param layerId [in] The xref layer id in the host drawing
  \param p [in] the enum value indicating which property to set
  */
  static void addXRefLayerOverride(OdDbObjectId hostLayerId, XRefLayerPropertyOverrideType p);
  
  /** \details
  This function is set which layer property is overridden in a xref layer (in host drawing)
  the flag is saved in xdata of xref layer with in the host drawing
  \param layer [in] The xref layer in the host drawing
  \param p [in] the enum value indicating which property to set
  */
  static void addXRefLayerOverride(OdDbObject* hostLayer, XRefLayerPropertyOverrideType p);

  /** \details
  This function is to turn off the flag in xref layer indicating which layer property will be overridden
  \param layerId [in] The xref layer record id in host drawing
  \param p [in] the enum value indicating which property to remove
   */
  static void removeXRefLayerOverride(OdDbObjectId hostLayerId, XRefLayerPropertyOverrideType p);

  /** \details
  shortcut of removeXRefLayerOverrides, remove specified layer property override in the whole drawing
  \param pHostDb [in] The pointer to host drawing's database
  \param p [in] the enum value indicating which property to remove
  */
  static void removeXRefLayerOverride(OdDbDatabase* pHostDb, XRefLayerPropertyOverrideType p);

  /** \details
  Shortcut of removeXRefLayerOverride, remove all xref layer property overrides
  \param layerId The xref layer id in the host drawing
  */
  static void removeXRefLayerOverrides(OdDbObjectId hostLayerId);

  /** \details
  shortcut of removeXRefLayerOverride, remove all xref layer property overrides in the whole drawing
  \param pHostDb [in] The pointer to host drawing's database
   */
  static void removeXRefLayerOverrides(OdDbDatabase* pHostDb);

  /** \details
  To enable xref layer override recording
  if override recording is enabled, then any modification on xref layer property will be automatically marked as an override,
  \remarks 
  By default the xref override recording is enabled
  (this is a global application flag)
  */
  static void enableXRefLayerPropertyOverrideRecording();

  /** \details
  To disable xref layer override recording
  if override recording is disabled, then the modification on xref layer property will *not* be automatically marked as an override
  xdata flag will *not* be added for this layer property in layer table record's xdata
  \remarks 
  By default the xref override recording is enabled
  (this is a global application flag)
  */
  static void disableXRefLayerPropertyOverrideRecording();

  /** \details
  To check whether xref layer override recording is enabled
  If override recording is enabled, then any modification on xref layer property will be automatically marked as an override
  (this is a global application flag)
  \returns return true if xref layer override recording is enabled, otherwise return false
  */
  static bool isXRefLayerPropertyOverrideRecordingEnabled();
};

