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

#include "DbViewRepStandardInfo.h"
#include "Int32Array.h"
#include "odiv.h"
#include "Ge/GeCurve3dPtrArray.h"
#include <DbDatabase.h>

#include "TD_PackPush.h"

class OdDbDatabase;

using OdDbExtents = OdGeExtents3d;

using OdUInt64Array = OdArray<OdUInt64, OdMemoryAllocator<OdUInt64> >;

/**
 * <group OdModelDocObj_Classes>
 * 
 */
class OdSyDrawingMgr : public OdRxObject {
public:
  virtual bool attachTo(OdDbDatabase* pHostDb, bool bForceCreateNew = false, OdError* pIdwError = 0) = 0;
  virtual void detach() = 0;

  virtual bool isDirty() = 0;
  virtual void saveIdwInDwg(OdDbDatabase* pHostDb) = 0;
  virtual bool inheritViewStyle(OdUInt64 invViewId) = 0;
  virtual bool inheritSectionCut(OdUInt64 invViewId) = 0;
  virtual bool tangentEdgeVisibility(OdUInt64 invViewId) = 0;
  virtual bool interferenceEdgesVisibility(OdUInt64 invViewId) = 0;
  virtual bool foreshortened(OdUInt64 invViewId) = 0;
  virtual OdUInt32 getActiveSheetId() = 0;

  // Document
  virtual OdResult addNewDrawingDocument(OdString const& sheetName, bool b) = 0;
  virtual OdResult openCachedDrawingDoc(OdString const& fullFileName, bool openVisible) = 0;
  virtual OdResult saveDrawingDoc() = 0;
  virtual OdResult closeDrawingDoc(bool b) = 0;
  virtual OdResult setDocumentDirty(bool) = 0;
  virtual OdResult getDrawingDocName(OdString& fileName) = 0;
  virtual OdResult setDrawingDocName(OdString const& fileName) = 0;

  virtual OdResult getDrawingDocVersion(OdInt32& majorVer) = 0;
  virtual OdResult getDrawingDocDatabaseRevisionId(OdString& revisionId) = 0;
  virtual OdResult getFullDocumentName(OdString const& sFileName, OdString const& sLODName, OdString& sFullDocName) = 0;
  virtual OdResult refreshAllDocuments() = 0;
  virtual OdResult setAcadDWG(bool b) = 0;
  virtual OdResult isAcadDWG(bool& b) = 0;

  // Sheet
  virtual OdResult getActiveSheetId(OdUInt32& sheetID) = 0;
  virtual OdResult createSheet(OdDbObjectId, OdUInt32& sheetID) = 0;
  virtual OdResult activateSheet(OdUInt32 sheetID, OdUInt64Array const& viewIds) = 0;
  virtual OdResult deleteSheet(OdUInt32 sheetID, bool bRetainDepViews) = 0;
  virtual OdResult getSheetName(OdUInt32 sheetID, OdString& name) = 0;
  virtual OdResult getDrawingViews(OdUInt32 sheetID, OdUInt64Array& viewIds) = 0;

  // SelectionSet
  virtual OdResult addSelSet(OdUInt64 selSetId, OdUInt64Array const& selectedObjHandles) = 0;
  virtual OdResult updateSelSet(OdUInt64 selSetId, OdUInt64Array const& selectedObjHandles) = 0;
  virtual OdResult deleteSelSet(OdUInt64 selSetId) = 0;

  // Base + Projected
  virtual OdResult addBaseView(OdUInt32 sheet, odiv::ViewData const& viewData, OdUInt64& viewId) = 0;
  virtual OdResult addProjectedView(OdUInt64 viewId, odiv::ViewEnums::EViewRepZoneType zone, OdGePoint3d const& placementPoint, OdUInt64& projectedViewId) = 0;

  // Alignment
  virtual OdResult breakViewAlignment(OdUInt64 viewId) = 0;
  virtual OdResult createViewAlignment(OdUInt64 baseView, OdUInt64 dependentView, bool bIsHorizontal) = 0;

  // Edit
  virtual OdResult updateView(OdUInt64Array const& viewIds) = 0;
  virtual OdResult editView(OdUInt64 viewId, odiv::ViewData const& data) = 0;
  virtual OdResult moveView(OdUInt64 viewId, OdGePoint2d targetPosition) = 0;
  virtual OdResult rotateView(OdUInt64 viewId, double angle) = 0;
  virtual OdResult copyView(OdUInt32 sheetID, OdUInt64 srcViewId, OdUInt64& targetViewId) = 0;
  virtual OdResult deleteView(OdUInt64 viewId) = 0;

