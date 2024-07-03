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

#if _MSC_VER > 1000         // remove "PCH warning: cannot find a suitable header stop location"
#pragma once
#endif // _MSC_VER > 1000


#ifndef _OD_PDF_VERSION_INCLUDED_
#define _OD_PDF_VERSION_INCLUDED_

/** \details 
  The namespace contains declarations related to working with PDF format.

  <group TD_Namespaces>
*/
namespace OdPDF
{

  /** \details
	PDF format versions enumeration, used during the export process.
  */
  enum PDFFormatVersions
  {
    /** PDF format version is set by the corresponding module.*/
    kPDFAuto = 0,
    /** PDF format version 1.0.*/
    kPDFv1_0 = 10,
    /** PDF format version 1.1.*/
    kPDFv1_1 = 11,
    /** PDF format version 1.2.*/
    kPDFv1_2 = 12,
    /** PDF format version 1.3.*/
    kPDFv1_3 = 13,
    /** PDF format version 1.4.*/
    kPDFv1_4 = 14,
    /** PDF format version 1.5.*/
    kPDFv1_5 = 15,
    /** PDF format version 1.6.*/
    kPDFv1_6 = 16,
    /** PDF format version 1.7.*/
    kPDFv1_7 = 17,
    /** PDF format version 2.0.*/
    kPDFv2_0 = 20,
    /** The latest PDF format version supported by the PDF export functionality.*/
    kLast    = kPDFv2_0,

  };

}

#endif //_OD_PDF_VERSION_INCLUDED_
