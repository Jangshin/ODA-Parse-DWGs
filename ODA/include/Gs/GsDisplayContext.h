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

#ifndef __OD_GS_DISPLAY_CONTEXT_H_
#define __OD_GS_DISPLAY_CONTEXT_H_

#include "TD_PackPush.h"

#include "Gs/GsBaseVectorizer.h"
struct OdSiShape;
class OdGsContainerNode;
class OdGsEntityNode;
class OdGsNestedMetafile;

class OdGsBaseContext
{
public:
    /** \details
      Destructor for the OdGsBaseContext class.
    */
    virtual ~OdGsBaseContext(){}
    virtual bool processNestedMetafile(OdGsEntityNode& node, const OdGsNestedMetafile* pMf) { return false; }

    virtual bool isDeviceDisplayOffLayers() const { return false; }

    virtual void increaseXrefLevel(bool /*bFade*/) {}

    virtual const OdSiShape* query() const = 0;
};

class OdGsDisplayContext: public OdGsBaseContext
{
public:
  /** \details
    Constructor for the OdGsDisplayContext class.
    
    \param vectorizer   [in] Associated vectorizer.
  */
  OdGsDisplayContext(OdGsBaseVectorizer& vectorizer);

  /** \details
    Returns an associated vectorizer.
    
    \returns
    Associated vectorizer.
  */
  OdGsBaseVectorizer& vectorizer() { return m_vectorizer; }
  
  /** \details
    Returns a graphics view associated with a vectorizer.
    
    \returns
    Reference to an associated view.
  */
  OdGsViewImpl& view() { return m_vectorizer.view(); }

  /** \details
    Checks whether an associated vectorizer has the kHighlighted flag set to true.

    \returns
    True if the kHighlighted flag is set to true, false otherwise.
  */
  bool isHighlighted() const { return m_vectorizer.isHighlighted(); }
  
  /** \details
    Sets the highlight flag for an associated vectorizer.
    \param bHighlight [in]  Enables or disables highlighting.
    \param nSelStyle  [in]  Selection style.
    \sa
    <link tv_working_with_features_highlighting, Work with Highlighting>
  */
  void highlight(bool bHighlight, OdUInt32 nSelStyle = 0) { vectorizer().highlight(bHighlight, nSelStyle); }

  /** \details
    Returns the current selection style of an associated vectorizer.
    \returns Current selection style index.
  */
  OdUInt32 currentSelectionStyle() const { return m_vectorizer.currentSelectionStyle(); }

  void displaySubnode(bool isHighlightedAll, OdGsEntityNode* pSubNode);
  void displaySubnode(OdGsContainerNode* pCont, OdGsEntityNode* pSubNode, int nHighlightPass = 0);

  bool isDeviceHighlightOptimized() const
  { return GETBIT(m_status, kDeviceHighlightOptimized); }

  bool isDeviceDisplayOffLayers() const
  { return GETBIT(m_status, kDeviceDisplayOffLayers); }
  bool isSpatialIndexDisabled() const
  { return GETBIT(m_status, kDeviceDisableSpatialIdx) || m_vectorizer.isSpatialIndexDisabled(); }

  bool isDeviceDisableNested() const
  { return GETBIT(m_status, kDeviceDisableNested); }
  void setDeviceDisableNested(bool bSet)
  { SETBIT(m_status, kDeviceDisableNested, bSet); }

  OdGsBaseVectorizer::BlockScopesCallback *blockScopesCallback() const
  { return m_pBlockScopesCbk; }
  void setBlockScopesCallback(OdGsBaseVectorizer::BlockScopesCallback *pBlockScopesCbk)
  { m_pBlockScopesCbk = pBlockScopesCbk; }
  class BlockScopesCallback
  { OdGsBaseVectorizer::BlockScopesCallback *m_pBlockScopes;
    const void *m_pRefId;
    public:
      BlockScopesCallback(const OdGsDisplayContext &ctx, const void *pRefId)
        : m_pBlockScopes(ctx.blockScopesCallback()), m_pRefId(pRefId)
      { if (m_pBlockScopes) m_pBlockScopes->blockBegin(m_pRefId); }
      ~BlockScopesCallback()
      { if (m_pBlockScopes) m_pBlockScopes->blockEnd(m_pRefId); }
  };

  bool forceDrawOrder() const { return GETBIT(m_status, kForceDrawOrder); }

