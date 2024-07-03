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

#ifndef _OD_ASYNC_IO_REQUEST_HANDLER__INCLUDED_
#define _OD_ASYNC_IO_REQUEST_HANDLER__INCLUDED_

#include "RootExport.h"
#include "RxObject.h"
#include "RxSystemServices.h"
#include "OdAsyncIOResult.h"
#include "OdAsyncIORequest.h"
#include "OdAsyncOpenFileRequest.h"

#include "TD_PackPush.h"

/**
  <group OdAsyncIO_Classes>
  \details
  This is an interface class to implement asynchronous I/O operations.
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdAsyncIORequestHandler : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdAsyncIORequestHandler);

  /** \details
    Destructor for the OdAsyncIORequestHandler class.
  */
  virtual ~OdAsyncIORequestHandler(){}

  /** \details
    Registers new request and returns a descriptor to be set in the field m_requestDescriptor of request data structure.
  */
  virtual OdUInt64 newRequestDescriptor() = 0;
  
  /** \details
    Executes a request to open a file.

    \param request [in] Request data structure.
  */
  virtual void openFile(const OdAsyncOpenFileRequest& request) = 0;

  /** \details
    Closes the file corresponding to the file descriptor value.

    \param fileDescriptor [in] File descriptor.
  */
  virtual void closeFile(OdUInt64 fileDescriptor) = 0;
  
  /** \details
    Executes a request to read data.

    \param request [in] Request data structure.
  */
  virtual void read(const OdAsyncIORequest& request) = 0;

  /** \details
    Executes a request to write data.

    \param request [in] Request data structure.
  */
  virtual void write(const OdAsyncIORequest& request) = 0;
  
  /** \details
    Synchronous method for getting the request result.
    Intended to be used if the flag m_bAsyncNotification in request data structure was set to false.

    \param requestDescriptor [in] Request descriptor.
    \param pOpenedFileDescriptor [out] Descriptor of successfully opened file if a request to open a file is made. When calling the method, pass 0 if the result of a read/write request is being checked.
    \param pDataPtr [out] Pointer to the data if the read request was successful.
    \param pActualDataSize [out] The actual size of the data that was read.

    \returns
    The status of the request as OdAsyncIO::OdAsyncIOResult value.
  */
  virtual OdAsyncIO::OdAsyncIOResult returnResult(OdUInt64 requestDescriptor,
    OdUInt64* pOpenedFileDescriptor = NULL,
    OdUInt8** pDataPtr = NULL, OdUInt32* pActualDataSize = NULL) = 0;

  /** \details
    Method to cancel request.

    \param requestDescriptor [in] Request descriptor.
  */
  virtual void cancel(OdUInt64 requestDescriptor) = 0;

  /** \details
    Method to confirm that the response to the request has been received.

    \param requestDescriptor [in] Request descriptor.
  */
  virtual void responseParsed(OdUInt64 requestDescriptor) = 0;
};

/** \details
  A data type that represents a smart pointer to OdAsyncIORequestHandler object.
*/
typedef OdSmartPtr<OdAsyncIORequestHandler> OdAsyncIORequestHandlerPtr;

#include "TD_PackPop.h"

#endif
