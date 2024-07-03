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

#ifndef _DG_EXTRAELEMENTCUSTOMIZER_H_INCLUDED_
#define _DG_EXTRAELEMENTCUSTOMIZER_H_INCLUDED_

#include "RxObject.h"

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDgExtraElementCustomizationServices object pointers.
*/
class OdDgExtraElementCustomizationServices;
typedef OdSmartPtr<OdDgExtraElementCustomizationServices> OdDgExtraElementCustomizationServicesPtr;

/** \details
    This class allows to register user custom classes for extra dgn element ( type OdDgElement::kTypeExtraGraphicsElement
    and type OdDgElement::kTypeExtraNonGraphicsElement ) of specific extended element type ( see OdDgExtendedElementTypeXAttribute). 
    The custom element class must be inherited from base proxy class, that corresponded to extra dgn element of the extended type.
    (OdDgProxyElement, OdDgProxyGraphicsElement or OdDgComplexProxyElement classes )

    Corresponding C++ library: TD_Gi
    <group OdDg_Classes>
*/
class TG_EXPORT OdDgExtraElementCustomizationServices : public OdRxObject
{
  ODDG_DECLARE_MEMBERS(OdDgExtraElementCustomizationServices);

  public:

  virtual void registerExtraElementClass(OdUInt64 uType, OdRxClass* pClassDesc ) = 0;
  virtual void unregisterExtraElementClass(OdUInt64 uType ) = 0;
  virtual OdRxClass* getExtraElementClass(OdUInt64 uType ) const = 0;

  static OdDgExtraElementCustomizationServicesPtr getExtraElementCustomizationServices();
  static void					                            registerExtraElementCustomizationServices();
  static void					                            unregisterExtraElementCustomizationServices();
  static void					                            setupExtraElementClass(OdUInt64 uType, OdRxClass* pClassDesc);
  static void					                            removeExtraElementClass(OdUInt64 uType);
  static OdRxClass* 	                            getClass(OdUInt64 uType);
  static OdRxObjectPtr                            createExtraElement(OdUInt64 uType);
};

#endif //#ifndef _DG_EXTRAELEMENTCUSTOMIZER_H_INCLUDED_
