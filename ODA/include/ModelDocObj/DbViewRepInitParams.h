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

#ifndef _OdDbViewInitParams_H
#define _OdDbViewInitParams_H

#include "DbViewRep.h"
#include "DbViewRepSectionDefinition.h"
#include "DbSectionSymbol.h"
#include "DbDetailSymbol.h"

#include "TD_PackPush.h"

/** \details

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 
*/
class OdDbViewInitParams {
public:
  OdDbViewInitParams()
    : m_scale(1.)
    , m_viewType(OdDbViewRep::kBase)
    , m_orientation(OdDbViewRep::kFront), m_viewStyleType(OdDbViewRep::kVisibleAndHiddenLines)
    , m_boundaryType(OdDbDetailSymbol::kCircularBoundary), m_modelEdge(OdDbDetailViewStyle::kSmoothWithConnectionLine)
    , m_constrainTo(OdDbViewRepSectionDefinition::kConstrainUndefined)
    , m_overrides(kEmpty)
    , m_bInheritScale(true), m_bInheritStyle(true), m_bInheritSection(false), m_bShowLabel(true), m_bMethodAligned(true), m_bShaded(false)
    , m_bShowInterferenceEdges(false), m_bShowTangentEdges(false), m_bTangentEdgesForeshortened(false)
  {
  }

  void applyToViewSymbol(OdDbViewSymbol& symbol) const
  {
    if (!labelIdentifier().isEmpty())
      symbol.setIdentifier(labelIdentifier());
  }

  void applyToDetailSymbol(OdDbDetailSymbol& symbol) const
  {
    applyToViewSymbol(symbol);
    //symbol.setModelEdgeOrigin();
    if (GETBIT(m_overrides, kDetailViewModelEdgeType))
      symbol.setModelEdgeType(detailViewModelEdgeType());
    if (GETBIT(m_overrides, kBoundaryType))
      symbol.setBoundaryType(boundaryType());
    if (GETBIT(m_overrides, kScale))
      symbol.setDetailViewScale(scale());
    symbol.setDisplayIdentifier(labelVisibility());
  }

  void applyToSectionSymbol(OdDbSectionSymbol& symbol) const
  {
    applyToViewSymbol(symbol);
  }

  OdDbViewRep::ViewOrientType viewOrientType() const {return m_orientation;}
  void setViewOrientType(OdDbViewRep::ViewOrientType type) {m_orientation = type;}

  const OdGePoint3d& center() const {return m_centerPoint;}
  void setCenter(const OdGePoint3d& pt) {m_centerPoint = pt;}

  double scale() const {return m_scale;}
  void setScale(double scale){SETBIT_1((OdUInt32&)m_overrides,kScale); m_bInheritScale = false; m_scale = scale;}

  OdDbObjectId scaleId() const{return m_idScale;} // TODO: Use somehow
  void setScaleId(const OdDbObjectId& scaleId){SETBIT_1((OdUInt32&)m_overrides,kScale); m_bInheritScale = false; m_idScale = scaleId;}

  void setScale(const OdDbObjectId& scaleId, double scale){SETBIT_1((OdUInt32&)m_overrides,kScale); m_bInheritScale = false; m_scale = scale; m_idScale = scaleId;}

  bool inheritScale() const{return m_bInheritScale;}
  void setInheritScale(bool inherit){m_bInheritScale = inherit;}

  bool inheritStyle() const{return m_bInheritStyle;}
  void setInheritStyle(bool inherit){m_bInheritStyle = inherit;}

  bool inheritSection() const { return m_bInheritSection; }
  void setInheritSection(bool inherit) { m_bInheritSection = inherit; }

  bool showInterferenceEdges() const{return m_bShowInterferenceEdges;}
  void setShowInterferenceEdges(bool visibility){m_bShowInterferenceEdges = visibility;}

  bool showTangentEdges() const{return m_bShowTangentEdges;}
  void setShowTangentEdges(bool visibility){m_bShowTangentEdges = visibility;}

  bool tangentEdgesForeshortened() const { return m_bTangentEdgesForeshortened; }
  void setTangentEdgesForeshortened(bool foreshortened) { m_bTangentEdgesForeshortened = foreshortened; }

  bool labelVisibility() const{return m_bShowLabel;}
  void setLabelVisibility(bool visibility){m_bShowLabel = visibility;}

