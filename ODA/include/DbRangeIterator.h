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

#pragma once

#include "SmartPtr.h"

#ifndef SWIG
/** \details
  <group OdDb_Classes>

  This class is an iterator wrapper to be used to implement "range-based for" loop support
  in collections using OdDbSymbolTableIterator and OdDbObjectIterator 
  (actually any iterator that uses `step()` function to iterate).
  When the wrapper iterator `done()` function returns true, it is released and becomes equal to the null iterator representing collection end.
*/
template<class I, class V = I*> class OdDbStepIteratorWrap
{
protected:
  OdSmartPtr<I> m_pIterator;
public:
  using difference_type = ptrdiff_t;
  using value_type = V;
  using pointer = V*;
  using reference = V&;
  using iterator_category = std::input_iterator_tag;
  /** \details
    Default constructor
  */ 
  OdDbStepIteratorWrap(const OdSmartPtr<I>& i)
  {
    m_pIterator = i;
    if (!!m_pIterator && m_pIterator->done())
      m_pIterator.release();
  }

  /** \details
    Dereference operator
    \returns Wrapped iterator.
  */
  I* operator*() { return m_pIterator.get(); }

  /** \details
    Dereference operator
    \returns Wrapped iterator.
  */
  const I* operator*() const { return m_pIterator.get(); }

  /** \details
    Natural comparison operator.
  */
  bool operator ==(const OdDbStepIteratorWrap& other) const { return m_pIterator == other.m_pIterator; }

  /** \details
    Natural comparison operator.
  */
  bool operator !=(const OdDbStepIteratorWrap& other) const { return m_pIterator != other.m_pIterator; }

  /** \details
    Increment operator. Moves iterator forward.
  */
  const OdDbStepIteratorWrap& operator++()
  {
    if (!!m_pIterator)
    {
      m_pIterator->step();
      if (m_pIterator->done())
        m_pIterator.release();
    }
    return *this;
  }
};
#endif


