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


#ifndef _SpBBlock_h_Included_
#define _SpBBlock_h_Included_

#include "TD_PackPush.h"

#include "Ge/GeBoundBlock3d.h"

/** \details
  This class is an alternative of OdGeBoundBlock3d class for Spatial Index queries with optimized performance and improved precision.
  <group OdGs_Classes>
  
  \sa
  <link ge_OdGeBoundBlock3D, Working with Bounding Blocks>
*/
class OdSiBoundBlock3d
{
  protected:
    OdGePoint3d m_origin;
    OdGeVector3d m_basis[3];
    OdGeVector2d m_ivals[3];
    enum class BasisType { kWcs, kOrtho, kArbitrary } m_type;
  protected:
    void setWcsBasis(bool bNormalIval = true)
    { m_origin = OdGePoint3d::kOrigin;
      m_basis[0] = OdGeVector3d::kXAxis;
      m_basis[1] = OdGeVector3d::kYAxis;
      m_basis[2] = OdGeVector3d::kZAxis;
      if (bNormalIval)
        m_ivals[0] = m_ivals[1] = m_ivals[2].set(0.0, 1.0);
      m_type = BasisType::kWcs;
    }
    void setGeExtents(const OdGeExtents3d &ab)
    {
      setWcsBasis(false);
      m_ivals[0].set(ab.minPoint().x, ab.maxPoint().x);
      m_ivals[1].set(ab.minPoint().y, ab.maxPoint().y);
      m_ivals[2].set(ab.minPoint().z, ab.maxPoint().z);
    }
    void setGeBoundBlock(const OdGeBoundBlock3d &bb)
    {
      if (bb.isBox())
        setGeExtents(OdGeExtents3d(bb.minPoint(), bb.maxPoint()));
      else
      {
        bb.get(m_origin, m_basis[0], m_basis[1], m_basis[2]);
        m_ivals[0].set(0.0, m_basis[0].normalizeGetLength());
        m_ivals[1].set(0.0, m_basis[1].normalizeGetLength());
        m_ivals[2].set(0.0, m_basis[2].normalizeGetLength());
        subClassifyArbitrary();
      }
    }
    void setUnclassified(const OdGePoint3d &origin, const OdGeVector3d &xAxis, const OdGeVector3d &yAxis, const OdGeVector3d &zAxis)
    { m_origin = origin; m_basis[0] = xAxis; m_basis[1] = yAxis; m_basis[2] = zAxis;
      m_ivals[0].set(0.0, m_basis[0].normalizeGetLength());
      m_ivals[1].set(0.0, m_basis[1].normalizeGetLength());
      m_ivals[2].set(0.0, m_basis[2].normalizeGetLength());
      classify();
    }
    void classify();
    void subClassifyArbitrary()
    {
      m_type = (OdZero(m_basis[0].dotProduct(m_basis[1])) && OdZero(m_basis[0].dotProduct(m_basis[2])) &&
                OdZero(m_basis[1].dotProduct(m_basis[2]))) ? BasisType::kOrtho : BasisType::kArbitrary;
    }
    void getInternalArbitraryBasis(OdGePoint3d &minPoint, OdGePoint3d &maxPoint,
                                   OdGeVector3d &xNorm, OdGeVector3d &yNorm, OdGeVector3d &zNorm) const
    {
      minPoint = OdGePoint3d::kOrigin + m_basis[0] * m_ivals[0].x + m_basis[1] * m_ivals[1].x + m_basis[2] * m_ivals[2].x;
      maxPoint = OdGePoint3d::kOrigin + m_basis[0] * m_ivals[0].y + m_basis[1] * m_ivals[1].y + m_basis[2] * m_ivals[2].y;
      xNorm = m_basis[1].crossProduct(m_basis[2]);
      yNorm = m_basis[2].crossProduct(m_basis[0]);
      zNorm = m_basis[0].crossProduct(m_basis[1]);
    }
    bool intersectPoint(const OdGePoint3d &pt, const OdGeVector3d &planeNormal, double planeDist, double tol) const
    {
      return planeNormal.x * (pt.x - m_origin.x) + planeNormal.y * (pt.y - m_origin.y) + planeNormal.z * (pt.z - m_origin.z) + planeDist >= -tol;
    }
    bool intersectPlane(const OdGePoint3d &minPt, const OdGePoint3d &maxPt, const OdGeVector3d &planeNormal, double planeDist, double tol) const
    {
      const OdGePoint3d pt((planeNormal[0] > 0.0) ? maxPt.x : minPt.x,
                           (planeNormal[1] > 0.0) ? maxPt.y : minPt.y,
                           (planeNormal[2] > 0.0) ? maxPt.z : minPt.z);
      return planeNormal.x * (pt.x - m_origin.x) + planeNormal.y * (pt.y - m_origin.y) + planeNormal.z * (pt.z - m_origin.z) + planeDist >= -tol;
    }
    bool intersectPlaneBk(const OdGeVector3d &planeNormal, double planeDist, double tol) const
    {
      const OdGePoint3d pt = m_origin + m_basis[0] * ((planeNormal.dotProduct(m_basis[0]) > 0.0) ? m_ivals[0].y : m_ivals[0].x) +
                                        m_basis[1] * ((planeNormal.dotProduct(m_basis[1]) > 0.0) ? m_ivals[1].y : m_ivals[1].x) +
                                        m_basis[2] * ((planeNormal.dotProduct(m_basis[2]) > 0.0) ? m_ivals[2].y : m_ivals[2].x);
      return planeNormal.x * pt.x + planeNormal.y * pt.y + planeNormal.z * pt.z + planeDist >= -tol;
    }
  public:
    /** \details
      Default constructor for the OdSiBoundBlock3d class.
    */
    OdSiBoundBlock3d() { setWcsBasis(); }
    
