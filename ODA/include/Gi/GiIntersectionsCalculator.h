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

#ifndef __ODGIINTERSECTIONSCALCULATOR__
#define __ODGIINTERSECTIONSCALCULATOR__

#include "TD_PackPush.h"
#include "Ge/GeExtents3d.h"
#include "Gi/GiExtentsSpaceTree.h"

/** \details
  .
  Library: Source code provided.
*/
class OdGiTriangleForIntersectTest
{
  friend class OdGiIntersectionsCalculator;
  friend class OdGiCollisionDetector;
  friend class OdGiCollisionDetectorIntersectionsOnly;

  // unique ID of the object
  //IMPORTANT: the user is responsible for the uniqueness of the ID
  OdUInt32    ID;

  // extents of the triangle
  OdGeExtents3d       m_extents;

  // parameters of the triangle's plane
  OdGeVector3d        planeNorm;
  double              planeD;
  bool                m_bIsPlaneCalculated;

public:
  //three vertices
  OdGePoint3d         ABC[3];

  // default constructor
  OdGiTriangleForIntersectTest();

  //constructor
  OdGiTriangleForIntersectTest(const OdGePoint3d *points, OdUInt32 uniqueID);

  /** \details
  Specifies triangle data.
  \param points [in] Array of 3 points.
  \param bCalcExtents [in] If true, extents will be calculated using const OdGePoint3d* points.
  */
  void setData( const OdGePoint3d* points, bool bCalcExtents = true );
  /** \details
  Overrides triangle extents.
  \param extents [in] New triangle extents.
  */
  void rewriteExtents( const OdGeExtents3d& extents );

  // retrieve the plane's normal
  inline const OdGeVector3d*  getTrianglePlaneNorm();

  //retrieve the D
  inline double getPlaneD();

  //**********************************************************************//
  //********************METHODS FOR USING IN SPACE TREE*******************//
  //**********************************************************************//
  //set/get ID
  OdUInt32  getID() {return ID;}
  void      setID(OdUInt32 uniqueID){ID = uniqueID;}

  // check that the triangle is in extents
  inline bool isInExtents(OdGeExtents3d& extents) const;

  // not need for this class
  bool isInExtents(OdGeExtents2d& extents) const {return false;}

  // check that objects are equal
  bool isEqual(OdGiTriangleForIntersectTest* pObject, const OdGeTol& tol = OdGeContext::gTol) const
  {
    return false;
  }

private:
  
  // calculate the parameters of the plane
  inline void calculatePlaneParameters();
};

/** \details
  The data type that represents a vector of the <link OdGiTriangleForIntersectTest, OdGiTriangleForIntersectTest> objects.
*/
typedef OdVector<OdGiTriangleForIntersectTest, OdMemoryAllocator<OdGiTriangleForIntersectTest> > OdGiIntersectTrianglesVector;
typedef OdGiExtentsSpaceTree<3, 5, 20, OdGeExtents3d, OdGePoint3d, OdGiTriangleForIntersectTest>  OdGiExtents3dSpaceTree_Gi;
typedef OdGiExtentsSpaceNode<OdGeExtents3d, OdGiTriangleForIntersectTest> OdGiExtents3dSpaceNode_Gi;

/** \details
  .

  Library: Source code provided.
*/
class OdGiEdgeForIntersectTest : public OdGiExtents3dSpaceEdge
{
  public:  
  //means that this edge is an edge of touching of two triangles
  bool        m_bIsTouchingEdge;

  OdGiEdgeForIntersectTest(OdGiExtents3dSpacePoint& pt1, OdGiExtents3dSpacePoint& pt2, OdUInt32 uniqueID) : OdGiExtents3dSpaceEdge(pt1, pt2, uniqueID)
  {
    m_bIsTouchingEdge = false;
  }
};

