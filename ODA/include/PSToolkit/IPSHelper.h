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


#ifndef __IPSHELPER_H__
#define __IPSHELPER_H__

#include "PSExport.h"
#include "OdStreamBuf.h"

class OdBrBrep;

/** \details
    This class is the base class for classes that provide platform-dependent loading and saving
    of Parasolid files.

    Corresponding C++ library: TG_Db
    <group OdDg_Classes>
*/
class PS_EXPORT IPSHelper
{
public:
  /** \details
      Loads the specified Parasolid file.
      \param pStreamBuf [in]  Pointer to the StreamBuf object from which the data are to be read.
      \returns
      Returns true if and only if successful
  */
  virtual bool in(OdStreamBuf* pStreamBuf) = 0;
  /** \details
      Saves the specified Parasolid file.
      \param pStreamBuf [in]  Pointer to the StreamBuf object to which the data are to be written.
      \returns
      Returns true if and only if successful
  */
  virtual bool out(OdStreamBuf* pStreamBuf) = 0;
  /** \details
    Gets the pointer to the Parasolid file.
    \returns
    Pointer to the Parasolid file object.
  */
  virtual void* getIBr() = 0;

  virtual ~IPSHelper();
};

PS_EXPORT IPSHelper* createPSHelper();

PS_EXPORT void deletePSHelper(IPSHelper* pIC);

PS_EXPORT IPSHelper* getPSHelper(OdBrBrep& brep);

PS_EXPORT bool breakPSToSingleBody(OdStreamBuf* pStreamBuf, OdArray<IPSHelper*>& entitySet);

PS_EXPORT IPSHelper* mergePSHelpers(const OdArray<IPSHelper*>& entitySet);

#endif // __IPSHELPER_H__
