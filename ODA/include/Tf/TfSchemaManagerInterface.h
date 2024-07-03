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


#ifndef _OD_TF_SCHEMAMANAGERNTERFACE_Included_
#define _OD_TF_SCHEMAMANAGERNTERFACE_Included_


#include "TD_PackPush.h"

/** \details
  Provides an enumeration for working with save types.
*/
namespace OdTf
{
  /** \details
    Defines save types for schema files.
  */
  enum SaveType
  {
    /** The XML schema file type. */
    kTxds = 0,
    /** The binary schema file type. */
    kTsbf = 1
  };
}

/** \details
  Represents the interface for the Schema Manager.
*/
class OdTfSchemaManagerInterface : public OdRxObject
{
public:
  /** \details
  Tries to register the XML or binary schema.
  \param schemeName [in] The XML or binary schema name.
  \returns The true value if the schema is registered, or false if the schema was registered earlier.
  \remarks
  The name of the schema must have a type .tsbf or .txds.
  */
  virtual bool registerSchema(const OdString& schemeName) = 0;
  
  /** \details
  Tries to register the XML or binary schema.
  \param schemeName [in] The XML or binary schema name.
  \param fileType [in] Type of the file. Refer to the OdTf::SaveType enumerated type for the available file types.
  \returns The true value if the schema is registered, or false if the schema was registered earlier.
  */
  virtual bool registerSchema(const OdString& schemaName, OdTf::SaveType fileType) = 0;
  
  /** \details
  Converts an XML schema to the binary format.
  \param schemeName [in] The XML schema name.
  \remarks
  The binary schema is saved with the file type .tsbf in the same folder as the XML schema.
  */
  virtual void convertSchema(const OdString& schemeName) = 0;
  
  /** \details
  Unloads a registered schema.
  \param schemeName [in] The schema name.
  */
  virtual void unloadSchema(const OdString& schemeName) = 0;

  /** \details
    Creates a new instance of a Schema Manager interface with default parameters.
  */
  OdTfSchemaManagerInterface() {};
  
  /** \details
    Destructor for objects of the OdTfSchemaManagerInterface class. Frees allocated resources.
  */
  virtual ~OdTfSchemaManagerInterface() {};
};

#include "TD_PackPop.h"

#endif // _OD_TF_SCHEMAMANAGERNTERFACE_Included_
