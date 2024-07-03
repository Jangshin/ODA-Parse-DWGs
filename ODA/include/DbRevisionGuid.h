/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2023, Open Design Alliance (the "Alliance"). 

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

#pragma once

#include <OdGUID.h>
#include "NextCodeDefs.h"
#include "DbFiler.h"

#include "TD_PackPush.h"

/** \details
  This class represents GUID value.

  Corresponding C++ library: TD_DbCore

  <group OdDb_Classes>
*/
class OdDbRevisionGuid : public OdGUID { // used in Model-Doc feature to reference body geometry revision
public:
  /** \details
    Default constructor for objects of the OdDbRevisionGuid class.

    \remarks
    Constructs a GUID object and sets it to {00000000-0000-0000-0000-000000000000}.
  */
  OdDbRevisionGuid() {};

  /** \details
    Constructs the OdDbRevisionGuid and sets it to a value specified by string representation.

    \param value [in] ASCII string representation of GUID value to initialize the instance
      in the format "{12345678-9ABC-DEF0-1234-56789ABCDEF0}".
  */
  OdDbRevisionGuid(const OdString& value) { 
    *this = value; 
  }

  /** \details
    Assigns a value specified by string representation.

    \param str [in] ASCII string representation of GUID value to set
      in the format "{12345678-9ABC-DEF0-1234-56789ABCDEF0}".
  */
  OdDbRevisionGuid& operator=(const OdString& str) {
    if (str.getLength() != 38 || 
      !(str[0] == '{' && str[9] == '-' && str[14] == '-' && str[19] == '-' && str[24] == '-'  && str[37] == '}'))
    {
      throw OdError(eInvalidInput);
    }
    OdUInt32 data32 = (OdUInt32)(OdUInt64)OdDbHandle(OdString(&str.c_str()[1], 8));
    OdUInt16 data16_1 = (OdUInt16)(OdUInt64)OdDbHandle(OdString(&str.c_str()[10], 4));
    OdUInt16 data16_2 = (OdUInt16)(OdUInt64)OdDbHandle(OdString(&str.c_str()[15], 4));
    OdUInt8 data8[8];
    for (int i = 0; i < 8; ++i) {
      data8[i] =  (OdUInt8)(OdUInt64)OdDbHandle(OdString(&str.c_str()[20 + i*2 + (i < 2 ? 0 : 1)], 2));
    }
    setGUIDdata(data32, data16_1, data16_2, data8);
    return *this;
  }

  /** \details
    Creates new unique GUID value and sets it to a given OdDbRevisionGuid object.

    \param newGuid [out] OdDbRevisionGuid object to initialize with a new unique value.
  */
  static void createGuid(OdDbRevisionGuid &newGuid) {
    newGuid = odrxSystemServices()->createGuid();
  }


  /** \details
    Converts GUID value to ASCII string.

    \returns the ASCII string representing GUID value assigned to this object.
  */
  OdString ascii() const {
    return toString(StringFormat::Braces);
  }

  /** \details
    Loads OdDbRevisionGuid object from a DXF filer.

    \returns eOk if operation was succesful and error code otherwise.
  */
  OdResult dxfInRaw(OdDbDxfFiler* pFiler) { // Model-Doc way
    NEXT_CODE(90);
    OdUInt32 data32 = pFiler->rdInt32();
    NEXT_CODE(70);
    OdUInt16 data16_1 = pFiler->rdInt16();
    NEXT_CODE(70);
    OdUInt16 data16_2 = pFiler->rdInt16();
    OdUInt8 data8[8];
    for (int i = 0; i < 8; ++i) {
      NEXT_CODE(280);
      data8[i] = pFiler->rdInt8();
    }
    setGUIDdata(data32, data16_1, data16_2, data8);
    return eOk;
  }

  /** \details
    Writes OdDbRevisionGuid object to a DXF filer.
  */
  void dxfOutRaw(OdDbDxfFiler* pFiler) const { // Model-Doc way
     const OdUInt8 *RevGUIDData = data();
     pFiler->wrInt32(90, *reinterpret_cast<const OdUInt32*>(RevGUIDData));
     pFiler->wrInt16(70, *reinterpret_cast<const OdUInt16*>(RevGUIDData + 4));
     pFiler->wrInt16(70, *reinterpret_cast<const OdUInt16*>(RevGUIDData + 6));
     for (int i = 0; i < 8; ++i)
       pFiler->wrInt8(280, RevGUIDData[8 + i]);
  }