  virtual bool processNestedMetafile(OdGsEntityNode& node, const OdGsNestedMetafile* pMf);
  virtual void increaseXrefLevel(bool bFade);

  bool isDisplayClippingEnabled() const { return m_vectorizer.view().clippingShapes().size() > 0; }
  unsigned markToSkipMask() const;
  bool markedToSkip(OdGsEntityNode* pEnt, unsigned markToSkipMask) const;
  virtual const OdSiShape* query() const ODRX_OVERRIDE { return m_spQuery; }

  bool isDeviceSuppressHide() const 
  {
    return GETBIT( m_status, kDeviceSuppressHide );
  }
  void setDeviceSuppressHide( bool bSuppress )
  {
    SETBIT( m_status, kDeviceSuppressHide, bSuppress );
  }

  bool isBlockContentDisabled() const
  {
    return GETBIT(m_status, kDisableBlockContent);
  }
  void setDisableBlockContent(bool bDisable)
  {
    SETBIT(m_status, kDisableBlockContent, bDisable);
  }
  bool isBlockAttributesDisabled() const
  {
    return GETBIT(m_status, kDisableBlockAttributes);
  }
  void setDisableBlockAttributes(bool bDisable)
  {
    SETBIT(m_status, kDisableBlockAttributes, bDisable);
  }
public:
  const OdSiShape* m_spQuery; //spatial query for displaying of top-level container
  const OdGsEntityNode* m_node; //reference node being displayed
  bool m_bPushModelTransform; //fix model to world transformation when playing metafiles for non-shared OdGsBlockReferenceNodes

protected:
  enum
  {
    //NS: probably temporary
    kDeviceHighlightOptimized = 1,
    kDeviceDisplayOffLayers   = 2,
    kDeviceDisableSpatialIdx  = 4,
    kDeviceDisableNested      = 8,
    kDeviceSuppressHide       = 16,
    kForceDrawOrder           = 32,
    kDisableBlockAttributes   = 64,
    kDisableBlockContent      = 128
  };
protected:
  OdGsBaseVectorizer& m_vectorizer;
  OdGsBaseVectorizer::BlockScopesCallback *m_pBlockScopesCbk;
  OdUInt32 m_status;
  OdUInt32 m_xrefFadingCounter;
};

class OdSiRecursiveVisitor;
class OdGsBlockNode;
class OdGsSpQueryContext: public OdGsBaseContext
{
public:
  OdGsSpQueryContext(const OdGsView& view, OdSiRecursiveVisitor* pVisitor): m_view(view), m_vis(pVisitor),
      m_curBlockNode(NULL){}
  virtual bool processNestedMetafile(OdGsEntityNode& node, const OdGsNestedMetafile* pMf);
  void applyQuery(OdGsEntityNode& node);
  const OdGsView& view() { return m_view; }
  OdSiRecursiveVisitor* visitor() { return m_vis; }
  OdGsBlockNode* curBlockNode() { return m_curBlockNode; }
  virtual const OdSiShape* query() const ODRX_OVERRIDE;

protected:
  const OdGsView& m_view;
  OdSiRecursiveVisitor* m_vis;
  OdGsBlockNode* m_curBlockNode;
};

typedef OdSiRecursiveVisitor OdSiSelBaseVisitor;
class OdGsSelectContext: public OdGsBaseContext
{
public:
  OdGsSelectContext(OdGsBaseVectorizer& vect, OdGiDrawable* pDrw,
    OdSiSelBaseVisitor* pVisitor, OdGsView::SelectionMode mode):
    m_vect(vect), m_drw(pDrw), m_vis(pVisitor), m_mode(mode){}
  virtual bool processNestedMetafile(OdGsEntityNode& node, const OdGsNestedMetafile* pMf);
  //natalias: OdGsBaseContext extended with query() method to provide customization at
  //OdGsBaseVectorizer-derived class by means of OdGsBaseVectorizer::m_MfPlayQuery
  virtual const OdSiShape* query() const ODRX_OVERRIDE;

protected:
  OdGsBaseVectorizer& m_vect;
  OdGiDrawable* m_drw;
  OdSiSelBaseVisitor* m_vis;
  OdGsView::SelectionMode m_mode;
};

#include "TD_PackPop.h"

#endif // __OD_GS_DISPLAY_CONTEXT_H_
