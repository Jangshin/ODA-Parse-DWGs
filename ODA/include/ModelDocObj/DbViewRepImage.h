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

#ifndef OD_VIEWREPIMAGE_H
#define OD_VIEWREPIMAGE_H

#include "DbEntity.h"
#include "ModelDocObjExports.h"
#include "Gi/GiImage.h"
#include "Gi/GiViewportDraw.h"
#include "Gi/GiRasterWrappers.h"

#include "TD_PackPush.h"

/** \details

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 
*/
class MODELDOCOBJ_EXPORT OdDbViewRepImage : public OdDbEntity
{
public:
  ODDB_DECLARE_MEMBERS(OdDbViewRepImage);

  OdDbViewRepImage();
  virtual ~OdDbViewRepImage();


	OdGePoint3d const &  centerPoint() const;
	void setCenterPoint(OdGePoint3d const & );

	double getHeight() const;
	void setHeight(double);

	double getWidth() const;
	void setWidth(double);

	OdDbObjectId ownerViewportId() const;
	void setOwnerViewportId(const OdDbObjectId);

  /*
	OdGeMatrix3d getModelCoordinate() const;
	void setModelCoordinate(OdGeMatrix3d const & );

	OdUInt8* getRawImageBytes() const;
	void setRawImageBytes(OdUInt8*);

	virtual void saveAs(OdGiWorldDraw*, OdDb::SaveType);

	void setImageData(unsigned char*);

	virtual OdResult subTransformBy(OdGeMatrix3d const&);
   */
  void setImageData(const OdGiImageBGRA32& imageBGRA32);

  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;
protected:
  // OdDbObject methods :
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subClose();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbViewRepImage object pointers.
*/
typedef OdSmartPtr<OdDbViewRepImage> OdDbViewRepImagePtr;

#include "TD_PackPop.h"

#endif // OD_VIEWREPIMAGE_H
