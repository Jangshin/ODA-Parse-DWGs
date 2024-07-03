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


#ifndef _INC_DDBRBREPSHELLTRAVERSER_3F83F556035B_INCLUDED
#define _INC_DDBRBREPSHELLTRAVERSER_3F83F556035B_INCLUDED
#include "Br/BrBrep.h"
#include "Br/BrShell.h"


#include "Br/BrTraverser.h"

#include "TD_PackPush.h"


/** \details
    This class is the interface class for BREP shell traversers.
    
    \sa
    TD_Br

    <group OdBr_Classes>
*/
class ODBR_TOOLKIT_EXPORT OdBrBrepShellTraverser : public OdBrTraverser
{
public:
  OdBrBrepShellTraverser();
#ifdef OD_ADD_MOVE_CTOR_HAVE_DEF_DEL_FUNC
  //DOM-IGNORE-BEGIN
  OdBrBrepShellTraverser(const OdBrBrepShellTraverser&) = default;
  OdBrBrepShellTraverser& operator=(const OdBrBrepShellTraverser&) = default;
  OdBrBrepShellTraverser(OdBrBrepShellTraverser&&) = default;
  OdBrBrepShellTraverser& operator=(OdBrBrepShellTraverser&&) = default;
  //DOM-IGNORE-END
#endif

  /** \details
    Sets this Traverser object to a specific BREP shell list.
    \param brep [in]  Owner of the shell list.
    
    \remarks
    This Traverser object is set to the first element in the list.

    Returns odbrOK if successful, or an appropriate error code if not.
  */
  OdBrErrorStatus setBrep(const OdBrBrep& brep);

  /** \details
    Sets this Traverser object to a specific BREP shell list
    and starting position.
    \param shell [in]  Defines the shell list and starting position.
  */
  OdBrErrorStatus setBrepAndShell(const OdBrShell& shell);

  /** \details
    Sets the starting position of this Traverser object.
    \param shell [in]  Defines the starting position.
  */
  OdBrErrorStatus setShell(const OdBrShell& shell);

  /** \details
    Returns the shell object at the current Traverser position.
  */
  OdBrShell getShell() const;
  /** \details
    Returns the owner of the shell list associated with this Traverser object.
  */
  OdBrBrep getBrep() const;
};

#include "TD_PackPop.h"

#endif /* _INC_DDBRBREPSHELLTRAVERSER_3F83F556035B_INCLUDED */

