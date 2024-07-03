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




#ifndef ODARRAY_H_INCLUDED
#define ODARRAY_H_INCLUDED

#include <new>
#include <utility>

#include "TD_PackPush.h"

#include "OdArrayPreDef.h"
#include "OdHeap.h"
#include "OdMutex.h"
#include "OdError.h"
#include "RxSystemServices.h"
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <initializer_list>

template<class T>
struct OdIsTriviallyCopyablePair
{
  static const bool value = false;
};

template <class First, class Second>
struct OdIsTriviallyCopyablePair <std::pair<First, Second> >
{
  static const bool value = std::is_trivially_copyable<First>::value && std::is_trivially_copyable<Second>::value;
};

/** \details
    This template class implements memory allocation functions within the ODA Platform.
    
    \sa
    TD_Db
    
    <group Other_Classes>
*/
template <class T> class OdMemoryAllocator
{
public:
  typedef unsigned int size_type;

  /** \details
    This function performs a copy assignment from a source range to a destination range (ranges must not overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the behavior of the function is undefined.
    Use copyAssignRange() to handle overlapping regions.
  */
  static inline void copyAssignRangeDisjoint(
    T* pDestination, 
    const T* pSource, 
    size_type numElements)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memcpy(pDestination, pSource, numElements * sizeof(T));
  }

  /** \details
    This function performs a copy assignment from a source range to a destination range (ranges may overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the method copies the overlapping region before it is overwritten.
    Use copyAssignRangeDisjoint() to handle non-overlapping regions. 
  */
  static inline void copyAssignRange(
    T* pDestination, 
    const T* pSource, 
    size_type numElements)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memmove(pDestination, pSource, numElements * sizeof(T));
  }

  /** \details
    This function performs a move assignment from a source range to a destination range (ranges may overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the method moves the overlapping region before it is overwritten.
  */
  static inline void moveAssignRange(
    T* pDestination, 
    T* pSource, 
    size_type numElements)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memmove(pDestination, pSource, numElements * sizeof(T));
  }

  /** \details
    This function performs a default constructor on one memory location.
    
    \param pElement [out]  Receives the element. 

    \remarks
    In some memory allocators, the method performs value initialization instead of default initialization,
    i.e., primitive types are zero-initialized instead of being left with undefined values.
  */
  static inline void defaultConstruct(
    T* /*pElement*/)
  {
    // DOES NOTHING
  }

  /** \details
    This function performs a copy constructor on one memory location.
    
    \param pElement [out]  Receives the element. 
    \param value [in]  Value for the element.
  */
  static inline void copyConstruct(
    T* pElement, 
    const T& value)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memcpy(pElement, std::addressof(value), sizeof(value));
  }

  /** \details
    This function performs a move constructor on one memory location.
    
    \param pElement [out]  Receives the element. 
    \param value [in]  Value for the element.
  */
  static inline void moveConstruct(
    T* pElement, 
    T&& value)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memmove(pElement, std::addressof(value), sizeof(value));
  }

  /** \details
    This function performs a constructor on one memory location for the given arguments.

    \param pDestination [in]  Pointer to the destination.
    \param args [in]  Constructor arguments.
  */
  template <class... Args>
  static inline void construct(
    T* pDestination,
    Args&&... args)
  {
    ::new (pDestination) T(std::forward<Args>(args)...);
  }

  /** \details
    This function performs a copy constructor on a destination range, copying the same source element.
    
    \param pDestination [in]  Pointer to the destination.
    \param numElements [in]  Number of elements.
    \param value [in]  Value for the elements.
  */
  static inline void copyConstructFill(
    T* pDestination, 
    size_type numElements, 
    const T& value)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    while(numElements--)
    {
      memcpy(pDestination + numElements, std::addressof(value), sizeof(value));
    }
  }

  /** \details
    This function performs a copy constructor from a source range to a destination range.

    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
  */
  static inline void copyConstructRange(
    T* pDestination, 
    const T* pSource, 
    size_type numElements)
  {
    copyAssignRangeDisjoint(pDestination, pSource, numElements);
  }

  /** \details
    This function performs a move constructor from a source range to a destination range.
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
  */
  static inline void moveConstructRange(
    T* pDestination, 
    T* pSource, 
    size_type numElements)
  {
    copyAssignRangeDisjoint(pDestination, pSource, numElements);
  }

  /** \details
    This function performs a default constructor on a destination range.
    
    \param pDestination [in]  Pointer to the destination.
    \param numElements [in]  Number of elements.
  
    \remarks
    In some memory allocators, the method performs a value initialization instead of default initialization,
    i.e., primitive types are zero-initialized instead of being left with undefined values.
  */
  static inline void defaultConstructFill(
    T* /*pDestination*/, 
    size_type /*numElements*/)
  {
    // DOES NOTHING
  }

  /** \details
    Calls a destructor for an element at one location.

    \param pObject [in]  Pointer to the object. 
  */
  static inline void destroy(
    T* pObject)
  {
    // DOES NOTHING
  }

  /** \details
    Calls a destructor for elements at a destination range.

    \param objects [in]  Array of objects.
    \param numObjects [in]  Number of objects.
  */
  static inline void destroyRange(
    T* /*objects*/, 
    size_type /*numObjects*/)
  {
    // DOES NOTHING
  }

  /** \details
     Indicates whether odrxRealloc can be used to resize an array.

     \returns The true value if odrxRealloc can be used to resize an array, or false otherwise.
  */
  static inline bool useRealloc()
  {
    return true;
  }
};


/** \details
This template class implements memory allocation functions within the ODA Platform.

\sa
TD_Db

<group Other_Classes>
*/
template <class T> class OdClrMemAllocator : public OdMemoryAllocator<T>
{
public:
  typedef unsigned int size_type;

  /** \details
    This function performs a copy constructor on a destination range, copying the same source element.
    
    \param pDestination [in]  Pointer to the destination.
    \param numElements [in]  Number of elements.
    \param value [in]  Value for the elements.
  */
  static inline void copyConstructFill(
    T* pDestination,
    size_type numElements,
    const T& value)
  {
    OdMemoryAllocator<T>::copyConstructFill(pDestination, numElements, value);
  }

  /** \details
    This function performs a copy constructor from a source range to a destination range.

    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
  */
  static inline void copyConstructRange(
    T* pDestination,
    const T* pSource,
    size_type numElements)
  {
    OdMemoryAllocator<T>::copyConstructRange(pDestination, pSource, numElements);
  }

  /** \details
    This function performs a default constructor on one memory location.

    \param pElement [out]  Receives the element.

    \remarks
    In some memory allocators, the method performs value initialization instead of default initialization,
    i.e., primitive types are zero-initialized instead of being left with undefined values.
  */
  static inline void defaultConstruct(
    T* pElement)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memset(pElement, 0, sizeof(T));
  }

  /** \details
    This function performs default constructor on destination range.
    
    \param pDestination [in]  Pointer to the destination.
    \param numElements [in]  Number of elements.
  
    \remarks
    In some memory allocators, the method performs a value initialization instead of default initialization,
    i.e., primitive types are zero-initialized instead of being left with undefined values.
  */
  static inline void defaultConstructFill(
    T* pDestination,
    size_type numElements)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memset(pDestination, 0, numElements * sizeof(T));
  }
};


