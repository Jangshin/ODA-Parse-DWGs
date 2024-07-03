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

#ifndef _OD_ASYNC_IO_SERVICE__INCLUDED_
#define _OD_ASYNC_IO_SERVICE__INCLUDED_

#include "RootExport.h"
#include "RxObject.h"
#include "OdAsyncIORequestHandler.h"
#include "OdAsyncIOResponseReceiver.h"

#include "TD_PackPush.h"

/**
  <group OdAsyncIO_Classes>
  \details
  This is an interface class to implement asynchronous I/O operations.
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdAsyncIOService : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdAsyncIOService);

  /** \details
    Destructor for the OdAsyncIOService class.
  */
  virtual ~OdAsyncIOService(){}
  
  /** \details
    Gets I/O request handler.

    \returns
    Pointer to OdAsyncIORequestHandler object.
  */
  virtual OdAsyncIORequestHandlerPtr getRequestHandler() = 0;

  /** \details
    Registers new response receiver.

    \param pReceiver [in] Pointer to OdAsyncIOResponseReceiver object.

    \returns
    Receiver descriptor as OdUInt64 value.
  */
  virtual OdUInt64 registerResponseReceiver(OdAsyncIOResponseReceiver* pReceiver) = 0;

  /** \details
    Unregisters the response receiver.

    \param receiverDescriptor [in] Receiver descriptor.
  */
  virtual void unregisterResponseReceiver(OdUInt64 receiverDescriptor) = 0;

  /** \details
    Sends the result of processing the open file request to the receiver.

    \param receiverDescriptor [in] Receiver descriptor.
    \param requestDescriptor [in] Request descriptor.
    \param fileDescriptor [in] File descriptor.
    \param status [in] Request status.
  */
  virtual void receiveOpenRequestResponse(OdUInt64 receiverDescriptor, OdUInt64 requestDescriptor, OdUInt64 fileDescriptor, OdAsyncIO::OdAsyncIOResult status) = 0;

  /** \details
    Sends the result of processing the read request to the receiver.

    \param receiverDescriptor [in] Receiver descriptor.
    \param requestDescriptor [in] Request descriptor.
    \param pData [in] Data buffer.
    \param actualDataSize [in] Actual data size.
    \param status [in] Request status.
  */
  virtual void receiveReadRequestResponse(OdUInt64 receiverDescriptor, OdUInt64 requestDescriptor, const OdUInt8* pData, OdUInt32 actualDataSize, OdAsyncIO::OdAsyncIOResult status) = 0;

  /** \details
    Sends the result of processing the write request to the receiver.

    \param receiverDescriptor [in] Receiver descriptor.
    \param requestDescriptor [in] Request descriptor.
    \param status [in] Request status.
  */
  virtual void receiveWriteRequestResponse(OdUInt64 receiverDescriptor, OdUInt64 requestDescriptor, OdAsyncIO::OdAsyncIOResult status) = 0;
};

/** \details
  A data type that represents a smart pointer to OdAsyncIOService object.
  */
typedef OdSmartPtr<OdAsyncIOService> OdAsyncIOServicePtr;

/** \details
  Function to initialize async I/O service.

  \param pRequestHandler [in] Pointer to request handler object.
  */
FIRSTDLL_EXPORT void odInitAsyncIOService(OdAsyncIORequestHandler* pRequestHandler);

/** \details
  Function to get access to async I/O service.

  \returns
  Pointer to OdAsyncIOService object.
  */
FIRSTDLL_EXPORT OdAsyncIOService* odGetAsyncIOService();

/** \details
  Function to uninitialize async I/O service.
  */
FIRSTDLL_EXPORT void odUninitAsyncIOService();

#include "TD_PackPop.h"

#endif
