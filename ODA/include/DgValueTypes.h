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


#ifndef _DGVALUETYPES_H_INCLUDED_
#define _DGVALUETYPES_H_INCLUDED_

#include "DbRootValueTypes.h"
#include "DgElementId.h"
#include "DgElement.h"
#include "DgGraphicsElement.h"
#include "RxValueType.h"
#include "DgHatchPattern.h"
#include "DgItemTypeLibrary.h"
#include "RxAttribute.h"
#include "DgLineStyleInfo.h"
#include "DgCommonStructs.h"
#include "DgDatabase.h"
#include "DgLevelTableRecord.h"
#include "DgLevelFilterTableRecord.h"
#include "DgMultilineStyleTableRecord.h"
#include "DgGeoData.h"
#include "DgText.h"
#include "DgReferenceAttach.h"
#include "Ge/GeEllipArc3d.h"
#include "DgNamedGroup.h"
#include "DgDetailingSymbol.h"
#include "DgRaster.h"
#include "DgRasterFrame.h"
#include "DgKMLPlacemark.h"
#include "Dg3DObject.h"
#include "DgCone.h"
#include "DgMultiline.h"
#include "DgRasterAttach.h"

//-----------------------------------------------------------------------------------------

#undef  ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR
#define ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(Type) \
struct OdRx ## Type ## ValueIterator : OdRxValueIterator \
{ \
  OdArray<Type> m_arrData;   \
  OdUInt32      m_uCurIndex; \
  OdRx ## Type ## ValueIterator() { m_uCurIndex = 0; } \
  virtual void init( const OdArray<Type>& arrData, OdUInt32 uStartIndex ) \
  { \
    m_arrData = arrData; \
    m_uCurIndex = uStartIndex; \
  } \
  virtual bool done() \
  { \
    if( m_arrData.isEmpty() )\
      return true;\
    return m_uCurIndex == m_arrData.size();\
  }\
  virtual bool next()\
  {\
    if( m_uCurIndex < m_arrData.size() )\
      m_uCurIndex++;\
    return !done();\
  }\
  virtual OdRxValue current() const\
  {\
    if( m_uCurIndex >= m_arrData.size() )\
      throw OdError(eInvalidIndex);\
    return m_arrData[m_uCurIndex];\
  }\
}

//-----------------------------------------------------------------------------------------

