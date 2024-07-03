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
#ifndef ODRXSKETCHMANAGER_H_
#define ODRXSKETCHMANAGER_H_

#include "RxObject.h"


#include "ModelDocObjExports.h"
#include "TD_PackPush.h"
#include "RxSketchObject.h"

class OdRxSketchManagerImpl;

/** <group OdModelDocObj_Classes>
*/
class MODELDOCOBJ_EXPORT OdRxSketchManager : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS( OdRxSketchManager );
  OdRxSketchManager();
  virtual ~OdRxSketchManager();

  virtual OdResult dwgInFields( OdDbDwgFiler* pFiler );
  virtual void dwgOutFields( OdDbDwgFiler* pFiler ) const;
  virtual OdResult dxfInFields( OdDbDxfFiler* pFiler );
  virtual void dxfOutFields( OdDbDxfFiler* pFiler ) const;

  
  //virtual OdResult applyPartialUndo( AcDbDwgFiler *, unsigned short );
  void clearSketchObjects();
  OdDbObjectId constructionLineType()const;
  void addSketch( OdRxSketchObject* sketch );
  void deleteSketch( OdRxSketchObject const *pSketchObj );
  OdResult enterSketchMode( OdRxSketchObject *pSketchObj );
  OdResult exitSketchMode();
  OdRxSketchObject *  getActiveSketch();
  OdRxSketchObject *  getSketchFromTag( unsigned short tag );
  OdRxSymbolSketch *  getSymbolSketchFromSymbol( const OdDbObjectId &symbolId );
  OdRxSymbolSketch *  getSymbolSketchFromViewRep( const OdDbObjectId &viewRepId );
  bool hasSketchObjects() const;
  bool isDirty() const;
  bool isInSketchMode() const;
  OdDbObjectId owningViewRep() const;  
  void setIsDirty( bool bDirty );
  OdDbObjectId sketchBlockReference() const;
  void transformSketches( const OdGeMatrix3d &matrix );
  void updateConstraintGroupWorkPlanes( const OdGePlane &plane );
  void getSketchesByClass(OdRxClass* sketchClass, OdArray<OdRxSketchObjectPtr>& foundSketches);

  OdRxSketchManagerImpl* getImpl() { return m_pImpl; }
protected:
  friend class OdDbViewRep;
  friend class OdDbViewRepImpl;
  OdRxSketchManagerImpl* m_pImpl;
};

#include "TD_PackPop.h"

typedef OdSmartPtr<OdRxSketchManager> OdRxSketchManagerPtr;

#endif //#ifndef ODRXSKETCHMANAGER_H_
