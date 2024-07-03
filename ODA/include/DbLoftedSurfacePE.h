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

#ifndef _OD_DB_LSURF_PE_
#define _OD_DB_LSURF_PE_


#include "DbLoftedSurface.h"

/** \details
    This class defines the interface for the lofted surface Protocol Extension classes.
    
    
    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbLoftedSurfacePE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbLoftedSurfacePE);

  /** \details
  Returns the type of lofted surface.

   \returns Loft surface type:  ordinary loft, blend, or network.
  */
  virtual OdDbLoftedSurface::LoftSurfaceType loftSurfaceType(const OdDbObject* pObj) const = 0;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbCurvePE object pointers.
*/
typedef OdSmartPtr<OdDbLoftedSurfacePE> OdDbLoftedSurfacePEPtr;

#endif //_OD_DB_LSURF_PE_
