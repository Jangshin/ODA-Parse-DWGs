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

#ifndef __ODGSHIGHLIGHTDATA_H__
#define __ODGSHIGHLIGHTDATA_H__

#define STL_USING_MAP
#include "OdaSTL.h"

#include "Gi/GiDrawable.h"
#include "Gs.h"
#include "GsSimpleParams.h"
#include "TPtr.h"

#include "TD_PackPush.h"

class OdGsStateBranch;
typedef TPtr<OdGsStateBranch> OdGsStateBranchPtr;
typedef OdArray<OdGsStateBranchPtr> OdGsStateBranchPtrArray;

typedef std::map<OdGsMarker, OdGsSimpleParamPtr> OdGsMarkerSet;

class OdGsStateBranchReactor;

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGsStateBranchReactor object pointers.
*/
typedef OdSmartPtr<OdGsStateBranchReactor> OdGsStateBranchReactorPtr;

/** \details
    This class is a service class to keep information about highlighted subentities and nested entities on OsGsEntityNode.

    Corresponding C++ library: TD_Gs

    <group OdGs_Classes> 
*/
class GS_TOOLKIT_EXPORT OdGsStateBranch
{
  public:
    /** \details
      Type of state branch.
    */
    enum BranchType
    {
      kHighlightingBranch,   // Highlighting state branch.
      kVisibilityBranch,     // Visibility state branch.
      kTransformationBranch, // Transformation state branch.

      kNumBranchTypes        // Number of state branch types.
    };
  protected:
    ODRX_HEAP_OPERATORS();
    ~OdGsStateBranch() { if (m_pSetMarkers) { delete m_pSetMarkers; } } // Prevent direct delete of state branches
    OdGsStateBranchPtrArray::iterator findChildImp(const OdDbStub *pDrawableId) const;
    OdGsStateBranchPtrArray::iterator findChildImp(const OdGiDrawable *pTransDrawable) const;
    OdGsMarkerSet &initCheckMarkers() const;
    void destroyCheckMarkers();

    enum Flags
    {
      kPersistentId = (1 << 0)            // true if m_pDrawableId stores OdDbStub pointer
    };

    OdRefCounter m_nRefCounter;           // Shared ownership
    OdUInt16 m_flags;                     // Bit flags
    OdUInt16 m_type;                      // Branch type
    const void *m_pDrawableId;            // Persistent id or transient drawable pointer (depends from flag)
    // @@@TODO: Add ability to set style index per selection marker.
    OdGsSimpleParamPtr m_pData;           // Additional data attached to specific branch type
    OdGsStateBranchReactorPtr m_pReactor; // OdGsStateBranch reactor
    OdGsStateBranchPtr m_pNext;           // Next type of per-entity branch
    mutable OdGsMarkerSet *m_pSetMarkers; // Set of selection markers 
    mutable OdGsStateBranchPtrArray m_aChild; // Sorted array of nested entities
    // the sorting rule: first are transient entities with id 0, sorted by drw() value,
    // next are persistent entities with id != 0, sorted by id()
  public:
    OdGsStateBranch(const OdDbStub* pDrawableId, BranchType branchType)
      : m_nRefCounter(1)
      , m_flags(kPersistentId)
      , m_type((OdUInt16)branchType)
      , m_pDrawableId(pDrawableId)
      , m_pSetMarkers(NULL)
      , m_aChild(0, 1)
    {
    }
    OdGsStateBranch(const OdGiDrawable* pTransDrawable, BranchType branchType)
      : m_nRefCounter(1)
      , m_flags(0)
      , m_type((OdUInt16)branchType)
      , m_pDrawableId(pTransDrawable)
      , m_pSetMarkers(NULL)
      , m_aChild(0, 1)
    {
    }

    static OdGsStateBranchPtr create(OdDbStub* pDrawableId, BranchType branchType,
                                     OdGsMarker marker = kNullSubentIndex, const OdGsSimpleParam *pData = NULL);
    static OdGsStateBranchPtr create(OdGiDrawable* pTransDrawable, BranchType branchType,
                                     OdGsMarker marker = kNullSubentIndex, const OdGsSimpleParam *pData = NULL);
    static void destroy(OdGsStateBranch *pStateBranch);

