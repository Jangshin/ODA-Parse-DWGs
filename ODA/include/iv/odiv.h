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

#include "OdaDefs.h"
#include "OdArray.h"
#include "OdGUID.h"
#include "DbHandle.h"

#include "Ge/GePoint3d.h"
#include "Ge/GeMatrix3d.h"
#include "Ge/GeExtents3d.h"

#define STL_USING_VECTOR
#include "OdaSTL.h"

namespace odiv
{
  struct ASMVersion
  {
    unsigned int miMajor;
    unsigned int miMinor;
  };

  struct DWGBodyRecord
  {
    OdGUID bodyVer;
    OdDbHandle handle;
    OdGeExtents3d box;
  };
  using DWGBodyRecordArray = std::vector<DWGBodyRecord>;

  struct DWGBodyOccurrence
  {
    OdHandleArray path;
    OdDbHandle handle;
    OdGUID bodyVer;
    OdGeMatrix3d transform;
    enum Type : OdUInt32
    {
      kUnchanged = 1,
      kAdd = 2,
      kDelete = 3,
      kUpdate = 4,
    };
    Type type = kUnchanged;
  };
  using DWGBodyOccurrenceArray = std::vector<DWGBodyOccurrence>;

  struct DWGSynergyOccurrenceInfo
  {
    DWGBodyRecordArray records;
    DWGBodyOccurrenceArray occurrences;

    OdDb::MeasurementValue measurement = OdDb::kEnglish;
  };

  namespace ViewEnums
  {
    enum EConstraintStatus
    {
      kDefaultConstraintStatus = 0x0,
    };
    enum EAllowSectionParticipation
    {
      kDefaultAllowSectionParticipation = 0x0,
    };
    enum EDetailViewFenceType
    {
      kDefaultDetailViewFenceType = 0x2,

      kRectangularBoundary = 1,
      kCircularBoundary = 2,
    };
    enum EFrontViewPlane
    {
      kDefaultFrontViewPlane = 0x2,
    };
    enum EGroupType
    {
      kDefaultGroupType = 0x400000,
    };
    enum ERefAndNonRefTreatment
    {
      kDefaultRefAndNonRefTreatment = 0x0,
      kRefAndNonRefSeparate = 0,
      kRefAndNonRefCombine = 1,
    };
    enum ESectionConstrainTo
    {
      kDefaultSectionConstrainTo = 0x1,
    };
    enum ESectionParticipation
    {
      kDefaultSectionParticipation = 0x2,
    };
    enum ESectionStandardPartsSetting
    {
      kDefaultSectionStandardPartsSetting = 0x2,
      /* Standard parts should always be sectioned irrespective of the settings. */
      kAlwaysSectionStandardParts = 0,
      /* Standard parts should never be sectioned irrespective of the settings. */
      kNeverSectionStandardParts = 1,
      /* The drawing browser settings should be obeyed when sectioning standard parts. */
      kObeyBrowserSettingsSectionStandardParts = 2,
    };
    enum EViewRepZoneType
    {
      kZoneUndefined = -1,
      kZoneCenter = 0,
      kZoneRight = 1,
      kZoneTopRight = 2,
      kZoneTop = 3,
      kZoneTopLeft = 4,
      kZoneLeft = 5,
      kZoneBottomLeft = 6,
      kZoneBottom = 7,
      kZoneBottomRight = 8,
    };
    enum EViewJustification
    {
      kDefaultViewJustification = 0x0,
      kCenteredViewJustification = 0,
      kFixedViewJustification = 1,
    };
    enum EViewOrientType
    {
      kDefaultViewOrientType = 0x0,
    };
    enum EViewReferenceDataState
    {
      kDefaultViewReferenceDataState = 0x2,
    };
    enum EViewStyle
    {
      /* Value for constructor. */
      kDefaultViewStyle = 0x0,
      /* Shaded style with hidden lines. */
      kShadedHiddenLineDrawingViewStyle = 0,
      /* Hidden line style. */
      kHiddenLineDrawingViewStyle = 1,
      /* Hidden lines removed style. */
      kHiddenLineRemovedDrawingViewStyle = 2,
      /* Shaded style with hidden lines removed. */
      kShadedDrawingViewStyle = 3,
      /* Derive the style from the base view. */
      kFromBaseDrawingViewStyle = 4,

      kVisibleLines = 0,
      kVisibleAndHiddenLines = 1,
      kShadedVisibleLines = 2,
      kShadedVisibleAndHiddenLines = 3,
    };
    enum EViewType
    {
      kDefaultViewType = 0x0,
      kBaseViewType = 0,
      kUnkViewType = 1,
      kDetailViewType = 2,
      kSectionViewType = 3,
      kProjectedViewType = 4,
    };
  };

  using namespace ViewEnums;

