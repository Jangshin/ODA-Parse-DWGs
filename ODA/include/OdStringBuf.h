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

#ifndef __ODSTRINGBUF_H_
#define __ODSTRINGBUF_H_

#include "DbRootExport.h"
#include "OdStreamBuf.h"

#include "TD_PackPush.h"

/** \details
  Text read/write helper. Provide Unicode charsets support for text files processing.

 	Corresponding C++ library: TD_DbRoot
  
  <group Other_Classes>
*/
class DBROOT_EXPORT OdStringBuf : public OdRxObject
{
public:
  /** \details
    Charset.
  */
  enum CharFormat
  {
    CharFormat_Undefined = 0, // Can't determine character format
    CharFormat_ANSI, // ANSI
    CharFormat_UTF8, // UTF8
    CharFormat_UTF16LE, // UTF16 LittleEndian
    CharFormat_UTF16BE, // UTF16 BigEndian
    CharFormat_UTF32LE, // UTF32 LittleEndian
    CharFormat_UTF32BE // UTF32 BigEndian
  };
protected:
  mutable OdStreamBufPtr m_pIo;
  CharFormat m_cf;
public:
  OdStringBuf();
  /** \details
    Initialize OdStringBuf by OdStreamBuf interface and, optionally, by charset.
    \param pIo [in]  OdStreamBuf interface.
    \param cf [in]  Charset.
  */
  void init(OdStreamBuf* pIo, CharFormat cf = CharFormat_Undefined);

  ODRX_DECLARE_MEMBERS(OdStringBuf);

  /** \details
    Reads next line of text from text file.
  */
  virtual OdString getString();

  /** \details
    Returns pointer onto current OdStreamBuf interface.
  */
  inline OdStreamBuf* getIOPtr() const
  {
    return ((OdStreamBuf*)(m_pIo.get()));
  }

  /** \details
    Returns current charset.
  */
  inline CharFormat getCharFormat()
  {
    return m_cf;
  }
protected:
  OdStringBuf::CharFormat DetermineCharFormat() const;
  OdChar ReadChar(OdChar &secChr) const;
  OdInt64 GetUnicodeHeaderSize() const;
  OdInt64 GetUnicodeBitSize() const;
  // Conversions
  OdChar FromANSI(OdUInt8 chr) const;
  OdChar FromUTF8(OdUInt8 chr) const;
  OdChar FromUTF16LE(OdUInt16 chr) const;
  OdChar FromUTF16BE(OdUInt16 chr) const;
  OdChar FromUTF32LE(OdUInt32 chr, OdChar &secChr) const;
  OdChar FromUTF32BE(OdUInt32 chr, OdChar &secChr) const;
  // Cross-platform swap bytes
  static void Swap2BytesNumber(OdUInt16& W);
  static void Swap4BytesNumber(OdUInt32& DW);
  static void Swap2BytesChar(OdChar& W);

public:
  // Static
  /** \details
    Returns text file header value for specified charset.
    \param type [in]  Charset.
  */
  static OdUInt32 GetUnicodeHeaderForType(OdStringBuf::CharFormat type);
  /** \details
    Returns text file header size for specified charset.
    \param type [in]  Charset.
  */
  static OdInt64 GetUnicodeHeaderSizeForType(OdStringBuf::CharFormat type);
  /** \details
    Returns character size in bytes for specified charset.
    \param type [in]  Charset.
  */
  static OdInt64 GetUnicodeBitSizeForType(OdStringBuf::CharFormat type);
  /** \details
    Sets charset for current configuration.
    \param type [out]  Charset.
  */
  static void DefaultingType(OdStringBuf::CharFormat &type);
  /** \details
    Sets charset for current UTF-16 configuration.
    \param type [out]  Charset.
  */
  static void DefaultUTF16Type(OdStringBuf::CharFormat &type);
  /** \details
    Sets charset for current UTF-32 configuration.
    \param type [out]  Charset.
  */
  static void DefaultUTF32Type(OdStringBuf::CharFormat &type);
  // Save to stream
  /** \details
    Writes text file header into specified OdStreamBuf.
    \param type [in]  Charset.
    \param io [in]  OdStreamBuf interface.
  */
  static void WriteUnicodeHeader(OdStringBuf::CharFormat type, OdStreamBuf &io);
  /** \details
    Writes ANSI string into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param text [in]  ANSI text string.
  */
  static void WriteString(OdStringBuf::CharFormat type, OdStreamBuf &io, const char *text);
  /** \details
    Writes Unicode string into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param text [in]  Unicode text string.
  */
  static void WriteString(OdStringBuf::CharFormat type, OdStreamBuf &io, const OdChar *text);
  // Additional
  /** \details
    Writes line feed into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param use_odc [in]  Write as Unicode text.
  */
  static void WriteNL(OdStringBuf::CharFormat type, OdStreamBuf &io, bool use_odc = true);
  /** \details
    Writes space character into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param use_odc [in]  Write as Unicode text.
  */
  static void WriteSpace(OdStringBuf::CharFormat type, OdStreamBuf &io, bool use_odc = true);
  /** \details
    Writes tabulation character into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param use_odc [in]  Write as Unicode text.
  */
  static void WriteTab(OdStringBuf::CharFormat type, OdStreamBuf &io, bool use_odc = true);
  // Types
  /** \details
    Writes OdInt8 value as text into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param var [in]  Numeric value.
  */
  static void WriteOdInt8(OdStringBuf::CharFormat type, OdStreamBuf &io, OdInt8 var);
  /** \details
    Writes OdUInt8 value as text into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param var [in]  Numeric value.
  */
  static void WriteOdUInt8(OdStringBuf::CharFormat type, OdStreamBuf &io, OdUInt8 var);
  /** \details
    Writes OdInt16 value as text into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param var [in]  Numeric value.
  */
  static void WriteOdInt16(OdStringBuf::CharFormat type, OdStreamBuf &io, OdInt16 var);
  /** \details
    Writes OdUInt16 value as text into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param var [in]  Numeric value.
  */
  static void WriteOdUInt16(OdStringBuf::CharFormat type, OdStreamBuf &io, OdUInt16 var);
  /** \details
    Writes OdInt32 value as text into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param var [in]  Numeric value.
  */
  static void WriteOdInt32(OdStringBuf::CharFormat type, OdStreamBuf &io, OdInt32 var);
  /** \details
    Writes OdUInt32 value as text into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param var [in]  Numeric value.
  */
  static void WriteOdUInt32(OdStringBuf::CharFormat type, OdStreamBuf &io, OdUInt32 var);
  /** \details
    Writes floating point value as text into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param var [in]  Numeric value.
  */
  static void WriteOdFloat(OdStringBuf::CharFormat type, OdStreamBuf &io, float var);
  /** \details
    Writes double floating point value as text into specified OdStreamBuf.
    \param type [in]  Writing charset.
    \param io [in]  OdStreamBuf interface.
    \param var [in]  Numeric value.
  */
  static void WriteOdDouble(OdStringBuf::CharFormat type, OdStreamBuf &io, double var);
};

typedef OdSmartPtr<OdStringBuf> OdStringBufPtr;

#include "TD_PackPop.h"

#endif //__ODSTRINGBUF_H_
