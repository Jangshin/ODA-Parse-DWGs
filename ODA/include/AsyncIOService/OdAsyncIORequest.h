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

#ifndef _OD_ASYNC_IO_REQUEST__INCLUDED_
#define _OD_ASYNC_IO_REQUEST__INCLUDED_

#include "OdAsyncBaseRequest.h"

#include "TD_PackPush.h"

/**
  <group OdAsyncIO_Classes>
  \details
  This class is a special data structure to represent input/output request.
*/
class OdAsyncIORequest : public OdAsyncBaseRequest
{
public:

  /** \details
    Constructor for the OdAsyncIORequest class.
  */
  OdAsyncIORequest()
    : m_fileDescriptor(0), m_offset(0), m_size(0), m_pBuf(0)
  {
  }

  /** Descriptor the file on which the I/O operation is being performed.*/
  OdUInt64 m_fileDescriptor;

  /** Offset in target file to perform I/O operation.*/
  OdUInt64 m_offset;

  /** Number of bytes to read/write.*/
  OdUInt64 m_size;

  /** Pointer to a user-allocated buffer that should contain the data to be written (only used for the write operation).*/
  OdUInt8* m_pBuf;
};

#include "TD_PackPop.h"

#endif