  OdResult getViewStandardSettings(OdDbDatabase* pDb, OdDbViewRepStandardInfo& viewSetting, bool& b1, bool& b2)
  {
    OdUInt32 iViewSetting;
    auto res = getViewStandardSetting(iViewSetting);
    if (res != eOk)
      return res;

    //viewSetting.dpiResolutionType;
    viewSetting.projectionType = iViewSetting & 0x1 ? OdDbViewRepStandard::kFirstAngle : OdDbViewRepStandard::kThirdAngle;
    viewSetting.sectionThreadEndDisplayType = iViewSetting & 0x2 ? OdDbViewRepStandard::kOpenedThreadEnd : OdDbViewRepStandard::kClosedThreadEnd;
    viewSetting.circularThreadEdgeDisplayType = iViewSetting & 0x4 ? OdDbViewRepStandard::kOpenedCircularThreadEdge : OdDbViewRepStandard::kClosedCircularThreadEdge;
    //viewSetting.previewDisplayType;
    //viewSetting.synergyVersion;
    b1 = GETBIT(iViewSetting, 0x8);
    b2 = ((iViewSetting & 0x10) != 0) != (pDb->getVIEWUPDATEAUTO() == 0);

    return res;
  }
  OdResult setViewStandardSettings(OdDbDatabase* pDb, const OdDbViewRepStandardInfo& viewSetting)
  {
    OdUInt32 iViewSetting = 0;
    iViewSetting |= viewSetting.projectionType == OdDbViewRepStandard::kFirstAngle ? 0x1 : 0x0;
    iViewSetting |= viewSetting.sectionThreadEndDisplayType == OdDbViewRepStandard::kOpenedThreadEnd ? 0x2 : 0x0;
    iViewSetting |= viewSetting.circularThreadEdgeDisplayType == OdDbViewRepStandard::kOpenedCircularThreadEdge ? 0x4 : 0x0;
    iViewSetting |= 0x8;
    iViewSetting |= pDb->getVIEWUPDATEAUTO() == 0 ? 0x10 : 0x0;
    return setViewStandardSetting(iViewSetting);
  }

  virtual OdResult getViewName(OdUInt64 viewId, OdString& name) = 0;
  virtual OdResult getDrawingViewDataById(OdUInt64, bool, odiv::ViewData&) = 0;
  virtual OdResult isViewDirty(OdUInt64, bool&) = 0;
  virtual OdResult setViewDirty(OdUInt64, bool) = 0;
  virtual OdResult setDrawingManualUpdate(bool b) = 0;
  virtual OdResult isDrawingManualUpdate(bool& b) = 0;
  virtual OdResult getViewStandardSetting(OdUInt32& viewSetting) = 0;
  virtual OdResult setViewStandardSetting(OdUInt32 viewSetting) = 0;
  virtual OdResult getViewCenterPoint(OdUInt64 viewId, OdGePoint2d& pt) = 0;
  virtual OdResult setViewCenterPoint(OdUInt64 viewId, OdGePoint3d const& pt) = 0;
  virtual OdResult isDrawingViewResolved(OdUInt64, bool&) = 0;
  virtual OdResult setShadedViewOption(OdUInt32 bgColor, int dpi) = 0;
  virtual OdResult getCameraInfoFromView(OdUInt64, OdGePoint3d&, OdGePoint3d&, OdGeVector3d&) = 0;
  virtual OdResult isViewScaleFromBase(OdUInt64 viewId, bool& b) = 0;
  virtual OdResult getViewScale(OdUInt64 viewId, double& dbScale) = 0;
  virtual OdResult getModelBBox(OdUInt64 viewId, OdDbExtents& minMaxPts) = 0;
//  virtual OdResult setViewCameraInfo(OdUInt64 viewId, enum OdDbViewRep::ViewOrientType viewOrientType, class OdDbViewRepCamera& cameraInfo) = 0;
//  virtual OdResult getHoleFeatureData(OdUInt64 viewId, OdUInt64 bodyId, OdDbEdgeRep const* varEdgeInfo, odiv::HoleFeatureData& featureData) = 0;
//  virtual OdResult getThreadFeatureData(OdUInt64 viewId, OdUInt64 bodyId, OdDbEdgeRep const* varEdgeInfo, odiv::ThreadFeatureData& featureData) = 0;

