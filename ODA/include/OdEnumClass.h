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

#ifndef ODENUMCLASS_INCLUDED
#define ODENUMCLASS_INCLUDED

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)

#include <type_traits>
#include <cstdarg>

/** \details
  \returns value of enumeration type provided in parameter as underlying type of this enumeration.
  If TEnum is not an enumeration type, the function is removed from the candidate set.
  \param value [in] Value of an enumeration.
*/
template<typename TEnum,
  typename std::enable_if<std::is_enum<TEnum>::value, bool>::type = true>
typename std::underlying_type<TEnum>::type
OdEnumGetUnderlying(const TEnum value)
{
  return static_cast<typename std::underlying_type<TEnum>::type>(value);
}

/** \details
  This class is a wrapper around C++11 enum classes that allows more convenient
  and type-safe usage of enum classes as bitmasks.
*/
template<typename TEnum>
class OdEnumClass
{
public:
  using underlying_t = typename std::underlying_type<TEnum>::type;

  /** \details
    Constructs OdEnumClass from args.
    Args can only be of types that are convertible to integer or TEnum.
    \param args [in] Parameter pack of values to construct from.
  */
  template<typename... Args>
  OdEnumClass(const Args... args)
  {
    OR(args...);
  }

  /** \details
    Assigns OdEnumClass new value from other instance of OdEnumClass.
    \param value [in] Other instance of OdEnumClass.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator=(const OdEnumClass value)
  {
    set(value.asInt());
    return *this;
  }

  /** \details
    Assigns OdEnumClass new value from instance of enum class.
    \param value [in] Instance of enum class.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator=(const TEnum value)
  {
    set(value);
    return *this;
  }

  /** \details
    Assigns OdEnumClass new value from instance of underlying integer type.
    \param value [in] Value of underlying integer type.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator=(const underlying_t value)
  {
    set(value);
    return *this;
  }

  /** \details
    Compares values of OdEnumClass with other instance.
    \param value [in] Value to be compared with.
    \returns true if values are not the same, otherwise false.
  */
  bool operator!=(const OdEnumClass<TEnum> value) const
  {
    return asInt() != value.asInt();
  }

  /** \details
    Compares values of OdEnumClass with value of enum class.
    \param value [in] Value to be compared with.
    \returns true if values are not the same, otherwise false.
  */
  bool operator!=(const TEnum value) const
  {
    return asInt() != OdEnumGetUnderlying(value);
  }

  /** \details
    Compares values of OdEnumClass with value of integer underlying type.
    \param value [in] Value to be compared with.
    \returns true if values are not the same, otherwise false.
  */
  bool operator!=(const underlying_t value) const
  {
    return asInt() != value;
  }

  /** \details
    Compares values of OdEnumClass with other instance.
    \param value [in] Value to be compared with.
    \returns true if values are the same, otherwise false.
  */
  bool operator==(const OdEnumClass<TEnum> value) const
  {
    return asInt() == value.asInt();
  }

  /** \details
    Compares values of OdEnumClass with value of enum class.
    \param value [in] Value to be compared with.
    \returns true if values are the same, otherwise false.
  */
  bool operator==(const TEnum value) const
  {
    return asInt() == OdEnumGetUnderlying(value);
  }

  /** \details
    Compares values of OdEnumClass with value of integer underlying type.
    \param value [in] Value to be compared with.
    \returns true if values are the same, otherwise false.
  */
  bool operator==(const underlying_t value) const
  {
    return asInt() == value;
  }

