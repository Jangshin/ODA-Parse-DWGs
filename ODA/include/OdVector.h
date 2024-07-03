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

#ifndef OdVector_H_INCLUDED
#define OdVector_H_INCLUDED

#include <new>
#include <utility>

#include "TD_PackPush.h"

#include "OdArrayMemAlloc.h"
#include "OdAlloc.h"

template <class T, class A = OdObjectsAllocator<T>, class Mm = OdrxMemoryManager> class OdVector;

/** \details
  This template class implements dynamic vector objects within the ODA Platform.

  \remarks
  Objects of the OdVector and OdArray classes are similar: elements are sequenced linearly, elements can be directly accessed, adding and deleting elements from the end is fast, and the objects can resize automatically when an element is inserted or deleted. However, OdVector objects use internal dynamic arrays that may need to be reallocated to increase in size when new elements are inserted. This does not happen every time an element is added though because an initial larger size is set to allow for growth.

  A vector owns its own buffer. This means that when a class object is copied or moved, the buffer is also copied or moved.
    
  Use the OdArray class to avoid unnecessary array copies in cases where, according to the rules of C++, OdVector is copied, although this is not necessary.
  It is recommended to use C++11 move semantics with OdVector to avoid unnecessary buffer copying.
  The OdVector class works similarly to std::vector.


  Methods are provided to access vector elements via both vector indices and vector pointers (iterators).

  Definitions:

  1. Logical length or size -- The number of entries in the vector. Initially zero.
  2. Physical length -- The maximum logical length of the vector before it automatically grows.
  3. Grow length -- The number of entries by which the physical length will grow as required.

  \sa
  Db

  <group Other_Classes>
*/
template <class T, class A, class Mm> class OdVector
{
public:
  using size_type = typename A::size_type;
  using iterator = T*;
  using const_iterator = const T*;
  // compatibility with OdArray
  using value_type = T;
  using const_reference = const T&;
  using reference = T&;
  using ConstForPtrT = typename std::conditional<std::is_pointer<T>::value,
    typename std::add_const<typename std::remove_pointer<T>::type>::type*, T>::type;

private:
  static T* allocate(size_type physicalLength);

  size_type calcPhysicalLength(size_type minPhysicalLength)
  {
    if (m_growLength > 0)
    {
      return ((minPhysicalLength + m_growLength - 1) / m_growLength) * m_growLength;
    }
    else
    {
      size_type newPhysicalLength = m_logicalLength + (-m_growLength)*m_logicalLength / 100;

      if (newPhysicalLength < minPhysicalLength)
        newPhysicalLength = minPhysicalLength;

      return newPhysicalLength;
    }
  }

  void release();
  
  void reallocate(size_type physicalLength, bool isUseRealloc = false, bool isForcePhysicalLength = false);
  
  bool isValid(size_type index) const;
  void assertValid(size_type index) const;
  
  static void riseError(OdResult res);
  
  const_iterator begin_const() const;
  iterator begin_non_const();
  const_iterator end_const() const;
  iterator end_non_const();

public:
  /** \details
    Creates a new instance of an OdVector object.
  
    \param physicalLength [in]  Initial physical length.
    \param growLength [in]  Initial grow length. The default value is 8.
  */
  explicit OdVector(size_type physicalLength, int growLength = 8);
  
  /** \details
    Default constructor for an OdVector object.
  */
  OdVector();

  /** \details
    Copy constructor. Creates a vector and initializes it with parameters of the specified vector.

    \param vec [in] Vector object to copy.
  */
  OdVector(const OdVector& vec);

  /** \details
    Move constructor. Creates a vector and initializes it with parameters of the specified vector, that is then cleared.

    \param vec [in] Vector object to move.
  */
  OdVector(OdVector&& vec);

  /** \details
    Destroys a vector instance.
  */
  ~OdVector();

  OdVector& operator=(const OdVector& vec);
  OdVector& operator=(OdVector&& vec);
  
  /** \details
    Returns an iterator referring to the first element in this vector object.
  */
  iterator begin();
  
  /** \details
    Returns an iterator referring to the first element in this vector object.
  */
  const_iterator begin() const;

  /** \details
    Returns an iterator referring to the past-the-end element in this vector object.
  */
  iterator end();

  /** \details
    Returns an iterator referring to the past-the-end element in this vector object.
  */
  const_iterator end() const;
  
  /** \details
    Inserts a range of elements into the vector object.

    \param before [in]  Position after which the first element should be inserted.
    \param first [in]  Position of the first element to be inserted.
    \param afterLast [in]  Position of the first element after the last element to be inserted.
    \remarks
    The range of elements may be from another vector object.
  */
  void insert(iterator before, const_iterator first, const_iterator afterLast);

  /** \details
    Inserts a range of elements into the vector object.

    \param before [in]  Position after which the first element should be inserted.
    \param first [in]  Position of the first element to be inserted.
    \param afterLast [in]  Position of the first element after the last element to be inserted.
    \remarks
    The range of elements may be from another vector object.
  */
  void insertMove(iterator before, iterator first, iterator afterLast);

  /** \details
    Inserts an element into the vector object.

    \param before [in]  Position after which the first element should be inserted.
    \param numElem [in]  Number of elements to insert.
    \param value [in]  Value to insert.
  */
  iterator insert(iterator before, size_type numElem, const T& value);

  /** \details
    Inserts an element into the vector object.

    \param before [in]  Position after which the first element should be inserted.
    \param value [in]  Value to insert.
  */
  iterator insert(iterator before, const T& value = T());
  /** \details
    Inserts an element into the vector object.

    \param before [in]  Position after which the first element should be inserted.
    \param value [in]  Value to insert.
  */
  iterator insert(iterator before, T&& value = T());

  /** \details
    Inserts the specified value into the vector object at the specified index.

    \param index [in]  Index where the element should be inserted.
    \param value [in]  Value to insert.
    \returns Reference to the vector object.
    \remarks
          0 <= index <= length()
    Elements starting at the index will have their indices incremented.
  */
  OdVector& insertAt(size_type index, const T& value);

  /** \details
    Inserts the specified value into the vector object at the specified index.

    \param index [in]  Index where the element should be inserted.
    \param value [in]  Value to insert.
    \returns Reference to the vector object.
    \remarks
          0 <= index <= length()
    Elements starting at the index will have their indices incremented.
  */
  OdVector& insertAt(size_type index, T&& value);

  /** \details
    Constructs an element and places it into the vector object at the specified position.

    \param before [in]  Position where the element is to be inserted.
    \param args [in]  Constructor arguments.
    \returns Iterator pointing to the inserted element.
  */
  template<class... Args>
  iterator emplace(iterator before, Args&&... args);

  /** \details
    Constructs an element and places it into the vector object at the specified index.

    \param index [in]  Index where the element should be inserted.
    \param args [in]  Constructor arguments.
    \returns Reference to the vector object.
    \remarks
                0 <= index <= length()

    Elements starting at index will have their indices incremented.
  */
  template<class... Args>
  OdVector& emplaceAt(size_type index, Args&&... args);

  /** \details
    Removes the element at the specified index from the vector object.

    \param index [in]  Index of the element to remove.
    \returns Reference to the vector object.
    \remarks
        0 <= index < length()
    Elements starting at index+1 will have their indices decremented.
  */
  OdVector& removeAt(size_type index);

  /** \details
    Removes the specified elements from the vector object.

    \param startIndex [in]  Index of the first element to remove.
    \param endIndex [in]  Index after the last element to remove.
    \returns Reference to the vector object.
    \remarks
    Elements from the range [startIndex, endIndex) are removed.
  */
  OdVector& removeSubArray(size_type startIndex, size_type endIndex);

  /** \details
    Removes the element with the specified value from the vector object.

    \param value [in]  Value for which to search.
    \param startIndex [in]  Start index of the search.
    \returns The true value if an element is removed, or false otherwise.
    \remarks
    Removes the first occurance of the value starting at startIndex.
  */
  bool remove(const T& value, size_type startIndex = 0);

  /** \details
    Specifies the logical length for the vector object.

    \param logicalLength [in]  Logical length.
    \param value [in]  Value for the elements that are added to obtain the new logical length.
    \remarks
    The logical length is the number of entries in the array. Initially zero.
  */
  void resize(size_type logicalLength, const T& value);

  /** \details
    Specifies the logical length for the vector object.

    \param logicalLength [in]  Logical length.
    \remarks
    The logical length is the number of entries in the array. Initially zero.
  */
  void resize(size_type logicalLength);

  /** \details
    Returns the logical length of the vector object.

    \remarks
    The logical length is the number of entries in the array. Initially zero.
  */
  size_type size() const;

  /** \details
    Indicates whether the vector is empty.

    \returns The true value if the vector is empty, or false otherwise.
  */
  bool empty() const;

  /** \details
    Returns the physical length of the vector object.

    \remarks
    The physical length is the maximum logical length of the vector before it automatically grows.
  */
  size_type capacity() const;

  /** \details
    Sets the physical length of the vector object to the specified
    reserve length if the reserve length is greater than its physical length.

    \param reserveLength [in]  Minimum physical length.
  */
  void reserve(size_type reserveLength);

  /** \details
    Assigns the specified range of elements to the vector object.

    \param first [in]  Position of the first element to be assigned.
    \param afterLast [in]  Position of the first element after the last element to be assigned.
    \remarks
    After the vector object is cleared, the function assigns the specified range of elements from
    another vector object.
  */
  void assign(const_iterator first, const_iterator afterLast);

  /** \details
    Assigns the specified range of elements to the vector object.

    \param first [in]  Position of the first element to be assigned.
    \param afterLast [in]  Position of the first element after the last element to be assigned.
    \remarks
    After the vector object is cleared, the function assigns the specified range of elements from
    another vector object.
  */
  void assignMove(iterator first, iterator afterLast);

  /** \details
    Removes a range of elements from the vector object.

    \param first [in]  Position of the first element to be assigned.
    \param afterLast [in]  Position of the first element after the last element to be assigned.
  */
  iterator erase(iterator first, iterator afterLast);

  /** \details
    Removes the specified element from the vector object.

    \param where [in]  Element to remove.
  */
  iterator erase(iterator where);

  /** \details
    Removes all elements from the vector object.
  */
  void clear();

  /** \details
    Appends an element to the end of the vector object.

    \param value [in] Value to append.
  */
  void push_back(const T& value);

  /** \details
    Appends an element to the end of the vector object.

    \param value [in] Value to append.
  */
  void push_back(T&& value);

  /** \details
    Constructs an element and places it to the end of the vector object.

    \param args [in]  Constructor arguments.
  */
  template<class... Args>
  void emplace_back(Args&&... args);

  /** \details
    Indicates whether the vector object contains ths specified value.

    \param value [in]  Value for which to search.
    \param startIndex [in]  Start index of the search.
    \returns The true value if the vector object contains the specified value, or false otherwise.
  */
  bool contains(const ConstForPtrT& value, size_type startIndex = 0) const;

  /** \details
    Returns the length of the vector object.

    \returns The number of elements in the vector object.
  */
  size_type length() const;

  /** \details
    Indicates whether the vector is empty.

    \returns The true value if the vector is empty, or false otherwise.
  */
  bool isEmpty() const;

  /** \details
    Returns the logical length of the vector object.

    \returns The number of entries in the vector object.
  */
  size_type logicalLength() const;

  /** \details
    Returns the physical length of the vector object.

    \returns The maximum logical length of the vector before it automatically grows.
  */
  size_type physicalLength() const;

  /** \details
    Returns the grow length of the vector object.

    \returns The number of entries by which the physical length will grow as required.
  */
  int growLength() const;

  /** \details
    Returns the data buffer of the vector object.

    \returns Pointer to the data buffer.
  */
  const T* asArrayPtr() const;

  /** \details
    Returns the data buffer of the vector object.
    
    \returns Pointer to the data buffer.
  */
  const T* getPtr() const;

  /** \details
    Returns the data buffer of the vector object.
      
    \returns Pointer to the data buffer.
  */
  T* asArrayPtr();

  /** \details
    For convenient access to the data.
  */
  const T& operator[](size_type index) const;

  /** \details
    For convenient access to the data.
  */
  T& operator[](size_type index);

  /** \details
    Returns the element of the vector object at the specified index.

    \param arrayIndex [in]  Index of the vector element.
    \returns Reference to the element at the specified index.
  */
  T& at(size_type index);

  /** \details
    Returns the element of the vector object at the specified index.
    
    \param arrayIndex [in]  Index of the vector element.
    \returns Reference to the element at the specified index.
  */
  const T& at(size_type index) const;

  /** \details
    Sets the element of the vector object at the specified index.

    \param arrayIndex [in]  Index of the vector element for which to set the value.
    \param value [in]  Value of the element to set.
    \returns Reference to the vector.
  */
  OdVector& setAt(size_type index, const T& value);

  /** \details
    Returns the element of the vector object at the specified position.

    \param arrayIndex [in]  Index of the vector element for which to return the value.
    \returns Reference to the specified element.
  */
  const T& getAt(size_type index) const;

  /** \details
    Returns the first element of the vector object.
    
    \returns Reference to the first element of the vector.
  */
  T& first();

  /** \details
    Returns the first element of the vector object.
    
    \returns Reference to the first element of the vector.
  */
  const T& first() const;

  /** \details
    Returns the last element of the vector object.
    
    \returns Reference to the last element of the vector.
  */
  T& last();

  /** \details
    Returns the last element of the vector object.
    
    \returns Reference to the last element of the vector.
  */
  const T& last() const;

  /** \details
    Appends the specified value to the end of the vector object.

    \param value [in]  Value to append.
    \returns The index of the new last element.
  */
  size_type append(const T& value);

  /** \details
    Appends the specified value to the end of the vector object.

    \param value [in]  Value to append.
    \returns The index of the new last element.
  */
  size_type append(T&& value);

  /** \details
    Returns an interator to the first element
    after the last element in the array.

    \returns Pointer to the first element after the last element in the array.
  */
  iterator append();

  /** \details
    Appends the specified vector object to the end of the vector object.

    \param vec [in]  Vector to append.
    \returns Reference to the vector object.
  */
  OdVector& append(const OdVector& vec);

  /** \details
    Appends the specified vector object to the end of the vector object.

    \param vec [in]  Vector to append.
    \returns Reference to the vector object.
  */
  OdVector& append(OdVector&& vec);

  /** \details
    Appends the specified vector object to the end of the vector object.

    \param vec [in]  Vector to append.
    \returns Reference to the vector object.
  */
  OdVector& appendMove(OdVector& vec);

  /** \details
    Removes the first element from the vector object.
  */
  OdVector& removeFirst();

  /** \details
    Removes the last element from the vector object.
  */
  OdVector& removeLast();

  bool operator==(const OdVector& vec) const;

  /** \details
    Sets all the elements in the vector object to the specified value.

    \param value [in]  Value to set.
    \returns Reference to the vector object.
  */
  OdVector& setAll(const T& value);

  /** \details
    Indicates whether the vector object contains the specified value and receives the index of the found value.

    \param value [in]  Value to search for.
    \param index [out]  Receives the index of the found value.
    \param startIndex [in]  Start index of the search.
    \returns The true value if the vector object contains the specified value, or false otherwise.
  */
  bool find(const ConstForPtrT& value, size_type& index, size_type startIndex = 0) const;

  /** \details
    Sets the logical length of the vector object.

    \param logicalLength [in]  Logical length.
    \returns Reference to the vector object.
    \remarks
    The physical length is increased as required.
    The logical length is the number of entries in the vector. Initially zero.
  */
  OdVector& setLogicalLength(size_type logicalLength);

  /** \details
    Sets the physical length of the vector object.

    \param physicalLength [in]  Physical length.
    \returns Reference to the vector object.
    \remarks
    The logical length is decreased as required.
    The physical length is the maximum logical length of the vector before it automatically grows.
  */
  OdVector& setPhysicalLength(size_type physicalLength);

  /** \details
    Sets the grow length of the vector object.

    \param growLength [in]  Grow length.
    \returns Reference to the vector object.
    \remarks
    The grow length is the number of entries by which the physical length will grow as required.
  */
  OdVector& setGrowLength(int growLength);

  /** \details
    Reverses the order of the elements in the vector object.

    \returns Reference to the vector object.
  */
  OdVector& reverse();

  /** \details
    Swaps the specified elements in the vector object.

    \param firstIndex [in]  Index of the first element.
    \param secondIndex [in]  Index of the second element.
    \returns Reference to the vector object.
  */
  OdVector& swap(size_type firstIndex, size_type secondIndex);

  /** \details
    Swaps buffers of the vector object and another one.
    \param other [in,out]  The other vector to swap buffers with.
  */
  void swap(OdVector &other);

private:
  T* m_pData;
  size_type m_physicalLength;
  size_type m_logicalLength;
  int m_growLength;
};