#undef  ODDG_DEFINE_RX_VALUE_TYPEARRAY_ITERATOR
#define ODDG_DEFINE_RX_VALUE_TYPEARRAY_ITERATOR(Type) \
struct OdRx ## Type ## ArrayValueIterator : OdRxValueIterator \
{ \
  Type ## Array m_arrData;   \
  OdUInt32      m_uCurIndex; \
  OdRx ## Type ## ArrayValueIterator() { m_uCurIndex = 0; } \
  virtual void init( const Type ## Array& arrData, OdUInt32 uStartIndex ) \
  { \
    m_arrData = arrData; \
    m_uCurIndex = uStartIndex; \
  } \
  virtual bool done() \
  { \
    if( m_arrData.isEmpty() )\
      return true;\
    return m_uCurIndex == m_arrData.size();\
  }\
  virtual bool next()\
  {\
    if( m_uCurIndex < m_arrData.size() )\
      m_uCurIndex++;\
    return !done();\
  }\
  virtual OdRxValue current() const\
  {\
    if( m_uCurIndex >= m_arrData.size() )\
      throw OdError(eInvalidIndex);\
    return m_arrData[m_uCurIndex];\
  }\
}

//-----------------------------------------------------------------------------------------

ODRX_DECLARE_VALUE_TYPE(OdDgElementId, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgElement::ElementTypes, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGraphicsElement::Class, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGradientFill::OdDgGradientType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGradientKey, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGradientFill, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(DWGHatchLine, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgHatchPattern::PatternType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLineStyleInfo, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdAngleCoordinate, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPdfRegionInfoItem, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgWordHeadingInfoItem, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLightColor, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTool::TextType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTool::CustomSymbol, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDg::OdDgDesignCenterUnits, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextFormat::AngleValueDisplayMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDg::OdDgDecimalAccuracy, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDg::OdDgAngleReadoutDirectionMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLevelTableRecord::ElementAccess, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDg::LineStyleUnitsType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDg::LineStyleType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapBackground::OdDgEnvMapBackgroungMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapFog::OdDgEnvMapFogMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapLayer::OdDgEnvMapLayerType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapImage::OdDgEnvMapProjectionType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapImage::OdDgEnvMapFilterType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapGradient::OdDgEnvMapGradientMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMaterialPattern::OdDgMaterialPatternType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMaterialMap::MappingType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMaterialMap::ScaleMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMaterialLayerPattern::OdDgMaterialLayerPatternType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDisplayStyleTableRecord::OdDgEnvironmentTypeDisplayed, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDisplayStyleTableRecord::OdDgDisplayMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDisplayStyleTableRecord::OdDgDisplayStyleLineType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDisplayStyleTableRecord::OdDgDisplayStyleDisplayHeader, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLevelFilterTable::OdDgFilterMemberType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLevelFilterTableRecord::OdDgLevelFilterType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextFormat::Accuracy, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimension::PlacementAlignment, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextInfo::TextAlignment, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextFormat::LabelDisplayMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextInfo::TextLocation, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimension::TerminatorArrowHeadType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimension::TerminatorOrientation, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimension::ToolType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimNote::NoteFrameType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimNote::NoteJustification, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextInfo::StackedFractionType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextInfo::StackFractionAlignment, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimOptionTerminators::TerminatorStyle, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimOptionAltFormat::ComparisonOperator, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTool::TerminatorType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimOptionOffset::ChainType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimOptionOffset::LeaderAlignment, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextInfo::FitOptions, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimLabelLine::LabelLineDimensionMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimNote::NoteTerminatorType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextInfo::TextRotation, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimNote::NoteAttachmentDirection, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimNote::NoteEditAbout, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimNote::NoteAttachmentAlignment, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::UnitBase, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::UnitSystem, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModelLinkNode::OdDgModelLinkNodeType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgRegionLinkNode::OdDgRegionLinkNodeType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPdfRegionInfoItem::OdDgPdfRegionType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgWordHeadingInfoItem::OdDgWordHeadingItemType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStylePrintArea, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStyle3StateBoolean, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStylePaperOrientation, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStyleLayoutUnits, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStyleLayoutSizeScaleMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStyleLayoutOriginMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStyleLayoutMirrorMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStyleLayoutFenceAlign, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStyleColorMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStylePropertyPubMethod, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStylePrintDefCreationMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStylePdfPaperSizeMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleTableRecord::OdDgPrintStyleRasterRotation, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleFenceCreationData::OdDgPrintStyleFenceCreationMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTagDefinition::Type, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLinkNode::OdDgLinkNodeType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrototypeSchemaItem::OdDgPrototypeSchemaItemType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDg::TextJustification, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDg::TextDirection, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTextExtendedProperties::LineSpacingType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTemplateValueVariant::OdDgTemplateVariantDataType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTemplateColorValue::OdDgTemplateColorType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgView::OdDgDisplayMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::AcsType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::Type, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::WorkingUnit, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::UnitMeasure, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::OdDgUnitsFormat, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::OdDgAngleFormat, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::OdDgUnitsAccuracy, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::OdDgAngleDirectionMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::OdDgAngleAccuracy, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::CellType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::OdDgGridOrientationType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataInfo::OdDgGeoDataVerticalDataType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataInfo::OdDgGeoDataLocalTransformType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataDatum::OdDgGeoDataConversionMethod, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemProjectionType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataCoordinateSystem::OdDgGeoDataCoordSystemUnitType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordinateSystemParamDataType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataCoordinateSystemParam::OdDgDataCoordinateSystemParamType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemQuadrantValue, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataCoordinateSystemParam::OdDgGeoDataCoordSystemHemisphereValue, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLineStyleResource::OdLsResourceType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLineCodeResourceStrokeData::OdLsStrokeWidthMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLineCodeResourceStrokeData::OdLsStrokeCapsType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLinePointResourceSymInfo::OdLsSymbolPosOnStroke, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgAssocPointRoot::OdDgAssocPointRootType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTool::Leader, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgAssocRegion::OdDgAssocRegionType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgAssocRegion::OdDgAssocRegionFillModeInteriorShapes, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDetailingSymbol::Type, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgOle2Frame::OdDgOleObjectType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgOle2Frame::OdDgDrawAspect, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgOle2Frame::OdDgOleViewRotationMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLight::Type, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMesh::StyleValues, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdFontType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapBackground, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapSkyLight, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapImage, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapImageCube, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapGradient, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapFog, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvMapLayer, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvironmentMap, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEnvironmentCube, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMaterialParam, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgXMLNode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgXMLProperty, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::UnitDescription, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMultilineSymbology, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMultilineProfile, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleFenceCoordinate, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleFencePoint, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleFenceCreationData, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleLevelOverride, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrintStyleReferenceOverride, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrototypeSchemaItem, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgPrototypeSchema, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgColorBookItem, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTemplateColorValue, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTemplateValueVariant, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTemplateItem, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdGsDCRect, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgModel::StorageUnitDescription, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataDatum, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataEllipsoid, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataHelmertParams, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeoDataCoordinateSystemParam, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTextExtendedProperties::OdDgSpecialSymbol, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTextEditField, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimPoint, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextInfo, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimTextFormat, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimGeometry, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLightParam, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMeshFaceLoops::FacePoint, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeometryCacheAction::OdDgGeometryCacheActionType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgGeometryCacheActionPtr, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgRaster::RasterFormat, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgRasterFrame::OdDgGeoPriority, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgRasterFrame::OdDgRasterDrawingPlane, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgRasterFrame::OdDgRasterColorMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgKMLPlacemarkSource::OdDgKMLPlacemarkType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgKMLPlacemarkSourcePtr, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgSurface::Type, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgCone::ConeType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgSolid::Type, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTableElement::OdDgTableElementBreakType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTableElement::OdDgTableElementSubTablePosition, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTableElementMerge, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTableCellElement::OdDgTableCellElementType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTableCellElement::OdDgTableCellElementMarginType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTableCellElement::OdDgTableCellElementTextAlignment, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTableCellElement::OdDgTableCellElementTextOrientation, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTableCellSymbology, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMultiline::OffsetMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMultilineBreak::Flags, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMultilineBreak, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgMultilinePoint, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimOption::Type, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgDimOptionPrefixSuffixSymbol::OdDgDimPrefixSuffixStyle, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgRasterAttachmentHeader::OdDgRasterAttachmentPlane, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgRasterAttachmentHeader::OdDgIndexTransEntry, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgRasterAttachmentHeader::OdDgRGBTransEntry, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgArcAssociation::OdDgArcAssociationKeyPoint, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgOriginAssociation::OdDgOriginAssocOption, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgReferenceAttachmentHeader::OdDgNewLevelDisplyMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgReferenceAttachmentHeader::OdDgLineStyleScaleMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgReferenceAttachmentHeader::OdDgReferenceForeignUnits, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgReferenceAttachmentHeader::OdDgXRefPaletteModificationMode, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgReferenceAttachmentViewFlags, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgCompoundLineStyleComponentInfo, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLineCodeResourceStrokeData, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgLinePointResourceSymInfo, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTerrainOptions::OdDgTerrainOptionsType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTerrainOptions::OdDgTerrainPointDisplayType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTerrainOptions::OdDgTerrainContourSmoothingType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTerrainFeature::OdDgTerrainFeatureType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTerrainControlElement::OdDgTerrainEdgeMethod, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTerrainTriangle, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgTerrainFeature, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdUInt32Array, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdGePoint2dArray, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgNamedGroupItem::OdDgNamedGroupPropagateType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgNamedGroupItem, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgExpressionItem::OdDgExpressionItemType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgExpressionConstValueVariant::OdDgExpressionConstValueVariantType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgCompareOperator::OdDgCompareOperatorType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgFunctionOperator::OdDgFunctionOperatorType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgEqualOrNotOperator::OdDgEqualOrNotOperatorType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgSpecialConstant::OdDgSpecialConstantType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgVariable::OdDgVariableType, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgVariable::OdDgVariableScope, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgItemTypeBasedVariable::OdDgItemTypeBasedVariableUnits, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgExpressionConstValueVariant, DGENT_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdDgVariableValueVariant, DGENT_EXPORT);

//-----------------------------------------------------------------------------------------

class OdDgRxDisplayAsAttribute;
typedef OdSmartPtr<OdDgRxDisplayAsAttribute> OdDgRxDisplayAsAttributePtr;

/** \details
    Corresponding C++ library: TG_Db
    <group OdDg_Classes>
*/
class TG_EXPORT OdDgRxDisplayAsAttribute : public OdRxDisplayAsAttribute
{
public:
  ODRX_DECLARE_MEMBERS(OdDgRxDisplayAsAttribute);
  static OdRxAttributePtr createObject(bool bSetIndex, bool bSetName);
  virtual OdString getDisplayValue(OdRxValue& value, bool useDynamicProperties);
  void setShowName(bool val);
  void setShowIndex(bool val);
private:
  bool m_bShowIndex;
  bool m_bShowName;
};

//-----------------------------------------------------------------------------------------

class OdDgRxHierarchyLevelAttribute;
typedef OdSmartPtr<OdDgRxHierarchyLevelAttribute> OdDgRxHierarchyLevelAttributePtr;

/** \details
    Corresponding C++ library: TG_Db
    <group OdDg_Classes>
*/
class TG_EXPORT OdDgRxHierarchyLevelAttribute : public OdRxHierarchyLevelAttribute
{
public:
  ODRX_DECLARE_MEMBERS(OdDgRxHierarchyLevelAttribute);
  virtual OdString value(OdRxValue& value);
};

//-----------------------------------------------------------------------------------------

#endif