/** \details
    This template class implements object allocation functions within the ODA Platform.
    
    \remarks
    This class is for objects that must be copied with the assignment operator.
    For objects that can be copied with memcpy(), see OdPlainObjectsAllocator.
    
    \sa
    TD_Db

    <group Other_Classes>
*/
template <class T> class OdObjectsAllocator
{
public:
  typedef unsigned int size_type;
  
  /** \details
    This function performs a copy assignment from a source range to a destination range (ranges must not overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the behavior of the function is undefined.
    Use copyAssignRange() to handle overlapping regions.
  */
  static inline void copyAssignRangeDisjoint(
    T* pDestination, 
    const T* pSource, 
    size_type numElements)
  {
    while(numElements--)
    {
      *pDestination = *pSource;
      pDestination++;
      pSource++;
    }
  }

  /** \details
    This function performs a copy assignment from a source range to a destination range (ranges may overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the method copies the overlapping region before it is overwritten.
    Use copyAssignRangeDisjoint() to handle provably non-overlapping regions. 
  */
  static inline void copyAssignRange(
    T* pDestination, 
    const T* pSource, 
    size_type numElements)
  {
    if (pDestination <= pSource || pDestination >= pSource + numElements)
    {
      copyAssignRangeDisjoint(pDestination, pSource, numElements);
    }
    else
    {
      while(numElements--)
      {
        pDestination[numElements] = pSource[numElements];
      }
    }
  }

  /** \details
    This function performs a move assignment from a source range to a destination range (ranges may overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the method moves the overlapping region before it is overwritten.
  */
  static inline void moveAssignRange(
    T* pDestination, 
    T* pSource, 
    size_type numElements)
  {
    if (pDestination <= pSource || pDestination >= pSource + numElements)
    {
      while(numElements--)
      {
        *pDestination = std::move(*pSource);
        pDestination++;
        pSource++;
      }
    }
    else
    {
      while(numElements--)
      {
        pDestination[numElements] = std::move(pSource[numElements]);
      }
    }
  }

  /** \details
    This function performs a default constructor on one memory location.
    
    \param pElement [out]  Receives the element. 

    \remarks
    In some memory allocators, the method performs a value initialization instead of default initialization,
    i.e., primitive types are zero-initialized instead of being left with undefined values.
  */
  static inline void defaultConstruct(
    T* pElement)
  {
    ::new (pElement) T;
  }

  /** \details
    This function performs a copy constructor on one memory location.
    
    \param pElement [out]  Receives the element. 
    \param value [in]  Value for the element.
  */
  static inline void copyConstruct(
     T* pElement, 
     const T& value)
  {
    ::new (pElement) T(value);
  }

  /** \details
    This function performs a move constructor on one memory location.
    
    \param pElement [out]  Receives the element. 
    \param value [in]  Value for the element.
  */
  static inline void moveConstruct(
     T* pElement, 
     T&& value)
  {
    ::new (pElement) T(std::move(value));
  }

  /** \details
    This function performs a constructor on one memory location for the given arguments.

    \param pDestination [in]  Pointer to the destination.
    \param args [in]  Constructor arguments.
  */
  template <class... Args>
  static inline void construct(
    T* pDestination,
    Args&&... args)
  {
    ::new (pDestination) T(std::forward<Args>(args)...);
  }

  /** \details
    This function performs a copy constructor on a destination range, copying the same source element.
    
    \param pDestination [in]  Pointer to the destination.
    \param numElements [in]  Number of elements.
    \param value [in]  Value for the elements.
  */
  static inline void copyConstructFill(
    T* pDestination, 
    size_type numElements, 
    const T& value)
  {
    while(numElements--)
    {
      copyConstruct(pDestination+numElements, value);
    }
  }

  /** \details
    This function performs a default constructor on a destination range.
    
    \param pDestination [in]  Pointer to the destination.
    \param numElements [in]  Number of elements.
  
    \remarks
    In some memory allocators, the method performs a value initialization instead of default initialization,
    i.e., primitive types are zero-initialized instead of being left with undefined values.
  */
  static inline void defaultConstructFill(
    T* pDestination, 
    size_type numElements)
  {
    while(numElements--)
    {
      defaultConstruct(pDestination+numElements);
    }
  }

  /** \details
    This function performs a copy constructor from a source range to a destination range.

    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
  */
  static inline void copyConstructRange(
    T* pDestination, 
    const T* pSource, 
    size_type numElements)
  {
    while(numElements--)
    {
      copyConstruct(pDestination, *pSource);
      pDestination++;
      pSource++;
    }
  }

  /** \details
    This function performs a move constructor from a source range to a destination range.
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
  */
  static inline void moveConstructRange(
    T* pDestination, 
    T* pSource, 
    size_type numElements)
  {
    while(numElements--)
    {
      moveConstruct(pDestination, std::move(*pSource));
      pDestination++;
      pSource++;
    }
  }

  /** \details
    Calls a destructor for an element at one location.

    \param pObject [in]  Pointer to the object. 
  */
  static inline void destroy(
    T* pObject)
  {
    pObject->~T();
    pObject = 0;
  }

  /** \details
    Calls a destructor for elements at a destination range.

    \param objects [in]  Array of objects.
    \param numObjects [in]  Number of objects.
  */
  static inline void destroyRange(
    T* objects, 
    size_type numObjects)
  {
    while(numObjects--)
    {
      destroy(objects + numObjects);
    }
  }

  /** \details
     Indicates whether odrxRealloc can be used to resize an array.

     \returns The true value if odrxRealloc can be used to resize an array, or false otherwise.
     
     \remarks
     This function always returns false.
  */
  static inline bool useRealloc()
  {
    return false;
  }
};


/** \details
    This template class implements object allocation functions for objects within the ODA Platform.
    
    \remarks
    This class is for objects that can be copied with memcpy() (plain objects). For objects that must be copied with an assignment operator,
    see OdObjectsAllocator.
    
    \sa
    TD_Db

    <group Other_Classes>
*/
template <class T> class OdPlainObjectsAllocator : public OdObjectsAllocator<T>
{
public:
  typedef unsigned int size_type;
  
  /** \details
    This function performs a copy assignment from a source range to a destination range (ranges must not overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the behavior of the function is undefined.
    Use copyAssignRange() to handle overlapping regions.
  */
  static inline void copyAssignRangeDisjoint(
    T* pDestination, 
    const T* pSource, 
    size_type numElements)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memcpy(pDestination, pSource, numElements * sizeof(T));
  }
  
  /** \details
    This function performs a copy assignment from a source range to a destination range (ranges may overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the method copies the overlapping region before it is overwritten.
    Use copyAssignRangeDisjoint() to handle non-overlapping regions. 
  */
  static inline void copyAssignRange(
    T* pDestination, 
    const T* pSource, 
    size_type numElements)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memmove(pDestination, pSource, numElements * sizeof(T));
  }
  
  /** \details
    This function performs a move assignment from a source range to a destination range (ranges may overlap).
    
    \param pDestination [in]  Pointer to the destination.
    \param pSource [in]  Pointer to the source.
    \param numElements [in]  Number of elements.
    
    \remarks
    If the source and destination regions overlap, the method moves the overlapping region before it is overwritten.
  */
  static inline void moveAssignRange(
    T* pDestination, 
    T* pSource, 
    size_type numElements)
  {
    ODA_ASSERT_ONCE(std::is_trivially_copyable<T>::value || OdIsTriviallyCopyablePair<T>::value);
    memmove(pDestination, pSource, numElements * sizeof(T));
  }

  /** \details
     Indicates whether odrxRealloc can be used to resize an array.
     
     \returns The true value if odrxRealloc can be used to resize an array.
     
     \remarks
     This function always returns true.
  */
  static inline bool useRealloc()
  {
    return true;
  }
};

/** \details

    <group !!RECORDS_tkernel_apiref>
*/
struct FIRSTDLL_EXPORT OdArrayBuffer
{
  typedef unsigned int size_type;

  mutable OdRefCounter m_nRefCounter;
  int               m_nGrowBy;
  size_type         m_nAllocated;
  size_type         m_nLength;

