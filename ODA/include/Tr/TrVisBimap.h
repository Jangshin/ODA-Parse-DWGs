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
// Bidirectional maps.

#ifndef ODTRVISBIMAP
#define ODTRVISBIMAP

#include "TD_PackPush.h"

#include <unordered_set>
#include <set>

// Original source code: https://github.com/LarsHagemann/bimap

template <class _KeyType, class _ValueType,
          class _Key_Container = std::set<_KeyType>,
          class _Mapped_Container = std::set<_ValueType>> class OdTrVisBimap
{
  public:
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, std::pair<const _KeyType&, const _ValueType&>>
    {
      public:
        typedef const_iterator self_type;
        typedef std::pair<typename _Key_Container::iterator, typename _Mapped_Container::iterator> value_type;
        typedef int difference_type;
        explicit const_iterator(const value_type& value) : m_data(std::move(value)) { }
        const self_type& operator++() { ++m_data.first; ++m_data.second; return *this; }
        const value_type& operator*() { return m_data; }
        bool operator==(const self_type& rhs) { return m_data.first == rhs.m_data.first; }
        bool operator!=(const self_type& rhs) { return m_data.first != rhs.m_data.first; }
      private:
        value_type m_data;
    };
    using key_type = _KeyType;
    using value_type = _ValueType;
    using rkey_type = _ValueType;
    using rvalue_type = _KeyType;
  private:
    using _Tree = _Key_Container;
    using _RTree = _Mapped_Container;
    using _Tree_Node = std::pair<key_type, value_type>;
    using _RTree_Node = std::pair<rkey_type, rvalue_type>;
  private:
    // Test for the container types
#if 0 // C++17
    static_assert(std::is_same_v<key_type, typename _Tree::key_type>,
                  "OdTrVisBimap::key_type has to match _Container_Type::key_type!");
    static_assert(std::is_same_v<rkey_type, typename _RTree::key_type>,
                  "OdTrVisBimap::rkey_type has to match _Reverse_Container_Type::key_type!");
#else
    static_assert(std::is_same<key_type, typename _Tree::key_type>::value,
                  "OdTrVisBimap::key_type has to match _Container_Type::key_type!");
    static_assert(std::is_same<rkey_type, typename _RTree::key_type>::value,
                  "OdTrVisBimap::rkey_type has to match _Reverse_Container_Type::key_type!");
#endif
  private:
    _Tree m_key_tree;
    _RTree m_value_tree;
  private:
    /* Inner helper functions */
    inline size_t index_of_key(const key_type& key) const
    {
      const auto k_itr = m_key_tree.find(key);
      const auto offset = static_cast<unsigned>(std::distance(m_key_tree.begin(), k_itr));
      return (offset < m_key_tree.size() ? offset : 0);
    }
    inline size_t index_of_value(const value_type& value) const
    {
      const auto v_itr = m_value_tree.find(value);
      const auto offset = static_cast<unsigned>(std::distance(m_value_tree.begin(), v_itr));
      return (offset < m_value_tree.size() ? offset : 0);
    }
    inline value_type value_at_index(size_t index) const
    {
      auto v_itr = m_value_tree.begin();
      std::advance(v_itr, index);
      return *v_itr;
    }
    inline key_type key_at_index(size_t index) const
    {
      auto k_itr = m_key_tree.begin();
      std::advance(k_itr, index);
      return *k_itr;
    }
  public:
    /* Constructors */
    OdTrVisBimap() = default;
    OdTrVisBimap(std::initializer_list<_Tree_Node> init)
    {
      for (const auto& elem : init)
        insert(elem);
    }
  public:
    /* Iterator functions */
    const_iterator begin()	const { return const_iterator({ m_key_tree.begin(), m_value_tree.begin() }); }
    const_iterator end()	const { return const_iterator({ m_key_tree.end(), m_value_tree.end() }); }
  public:
    /* Modification functions */
    void insert(_Tree_Node&& node)
    {
      m_key_tree.emplace_hint(m_key_tree.begin(), std::move(node.first));
      m_value_tree.emplace_hint(m_value_tree.begin(), std::move(node.second));
    }
    void insert(const _Tree_Node& node)
    {
      m_key_tree.emplace_hint(m_key_tree.begin(), std::move(node.first));
      m_value_tree.emplace_hint(m_value_tree.begin(), std::move(node.second));
    }
    void insert(const key_type& key, const value_type& value)
    {
      m_key_tree.emplace_hint(m_key_tree.begin(), std::move(key));
      m_value_tree.emplace_hint(m_value_tree.begin(), std::move(value));
    }
    void erase_key(const key_type& key)
    {
      const auto k_itr = m_key_tree.find(key);
      const auto offset = std::distance(m_key_tree.begin(), k_itr);
      auto v_itr = m_value_tree.begin();
      std::advance(v_itr, offset);
      m_key_tree.erase(k_itr);
      m_value_tree.erase(v_itr);
    }
    void erase_value(const value_type& value)
    {
      const auto v_itr = m_value_tree.find(value);
      const auto offset = std::distance(m_value_tree.begin(), v_itr);
      auto k_itr = m_key_tree.begin();
      std::advance(k_itr, offset);
      m_key_tree.erase(k_itr);
      m_value_tree.erase(v_itr);
    }
  public:
    /* Helper functions */
    bool has_key(const key_type& key) const
    {
      return m_key_tree.find(key) != m_key_tree.end();
    }
    bool has_value(const value_type& value) const
    {
      return m_value_tree.find(value) != m_value_tree.end();
    }
    value_type get_value(const key_type& key) const
    {
      const auto offset = index_of_key(key);
      auto v_itr = m_value_tree.begin();
      std::advance(v_itr, offset);
      return *v_itr;
    }
    key_type get_key(const value_type& value) const
    {
      const auto offset = index_of_value(value);
      auto k_itr = m_key_tree.begin();
      std::advance(k_itr, offset);
      return *k_itr;
    }
    size_t size() const
    {
      return m_key_tree.size();
    }
};

template<class _KeyType, class _ValueType>
using OdTrVisUnorderedBimap = OdTrVisBimap<_KeyType, _ValueType, std::unordered_set<_KeyType>, std::unordered_set<_ValueType>>;

#include "TD_PackPop.h"

#endif // ODTRVISBIMAP
