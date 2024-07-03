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
#ifndef _ODTFSCHEMAMANAGERN_H_INCLUDED_
#define _ODTFSCHEMAMANAGERN_H_INCLUDED_


#include "OdaCommon.h"
#include "OdPlatformStreamer.h"
#include "OdaDefs.h"
#include "Tf.h"

#include "FlatMemStream.h"
#include "../../ThirdParty/tinyxml/tinyxml.h"

#define STL_USING_SET
#include "OdaSTL.h"
#include "DbHostAppServices.h"
#include "RxDynamicModule.h"

class OdTfBinarySchemaIteratorImpl;

/** \details
This class represents working with XML schemas for revision control.
*/
class TFDLL_EXPORT OdTfSchemaManager : public OdTfSchemaManagerInterface
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdTfSchemaManager);
  OdTfSchemaManager() : m_appServices(NULL) {};
  //DOM-IGNORE-END

  /** \details
    Destructor for objects of the OdTfSchemaManager class. Frees allocated resources.
  */
  virtual ~OdTfSchemaManager() {};

  /** \details
  Tries to register the XML or binary schema.
  \param schemeName [in] The XML or binary schema name.
  \returns The true value if the schema is registered, or false if the schema was registered earlier.
  \remarks
  The name of the schema must have a type .tsbf or .txds.
  */
  bool registerSchema(const OdString& schemeName);
  /** \details
  Tries to register the XML or binary schema.
  \param schemaName [in] The XML or binary schema name.
  \param fileType [in] Type of the file. Refer to the OdTf::SaveType enumerated type for the available file types.
  \returns The true value if the schema is registered, or false if the schema was registered earlier.
  */
  virtual bool registerSchema(const OdString& schemaName, OdTf::SaveType fileType);
  /** \details
  Converts an XML schema to a binary schema.
  \param schemeName [in] The XML schema name.
  \remarks 
  The binary schema is saved in the same folder as the XML one, but with the file type .tsbf.
  */
  virtual void convertSchema(const OdString& schemeName);
  /** \details
  Sets HostAppServices to be used by OdTfSchemaManager.
  \param pHostAppServices [in] Pointer to OdDbHostAppServices.
  \remarks
  The method setAppServices() is used in ::odTfInitialize(pHostApp);.
  */
  void setAppServices(OdDbHostAppServices* pHostAppServices);
  /** \details
  Unloads a registered schema.
  \param schemeName [in] Schema name.
  */
  void unloadSchema(const OdString& schemeName);
  /** \details
  Gets an array of registered schema names.
  \param setNames [out] Array of schema names.
  */
  void getNamesRegisteredSchemes(OdStringArray& setNames);
protected:
  void mergeSchema(const OdString& schemeName);
  void mergeSchemaBin(const OdString& schemeName);

  OdDbHostAppServices* m_appServices;
};

typedef OdSmartPtr<OdTfSchemaManager> OdTfSchemaManagerPtr;

/** \details
Registers a basic (core) schema.
\param pAppServices [in] OdDbHostAppServices.
\remarks 
Parameter pAppServices cannot be NULL.
*/
TFDLL_EXPORT bool odTfInitialize(OdDbHostAppServices* pAppServices);

/** \details
Tries to register the schema.
\param schemeName [in] Schema name. Avoid repeated registeration of a schema.
\returns The true value if the schema is registered, or false if the schema was registered earlier.
*/
TFDLL_EXPORT bool odrxRegisterSchema(const OdString& schemeName);

/** \details
Converts an XML schema to a binary schema.
\param schemeName [in] The XML schema name.
\remarks
The binary schema is saved in the same folder as the XML schema, but with the file type .tsbf.
*/
TFDLL_EXPORT void odrxConvertSchema(const OdString& schemeName);


#endif //_ODTFSCHEMAMANAGERN_H_INCLUDED_