/** \details
  This class implements triangles-based intersection calculation.
  Usage:
  1) call initializeCalculations()
  2) add triangles:
    2.1) call appendTriangleContainer to obtain containerID
    2.2) call addTriangleToContainer with obtained ID
  3) specify containers that should be tested by calling addContainerToBeTested and call processPathCalculation for them
  4) call computeIntersections to calculate intersections between specified container and all "should be tested" containers
  5) use processPathCalculation() to obtain results

  Library: Source code provided.

  <group OdGi_Classes>
  \sa
  <link gs_collision_detection, Work with Collision Detection>
*/
class OdGiIntersectionsCalculator : public OdGiExtentsSpaceTreeCallback<OdGeExtents3d, OdGiTriangleForIntersectTest>
{
  protected:
    // tolerance for the intersection calculation
    OdGeTol m_tol;

    // cach data for the controlling already intersected triangles with the given triangle
    OdVector<bool, OdMemoryAllocator<bool>>                 m_vectTestedTriangles;            
    OdUInt32Vector                                          m_vectTestTriangles_objBoundary;

    // data for controlling the objects with which will be intersected the given object
    OdUInt32Vector                                          m_vectToBeTestedObjects;

    // following parameter need for the callback method' notifyObjectPlacedAtNode'
    bool                                                    m_bSecondObjectProcessedInTree;

    // cach data for storing the triangles from all objects
    OdVector<OdGiIntersectTrianglesVector*>                 m_containerTriangles;
        
    // extents trees for the triangles and vertices
    OdGiExtents3dSpaceTree_Gi                               m_spaceTriangTree;
    OdGiExtents3dSpaceTree                                  m_spaceVertexTree;

    // arrays for storing the intersecting vertices and edges (this arrays will have the same size as 'm_vectToBeTestedObjects')
    OdArray<OdGiExtents3dSpacePoint*>*                      m_intersectVertices;
    OdArray<OdGiEdgeForIntersectTest*>*                     m_intersectEdges;

    // list for the storing final pathes for polyout
    OdList<OdGiExtents3dSpaceChainPolyline*>                m_finalIntersectPathes;
    bool                                                    m_b3dFacesActive;

    // method for the callback from the tree
    virtual bool notifyObjectPlacedAtNode(OdGiTriangleForIntersectTest* pTriang, int objectType, OdGiExtents3dSpaceNode_Gi* pNode);

    // calculate intersections of the triangles
    void intersectTriangles(OdUInt32 idObjA, OdUInt32 trIdA, OdUInt32 idObjB, OdUInt32 trIdB, OdUInt32 idObjTested, const OdGeTol& tol);

    //Public API
  public:
    
    /** \details
      Default constructor for the OdGiIntersectionsCalculator class.
    */
    OdGiIntersectionsCalculator();

    /** \details
      Destructor for the OdGiIntersectionsCalculator class.
    */
    virtual ~OdGiIntersectionsCalculator(){}
    /** Appends specified triangle container to the containers list and returns it ID
    */
    OdInt32 appendTriangleContainer( OdGiIntersectTrianglesVector* pContainer );
    /** Adds triangle to the specified triangle container
    */
    OdInt32 addTriangleToContainer( OdInt32 containerID, const OdGePoint3d *pTriangle );
    /** Adds specified triangle container to the "containers to be tested" list
    */
    OdInt32 addContainerToBeTested( OdInt32 containerID );
    /** Computes intersections between specified triangle container and "containers to be tested" list
    */
    void computeIntersections( OdInt32 containerID, OdGeExtents3d &extents );
    // initialize calculations
    virtual void initializeCalculations(OdGeExtents3d& ext, OdInt32 nObjects);
    // finalize calculations
    virtual void finalizeCalculations();
    // intermediate finalize calculations
    void intermediatefinalizeCalculations();

    //process triangles into tree
    void processTrianglesIntoSpaceTree(OdUInt32 objID, bool bOtherObjectsProcessed);
    //process path calculation
    void processPathCalculation(OdUInt32 idObjTested);
    /** \details
    Retrives intersection tolerance
    \returns Returns intersection tolerance
    */
    const OdGeTol& tolerance() const { return m_tol; }
    /** \details
    Specifies intersection tolerance
    \param tol [in] Intersection tolerance
    */
    void setTolerance( const OdGeTol& tol ) { m_tol = tol; }

  public:
    //Data accessors
    bool& facesActive() { return m_b3dFacesActive; }

    bool getSpaceTreeRootExtents( OdGeExtents3d& ext );

    OdUInt32 triangleContainerSize() const { return m_containerTriangles.size(); }

