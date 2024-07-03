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

#ifndef _SpatialIndex_h_Included_
#define _SpatialIndex_h_Included_

#include "OdPlatformSettings.h"

#ifdef SPATIALINDEX_DLL_EXPORTS
  #define ODSI_API          OD_TOOLKIT_EXPORT
  #define ODSI_API_STATIC   OD_STATIC_EXPORT
#else
  #define ODSI_API          OD_TOOLKIT_IMPORT
  #define ODSI_API_STATIC   OD_STATIC_IMPORT
#endif

//////////////////////////////////////////////////////////////////////////

#include "RxObject.h"
#include "Ge/GeExtents3d.h"
#include "Ge/GeExtents2d.h"

#include "TD_PackPush.h"

/** \details
    This class represents Spatial Index Shape objects.
    Corresponding C++ library: SpatialIndex
    <group OdSi_Classes>
*/
struct ODSI_API OdSiShape
{
  /** \details
    Returns true if and only if this Shape object contains the specified extents.

    \param extents [in]  Any 3D extents box.
    \param planar [in]  If and only if true, a planar computation is made.
  */
  virtual bool contains( const OdGeExtents3d& extents, bool planar, const OdGeTol& tol = OdGeContext::gTol ) const = 0;
  /** \details
    Returns true if and only if this Shape object intersects the specified extents.

    \param extents [in]  Any 3D extents box.
    \param planar [in]  If and only if true, a planar computation is made.
  */
  virtual bool intersects( const OdGeExtents3d& extents, bool planar, const OdGeTol& tol = OdGeContext::gTol ) const = 0;

  virtual ~OdSiShape() {};
  virtual OdSiShape* clone() const { return 0; }
  virtual void transform(const OdGeMatrix3d&) {};

  static bool isOverallSpace(const OdSiShape* ptr);
  static bool isNoSpace(const OdSiShape* ptr);

  ODSI_API_STATIC static const OdSiShape& kOverallSpace;
  ODSI_API_STATIC static const OdSiShape& kNoSpace;
};
/** \details
    This class represents Spatial Index Entity objects.
    Corresponding C++ library: SpatialIndex

    <group OdSi_Classes>
*/
struct OdSiEntity
{
  /** \details
    Returns the extents of this Entity object.

    \param extents [out]  Receives the extents.
    \returns
    Returns true if and only if this Entity object has extents.
  */
  virtual bool extents(OdGeExtents3d& extents) const = 0;
};

/** \details
    This class represents Spatial Index Visitor Objects
    Corresponding C++ library: SpatialIndex
    <group OdSi_Classes>
*/
struct OdSiVisitor
{
  /** 
    \param entity [in] Pointer to any OdSiEntity object.
    completelyInside [in] unknown.
  */
  virtual void visit( OdSiEntity* entity, bool completelyInside ) = 0;
};

class ODSI_API OdSiSpatialIndex;
/** \details
    This template class is a specialization of the OdSmartPtr class for OdSiSpatialIndex object pointers.
*/
typedef OdSmartPtr<OdSiSpatialIndex> OdSiSpatialIndexPtr;