#define VEC_SIZE_TYPE typename OdVector<T, A, Mm>::size_type
#define VEC_ITERATOR typename OdVector<T, A, Mm>::iterator
#define VEC_CONST_ITERATOR typename OdVector<T, A, Mm>::const_iterator

template<class T, class A, class Mm>
inline OdVector<T, A, Mm>::OdVector(size_type physicalLength, int growLength)
: m_pData(NULL), m_physicalLength(physicalLength), m_logicalLength(0)
, m_growLength(growLength)
{
  if(m_growLength == 0)
  {
    ODA_FAIL();
    m_growLength = -200;
  }
  if (m_physicalLength)
  {
    m_pData = allocate(m_physicalLength);
  }
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>::OdVector()
: m_pData(NULL), m_physicalLength(0), m_logicalLength(0), m_growLength(-200)
{
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>::OdVector(const OdVector<T, A, Mm>& vec)
: m_pData(NULL), m_physicalLength(vec.m_physicalLength)
, m_logicalLength(vec.m_logicalLength), m_growLength(vec.m_growLength)
{
  static_assert(std::is_copy_constructible<T>::value, "Can not copy vector with non-copyable argument");
  if(m_physicalLength > 0)
  {
    m_pData = allocate(m_physicalLength);

    A::copyConstructRange(m_pData, vec.m_pData, m_logicalLength);
  }
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>::OdVector(OdVector<T, A, Mm>&& vec)
  : m_pData(vec.m_pData), m_physicalLength(vec.m_physicalLength)
  , m_logicalLength(vec.m_logicalLength), m_growLength(vec.m_growLength)
{
  vec.m_pData = nullptr;
  vec.m_physicalLength = 0;
  vec.m_logicalLength = 0;
  vec.m_growLength = -200;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>::~OdVector()
{
  release();
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::operator=(const OdVector<T, A, Mm>& vec)
{
  static_assert(std::is_copy_constructible<T>::value, "Can not copy vector with non-copyable argument");
  if(this != &vec)
  {
    release();
    m_logicalLength = 0;
    if (vec.m_logicalLength > 0)
    {
      m_pData = allocate(vec.m_logicalLength);
      m_physicalLength = vec.m_logicalLength;
      A::copyConstructRange(m_pData, vec.m_pData, vec.m_logicalLength);
      m_logicalLength = vec.m_logicalLength;
    }
  }
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::operator=(OdVector<T, A, Mm>&& vec)
{
  if(this != &vec)
  {
    release();
    m_pData = vec.m_pData;
    m_physicalLength = vec.m_physicalLength;
    m_logicalLength = vec.m_logicalLength;
    m_growLength = vec.m_growLength;
    vec.m_pData = nullptr;
    vec.m_physicalLength = 0;
    vec.m_logicalLength = 0;
    vec.m_growLength = -200;
  }
  return *this;
}

template <class T, class A, class Mm>
inline T* OdVector<T, A, Mm>::allocate(size_type physicalLength)
{
  ODA_ASSERT(physicalLength != 0);
  OdUInt64 nBytes2Allocate = (OdUInt64)physicalLength * sizeof(T);
  ODA_ASSERT(nBytes2Allocate >= physicalLength); // size_type overflow
  size_t nBytes2AllocateSize_t = (size_t)nBytes2Allocate;//size_t overflow on x32
  T* pData = NULL;
  if (nBytes2Allocate >= physicalLength && (OdUInt64)nBytes2AllocateSize_t == nBytes2Allocate)
    pData = static_cast<T*>(Mm::Alloc(nBytes2AllocateSize_t));

  if (pData == NULL)
    throw OdError(eOutOfMemory);

  return pData;
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::release()
{
  if (m_pData != NULL)
  {
    A::destroyRange(m_pData, m_logicalLength);

    Mm::Free(m_pData);
    m_pData = NULL;
    m_physicalLength = 0;
  }
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::reallocate(size_type physicalLength, bool isUseRealloc, bool isForcePhysicalLength)
{
  T* pOldData = m_pData;
  size_type newPhysicalLength = physicalLength;

  if(!isForcePhysicalLength)
    newPhysicalLength = calcPhysicalLength(physicalLength);
  
  if(isUseRealloc && A::useRealloc() && m_logicalLength > 0 && m_pData != NULL)
  {
    m_pData = reinterpret_cast<T*>(Mm::Realloc(pOldData, newPhysicalLength*sizeof(T), m_physicalLength*sizeof(T)));

    if (!m_pData)
      throw OdError(eOutOfMemory);

    m_physicalLength = newPhysicalLength;

    if(physicalLength < m_logicalLength)
      m_logicalLength = physicalLength;
  }
  else
  {
    T* pNewData = allocate(newPhysicalLength);
    const size_type newLogicalLength = odmin(m_logicalLength, physicalLength);

    A::moveConstructRange(pNewData, pOldData, newLogicalLength);
    
    release();

    m_pData = pNewData;
    m_physicalLength = newPhysicalLength;
    m_logicalLength = newLogicalLength;
  }
}

template <class T, class A, class Mm>
inline bool OdVector<T, A, Mm>::isValid(size_type index) const
{
  // index is unsigned here, no need >= 0 check
  return (index < m_logicalLength);
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::assertValid(size_type index) const
{
  if(!isValid(index))
  {
    ODA_FAIL();
    throw OdError_InvalidIndex();
  }
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::riseError(OdResult res)
{
  ODA_FAIL();
  throw OdError(res);
}

template <class T, class A, class Mm>
inline VEC_CONST_ITERATOR OdVector<T, A, Mm>::begin_const() const
{
  return begin();
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::begin_non_const()
{
  return begin();
}

template <class T, class A, class Mm>
inline VEC_CONST_ITERATOR OdVector<T, A, Mm>::end_const() const
{
  return end();
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::end_non_const()
{
  return end();
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::begin()
{
  return (!isEmpty() ? m_pData : NULL);
}

template <class T, class A, class Mm>
inline VEC_CONST_ITERATOR OdVector<T, A, Mm>::begin() const
{
  return (!isEmpty() ? m_pData : NULL);
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::end()
{
  return (!isEmpty() ? m_pData + m_logicalLength : NULL);
}

template <class T, class A, class Mm>
inline VEC_CONST_ITERATOR OdVector<T, A, Mm>::end() const
{
  return (!isEmpty() ? m_pData + m_logicalLength : NULL);
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::insert(iterator before, const_iterator first, const_iterator afterLast)
{
#ifdef ODA_DIAGNOSTICS
  if (first >= begin_const() && first < end_const() && before < afterLast)
    throw OdError(L"Inserted iterator range will become invalid while inserting.");
#endif
  const size_type oldLogicalLength = m_logicalLength;
  const size_type index = (size_type)(before - begin_const());
  
  if(index <= m_logicalLength && afterLast >= first)
  {
    if(afterLast > first)
    {
      const size_type numElem = (size_type)(afterLast - first);
      const size_type newLogicalLength = oldLogicalLength + numElem;
      
      if (newLogicalLength <= m_physicalLength)
      {
        A::defaultConstructFill(m_pData + oldLogicalLength, numElem);
        m_logicalLength = newLogicalLength;
        T* pData = m_pData + index;

        if (index != oldLogicalLength)
          A::moveAssignRange(pData + numElem, pData, oldLogicalLength - index);

        A::copyAssignRangeDisjoint(pData, first, numElem);
      }
      else
      {
        size_type newPhysicalLength = calcPhysicalLength(newLogicalLength);
        T* pNewData = allocate(newPhysicalLength);
        A::copyConstructRange(pNewData + index, first, numElem);
        A::moveConstructRange(pNewData, m_pData, index);
        A::moveConstructRange(pNewData + index + numElem, m_pData + index, m_logicalLength - index);
        release();
        m_pData = pNewData;
        m_physicalLength = newPhysicalLength;
        m_logicalLength = newLogicalLength;
      }
    }
  }
  else
    riseError(eInvalidInput);
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::insertMove(iterator before, iterator first, iterator afterLast)
{
#ifdef ODA_DIAGNOSTICS
  if (first >= begin_const() && first < end_const() && before < afterLast)
    throw OdError(L"Inserted iterator range will become invalid while inserting.");
#endif
  const size_type oldLogicalLength = m_logicalLength;
  const size_type index = (size_type)(before - begin_const());

  if (index <= m_logicalLength && afterLast >= first)
  {
    if (afterLast > first)
    {
      const size_type numElem = (size_type)(afterLast - first);
      const size_type newLogicalLength = oldLogicalLength + numElem;

      if (newLogicalLength <= m_physicalLength)
      {
        A::defaultConstructFill(m_pData + oldLogicalLength, numElem);
        m_logicalLength = newLogicalLength;
        T* pData = m_pData + index;

        if (index != oldLogicalLength)
          A::moveAssignRange(pData + numElem, pData, oldLogicalLength - index);

        A::moveAssignRange(pData, first, numElem);
      }
      else
      {
        size_type newPhysicalLength = calcPhysicalLength(newLogicalLength);
        T* pNewData = allocate(newPhysicalLength);
        A::moveConstructRange(pNewData + index, first, numElem);
        A::moveConstructRange(pNewData, m_pData, index);
        A::moveConstructRange(pNewData + index + numElem, m_pData + index, m_logicalLength - index);
        release();
        m_pData = pNewData;
        m_physicalLength = newPhysicalLength;
        m_logicalLength = newLogicalLength;
      }
    }
  }
  else
    riseError(eInvalidInput);
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::insert(iterator before, size_type numElem, const T& value)
{
  if (numElem == 0)
    return before;

  const size_type oldLogicalLength = m_logicalLength;
  const size_type newLogicalLength = oldLogicalLength + numElem;
  const size_type index = (size_type)(before - begin_const());
  
  if (index == oldLogicalLength)
  {
    if (newLogicalLength <= m_physicalLength)
    {
      A::copyConstructFill(m_pData + oldLogicalLength, numElem, value);
    }
    else
    {
      const T valueCopy(value);
      reallocate(newLogicalLength, true);
      A::copyConstructFill(m_pData + oldLogicalLength, numElem - 1, valueCopy);
      A::copyConstruct(m_pData + oldLogicalLength + numElem - 1, std::move(valueCopy));
    }
    m_logicalLength = newLogicalLength;
  }
  else if (index < oldLogicalLength)
  {
    const T valueCopy(value);
    if (newLogicalLength > m_physicalLength)
      reallocate(newLogicalLength, true);

    A::defaultConstructFill(m_pData + oldLogicalLength, numElem);

    m_logicalLength = newLogicalLength;

    T* pData = m_pData + index;

    A::moveAssignRange(pData + numElem, pData, oldLogicalLength - index);

    while (numElem-- > 1)
      pData[numElem] = valueCopy;
    pData[0] = std::move(valueCopy);
  }

  return (begin_non_const() + index);
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::insert(iterator before, const T& value)
{
  const size_type index = (size_type)(before - begin_const());
  
  insertAt(index, value);
  
  return (begin_non_const() + index);
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::insert(iterator before, T&& value)
{
  const size_type index = (size_type)(before - begin_const());

  insertAt(index, std::move(value));

  return (begin_non_const() + index);
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::insertAt(size_type index, const T& value)
{
  const size_type oldLogicalLength = m_logicalLength;
  const size_type newLogicalLength = oldLogicalLength + 1;
  
  if (index == oldLogicalLength)
  {
    push_back(value);
  }
  else if (index < oldLogicalLength)
  {
    const T valueCopy(value);
    if (newLogicalLength > m_physicalLength)
      reallocate(newLogicalLength, true);

    A::defaultConstruct(m_pData + oldLogicalLength);

    ++m_logicalLength;

    T* pData = m_pData + index;

    A::moveAssignRange(pData + 1, pData, oldLogicalLength - index);

    *pData = std::move(valueCopy);
  }
  else
    riseError(eInvalidIndex);
  
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::insertAt(size_type index, T&& value)
{
  const size_type oldLogicalLength = m_logicalLength;
  const size_type newLogicalLength = oldLogicalLength + 1;

  if (index == oldLogicalLength)
  {
    push_back(std::move(value));
  }
  else if (index < oldLogicalLength)
  {
    T valueMoved(std::move(value));
    if (newLogicalLength > m_physicalLength)
      reallocate(newLogicalLength, true);

    A::defaultConstruct(m_pData + oldLogicalLength);

    ++m_logicalLength;

    T* pData = m_pData + index;

    A::moveAssignRange(pData + 1, pData, oldLogicalLength - index);

    *pData = std::move(valueMoved);
  }
  else
    riseError(eInvalidIndex);

  return *this;
}

template <class T, class A, class Mm>
template <class... Args>
inline VEC_ITERATOR OdVector<T, A, Mm>::emplace(iterator before, Args&&... args)
{
  const size_type index = (size_type)(before - begin_const());

  emplaceAt(index, std::forward<Args>(args)...);

  return (begin_non_const() + index);
}

template <class T, class A, class Mm>
template <class... Args>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::emplaceAt(size_type index, Args&&... args)
{
  const size_type oldLogicalLength = m_logicalLength;
  const size_type newLogicalLength = oldLogicalLength + 1;

  if (index == oldLogicalLength)
  {
    emplace_back(std::forward<Args>(args)...);
  }
  else if (index < oldLogicalLength)
  {
    size_type newPhysicalLength = calcPhysicalLength(newLogicalLength);
    T* pNewData = allocate(newPhysicalLength);
    A::construct(pNewData + index, std::forward<Args>(args)...);
    A::moveConstructRange(pNewData, m_pData, index);
    A::moveConstructRange(pNewData + index + 1, m_pData + index, m_logicalLength - index);
    release();
    m_pData = pNewData;
    m_physicalLength = newPhysicalLength;
    m_logicalLength = newLogicalLength;
  }
  else
    riseError(eInvalidIndex);

  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::removeAt(size_type index)
{
  assertValid(index);
  
  const size_type newLogicalLength = m_logicalLength - 1;
  
  if(index < newLogicalLength)
  {
    T* pData = m_pData + index;
    A::moveAssignRange(pData, pData + 1, newLogicalLength - index);
  }
  
  resize(newLogicalLength);
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::removeSubArray(size_type startIndex, size_type endIndex)
{
  if(!isValid(startIndex) || startIndex > endIndex)
    riseError(eInvalidIndex);
  
  const size_type oldLogicalLength = m_logicalLength;
  
  T* pData = m_pData;
  
  ++endIndex;
  
  const size_type numElem = endIndex - startIndex;
  
  A::moveAssignRange(pData + startIndex, pData + endIndex, oldLogicalLength - endIndex);
  A::destroyRange(pData + oldLogicalLength - numElem, numElem);
  
  m_logicalLength -= numElem;  
  return *this;
}

template <class T, class A, class Mm>
inline bool OdVector<T, A, Mm>::remove(const T& value, size_type startIndex)
{
  size_type index = 0;
  if(find(value, index, startIndex))
  {
    removeAt(index);
    return true;
  }
  return false;
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::resize(size_type logicalLength, const T& value)
{
  const size_type oldLogicalLength = m_logicalLength;
  const int lengthDiff = logicalLength - oldLogicalLength;

  if(lengthDiff > 0)
  {
    const T valueCopy(value);
    if (logicalLength > m_physicalLength)
      reallocate(logicalLength, true);

    A::copyConstructFill(m_pData + oldLogicalLength, lengthDiff, valueCopy);
  }
  else if(lengthDiff < 0)
    A::destroyRange(m_pData + logicalLength, -lengthDiff);

  m_logicalLength = logicalLength;
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::resize(size_type logicalLength)
{
  const size_type oldLogicalLength = m_logicalLength;

  if(logicalLength > oldLogicalLength)
  {
    if(logicalLength > m_physicalLength)
      reallocate(logicalLength, true);
    A::defaultConstructFill(m_pData + oldLogicalLength, logicalLength - oldLogicalLength);
  }
  else if(logicalLength < oldLogicalLength)
    A::destroyRange(m_pData + logicalLength, oldLogicalLength - logicalLength);

  m_logicalLength = logicalLength;
}

template <class T, class A, class Mm>
inline VEC_SIZE_TYPE OdVector<T, A, Mm>::size() const
{
  return m_logicalLength;
}

template <class T, class A, class Mm>
inline bool OdVector<T, A, Mm>::empty() const
{
  return (m_logicalLength == 0);
}

template <class T, class A, class Mm>
inline VEC_SIZE_TYPE OdVector<T, A, Mm>::capacity() const
{
  return m_physicalLength;
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::reserve(size_type reserveLength)
{
  if(m_physicalLength < reserveLength)
    setPhysicalLength(reserveLength);
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::assign(const_iterator first, const_iterator afterLast)
{
#ifdef ODA_DIAGNOSTICS
  if (first >= begin_const() && first < end_const())
    throw OdError(L"Assignment of a subrange from self is not allowed.");
#endif
  clear();
  insert(begin_non_const(), first, afterLast);
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::assignMove(iterator first, iterator afterLast)
{
#ifdef ODA_DIAGNOSTICS
  if (first >= begin_const() && first < end_const())
    throw OdError(L"Assignment of a subrange from self is not allowed.");
#endif
  clear();
  insertMove(begin_non_const(), first, afterLast);
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::erase(iterator first, iterator afterLast)
{
  const size_type index = (size_type)(first - begin_const());
	
  if(first != afterLast)
    removeSubArray(index, (size_type)(afterLast - begin_const() - 1));
	
  return (begin_non_const() + index);
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::erase(iterator it)
{
  const size_type index = (size_type)(it - begin_const());
	
  removeAt(index);

  return (begin_non_const() + index);
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::clear()
{
  const size_type numElem = (size_type)(end_const() - begin_const());
  A::destroyRange(m_pData, numElem);
  m_logicalLength = 0;
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::push_back(const T& value)
{
  if (m_physicalLength > m_logicalLength)
  {
    A::copyConstruct(m_pData + m_logicalLength, value);
  }
  else
  {
    const T valueCopy(value);
    reallocate(m_logicalLength + 1, true);
    A::copyConstruct(m_pData + m_logicalLength, std::move(valueCopy));
  }
  ++m_logicalLength;
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::push_back(T&& value)
{
  if (m_physicalLength > m_logicalLength)
  {
    A::moveConstruct(m_pData + m_logicalLength, std::move(value));
  }
  else
  {
    T valueMoved(std::move(value));
    reallocate(m_logicalLength + 1, true);
    A::moveConstruct(m_pData + m_logicalLength, std::move(valueMoved));
  }
  ++m_logicalLength;
}

template <class T, class A, class Mm>
template<class... Args>
inline void OdVector<T, A, Mm>::emplace_back(Args&&... args)
{
  if (m_physicalLength > m_logicalLength)
  {
    A::construct(m_pData + m_logicalLength, std::forward<Args>(args)...);
  }
  else
  {
    size_type newPhysicalLength = calcPhysicalLength(m_logicalLength + 1);
    T* pNewData = allocate(newPhysicalLength);
    A::construct(pNewData + m_logicalLength, std::forward<Args>(args)...);
    A::moveConstructRange(pNewData, m_pData, m_logicalLength);
    release();
    m_pData = pNewData;
    m_physicalLength = newPhysicalLength;
  }
  ++m_logicalLength;
}

template <class T, class A, class Mm>
inline bool OdVector<T, A, Mm>::contains(const ConstForPtrT& value, size_type startIndex) const
{
  size_type index;

  return find(value, index, startIndex);
}

template <class T, class A, class Mm>
inline VEC_SIZE_TYPE OdVector<T, A, Mm>::length() const
{
  return m_logicalLength;
}

template <class T, class A, class Mm>
inline bool OdVector<T, A, Mm>::isEmpty() const
{
  return (m_logicalLength == 0);
}

template <class T, class A, class Mm>
inline VEC_SIZE_TYPE OdVector<T, A, Mm>::logicalLength() const
{
  return m_logicalLength;
}

template <class T, class A, class Mm>
inline VEC_SIZE_TYPE OdVector<T, A, Mm>::physicalLength() const
{
  return m_physicalLength;
}

template <class T, class A, class Mm>
inline int OdVector<T, A, Mm>::growLength() const
{
  return m_growLength;
}

template <class T, class A, class Mm>
inline const T* OdVector<T, A, Mm>::asArrayPtr() const
{
  return m_pData;
}

template <class T, class A, class Mm>
inline const T* OdVector<T, A, Mm>::getPtr() const
{
  return m_pData;
}

template <class T, class A, class Mm>
inline T* OdVector<T, A, Mm>::asArrayPtr()
{ // OdArray::asArrayPtr invokes non-const version of data() method which checks length and return null.
  // Constant version of asArrayPtr and getPtr will return m_pData as is for OdArray too.
  return (length()) ? m_pData : NULL;
}

template <class T, class A, class Mm>
inline const T& OdVector<T, A, Mm>::operator[](size_type index) const
{
  assertValid(index);
  return m_pData[index];
}

template <class T, class A, class Mm>
inline T& OdVector<T, A, Mm>::operator[](size_type index)
{
  assertValid(index);
  return m_pData[index];
}

template <class T, class A, class Mm>
inline T& OdVector<T, A, Mm>::at(size_type index)
{
  assertValid(index);
  return m_pData[index];
}

template <class T, class A, class Mm>
inline const T& OdVector<T, A, Mm>::at(size_type index) const
{
  assertValid(index);
  return m_pData[index];
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::setAt(size_type index, const T& value)
{
  assertValid(index);
  
  m_pData[index] = value;
  
  return *this;
}

template <class T, class A, class Mm>
inline const T& OdVector<T, A, Mm>::getAt(size_type index) const
{
  assertValid(index);
  return m_pData[index];
}

template <class T, class A, class Mm>
inline T& OdVector<T, A, Mm>::first()
{
  return m_pData[0];
}

template <class T, class A, class Mm>
inline const T& OdVector<T, A, Mm>::first() const
{
  return m_pData[0];
}

template <class T, class A, class Mm>
inline T& OdVector<T, A, Mm>::last()
{
  return m_pData[m_logicalLength - 1];
}

template <class T, class A, class Mm>
inline const T& OdVector<T, A, Mm>::last() const
{
  return m_pData[m_logicalLength - 1];
}

template <class T, class A, class Mm>
inline VEC_SIZE_TYPE OdVector<T, A, Mm>::append(const T& value)
{
  push_back(value);
  return (m_logicalLength - 1);
}
template <class T, class A, class Mm>
inline VEC_SIZE_TYPE OdVector<T, A, Mm>::append(T&& value)
{
  push_back(std::move(value));
  return (m_logicalLength - 1);
}

template <class T, class A, class Mm>
inline VEC_ITERATOR OdVector<T, A, Mm>::append()
{
  const size_type index = append(T());
  return (begin_non_const() + index);
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::append(const OdVector<T, A, Mm>& vec)
{
  insert(end_non_const(), vec.begin(), vec.end());
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::appendMove(OdVector<T, A, Mm>& vec)
{
  insertMove(end_non_const(), vec.begin(), vec.end());
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::append(OdVector<T, A, Mm>&& vec)
{
  return appendMove(vec);
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::removeFirst()
{
  return removeAt(0);
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::removeLast()
{
  return removeAt(m_logicalLength - 1);
}

template <class T, class A, class Mm>
inline bool OdVector<T, A, Mm>::operator==(const OdVector<T, A, Mm>& vec) const
{
  if(m_logicalLength == vec.m_logicalLength)
  {
    for(size_type i = 0; i < m_logicalLength; ++i)
    {
      if(m_pData[i] != vec.m_pData[i])
        return false;
    }
    return true;
  }
  return false;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::setAll(const T& value)
{
  for(size_type i = 0; i < m_logicalLength; ++i)
    m_pData[i] = value;
  
  return *this;
}

template <class T, class A, class Mm>
inline bool OdVector<T, A, Mm>::find(const ConstForPtrT& value, size_type& index, size_type startIndex) const
{
  if(!isEmpty())
  {
    assertValid(startIndex);
    
    for(size_type i = startIndex; i < m_logicalLength; ++i)
    {
      if(m_pData[i] == value)
      {
        index = i;
        return true;
      }
    }
  }
  return false;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::setLogicalLength(size_type logicalLength)
{
  resize(logicalLength);
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::setPhysicalLength(size_type physicalLength)
{
  if(physicalLength == 0)
  {
    release();
    
    m_pData = NULL;
    m_physicalLength = 0;
  }
  else if(physicalLength != m_physicalLength)
    reallocate(physicalLength, true, true);
  
  if(m_physicalLength < m_logicalLength)
    m_logicalLength = m_physicalLength;
  
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::setGrowLength(int growLength)
{
  if(growLength != 0)
    m_growLength = growLength;
  else
    ODA_FAIL();
  
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::reverse()
{
  if(!isEmpty())
  {
    T value;
    iterator it1 = begin_non_const();
    iterator it2 = end_non_const();
    
    --it2;
    
    while(it1 < it2)
    {
      value = *it1;
      *it1 = *it2;
      *it2 = value;
      
      ++it1;
      --it2;
    }
  }  
  return *this;
}

template <class T, class A, class Mm>
inline OdVector<T, A, Mm>& OdVector<T, A, Mm>::swap(size_type firstIndex, size_type secondIndex)
{
  if(!isValid(firstIndex) || !isValid(secondIndex))
    riseError(eInvalidIndex);
  
  if(firstIndex != secondIndex)
  {
    T value = std::move(m_pData[firstIndex]);
    m_pData[firstIndex] = std::move(m_pData[secondIndex]);
    m_pData[secondIndex] = std::move(value);
  }
  
  return *this;
}

template <class T, class A, class Mm>
inline void OdVector<T, A, Mm>::swap(OdVector<T, A, Mm> &other)
{
  T* ptr = m_pData;
  m_pData = other.m_pData;
  other.m_pData = ptr;
  size_type sz = m_physicalLength;
  m_physicalLength = other.m_physicalLength;
  other.m_physicalLength = sz;
  sz = m_logicalLength;
  m_logicalLength = other.m_logicalLength;
  other.m_logicalLength = sz;
  int tmpi = m_growLength;
  m_growLength = other.m_growLength;
  other.m_growLength = tmpi;
}


#include "TD_PackPop.h"

typedef OdVector<int, OdMemoryAllocator<int> > OdIntVector;
typedef OdVector<OdUInt32, OdMemoryAllocator<OdUInt32> > OdUInt32Vector;
typedef OdVector<OdInt32, OdMemoryAllocator<OdInt32> > OdInt32Vector;
typedef OdVector<OdUInt8, OdMemoryAllocator<OdUInt8> > OdUInt8Vector;
typedef OdVector<OdUInt64, OdMemoryAllocator<OdUInt64> > OdUInt64Vector;
typedef OdVector<bool, OdMemoryAllocator<bool> > OdBoolVector;
#ifdef OD_GEPNT3D_H
typedef OdVector<OdGePoint3d, OdMemoryAllocator<OdGePoint3d> > OdGePoint3dVector;
#endif
#ifdef OD_GEVEC3D_H
typedef OdVector<OdGeVector3d, OdMemoryAllocator<OdGeVector3d> > OdGeVector3dVector;
#endif

#endif // OdVector_H_INCLUDED
