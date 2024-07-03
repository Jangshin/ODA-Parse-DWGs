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


#ifndef _OdErrorContext_h_Included_
#define _OdErrorContext_h_Included_

#include "OdaDefs.h"
#include "RxObjectImpl.h"
#include "OdString.h"

#include "TD_PackPush.h"

/** \details
    This class implements a node in an ErrorContext stack.
    
    \remarks
    Each ErrorContext object points to the previous ErrorContext object in the stack.
    Note that this class is not registered in ODA RTTI, so be careful when storing these objects in OdSmartPtr
    (use dynamic_cast if necessary)

    Corresponding C++ library: TD_Root
    <group Error_Classes> 
*/
class FIRSTDLL_EXPORT OdErrorContext : public OdRxObject
{
protected:
  OdErrorContext* m_pPreviousError;
  OdErrorContext() : m_pPreviousError(0) {}
  /** \details
    Constructor for the OdErrorContext class.
    
    \param pPreviousError [in]  Pointer to the previous ErrorContext object.
  */
  OdErrorContext(OdErrorContext* pPreviousError);
public:

  /** \details
    Destructor for the OdErrorContext class.
  */
  virtual ~OdErrorContext();
  
  /** \details
    Returns the description of this ErrorContext object.
  */
  virtual OdString description() const = 0;
  
  /** \details
    Returns the OdResult code of this ErrorContext object.
  */
  virtual OdResult code() const = 0;
  
  /** \details
    Returns the complete description of this ErrorContext object.
    \remarks
    completeDescription() returns a string containing the concatenation of
    all of the description strings in the ErrorContext stack.
    
    The default implementation of this function returns a string in the following format:
            
                   <Description n-1>\n
                    Previous error: <Description n-2>\n
                    Previous error: <Description n-3>\n
                    ...
                    Previous error: <Description 0>\n
  */
  OdString completeDescription() const;
  /** \details
    Returns the ErrorContext object previous to this one in this ErrorContext stack.
  */
  OdErrorContext* getPreviousError() const { return m_pPreviousError; }

  /** \details
    Sets the ErrorContext object previous to this one in this ErrorContext stack.
    \param pPreviousError [in]  Pointer to the previous ErrorContext object.
  */
  void setPreviousError(OdErrorContext* pPreviousError);
};

/*  \details
  This class is used by OdError constructed from an error code
*/
class FIRSTDLL_EXPORT OdDefaultErrorContext : public OdErrorContext
{
  OdResult m_res;
public:
  /** \details
    Constructor for the OdDefaultErrorContext class.
    \param err [in] Error code
    \param pPreviousError [in]  Pointer to the previous ErrorContext object.
  */
  OdDefaultErrorContext(OdResult err, OdErrorContext* pPreviousError = nullptr);
  /** \details
    Returns the OdResult code of this ErrorContext object.
  */
  virtual OdResult code() const override;
  /** \details
    Returns the description of this ErrorContext object.
    (calls odrxSystemServices()->formatMessage(code()) by default)
  */
  virtual OdString description() const override;
};

/*  \details
  This class is used by OdError constructed from an error message.
*/
class FIRSTDLL_EXPORT OdUserErrorContext : public OdErrorContext
{
  OdString m_sErrorMessage;
public:
  /** \details
    Constructor for the OdUserErrorContext class.
    \param szErrorMessage [in] Error message
    \param pPreviousError [in]  Pointer to the previous ErrorContext object.
  */
  OdUserErrorContext(const OdString& szErrorMessage, OdErrorContext* pPreviousError = nullptr);
  /** \details
    Returns the OdResult code of this ErrorContext object. (eExtendedError by default)
  */
  virtual OdResult code() const override;
  /** \details
    Returns the description of this ErrorContext object.
  */
  virtual OdString description() const override;
};

/*  \details
  This class is used by OdError_FileException and its descendants
*/
class FIRSTDLL_EXPORT OdFileExceptionContext : public OdDefaultErrorContext
{
  OdString m_fileName;
  OdString m_extended;
public:
  /** \details
    Constructor for the OdFileExceptionContext class.
    \param error [in] Error code
    \param fileName [in] File name
    \param extended [in] Additional information
    \param pPreviousError [in]  Pointer to the previous ErrorContext object.
  */
  OdFileExceptionContext(OdResult error, const OdString& fileName, const OdString& extended = OdString::kEmpty, OdErrorContext* pPreviousError = nullptr);
  /** \details
    Returns the file name for which this exception was generated
  */
  OdString getFileName() const;
  /** \details
    Returns the description of this ErrorContext object.
  */
  virtual OdString description() const override;
};

#include "TD_PackPop.h"

#endif