    /** \details
      Constructor for the OdSiBoundBlock3d class.
      Creates a bound block from the specified OdGeExtents3d object.
      
      \param ab [in] Source object.
    */
    OdSiBoundBlock3d(const OdGeExtents3d &ab) { setGeExtents(ab); }
    
    /** \details
      Constructor for the OdSiBoundBlock3d class.
      Creates a bound block from the specified OdGeBoundBlock3d object.
      
      \param bb [in] Source object.
    */
    OdSiBoundBlock3d(const OdGeBoundBlock3d &bb) { setGeBoundBlock(bb); }
    
    /** \details
      Constructor for the OdSiBoundBlock3d class.
      Creates a bound block from the specified points.
      
      \param p1 [in] First point.
      \param p2 [in] Second point.
    */
    OdSiBoundBlock3d(const OdGePoint3d &p1, const OdGePoint3d &p2) { setGeExtents(OdGeExtents3d(p1, p2)); }
    
    /** \details
      Constructor for the OdSiBoundBlock3d class.
      Creates a bound block from an origin point extending by the specified axes.
      
      \param origin   [in] Origin point.
      \param xAxis    [in] X axis.
      \param yAxis    [in] Y axis.
      \param zAxis    [in] Z axis.
    */
    OdSiBoundBlock3d(const OdGePoint3d &origin, const OdGeVector3d &xAxis, const OdGeVector3d &yAxis, const OdGeVector3d &zAxis)
    { setUnclassified(origin, xAxis, yAxis, zAxis); }

    /** \details
      Sets parameters of this bound block from the specified OdGeExtents3d object.
      
      \param ab   [in] Source object.
    */
    void set(const OdGeExtents3d &ab) { setGeExtents(ab); }
    
    /** \details
      Sets parameters of this bound block from the specified OdGeBoundBlock3d object.
      
      \param bb   [in] Source object.
    */
    void set(const OdGeBoundBlock3d &bb) { setGeBoundBlock(bb); }
    
    /** \details
      Sets parameters of this bound block from the specified corner points.
      
      \param p1   [in] First point.
      \param p2   [in] Second point.
    */
    void set(const OdGePoint3d &p1, const OdGePoint3d &p2) { setGeExtents(OdGeExtents3d(p1, p2)); }
    
    /** \details
      Sets parameters of this bound block from an origin point and directional vectors.
      
      \param origin   [in] Origin point.
      \param xAxis    [in] X axis.
      \param yAxis    [in] Y axis.
      \param zAxis    [in] Z axis.
    */
    void set(const OdGePoint3d &origin, const OdGeVector3d &xAxis, const OdGeVector3d &yAxis, const OdGeVector3d &zAxis)
    { setUnclassified(origin, xAxis, yAxis, zAxis); }