    OdUInt32 containerToBeTestedSize() const { return m_vectToBeTestedObjects.size(); }

    void removeEdgeInfo( OdInt32 objID );

    OdList<OdGiExtents3dSpaceChainPolyline*>& finalIntersectionPathes() { return m_finalIntersectPathes; }
    OdArray<OdGiExtents3dSpacePoint*>*  intersectionVertices() { return m_intersectVertices; }
    OdArray<OdGiEdgeForIntersectTest*>* intersectionEdges(){ return m_intersectEdges; }
};

/** \details
  This class is a detector for collision of triangular representations of entities.

  <group OdGi_Classes>
  \sa
  <link gs_collision_detection, Work with Collision Detection>
*/
class OdGiCollisionDetector : public OdGiIntersectionsCalculator
{
public:
  /** \details
    Default constructor for the OdGiCollisionDetector class.
  */
  OdGiCollisionDetector();
  
  /** \details
    Destructor for the OdGiCollisionDetector class.
  */
  virtual ~OdGiCollisionDetector() {};

protected:
   // method for the callback from the tree
  virtual bool notifyObjectPlacedAtNode(OdGiTriangleForIntersectTest* pTriang, int objectType, OdGiExtents3dSpaceNode_Gi* pNode);

protected: //Hide OdGiIntersectionsCalculator methods
  void computeIntersections( OdInt32 containerID, OdGeExtents3d &extents ) { OdGiIntersectionsCalculator::computeIntersections( containerID, extents ); }
  void processPathCalculation(OdUInt32 idObjTested) { OdGiIntersectionsCalculator::processPathCalculation( idObjTested ); }
  void removeEdgeInfo( OdInt32 objID ) { OdGiIntersectionsCalculator::removeEdgeInfo( objID ); }
  OdList<OdGiExtents3dSpaceChainPolyline*>& finalIntersectionPathes() { return m_finalIntersectPathes; }
  OdArray<OdGiExtents3dSpacePoint*>*  intersectionVertices() { return m_intersectVertices; }
  OdArray<OdGiEdgeForIntersectTest*>* intersectionEdges(){ return m_intersectEdges; }

public:
  /** \details
    Detects collisions between a specified triangle container and all triangle containers that are marked as "container to be tested".
    \param containerID [in] Triangle container.
    \param extents     [in] Not used.
  */
  void detectCollisions( OdInt32 containerID, const OdGeExtents3d &extents );
  
  /** \details
    Gets a list of all detected collisions.
    \param result   [out] Recieves results of collision detection.
  */
  void getCollisions( OdList<OdInt32>& result );
  
  /** \details
    Retrieves a collision distance at the specified index.
    \param collisionIndex [in] Index of a collision for which to get the distance.
    \param result         [out] Receives collision distance.
    \returns
    true if collision distance is sucessfully received. This method returns false if index exceeds 
    the size of vector with collisions or if collision at the specified index is not detected.
  */
  bool getCollisionDistance( OdUInt32 collisionIndex, double& result ) const;

  /** \details
    Finalizes calculations, i.e. resets the triangles tree, removes triangles info and releases all data related to collision detection.
  */
  virtual void finalizeCalculations();

  /** \details
    Clears all triangle containers that were marked for collision detection calculations.
  */
  void clearContainersToBeTested();

  /** \details
    Specifies whether to detect collisions only when collided objects intersect.
    \param b [in] Flag that specifies whether to detect only intersecting objects. If true, touches are not detected.
  */
  void setIntersectionsOnly( bool b ) { SETBIT( m_options, kOption_IntersectionOnly, b ); }
  
  /** \details
    Checks whether only intersected objects are detected as collisions.
    \returns
    true if only intersected objects are detected as collisions, false otherwise.
  */
  bool isIntersectionsOnly() const { return GETBIT( m_options, kOption_IntersectionOnly ); }

  /** \details
    Specifies a distance for the clearance mode when objects that are "too close" are detected as intersections.
    \param cl [in] Clearance distance. Object which have less distance than this value are considered collided in the clearance mode.
  */
  void setClearance( double cl ) 
  {
    SETBIT( m_options, kOption_Clearance, cl > 0. );
    m_dClearance = cl;
  }
  
