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

#ifndef __ODGIDGLINETYPER_H__
#define __ODGIDGLINETYPER_H__

#include "Gi/GiLinetyper.h"
// #include "Gi/GiDgLinetype.h"

#include "TD_PackPush.h"

class OdGiDgLinetypeTraits;

/** \details

    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiDgLinetyper : public OdGiLinetyper
{
public:
  ODRX_DECLARE_MEMBERS(OdGiDgLinetyper);

  /** \details
    Retrieves Dgn-specific linetype traits.
    \returns
    Reference to OdGiDgLinetypeTraits object that contains Dgn-specific linetype traits.
  */
  virtual OdGiDgLinetypeTraits& dgLinetypeTraits() const = 0;
};

/** \details
  The data type that represents a smart pointer to the <link OdGiDgLinetyper, OdGiDgLinetyper> object.
*/
typedef OdSmartPtr<OdGiDgLinetyper> OdGiDgLinetyperPtr;

#include "TD_PackPop.h"

#endif //#ifndef __ODGIDGLINETYPER_H__
