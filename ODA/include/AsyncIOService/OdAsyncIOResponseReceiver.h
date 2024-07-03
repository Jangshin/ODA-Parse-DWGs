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

#ifndef _OD_ASYNC_IO_RESPONSE_RECEIVER__INCLUDED_
#define _OD_ASYNC_IO_RESPONSE_RECEIVER__INCLUDED_

#include "RootExport.h"
#include "RxObject.h"
#include "OdAsyncIOResult.h"

#include "TD_PackPush.h"

/**
  <group OdAsyncIO_Classes>
  \details
  This is an interface class of response receiver.
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdAsyncIOResponseReceiver : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdAsyncIOResponseReceiver);

  /** \details
    Destructor for the OdAsyncIOResponseReceiver class.
  */
  virtual ~OdAsyncIOResponseReceiver(){}

  /** \details
    Method to process the result of open request.

    \param requestDescriptor [in] Request descriptor.
    \param fileDescriptor [in] File descriptor.
    \param status [in] Request status.
  */
  virtual void receiveOpenRequestResponse(OdUInt64 requestDescriptor, OdUInt64 fileDescriptor, OdAsyncIO::OdAsyncIOResult status) = 0;

  /** \details
    Method to process the result of read request.

    \param requestDescriptor [in] Request descriptor.
    \param pData [in] Data buffer.
    \param actualDataSize [in] Actual data size.
    \param status [in] Request status.
  */
  virtual void receiveReadRequestResponse(OdUInt64 requestDescriptor, const OdUInt8* pData, OdUInt32 actualDataSize, OdAsyncIO::OdAsyncIOResult status) = 0;

  /** \details
    Method to process the result of write request.

    \param requestDescriptor [in] Request descriptor.
    \param status [in] Request status.
  */
  virtual void receiveWriteRequestResponse(OdUInt64 requestDescriptor, OdAsyncIO::OdAsyncIOResult status) = 0;
};

/** \details
  A data type that represents a smart pointer to OdAsyncIOResponseReceiver object.
*/
typedef OdSmartPtr<OdAsyncIOResponseReceiver> OdAsyncIOResponseReceiverPtr;

#include "TD_PackPop.h"

#endif