    /** \details
      Gets parameters of this bound block.
      
      \param origin   [out] Receives origin point.
      \param xAxis    [out] Receives X axis.
      \param yAxis    [out] Receives Y axis.
      \param zAxis    [out] Receives Z axis.
    */
    void get(OdGePoint3d &origin, OdGeVector3d &xAxis, OdGeVector3d &yAxis, OdGeVector3d &zAxis) const
    {
      origin = m_origin + m_basis[0] * m_ivals[0].x + m_basis[1] * m_ivals[1].x + m_basis[2] * m_ivals[2].x;
      xAxis = m_basis[0] * (m_ivals[0].y - m_ivals[0].x);
      yAxis = m_basis[1] * (m_ivals[1].y - m_ivals[1].x);
      zAxis = m_basis[2] * (m_ivals[2].y - m_ivals[2].x);
    }

    /** \details
      Transforms this bound block with the specified transformation matrix.
      
      \param tm   [in] Transformation matrix.
    */
    void transformBy(const OdGeMatrix3d &tm)
    {
      m_origin.transformBy(tm);
      m_basis[0].transformBy(tm);
      m_basis[1].transformBy(tm);
      m_basis[2].transformBy(tm);
      // Normalize basis
      const double xScale = m_basis[0].normalizeGetLength();
      const double yScale = m_basis[1].normalizeGetLength();
      const double zScale = m_basis[2].normalizeGetLength();
      m_ivals[0] *= xScale; m_ivals[1] *= yScale; m_ivals[2] *= zScale;
      // Classify
      classify();
    }

    /** \details
      Checks whether the specified bounding block does not intersect this bounding block.

      \param exts  [in]  Bounding block to check.
      \param tol   [in]  Geometric tolerance.

      \returns
      true if the specified bounding block does not intersect this bounding block.
    */
    bool isDisjoint(const OdGeExtents3d &exts, const OdGeTol &tolerance = OdGeContext::gTol) const;
    
    /** \details
      Checks whether this bounding block intersects the specified extents.
      
      \param exts [in]  Extents to check.
      \param tol  [in]  Geometric tolerance.
      
      \returns
      true if and only if this bounding block intersects the specified extents.
    */
    bool contains(const OdGeExtents3d &exts, const OdGeTol &tolerance = OdGeContext::gTol) const;
    
    /** \details
      Checks whether this bounding block contains the specified point.
      
      \param pt    [in]  A 3D point that is presumably contained inside these extents.
      \param tol   [in]  Geometric tolerance.
      
      \returns
      true if and only if this bounding block contains the specified point.
    */
    bool contains(const OdGePoint3d &pt, const OdGeTol &tolerance = OdGeContext::gTol) const;

    /** \details
      Returns minimum point of this bounding block.
      
      \returns
      Minimum point as OdGePoint3d instance.
    */
    OdGePoint3d minPoint() const;
    
    /** \details
      Returns maximum point of this bounding block.
      
      \returns
      Maximum point as OdGePoint3d instance.
    */
    OdGePoint3d maxPoint() const;
    
    /** \details
      Gets minimum and maximum points of this bounding block.
      
      \param p1   [out] Receives minimum point.
      \param p2   [out] Receives maximum point.
    */
    void getMinMaxPoints(OdGePoint3d &p1, OdGePoint3d &p2) const { p1 = minPoint(); p2 = maxPoint(); }
    
    /** \details
      Sets minimum and maximum points of the specified extents from minimum and maximum points of this bounding block.
      
      \param exts   [in/out] Extents to modify.
    */
    void extents(OdGeExtents3d &exts) const { exts.set(minPoint(), maxPoint()); }
    
    bool isBox() const { return m_type == BasisType::kWcs; }
    bool isOrtho() const { return m_type <= BasisType::kOrtho; }
};

