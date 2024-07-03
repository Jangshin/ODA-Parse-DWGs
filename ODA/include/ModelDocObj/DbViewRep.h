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

#ifndef OD_VIEWREP_H
#define OD_VIEWREP_H

#include "DbObject.h"
#include "DbViewRepStandard.h"
#include "ModelDocObjExports.h"
#include "DbViewSymbol.h"

#include "TD_PackPush.h"

class OdDbViewInitParams;
class OdDbViewRepLogical;
class OdDbViewRepBodyManager;

/** \details

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 

    The key class in the model documentation functionality.
    Represents every ModelDoc view in the database.
    An OdDbViewRep instance resides in an associated network and owned by an instance of the OdDbAssocViewRepActionBody class.
    Call OdDbViewRep::createViewRep() to add a new view representation.
*/
class MODELDOCOBJ_EXPORT OdDbViewRep : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbViewRep);
  OdDbViewRep();
  virtual ~OdDbViewRep();

  enum ViewStyleType 
  {
    kVisibleAndHiddenLines       = 1,
    kVisibleLinesOnly            = 2,
  };

  enum SourceType
  {
    kSourceNotDefined   = 0,
    kInventorSource     = 1,
    kFusionSource       = 2,
    kModelSpaceSource   = 3
  };

  enum ViewType
  {
    kBase = 0,
    kAuxiliary = 1,
    kDetail = 2,
    kSection = 3,
    kProjected = 4,
  };

  /* For ViewType::kBase only */
  enum ViewOrientType
  {
    kFront = 0,
    kTop = 1,
    kRight = 2,
    kBack = 3,
    kBottom = 4,
    kLeft = 5,
    kNEIsometric = 6,
    kNWIsometric = 7,
    kSEIsometric = 8,
    kSWIsometric = 9,

    kUnk10ViewOrientation = 10,
    kUnk11ViewOrientation = 11,
    kUnk12ViewOrientation = 12,
    kUnk13ViewOrientation = 13,

    kUnk14ViewOrientation = 14,
    kUnk15ViewOrientation = 15,
    kUnk16ViewOrientation = 16,
    kUnk17ViewOrientation = 17,
    kUnk18ViewOrientation = 18,
    kUnk19ViewOrientation = 19,

    kCustom = 20,
    kCurrent = 21,
  };


  /** \details
    Gets a view type.
    \returns
    A view type as one of the ViewType enum's values.
    <table>
    Name        Value
    kBase         0
    kDetail       2
    kSection      3
    kProjected    4
    </table>
  */
  OdDbViewRep::ViewType viewType() const;
  /** \details
    Gets a view orientation type.
    \returns
    A view orientation type as one of the ViewOrientType enum's values.
    <table>
    Name          Value   Description
    kFront          0     Front      
    kTop            1     Top        
    kRight          2     Right      
    kBack           3     Back       
    kBottom         4     Bottom     
    kLeft           5     Left       
    kNEIsometric    6     NE Isometric
    kNWIsometric    7     NW Isometric
    kSEIsometric    8     SE Isometric
    kSWIsometric    9     SW Isometric
    kCurrent       21     Same as source model view orientation
    </table>
  */
  OdDbViewRep::ViewOrientType viewOrientType() const;
  //DOM-IGNORE-BEGIN
  /** \details
    For internal use.
  */
  void setViewType(OdDbViewRep::ViewType type);
  /** \details
    For internal use.
  */
  void setViewOrientType(OdDbViewRep::ViewOrientType type);

  /** \details
    For internal use.
  */
  OdResult sketchModelSpaceToViewModelSpaceXform( OdGeMatrix3d &mat ) const;
  /** \details
    For internal use.
  */
  OdResult sketchModelSpaceToModelSpaceXform( OdGeMatrix3d &mat ) const;
  /** \details
    For internal use.
  */
  OdResult sketchModelSpaceToPaperSpaceXform( OdGeMatrix3d &mat ) const;

  /** \details
    For internal use.
  */
  OdResult viewModelSpaceToModelSpaceXform( OdGeMatrix3d &mat ) const;
  /** \details
    For internal use.
  */
  OdResult viewModelSpaceToPaperSpaceXform( OdGeMatrix3d &mat ) const;
  //DOM-IGNORE-END

  /** \details
    Gets a set of source entities.
    \returns
    Object ID of an OdDbViewRepModelSpaceViewSelSet object
    that represents a set of source entities for this view representation.
  */
  OdDbObjectId selSetObjId() const;
  //DOM-IGNORE-BEGIN
  /** \details
    For internal use.
  */
  void setSelSetObjId(OdDbObjectId id);
  /** \details
    For internal use.
  */
  void setModelSpaceSourceId(OdDbObjectId id);
  /** \details
    For internal use.
  */
  bool isPartialMSView() const;
  /** \details
    Not implemented yet.
  */
  unsigned long viewIndex() const;

  /** \details
    For internal use.
  */
  void setInventorDrawingViewId(OdUInt64 invDVid);
  /** \details
    For internal use.
  */
  OdUInt64 inventorDrawingViewId() const;
  //DOM-IGNORE-END
  /** \details
    Gets the OdDbLayout object where this view representation resides.
    \returns
    Object ID of the OdDbLayout object.
  */
  OdDbObjectId layoutId() const;
  //DOM-IGNORE-BEGIN
  /** \details
    For internal use.
  */
  OdDbViewRepLogical* logical();

  /** \details
    For internal use.
  */
  const class OdRxSketchManager* getSketchManager() const;
  /** \details
    For internal use.
  */
  OdRxSketchManager* getSketchManager();
  //DOM-IGNORE-END

  /** \details
    Gets the block reference entity that refers to an
    anonymous block filled with generated projected geometry of the source model.
    \returns
    Object ID of the OdDbBlockReference entity.
  */
  OdDbObjectId viewBlockReference() const;
  //DOM-IGNORE-BEGIN
  /** \details
    For internal use.
  */
  OdDbObjectId entityBackupBlockRef() const;
  //DOM-IGNORE-END
  /** \details
    Gets the view border entity representing the view representation in paper space.
    \returns
    Object ID of the OdDbViewBorder entity.
  */
  OdDbObjectId viewBorderId() const;
  /** \details
    Gets a viewport entity representing the view representation in paper space.
    \returns
    Object ID of the OdDbViewport entity.
  */
  OdDbObjectId viewportId() const;
  /** \details
    Gets a viewport entity for the shaded image of this view representation.
    \returns
    Object ID of the the OdDbViewport entity.
  */
  OdDbObjectId shadedImageViewportId() const;
  //DOM-IGNORE-BEGIN
  /** \details
    For internal use.
  */
  OdDbObjectId cutDefinitionId(OdUInt32 index = 0) const;
  /** \details
    For internal use.
  */
  OdDbObjectId orientationId() const;
  //DOM-IGNORE-END

  /** \details
    Gets the source type of this view representation.
    \remarks
    Only OdDbViewRep::kModelSpaceSource is currently supported.
    \returns
    The source type of this view representation.
  */
  OdDbViewRep::SourceType sourceType() const;
  /** \details
    Gets view label content.
    \returns
    View label (caption) string as an OdString object. 
  */
  OdString label() const;
  /** \details
    Gets the label's visibility.
    \returns
    The true value if the label (caption) is visible, or false otherwise.
  */
  bool labelVisibility() const;
  /** \details
    Sets a label's visibility.
    \param vis [in] View label (caption) visibility value to set.
  */
  void setLabelVisibility(bool vis);
  /** \details
    Gets a view scale.
    \returns
    The current view scale.
  */
  double scale() const;
  
  /** \details
    Checks whether the view is shaded.
    \returns
    The true value if the view is shaded, or false otherwise.
  */
  bool isShaded() const;
  /** \details
    Gets the shaded image resolution DPI.
    \returns
    Shaded image resolution in DPI as an OdDbViewRepStandard::DpiResolutionType value.
    <table>
    Name          Value
    k50dpi         50  
    k100dpi       100  
    k150dpi       150  
    k200dpi       200  
    k300dpi       300  
    </table>
  */
  OdDbViewRepStandard::DpiResolutionType shadeResolution() const;
  /** \details
    Gets a view style type.
    \returns
    The view style type as an OdDbViewRep::ViewStyleType value.
    <table>
    Name                    Value
    kVisibleAndHiddenLines  1
    kVisibleLinesOnly       2
    </table>
  */
  OdDbViewRep::ViewStyleType viewStyleType() const;
  /** \details
    Sets a new view style type.
    \param vst [in] A new style type value to set from the OdDbViewRep::ViewStyleType enum.
    <table>
    Name                    Value
    kVisibleAndHiddenLines  1
    kVisibleLinesOnly       2
    </table>
  */
  void setViewStyleType(OdDbViewRep::ViewStyleType vst);

  /** \details
    Gets the tangent edge visibility.
    \returns
    The true value if tangent edges are visible, or false otherwise.
  */
  bool tangentEdgeVisibility() const;
  /** \details
    Sets the tangent edge visibility.
    \param val [in] Tangent visibility to set: true to turn on and false to turn off.
  */
  void setTangentEdgeVisibility(bool val);
  /** \details
    Gets the flag indicating whether tangent edges should be foreshortened.
    \returns
    The true value if the tangent edge should be foreshortened, or false otherwise.
  */
  bool foreshortened() const;
  /** \details
    Sets a new value of the flag indicating whether tangent edges should be foreshortened.
    \param val [in] A new value of the flag indicating whether tangent edges should be foreshortened.
  */
  void setForeshortened(bool val);
  /** \details
    Gets the flag indicating the visibility of bodies' interference edges.
    \returns
    The true value if bodies' interference edges are visible, or false otherwise.
  */
  bool interferenceEdgesVisibility() const;
  /** \details
    Turns bodies' interference edge visibility on or off.
    \param val [in] A new value of the flag indicating the interference edge visibility.
  */
  void setInterferenceEdgesVisibility(bool val);
  /** \details
    Gets the flag indicating view style inheritance.
    \returns
    The true value if the view inherits a view style from the parent view, or false if the view has its own view style.
    \sa
     <link OdDbViewRep::ViewStyleType>
  */
  bool inheritViewStyle() const;
  /** \details
    Turns view style inheritance on or off.
    \param value [in] A new value of the flag indicating the view style inheritance.
  */
  void setInheritViewStyle(bool value);
  /** \details
    Turns shaded image visibility on or off.
    \param doIt [in] A new shaded image visibility value to set.
  */
  void setIsShaded(bool doIt);

  /** \details
    Gets the camera's rotation angle.
    \returns
    Camera's rotation angle as a double value.

    \param target [out] Receives the camera's target position.
    \param eye [out] Receives the camera's eye position.
    \param up [out] Receives the camera's up vector.
  */
  void camera( OdGePoint3d &eye, OdGePoint3d &target, OdGeVector3d &upVector ) const;
  //DOM-IGNORE-BEGIN
  /** \details
    For internal use.
  */
  void setCamera(const OdGePoint3d& target, const OdGePoint3d & eye, const OdGeVector3d& up);
  //DOM-IGNORE-END
  /** \details
    Returns the camera's rotation angle.
  */
  double rotationAngle() const;
  //DOM-IGNORE-BEGIN
  /** \details
    For internal use.
  */
  OdGePoint2d viewBasePoint() const;
  /** \details
    For internal use.
  */
  OdGePoint3d center() const;
  //DOM-IGNORE-END
  /** \details
    Updates the view scale and marks the view representation to be regenerated using a new scale value.
    \param scale [in] New scale value.
  */
  OdResult updateViewportScale( double scale );
  /** \details
    Gets a value of the flag indicating whether the view representation scale is inherited from the parent view representation.
    \returns
    The true value if the scale is inherited from the parent view representation, or false if the view has its own scale.
  */
  bool isScaleFromParent() const;
  /** \details
    Sets the flag indicating whether this view representation should inherit the scale from the parent view representation.

    \param fromParent [in] A new value of the flag to set.

    \remarks
    This flag is true by default for a projected or section view.
  */
  void setScaleFromParent( bool fromParent );
  /** \details
    Checks whether the view representation inherits sections from parent views.

    \returns The true value if the view representation inherits sections from parent views, or false otherwise.

    \remarks
    If this flag is false for a projected or section view based on a section view,
    view content is generated ignoring the parent view section operation.
  */
  bool inheritSection() const;
  /** \details
    Sets the flag indicating whether this view representation should inherit sections from parent views.

    \param inherit [in] A new value of the flag to set.
  */
  void setInheritSection(bool inherit);

  /** \details
    Traverses the internal object structure to find an associated view symbol (section or detail).

    \returns
    Object ID of either an OdDbSectionSymbol or OdDbDetailSymbol entity
    that defines the content of this view representation.
  */
  OdDbObjectId lookUpSectionSymbol() const;

  /** \details
    Creates a new view representation in the specified database.

    \param db [in] Database in which to create the view representation.
    \param params [in] Structure filled with initial params for the new view representation.
    \param viewSymbol [in] Optional. The filled template view symbol entity.
      When creating a section view representation, this parameter points to an OdDbSectionSymbol entity
      with section points and optionally other properties defined.
      When creating a detail view representation, this parameter points to an OdDbDetailSymbol entity
      with position, size, and optionally other properties defined.

    \returns
    Smart pointer to the newly created OdDbViewRep object.

    \remarks
    This method also creates all necessary associated network and model documentation infrastructure objects
    in the specified OdDbDatabase. If this function succeeds, it returns a pointer to
    a ready-to-use view representation object. You can use this pointer to set or extract a view's properties
    and traits that were initialized with defaults during execution.
  */
  static OdSmartPtr<OdDbViewRep> createViewRep( OdDbDatabase* db, const OdDbViewInitParams& params,
    const OdDbViewSymbol* viewSymbol = nullptr );

  /** \details
    Generates projected HLR segments and fills them with database entities in the displayed view representation block.
    It checks whether the view or source model was changed and regenerates graphics only when necessary.
  */
  //OdResult generateGraphics();

  //DOM-IGNORE-BEGIN
  /** \details
    For internal use.
  */
  OdDbViewRepBodyManager* bodyManager();
  /** \details
    For internal use.
  */
  const OdDbViewRepBodyManager* bodyManager() const;

  /** \details
    For internal use.
  */
  void clearBodyManager();

  /** \details
    For internal use.
  */
  bool bodyOverridesLoaded() const;

  /** \details
    For internal use.
  */
  OdResult loadBodyOverrides();
  //DOM-IGNORE-END

  virtual void subClose() override;

protected:
  // OdDbObject methods :
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;
  void applyPartialUndo(OdDbDwgFiler* undoFiler, OdRxClass* pClass) override;

  friend class OdDbImpAssocViewRepActionBody;
  friend class OdDbAssocViewRepActionBodyEvaluator;

private:
  void setRotationAngle(double angle);

};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbViewRep object pointers.
*/
typedef OdSmartPtr<OdDbViewRep> OdDbViewRepPtr;

/** \details
  Converts ODA-incompatible ModelDoc views to ODA-compatible form.

  \param db [in]  database in which to perform view conversion.
  \param idwWarning [out]  optional pointer to string which receves .idw data reading warning.

  \returns
  the number of converted views

  \remarks
  If warning string is not empty it contatins the description of the .idw data reading error.
  Views still can be converted but some view style information may be lost.
*/
MODELDOCOBJ_EXPORT int odmdConvertViews(OdDbDatabase* db, OdString* idwWarning = 0);

#include "TD_PackPop.h"

#endif // OD_VIEWREP_H
