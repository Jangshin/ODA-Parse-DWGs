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

#ifndef _OD_POINTCLOUD_DATABASE_RECEIVER__INCLUDED_
#define _OD_POINTCLOUD_DATABASE_RECEIVER__INCLUDED_

#include "RootExport.h"
#include "RxObject.h"
#include "OdPointCloudScanDatabase.h"
#include "OdPointCloudProjectDatabase.h"

#include "TD_PackPush.h"

/**
  <group OdRcs_Classes>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdPointCloudDatabaseReceiver : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdPointCloudDatabaseReceiver);

  virtual ~OdPointCloudDatabaseReceiver() {}

  virtual void receiveIndividualScanDb(OdPointCloudScanDatabasePtr pScanDb, bool dbIsOk = false) = 0;

  virtual void receiveProjDb(OdPointCloudProjectDatabasePtr pProjDb, bool dbIsOk = false) = 0;
};

typedef OdSmartPtr<OdPointCloudDatabaseReceiver> OdPointCloudDatabaseReceiverPtr;

#include "TD_PackPop.h"

#endif
