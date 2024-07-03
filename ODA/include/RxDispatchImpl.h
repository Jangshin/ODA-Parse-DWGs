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




#ifndef __PROPERTIES_H_INCLUDED_
#define __PROPERTIES_H_INCLUDED_

#include "TD_PackPush.h"

#include "RxDictionary.h"
#include "RxObjectImpl.h"
#include "OdString.h"

/** \details

    <group OdRx_Classes> 
*/
class OdRxPropDesc : public OdRxObject
{
public:
  virtual OdString name() const = 0;
  virtual OdRxObjectPtr prop_get(const void* pThis) const = 0;
  virtual void prop_put(void* pThis, OdRxObject* pVal) = 0;
};

/** \details

    <group OdRx_Classes> 
*/
template <class TBase = OdRxDictionary>
class OdRxDispatchImpl : public TBase
{
  typedef OdRxPropDesc PropDesc;
protected:
  class Iterator : public OdRxObjectImpl<OdRxDictionaryIterator>
  {
    OdRxDictionaryPtr         m_pOwner;
    OdRxDictionaryIteratorPtr m_pDescIter;
  public:
    Iterator(OdRxDictionary* pOwner, OdRxDictionaryIterator* pDescIter)
      : m_pOwner(pOwner), m_pDescIter(pDescIter) {}

    static OdRxDictionaryIteratorPtr createObject(OdRxDictionary* pOwner, OdRxDictionaryIterator* pDescIter)
    {
      return OdRxDictionaryIteratorPtr((OdRxDictionaryIterator*)new Iterator(pOwner, pDescIter), kOdRxObjAttach);
    }
    OdString getKey() const { return m_pOwner->keyAt(id()); }
    OdUInt32 id() const { return m_pDescIter->id(); }
    bool done() const { return m_pDescIter->done(); }
    bool next() { return m_pDescIter->next(); }
    OdRxObjectPtr object() const { return m_pOwner->getAt(id()); }
  };
  OdRxDictionaryPtr createPropMap() const
  {
    OdRxDictionaryPtr pInfo;
    pInfo = ::odrxCreateRxDictionary();
    generatePropMap(pInfo);
    return pInfo;
  }

  virtual OdRxDictionary* propertiesInfo() const = 0;
  virtual void generatePropMap(OdRxDictionary*) const = 0;

  inline PropDesc* descAt(OdUInt32 id) const
  { return (PropDesc*)propertiesInfo()->getAt(id).get(); }
public:
  OdRxObjectPtr getAt(const OdString& key) const
  { return OdRxDispatchImpl::getAt(idAt(key)); }

  OdRxObjectPtr putAt(const OdString& key, OdRxObject* pObject, OdUInt32* pId = 0)
  {
    OdUInt32 id = idAt(key);
    if (pId)
      *pId = id;
    return OdRxDispatchImpl::putAt(id, pObject); 
  }

  OdRxObjectPtr getAt(OdUInt32 id) const
  { 
    PropDesc* pd = descAt(id);
    if (!pd)
      throw OdError(eInvalidInput);
    return pd->prop_get((TBase*)this); 
  }

  OdRxObjectPtr putAt(OdUInt32 id, OdRxObject* pObject)
  {
    if(id < numEntries())
    {
      PropDesc* pDesc = descAt(id);
      OdRxObjectPtr pRes = pDesc->prop_get((TBase*)this);
      pDesc->prop_put((TBase*)this, pObject);
      return pRes;
    }
    throw OdError(eInvalidInput);
  }

  bool has(const OdString& entryName) const { return propertiesInfo()->has(entryName); }
  bool has(OdUInt32 id) const { return propertiesInfo()->has(id); }
  OdUInt32 idAt(const OdString& key) const { return propertiesInfo()->idAt(key); }
  OdString keyAt(OdUInt32 id) const { return propertiesInfo()->keyAt(id); }
  OdUInt32 numEntries() const { return propertiesInfo()->numEntries(); }
  bool isCaseSensitive() const { return propertiesInfo()->isCaseSensitive(); }

