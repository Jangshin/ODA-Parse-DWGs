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




#ifndef ODDBHANDLE
#define ODDBHANDLE /*!DOM*/

#include "TD_PackPush.h"

#include "DbRootExport.h"
#include "OdArrayPreDef.h"
#include "OdaDefs.h"
#include "OdString.h"

/** \details
  Returns the decimal value of a hexadecimal digit.
  
  \param hexDigit [in]  Hex digit.
  
  Examples:  
  getHexValue('A') returns 10, etc.
*/
DBROOT_EXPORT int getHexValue(
  int hexDigit);

/** \details
  Returns the 64-bit integer value corresponding to the passed string.
  \param pStr [in] String representation of an integer.
*/
//TOOLKIT_EXPORT OdInt64 atoi64(const OdChar* pStr);
//TOOLKIT_EXPORT void    i64toA(const OdInt64 &val, OdChar* pStr);


template <class T>
struct OdDbHandleConvertible;


/** \details
    This class encapsulates the 64-bit integer handles associated with OdDbObject instances.
    
    Corresponding C++ library: TD_Db
    
    \remarks
    Handles are persistent and unique within a database. Handles are not, 
	however, unique between databases.
    
    <group OdDb_Classes>
*/
class DBROOT_EXPORT OdDbHandle
{
public:
  /** \details
    Default constructor for instances of the OdDbHandle class.

    \remarks
    Initializes the handle with the null value.
  */
  OdDbHandle() : m_val(0) {}

  /** \details
    Copy constructor for instances of the OdDbHandle class. 

    \param value [in] Reference to an OdDbHandle value.
  */
  OdDbHandle(const OdDbHandle& value) = default;

#ifndef SWIG
  template <class T, std::enable_if<OdDbHandleConvertible<typename std::remove_reference<typename std::remove_cv<T>::type>::type>::value>* = nullptr>
  
  /** \details
    Constructoor for instances of the OdDbHandle class. 

    \param value [in] Value to convert.
    \remarks
    The value is converted to the OdUInt64 type.
  */
  OdDbHandle(T value) : m_val(static_cast<OdUInt64>(value)) {}
#endif

  /** \details
    Constructor for a handle using the specified 64-bit handle value.

    \param value [in] OdUInt64 value.
  */
  OdDbHandle(OdUInt64 value) : m_val(value) {}
  
  /** \details
    Constructor for a handle from a pointer to an OdChar value.

    \param value [in] Pointer to an OdChar value.
  */
  OdDbHandle(const OdChar* value) { *this = value; }

  /** \details
    Constructor for a handle from a pointer to a char value.

    \param value [in] Pointer to an char value.
  */
  OdDbHandle(const char* value) { *this = value; }

  /** \details
    Constructor for a handle from a specified OdString value.

    \param value [in] An OdString value.
  */
  OdDbHandle(const OdString& value) { *this = (const OdChar*)value; }

  /** \details
    Constructor for a handle from a specified OdAnsiString value.

    \param value [in] An OdAnsiString value.
  */
  OdDbHandle(const OdAnsiString& value) { *this = (const char*)value; }

  /** \details
    Constructor for a handle from a specified int value.

    \param value [in] An int value.
  */
  OdDbHandle(int value) : m_val(value) {}
#if OD_SIZEOF_LONG == 4

  /** \details
    Constructor for a handle using the specified OdInt32 handle value.

    \param value [in] OdInt32 value.
  */
  OdDbHandle(OdInt32 value) : m_val(value) {}
#endif
  /** \details
    Assignment operator. Assigns a new OdUInt64 value to this OdDbHandle object, replacing its current contents.

    \param value [in] New OdUInt64 value.
    \returns Reference to this object.
  */
  OdDbHandle& operator=(OdUInt64 value) 
  {
    m_val = value;
    return *this;
  }
  
  /** \details
    Assignment operator. Assigns a new OdChar value to this OdDbHandle object, replacing its current contents.

    \param value [in] Pointer to an OdChar value.
    \returns Reference to this object.
  */
  OdDbHandle& operator=(const OdChar* value);

  /** \details
    Assignment operator. Assigns a new char value to this OdDbHandle object, replacing its current contents.

    \param value [in] Pointer to a char value.
    \returns Reference to this object.
  */
  OdDbHandle& operator=(const char* value);

  /** \details
    Copy assignment operator. Assigns a new value to this OdDbHandle object, replacing its current contents. 

    \param value [in] New OdDbHandle value.
    \returns Reference to this object.
  */
  OdDbHandle& operator=(const OdDbHandle& value) = default;