inline void OdSiBoundBlock3d::classify()
{
  enum { kXAlign = (1 << 0), kYAlign = (1 << 1), kZAlign = (1 << 2), kXOrtho = (1 << 3), kYOrtho = (1 << 4), kZOrtho = (1 << 5) };
#define CheckFlags(flags) ((classFlags & (flags)) == (flags))
  OdUInt16 classFlags = 0;
  // #CORE-20086 : Old calculations doesn't include real extents in vector, so we could cause large offsets potentially.
  //if (OdEqual(m_basis[0].x, 1.0)) SETBIT_1(classFlags, kXAlign); if (OdEqual(m_basis[1].y, 1.0)) SETBIT_1(classFlags, kYAlign); if (OdEqual(m_basis[2].z, 1.0)) SETBIT_1(classFlags, kZAlign);
  //if (GETBIT(classFlags, kXAlign) || OdEqual(fabs(m_basis[0].x), 1.0) || OdEqual(fabs(m_basis[0].y), 1.0) || OdEqual(fabs(m_basis[0].z), 1.0)) SETBIT_1(classFlags, kXOrtho);
  //if (GETBIT(classFlags, kYAlign) || OdEqual(fabs(m_basis[1].x), 1.0) || OdEqual(fabs(m_basis[1].y), 1.0) || OdEqual(fabs(m_basis[1].z), 1.0)) SETBIT_1(classFlags, kYOrtho);
  //if (GETBIT(classFlags, kZAlign) || OdEqual(fabs(m_basis[2].x), 1.0) || OdEqual(fabs(m_basis[2].y), 1.0) || OdEqual(fabs(m_basis[2].z), 1.0)) SETBIT_1(classFlags, kZOrtho);
  const OdGeVector3d cpBasisX = m_basis[0] * (fabs(m_origin.x) + odmax(fabs(m_ivals[0].x), fabs(m_ivals[0].y))),
                     cpBasisY = m_basis[1] * (fabs(m_origin.y) + odmax(fabs(m_ivals[1].x), fabs(m_ivals[1].y))),
                     cpBasisZ = m_basis[2] * (fabs(m_origin.z) + odmax(fabs(m_ivals[2].x), fabs(m_ivals[2].y)));
  enum { kXZeroX = (1 << 6), kXZeroY = (1 << 7), kXZeroZ = (1 << 8), kYZeroX = (1 << 9), kYZeroY = (1 << 10), kYZeroZ = (1 << 11), kZZeroX = (1 << 12), kZZeroY = (1 << 13), kZZeroZ = (1 << 14) };
  if (OdZero(cpBasisX.x)) SETBIT_1(classFlags, kXZeroX); if (OdZero(cpBasisX.y)) SETBIT_1(classFlags, kXZeroY); if (OdZero(cpBasisX.z)) SETBIT_1(classFlags, kXZeroZ);
  if (OdZero(cpBasisY.x)) SETBIT_1(classFlags, kYZeroX); if (OdZero(cpBasisY.y)) SETBIT_1(classFlags, kYZeroY); if (OdZero(cpBasisY.z)) SETBIT_1(classFlags, kYZeroZ);
  if (OdZero(cpBasisZ.x)) SETBIT_1(classFlags, kZZeroX); if (OdZero(cpBasisZ.y)) SETBIT_1(classFlags, kZZeroY); if (OdZero(cpBasisZ.z)) SETBIT_1(classFlags, kZZeroZ);
  if (cpBasisX.x > 0.0 && CheckFlags(kXZeroY | kXZeroZ)) SETBIT_1(classFlags, kXAlign);
  if (cpBasisY.y > 0.0 && CheckFlags(kYZeroX | kYZeroZ)) SETBIT_1(classFlags, kYAlign);
  if (cpBasisZ.z > 0.0 && CheckFlags(kZZeroX | kZZeroY)) SETBIT_1(classFlags, kZAlign);
  if (GETBIT(classFlags, kXAlign) || CheckFlags(kXZeroY | kXZeroZ) || CheckFlags(kXZeroX | kXZeroZ) || CheckFlags(kXZeroX | kXZeroY)) SETBIT_1(classFlags, kXOrtho);
  if (GETBIT(classFlags, kYAlign) || CheckFlags(kYZeroY | kYZeroZ) || CheckFlags(kYZeroX | kYZeroZ) || CheckFlags(kYZeroX | kYZeroY)) SETBIT_1(classFlags, kYOrtho);
  if (GETBIT(classFlags, kZAlign) || CheckFlags(kZZeroY | kZZeroZ) || CheckFlags(kZZeroX | kZZeroZ) || CheckFlags(kZZeroX | kZZeroY)) SETBIT_1(classFlags, kZOrtho);
  // Apply type
  if (CheckFlags(kXAlign | kYAlign | kZAlign))
  {
    m_ivals[0].x += m_origin.x; m_ivals[0].y += m_origin.x;
    m_ivals[1].x += m_origin.y; m_ivals[1].y += m_origin.y;
    m_ivals[2].x += m_origin.z; m_ivals[2].y += m_origin.z;
    m_origin = OdGePoint3d::kOrigin; m_type = BasisType::kWcs;
  }
  else if (CheckFlags(kXOrtho | kYOrtho | kZOrtho))
  {
    const OdGePoint3d ptMin = OdGePoint3d::kOrigin + m_basis[0] * m_ivals[0].x + m_basis[1] * m_ivals[1].x + m_basis[2] * m_ivals[2].x;
    const OdGePoint3d ptMax = OdGePoint3d::kOrigin + m_basis[0] * m_ivals[0].y + m_basis[1] * m_ivals[1].y + m_basis[2] * m_ivals[2].y;
    const OdGePoint3d origin = m_origin;
    setWcsBasis(false);
    m_ivals[0].set(origin.x + odmin(ptMin.x, ptMax.x), origin.x + odmax(ptMin.x, ptMax.x));
    m_ivals[1].set(origin.y + odmin(ptMin.y, ptMax.y), origin.y + odmax(ptMin.y, ptMax.y));
    m_ivals[2].set(origin.z + odmin(ptMin.z, ptMax.z), origin.z + odmax(ptMin.z, ptMax.z));
  }
  else
    subClassifyArbitrary();
#undef CheckFlags
}

