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
#ifndef _ODSPATIALREFERENCE_ODGRIDFILE_INCLUDED_
#define _ODSPATIALREFERENCE_ODGRIDFILE_INCLUDED_

#include "OdSpatialReference.h"

namespace OdSpatialReference
{
  class OdGridFileImpl;

  /** \details
    This class represents a grid file.

    <group OdSpatialReference_Classes>
  */
  class TD_SPATIALREFERENCE_API OdGridFile : public OdRxObject
  {
    ODSPREF_RX_WITH_IMPL_DECLARE_MEMBERS(OdGridFile);
  public:
    /** \details
      Returns the file name of this grid file.

      \param sFileName [out] File name.
    */
    void getFileName(OdString& sFileName) const;

    /** \details
      Sets the file name for this grid file.

      \param sFileName [in] File name.

      \returns Returns eOK if successful, or an appropriate error code if not.
    */
    OdResult setFileName(const OdString& sFileName);

    /** \details
      Returns the File format of this grid file.

      \returns Returns File format.
    */
    OdUInt8 getFileFormat() const;

    /** \details
      Sets the file format for this grid file.

      \param uFileFormat [in] File format.
    */
    void setFileFormat(OdUInt8 uFileFormat);

    /** \details
      Checks whether this grid file has inverse direction flag.

      \returns Returns Inverse direction flag.
    */
    bool isInverseDirection() const;
    
    /** \details
      Set inverse direction flag for this grid file.

      \param bIsInverseDirection [in] If true - set inverse direction flag.
    */
    void setInverseDirection(bool bIsInverseDirection);
  };
  typedef OdSmartPtr<OdGridFile> OdGridFilePtr;
  typedef OdArray<OdGridFilePtr> OdGridFileArray;
}

#endif //_ODSPATIALREFERENCE_ODGRIDFILE_INCLUDED_