  OdRxDictionaryIteratorPtr newIterator(OdRx::DictIterType type = OdRx::kDictCollated)
  {
    return Iterator::createObject(this, propertiesInfo()->newIterator(type));
  }

  // not used
  bool atKeyAndIdPut(const OdString& , OdUInt32 , OdRxObject* ) { 
          throw OdError(eNotApplicable); 
          return false; 
  }

  bool resetKey(OdUInt32 , const OdString& ) { 
          throw OdError(eNotApplicable); 
          return false; 
  }
  OdRxObjectPtr remove(const OdString& ) { 
          throw OdError(eNotApplicable); 
          return OdRxObjectPtr(); 
  }
  OdRxObjectPtr remove(OdUInt32 ) { 
          throw OdError(eNotApplicable); 
          return OdRxObjectPtr(); 
  }
};

#define ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(CLASS) \
  virtual void generatePropMap(OdRxDictionary*) const;\
  virtual OdRxDictionary* propertiesInfo() const

#define ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(CLASS) \
void CLASS::generatePropMap(OdRxDictionary* pInfo) const {

#if (defined(_MSC_VER) && (_MSC_VER > 1800)) || (defined(__cplusplus) && (__cplusplus > 199711L))

#define ODRX_END_DYNAMIC_PROPERTY_MAP(CLASS) }\
OdRxDictionary* CLASS::propertiesInfo() const\
{\
  static OdRxDictionaryPtr pInfo = createPropMap();\
  return pInfo.get();\
}

#else

#define ODRX_END_DYNAMIC_PROPERTY_MAP(CLASS) }\
static OdMutex _##CLASS##PropMapMutex;\
OdRxDictionary* CLASS::propertiesInfo() const\
{\
  TD_AUTOLOCK(_##CLASS##PropMapMutex);\
  static OdRxDictionaryPtr pInfo = createPropMap();\
  return pInfo.get();\
}

#endif

#define ODRX_INHERIT_PROPERTIES(BASE_CLASS) \
  BASE_CLASS::generatePropMap(pInfo);


#define ODRX_DECLARE_PROPERTY(PropName) \
  class _##PropName##_PropDesc : public OdRxObjectImpl<OdRxPropDesc>\
  {\
  public:\
    static OdRxObjectPtr createObject();\
    static inline  OdString _name();\
    OdString name() const;\
    OdRxObjectPtr prop_get(const void* pThis) const;\
    void prop_put(void* pThis, OdRxObject* pVal);\
  };

#define ODRX_DECLARE_PROPERTY2(PropName, SrcFileName) \
  class _##PropName##_##SrcFileName##_PropDesc : public OdRxObjectImpl<OdRxPropDesc>\
  {\
  public:\
    static OdRxObjectPtr createObject();\
    static inline  OdString _name();\
    OdString name() const;\
    OdRxObjectPtr prop_get(const void* pThis) const;\
    void prop_put(void* pThis, OdRxObject* pVal);\
  };

#define ODRX_DEFINE_PROPERTY_METHODS(PropName, PropHolder, getMethodName, putMethodName, accessFn) \
  OdRxObjectPtr _##PropName##_PropDesc::createObject()\
  {\
    return OdRxObjectPtr(new _##PropName##_PropDesc, kOdRxObjAttach);\
  }\
  inline OdString _##PropName##_PropDesc::_name()\
  {\
    static OdString sName(OD_T(#PropName));\
    return sName;\
  }\
  OdString _##PropName##_PropDesc::name() const \
  {\
    return _name();\
  }\
  OdRxObjectPtr _##PropName##_PropDesc::prop_get(const void* pThis) const\
  {\
    return (OdRxObject*)OdRxVariantValue((static_cast<PropHolder*>((OdRxDictionary*)pThis))->getMethodName());\
  }\
  void _##PropName##_PropDesc::prop_put(void* pThis, OdRxObject* pVal)\
  {\
    (static_cast<PropHolder*>((OdRxDictionary*)pThis))->putMethodName(OdRxVariantValue(pVal)->accessFn());\
  }

#define ODRX_DEFINE_PROPERTY_METHODS2(PropName, SrcFileName, PropHolder, getMethodName, putMethodName, accessFn) \
  OdRxObjectPtr _##PropName##_##SrcFileName##_PropDesc::createObject()\
  {\
    return OdRxObjectPtr(new _##PropName##_##SrcFileName##_PropDesc, kOdRxObjAttach);\
  }\
  inline OdString _##PropName##_##SrcFileName##_PropDesc::_name()\
  {\
    static OdString sName(OD_T(#PropName));\
    return sName;\
  }\
  OdString _##PropName##_##SrcFileName##_PropDesc::name() const \
  {\
    return _name();\
  }\
  OdRxObjectPtr _##PropName##_##SrcFileName##_PropDesc::prop_get(const void* pThis) const\
  {\
    return (OdRxObject*)OdRxVariantValue((static_cast<PropHolder*>((OdRxDictionary*)pThis))->getMethodName());\
  }\
  void _##PropName##_##SrcFileName##_PropDesc::prop_put(void* pThis, OdRxObject* pVal)\
  {\
    (static_cast<PropHolder*>((OdRxDictionary*)pThis))->putMethodName(OdRxVariantValue(pVal)->accessFn());\
  }

#define ODRX_DEFINE_PROPERTY_METHODS_PREFIX(ClassPrefix, PropName, PropHolder, getMethodName, putMethodName, accessFn) \
  OdRxObjectPtr ClassPrefix _##PropName##_PropDesc::createObject()\
  {\
    return OdRxObjectPtr(new _##PropName##_PropDesc, kOdRxObjAttach);\
  }\
  inline OdString ClassPrefix _##PropName##_PropDesc::_name()\
  {\
    static OdString sName(OD_T(#PropName));\
    return sName;\
  }\
  OdString ClassPrefix _##PropName##_PropDesc::name() const \
  {\
    return _name();\
  }\
  OdRxObjectPtr ClassPrefix _##PropName##_PropDesc::prop_get(const void* pThis) const\
  {\
    return (OdRxObject*)OdRxVariantValue((static_cast<PropHolder*>((OdRxDictionary*)pThis))->getMethodName());\
  }\
  void ClassPrefix _##PropName##_PropDesc::prop_put(void* pThis, OdRxObject* pVal)\
  {\
    (static_cast<PropHolder*>((OdRxDictionary*)pThis))->putMethodName(OdRxVariantValue(pVal)->accessFn());\
  }

#define ODRX_GENERATE_PROPERTY(PropName) \
  pInfo->putAt(_##PropName##_PropDesc::_name(), _##PropName##_PropDesc::createObject());

#define ODRX_GENERATE_PROPERTY2(PropName, SrcFileName) \
  pInfo->putAt(_##PropName##_##SrcFileName##_PropDesc::_name(), _##PropName##_##SrcFileName##_PropDesc::createObject());

#define ODRX_DEFINE_PROPERTY(PropName, PropHolder, accessFn) ODRX_DEFINE_PROPERTY_METHODS(PropName, PropHolder, get_##PropName, put_##PropName, accessFn)

#define ODRX_DEFINE_PROPERTY2(PropName, SrcFileName, PropHolder, accessFn) ODRX_DEFINE_PROPERTY_METHODS2(PropName, SrcFileName, PropHolder, get_##PropName, put_##PropName, accessFn)

#define ODRX_DEFINE_PROPERTY_PREFIX(ClassPrefix, PropName, PropHolder, accessFn) ODRX_DEFINE_PROPERTY_METHODS_PREFIX(ClassPrefix, PropName, PropHolder, get_##PropName, put_##PropName, accessFn)



#define ODRX_DEFINE_PROPERTY_OBJECT(PropName, PropHolder, getMethodName, putMethodName, ObjType) \
  OdRxObjectPtr _##PropName##_PropDesc::createObject()\
  {\
    return OdRxObjectPtr(new _##PropName##_PropDesc, kOdRxObjAttach);\
  }\
  OdString _##PropName##_PropDesc::_name()\
  {\
    static OdString sName(OD_T(#PropName));\
    return sName;\
  }\
  OdString _##PropName##_PropDesc::name() const \
  {\
    return _name();\
  }\
  OdRxObjectPtr _##PropName##_PropDesc::prop_get(const void* pThis) const\
  {\
    return static_cast<PropHolder*>((OdRxDictionary*)pThis)->getMethodName();\
  }\
  void _##PropName##_PropDesc::prop_put(void* pThis, OdRxObject* pVal)\
  {\
    static_cast<PropHolder*>((OdRxDictionary*)pThis)->putMethodName(OdSmartPtr<ObjType>(pVal));\
  }

#define ODRX_DEFINE_PROPERTY_OBJECT2(PropName, SrcFileName, PropHolder, getMethodName, putMethodName, ObjType) \
  OdRxObjectPtr _##PropName##_##SrcFileName##_PropDesc::createObject()\
  {\
    return OdRxObjectPtr(new _##PropName##_##SrcFileName##_PropDesc, kOdRxObjAttach);\
  }\
  OdString _##PropName##_##SrcFileName##_PropDesc::_name()\
  {\
    static OdString sName(OD_T(#PropName));\
    return sName;\
  }\
  OdString _##PropName##_##SrcFileName##_PropDesc::name() const \
  {\
    return _name();\
  }\
  OdRxObjectPtr _##PropName##_##SrcFileName##_PropDesc::prop_get(const void* pThis) const\
  {\
    return static_cast<PropHolder*>((OdRxDictionary*)pThis)->getMethodName();\
  }\
  void _##PropName##_##SrcFileName##_PropDesc::prop_put(void* pThis, OdRxObject* pVal)\
  {\
    static_cast<PropHolder*>((OdRxDictionary*)pThis)->putMethodName(OdSmartPtr<ObjType>(pVal));\
  }

#define ODRX_DEFINE_PROPERTY_OBJECT_PREFIX(ClassPrefix, PropName, PropHolder, getMethodName, putMethodName, ObjType) \
  OdRxObjectPtr ClassPrefix _##PropName##_PropDesc::createObject()\
  {\
    return OdRxObjectPtr(new _##PropName##_PropDesc, kOdRxObjAttach);\
  }\
  OdString ClassPrefix _##PropName##_PropDesc::_name()\
  {\
    static OdString sName(OD_T(#PropName));\
    return sName;\
  }\
  OdString ClassPrefix _##PropName##_PropDesc::name() const \
  {\
    return _name();\
  }\
  OdRxObjectPtr ClassPrefix _##PropName##_PropDesc::prop_get(const void* pThis) const\
  {\
    return static_cast<PropHolder*>((OdRxDictionary*)pThis)->getMethodName();\
  }\
  void ClassPrefix _##PropName##_PropDesc::prop_put(void* pThis, OdRxObject* pVal)\
  {\
    static_cast<PropHolder*>((OdRxDictionary*)pThis)->putMethodName(OdSmartPtr<ObjType>(pVal));\
  }


//wrapper to use non-Rx classes as an object passed through the properties
template <class Type>
class OdRxWrapper : public OdRxObject, public Type
{

};
template <class Type>
class OdRxWrapperValue : public OdSmartPtr<OdRxWrapper<Type> >
{
public:

  OdRxWrapperValue (const OdRxObjectPtr& pObject)
    :OdSmartPtr<OdRxWrapper<Type> >(pObject)
  {
  }

  OdRxWrapperValue(const Type& val)
  {
    OdSmartPtr<OdRxWrapper<Type> >::operator=(OdRxObjectImpl<OdRxWrapper<Type> >::createObject());
    *((Type*)OdSmartPtr<OdRxWrapper<Type> >::get()) = val;
  }
  operator const Type&() const 
  { 
    return *((Type*)OdSmartPtr<OdRxWrapper<Type> >::get());
  }
};

template<class T>
OdRxWrapperValue<T> createRxWrapper(const T& val)
{
  return OdRxWrapperValue<T>(val);
}

#include "TD_PackPop.h"

#endif // __PROPERTIES_H_INCLUDED_