    void addRef()
    {
      ++m_nRefCounter;
    }
    bool release()
    {
      ODA_ASSERT((m_nRefCounter > 0));
      if (!(--m_nRefCounter))
      {
        destroy(this);
        return true;
      }
      return false;
    }

    // access to nested entities
    const OdGsStateBranchPtrArray& aChild() const { return m_aChild; }
    // access to subentities
    const OdGsMarkerSet& markers() const { return initCheckMarkers(); }
    OdUInt32 markersSize() const { return m_pSetMarkers ? (OdUInt32)m_pSetMarkers->size() : 0; }
    bool markersEmpty() const { return m_pSetMarkers ? m_pSetMarkers->empty() : true; }

    // add/remove/find nested entities info
    OdGsStateBranch* addChild(OdDbStub* pDrawableId);
    OdGsStateBranch* addChild(const OdGiDrawable* pTransDrawable);
    void removeChild(const OdGsStateBranch* pChild);
    OdGsStateBranch* findChild(const OdDbStub* pDrawableId) const; // search in a sorted array, fast
    OdGsStateBranch* findChild(const OdGiDrawable* pTransDrawable) const; // search in a sorted array, fast

    // add/remove/find subentities info
    bool addMarker(OdGsMarker marker, const OdGsSimpleParam *pData = NULL, bool bDiffParamSet = false);
    bool removeMarker(OdGsMarker marker);
    bool hasMarker(OdGsMarker marker) const; // search in a sorted array, fast
    bool hasMarker(OdGsMarker marker, OdGsMarkerSet::const_iterator &itRev) const;

    // access to the OdGsEntityNode data
    const OdDbStub* id() const
    {
      return (GETBIT(m_flags, kPersistentId)) ? reinterpret_cast<const OdDbStub*>(m_pDrawableId) : NULL;
    }
    const OdGiDrawable* drw() const
    {
      return (!GETBIT(m_flags, kPersistentId)) ? reinterpret_cast<const OdGiDrawable*>(m_pDrawableId) : NULL;
    }
    bool isEmpty() const
    {
      return (!m_pSetMarkers || m_pSetMarkers->empty()) && aChild().isEmpty();
    }

    // access flags
    bool isPersistentId() const { return GETBIT(m_flags, kPersistentId); }

    BranchType type() const { return (BranchType)m_type; }

    // chain
    void setNextTypeOfBranch(OdGsStateBranch *pNext) { m_pNext = pNext; }
    OdGsStateBranch *nextTypeOfBranch() { return m_pNext.get(); }
    const OdGsStateBranch *nextTypeOfBranch() const { return m_pNext.get(); }

    // reactor
    void setReactor(OdGsStateBranchReactor *pReactor);
    OdGsStateBranchReactor *reactor();

    // style/transform
    bool setData(const OdGsSimpleParam *pData);
    void resetData() { setData(NULL); }
    const OdGsSimpleParam *data() const { return m_pData.get(); }
    bool hasData() const { return !m_pData.isNull(); }

    const OdGsSimpleParam *markerData(OdGsMarker marker, OdGsMarkerSet::const_iterator *itRev = nullptr) const;
    bool hasMarkerData(OdGsMarker marker, OdGsMarkerSet::const_iterator *itRev = nullptr) const;

    OdUInt32 dataAsInt() const;
    OdUInt32 markerDataAsInt(OdGsMarker marker, OdGsMarkerSet::const_iterator *itRev = nullptr) const;
    const OdGeMatrix3d &dataAsMatrix() const;
    const OdGeMatrix3d &markerDataAsMatrix(OdGsMarker marker, OdGsMarkerSet::const_iterator *itRev = nullptr) const;

    static inline bool isValidMarker(OdGsMarker marker)
    {
      return (marker != kNullSubentIndex);
    }
};