  /** \details
    Assignment operator. Assigns a new int value to this OdDbHandle object, replacing its current contents.

    \param value [in] New int value.
    \returns Reference to this object.
  */
  OdDbHandle& operator=(int value)
  {
    m_val = value;
    return *this;
  }

  /** \details
    Returns a converted instance of the OdDbHandle class as an OdUInt64 value.

    \returns The instance of the OdDbHandle class as an OdUInt64 value.
  */
  operator OdUInt64() const { return m_val; }
  
  /** \details
    Returns the hexidecmal representation of this Handle object as a null terminated string.
    
    \param pBuf [in]  Pointer to the buffer to receive the string.
    \remarks
    The buffer must be at least 17 bytes long.
  */
    void getIntoAsciiBuffer(
    OdChar* pBuf) const;
    
  /** \details
    Returns the hexidecmal representation of this Handle object as an OdString.
  */
  OdString ascii() const;
  /** \details
    Returns true and only if this Handle object is null.
  */
  bool isNull() const { return m_val == 0; }
  
  /** \details
    Compares the value of an instance of the OdDbHandle class and a specified value.

    \param value [in] OdUInt64 value to compare with.
    \returns The true value if the value of the OdDbHandle class instance and the specified value are equal, or false otherwise.
  */
  bool operator == (
    OdUInt64 value) const { return m_val == value; }
  
  /** \details
    Compares the value of an instance of the OdDbHandle class and a specified value.

    \param value [in] OdUInt64 value to compare with.
    \returns The true value if the value of the OdDbHandle class instance and the specified value are not equal, or false otherwise.
  */
  bool operator != (
    OdUInt64 value) const { return m_val != value; }
  
  /** \details
    Compares the value of an instance of the OdDbHandle class and a specified value.

    \param value [in] OdUInt64 value to compare with.
    \returns The true value if the value of the OdDbHandle class instance is bigger than the specified value, or false otherwise.
  */
  bool operator > (
    OdUInt64 value) const { return m_val > value; }
  
  /** \details
    Compares the value of an instance of the OdDbHandle class and a specified value.

    \param value [in] OdUInt64 value to compare with.
    \returns The true value if the value of the OdDbHandle class instance is smaller than the specified value, or false otherwise.
  */
  bool operator < (
    OdUInt64 value) const { return m_val < value; }
  
  /** \details
    Compares the value of an instance of the OdDbHandle class and a specified value.

    \param value [in] OdUInt64 value to compare with.
    \returns The true value if the value of the OdDbHandle class instance is less than or equal to the specified value, or false otherwise.
  */
  bool operator <= (
    OdUInt64 value) const { return m_val < value || m_val == value; }
  
  /** \details
    Compares the value of an instance of the OdDbHandle class and a specified value.

    \param value [in] OdUInt64 value to compare with.
    \returns The true value if the value of the OdDbHandle class instance is greater than or equal to the specified value, or false otherwise.
  */
  bool operator >= (
    OdUInt64 value) const { return m_val > value || m_val == value; }
  
  /** \details
    Adds a specified value to the value of this OdDbHandle object.

    \returns Returns the updated value of this OdDbHandle class.
    \remarks The value of this OdDbHandle class is changed.
  */
  OdDbHandle& operator+=(
    const OdInt64& value)
  {
    m_val += value;
    ODA_ASSERT_ONCE(!isNull()); // check handle stuff overflow
    return *this;
  }

  /** \details
    Returns the result of adding a specified value to the value of the OdDbHandle class instance.

    \returns Returns the result of adding a value.
    \remarks The value of an instance of the OdDbHandle class is not changed.
  */
  OdDbHandle operator+(
    const OdInt64& value)
  {
    OdDbHandle res;
    res.m_val = m_val + value;
    return res;
  }

  /** \details
    Returns this handle object as an array of OdUInt8[8] values.
    
    \param bytes [in] Array of low-ordered bytes to receive the handle.
    \remarks
    The low order byte is returned in bytes[0].
    The buffer must be at least 17 bytes long.
  */
    void bytes(
    OdUInt8 * bytes) const
  {
    OdUInt64 val = m_val;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes++ = (OdUInt8)(val & 0xFF);
    val >>= 8;
    *bytes = (OdUInt8)(val & 0xFF);
  }

private:
    OdUInt64  m_val;
};


/** \details
  This template class is a specialization of the OdArray class for OdDbHandle objects.
*/
typedef OdArray<OdDbHandle> OdHandleArray;

#include "TD_PackPop.h"

#endif