inline bool OdSiBoundBlock3d::isDisjoint(const OdGeExtents3d &exts, const OdGeTol &tolerance) const
{ const double tol = tolerance.equalPoint();
  if (isBox())
    return (exts.minPoint().x - tol) > m_ivals[0].y || (exts.minPoint().y - tol) > m_ivals[1].y ||
           (exts.minPoint().z - tol) > m_ivals[2].y || m_ivals[0].x > (exts.maxPoint().x + tol) ||
           m_ivals[1].x > (exts.maxPoint().y + tol) || m_ivals[2].x > (exts.maxPoint().z + tol);
  else
  {
    if (isOrtho())
    {
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), m_basis[0], -m_ivals[0].x, tol)) // Left
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), -m_basis[0], m_ivals[0].y, tol)) // Right
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), m_basis[1], -m_ivals[1].x, tol)) // Top
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), -m_basis[1], m_ivals[1].y, tol)) // Bottom
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), m_basis[2], -m_ivals[2].x, tol)) // Front
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), -m_basis[2], m_ivals[2].y, tol)) // Back
        return true;
    }
    else
    { OdGePoint3d minPoint, maxPoint; OdGeVector3d xNorm, yNorm, zNorm;
      getInternalArbitraryBasis(minPoint, maxPoint, xNorm, yNorm, zNorm);
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), xNorm, -(xNorm.dotProduct(minPoint.asVector())), tol)) // Left
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), -xNorm, (xNorm.dotProduct(maxPoint.asVector())), tol)) // Right
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), yNorm, -(yNorm.dotProduct(minPoint.asVector())), tol)) // Top
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), -yNorm, (yNorm.dotProduct(maxPoint.asVector())), tol)) // Bottom
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), zNorm, -(zNorm.dotProduct(minPoint.asVector())), tol)) // Front
        return true;
      if (!intersectPlane(exts.minPoint(), exts.maxPoint(), -zNorm, (zNorm.dotProduct(maxPoint.asVector())), tol)) // Back
        return true;
    }
    // If passed for OBB, run same test for AABB. If we have at least one separating axis - objects is disjoint.
    if (!intersectPlaneBk(OdGeVector3d::kXAxis, -exts.minPoint().x, tol)) // Left
      return true;
    if (!intersectPlaneBk(-OdGeVector3d::kXAxis, exts.maxPoint().x, tol)) // Right
      return true;
    if (!intersectPlaneBk(OdGeVector3d::kYAxis, -exts.minPoint().y, tol)) // Top
      return true;
    if (!intersectPlaneBk(-OdGeVector3d::kYAxis, exts.maxPoint().y, tol)) // Bottom
      return true;
    if (!intersectPlaneBk(OdGeVector3d::kZAxis, -exts.minPoint().z, tol)) // Front
      return true;
    if (!intersectPlaneBk(-OdGeVector3d::kZAxis, exts.maxPoint().z, tol)) // Back
      return true;
    return false;
  }
}