  /** \details
    Checks whether clearance mode for detecting collisions is enabled. This method detects collisions between intersectiong, touching and objects that are "too close".
    \returns
    true if clearance mode is enabled, false otherwise.
  */
  bool isClearance() const { return GETBIT( m_options, kOption_Clearance ); }
  
  /** \details
    Retrieves a distance for the clearance mode when objects that are "too close" are detected as intersections.
  */
  double getClearance() const { return m_dClearance; }

  /** \details
    Specifies whether collision detection should calculate collision distance.
    \param b [in] The flag that indicates that collision detection should calculate collision distance.
  */
  void setCalcDistance( bool b ) { SETBIT( m_options, kOption_CalcDistance, b ); }
  
  /** \details
    Checks whether collision detection calculates collision distance.
    \returns
    true if collision detection calculates collision distance, false otherwise.
  */
  bool getCalcDistance() const { return GETBIT( m_options, kOption_CalcDistance ); }

  /** \details
    Specifies whether collision detection should check all faces instead of detecting the first collision.
    \param b [in] If true, collision detection checks all faces instead of detecting the first collision.
  */
  void setCheckAll( bool b ) { SETBIT( m_options, kOption_CheckAll, b ); }
  
  /** \details
    Checks whether collision detection checks all faces instead of detecting the first collision.
    \returns
    true if collision detection checks all faces, false otherwise.
  */
  bool getCheckAll() const { return GETBIT( m_options, kOption_CheckAll ); }

protected:
  //DOM-IGNORE-BEGIN
  
  struct DetectedCollision
  {
    bool bDetected;
    double dDistance;
    DetectedCollision() : bDetected( false ), dDistance( 0.0 ) {}
    operator bool() const { return bDetected; }
    DetectedCollision& operator=( bool b ) { bDetected = b; return *this; }
  };
  OdVector<DetectedCollision, OdMemoryAllocator<DetectedCollision> >                m_vectCollidedContainers;
  //Performance
  DetectedCollision*                                                   m_vectCollidedContainersAsPtr;
  OdGePoint3d   m_ptA;
  OdGePoint3d   m_ptB;

  bool collideTriangles( OdUInt32 idObjA, OdUInt32 trIdA, OdUInt32 idObjB, OdUInt32 trIdB, OdUInt32 idObjTested, const OdGeTol& tol );

  //check that points of one triangle are placed on opposite siedes of the second triangle plane
  OdUInt32 checkPointsPlacement( const OdGeVector3d* pPlaneNormalA, double D_A, const OdGePoint3d* pPointsTriangleB, const OdGeTol& tol );

  enum CollisionOption
  {
    kOption_IntersectionOnly = 1,
    kOption_Clearance = 2,
    kOption_CalcDistance = 4,
    kOption_CheckAll = 8
  };
  OdUInt8 m_options;

  double m_dClearance;
  
  //DOM-IGNORE-END
};

//Collision detector that detect only intersections (no touching)
//It is separate class because additional checks in OdGiCollisionDetector::collideTriangles will slow down it
/*class OdGiCollisionDetectorIntersectionsOnly : public OdGiCollisionDetector
{
public:
  OdGiCollisionDetectorIntersectionsOnly() : OdGiCollisionDetector()
  {};
  virtual ~OdGiCollisionDetectorIntersectionsOnly()
  {};
protected:
   // method for the callback from the tree
  virtual bool notifyObjectPlacedAtNode(OdGiTriangleForIntersectTest* pTriang, int objectType, OdGiExtents3dSpaceNode_Gi* pNode);

  bool collideTriangles(OdUInt64 idObjA, OdUInt64 trIdA, OdUInt64 idObjB, OdUInt64 trIdB, OdUInt64 idObjTested, const OdGeTol& tol);

  //check that points of one triangle are placed on opposite siedes of the second triangle plane
  OdUInt32 checkPointsPlacement(const OdGeVector3d* pPlaneNormalA, double D_A, const OdGePoint3d* pPointsTriangleB, const OdGeTol& tol);
};*/


#include "TD_PackPop.h"

#endif //#ifndef __ODGIINTERSECTIONSCALCULATOR__
