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
// GLES2 device definitions

#ifndef ODBASETRVECDEVICEDEFINITIONS
#define ODBASETRVECDEVICEDEFINITIONS

#include "../TrVisDefs.h"
#include "../TrVisLightDef.h"

/** \details
    <group ExRender_Windows_Classes> 
*/
struct OdTrVecLightDef : public OdTrVisLightDef
{ OdUInt32 m_nDuplicate;
  OdString m_webFile;
  OdStreamBufPtr m_pWebStream;
  enum { kOverrideDuplicate = kLastOverride << 1,
         kOverrideWebFile   = kLastOverride << 2,
         kOverrideWebStream = kLastOverride << 3
  };
  void setDefault()
  { 
    OdTrVisLightDef::setDefault();
    m_nDuplicate = 0; m_webFile = OdString::kEmpty; 
    if (!m_pWebStream.isNull())
      m_pWebStream->release();
  }
  OdTrVecLightDef &apply(OdUInt32 nMod, const OdTrVecLightDef &l)
  { if (nMod != 0xFFFFFFFF)
    { OdTrVisLightDef::apply(nMod, l);
      if (GETBIT(nMod, kOverrideDuplicate))
        m_nDuplicate = l.m_nDuplicate;
      if (GETBIT(nMod, kOverrideWebFile))
        m_webFile = l.m_webFile;
      if (GETBIT(nMod, kOverrideWebStream))
        m_pWebStream = l.m_pWebStream;
    } else
      *this = l;
    return *this; }
  OdUInt32 diff(const OdTrVecLightDef &dl2, bool bFinFirstDiff = false) const
  { 
    OdUInt32 axxum = OdTrVisLightDef::diff(dl2, bFinFirstDiff);
    if (axxum != 0xFFFFFFFF)
    {
      if (m_nDuplicate != dl2.m_nDuplicate)
      { if (bFinFirstDiff)
          return 0xFFFFFFFF;
        SETBIT_1(axxum, kOverrideDuplicate);
      }
      if (m_webFile != dl2.m_webFile)
        return (bFinFirstDiff) ? 0xFFFFFFFF : (axxum | kOverrideWebFile);
      if ((m_pWebStream.isNull() && !dl2.m_pWebStream.isNull()) || (!m_pWebStream.isNull() && dl2.m_pWebStream.isNull()))
        return (bFinFirstDiff) ? 0xFFFFFFFF : (axxum | kOverrideWebStream);
      else if (!m_pWebStream.isNull() && !dl2.m_pWebStream.isNull())
      {
        if (const_cast<OdTrVecLightDef*>(this)->m_pWebStream->length() != const_cast<OdTrVecLightDef&>(dl2).m_pWebStream->length())
          return (bFinFirstDiff) ? 0xFFFFFFFF : (axxum | kOverrideWebStream);

        void* pData = NULL; OdUInt32 nBytes = 0;
        const_cast<OdTrVecLightDef*>(this)->m_pWebStream->getBytes(pData, nBytes);
        void* pData2 = NULL; OdUInt32 nBytes2 = 0;
        const_cast<OdTrVecLightDef&>(dl2).m_pWebStream->getBytes(pData2, nBytes2);
        if (nBytes != nBytes2)
          return (bFinFirstDiff) ? 0xFFFFFFFF : (axxum | kOverrideWebStream);
        if (pData != NULL && pData2 != NULL)
        {
          char* charPtr1 = static_cast<char*>(pData);
          char* charPtr2 = static_cast<char*>(pData2);
          if (strncmp(charPtr1, charPtr2, nBytes) != 0)
            return (bFinFirstDiff) ? 0xFFFFFFFF : (axxum | kOverrideWebStream);
        }
      }
    } 
    return axxum; }
  bool operator ==(const OdTrVecLightDef &dl2) const
  { return diff(dl2, true) == 0; }
  bool operator !=(const OdTrVecLightDef &dl2) const
  { return diff(dl2, true) != 0; }
};

#endif // ODBASETRVECDEVICEDEFINITIONS
