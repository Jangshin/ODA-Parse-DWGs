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


#ifndef _ODTraceRuntime_h_Included_
#define _ODTraceRuntime_h_Included_

#include "TD_PackPush.h"
#include "RxDefs.h"
#include "DbDatabase.h"
#include "TraceStorage/DbTraceStore.h"

class OdDbTraceRuntimeObject;
class OdTraceRuntime;
typedef OdDbDate(*OdTraceDateFunc)();

/** \details
    This function is used to define a custom implementation of getting the current time.
    Corresponding C++ library: AcTrace
   \param traceDateFunc [in]  Pointer to a function that returns the current date and time.
   \returns Previous registered function. Null if there is no function registered.
*/
OdTraceDateFunc OD_DLL_EXPORT odSetTraceDateFunc(OdTraceDateFunc traceDateFunc);

/** \details
    This class represents information about the collaborator user.
    This class is intended to be used with methods from OdTraceRuntime class.
    Corresponding C++ library: AcTrace
	
	<group !!RECORDS_tdrawings_apiref>
*/
struct OdTraceCollaborator
{
private:
  /**String containing the first name.*/
  OdString m_firstName;
  /**String containing the last name.*/
  OdString m_lastName;
  /**String containing the user name.*/
  OdString m_userName;
  //DOM-IGNORE-BEGIN
  OdString m_traceFile;//internal use
  OdString m_oxygenID; //internal use. String containing the user unique hash code
  //DOM-IGNORE-END
  /**A enum variable indicating whether this collaborator's changes are shown in the trace.*/
  OdDb::Visibility m_visibility = OdDb::kVisible;

  //DOM-IGNORE-BEGIN
  OdTraceCollaborator() = delete;
  OdTraceCollaborator(const OdString& firstName, const OdString& lastName, const OdString& userName, const OdString& traceFile, const OdString oxygenID, const OdDb::Visibility visibility)
    : m_firstName(firstName), m_lastName(lastName), m_userName(userName), m_traceFile(traceFile), m_oxygenID(oxygenID), m_visibility(visibility) {}
  //DOM-IGNORE-END
public:
  /** \details
   Sets whether to show this collaborator's changes in the trace.

   \param visibility [in]  set kVisible to shown this collaborator changes in the trace, otherwise set kInvisible.
   \remark OdTraceRuntime::showOpenTraceCollaborators(OdArray<OdTraceCollaborator>) is used to display changes, 
   in which in dependence of this flag will turn on / off the display of changes of collaborators
 */
  void     setVisible(const OdDb::Visibility visibility){ m_visibility = visibility; }

  /** \details
   Returns A enum value indicating whether this collaborator's changes are reflected in traces.

   \returns kVisible if collaborator's changes are reflected in traces, otherwise return kInvisible.
 */
  OdDb::Visibility isVisible()    const { return m_visibility; }

  /** \details
   Returns A string contains a first name of collaborator.

   \returns A string contains a first name of collaborator.
 */
  OdString getFirstName() const { return m_firstName; }

  /** \details
   Returns a string contains a last name of collaborator.

   \returns A string contains a last name of collaborator.
 */
  OdString getLastName()  const { return m_lastName;  }

  /** \details
   Returns A string contains a user name of collaborator.

   \returns A string contains a user name of collaborator.
 */
  OdString getUserName()  const { return m_userName;  }

  /** \details
   Returns A string contains a trace file name of collaborator.

   \returns A string contains a trace file name of collaborator.
 */
  OdString getTraceFile()  const { return m_traceFile; }

  /** \details
   Returns A string contains a user unique hash code.

   \returns A string contains a user unique hash code.
 */
  OdString getOxygenId()   const { return m_oxygenID; }

  //DOM-IGNORE-BEGIN
  friend class OdDbTraceRuntimeObject;
  //DOM-IGNORE-END
};

/** \details
    This class is designed to work with tracing.
    Corresponding C++ library: AcTrace
	
	<group Other_Classes>
*/
class OD_DLL_EXPORT OdTraceRuntime
{
public:
  /** \details
   Adds the specified .dwg file to the current database as a trace.

   \param sPath2DwgFileAsTrace [in]      A string containing the path to the dwg file.
   \param traceName            [in/out]  String with the name which will given to the trace. If the name is not unique, traceName will be changed.
   \returns * eOk             if dwg file added as trace successful. 
            * eNoFileName     if the argument sPath2DwgFileAsTrace is empty.
            * eFileAccessErr  if the file sPath2DwgFileAsTrace is not available.
            * eInvalidContext if OdDbTraceStore in the current database is not available.
            * eCantOpenFile   if can't create temporary zip file in temporary folder.
            * eAlreadyActive  if some trace is open.
 */
   OdResult appendDwgAsTrace(const OdString& sPath2DwgFileAsTrace, OdString& traceName);