inline bool OdSiBoundBlock3d::contains(const OdGeExtents3d &exts, const OdGeTol &tolerance) const
{ const double tol = tolerance.equalPoint();
  if (isBox())
    return ((exts.minPoint().x + tol) >= m_ivals[0].x && (exts.minPoint().y + tol) >= m_ivals[1].x &&
            (exts.minPoint().z + tol) >= m_ivals[2].x && m_ivals[0].y >= (exts.maxPoint().x - tol) &&
            m_ivals[1].y >= (exts.maxPoint().y - tol) && m_ivals[2].y >= (exts.maxPoint().z - tol));
  else if (isOrtho())
    return intersectPlane(exts.maxPoint(), exts.minPoint(), m_basis[0], -m_ivals[0].x, tol) && // Left
           intersectPlane(exts.maxPoint(), exts.minPoint(), -m_basis[0], m_ivals[0].y, tol) && // Right
           intersectPlane(exts.maxPoint(), exts.minPoint(), m_basis[1], -m_ivals[1].x, tol) && // Top
           intersectPlane(exts.maxPoint(), exts.minPoint(), -m_basis[1], m_ivals[1].y, tol) && // Bottom
           intersectPlane(exts.maxPoint(), exts.minPoint(), m_basis[2], -m_ivals[2].x, tol) && // Front
           intersectPlane(exts.maxPoint(), exts.minPoint(), -m_basis[2], m_ivals[2].y, tol);   // Back
  else
  { OdGePoint3d minPoint, maxPoint; OdGeVector3d xNorm, yNorm, zNorm;
    getInternalArbitraryBasis(minPoint, maxPoint, xNorm, yNorm, zNorm);
    return intersectPlane(exts.maxPoint(), exts.minPoint(), xNorm, -(xNorm.dotProduct(minPoint.asVector())), tol) && // Left
           intersectPlane(exts.maxPoint(), exts.minPoint(), -xNorm, (xNorm.dotProduct(maxPoint.asVector())), tol) && // Right
           intersectPlane(exts.maxPoint(), exts.minPoint(), yNorm, -(yNorm.dotProduct(minPoint.asVector())), tol) && // Top
           intersectPlane(exts.maxPoint(), exts.minPoint(), -yNorm, (yNorm.dotProduct(maxPoint.asVector())), tol) && // Bottom
           intersectPlane(exts.maxPoint(), exts.minPoint(), zNorm, -(zNorm.dotProduct(minPoint.asVector())), tol) && // Front
           intersectPlane(exts.maxPoint(), exts.minPoint(), -zNorm, (zNorm.dotProduct(maxPoint.asVector())), tol);   // Back
  }
}