  bool sectionMethodAligned() const { return m_bMethodAligned; }
  void setSectionMethodAligned(bool bMethodAligned) { m_bMethodAligned = bMethodAligned; }

  const OdGePoint3d& target() const{return m_target;}
  void setTarget(const OdGePoint3d& target){m_target = target;}

  const OdGePoint3d& eye() const { return m_eye; }
  void setEye(const OdGePoint3d& eye) { m_eye = eye; }

  const OdGeVector3d& upVec() const { return m_up; }
  void setUpVec(const OdGeVector3d& up) { m_up = up; }

  OdDbViewRep::ViewType viewType() const{return m_viewType;}
  void setViewType(OdDbViewRep::ViewType type){m_viewType = type;}

  OdDbViewRep::ViewStyleType viewStyleType() const{return m_viewStyleType;}
  void setViewStyleType(OdDbViewRep::ViewStyleType type){m_viewStyleType = type;}

  bool isShaded() const {return m_bShaded;}
  void setIsShaded(bool value) {m_bShaded = value;}

  OdString labelIdentifier() const{return m_identifier;}
  void setLabelIdentifier(const OdString& identifier){m_identifier = identifier;}

  const OdDbObjectIdArray& selSetEntities() const {return m_aSelectedIds;} // TODO: Change to selSetId
  void setSelSetEntities(const OdDbObjectIdArray& selectedIds){m_aSelectedIds = selectedIds;} // TODO: Change to selSetId

  OdDbObjectId parentViewRepId() const{return m_idParent;}
  void setParentViewRepId(OdDbObjectId idParent){m_idParent = idParent;}

  OdDbDetailSymbol::BoundaryType boundaryType() const {return m_boundaryType;}
  void setBoundaryType(OdDbDetailSymbol::BoundaryType type) {SETBIT_1((OdUInt32&)m_overrides,kBoundaryType); m_boundaryType = type;}

  OdDbDetailViewStyle::ModelEdge detailViewModelEdgeType() const {return m_modelEdge;}
  void setDetailViewModelEdgeType(OdDbDetailViewStyle::ModelEdge type) {SETBIT_1((OdUInt32&)m_overrides,kDetailViewModelEdgeType); m_modelEdge = type;}

  OdDbViewRepSectionDefinition::ESectionConstrainTo constrainTo() const { return m_constrainTo; }
  bool isConstrainToLastSegment() const { return m_constrainTo == OdDbViewRepSectionDefinition::kConstrainToLastSegment; }
  void setConstrainTo(OdDbViewRepSectionDefinition::ESectionConstrainTo constrain) { m_constrainTo = constrain; }
  void setConstrainToFirstSegment() { m_constrainTo = OdDbViewRepSectionDefinition::kConstrainToFirstSegment; }
  void setConstrainToLastSegment() { m_constrainTo = OdDbViewRepSectionDefinition::kConstrainToLastSegment; }

private:
  OdDbObjectId m_idParent;
  OdDbObjectIdArray m_aSelectedIds; // TODO: Change to selSetId

  OdGePoint3d m_centerPoint;
  OdGePoint3d m_target;
  OdGePoint3d m_eye;
  OdGeVector3d m_up;

  OdString m_identifier;

  double m_scale;
  OdDbObjectId m_idScale; // TODO: Use somehow

  OdDbViewRep::ViewType m_viewType;
  OdDbViewRep::ViewOrientType m_orientation;
  OdDbViewRep::ViewStyleType m_viewStyleType;

  OdDbDetailSymbol::BoundaryType m_boundaryType;
  OdDbDetailViewStyle::ModelEdge m_modelEdge;
  OdDbViewRepSectionDefinition::ESectionConstrainTo m_constrainTo;

  enum Overrides
  {
    kEmpty = 0,
    kScale = 0x2,
    kBoundaryType = 0x4,
    kDetailViewModelEdgeType = 0x8,
    // TODO: others
  };
  Overrides m_overrides;

  bool m_bInheritScale;
  bool m_bInheritStyle;
  bool m_bInheritSection;
  bool m_bShowLabel;
  bool m_bMethodAligned;
  bool m_bShaded;
  bool m_bShowInterferenceEdges;
  bool m_bShowTangentEdges;
  bool m_bTangentEdgesForeshortened;
};

#include "TD_PackPop.h"

#endif // _OdDbViewInitParams_H