  class ViewData
  {
  public:
    enum Flags : uint64_t
    {
      kShaded = 0x1,
      kShowTangentEdges = 0x2,
      kForeshortened = 0x4,
      kShowInterferenceEdges = 0x8,
      kCustomView = 0x10,
      kCustomViewDirty = 0x20,
      kLabelVisibility = 0x40,
      kGetWeldSymbols = 0x80,
      kShowTrails = 0x100,
      kDisplayThreadFeatures = 0x200,
      kDisplayWeldCosmetics = 0x400,
      kDisplayWorkFeatures = 0x800,
      kBendEdges = 0x1000,
      kDeferUpdate = 0x2000,
      kUnk0x4000 = 0x4000,
      kCustomScaleString = 0x8000,
      kUnk0x10000 = 0x10000,
      kDisplayPunchCenter = 0x20000,
      kPreviewAllComponents = 0x40000,
      kWantFlatPattern = 0x80000,
      kAssociativeView = 0x100000,
      kUnk0x200000 = 0x200000,
      kGetDimensions = 0x400000,
      kIsEditing = 0x800000,
      kInheritStyle = 0x1000000,
      kInheritScale = 0x2000000,
      kShowHatch = 0x4000000,
      kAlignToBase = 0x8000000,
      kShowDefinitionInBaseView = 0x10000000,
      kSwizzlePartslists = 0x20000000,
      kInheritBreaksFromParent = 0x40000000,
      kInheritBreakoutsFromParent = 0x80000000,
#ifndef SWIG
      kInheritSectionsFromParent = 0x100000000ull,
      kInheritSliceFromParent = 0x200000000ull,
      kOrientToParent = 0x400000000ull,
      kUnk0x800000000 = 0x800000000ull,
      kIsRasterViewOnly = 0x1000000000ull,
      kSectionMethodAligned = 0x2000000000ull,
      kSectionFullDepth = 0x4000000000ull,
      kJagged = 0x8000000000ull,
      kIncludeSurfaces = 0x10000000000ull,
      kIncludeMeshes = 0x20000000000ull,
      kCopiedView = 0x40000000000ull,
#else
      kInheritSectionsFromParent = 0x100000000ul,
      kInheritSliceFromParent = 0x200000000ul,
      kOrientToParent = 0x400000000ul,
      kUnk0x800000000 = 0x800000000ul,
      kIsRasterViewOnly = 0x1000000000ul,
      kSectionMethodAligned = 0x2000000000ul,
      kSectionFullDepth = 0x4000000000ul,
      kJagged = 0x8000000000ul,
      kIncludeSurfaces = 0x10000000000ul,
      kIncludeMeshes = 0x20000000000ul,
      kCopiedView = 0x40000000000ul,
#endif
      kDefault = (
        kInheritSliceFromParent |
        kInheritSectionsFromParent |
        kInheritBreakoutsFromParent |
        kInheritBreaksFromParent |
        kShowDefinitionInBaseView |
        kShowHatch |
        kInheritScale |
        kUnk0x200000 |
        kDisplayThreadFeatures |
        kShowTrails),
    };

    union
    {
    Flags flags = kDefault;
    uint64_t m_flags;
    };


    // Camera
    OdGePoint3d eye;
    OdGePoint3d target;
    OdGeVector3d upVector;
    OdGePoint3d center;

    OdString label;
    OdString fullFileName;
    OdString designView;
    OdString LOD;
    OdString memberName;
    OdString positionalName;
    OdString presentationView;
    OdString weldInstanceName;

    double scale = 1.0;
    double referenceMargin = 0.0;
    double sectionDepth = 0.0;

    int weldInstanceId = 0;
    ESectionParticipation sectionParticipation = kDefaultSectionParticipation;
    ESectionConstrainTo sectionConstrainTo = kDefaultSectionConstrainTo;
    EDetailViewFenceType boundaryType = kDefaultDetailViewFenceType;
    EFrontViewPlane viewFrontPlane = kDefaultFrontViewPlane;
    EViewStyle viewStyleType = kDefaultViewStyle;
    ERefAndNonRefTreatment refAndNonRefTreatment = kDefaultRefAndNonRefTreatment;
    int unk = 0;
    ESectionStandardPartsSetting sectionStandardPartsSetting = kDefaultSectionStandardPartsSetting;
    EViewJustification viewJustification = kDefaultViewJustification;
    EViewType viewType = kDefaultViewType;
    EViewOrientType viewOrientType = kDefaultViewOrientType;
    EGroupType weldmentGroup = kDefaultGroupType;
    EViewReferenceDataState refDataState = kDefaultViewReferenceDataState;
  };

  namespace DVO
  {
    struct featureId
    {
      unsigned int id0;
      unsigned int id1;
    };
    struct ThreadInfo
    {
      odiv::ASMVersion mVersion;
      OdArray<odiv::DVO::featureId> maFutureIds;
      OdGePoint3d mptPoint;
      OdGeVector3d mvVector;
    };
  };
}