  // Detail
  virtual OdResult addDetailView(OdUInt64 parentView, odiv::ViewData const& viewData, OdGePoint3dArray const& boundary, OdUInt64& ppDetaiView) = 0;
  virtual OdResult editDetailView(OdUInt64 viewId, odiv::ViewData const& viewData) = 0;
  virtual OdResult editDetailViewBoundary(OdUInt64 viewId, OdGePoint3dArray const& boundary, odiv::ViewEnums::EDetailViewFenceType boundaryType, bool bUpdateViews) = 0;

  // Section + Sketch
  virtual OdResult createViewSketch(OdUInt64 viewId, OdGeCurve3dPtrArray const& sketchCurves, OdInt32Array const&, OdInt32Array const&, OdUInt32& sketchId) = 0;
  virtual OdResult editViewSketch(OdUInt64 viewId, OdGeCurve3dPtrArray const& sketchCurves, OdInt32Array const&, OdInt32Array const&, bool bUpdateViews) = 0;
  virtual OdResult isValidSketchForSectionView(OdGeCurve3dPtrArray const& sketchCurves, bool& isValid) = 0;
  virtual OdResult changeSectionParticipation(OdUInt64 viewId, OdUInt64Array const& pBodyIds, unsigned char participation, bool bNoBodyNoAHLCompute) = 0;
  virtual OdResult addSectionView(OdUInt64 parentView, OdUInt32 sketchId, odiv::ViewData const& sectionViewData, bool bViewDirectionLeft, OdUInt64& ppSectionView) = 0;
  virtual OdResult editSectionView(OdUInt64 viewId, odiv::ViewData const& data) = 0;
  virtual OdResult reverseSectionViewCutter(OdUInt64 viewId, bool&) = 0;

  // Body
  virtual OdResult passBodyOccInfoToIdw(odiv::DWGSynergyOccurrenceInfo const& info, OdString const& fileName) = 0;

  virtual OdResult setModelSpaceDirty(bool b) = 0;
  virtual OdResult isDWGBodyLoaded(bool& b) = 0;
  virtual OdResult loadDWGBody(OdString const& fileName) = 0;
  virtual OdResult isViewBodyStateDirty(OdUInt64 viewId, bool& b) = 0;
  virtual OdResult computeViewBodyOverrides(OdUInt64 viewId) = 0;
  virtual OdResult dumpViewBodyOverrides(OdUInt64 viewId, OdString const& sSOIFilePath, odiv::ASMVersion const& version) = 0;
  virtual OdResult getInvASMVersion(odiv::ASMVersion& version) = 0;
  virtual OdResult updateConfigurations() = 0;
  virtual OdResult fixupBodyOccInfo(OdString const& fileName) = 0;
//  virtual OdResult setBodyHiddenLines(OdUInt64 viewId, OdUInt64Array const& bodyIds, bool bShowHiddenLines, bool bNoBodyNoAHLCompute, enum OdDbViewRep::ViewStyleType&) = 0;

  // Constraint
//  virtual OdResult getCurve(OdSyIdwWrapper*, OdUInt64 viewId, OdInt32 constraintId, OdGeCurve3d*& curve) = 0;
  virtual OdResult addCurveConstraint(OdDbDatabase*, OdUInt32, OdUInt64 viewId, OdUInt64 bodyId, class OdDbEdgeRep const* edgeData, OdInt32& constraintId) = 0;
  virtual OdResult removeCurveConstraint(OdUInt64 viewId, OdInt32 constraintId) = 0;
  virtual OdResult getCurveConstraintStatus(OdUInt64 viewId, OdInt32 constraintId, odiv::ViewEnums::EConstraintStatus& status) = 0;
  virtual OdResult getEdgeIds(OdUInt64 viewId, OdInt32 constraintId, OdUInt64& pEdgeIds, OdInt32Array&) = 0;
  virtual OdResult setFaceId(OdUInt64 viewId, OdInt32 constraintId, OdInt32 faceId) = 0;
  virtual OdResult getBodyRevisionGuid(OdUInt64 viewId, OdUInt64 bodyId, OdInt32 constraintId, struct _GUID& pGuid) = 0;

  // Transactions
  virtual OdResult startTransaction(OdString const& transactionName, OdUInt32& transactionId) = 0;
  virtual OdResult abortTransaction(OdUInt32 transactionId) = 0;
  virtual OdResult endTransaction(OdUInt32 transactionId) = 0;
  virtual OdResult mergePreviousTransaction(OdUInt32 transactionId) = 0;
  virtual OdResult clearAllTransactions() = 0;