/** \details
    This class is a reactor for OdGsStateBranch class.

    Corresponding C++ library: TD_Gs

    <group OdGs_Classes> 
*/
class GS_TOOLKIT_EXPORT OdGsStateBranchReactor : public OdRxObject
{
  public:
    virtual void onChildAdded(OdGsStateBranch *pStateBranch, OdGsStateBranch *pStateBranchAdded) = 0;
    virtual void onChildRemoved(OdGsStateBranch *pStateBranch, OdGsStateBranch *pStateBranchRemoved) = 0;
    virtual void onMarkerAdded(OdGsStateBranch *pStateBranch, OdGsMarker gsMarker, const OdGsSimpleParam *pData) = 0;
    virtual void onMarkerRemoved(OdGsStateBranch *pStateBranch, OdGsMarker gsMarker) = 0;
    virtual void onMarkerDataModified(OdGsStateBranch *pStateBranch, OdGsMarker gsMarker,
                                      const OdGsSimpleParam *pPrevData, const OdGsSimpleParam *pData) = 0;
    virtual void onDataModified(OdGsStateBranch *pStateBranch, const OdGsSimpleParam *pPrevData, const OdGsSimpleParam *pData) = 0;
    virtual void onExtentsChanged(const OdGsCache *pGsNode, OdGsStateBranch *pStateBranch,
                                  const OdGeExtents3d &extBefore, const OdGeExtents3d &extAfter) = 0;
    virtual void onBranchDetach(const OdGsCache *pGsNode, OdGsStateBranch *pStateBranch) = 0;
};

// gcc3x template instantiation must be done after class declaration
inline void OdGsStateBranch::setReactor(OdGsStateBranchReactor *pReactor) { m_pReactor = pReactor; }
inline OdGsStateBranchReactor *OdGsStateBranch::reactor() { return m_pReactor.get(); }

inline bool OdGsStateBranch::setData(const OdGsSimpleParam *pData)
{
  if (m_pData.get() != pData)
  { OdGsSimpleParamPtr pPrevData = m_pData;
    m_pData = pData;
    if (!m_pReactor.isNull())
      m_pReactor->onDataModified(this, pPrevData, pData);
    return true;
  }
  return false;
}

inline OdUInt32 OdGsStateBranch::dataAsInt() const
{
  if (type() == kHighlightingBranch && hasData())
    return static_cast<const OdGsIntParam*>(data())->value();
  return 0;
}

inline OdUInt32 OdGsStateBranch::markerDataAsInt(OdGsMarker marker, OdGsMarkerSet::const_iterator *itRev) const
{ const OdGsSimpleParam *pParam = NULL;
  if (type() == kHighlightingBranch && (pParam = markerData(marker, itRev)))
    return static_cast<const OdGsIntParam*>(pParam)->value();
  return 0;
}

inline const OdGeMatrix3d &OdGsStateBranch::dataAsMatrix() const
{
  if (type() == kTransformationBranch && hasData())
    return static_cast<const OdGsMatrixParam*>(data())->value();
  return OdGeMatrix3d::kIdentity;
}

inline const OdGeMatrix3d &OdGsStateBranch::markerDataAsMatrix(OdGsMarker marker, OdGsMarkerSet::const_iterator *itRev) const
{ const OdGsSimpleParam *pParam = NULL;
  if (type() == kTransformationBranch && (pParam = markerData(marker, itRev)))
    return static_cast<const OdGsMatrixParam*>(pParam)->value();
  return OdGeMatrix3d::kIdentity;
}

inline OdGsMarkerSet &OdGsStateBranch::initCheckMarkers() const
{
  if (!m_pSetMarkers)
    m_pSetMarkers = new OdGsMarkerSet();
  return *m_pSetMarkers;
}

inline void OdGsStateBranch::destroyCheckMarkers()
{
  if (m_pSetMarkers && m_pSetMarkers->empty())
  { delete m_pSetMarkers; m_pSetMarkers = NULL; }
}

/** \details
    This class is a multimodule reactor reactor implementation for OdGsStateBranch class.

    Corresponding C++ library: TD_Gs

    <group OdGs_Classes> 
*/
class GS_TOOLKIT_EXPORT OdGsStateBranchMultimoduleReactor
{
  public:
    static void attach(OdGsStateBranch *pStateBranch, const void *pModule, OdGsStateBranchReactor *pReactor);
    static void detach(OdGsStateBranch *pStateBranch, const void *pModule);
    static OdGsStateBranchReactor *getReactor(OdGsStateBranch *pStateBranch, const void *pModule);
    static void setReactor(OdGsStateBranch *pStateBranch, const void *pModule, OdGsStateBranchReactor *pReactor);
};

#include "TD_PackPop.h"

#endif // __ODGSHIGHLIGHTDATA_H__
