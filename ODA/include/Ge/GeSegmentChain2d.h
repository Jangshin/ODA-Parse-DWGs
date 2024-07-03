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

#ifndef OD_GE_SEGMENTCHAIN_2D_H
#define OD_GE_SEGMENTCHAIN_2D_H /*!DOM*/

#include "OdPlatform.h"
#include "Ge/GeSplineEnt2d.h"

#include "TD_PackPush.h"

/** \details
    This class represents piecewise linear splines in 2D space.

    Corresponding C++ library: TD_Ge

    <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeSegmentChain2d : public OdGeSplineEnt2d
{
public:
  GE_OPERATORS_OVERRIDE_2D(OdGeSegmentChain2d);
  
  /** \details 
    Default constructor for the OdGeSegmentChain2d class. Constructs a segment chain with no valid data.
  */
  OdGeSegmentChain2d();
  
  /** \details 
    Copy constructor for the OdGeSegmentChain2d class.
    
    \param source [in]  Object to be copied.
  */
  OdGeSegmentChain2d(
    const OdGeSegmentChain2d& source);
  
  /** \details 
    Constructor for the OdGeSegmentChain2d class.
    
    \param fitpoints [in]  Array of 2D fit points.
  */
  OdGeSegmentChain2d(
    const OdGePoint2dArray& fitpoints);
  
  /** \details 
    Constructor for the OdGeSegmentChain2d class.
    
    \param knots  [in]  Knot vector. A knot vector defines a sequence of parameter values that determine how the shape of chain segment is affected. The knot vector is a sequence of parameter values and divides the parametric space into intervals, usually called knot spans. Values of the knot vector must be provided in ascending order.
    \param points [in]  Array of 2D points.
  */
  OdGeSegmentChain2d(
    const OdGeKnotVector& knots,
    const OdGePoint2dArray& points);
  
  /** \details 
    Constructor for the OdGeSegmentChain2d class.
    
    \param crv  [in]  A 2D curve to be approximated as a polyline.
    \param approxEps [in]  Approximate geometric tolerance.
  */
  OdGeSegmentChain2d(
    const OdGeCurve2d& crv, 
    double approxEps);

  /** \details
    Assignment operator for the OdGeSegmentChain2d object.
    
    \param pline [in]  Segment chain to assign.
    
    \returns
    A reference to this segment chain.
  */
  OdGeSegmentChain2d& operator =(const OdGeSegmentChain2d& pline);

  //////////////////////////////////////////////////////////////////////////
  // overrides

  //////////////////////////////////////////////////////////////////////////
  // TD Special :

  /** \details
    Closes or opens this polyline.

    \param flag [in]  Boolean indicating if this polyline is to be closed.
  */
  OdGeSegmentChain2d& setClosed(
    bool flag);

  /** \details
    Returns a reference to the bulge vector for this polyline.

    \remarks
    The bulge is the tangent of 1/4 the included angle of the arc,
    measured counterclockwise.
  */
  OdGeDoubleArray& bulges();

  /** \details
    Returns the bulge vector for this polyline.

    \remarks
    The bulge is the tangent of 1/4 the included angle of the arc,
    measured counterclockwise.
  */
  const OdGeDoubleArray& getBulges() const;

  /** \details
    Returns a reference to the vertices for this polyline.
  */
  OdGePoint2dArray& vertices();

  /** \details
    Returns the vertices for this polyline.
  */
  const OdGePoint2dArray& getVertices() const;

  /** \details
    Returns true in and only if this polyline has at least one non-zero bulge.
  */
  bool hasBulges() const;



  /** \details
    Gets an approximate set of points for a curve. The specified number of points is the number of points that is received in a full circle for each arc from the curve. 
    Example: A curve has a straight line at intervals of 0.0-10.0, a circular arc at intervals of 10.0-13.14 (0.0-3.14), and a circular arc at intervals of 13.14-14.71 (0.0�1.57).
    If numSampleForEachArc is 100, 77 points are returned. 2 points for the line, 50 points for the first arc and 25 points for the second arc.

    \param numSampleForEachArc   [in]  Number of samples for each arc in the curve.
    \param pointArray            [out]  Receives an array of sample points.
  */
  void appendSamplePointsOptimal(
    int numSampleForEachArc,
    OdGePoint2dArray& pointArray) const;
};

#include "TD_PackPop.h"

#endif // OD_GE_SEGMENTCHAIN_2D_H
