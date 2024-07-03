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


#ifndef _OdDbTraceStorage_h_Included_
#define _OdDbTraceStorage_h_Included_

#include "TD_PackPush.h"
#include "RxDefs.h"
#include "DbObject.h"
#include "StringArray.h"
#include "OdPlatformSettings.h"
#include "DbDictionary.h"
#include "DbDatabase.h"

class OdDbTraceStore;
/** \details
  The typified smart pointer for the trace store object. This template class
  is specialization of the OdSmartPtr class for the OdDbTraceStore class.

  \sa
  <link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdDbTraceStore> OdDbTraceStorePtr;

/** \details
    This class represents user profile information.
    Corresponding C++ library: AcTrace
	
	<group !!RECORDS_tdrawings_apiref>
*/
struct OdTraceUserProfile
{
  /** \details
    Builds an instance of the OdTraceUserProfile object.
  */
  OdTraceUserProfile() {};
  /** \details
    Builds an instance of the OdTraceUserProfile object.

  \param firstName [in] String containing the first name
  \param lastName  [in] String containing the last name
  \param userName  [in] String containing the user name
  \param oxygenId  [in [optional]] String containing the user unique hash code
 */
  OdTraceUserProfile(const OdString& firstName, const OdString& lastName, const OdString& userName, const OdString& oxygenId = OdString::kEmpty) :
    m_firstName(firstName), m_lastName(lastName), m_userName(userName), m_oxygenID(oxygenId) {};

  /** \details
    Checks whether at least one of the required fields is empty.

    \returns true if first name or last name or user name is empty, otherwise returns false.
  */
  bool isEmpty()
  {
    return m_firstName.isEmpty() || m_lastName.isEmpty() || m_userName.isEmpty();
  }

  /**String containing the first name.*/
  OdString m_firstName;
  /**String containing the last name.*/
  OdString m_lastName;
  /**String containing the user name.*/
  OdString m_userName;
  /**Optional. String containing the user unique hash code.*/
  OdString m_oxygenID;

  //DOM-IGNORE-BEGIN
  OdString m_avatar;
  OdString m_date;
  //DOM-IGNORE-END
};

/** \details
    This class represents trace information.
    Corresponding C++ library: AcTrace
	
	<group !!RECORDS_tdrawings_apiref>
*/
struct OdTraceUserInfo
{
  /**Instance of OdTraceUserProfile class with information about the user who created the trace.*/
  OdTraceUserProfile m_createdBy;
  /**Instance of OdTraceUserProfile class with information about the user who last saved the trace.*/
  OdTraceUserProfile m_lastSavedBy;
  /**String containing name of a trace dwg file.*/
  OdString           m_traceFile;
  /**String containing name of a trace.*/
  OdString           m_traceName;
  /**A string containing a unique trace ID.*/
  OdString           m_traceId;
};

/** \details
    This class represents trace data information storage.
    Corresponding C++ library: AcTrace
	
	<group OdDb_Classes>
*/
class OD_DLL_EXPORT OdDbTraceStore : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbTraceStore);

  /** \details
    Builds an instance of the OdDbTraceStore object.
  */
  OdDbTraceStore();

  /** \details
   Get information of a traces.

   \returns An array of OdTraceUserInfo objects. Each array object contains information about one trace.
 */
  OdArray<OdTraceUserInfo> getTraceUserInfo() const;


  virtual  OdResult dwgInFields(OdDbDwgFiler* pFiler) ODRX_OVERRIDE;
  virtual  void dwgOutFields(OdDbDwgFiler* pFiler) const ODRX_OVERRIDE;

  /** \details
   Get OdDbTraceStore instance stored in specified database.
   \param pDb         [in]  Specified database.
   \param pTraceStore [out] OdDbTraceStore object of a specified database.
   \param openMode    [in] Mode to open OdDbTraceStore in a specified database.

   \returns true if a specified database store a OdDbTraceStore object, otherwise returns false.
 */
  static bool openTraceStore(OdDbDatabase* pDb, OdDbTraceStorePtr& pTraceStore, OdDb::OpenMode openMode = OdDb::kForRead)
  {
    if(!pDb)
      return false;
    OdDbObjectId dicId = pDb->getNamedObjectsDictionaryId();
    OdDbDictionaryPtr pDir = dicId.openObject();
    OdDbObjectId id = pDir->getAt(L"ACAD_TRACESTORE");
    if (id.isNull())
      return false;
    pTraceStore = id.openObject(openMode);
    return true;
  }
};




#include "TD_PackPop.h"

#endif