inline bool OdSiBoundBlock3d::contains(const OdGePoint3d &pt, const OdGeTol &tolerance) const
{ const double tol = tolerance.equalPoint();
  if (isBox())
    return (pt.x + tol) >= m_ivals[0].x && (pt.y + tol) >= m_ivals[1].x &&
           (pt.z + tol) >= m_ivals[2].x && m_ivals[0].y >= (pt.x - tol) &&
           m_ivals[1].y >= (pt.y - tol) && m_ivals[2].y >= (pt.z - tol);
  else if (isOrtho())
    return intersectPoint(pt, m_basis[0], -m_ivals[0].x, tol) && // Left
           intersectPoint(pt, -m_basis[0], m_ivals[0].y, tol) && // Right
           intersectPoint(pt, m_basis[1], -m_ivals[1].x, tol) && // Top
           intersectPoint(pt, -m_basis[1], m_ivals[1].y, tol) && // Bottom
           intersectPoint(pt, m_basis[2], -m_ivals[2].x, tol) && // Front
           intersectPoint(pt, -m_basis[2], m_ivals[2].y, tol);   // Back
  else
  { OdGePoint3d minPoint, maxPoint; OdGeVector3d xNorm, yNorm, zNorm;
    getInternalArbitraryBasis(minPoint, maxPoint, xNorm, yNorm, zNorm);
    return intersectPoint(pt, xNorm, -(xNorm.dotProduct(minPoint.asVector())), tol) && // Left
           intersectPoint(pt, -xNorm, (xNorm.dotProduct(maxPoint.asVector())), tol) && // Right
           intersectPoint(pt, yNorm, -(yNorm.dotProduct(minPoint.asVector())), tol) && // Top
           intersectPoint(pt, -yNorm, (yNorm.dotProduct(maxPoint.asVector())), tol) && // Bottom
           intersectPoint(pt, zNorm, -(zNorm.dotProduct(minPoint.asVector())), tol) && // Front
           intersectPoint(pt, -zNorm, (zNorm.dotProduct(maxPoint.asVector())), tol);   // Back
  }
}

inline OdGePoint3d OdSiBoundBlock3d::minPoint() const
{
  if (isBox())
    return OdGePoint3d(m_ivals[0].x, m_ivals[1].x, m_ivals[2].x);
  else
    return OdGePoint3d(m_origin.x + m_basis[0].x * ((m_basis[0].x > 0.0) ? m_ivals[0].x : m_ivals[0].y) +
                                    m_basis[1].x * ((m_basis[1].x > 0.0) ? m_ivals[1].x : m_ivals[1].y) +
                                    m_basis[2].x * ((m_basis[2].x > 0.0) ? m_ivals[2].x : m_ivals[2].y),
                       m_origin.y + m_basis[0].y * ((m_basis[0].y > 0.0) ? m_ivals[0].x : m_ivals[0].y) +
                                    m_basis[1].y * ((m_basis[1].y > 0.0) ? m_ivals[1].x : m_ivals[1].y) +
                                    m_basis[2].y * ((m_basis[2].y > 0.0) ? m_ivals[2].x : m_ivals[2].y),
                       m_origin.z + m_basis[0].z * ((m_basis[0].z > 0.0) ? m_ivals[0].x : m_ivals[0].y) +
                                    m_basis[1].z * ((m_basis[1].z > 0.0) ? m_ivals[1].x : m_ivals[1].y) +
                                    m_basis[2].z * ((m_basis[2].z > 0.0) ? m_ivals[2].x : m_ivals[2].y));
}

inline OdGePoint3d OdSiBoundBlock3d::maxPoint() const
{
  if (isBox())
    return OdGePoint3d(m_ivals[0].y, m_ivals[1].y, m_ivals[2].y);
  else
    return OdGePoint3d(m_origin.x + m_basis[0].x * ((m_basis[0].x > 0.0) ? m_ivals[0].y : m_ivals[0].x) +
                                    m_basis[1].x * ((m_basis[1].x > 0.0) ? m_ivals[1].y : m_ivals[1].x) +
                                    m_basis[2].x * ((m_basis[2].x > 0.0) ? m_ivals[2].y : m_ivals[2].x),
                       m_origin.y + m_basis[0].y * ((m_basis[0].y > 0.0) ? m_ivals[0].y : m_ivals[0].x) +
                                    m_basis[1].y * ((m_basis[1].y > 0.0) ? m_ivals[1].y : m_ivals[1].x) +
                                    m_basis[2].y * ((m_basis[2].y > 0.0) ? m_ivals[2].y : m_ivals[2].x),
                       m_origin.z + m_basis[0].z * ((m_basis[0].z > 0.0) ? m_ivals[0].y : m_ivals[0].x) +
                                    m_basis[1].z * ((m_basis[1].z > 0.0) ? m_ivals[1].y : m_ivals[1].x) +
                                    m_basis[2].z * ((m_basis[2].z > 0.0) ? m_ivals[2].y : m_ivals[2].x));
}

#include "TD_PackPop.h"

#endif // _SpBBlock_h_Included_