  FIRSTDLL_EXPORT_STATIC static OdArrayBuffer g_empty_array_buffer;
};



/** \details
    This template class implements dynamic array objects within the ODA Platform.

    \remarks    
    Objects of the OdArray and OdVector classes are similar: elements are sequenced linearly, elements can be directly accessed, adding and deleting elements from the end of the sequence is fast, and the objects can resize automatically when an element is inserted or deleted.

    The OdArray class uses copy-on-write (implicit sharing) to duplicate or copy data. 

    This prevents accidental corruption of unrelated data when changing the contents of an OdArray object.
    OdArray objects share data when possible, which reduces memory consumption and unnecessary data copying.

    Use the OdArray class to avoid unnecessary array copies in cases where, according to the rules of C++, OdVector is copied, although this is not necessary.
    However, OdArray does not support C++11 move semantics, which OdVector supports.
    The OdArray class works similarly to QList.

    Methods are provided to access array elements via both array indices and array pointers (iterators).

    Definitions:
    
    1. Logical length or size -- The number of entries in the array. Initially zero.
    2. Physical length -- The maximum logical length of the array before it automatically grows.
    3. Grow length -- The number of entries by which the physical length will grow as required.
    
    \sa
    TD_Db
    
    <group Other_Classes>
*/
template <class T, class A> class OdArray
{
public:
  using size_type = typename A::size_type;
  using iterator = T*;
  using const_iterator = const T*;
  using value_type = T;
  using const_reference = const T&;
  using reference = T&;
  using ConstForPtrT = typename std::conditional<std::is_pointer<T>::value,
    typename std::add_const<typename std::remove_pointer<T>::type>::type*, T>::type;
private:
  struct Buffer : OdArrayBuffer
  {
    const T* data() const { return reinterpret_cast<const T*>(this+1); }
    T* data() { return reinterpret_cast<T*>(this + 1); }

    static Buffer* allocate(size_type nLength2Allocate, int nGrowBy)
    {
      OdUInt64 nBytes2Allocate = (OdUInt64)sizeof(Buffer) + nLength2Allocate * sizeof(T);
      ODA_ASSERT(nBytes2Allocate > nLength2Allocate); // size_type overflow
      size_t nBytes2AllocateSize_t = (size_t)nBytes2Allocate;//size_t overflow on x32
      if(nBytes2Allocate > nLength2Allocate && (OdUInt64)nBytes2AllocateSize_t == nBytes2Allocate)
      {
        Buffer* pBuffer = (Buffer*)::odrxAlloc(nBytes2AllocateSize_t);
        if (pBuffer)
        {
          pBuffer->m_nRefCounter = 1;
          pBuffer->m_nGrowBy     = nGrowBy;
          pBuffer->m_nAllocated  = nLength2Allocate;
          pBuffer->m_nLength     = 0;
          return pBuffer;
        }
      }
      throw OdError(eOutOfMemory);
    }
    static Buffer* _default()
    {
      return reinterpret_cast<Buffer*>(&g_empty_array_buffer);
    }
    void release()
    {
      ODA_ASSERT(m_nRefCounter);
      if((--m_nRefCounter)==0 && this != _default())
      {
        A::destroyRange(data(), m_nLength);
        ::odrxFree(this);
      }
    }
    void addref() const { ++m_nRefCounter; }
  };
#if defined(_MSC_VER)
#pragma warning(disable : 4127) //  conditional expression is constant
#pragma warning(push)
#endif
  class reallocator
  {
    bool _may_use_realloc;
    Buffer* m_pBuffer;
  public:
    inline reallocator( bool may_use_realloc = false ) : _may_use_realloc(may_use_realloc), m_pBuffer(NULL) {}
    inline void reallocate(OdArray* pArray, size_type nNewLen)
    {
      if(!pArray->referenced())
      {
        if(nNewLen > pArray->physicalLength())
        {
          if ( !_may_use_realloc )
          {
            if (m_pBuffer)
              m_pBuffer->release();
            if (!std::is_copy_constructible<T>::value)
              throw OdError(eNotApplicable); //trying to copy buffer for non-copyable T!
            m_pBuffer = pArray->buffer();
            m_pBuffer->addref(); // save buffer to ensure copy from itself would work (e.g insertAt)
          }
          pArray->copy_buffer(nNewLen, _may_use_realloc);
        }
      }
      else
      {
        pArray->copy_buffer(nNewLen);
      }
    }
    inline ~reallocator() 
    {
      if (m_pBuffer)
        m_pBuffer->release();
    }
  };
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
  friend class reallocator;
  const_iterator begin_const() const { return begin(); }
  iterator begin_non_const() { return begin(); }
  const_iterator end_const() const { return end(); }
  iterator end_non_const() { return end(); }
  void copy_before_write(size_type len, bool may_use_realloc = false )
  {
    if( referenced() )
      copy_buffer(len);
    else if ( len > physicalLength() )
      copy_buffer( len, may_use_realloc );
  }
  void copy_if_referenced() { if(referenced()) { copy_buffer(physicalLength()); } }
#if !defined(SWIG)
  template<typename U = T,
    typename std::enable_if<std::is_same<U, T>::value && std::is_copy_constructible<U>::value, bool>::type = true>
  inline void copyConstructRangeChecked(T* dest, T* source, size_type len)
  {
    A::copyConstructRange(dest, source, len);
  }
  template<typename U = T,
    typename std::enable_if<std::is_same<U, T>::value && !std::is_copy_constructible<U>::value, bool>::type = true>
    inline void copyConstructRangeChecked(T* dest, T* source, size_type len)
  {
    if (len != 0)
      throw OdError(eNotApplicable); //trying to copy buffer for non-copyable T (should never be here)!
  }
#endif
  void copy_buffer(size_type len, bool may_use_realloc = false, bool force_size = false, bool releaseOldBufAfterCopy = true)
  {
    Buffer* pOldBuffer = buffer();
    int nGrowBy = pOldBuffer->m_nGrowBy;
    size_type len2 = len;
    if (!force_size)
    {
      if (nGrowBy > 0)
      {
        len2 += nGrowBy;
        len2 = ((len2 - 1) / nGrowBy) * nGrowBy;
      }
      else
      {
        len2 = pOldBuffer->m_nLength;
        len2 = len2 + -nGrowBy * len2 / 100;
        if (len2 < len)
        {
          len2 = len;
        }
      }
    }
    if (may_use_realloc && A::useRealloc() && !empty())
    {
      Buffer* pNewBuffer = reinterpret_cast<Buffer*>(::odrxRealloc(
        pOldBuffer, len2 * sizeof(T) + sizeof(Buffer), pOldBuffer->m_nAllocated * sizeof(T) + sizeof(Buffer)));
      if (!pNewBuffer)
        throw OdError(eOutOfMemory);
      pNewBuffer->m_nAllocated = len2;
      pNewBuffer->m_nLength = odmin(pNewBuffer->m_nLength, len);
      m_pData = pNewBuffer->data();
    }
    else
    {
      Buffer* pNewBuffer = Buffer::allocate(len2, nGrowBy);
      if (!pNewBuffer)
        throw OdError(eOutOfMemory);
      len = odmin(pOldBuffer->m_nLength, len);
      if (may_use_realloc)
        A::moveConstructRange(pNewBuffer->data(), pOldBuffer->data(), len);
      else
        copyConstructRangeChecked(pNewBuffer->data(), pOldBuffer->data(), len);
      pNewBuffer->m_nLength = len;
      m_pData = pNewBuffer->data();
      if (releaseOldBufAfterCopy)
        pOldBuffer->release();
    }
  }
  inline void assertValid(size_type index) const
  { 
    if(!isValid(index)) 
    { 
      ODA_FAIL(); 
      throw OdError_InvalidIndex(); 
    } 
  }
  static inline void rise_error(OdResult e) 
  { 
    ODA_FAIL(); 
    throw OdError(e); 
  }
public:
  // STL-like interface
  
  /** \details
    Returns an iterator that references the first element in the array object.
  */
  iterator begin() 
  { 
    if (!empty()) 
    { 
      copy_if_referenced(); 
      return data(); 
    } 
    return nullptr;
  }
  /** \details
    Returns a const_iterator that references the first element in the array object.
  */
  const_iterator begin() const 
  { 
    if (!empty()) 
    { 
      return data(); 
    } 
    return nullptr; 
  }

  /** \details
    Returns an iterator that references the location after the last element in the array object.
  */
  iterator end() 
  { 
    if (!empty()) 
    { 
      copy_if_referenced(); 
      return data() + length(); 
    } 
    return nullptr;
  }
  /** \details
    Returns a const_iterator that references the location after the last element in the array object.
  */
  const_iterator end() const 
  { 
    if (!empty()) 
    { 
      return data() + length(); 
    } 
    return nullptr;
  }

  /** \details
    Returns a reverse iterator that references the last element in the array object.
  */
  std::reverse_iterator<iterator> rbegin()
  {
    return std::reverse_iterator<iterator>(end());
  }
  /** \details
    Returns a reverse const_iterator that references the last element in the array object.
  */
  std::reverse_iterator<const_iterator> rbegin() const
  {
    return std::reverse_iterator<const_iterator>(end());
  }

  /** \details
    Returns a reverse iterator that references the location before the first element in the array object.
  */
  std::reverse_iterator<iterator> rend()
  {
    return std::reverse_iterator<iterator>(begin());
  }
  /** \details
    Returns a reverse const_iterator that references the location before the first element in the array object.
  */
  std::reverse_iterator<const_iterator> rend() const
  {
    return std::reverse_iterator<const_iterator>(begin());
  }

  /** \details
    Inserts a range of elements into the array object. 
    
    \param before [in]  Position before which the first element is to be inserted.
    \param first [in]  Position of the first element to be inserted.
    \param afterLast [in]  Position of the first element after the last element to be inserted.
    \remarks
    The range of elements may be from another array object.
  */
  void insert(
    iterator before, 
    const_iterator first, 
    const_iterator afterLast)
  {
#ifdef ODA_DIAGNOSTICS
    if (first >= begin_const() && first < end_const() && before < afterLast)
      throw OdError(L"Inserted iterator range will become invalid while inserting.");
#endif
    size_type len = length();
    size_type index = (size_type)(before - begin_const());
    if(index <= len && afterLast>=first)
    {
      if(afterLast > first)
      {
        size_type num2copy = (size_type)(afterLast - first);
        reallocator r( first < begin() || first >= end() );
        r.reallocate(this, len + num2copy);
        A::defaultConstructFill(m_pData + len, num2copy);
        buffer()->m_nLength = len + num2copy;
        T* pDestination = m_pData + index;
        if (index != len)
        {
          A::moveAssignRange(pDestination + num2copy, pDestination, len - index);
        }
        A::copyAssignRangeDisjoint(pDestination, first, (size_type)(afterLast - first));
      }
    }
    else
    {
      rise_error(eInvalidInput);
    }
  }

  /** \details
    Inserts a range of elements into the array object.

    \param before [in]  Position before which the first element is to be inserted.
    \param first [in]  Position of the first element to be inserted.
    \param afterLast [in]  Position of the first element after the last element to be inserted.
    \remarks
    The range of elements may be from another array object.
  */
  void insertMove(
    iterator before,
    iterator first,
    iterator afterLast)
  {
#ifdef ODA_DIAGNOSTICS
    if (first >= begin_const() && first < end_const() && before < afterLast)
      throw OdError(L"Inserted iterator range will become invalid while inserting.");
#endif
    size_type len = length();
    size_type index = (size_type)(before - begin_const());
    if (index <= len && afterLast >= first)
    {
      if (afterLast > first)
      {
        size_type num2copy = (size_type)(afterLast - first);
        reallocator r(first < begin() || first >= end());
        r.reallocate(this, len + num2copy);
        A::defaultConstructFill(m_pData + len, num2copy);
        buffer()->m_nLength = len + num2copy;
        T* pDestination = m_pData + index;
        if (index != len)
        {
          A::moveAssignRange(pDestination + num2copy, pDestination, len - index);
        }
        A::moveAssignRange(pDestination, first, (size_type)(afterLast - first));
      }
    }
    else
    {
      rise_error(eInvalidInput);
    }
  }
  /** \details
    Specifies the logical length for the array object.

    \param logicalLength [in]  Logical length.
    \param value [in]  Value for the elements that are added to obtain the new logical length.
    \remarks
    The logical length is the number of entries in the array. Initially zero.
  */
  void resize( 
    size_type logicalLength, 
    const T& value )
  {
    size_type len = length();
    int d = logicalLength - len;
    if ( d > 0 )
    {
      increaseLogicalLength(logicalLength, len, d, value);
    }
    else if ( d < 0 )
    {
      d=-d;
      if(!referenced())
      {
        A::destroyRange(m_pData + logicalLength, d);
      }
      else
      {
        copy_buffer(logicalLength);
      }
    }
    buffer()->m_nLength = logicalLength;
  }
  
  /** \details
    Specifies the logical length for the array object.

    \param logicalLength [in]  Logical length.
    \remarks
    The logical length is the number of entries in the array. Initially zero.
  */
  void resize( 
    size_type logicalLength )
  {
    size_type len = length();
    int d = logicalLength - len;
    if ( d > 0 )
    {
      increaseLogicalLength(logicalLength, len, d);
    }
    else if ( d < 0 )
    {
      d = -d;
      if ( !referenced() )
      {
        A::destroyRange( m_pData + logicalLength, d );
      }
      else
      {
        copy_buffer(logicalLength);
      }
    }
    buffer()->m_nLength = logicalLength;
  }
  
  /** \details
    Returns the logical length of the array object.

    \remarks
    The logical length is the number of entries in the array. Initially zero.
  */
  size_type size() const 
  { 
    return buffer()->m_nLength; 
  }

  /** \details
    Indicates whether the array object is empty.
    
    \returns The true value if the array is empty, or false otherwise.
  */
  bool empty() const 
  { 
    return size() == 0; 
  }
  
  /** \details
    Returns the physical length of the array object.

    \remarks
    The physical length is the maximum logical length of the array before it automatically grows.
  */
  size_type capacity() const 
  { 
    return buffer()->m_nAllocated; 
  }

  /** \details
    Sets the physical length of the array object to the specified
    reserve length if the reserve length is greater than its physical length.

    \param reserveLength [in]  Minimum physical length.
    \remarks
    The physical length is the maximum logical length of the array before it automatically grows.
  */
  void reserve(
    size_type reserveLength) 
  {
    if(physicalLength() < reserveLength) 
    { 
      setPhysicalLength(reserveLength); 
    } 
  }

  /** \details
    Assigns the specified range of elements to the array object.

    \param first [in]  Position of the first element to be assigned.
    \param afterLast [in]  Position of the first element after the last element to be assigned.
    \remarks
    After the array object is cleared, the function assigns the specified range of elements from
    another array object.  
  */
  void assign(
    const_iterator first,
    const_iterator afterLast)
  {
#ifdef ODA_DIAGNOSTICS
    if (first >= begin_const() && first < end_const())
      throw OdError(L"Assignment of a subrange from self is not allowed.");
#endif
    clear();
    if (afterLast < first)
    {
      rise_error(eInvalidInput);
    }
    if (afterLast > first)
    {
      size_type num2copy = (size_type)(afterLast - first);
      copy_buffer(num2copy, true);
      buffer()->m_nLength = num2copy;
      A::copyConstructRange(m_pData, first, (size_type)(afterLast - first));
    }
  }

  /** \details
    Assigns the specified range of elements to the array object.

    \param first [in]  Position of the first element to be assigned.
    \param afterLast [in]  Position of the first element after the last element to be assigned.
    \remarks
    After the array object is cleared, the function assigns the specified range of elements from
    another array object.
  */
  void assignMove(
    iterator first,
    iterator afterLast)
  {
#ifdef ODA_DIAGNOSTICS
    if (first >= begin_const() && first < end_const())
      throw OdError(L"Assignment of a subrange from self is not allowed.");
#endif
    clear();
    if (afterLast < first)
    {
      rise_error(eInvalidInput);
    }
    if (afterLast > first)
    {
      size_type num2move = (size_type)(afterLast - first);
      copy_buffer(num2move, true);
      buffer()->m_nLength = num2move;
      A::moveConstructRange(m_pData, first, (size_type)(afterLast - first));
    }
  }
  
  /** \details
    Removes the specified range of elements from the array object.

    \param first [in]  Position of the first element to be erased.
    \param afterLast [in]  Position of the first element after the last element to be erased.
  */
  iterator erase(
    iterator first, 
    iterator afterLast)
  {
    size_type i = (size_type)(first - begin_const());
    if(first != afterLast)
    {
      removeSubArray(i, (size_type)(afterLast-begin_const()-1));
    }
    return begin_non_const()+i;
  }
  /** \details
    Removes the specified element from the array object.

    \param where [in]  Element to remove.
  */
  iterator erase(
    iterator where)
  {
    size_type i = (size_type) (where - begin_const());
    removeAt(i);
    return begin_non_const()+i;
  }
  /** \details
    Removes all elements from the array object.
  */
  void clear()
  {
    copy_if_referenced();
    size_type len = length();
    A::destroyRange(m_pData, len);
    buffer()->m_nLength -= len;
  }

  /** \details
    Appends an element to the end of the array object.

    \param value [in]  Value to append.
  */
  void push_back(
    const T& value)
  {
    size_type len = length();
    bool ref = referenced();
    bool need2Copy = ref || len == physicalLength();

    if (need2Copy && std::addressof(value) >= begin() && std::addressof(value) < end())
    {
      T valueCopy(value);
      copy_buffer(len + 1, !ref);
      A::moveConstruct(m_pData + len, std::move(valueCopy));
    }
    else
    {
      if (need2Copy)
        copy_buffer(len + 1, !ref);
      A::copyConstruct(m_pData + len, value);
    }
    ++buffer()->m_nLength;
  }

  /** \details
    Appends an element to the end of the array object.

    \param value [in]  Value to append.
  */
  void push_back(
    T&& value)
  {
    size_type len = length();
    bool ref = referenced();
    bool need2Copy = ref || len == physicalLength();

    if (need2Copy && std::addressof(value) >= begin() && std::addressof(value) < end())
    {
      T valueMoved(std::move(value));
      copy_buffer(len + 1, !ref);
      A::moveConstruct(m_pData + len, std::move(valueMoved));
    }
    else
    {
      if (need2Copy)
        copy_buffer(len + 1, !ref);
      A::moveConstruct(m_pData + len, std::move(value));
    }
    ++buffer()->m_nLength;
  }
  
  /** \details
    Inserts multiple elements into the array object. 
    
    \param before [in]  Position where the first element is to be inserted.
    \param numElements [in]  Number of elements to insert.
    \param value [in]  Value to insert.
    \returns Iterator pointing to the first inserted element.
  */
  iterator insert(
    iterator before, 
    size_type numElements, 
    const T& value)
  {
    if (numElements == 0)
    {
      return before;
    }
    size_type len = length();
    size_type index = (size_type)(before - begin_const());
    T tmpval(value);
    reallocator r(true);
    r.reallocate(this, len + numElements);
    A::defaultConstructFill(m_pData + len, numElements);
    buffer()->m_nLength = len + numElements;
    T* pData = m_pData;
    pData += index;
    if (index != len)
    {
      A::moveAssignRange(pData + numElements, pData, len - index);
    }
    while (numElements-- > 1)
    {
      pData[numElements] = tmpval;
    }
    pData[0] = std::move(tmpval);
    return begin_non_const()+index;
  }
  /** \details
    Inserts an element into the array object at the specified position.

    \param before [in]  Position where the element is to be inserted.
    \param value [in]  Value to insert.
    \returns Iterator pointing to the inserted element.
  */
  iterator insert(
    iterator before, 
    const T& value = T())
  {
    size_type index = (size_type)(before - begin_const());
    insertAt(index, value);
    return (begin_non_const() + index);
  }
  /** \details
    Inserts an element into the array object at the specified position using move semantics.

    \param before [in]  Position where the element is to be inserted.
    \param value [in]  Value to insert.
    \returns Iterator pointing to the inserted element.
  */
  iterator insert(
    iterator before,
    T&& value)
  {
    size_type index = (size_type)(before - begin_const());
    insertAtMove(index, value);
    return (begin_non_const() + index);
  }

  /** \details
    Indicates whether the array object contains the specified value.
    
    \param value [in]  Value for which to search.
    \param start [in]  Start index of the search.
    \returns The true value if the array object contains the specified value, or false otherwise.
  */
  bool contains(
    const ConstForPtrT& value,
    size_type start = 0) const
  { 
    size_type dummy; 
    return find(value, dummy, start); 
  }

  /** \details
    Returns the length of the array object.

    \returns The number of elements in the array object.
  */
  size_type length() const 
  { 
    return buffer()->m_nLength; 
  }
  
  /** \details
    Indicates whether the array is empty.
    
    \returns The true value if the array is empty, or false otherwise.
  */
  bool isEmpty() const 
  { 
    return length() == 0; 
  }
  
  /** \details
    Returns the logical length of the array object.

    \remarks
    The logical length is the number of entries in the array. Initially zero.
  */
  size_type logicalLength() const 
  { 
    return length(); 
  }
  
  /** \details
    Returns the physical length of the array object.

    \remarks
    The physical length is the maximum logical length of the array before it automatically grows.
  */
  size_type physicalLength() const 
  { 
    return buffer()->m_nAllocated; 
  }
  
  /** \details
    Returns the grow length of the array object.

    \remarks
    The grow length is the number of entries by that the physical length will grow as required.
  */
  int growLength() const 
  { 
    return buffer()->m_nGrowBy; 
  }
  
  /** \details
    Returns the data buffer of the array object.

    \returns Pointer to the data buffer.
  */
  const T* asArrayPtr() const 
  { 
    return data(); 
  }

  /** \details
    Returns the data buffer of the array object.

    \returns Pointer to the data buffer.
  */
  const T* getPtr() const 
  { 
    return data(); 
  }
  
  /** \details
    Returns the data buffer of the array object. 

    \returns Pointer to the data buffer.
  */
  T* asArrayPtr() 
  { 
    copy_if_referenced(); 
    return data(); 
  }
  
  /** \remarks
    For convenient access to the data.
  */
  const T& operator [](
    size_type index) const 
  { 
    assertValid(index); 
    return m_pData[index]; 
  }
  /** \remarks
    For convenient access to the data.
  */
  T& operator [](
    size_type index) 
  { 
    assertValid(index);
    copy_if_referenced();
    return m_pData[index];
  }

  /** \details
    Returns the element of the array object at the specified index.

    \param arrayIndex [in]  Index of the array object.
    \returns Reference to the element at the specified index.
  */
  T& at(size_type arrayIndex) 
  { 
    assertValid(arrayIndex); 
    copy_if_referenced(); 
    return *(data() + arrayIndex); 
  }
  
  /** \details
    Returns the element of the array object at the specified index.

    \param arrayIndex [in] Index of the array object element to return.
    \returns Reference to the element at the specified index.
  */
  const T& at(size_type arrayIndex) const 
  { 
    assertValid(arrayIndex); 
    return *(data() + arrayIndex); 
  }
  
  /** \details
    Sets the element of the array object at the specified index.

    \param arrayIndex [in]  Index of the array object element to set.
    \param value [in]  Value to set. 
    \returns Reference to the array object.
  */
  OdArray& setAt(
    size_type arrayIndex, 
    const T& value)
  { 
    assertValid(arrayIndex); 
    copy_if_referenced(); 
    m_pData[arrayIndex] = value; 
    return *this; 
  }

  /** \details
    Returns the element of the array object at the specified position.

    \param arrayIndex [in]  Index of the array object element to return.
    \returns Reference to the element at the specified position.
  */
  const T& getAt(
    size_type arrayIndex) const 
  { 
    assertValid(arrayIndex); 
    return *(data() + arrayIndex); 
  }
  
  /** \details
    Returns the first element of the array object.

    \returns Reference to the first element of the array object.
  */
  T& first() 
  { 
    return *begin(); 
  }
  const T& first() const 
  { 
    return *begin(); 
  }
  
  /** \details
    Returns the last element of the array object.

    \returns Reference to the last element of the array object.
  */
  T& last() 
  { 
    return at(length() - 1); 
  }
  const T& last() const 
  { 
    return at(length() - 1); 
  }
  
  /** \details
    Appends the specified value to the end of the array object.

    \param value [in]  Value to append.
    \returns The index of the new last element.
  */
  size_type append(
    const T& value) 
  { 
    push_back(value);
    return length() - 1; 
  }

  /** \details
    Appends the specified value to the end of this Array object using move semantics.

    \param value [in]  Value to append.

    \returns
    Returns the index of the new last element.
  */
  size_type append(
    T&& value)
  {
    return appendMove(value);
  }

  /** \details
    Inserts the specified value into this Array object at the specified index using move semantics.
    
    \param arrayIndex [in]  Array index.
    \param value [in]  Value to insert.

    \remarks
    If the specified value supports move semantics value is moved, otherwise value is saved.

    Elements starting at arrayIndex will have their indices incremented.

                0 <= arrayIndex <= length()

    Returns a reference to this Array object.
  */
  OdArray& insertAtMove(
    size_type index,
    T& value)
  {
    if (index > logicalLength())
      rise_error(eInvalidIndex);
    size_type oldLen = logicalLength();

    T tmp(std::move(value));
    reallocator r(true);
    r.reallocate(this, oldLen + 1);
    A::moveConstruct(m_pData + oldLen, std::move(tmp));
    ++buffer()->m_nLength;
    if (index != oldLen) {
      tmp = std::move(m_pData[oldLen]);
      A::moveAssignRange(m_pData + index + 1, m_pData + index, oldLen - index);
      m_pData[index] = std::move(tmp);
    }
    return *this;
  }

  /** \details
    Appends the specified value to the end of this Array object using move semantics.

    \param value [in]  Value to append.
    
    \returns
    Returns the index of the new last element.
  */
  size_type appendMove(T& value)
  {
    push_back(std::move(value));
    return logicalLength() - 1;
  }
  /** \details
    Appends the specified array object to the end of this array object.

    \param otherArray [in]  Array to append.

    \returns Reference to the array object.
  */
  OdArray& appendMove(
    OdArray& otherArray)
  {
    insertMove(end_non_const(), otherArray.begin(), otherArray.end());
    return *this;
  }

  /** \details
    Appends the specified value to the end of this Array object n times.

    \param value [in]  Value to append.
    \param nCount [in] Count.

    \returns
    Returns the reference to this Array.
  */
  OdArray& appendRep(
    const T& value,
    size_type nCount
  )
  {
    if (nCount <= 0)
      return *this;
    size_type oldLen = logicalLength();
    T tmp(value);
    reallocator r(true);
    r.reallocate(this, oldLen + nCount);
    A::copyConstructFill(m_pData + oldLen, nCount, tmp); 
    (buffer()->m_nLength) += nCount; 
    return *this;
  }

  /** \details
    Appends the specified values to the end of this Array object.

    \param args [in]  Values to append.

    \returns
    Returns the reference to this Array.
  */
  template<typename... Args>
  OdArray& appendList(
    const Args&... args
  )
  {
    const size_type numElements = sizeof...(Args);
    if (numElements == 0)
    {
      return *this; 
    }
    reallocator r(!areArgsFromThisArray(args...));
    r.reallocate(this, length() + numElements);

    variadicAssignHelper(length(), args...);

    return *this;
  }

  /** \details
    Returns an iterator to the first element after the last element in the array.

    \returns Pointer to the first element after the last element in the array.
  */
  iterator append() 
  { 
    size_type i = append(T()); 
    return begin_non_const() + i;
  }
  
  /** \details
    Removes the first element from the array object.

    \returns Reference to the array object.
  */
  OdArray& removeFirst() 
  { 
    return removeAt(0); 
  }
  
  /** \details
    Removes the last element from the array object.

    \returns Reference to the array object.
  */
  OdArray& removeLast() 
  {
    resize(length() - 1);
    return *this;
  }
  
  /** \details
    Sets the grow length of the array object.

    \param growLength [in]  Grow length.
    \returns Reference to the array object.
  */
  OdArray& setGrowLength(
    int growLength)
  {
    if (growLength != 0)
    {
      copy_if_referenced();
      buffer()->m_nGrowBy = growLength;
    }
    else
    {
      ODA_FAIL();
    }
    return *this;
  }

  /** \details
    Constructor for the OdArray class.
    
    \param physicalLength [in]  Initial physical length.
    \param growLength [in]  Initial grow length.
  */
  explicit OdArray(
    size_type physicalLength,
    int growLength = 8) : m_pData(0)
  {
    if (growLength == 0)
    {
      growLength = 8;
    }
    m_pData = Buffer::allocate(physicalLength, growLength)->data();
  }
  
  OdArray() : m_pData(Buffer::_default()->data()) 
  { 
    buffer()->addref(); 
  }

  OdArray(const OdArray& source) : m_pData(source.m_pData) 
  { 
    static_assert(std::is_copy_constructible<T>::value, "Can not copy array with non-copyable argument");
    buffer()->addref(); 
  }

  OdArray(OdArray&& source) : m_pData(source.m_pData)
  {
    source.m_pData = Buffer::_default()->data();
    source.buffer()->addref();
  }
  
  /** \details
    This constructor allows initialization from an initializer list.
    For example OdArray<int> a{ 1, 2, 3, 4 };
  */
  OdArray(std::initializer_list<T> l)
  {
    m_pData = Buffer::allocate(static_cast<size_type>(l.size()), 8)->data();
    assign(l.begin(), l.end());
  }

#if !defined(SWIG)
#if !defined(_MSC_VER) || (_MSC_VER > 1800)
  /** \details
    This constructor allows initialization from a range of forward iterators (providing multipass guarantee).
    \param begin [in]  Range start.
    \param end   [in]  Range end.
  */
  template <typename Iter, typename std::enable_if<
     std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value, bool>::type = true>
  OdArray(Iter begin, Iter end)
  {
    m_pData = Buffer::allocate(static_cast<size_type>(std::distance(begin, end)), 8)->data();
    assign(begin, end);
  }
  
  /** \details
    This constructor allows initialization from a range of generic input iterators (no multipass guarantee).
    For example: OdDbObjectIdArray a{ modelspace->ids().begin(), modelspace->ids().end() }; // here modelspace is a pointer to OdDbBlockTableRecord.
    \param begin [in]  Range start.
    \param end   [in]  Range end.
  */
  template <typename Iter, typename std::enable_if<
    std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value
    && !std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>::value, bool>::type = true>
  OdArray(Iter begin, Iter end)
  {
    m_pData = Buffer::_default()->data();
    buffer()->addref();
    for (Iter i = begin; i != end; ++i)
      push_back(*i);
  }
#else // VS 2013 with half baked SFINAE support
  /** \details
    This constructor allows initialization from a range of generic input iterators (no multipass guarantee).
    For example: OdDbObjectIdArray a{ modelspace->ids().begin(), modelspace->ids().end() }; // here modelspace is a pointer to OdDbBlockTableRecord.
    \param begin [in]  Range start.
    \param end   [in]  Range end.
  */
  template <class Iter, class = typename std::enable_if<
    std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<typename Iter>::iterator_category>::value, void>::type>
  OdArray(Iter begin, Iter end)
  {
    construct(begin, end, std::_Iter_cat(begin));
  }
private:
  template<class Iter>  void construct(Iter begin, Iter end, std::input_iterator_tag)
  {
    m_pData = Buffer::_default()->data();
    buffer()->addref();
    for (Iter i = begin; i != end; ++i)
      push_back(*i);
  }
  template<class Iter>  void construct(Iter begin, Iter end, std::forward_iterator_tag)
  {
    m_pData = Buffer::allocate(static_cast<size_type>(std::distance(begin, end)), 8)->data();
    assign(begin, end);
  }
public:
#endif // _MSC_VER <= 1800
#endif // SWIG

  /** \details
    Creates an array from the specified array.
    \param sourceArray  [in]  Array to create from.
    \param sourceLength [in]  Length of the source array.
    \returns Created array.
  */
  static OdArray<T, A> create(const T* sourceArray, int sourceLength)
  {
    OdArray<T, A> res(sourceLength);
    res.assign(sourceArray, sourceArray + sourceLength);
    return res;
  }
  
  /** \details
    Destroys an array instance.
  */
  ~OdArray() 
  { 
    buffer()->release(); 
  }

  OdArray& operator =(
    const OdArray& source)
  {
    static_assert(std::is_copy_constructible<T>::value, "Can not copy array with non-copyable argument");
    source.buffer()->addref();
    buffer()->release();
    m_pData = source.m_pData;
    return *this;
  }

  OdArray& operator =(
    OdArray&& source)
  {
    buffer()->release();
    m_pData = source.m_pData;
    source.m_pData = Buffer::_default()->data();
    source.buffer()->addref();
    return *this;
  }

  bool operator ==(
    const OdArray& array) const
  {
    if(length() == array.length())
    {
      for(size_type i = 0; i < length(); i++)
      {
        if(at(i) != array[i])
        {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  bool operator !=(
    const OdArray& array) const
  {
    return !operator == (array);
  }
  
  /** \details
    Sets all the elements in the array object to the specified value.

    \param value [in]  Value to assign.
    \returns Reference to the array object.
  */
  OdArray& setAll(
    const T& value)
  {
    copy_if_referenced();
    T* pData = m_pData;
    size_type n = length();
    while(n)
    {
      pData[--n] = value;
    }
    return *this;
  }
  /** \details
    Appends the specified array object to the end of this array object.

    \param otherArray [in]  Array to append.
    
    \returns Reference to the array object.
  */
  OdArray& append(
    const OdArray& otherArray)
  {
    insert(end_non_const(), otherArray.begin(), otherArray.end());
    return *this;
  }

  /** \details
    Appends the specified array object to the end of this array object.

    \param otherArray [in]  Array to append.

    \returns Reference to the array object.
  */
  OdArray& append(
    OdArray&& otherArray)
  {
    appendMove(otherArray);
    return *this;
  }
  
  /** \details
    Inserts the specified value into the array object at the specified index.

    \param index [in]  Index where the element should be inserted.
    \param value [in]  Value to insert.
    \returns Reference to the array object.
    \remarks
                0 <= index <= length()
    
    Elements starting at index will have their indices incremented.
  */
  OdArray& insertAt(
    size_type index,
    const T& value)
  {
    if (index > logicalLength())
      rise_error(eInvalidIndex);
    size_type oldLen = logicalLength();

    T tmp(value);
    reallocator r(true);
    r.reallocate(this, oldLen + 1);
    A::moveConstruct(m_pData + oldLen, std::move(tmp));
    ++buffer()->m_nLength;
    if (index != oldLen) {
      tmp = std::move(m_pData[oldLen]);
      A::moveAssignRange(m_pData + index + 1, m_pData + index, oldLen - index);
      m_pData[index] = std::move(tmp);
    }
    return *this;
  }
  
  /** \details
    Inserts the specified value into this Array object at the specified index using move semantics.

    \param index [in]  Index where the element should be inserted.
    \param value [in]  Value to insert.
    \returns Reference to the array object.
    \remarks
                0 <= index <= length()
    
    Elements starting at index will have their indices incremented.
  */
  OdArray& insertAt(
    size_type index,
    T&& val
  )
  {
    return insertAtMove(index, val); 
  }

  /** \details
    Constructs an element and places it to the end of the array object.

    \param args [in]  Constructor arguments.
  */
  template<class... Args>
  void emplace_back(Args&&... args)
  {
    reallocator r(!areArgsFromThisArray(std::forward<Args>(args)...));
    size_type len = length();
    r.reallocate(this, len + 1);
    A::construct(m_pData + len, std::forward<Args>(args)...);
    ++buffer()->m_nLength;
  }

  /** \details
    Constructs an element and places it into the array object at the specified index.

    \param index [in]  Index where the element should be inserted.
    \param args [in]  Constructor arguments.
    \returns Reference to the array object.
    \remarks
                0 <= index <= length()
    
    Elements starting at index will have their indices incremented.
  */
  template<class... Args>
  OdArray& emplaceAt(
    size_type index,
    Args&&... args)
  {
    if (index > logicalLength())
      rise_error(eInvalidIndex);
    size_type oldLen = logicalLength();

    reallocator r(!areArgsFromThisArray(std::forward<Args>(args)...));
    r.reallocate(this, oldLen + 1);
    A::construct(m_pData + oldLen, std::forward<Args>(args)...);
    ++buffer()->m_nLength;
    if (index != oldLen) {
      T tmp = std::move(m_pData[oldLen]);
      A::moveAssignRange(m_pData + index + 1, m_pData + index, oldLen - index);
      m_pData[index] = std::move(tmp);
    }
    return *this;
  }

  /** \details
    Constructs an element and places it into the array object at the specified position.

    \param before [in]  Position where the element is to be inserted.
    \param args [in]  Constructor arguments.
    \returns Iterator pointing to the inserted element.
  */
  template<class... Args>
  iterator emplace(
    iterator before,
    Args&&... args)
  {
    size_type index = (size_type)(before - begin_const());
    emplaceAt(index, std::forward<Args>(args)...);
    return begin_non_const() + index;
  }

  /** \details
    Removes the element at the specified index from the array object.

    \param arrayIndex [in]  Index of the element to remove.
    \returns Reference to the array object.
    \remarks
                0 <= arrayIndex < length()
    
    Elements starting at arrayIndex+1 will have their indices decremented.
  */
  OdArray& removeAt(
    size_type arrayIndex)
  {
    assertValid(arrayIndex);
    size_type len = length();
    if (arrayIndex < --len)
    {
      copy_if_referenced();
      T* pData = m_pData;
      A::moveAssignRange(pData + arrayIndex, pData + arrayIndex + 1, len - arrayIndex);
    }
    resize(len);
    return *this;
  }
  
  /** \details
    Removes the specified elements from the array object.

    \param startIndex [in]  Index of the first element to remove.
    \param endIndex [in]  Index after the last element to remove.
    \returns Reference to the array object.
    \remarks
    Elements from the range [startIndex, endIndex) are removed.
  */
  OdArray& removeSubArray(
    size_type startIndex, 
    size_type endIndex)
  {
    if (!isValid(startIndex) || startIndex > endIndex)
    {
      rise_error(eInvalidIndex);
    }
    size_type len = length();
    copy_if_referenced();
    T* pData = m_pData;
    ++endIndex;
    size_type n2remove = endIndex - startIndex;
    A::moveAssignRange(pData + startIndex, pData + endIndex, len - endIndex);
    A::destroyRange(pData + len - n2remove, n2remove);
    buffer()->m_nLength -= n2remove;
    return *this;
  }
  
  /** \details
    Indicates whether the array object contains the specified value and receives the index of the found value.

    \param value [in]  Value for which to search.
    \param findIndex [out]  Receives the index of the found value.
    \param start [in]  Start index of the search.
    \returns The true value if the array object contains the specified value, or false otherwise.
  */
  bool find(
    const ConstForPtrT& value,
    size_type& findIndex,
    size_type start = 0) const
  {
    if (!empty())
    {
      assertValid(start);
      size_type len = length();
      const T* pData = m_pData;
      for (size_type i = start; i < len; ++i)
      {
        if (pData[i] == value)
        {
          findIndex = i;
          return true;
        }
      }
    }
    return false;
  }
  
  /** \details
    Sets the logical length of the array object.

    \param logLength [in]  Logical length.
    \remarks
    The physical length is increased as required. 
    The logical length is the number of entries in the array. Initially zero.
  */
  OdArray& setLogicalLength(
    size_type logLength)
  {
    resize(logLength);
    return *this;
  }
  
  /** \details
    Sets the physical length of the array object.

    \param physLength [in]  Physical length.
    \remarks
    The logical length is decreased as required.
    The physical length is the maximum logical length of the array before it automatically grows.
  */
  OdArray& setPhysicalLength(
    size_type physLength)
  {
    if(physLength==0)
    {
      *this = OdArray<T, A>();
    }
    else if(physLength != physicalLength())
    {
      copy_buffer(physLength, !referenced(), true);
    }
    return *this;
  }
  
  /** \details
    Reverses the order of the elements in the array object.

    \returns Reference to the array object.
  */
  OdArray& reverse()
  {
    if(!empty())
    {
      copy_if_referenced();
      T tmp;
      iterator iter1 = begin_non_const();
      iterator iter2 = end_non_const();
      --iter2;
      while(iter1 < iter2)
      {
        tmp = *iter1;
        *iter1 = *iter2;
        *iter2 = tmp;
        ++iter1;
        --iter2;
      }
    }
    return *this;
  }
    
  /** \details
    Swaps the specified elements in the array object.

    \param firstIndex [in]  Index of first element.
    \param secondIndex [in]  Index of second element.
    \returns Reference to the array object.
  */
  OdArray& swap(
    size_type firstIndex, 
    size_type secondIndex)
  {
    if(!isValid(firstIndex) || !isValid(secondIndex))
    {
      rise_error(eInvalidIndex);
    }    
    if(firstIndex != secondIndex)
    {
      T tmp = std::move(at(firstIndex));
      at(firstIndex) = std::move(at(secondIndex));
      at(secondIndex) = std::move(tmp);
    }
    return *this;
  }

  /** \details
    Swaps buffers of the array object and another one.

    \param other [in,out]  The other array to swap buffers with.
  */
  void swap(
    OdArray &other)
  {
    T *temp = m_pData;
    m_pData = other.m_pData;
    other.m_pData = temp;
  }

  /** \details
    Removes the element with the specified value from the array object.
    
    \param value [in]  Value for which to search.
    \param start [in]  Start index of the search.
    \returns The true value if an element is removed, or false otherwise.
    \remarks
    Removes the first occurence of the value starting at start.
  */
  bool remove(
    const T& value, 
    size_type start = 0)
  {
    size_type i = 0;
    if(find(value, i, start))
    {
      removeAt(i);
      return true;
    }
    return false;
  }
private:

  T*    m_pData;

  bool isValid(size_type i) const 
  { 
    return i < length();
  }

  T* data() 
  { 
    return (length() ? m_pData : nullptr); 
  }

  const T* data() const 
  {
    return (length() ? m_pData : nullptr);
  }

  const Buffer* buffer() const
  {
    return reinterpret_cast<const Buffer*>(m_pData) - 1;
  }
  Buffer* buffer()
  {
    return reinterpret_cast<Buffer*>(m_pData) - 1;
  }
  bool referenced() const
  {
    return buffer()->m_nRefCounter > 1;
  }

  // to support appendList() call without args 
  OdArray& variadicAssignHelper(
    size_type
  )
  {
    return *this;
  }

  // called when last value is to be assigned 
  OdArray& variadicAssignHelper(
    size_type index, 
    const T& value
  )
  {
    A::copyConstruct(&m_pData[index], value);
    ++(buffer()->m_nLength);
    return *this;
  }

  template<typename... Args>
  OdArray& variadicAssignHelper(
    size_type index,
    const T& value,
    const Args&... args
  )
  {
    variadicAssignHelper(index, value); 
    return variadicAssignHelper(index + 1, args...);
  }

#if !defined(SWIG)
  template<typename U = T,
    typename std::enable_if<std::is_same<U, T>::value && !std::is_move_assignable<U>::value, bool>::type = true>
  void increaseLogicalLength(
    size_type,
    size_type,
    int,
    const T&)
  {
    throw OdError(eNotApplicable);
  }

  template<typename U = T,
    typename std::enable_if<std::is_same<U, T>::value && std::is_move_assignable<U>::value, bool>::type = true>
  void increaseLogicalLength(
    size_type logicalLength,
    size_type oldLen,
    int diff,
    const T& value)
  {
    reallocator r(m_pData > std::addressof(value) || std::addressof(value) > m_pData + oldLen);
    r.reallocate(this, logicalLength);
    A::copyConstructFill(m_pData + oldLen, diff, value);
  }

  template<typename U = T,
    typename std::enable_if<std::is_same<U, T>::value && !std::is_default_constructible<U>::value, bool>::type = true>
  void increaseLogicalLength(
    size_type,
    size_type,
    int)
  {
    throw OdError(eNotApplicable);
  }

  template<typename U = T,
    typename std::enable_if<std::is_same<U, T>::value && std::is_default_constructible<U>::value, bool>::type = true>
  void increaseLogicalLength(
    size_type /*logicalLength*/,
    size_type oldLen,
    int diff)
  {
    copy_before_write(oldLen + diff, true);
    A::defaultConstructFill(m_pData + oldLen, diff);
  }
#endif

  bool areArgsFromThisArray()
  {
    return false;
  }
  template<class U>
  bool areArgsFromThisArray(U&& arg)
  {
    return static_cast<const void*>(std::addressof(arg)) >= static_cast<const void*>(begin()) &&
      static_cast<const void*>(std::addressof(arg)) < static_cast<const void*>(end());
  }
  template<class U, class... Args>
  bool areArgsFromThisArray(U&& arg, Args&&... args)
  {
    return areArgsFromThisArray(std::forward<U>(arg)) || areArgsFromThisArray(std::forward<Args>(args)...);
  }
};

#include "TD_PackPop.h"

#endif // ODARRAY_H_INCLUDED


