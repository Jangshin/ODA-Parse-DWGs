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

#ifndef __ODGISELECTPROCBASE__
#define __ODGISELECTPROCBASE__

#include "Gi/GiConveyorNode.h"
#include "Ge/GeDoubleArray.h"

class OdGiDeviation;
class OdGiConveyorContext;

#include "TD_PackPush.h"

/** \details
  Base class for conveyor nodes which implements selection processes.

  <group OdGi_Classes>
*/
class ODGI_EXPORT OdGiSelectProcBase : public OdGiConveyorNode
{
public:
  /** \details
    Type of change, used as input argument for check_n_fire_selected method. 
  */
  enum
  {
    kCheckMarkerOnChange         = 1, // Selection marker changed
    kCheckMarkerOnViewModeChange = 2, // View mode changed

    kCheckMarkerFinish           = 0x80000000 // Selection finished
  };
  /** \details
    Type of geometry processible by this selection process node implementation.
  */
  enum
  {
    kSupportPointsPrim    = 1, // Support point primitives (degenerate polylines)
    kSupportLinesPrim     = 2, // Support line primitives
    kSupportTrianglesPrim = 4, // Support triangles/polygons/shells and meshes (filled geometry)
    kSupportAllPrims      = kSupportPointsPrim | kSupportLinesPrim | kSupportTrianglesPrim // Support all geometry primitives
  };
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdGiSelectProcBase);
  //DOM-IGNORE-END

  /** \details
    This method can be called externally for separating selection process between different objects.
    \param flags [in]  Set of flags, listed in unnamed enumeration declared in this class.
  */
  virtual void check_n_fire_selected(OdUInt32 flags = 0) = 0;

  /** \details
    This method can be called externally to switch between sectionable and non-sectionable geometry.
    \param bEnable [in]  Flag to enable or disable geometry sectioning.
  */
  virtual void switchSectioning(bool /*bEnable*/) { }

  /** \details
    Checks that selection can be performed by checking extents without playing content.
    \param extWc [in] Data extents.
    \returns True if content should be selected without playing; otherwise
    returns false.
  */
  virtual bool handleSelectionByExtents( const OdGeExtents3d& extWc ) { return false; }

  /** \details
    Checks which kind of geometry primitives supported by this selection process.
    \returns Set of bit flags indicating which kind of geometry primitives supported by this selection process.
  */
  virtual OdUInt32 supportGeometryPrimitives() const { return kSupportAllPrims; }

  /** \details
    Sets max deviation for curve tessellation.

    \param deviations [in]  Array with deviation values.
  */
  virtual void setDeviation(const OdGeDoubleArray& deviations) = 0;

  /** \details
    Sets deviation object to obtain max deviation for curve tessellation.
  
    \param pDeviation [in]  Pointer to the deviation object.
  */
  virtual void setDeviation(const OdGiDeviation* pDeviation) = 0;

  /** \details
    Sets the draw context object (to access to traits, etc).

    \param pDrawCtx [in]  Pointer to the draw context.
  */
  virtual void setDrawContext(OdGiConveyorContext* pDrawCtx) = 0;
};

/** \details
  A data type that represents a smart pointer to an
  <link OdGiSelectProcBase, OdGiSelectProcBase> object.
*/
typedef OdSmartPtr<OdGiSelectProcBase> OdGiSelectProcBasePtr;

#include "TD_PackPop.h"

#endif //#ifndef __ODGISELECTPROCBASE__
