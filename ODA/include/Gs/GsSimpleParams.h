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

#ifndef __ODGSSIMPLEPARAMS_H_INCLUDED_
#define __ODGSSIMPLEPARAMS_H_INCLUDED_

#include "Ge/GeMatrix3d.h"

#include "TD_PackPush.h"

/** \details
    This is a base class for simple container parameters.

    <group OdGs_Classes> 
*/
class FIRSTDLL_EXPORT ODRX_ABSTRACT OdGsSimpleParam : public OdRxObject
{
  public:
    ODRX_DECLARE_MEMBERS(OdGsSimpleParam);
    /** \details
        Default construction. Does nothing.
    */
    OdGsSimpleParam() {}
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGsSimpleParam object pointers.
*/
typedef OdSmartPtr<OdGsSimpleParam> OdGsSimpleParamPtr;


/** \details
    Simple integer container.

    Corresponding C++ library: TD_Gs

    <group OdGs_Classes> 
*/
class GS_TOOLKIT_EXPORT OdGsIntParam : public OdGsSimpleParam
{
  protected:
    OdUInt32 m_intVal;
  public:
    /** \details
        Default construction. Sets matrix to identity.
    */
    OdGsIntParam() : m_intVal(0) {}
    
    /** \details
        Sets integer value.
        \param intVal [in] Integer value.
    */
    void setValue(OdUInt32 intVal) { m_intVal = intVal; }
    
    /** \details
        Returns integer value.
    */
    OdUInt32 value() const { return m_intVal; }

    /** \details
        Create OdGsIntParam object.
        \param nVal [in] Initial value;
        \returns
        Smart pointer to created object.
    */
    static OdSmartPtr<OdGsIntParam> createObject(OdUInt32 nVal = 0);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGsIntParam object pointers.
*/
typedef OdSmartPtr<OdGsIntParam> OdGsIntParamPtr;

/** \details
    Simple matrix container.

    Corresponding C++ library: TD_Gs

    <group OdGs_Classes> 
*/
class GS_TOOLKIT_EXPORT OdGsMatrixParam : public OdGsSimpleParam
{
  protected:
    OdGeMatrix3d m_xForm;
  public:
    /** \details
        Default construction. Sets matrix to identity.
    */
    OdGsMatrixParam() {}
    /** \details
        Sets transformation matrix.
        \param xForm [in] Transformation matrix to set.
    */
    void setValue(const OdGeMatrix3d &xForm) { m_xForm = xForm; }
    /** \details
        Returns transformation matrix.
    */
    const OdGeMatrix3d &value() const { return m_xForm; }

    /** \details
        Creates OdGsMatrixParam object.
        \param xValue [in] Input matrix.
        
        \returns
        Smart pointer to the created object.
    */
    static OdSmartPtr<OdGsMatrixParam> createObject(const OdGeMatrix3d &xValue = OdGeMatrix3d::kIdentity);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGsMatrixParam object pointers.
*/
typedef OdSmartPtr<OdGsMatrixParam> OdGsMatrixParamPtr;

#include "TD_PackPop.h"

#endif // __ODGSSIMPLEPARAMS_H_INCLUDED_