/** \details
    This class represents SpatialIndex objects.
    Corresponding C++ library: SpatialIndex
    <group OdSi_Classes>
*/
class ODSI_API OdSiSpatialIndex : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdSiSpatialIndex);

  /** \details
    Spatial Index creation flags.
  */
  enum CreationFlags
  {
    kSiNoFlags       = 0,

    kSiPlanar        = (1 << 0), // Create 2D Spatial Index.
    kSiModifyMtAware = (1 << 1), // Protect insert/remove/clear by mutex object.
    kSiAccessMtAware = (1 << 2), // Protect query/extents/tolerance by mutex object.

    kSiFullMtAware   = (kSiModifyMtAware | kSiAccessMtAware)
  };

  /** \details
    Creates a SpatialIndex object with the specified parameters.
    \param flags [in]  Specifies set of flags for Spatial Index creation.
    \param maxDepth [in]  Maximum depth of the Spatial Index.
    \param maxCount [in]  Maximum number of nodes in the SpatialIndex.
    \param eps [in]  Relative tolerance (equalVector).

    \returns
    Returns a SmartPointer to the new SpatialIndex object.
    \remarks
    maxDepth specifies the maximum number of times the tree-structured SpatialIndex can branch.
  */
  static OdSiSpatialIndexPtr createObject( OdUInt32 flags, unsigned int initialNumEntity, unsigned int maxDepth = 30, unsigned int maxCount = 20, double eps = 1e-10 );

  /** \details
    Inserts the specified SiEntity object into the this SpatialIndex object.
    \param entity [in]  Pointer to the OdSiEntity to insert.
  */
  virtual void insert( OdSiEntity* entity ) = 0;
  /** \details
    Removes the specified SiEntity object into the this SpatialIndex object.
    \param entity [in]  Pointer to the OdSiEntity to remove.
    \returns
    Returns true if and only if the specified entity was in this SpatialIndex object.
  */
  virtual bool remove( OdSiEntity* entity ) = 0;

  /** \details
    \param shape [in]  Any OdSiShape object.
    \param visitor [in]  Any OdSiVisitor object.
  */
  virtual void query( const OdSiShape& shape, OdSiVisitor& visitor ) const = 0;
  /** \details
    Clears this SpatialIndex object.
  */
  virtual void clear() = 0;
  /** \details
    Sets the maximum depth of this SpatialIndex object.
    \param maxDepth [in]  Maximum depth.
    \remarks
    maxDepth specifies the maximum number of times the tree-structured SpatialIndex can branch.
  */
  virtual void setMaxTreeDepth( unsigned char maxDepth ) = 0;
  /** \details
    Sets the maximum number of entities a spatial index node may contain.
    \param maxCount [in]  Maximum number of entities.
  */
  virtual void setMaxNodeSize( unsigned char maxCount ) = 0;
  /** \details
    Returns the extents of this SpatialIndex object.

    \param extents [out]  Receives the extents.
    \returns
    Returns true if and only if this SpatialIndex object has extents.
  */
  virtual bool extents(OdGeExtents3d& extents) const = 0;

  /** \details
    Returns the maximum depth of this SpatialIndex object.
    \remarks
    maxDepth specifies the maximum number of times the tree-structured SpatialIndex can branch.
  */
  virtual unsigned maxTreeDepth() const = 0;

  /** \details
    Returns the maximum number of entities a spatial index node may contain.
  */
  virtual unsigned maxNodeSize() const = 0;

  /** \details
    Returns the tolerance of this SpatialIndex object.

    \returns
    Returns tolerance where equalPoint value is scaled by extents of SpatialIndex.
  */
  virtual const OdGeTol& tolerance() const = 0;

  /** \details
    Sets tolerance where equalPoint value is scaled by extents of SpatialIndex.
    \param tol [in]  New tolerance value.
  */
  virtual void setTolerance(const OdGeTol& tol) = 0;

  /** \details
    Returns state of SpatialIndex tree.
    \returns
    Return true if SpatialIndex tree already built or false if SpatialIndex tree is still in initial state.
  */
  virtual bool isInitialized() const = 0;
};

namespace OdSi
{
bool ODSI_API properExtents(const OdGeExtents3d& ext);
}

/** \details
This class represents a concept of a shape that depends on the actual size of the model.
Library: SpatialIndex
<group OdSi_Classes>
*/
struct ODSI_API OdSiDynamicShape: public OdSiShape
{
  virtual void update(const OdGeExtents3d& we) const = 0;
};

typedef OdArray<OdSiShape*, OdMemoryAllocator<OdSiShape*> > OdSiShapePtrArray;
typedef OdArray<const OdSiShape*, OdMemoryAllocator<const OdSiShape*> > OdSiShapeConstPtrArray;

/** \details
    This class represents intersection of OdSiShapes as one OdSiShape.

    Library: SpatialIndex
    <group OdSi_Classes>
*/
struct ODSI_API OdSiShapesIntersection: public OdSiShape
{
  OdSiShapesIntersection()
  {
  }

  OdSiShapesIntersection(const OdSiShapeConstPtrArray& shapes)
  {
    reset(shapes);
  }

  ~OdSiShapesIntersection()
  {
    clear();
  }

  const OdSiShapePtrArray& shapes() const
  {
    return m_shapes;
  }

  void reset(const OdSiShapeConstPtrArray& shapes)
  {
    clear();
    m_shapes.reserve(shapes.size());
    for(OdSiShapeConstPtrArray::const_iterator it = shapes.begin(); it != shapes.end(); it++)
      m_shapes.push_back((*it)->clone());
  }

  void clear()
  {
    for(OdSiShapePtrArray::iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
      delete *it;
    m_shapes.clear();
  }
  virtual bool contains(const OdGeExtents3d& extents, bool planar, const OdGeTol& tol = OdGeContext::gTol) const
  {
    for(OdSiShapePtrArray::const_iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
    {
      if(!(*it)->contains(extents, planar, tol))
        return false;
    }
    return true;
  }

  virtual bool intersects( const OdGeExtents3d& extents, bool planar, const OdGeTol& tol = OdGeContext::gTol ) const
  {
    for(OdSiShapePtrArray::const_iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
    {
      if(!(*it)->intersects(extents, planar, tol))
        return false;
    }
    return true;
  }

  virtual OdSiShape* clone() const
  {
    OdSiShapeConstPtrArray ar;
    ar.reserve(m_shapes.size());
    for(OdSiShapePtrArray::const_iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
        ar.push_back(*it);
    return new OdSiShapesIntersection(ar);
  }

  virtual void transform(const OdGeMatrix3d& tf)
  {
    for(OdSiShapePtrArray::iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
      (*it)->transform(tf);
  }

private:
  OdSiShapePtrArray m_shapes;
};

#include "TD_PackPop.h"

#endif