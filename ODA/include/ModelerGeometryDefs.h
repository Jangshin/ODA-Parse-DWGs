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

#ifndef _MODELERGEOMETRYDEFS_INCLUDED_
#define _MODELERGEOMETRYDEFS_INCLUDED_

#include "BoolArray.h"

class OdGeCurve3d;

/**
  <group !!RECORDS_tdrawings_apiref>
*/
namespace OdEdgeTypeFlags {
/** \details
  Represents the visibility of edges.
*/
enum Enum {

  /** Turns visibility of tangent edges on or off. Tangent edges mark the transition between a flat surface and a rounded edge, most commonly seen as filleted edges. */
  kTangent = 1L,

  /** Shortens the length of tangential edges to differentiate them from visible edges. This is available only if Tangent Edges is selected. */
  kTangentShortend = 2L,
  
  /** Turns visibility of interference edges on or off. */
  kInterference = 4L,
  
  /** Turns visibility of sheet metal bend extent lines on or off.
  Not implemented yet */
  kBend = 8L,

  /** Turns visibility of thread lines on screws and tapped holes on or off.
  Not implemented yet */
  kThread = 16L,

  /** Turns visibility of presentation trails on or off.
  Not implemented yet */
  kPresentation = 32L,

  /** Turns visibility of outer boundary edges produced by detail view section
  Not implemented yet */
  kOuterBoundary = 64L,

  /** Turns on usual visibility of edges. Other types are off. */
  kRegular = 0,
};
}


/** \details
  Represents the edge interval in parameter space.
*/
struct OdLineSegInterval {
  double startParam, endParam;
};

typedef OdArray<OdLineSegInterval, OdMemoryAllocator<OdLineSegInterval> > OdLineSegIntervalArray;


/** \details
  Represents HlrEdge Visitor.
  
  <group Other_Classes>
*/
class OdEdgeHLREdgeVisitor {
public:

  /** \details
    Receives an edge and associates information about its visibility.

    \param bodyIndex [out] Index of a body that the edge belongs to.
    \param edgeTag [out] The tag of the edge in a body.
    \param edgeType [out] Type of the edge.
    \param edge [in] Edge represented by a curve.
    \param segmenParameters [in] Array of visible/hidden edge segments.
    \param visibilities [in] Array of every segment status (true - visible, false - hidden).
  */
  virtual void edge(
    OdInt32 bodyIndex,
    OdInt32 edgeTag,
    OdEdgeTypeFlags::Enum edgeType,
    const OdGeCurve3d& edge,
    const OdLineSegIntervalArray& segmenParameters,
    const OdBoolArray& visibilities) = 0;
};



#endif //_MODELERGEOMETRYDEFS_INCLUDED_