  // GlobalStyles
  virtual OdResult disableGlobalStyles(bool b) = 0;


  // Other
  virtual OdResult addMarshalInterThreadDrawingManager() = 0;
  virtual OdResult releaseMarshalInterThreadDrawingManager() = 0;
  virtual OdResult isConnectionAlive() = 0;
  virtual OdResult loadInventorServerDlls(void) = 0;
  virtual OdResult createViewShadedImage(OdUInt64 view, OdUInt32 color, int dpi, OdString const& fileName, OdDbExtents& minMaxPts, OdString& errString) = 0;
  virtual OdResult getUnresolvedFilesCount(OdUInt32& unresolvedFilesCount) = 0;
  virtual OdResult getOutOfDateReferences(OdUInt64Array const& viewIds, OdStringArray& ppResult) = 0;
  virtual OdResult getMemberFile(OdString const& factoryFileName, OdString const& memberRowName, OdString const& LODName, OdString& memberFileName) = 0;
  virtual OdResult getActiveInvProject(OdString& sFullDocName, bool&) = 0;
  virtual OdResult editInventorView(class OdDbViewRepInfo const*, OdUInt64) = 0;
  virtual OdResult syncShadedViewOptionToInventor(OdDbDatabase*, OdDbObjectId const&) = 0;
  virtual OdResult findCorrectSheet(OdDbObjectId, OdUInt32&, bool, OdUInt32) = 0;
#if 0
  virtual OdResult getProjectProperties(OdString const&*) = 0;
  virtual OdResult getModelRepInfos(OdString const& fileName, odiv::OdDbModelRepInfos& modelRepInfos_o) = 0;
  virtual OdResult getDrawingReferences(class std::vector<OdUInt32, class std::allocator<OdUInt32>> const& refdFileIds, class std::vector<odiv::DrawingReference, class std::allocator<odiv::DrawingReference>>& references_o) = 0;
  virtual OdResult getViewSourceDocInfo(OdString const& fileName, odiv::ViewSourceDocInfo& viewSourceDocInfo_o) = 0;
  virtual OdResult createInventorProjectedView(class OdDbViewRepInfo*, class OdSyIdwWrapper*, enum OdSynergyObj::ViewRepZoneType, OdUInt32, OdUInt64&) = 0;
#endif

  virtual OdResult PLAIN_updateView(OdUInt64 invViewId,
    const OdGePoint3d& eye, const OdGePoint3d& target, const OdGeVector3d& upVector,
    const OdGePoint3d& viewportCenter, const OdGePoint2d& viewportCropUR, const OdGePoint2d& viewportCropLL)
  { throw OdError(eNotImplemented); }
  virtual OdResult PLAIN_updateDetailBoundary(OdUInt64 invViewId,
    odiv::EDetailViewFenceType fenceType, const OdGePoint3d& fenceOrigin, const OdGePoint3dArray& fencePoints)
  { throw OdError(eNotImplemented); }
  virtual void PLAIN_setTangentEdgeVisibility(OdUInt64 invViewId, bool val) { throw OdError(eNotImplemented); }
  virtual void PLAIN_setForeshortened(OdUInt64 invViewId, bool val) { throw OdError(eNotImplemented); }
  virtual void PLAIN_setInterferenceEdgesVisibility(OdUInt64 invViewId, bool val) { throw OdError(eNotImplemented); }
  virtual void PLAIN_setInheritSections(OdUInt64 invViewId, bool val) { throw OdError(eNotImplemented); }
  virtual void PLAIN_setViewStyle(OdUInt64 invViewId, bool showHidden, bool shaded, bool fromParent) { throw OdError(eNotImplemented); }
  virtual odiv::ViewEnums::EAllowSectionParticipation PLAIN_getBodySectionParticipation(OdUInt64 invViewId, OdUInt64 bodyInstanceId) { throw OdError(eNotImplemented); }
  virtual void PLAIN_setBodySectionParticipation(OdUInt64 invViewId, OdUInt64 bodyInstanceId, odiv::ViewEnums::EAllowSectionParticipation val) { throw OdError(eNotImplemented); }

  virtual void PLAIN_importDataFromIdwDbStreams(OdDbDatabase* dwgDb) { throw OdError(eNotImplemented); }
  virtual void PLAIN_exportDataToIdwDbStreams(OdDbDatabase* dwgDb) { throw OdError(eNotImplemented); }
};

typedef OdSmartPtr<OdSyDrawingMgr> OdSyDrawingMgrPtr;

#include "TD_PackPop.h"