  /** \details
    Sums up two values and returns new instance.
    \param value [in] Value to be summed up.
    \returns new instance of OdEnumClass with values summed up.
  */
  OdEnumClass<TEnum> operator+(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() + OdEnumGetUnderlying(value));
  }
  /** \details
    Sums up two values and returns new instance.
    \param value [in] Value to be summed up.
    \returns new instance of OdEnumClass with values summed up.
  */
  OdEnumClass<TEnum> operator+(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() + value);
  }

  /** \details
    Subtracts TEnum value and returns new instance.
    \param value [in] Value to be subracted.
    \returns new instance of OdEnumClass with difference in values.
  */
  OdEnumClass<TEnum> operator-(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() - OdEnumGetUnderlying(value));
  }

  /** \details
    Subtracts underlying type value and returns new instance.
    \param value [in] Value to be subracted.
    \returns new instance of OdEnumClass with difference in values.
  */
  OdEnumClass<TEnum> operator-(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() - value);
  }

  /** \details
    Multiplies two values and returns new instance.
    \param value [in] Value to be multiplied.
    \returns new instance of OdEnumClass with values multiplied.
  */
  OdEnumClass<TEnum> operator*(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() * OdEnumGetUnderlying(value));
  }

  /** \details
    Multiplies two values and returns new instance.
    \param value [in] Value to be multiplied.
    \returns new instance of OdEnumClass with values multiplied.
  */
  OdEnumClass<TEnum> operator*(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() * value);
  }

  /** \details
    Divides on TEnum value and returns new instance.
    \param value [in] Value to be divided on.
    \returns new instance of OdEnumClass with values divided.
  */
  OdEnumClass<TEnum> operator/(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() / OdEnumGetUnderlying(value));
  }

  /** \details
    Divides on TEnum value and returns new instance.
    \param value [in] Value to be divided on.
    \returns new instance of OdEnumClass with values divided.
  */
  OdEnumClass<TEnum> operator/(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() / value);
  }

  /** \details
    Performs bitwise AND operation and returns new instance.
    \param value [in] Second operand value in AND operation.
    \returns new instance of OdEnumClass with AND operation applied.
  */
  OdEnumClass<TEnum> operator&(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() & OdEnumGetUnderlying(value));
  }

  /** \details
    Performs bitwise AND operation and returns new instance.
    \param value [in] Second operand value in AND operation.
    \returns new instance of OdEnumClass with AND operation applied.
  */
  OdEnumClass<TEnum> operator&(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() & value);
  }

  /** \details
    Performs bitwise OR operation and returns new instance.
    \param value [in] Second operand value in OR operation.
    \returns new instance of OdEnumClass with OR operation applied.
  */
  OdEnumClass<TEnum> operator|(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() | OdEnumGetUnderlying(value));
  }

  /** \details
    Performs bitwise OR operation and returns new instance.
    \param value [in] Second operand value in OR operation.
    \returns new instance of OdEnumClass with OR operation applied.
  */
  OdEnumClass<TEnum> operator|(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() | value);
  }

  /** \details
    Performs bitwise XOR operation and returns new instance.
    \param value [in] Second operand value in XOR operation.
    \returns new instance of OdEnumClass with XOR operation applied.
  */
  OdEnumClass<TEnum> operator^(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() ^ OdEnumGetUnderlying(value));
  }

  /** \details
    Performs bitwise XOR operation and returns new instance.
    \param value [in] Second operand value in XOR operation.
    \returns new instance of OdEnumClass with XOR operation applied.
  */
  OdEnumClass<TEnum> operator^(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() ^ value);
  }

  /** \details
    Performs left bit shift and returns new instance.
    \param value [in] Value to left shift current value on.
    \returns new instance of OdEnumClass with left shift operation applied.
  */
  OdEnumClass<TEnum> operator<<(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() << OdEnumGetUnderlying(value));
  }

  /** \details
    Performs left bit shift and returns new instance.
    \param value [in] Value to left shift current value on.
    \returns new instance of OdEnumClass with left shift operation applied.
  */
  OdEnumClass<TEnum> operator<<(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() << value);
  }

  /** \details
    Performs right bit shift and returns new instance.
    \param value [in] Value to right shift current value on.
    \returns new instance of OdEnumClass with right shift operation applied.
  */
  OdEnumClass<TEnum> operator>>(const TEnum value) const
  {
    return OdEnumClass<TEnum>(asInt() >> OdEnumGetUnderlying(value));
  }

  /** \details
    Performs right bit shift and returns new instance.
    \param value [in] Value to right shift current value on.
    \returns new instance of OdEnumClass with right shift operation applied.
  */
  OdEnumClass<TEnum> operator>>(const underlying_t value) const
  {
    return OdEnumClass<TEnum>(asInt() >> value);
  }

  /** \details
    Sums up two values and returns new instance.
    \param value [in] Value to be summed up.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator+=(const TEnum value)
  {
    m_value += OdEnumGetUnderlying(value);
    return *this;
  }
  /** \details
    Sums up two values and returns new instance.
    \param value [in] Value to be summed up.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator+=(const underlying_t value)
  {
    m_value += value;
    return *this;
  }

  /** \details
    Subtracts TEnum value and returns new instance.
    \param value [in] Value to be subracted.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator-=(const TEnum value)
  {
    m_value -= OdEnumGetUnderlying(value);
    return *this;
  }

  /** \details
    Subtracts underlying type value and returns new instance.
    \param value [in] Value to be subracted.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator-=(const underlying_t value)
  {
    m_value -= value;
    return *this;
  }

  /** \details
    Multiplies two values and returns new instance.
    \param value [in] Value to be multiplied.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator*=(const TEnum value)
  {
    m_value *= OdEnumGetUnderlying(value);
    return *this;
  }

  /** \details
    Multiplies two values and returns new instance.
    \param value [in] Value to be multiplied.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator*=(const underlying_t value)
  {
    m_value *= value;
    return *this;
  }

  /** \details
    Divides on TEnum value and returns new instance.
    \param value [in] Value to be divided on.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator/=(const TEnum value)
  {
    m_value /= OdEnumGetUnderlying(value);
    return *this;
  }

  /** \details
    Divides on TEnum value and returns new instance.
    \param value [in] Value to be divided on.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator/=(const underlying_t value)
  {
    m_value /= value;
    return *this;
  }

  /** \details
    Performs bitwise AND operation and returns new instance.
    \param value [in] Second operand value in AND operation.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator&=(const TEnum value)
  {
    m_value &= OdEnumGetUnderlying(value);
    return *this;
  }

  /** \details
    Performs bitwise AND operation and returns new instance.
    \param value [in] Second operand value in AND operation.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator&=(const underlying_t value)
  {
    m_value &= value;
    return *this;
  }

  /** \details
    Performs bitwise OR operation and returns new instance.
    \param value [in] Second operand value in OR operation.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator|=(const TEnum value)
  {
    m_value |= OdEnumGetUnderlying(value);
    return *this;
  }

  /** \details
    Performs bitwise OR operation and returns new instance.
    \param value [in] Second operand value in OR operation.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator|=(const underlying_t value)
  {
    m_value |= value;
    return *this;
  }

  /** \details
    Performs bitwise XOR operation and returns new instance.
    \param value [in] Second operand value in XOR operation.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator^=(const TEnum value)
  {
    m_value ^= OdEnumGetUnderlying(value);
    return *this;
  }

  /** \details
    Performs bitwise XOR operation and returns new instance.
    \param value [in] Second operand value in XOR operation.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator^=(const underlying_t value)
  {
    m_value ^= value;
    return *this;
  }

  /** \details
    Performs left bit shift and returns new instance.
    \param value [in] Value to left shift current value on.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator<<=(const TEnum value)
  {
    m_value <<= OdEnumGetUnderlying(value);
    return *this;
  }

  /** \details
    Performs left bit shift and returns new instance.
    \param value [in] Value to left shift current value on.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator<<=(const underlying_t value)
  {
    m_value <<= value;
    return *this;
  }

  /** \details
    Performs right bit shift and returns new instance.
    \param value [in] Value to right shift current value on.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator>>=(const TEnum value)
  {
    m_value >>= OdEnumGetUnderlying(value);
    return *this;
  }

  /** \details
    Performs right bit shift and returns new instance.
    \param value [in] Value to right shift current value on.
    \returns current instance of OdEnumClass with new value.
  */
  OdEnumClass<TEnum>& operator>>=(const underlying_t value)
  {
    m_value >>= value;
    return *this;
  }

  /** \details
    Sets new value for current object from instance of enum class.
    \param value [in] Value to be set.
  */
  void set(const TEnum value)
  {
    m_value = OdEnumGetUnderlying(value);
  }

  /** \details
    Sets new value for current object from instance of underlying integer type.
    \param value [in] Value to be set.
  */
  void set(const underlying_t value)
  {
    m_value = value;
  }

  /** \details
    Sets the bit specified in parameter to corresponding value.
    \param bit [in] Bit to be set.
    \param value [in] Value to be set.
  */
  void setBit(const int bit, const bool value = true)
  {
    if (value)
      m_value |= (1 << bit);
    else
      unsetBit(bit);
  }

  /** \details
    Sets the bit specified in parameter to 0.
    \param bit [in] Bit to be unset.
  */
  void unsetBit(const int bit)
  {
    m_value &= ~(1 << bit);
  }

  /** \details
    Sets current value to 0.
  */
  void clear()
  {
    m_value = 0;
  }

  /** \details
    Performs bitwise OR operation with value.
    \param value [in] Second operand value in OR.
  */
  void OR(const OdEnumClass<TEnum> value)
  {
    m_value |= value.asInt();
  }

  /** \details
    Performs bitwise OR operation with value.
    \param value [in] Second operand value in OR.
  */
  void OR(const TEnum value)
  {
    m_value |= OdEnumGetUnderlying(value);
  }

  /** \details
    Performs bitwise OR operation with value.
    \param value [in] Second operand value in OR.
  */
  void OR(const underlying_t value)
  {
    m_value |= value;
  }

  /** \details
    Performs bitwise OR operation on all passed arguments.
    T and Args can only be of types that are convertible to integer or TEnum.
    \param value [in] Parameter to perform OR with.
    \param args [in] Parameter pack of values to perform OR with nextly.
  */
  template<typename T, typename... Args>
  void OR(const T value, const Args... args)
  {
    static_assert(
      std::is_convertible<T, TEnum>::value || std::is_convertible<T, underlying_t>::value,
      "This type is not allowed");
    OR(value);
    OR(args...);
  }

  /** \details
    Performs bitwise AND operation with value.
    \param value [in] Second operand value in AND.
  */
  void AND(const OdEnumClass<TEnum> value)
  {
    m_value &= value.asInt();
  }

  /** \details
    Performs bitwise AND operation with value.
    \param value [in] Second operand value in AND.
  */
  void AND(const TEnum value)
  {
    m_value &= OdEnumGetUnderlying(value);
  }

  /** \details
    Performs bitwise AND operation with value.
    \param value [in] Second operand value in AND.
  */
  void AND(const underlying_t value)
  {
    m_value &= value;
  }

  /** \details
    Performs bitwise AND operation on all passed arguments.
    T and Args can only be of types that are convertible to integer or TEnum.
    \param value [in] Parameter to perform AND with.
    \param args [in] Parameter pack of values to perform AND with nextly.
  */
  template<typename T, typename... Args>
  void AND(const T value, const Args... args)
  {
    static_assert(
      std::is_convertible<T, TEnum>::value || std::is_convertible<T, underlying_t>::value,
      "This type is not allowed");
    AND(value);
    AND(args...);
  }

  /** \details
    Performs bitwise XOR operation with value.
    \param value [in] Second operand value in XOR.
  */
  void XOR(const OdEnumClass<TEnum> value)
  {
    m_value ^= value.asInt();
  }

  /** \details
    Performs bitwise XOR operation with value.
    \param value [in] Second operand value in XOR.
  */
  void XOR(const TEnum value)
  {
    m_value ^= OdEnumGetUnderlying(value);
  }

  /** \details
    Performs bitwise XOR operation with value.
    \param value [in] Second operand value in XOR.
  */
  void XOR(const underlying_t value)
  {
    m_value ^= value;
  }

  /** \details
    Performs bitwise XOR operation on all passed arguments.
    T and Args can only be of types that are convertible to integer or TEnum.
    \param value [in] Parameter to perform XOR with.
    \param args [in] Parameter pack of values to perform XOR with nextly.
  */
  template<typename T, typename... Args>
  void XOR(const T value, const Args... args)
  {
    static_assert(
      std::is_convertible<T, TEnum>::value || std::is_convertible<T, underlying_t>::value,
      "This type is not allowed");
    XOR(value);
    XOR(args...);
  }

  /** \details
    \returns true only if all the bits in current value are set to one, otherwise false.
  */
  bool all() const
  {
    for (std::size_t i = 0; i < sizeof (underlying_t) * CHAR_BIT; ++i)
    {
      if ((m_value & (1 << i)) == 0)
        return false;
    }
    return true;
  }

  /** \details
    \returns true only if any of the bits in current value is set to one, otherwise false.
  */
  bool any() const
  {
    return asBool();
  }

  /** \details
    \returns true only if no bit in current value is set to one, otherwise false.
  */
  bool none() const
  {
    return !any();
  }

  /** \details
    \returns current value casted to enumeration type.
  */
  TEnum asEnum() const
  {
    return static_cast<TEnum>(m_value);
  }

  /** \details
    \returns current value as underlying integer type.
  */
  underlying_t asInt() const
  {
    return m_value;
  }

  /** \details
    \returns current value as boolean type.
  */
  bool asBool() const
  {
    return (m_value ? true : false);
  }

  /** \details
    \returns current value.
  */
  operator TEnum() const { return asEnum(); }

private:
  /** \details
    Holds current value.
  */
  underlying_t m_value{};
};

#endif //#if __cplusplus >= 201103L

#endif //#ifndef ODENUMCLASS_INCLUDED
