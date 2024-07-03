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

#ifndef _DbBlocksActions_h_Included_
#define _DbBlocksActions_h_Included_

#include "DbEvalGraph.h"
#include "Ge/GePoint2dArray.h"
#include "DbBlockElement.h"
#include "DbBlockParameter.h"

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockAction : public OdDbBlockElement
{
public:
  enum OdDbBlockActionXYType{ XY, X, Y };
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockAction);
  virtual OdGePoint3d displayLocation() const;
  virtual void setDisplayLocation(const OdGePoint3d&);
  virtual OdDbEvalNodeId drivingParameterNodeId() const;
  OdDbObjectIdArray elementSelectionSet() const;

  virtual OdDbObjectIdArray selectionSet() const;
  virtual OdDbBlockParameterPtr getAssociatedParameter(OdDb::OpenMode mode = OdDb::kForRead) const;
  virtual void setSelectionSet(const OdDbObjectIdArray&);
  virtual void adjacentNodeRemoved(const OdDbEvalNodeId&) override;
};

typedef OdSmartPtr<OdDbBlockAction> OdDbBlockActionPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockMoveAction : public OdDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockMoveAction);
  OdDbBlockMoveAction();
  double angleOffset() const;
  double distanceMultiplier() const;
  OdDbBlockActionXYType distanceType() const;
  void setAngleOffset(double);
  void setDistanceMultiplier(double);
  void setDistanceType(OdDbBlockActionXYType);
};

typedef OdSmartPtr<OdDbBlockMoveAction> OdDbBlockMoveActionPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockStretchAction : public OdDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockStretchAction);
  OdDbBlockStretchAction();
  double angleOffset() const;
  double distanceMultiplier() const;
  OdDbBlockActionXYType distanceType() const;
  void setAngleOffset(double);
  void setDistanceMultiplier(double);
  void setDistanceType(OdDbBlockActionXYType);
  void setStretchFrame(const OdGePoint2dArray&);
  OdGePoint2dArray stretchFrame() const;
  virtual void setSelectionSet(const OdDbObjectIdArray&);
};

typedef OdSmartPtr<OdDbBlockStretchAction> OdDbBlockStretchActionPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockActionWithBasePt : public OdDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockActionWithBasePt);
  OdGePoint3d basePoint() const;
  OdGeVector3d basePointOffset() const;
  bool dependent() const;
  void setBasePoint(OdGePoint3d const&);
  void setBasePointOffset(OdGeVector3d const&);
  void setDependent(bool);
};

typedef OdSmartPtr<OdDbBlockActionWithBasePt> OdDbBlockActionWithBasePtPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockScaleAction : public OdDbBlockActionWithBasePt
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockScaleAction);
  OdDbBlockScaleAction();
  OdDbBlockActionXYType scaleType() const;
  void setScaleType(OdDbBlockActionXYType);
};

typedef OdSmartPtr<OdDbBlockScaleAction> OdDbBlockScaleActionPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockRotateAction : public OdDbBlockActionWithBasePt
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockRotateAction);
  OdDbBlockRotateAction();
};

typedef OdSmartPtr<OdDbBlockRotateAction> OdDbBlockRotateActionPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockFlipAction : public OdDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockFlipAction);
  OdDbBlockFlipAction();
};

typedef OdSmartPtr<OdDbBlockFlipAction> OdDbBlockFlipActionPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockArrayAction : public OdDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockArrayAction);
  OdDbBlockArrayAction();
  double columnOffset() const;
  double rowOffset() const;
  void setColumnOffset(double);
  void setRowOffset(double);
};

typedef OdSmartPtr<OdDbBlockArrayAction> OdDbBlockArrayActionPtr;

class OdDbDataTable;
typedef OdSmartPtr<OdDbDataTable>OdDbDataTablePtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockLookupAction : public OdDbBlockAction
{
public:
  struct ColumnInfo
  {
    OdDbEvalNodeId m_nParameterId = OdDbEvalGraph::kNullNodeId;
    OdInt32 m_nResType = 0;
    OdInt32 m_nType = 0; // unit type?
    bool m_bLookupProperty = true; // or input property
    bool m_bNotReadonly = true; // allows reverse lookup
    OdString m_sUnmatched;
    OdString m_sConnection;
  };
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockLookupAction);
  OdDbBlockLookupAction();
  //bool duplicateCellsInLookupColumn(int,int *);
  //bool duplicateCellsInLookupColumn( const OdResBufArray&, const OdArray<void*>&,int,int *);
  //bool duplicateRowsOverInputColumns(int *);
  //bool duplicateRowsOverInputColumns( const OdResBufArray &, const OdArray<void*>&,int *);
  //OdDbDataTablePtr getLookupTable( OdArray<void*> & );

  void getLookupTable(OdResBufArray&, OdArray<const ColumnInfo*>&) const;
  //bool nonSingletonRangeInInputColumns(int *);
  //bool nonSingletonRangeInInputColumns( const OdResBufArray &,const OdArray<void*>&,int *);
  //bool nullsInInputColumns(int *);
  //bool nullsInInputColumns( const OdResBufArray&, const OdArray<void*>&,int *);

  OdUInt32 numberOfInputColumns() const;
  OdUInt32 numberOfOutputColumns() const;
  OdUInt32 numberOfColumns() const;
  OdUInt32 numberOfRows() const;
  //void setLookupTable( const OdResBufArray &, OdArray<void*> const &);
  //void setLookupTable( const OdDbDataTable *, OdArray<void*>&);
};

typedef OdSmartPtr<OdDbBlockLookupAction>OdDbBlockLookupActionPtr;

/** \details

    
    <group OdDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdDbBlockPolarStretchAction : public OdDbBlockAction
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdDbBlockPolarStretchAction);
  OdDbBlockPolarStretchAction();
  double angleOffset() const;
  double distanceMultiplier() const;
  OdGePoint2dArray stretchFrame() const;
  OdDbObjectIdArray rotateOnlyElementSelectionSet() const;
  OdDbObjectIdArray rotateOnlySelectionSet() const;

  void setAngleOffset(double);
  void setDistanceMultiplier(double);
  void setStretchFrame(const OdGePoint2dArray&);
  void setRotateOnlySelectionSet(const OdDbObjectIdArray&);
  virtual void setSelectionSet(const OdDbObjectIdArray&);
};

typedef OdSmartPtr<OdDbBlockPolarStretchAction> OdDbBlockPolarStretchActionPtr;

#endif // _DbBlocksActions_h_Included_