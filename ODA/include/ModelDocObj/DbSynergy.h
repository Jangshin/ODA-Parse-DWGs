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

#ifndef OD_SYNERGY_H
#define OD_SYNERGY_H

#include "DbObject.h"
#include "ModelDocObjExports.h"
#include "UInt64Array.h"
#include "RxIterator.h"

#include "TD_PackPush.h"

class OdDbSynergyLayerMappingImpl;
class OdDbIdwViewMappingImpl;
class OdDbIdwSheetMappingImpl;

/**
 * <group TD_Namespaces> 
 * 
 */
namespace OdSynergyObj {
  enum ViewEdgeLayerStyleType {
    kLsHidden        = 3,
    kLsHiddenNarrow  = 4,
    kLsVisible       = 7,
    kLsVisibleNarrow = 8,
    kLsAnnotation    = 10,
    kLsHatching      = 11,
  };
  enum ViewEdgeType {};
  enum ViewRepZoneType {};
}

#define SYRX_DECLARE_MEMBERS(ClassName) \
protected:                               \
  ClassName(ClassName##Impl* pImpl);      \
public:                                    \
ODRX_DECLARE_MEMBERS (ClassName)


/**
 * <group OdModelDocObj_Classes>
 * 
 */
class MODELDOCOBJ_EXPORT OdDbSynergyLayerMapping : public OdRxObject {
public:
  SYRX_DECLARE_MEMBERS(OdDbSynergyLayerMapping);

  OdDbSynergyLayerMapping();
  virtual ~OdDbSynergyLayerMapping();

  void layerIds(OdDbObjectIdArray& ids) const;
  void removeLayerId(OdSynergyObj::ViewEdgeLayerStyleType edgeStyle);
  void addLayerId(OdSynergyObj::ViewEdgeLayerStyleType edgeStyle, OdDbObjectId id);
  bool layerId(OdSynergyObj::ViewEdgeLayerStyleType edgeStyle, OdDbObjectId& id) const;

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

protected:
  friend class OdDbSynergyMappings;
  OdDbSynergyLayerMappingImpl* m_pImpl;
};

typedef OdSmartPtr<OdDbSynergyLayerMapping> OdDbSynergyLayerMappingPtr;

/**
 * <group OdModelDocObj_Classes>
 * 
 */
class MODELDOCOBJ_EXPORT OdDbIdwViewMapping : public OdRxObject {
public:
  SYRX_DECLARE_MEMBERS(OdDbIdwViewMapping);

  OdDbIdwViewMapping();
  virtual ~OdDbIdwViewMapping();

  void setViewRepId(OdDbObjectId);
  OdDbObjectId viewRepId() const;
  void setViewportId(OdDbObjectId);
  OdDbObjectId viewportId() const;
  void setInventorViewId(OdUInt64);
  OdUInt64 inventorViewId() const;
  
  // OdDbObject methods :
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

protected:  
  friend class OdDbIdwViewMappingImpl;
  OdDbIdwViewMappingImpl* m_pImpl;
};

typedef OdSmartPtr<OdDbIdwViewMapping> OdDbIdwViewMappingPtr;

/**
 * <group OdModelDocObj_Classes>
 * 
 */
class MODELDOCOBJ_EXPORT OdDbIdwSheetMapping : public OdRxObject {
public:
  SYRX_DECLARE_MEMBERS(OdDbIdwSheetMapping);

  OdDbIdwSheetMapping();
  virtual ~OdDbIdwSheetMapping();

  OdDbObjectId layoutId() const;
  void setLayoutId(OdDbObjectId);

  OdUInt32 idwSheetId() const;
  void setIdwSheetId(OdUInt32 id);

  bool hasInventorModelDocViews() const;
  //OdResult invalidIds(OdUInt64Array& outIds) const;
  OdResult update(OdUInt64Array* outUpdatedIds = 0);
  bool eraseViewMappingByViewRepId(OdDbObjectId);
  bool eraseViewMappingByViewportId(OdDbObjectId);
  bool eraseViewMappingByViewId(OdUInt64);
  OdDbIdwViewMapping* addIdwViewMapping(OdUInt64 _inventorViewId, OdDbObjectId _viewportId, OdDbObjectId _viewRepId);
  const OdDbIdwViewMapping* idwViewMappingByViewRepId(OdDbObjectId) const;
  const OdDbIdwViewMapping* idwViewMappingByViewportId(OdDbObjectId) const;
  const OdDbIdwViewMapping* idwViewMappingByViewId(OdUInt64) const;
  OdDbIdwViewMapping* idwViewMappingByViewRepId(OdDbObjectId);
  OdDbIdwViewMapping* idwViewMappingByViewportId(OdDbObjectId);
  OdDbIdwViewMapping* idwViewMappingByViewId(OdUInt64);

  class Iterator : public OdRxIterator {
  public:
    /** \details
      Returns the smart pointer to the view mapping object on which the iterator object refers.
    */
    virtual OdDbIdwViewMappingPtr idwViewMapping() const = 0;
  };
  typedef OdSmartPtr<Iterator> IteratorPtr;

  IteratorPtr newIterator();

  // OdDbObject methods :
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

#ifndef ODMD_IDW_EDITING_SUPPORTED
  OdUInt64 nextIdwViewId() const;
#endif
protected:
  friend class OdDbIdwSheetMappingIterator;
  friend class OdDbIdwSheetMappingImpl;
  friend class OdDbSynergyMappings;

  OdDbIdwSheetMappingImpl* m_pImpl;
private: 
//  void eraseViewMappings();
};

typedef OdSmartPtr<OdDbIdwSheetMapping> OdDbIdwSheetMappingPtr;


/** \details
    This class and its functions are not currently implemented.

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 
*/
class MODELDOCOBJ_EXPORT OdDbSynergyMappings : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbSynergyMappings);

  OdDbSynergyMappings();
  virtual ~OdDbSynergyMappings();

  bool hasInventorModelDocViews() const;
  //OdResult allLayoutIds(OdDbObjectIdArray&) const;
  //OdResult invalidIds(OdArray<unsigned long>&, OdArray<OdUInt64>&) const;
  const OdDbSynergyLayerMapping& layerMapping() const;
  OdDbSynergyLayerMapping& layerMapping();
  //OdResult update(OdArray<unsigned long>&, OdArray<OdUInt64>&);
  bool eraseAllIdwSheetMappings();
  bool eraseIdwSheetMappingByLayoutId(OdDbObjectId layoutId);
  //bool eraseIdwSheetMappingBySheetId(unsigned long);
  //OdDbIdwSheetMapping* addIdwSheetMapping(unsigned long,OdDbObjectId);
  const OdDbIdwSheetMapping* idwSheetMappingByLayoutId(OdDbObjectId) const;
  const OdDbIdwSheetMapping* idwSheetMappingBySheetId(unsigned long) const;
  OdDbIdwSheetMapping* idwSheetMappingByLayoutId(OdDbObjectId);
  OdDbIdwSheetMapping* idwSheetMappingBySheetId(unsigned long);
  void addMapping(OdDbIdwSheetMapping* sheetMapping);

  // OdDbObject methods :
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;
  // virtual subErase
  void subClose() override;

  static OdDbObjectId fromDb(OdDbDatabase* db, bool create = false);

  OdUInt32 nextIdwLayoutId() const;
//private:
//  void eraseIdwSheetMappings();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbSynergyMappings object pointers.
*/
typedef OdSmartPtr<OdDbSynergyMappings> OdDbSynergyMappingsPtr;

/** \details
    This class and its functions are not currently implemented.

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 
*/
//class MODELDOCOBJ_EXPORT OdDbSynergyBulletin : public OdDbObject
//{
//public:
//  ODDB_DECLARE_MEMBERS(OdDbSynergyBulletin);
//  OdDbSynergyBulletin();
//  virtual ~OdDbSynergyBulletin();
//
//protected:
//  // OdDbObject methods :
//  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
//  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
//  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
//  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;
//};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbSynergyBulletin object pointers.
*/
//typedef OdSmartPtr<OdDbSynergyBulletin> OdDbSynergyBulletinPtr;

#include "TD_PackPop.h"

#endif // OD_SYNERGY_H