  /** \details
    Loads OdDbRevisionGuid object from a DWG filer.
  */
  void dwgIn(OdDbDwgFiler* pFiler) {
    OdUInt32 data32 = pFiler->rdInt32();
    OdUInt16 data16_1 = pFiler->rdInt16();
    OdUInt16 data16_2 = pFiler->rdInt16();
    OdUInt8 data8[8];
    for (int i = 0; i < 8; ++i)
      data8[i] = pFiler->rdInt8();
    setGUIDdata(data32, data16_1, data16_2, data8);
  }

  /** \details
    Writes OdDbRevisionGuid object to a DWG filer.
  */
  void dwgOut(OdDbDwgFiler* pFiler) const {
    const OdUInt8 *RevGUIDData = data();
    pFiler->wrInt32(*reinterpret_cast<const OdUInt32*>(RevGUIDData));
    pFiler->wrInt16(*reinterpret_cast<const OdUInt16*>(RevGUIDData + 4));
    pFiler->wrInt16(*reinterpret_cast<const OdUInt16*>(RevGUIDData + 6));
    for (int i = 0; i < 8; ++i)
      pFiler->wrInt8(RevGUIDData[8 + i]);
  }
};

/** \details
  This class represents GUID that may have unspecified value.

  Corresponding C++ library: TD_DbCore

  <group OdDb_Classes>
*/
struct OdRevisionGuid : public OdDbRevisionGuid {
  bool     m_bIsSet;

  /** \details
    Default constructor for objects of the OdRevisionGuid class.

    \remarks
    Constructs the OdRevisionGuid object leaving its value unspecified.
  */
  OdRevisionGuid() : m_bIsSet(false) {}

  /** \details
    Constructs the OdRevisionGuid object and sets it to a value specified by string representation.

    \param value [in] ASCII string representation of GUID value to initialize the instance
      in the format "{12345678-9ABC-DEF0-1234-56789ABCDEF0}".
  */
  OdRevisionGuid(const OdChar* value) {
    *this = value; 
  }

  /** \details
    Loads OdRevisionGuid object from a DXF filer.

    \returns eOk if operation was succesful and error code otherwise.
  */
  void dxfIn(OdDbDxfFiler* pFiler) {
    int nGC = pFiler->nextItem();
    if (nGC == 290) {
      m_bIsSet = pFiler->rdBool();
    }
    else {
      m_bIsSet = false;
      ODA_FAIL_M_ONCE("Unexpected group while reading OdRevisionGuid");
    }
    nGC = pFiler->nextItem();
    if (nGC == 2) {
      OdDbRevisionGuid::operator=(pFiler->rdString());
    }
    else {
      OdUInt8 data8[8] = { 0 };
      setGUIDdata(0, 0, 0, data8);
      ODA_FAIL_M_ONCE("Unexpected group while reading OdRevisionGuid");
    }
  }

  /** \details
    Writes OdDbRevisionGuid object to a DXF filer.
  */
  void dxfOut(OdDbDxfFiler* pFiler) const {
    pFiler->wrBool(290, m_bIsSet);
    pFiler->wrString(2, ascii());
  }

  /** \details
    Loads OdDbRevisionGuid object from a DWG filer.
  */
  void dwgIn(OdDbDwgFiler* pFiler) {
    m_bIsSet = pFiler->rdBool();
    OdDbRevisionGuid::dwgIn(pFiler);
  }

  /** \details
    Writes OdDbRevisionGuid object to a DWG filer.
  */
  void dwgOut(OdDbDwgFiler* pFiler) const {
    pFiler->wrBool(m_bIsSet);
    OdDbRevisionGuid::dwgOut(pFiler);
  }

  /** \details
    Sets new value.

    \param newGuid [in] new value to set.
    \param bSet [in] new value of "IsSet" flag.
  */
  void setGuid(const OdRevisionGuid& newGuid, bool bSet) {
    if (m_bIsSet != bSet || !(*this == newGuid)) {
      *this = newGuid;
      m_bIsSet = bSet;
    }
  }

  /** \details
    Generates new different GUID value for this object.
  */
  void generateDifferent() {
    OdRevisionGuid newGuid;
    createGuid(newGuid);
    setGuid(newGuid, m_bIsSet);
  }

  /** \details
    Enables or disables this object.
    \param bEnable [in] if this parameter is true then this method generates new different GUID value
      and sets "IsSet" flag. If this parameter is false then this method just resets "IsSet" flag. 
  */
  void enable(bool bEnable) {
    if (bEnable) {
      OdRevisionGuid newGuid;
      createGuid(newGuid);
      setGuid(newGuid, bEnable);
    }
    else {
      setGuid(*this, bEnable);
    }
  }
};

#include "TD_PackPop.h"