   /** \details
   Adds the specified .dwg file to the current database as a trace.

   \param sPath2DwgFileAsTrace [in]      A dwg database.
   \param traceName            [in/out]  String with the name which will given to the trace. If the name is not unique, traceName will be changed.
   \returns * eOk             if dwg file added as trace successful. 
            * eNoFileName     if the argument sPath2DwgFileAsTrace is empty.
            * eFileAccessErr  if the file sPath2DwgFileAsTrace is not available.
            * eInvalidContext if OdDbTraceStore in the current database is not available.
            * eCantOpenFile   if can't create temporary zip file in temporary folder.
            * eAlreadyActive  if some trace is open.
 */
   OdResult appendDwgAsTrace(OdDbDatabase* pDbTrace, OdString& traceName);

  /** \details
   Creates a new trace and open it to edit.

   \returns * eOk              if a trace opened successfully.
            * eAlreadyActive   if some trace is already open.
            * eMustBeNonZero   if user data is empty.
            * eNoInternalSpace if cannot add a trace paper.

   \remarks Sets value '2' to the database system variable TRACEMODE.
 */
  OdResult newTrace();

   /** \details
   Opens the specified trace.

   \param traceInfo [in]      Trace information to open.
  
   \returns * eOk                  if a trace open successful.
            * eAlreadyActive       if some trace already open.
            * eNoFileName          if the trace file is not found.
            * eInvalidContext      if OdDbTraceStore in the current database is not available.
            * eNoInternalSpace     if cannot add a trace paper.
            * eProfileDoesNotExist if user info is not set.
            * eNoLayout            if no layout is found for this trace.

   \remarks Sets value '2' to the database system variable TRACEMODE
 */
   OdResult openTrace(const OdTraceUserInfo& traceInfo);

   /** \details
   Renames the specified trace.

   \param traceInfo    [in]      Trace information to rename.
   \param newTraceName [in]      New trace name.

   \returns * eOk                  if a trace renaming is successful.
            * eNoFileName          if the trace file is not found.
            * eInvalidContext      if OdDbTraceStore in the current database is not available.
 */
   OdResult renameTrace(const OdTraceUserInfo& trace, const OdString& newTraceName);

   /** \details
   Deletes the specified trace.

   \param traceInfo [in]      Trace information to remove.

   \returns * eOk              if a trace is deleted successfully.
            * eNoFileName      if the trace file is not found.
            * eInvalidContext  if OdDbTraceStore in the current database is not available.

   \remarks If trace to delete is open the trace mode will be closed.
 */
   OdResult removeTrace(const OdTraceUserInfo& traceInfo);

       /** \details
    Deletes the specified sub trace.

    \param traceInfo [in]      Trace information in which subtrace needs to be removed.
    \param subTrace  [in]      SubTrace to remove.

    \returns * eOk                        if a subtrace is deleted successfully.
             * eNoFileName                if the trace file is not found.
             * eInvalidContext            if OdDbTraceStore in the current database is not available.
             * eUnableToRemoveAssociation if subTrace.m_traceFile == traceInfo.m_traceFile

    \remarks If trace to delete is open the trace mode will be closed.
             The main trace cannot be removed.
    */
   OdResult removeSubTrace(const OdTraceUserInfo& traceInfo, const OdTraceCollaborator& subTrace);

   /** \details
      Closes currently open trace. All changes in trace will be saved.

      \returns * eOk               if trace closed successful.
               * eAlreadyInactive  if no open trace.
               * eNotInDatabase    if this OdTraceRuntime does not have a reference to dwg database.
               * eCantOpenFile     if can't create temporary zip file in temporary folder.

      \remarks Sets value '0' to the database system variable TRACEMODE
   */
   OdResult closeTrace();

   /** \details
      Saturation is given to tracing, and fading to the main drawing. Trace editing enabled.
      Editing the main drawing disabled.

      \returns * eOk               if traceFront is executed successfully.
               * eAlreadyInactive  if no open trace.
               * eNotInDatabase    if this OdTraceRuntime does not have a reference to dwg database.
               * eLongTransReferenceError     if can't start editing a trace.

      \remarks Sets value '2' to the database system variable TRACEMODE
   */
   OdResult traceFront() const;

   /** \details
      Saturation is given to main drawing, and fading to the tracing. Trace view enabled.
      Editing the main drawing enabled.

      \returns * eOk               if traceBack executed successful.
               * eAlreadyInactive  if no open trace.
               * eNotInDatabase    if this OdTraceRuntime does not have a reference to dwg database.
               * eLongTransReferenceError     if can't end editing a trace.

      \remarks Sets value '1' to the database system variable TRACEMODE
   */
   OdResult traceBack() const;

