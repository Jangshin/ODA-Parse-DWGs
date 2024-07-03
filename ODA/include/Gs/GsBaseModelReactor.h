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

#ifndef __ODGSBASEMODELREACTOR_H__
#define __ODGSBASEMODELREACTOR_H__

#include "TD_PackPush.h"

#include "Gs/GsModel.h"

class OdGsNode;

/** \details
    OdGsBaseModel reactor.

    Corresponding C++ library: TD_Gs
    <group OdGs_Classes> 
*/
class OdGsBaseModelReactor : public OdGsModelReactor
{
  public:
    /** \details
      Callback that is called whenever GsModel is highlighted or un-highlighted.

      \param pModel [in]  Pointer to the model.
      \param path [in]  Path node to highlight.
      \param bDoIt [in]  Enables or disables highlighting.
      \param nStyle [in]  Selection style index.
      \param pView [in]  Pointer to the view in which model is highlighted.
      \returns
      Default implementation returns true.
    */
    virtual bool onHighlight(OdGsModel *pModel, const OdGiPathNode& path, bool bDoIt, OdUInt32 &nStyle, const OdGsView* pView) { return true; }
    /** \details
      Callback that is called whenever GsModel is highlighted or un-highlighted.

      \param pModel [in]  Pointer to the model.
      \param path [in]  Path node to highlight.
      \param pMarkers [in]  Pointer to an array of markers.
      \param nMarkers [in]  Number of markers.
      \param bDoIt [in]  Enables or disables highlighting.
      \param nStyle [in]  Selection style index.
      \param pView [in]  Pointer to the view in which model is highlighted.
      \returns
      Default implementation returns true.
    */
    virtual bool onHighlight(OdGsModel *pModel, const OdGiPathNode& path, const OdGsMarker* pMarkers, OdUInt32 nMarkers, bool bDoIt,
                             OdUInt32 &nStyle, const OdGsView* pView) { return true; }

    /** \details
      Callback that called before GsModel changes node hidden state.
      \param pModel [in]  Pointer to the model.
      \param pNode [in]  Pointer to the cache node.
      \param bHidden [in]  Flag that shows whether model is hidden.
      \param bSelectable [in]  Flag that shows whether model is sectionable.
      \param pView [in]  Pointer to the view where the specified entity should be hidden.
      \returns
      Default implementation returns true.
    */
    virtual bool onHide(OdGsModel *pModel, OdGsNode *pNode, bool &bHidden, bool &bSelectable, const OdGsView* pView) { return true; }
    /** \details
      Callback that called before GsModel changes node hidden state.
      \param pModel [in]  Pointer to the model.
      \param path [in]  Path to the entity for hide.
      \param pMarkers [in]  Pointer to an array of markers.
      \param nMarkers [in]  Number of markers.
      \param bHidden [in]  Flag that shows whether model is hidden.
      \param bSelectable [in]  Flag that shows whether model is sectionable.
      \param pView [in]  Pointer to the view where the specified entity should be hidden.
      \returns
      Default implementation returns true.
    */
    virtual bool onHide(OdGsModel *pModel, const OdGiPathNode& path, const OdGsMarker* pMarkers, OdUInt32 nMarkers,
                        bool& bHidden, bool &bSelectable, const OdGsView* pView) { return true; }

    /** \details
      Callback that called before GsModel changes node transformation state.
      \param pModel [in]  Pointer to the model.
      \param path  [in]  Path to the entity for transformation setting.
      \param bDoIt [in]  Enables or disables transformation.
      \param xForm [in]  Transformation matrix.
      \param pView [in]  Pointer to the view where the specified entity should be transformed.
      \returns
      Default implementation returns true.
    */
    virtual bool onExternalTransform(OdGsModel *pModel, const OdGiPathNode &path, bool bDoIt, const OdGsMatrixParamPtr &xForm,
                                     const OdGsView* pView) { return true; }
    /** \details
      Callback that called before GsModel changes node tranformation state.
      \param pModel [in]  Pointer to the model.
      \param path [in]  Path to the entity for transformation setting.
      \param pMarkers [in]  Pointer to an array of markers.
      \param nMarkers [in]  Number of markers.
      \param bDoIt [in]  Enables or disables transformation.
      \param xForm [in]  Transformation matrix.
      \param pView [in]  Pointer to the view where the specified entity should be transformed.
      \returns
      Default implementation returns true.
    */
    virtual bool onExternalTransform(OdGsModel *pModel, const OdGiPathNode& path, const OdGsMarker* pMarkers, OdUInt32 nMarkers,
                                     bool bDoIt, const OdGsMatrixParamPtr &xForm, const OdGsView* pView) { return true; }

    /** \details
      Callback that is called whenever GsModel is marked for invalidation.

      \param pModel [in]  Pointer to the model.
      \param hint [in]  Specifies which content of the model should be processed.
      \returns
      Default implementation returns true.
    */
    virtual bool onInvalidate(OdGsModel *pModel, OdGsModel::InvalidationHint hint) { return true; }
    /** \details
      Callback that is called whenever GsModel is marked for invalidation.

      \param pModel [in]  Pointer to the model.
      \param pView [in]  Pointer to the view.
      \returns
      Default implementation returns true.
    */
    virtual bool onInvalidate(OdGsModel *pModel, OdGsView* pView) { return true; }

    /** \details
      Enumeration contains GsModel properties which changes can be handled by reactor.
    */
    enum ModelProperty
    {
      kModelTransform = 0, // GsModel transformation matrix.
      kModelRenderType,    // GsModel render type override.
      kModelBackground,    // GsModel background.
      kModelVisualStyle,   // GsModel visual style override.
      kModelSectioning,    // GsModel sectioning data.

      kNumModelProps       // Number of handled GsModel properties.
    };
    /** \details
      Callback that called on GsModel property change.
      \param pModel [in]  Pointer to the model.
      \param nProp [in]  GsModel property type.
      \returns
      Default implementation returns true.
    */
    virtual bool onPropertyModified(OdGsModel *pModel, ModelProperty nProp) { return true; }
};

#include "TD_PackPop.h"

#endif // __ODGSBASEMODELREACTOR_H__