   /** \details
      Gets trace collaborators of currently open trace.

      \param traceCollaborators [out] Array of OdTraceCollaborator objects.

      \returns * eOk                 if new user information was set correctly.
               * eAlreadyInactive    if no open trace.
   */
   OdResult getOpenTraceCollaborators(OdArray<OdTraceCollaborator>& traceCollaborators) const;

   /** \details
      Gets trace collaborators of the specified trace.

      \param trace              [in]  Information about trace.
      \param traceCollaborators [out] Array of OdTraceUserProfile objects.

      \returns * eOk                 if new user information was set correctly.
               * eInvalidInput       if traceId from input argument 'trace' is empty.
               * eInvalidContext     if OdDbTraceStore in the current database is not available.
               * eKeyNotFound        if no trace was found with the specified data from the input argument 'trace'

   */
   OdResult getTraceCollaborators(const OdTraceUserInfo& trace, OdArray<OdTraceCollaborator>& traceCollaborators) const;

   /** \details
      Display/hide trace collaborator changes.

      \param traceCollaborators [in] Array of OdTraceUserProfile objects.

      \returns * eOk                 if display collaborators are updated successfully.
               * eAlreadyInactive    if no open trace.
               * eInvalidContext     if count of elements in traceCollaborators array is not equal to trace colloborators in the open trace.
               * eInvalidInput       if at least one collaborator from the array traceCollaborators does not match any collaborator in the open trace.

      \remarks To display/hide trace collaborator changes need get information about trace collaborators
      by getOpenTraceCollaborators(OdArray<OdTraceCollaborator>&) or getTraceCollaborators(const OdTraceUserInfo, OdArray<OdTraceCollaborator>&).
      Change visible state in OdTraceCollaborator objects by the method setVisible(bool).
   */
   OdResult showOpenTraceCollaborators(const OdArray<OdTraceCollaborator>& traceCollaborators) const;

   /** \details
   Gets information of traces.
   Get an array of OdTraceUserInfo objects. Each array object contains information about one trace.

      \param userInfoArr        [in]  Information about traces.

      \returns * eOk                 if new user information was set correctly.
               * eInvalidContext     if OdDbTraceStore in the current database is not available.

      \remarks The same as OdDbTraceStore::getTracesUserInfo().
 */
   OdResult getTracesUserInfo(OdArray<OdTraceUserInfo>& userInfoArr) const;

   /** \details
     This method allows to known if the object belongs to the drawing or some trace.

     \param pSubject [in]  Pointer to object.

     \returns Return true if pSubject loaded from the trace.
  */
   bool isObjectFromTrace(const OdDbObject* pSubject) const;
public:
   /** \details
     Sets current user for working with traces.

     \param currentUserInfo [in] Information about user.

     \returns * eOk               if new user information was set correctly.
              * eAlreadyActive    if some trace is open.

     \remarks Can't set if some trace is open.
              The m_oxygenId in the OdTraceUserProfile can be empty for new users.
  */
   OdResult setCurrentUserInfo(const OdTraceUserProfile& currentUserInfo);

   /** \details
      Gets information about current user.

      \returns OdTraceUserProfile object with current user information.
   */
   OdTraceUserProfile getCurrentUserInfo() const;

   /** \details
      Gets extents of open trace.

       \returns * eOk                 if extents are retrieved successfully.
                * eAlreadyInactive    if no open trace.
                
       \remarks Returns invalid extents if trace doen't has an entities.
   */
   OdResult getOpenTraceExtents(OdGeExtents3d&) const;

   /** \details
   Gets a pointer to the OdTraceRuntime instance associated with the specified database.

   \param pDb               [in]            Pointer to dwg database.
   \param bCreateIfNotFound [in][optional]  Create an instance of OdTraceRuntime for the specified database if not it no exist.

   \returns Pointer to the OdTraceRuntime if it exists, otherwise nullptr.
   */
   static OdTraceRuntime* getInstance(OdDbDatabase* pDb, const bool bCreateIfNotFound = false);

   /** \details
    Only internal use.

   \returns OdDbObjectId to an OdDbTraceRuntimeObject.
   */
   OdDbObjectId getTraceRuntimeId() const;
   
   //DOM-IGNORE-BEGIN
   virtual  ~OdTraceRuntime();
   //DOM-IGNORE-END
protected:
  /** \details
   Builds an instance of the OdTraceRuntime object.

   \remarks
   Use the static OdTraceRuntime::getInstance(OdDbDatabase, bool) instead it.
 */
  OdTraceRuntime(OdDbDatabase*, const bool);

  /** \details
   Builds an instance of the OdTraceRuntime object.

   \remarks
   Use the static OdTraceRuntime::getInstance(OdDbDatabase, bool) instead it.
 */
  OdTraceRuntime() = delete;
  
  //DOM-IGNORE-BEGIN
  OdDbObjectId m_traceRuntimeId;

  //DOM-IGNORE-END
};

#include "TD_PackPop.h"

#endif 
