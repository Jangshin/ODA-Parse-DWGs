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
#ifndef ODGI_SHELLTOOLKIT_H_INCLUDED
#define ODGI_SHELLTOOLKIT_H_INCLUDED

#include "OdVector.h"
#include "Ge/GeExtents3d.h"
#include "GiGeometry.h"

/** \details
  A class that provides an interface for operations with a shell. 
  <group OdGi_Classes>
  \sa 
  * <link tv_geometry_shells, Work with Shells>
  * <link tv_shell_boundary_detection, Shell Boundary Detection>
*/
class ODGI_EXPORT OdGiShellToolkit : public OdRxObject
{
public:
  
  /** \details
    Contains declarations that represent options for shell management.
  */
  enum ShellToolkitOption
  {
    /** Combines vertices with the same coordinates into one vertex.*/
    kUnifyVertices = 1,
    /** Automatically triangulates faces if a shell has holes.*/
    kTriangulateHoles = 1 << 1,
    /** Automatically triangulates all faces.*/
    kForceTriangulation = 1 << 2,
    /** Keeps holes and non-triangle faces in the model representation.*/
    kKeepInitialData = 1 << 3
  };
  
  /** \details
    This class implements a callback mechanism for face orientation.
  */
  class ODGI_EXPORT OdGiShellFaceOrientationCallback
  {
  public:
    
    /** \details
      Checks the face orientation.
      
      \param pts  [in] An array of vertices that is represented with a pointer to the first element of the array.
      \param face [in] A pointer to the first element of the array of faces.
      \returns The true value if the face orientation is correct; otherwise, it returns false.
      \remarks
      The default implementation always returns true and can be used to check whether all faces are oriented in the same way.
    */
    virtual bool isFaceOrientedCorrectly( const OdGePoint3d* pts, const OdInt32* face ) const
    {
      return true;
    }
  };
  
  /** \details
    A structure that describes an original face.
  */
  struct ODGI_EXPORT OdGiShellOriginalFaceDescription
  {
    /** The number of shells. This value corresponds to the number of times the  <link OdGiShellToolkit::addShell@OdUInt32@const_OdGePoint3d*@OdUInt32@const_OdInt32*@OdUInt8, addShell()> 
    method of the appropriate <link OdGiShellToolkit, OdGiShellToolkit> object was called.*/
    OdUInt32 nShell;
    /** The face offset in the original data.*/
    OdUInt32 nOffset;
  };
  
  /** \details
    A structure that describes a face within a <link OdGiShellToolkit, shell toolkit> object.
  */
  struct ODGI_EXPORT OdGiShellFaceDescription
  {
    /** An offset for the face in the face list (this list can be retrieved by using the <link OdGiShellToolkit::faceList@const, faceList()> method 
    of the <link OdGiShellToolkit, OdGiShellToolkit> object).*/
    OdUInt32 nOffset;
  };
  
  /** \details
    A structure that describes an edge within a <link OdGiShellToolkit, shell toolkit> object.
  */
  struct ODGI_EXPORT OdGiShellEdgeDescription
  {
    /** An instance of the corresponding <link OdGiShellToolkit::OdGiShellFaceDescription, face description>.*/
    OdGiShellFaceDescription face;
    /** A face edge index.*/
    OdUInt32 nEdge;
  };

  /** \details
  A structure that describes the edge visibility within a <link OdGiShellToolkit, shell toolkit> object.
  */
  struct ODGI_EXPORT OdGiShellEdgeVisibilityDescription
  {
    /** An <link OdGiShellToolkit::OdGiShellEdgeDescription, edge description>.*/
    OdGiShellEdgeDescription edge;
    /** The edge visibility flag is equal to true if the edge is visible, and it is false otherwise.*/
    bool bVisible;
  };

  /** \details
  A structure that describes visibility generation options for an edge within a <link OdGiShellToolkit, shell toolkit> object.
  */
  struct ODGI_EXPORT OdGiShellEdgeVisibilityOptions
  {
    /** A flag that indicates whether edge visibility options are duplicated according to the number of faces that pass it.*/
    bool bDuplicateEdges;
    /** A flag that indicates whether only invisible edges appear in the result.*/
    bool bVisibleOnly;
    /** A flag that indicates whether flat holes appear in the result.*/
    bool bIgnoreFlatHoles;
    
    /** \details
    Creates a new instance of the <link OdGiShellToolkit::OdGiShellEdgeVisibilityOptions, OdGiShellEdgeVisibilityOptions> structure.
    */
    OdGiShellEdgeVisibilityOptions() : bDuplicateEdges( false ), bVisibleOnly( true ), bIgnoreFlatHoles( false ){}
    
    /** \details
    Creates a new instance of the <link OdGiShellToolkit::OdGiShellEdgeVisibilityOptions, OdGiShellEdgeVisibilityOptions> 
    structure with specified parameters.
    \param bDuplicate   [in] A value of the flag that indicates whether edge visibility options are duplicated according to the number of faces that pass it.
    \param bVisible     [in] A value of the flag that indicates whether only invisible edges appear in the result.
    \param bNoFlatHoles [in] A value of the flag that indicates whether flat holes appear in the result.
    */
    OdGiShellEdgeVisibilityOptions( bool bDuplicate, bool bVisible, bool bNoFlatHoles = false ) : bDuplicateEdges( bDuplicate ), bVisibleOnly( bVisible ), bIgnoreFlatHoles( bNoFlatHoles ) {}
  };

  ODRX_DECLARE_MEMBERS( OdGiShellToolkit );
  
  /** \details 
    Creates an instance of a <link OdGiShellToolkit, shell toolkit> implementation.
    \returns A smart pointer to the toolkit implementation.
  */
  static OdSmartPtr<OdGiShellToolkit> create();
  
  /** \details
    Adds a shell to the <link OdGiShellToolkit, shell toolkit> object.
    \param nPoints [in] The number of vertices.
    \param pPoints [in] An array of vertices that is represented with a pointer to its first element.
    \param nFaces  [in] The size of the face list.
    \param pFaces  [in] A face list. Each face is described with the number of vertices and indices from the vertex array (its size is equal to the number of vertices + 1).
    \param options [in] A byte value that contains <link OdGiShellToolkit::ShellToolkitOption, shell toolkit options>.
    \returns The true value if shell data is successfully added to the toolkit model; otherwise, it returns false.
    \remarks 
    * If the <link OdGiShellToolkit::ShellToolkitOption::kUnifyVertices, kUnifyVertices> option is enabled, only vertices from the specified shell are unified; 
    vertices from previously added shell data are not modified.
    * The <link OdGiShellToolkit::ShellToolkitOption::kForceTriangulation, kForceTriangulation> option includes the 
    <link OdGiShellToolkit::ShellToolkitOption::kTriangulateHoles, kTriangulateHoles> option, so if it is enabled, 
    the <link OdGiShellToolkit::ShellToolkitOption::kTriangulateHoles, kTriangulateHoles> option is not required.
    * If the <link OdGiShellToolkit::ShellToolkitOption::kTriangulateHoles, kTriangulateHoles> and 
    <link OdGiShellToolkit::ShellToolkitOption::kForceTriangulation, kForceTriangulation> options are disabled, holes are not supported.
    * The <link OdGiShellToolkit::ShellToolkitOption::kKeepInitialData, kKeepInitialData> option guarantees that the number of faces and vertices are not modified. 
    This option disables other options and limits toolkit functionality. Also, this option is specified only when processing a single shell.
  */
  virtual bool addShell( OdUInt32 nPoints, const OdGePoint3d* pPoints, OdUInt32 nFaces, const OdInt32* pFaces, OdUInt8 options = OdGiShellToolkit::kTriangulateHoles ) = 0;
  
  /** \details
    Clears the <link OdGiShellToolkit, shell toolkit> object.
  */
  virtual void clear() = 0;
  
  /** \details
    Checks whether a shell contains duplicate vertices.
    
    \returns The true value if the shell contains at least one pair of vertices with the same coordinates; otherwise, it returns false.
  */
  virtual bool hasDupilcateVertices() const = 0;
  
  /** \details
    Checks whether a shell contains sharp edges.
    
    \param bOnlyCount [in]  A flag that specifies whether the toolkit checks only the number of connected faces (when it is equal to true) 
                            or considers the face orientation as well (when it is equal to false).
    \returns An unsigned 32-bit integer value that contains the number of sharp edges.
  */
  virtual OdUInt32 numSharpEdges( bool bOnlyCount = true ) const = 0;
  
  /** \details
    Checks whether a shell contains singular edges.
    
    \param bOnlyCount [in] A flag that specifies whether the toolkit checks only the number of connected faces (when it is equal to true) 
                           or considers the face orientation as well (when it is equal to false).
    \returns An unsigned 32-bit integer value that contains the number of singular edges.
  */
  virtual OdUInt32 numSingularEdges( bool bOnlyCount = true ) const = 0;
  
  /** \details
    Checks whether a shell contains degenerate faces.
    
    \returns An unsigned 32-bit integer value that contains the number of degenerate faces.
  */
  virtual OdUInt32 numDegeneratedFaces() const = 0;
  
  /** \details
    Checks whether a shell contains duplicate faces.
    
    \param pFirstDuplicateFace [out] A pointer to the first duplicate face.
    \param bRollFaces          [in] A flag that specifies whether the toolkit should roll faces to check for duplicates.
    \returns The true value when the shell contains duplicate faces; otherwise, it returns false.
    \remarks
    Faces like &quot;1-2-3&quot; and &quot;2-3-1&quot; are not equal without rolling.
  */
  virtual bool hasDuplicateFaces( OdUInt32* pFirstDuplicateFace = NULL, bool bRollFaces = false ) const = 0;
  
  /** \details
    Checks the face orientations of a shell.
    
    \returns The true value when all faces are correctly oriented.
    \remarks
    The method is not relevant if the shell contains sharp or singular edges.
  */
  virtual bool checkFacesOrientation() const = 0;
  
  /** \details
    Checks the face orientations of a shell using a face orientation callback.
    
    \param pCallback [in] A pointer to an <link OdGiShellToolkit::OdGiShellFaceOrientationCallback, OdGiShellFaceOrientationCallback> object.
    \returns The true value when all faces are correctly oriented.
    \remarks
    The method is relevant when the shell contains sharp or singular edges, 
    and it can be used instead of the <link OdGiShellToolkit::checkFacesOrientation@const, checkFacesOrientation()> method.
  */
  virtual bool checkFacesOrientation( const OdGiShellFaceOrientationCallback* pCallback ) const = 0;
  
  /** \details
    Unifies shell vertices.
  */
  virtual void unifyVertices() = 0;
  
  /** \details
    Removes degenerate faces.
  */
  virtual void removeDegenerateFaces() = 0;
  
  /** \details
    Removes duplicate faces.
    
    \param bRollFaces [in] A flag that specifies whether the toolkit should roll faces to check for duplicates.
    \remarks
    Faces like &quot;1-2-3&quot; and &quot;2-3-1&quot; are not equal without rolling.
  */
  virtual void removeDuplicateFaces( bool bRollFaces = false ) = 0;
  
  /** \details
    Orients shell faces correctly.
    
    \param bRestoreModel [in] A flag that specifies whether the toolkit should restore the internal shell model.
    \returns The true value when orientation correction is successful; otherwise, it returns false.
    \remarks
    * The method is not relevant if the shell contains sharp or singular edges.
    * After face reorientation, the internal shell model becomes invalid. 
      However, usually face reorientation is the last operation, so restoring the model may not be necessary.
    * Further <link OdGiShellToolkit, toolkit> object usage after the <link OdGiShellToolkit::fixFaceOrientation@bool, fixFaceOrientation>(false) call without calling the 
      <link OdGiShellToolkit::clear, clear()> method generates incorrect results.
  */
  virtual bool fixFaceOrientation( bool bRestoreModel = true ) = 0;
  
  /** \details
    Orients shell faces correctly using a face orientation callback.
    
    \param pCallback     [in] A pointer to the <link OdGiShellToolkit::OdGiShellFaceOrientationCallback, OdGiShellFaceOrientationCallback> object.
    \param bRestoreModel [in] A flag that specifies whether the toolkit should restore the internal shell model.
    \returns The true value when orientation correction is successful; otherwise, it returns false.
    \remarks
    * The method is relevant if the shell contains sharp or singular edges, and it can be used instead of the 
      <link OdGiShellToolkit::fixFaceOrientation@bool, fixFaceOrientation()> method.
    * After face reorientation, the internal shell model becomes invalid. 
      However, usually face reorientation is the last operation, so restoring the model may not be necessary.
    * Further <link OdGiShellToolkit, toolkit> object usage after the <link OdGiShellToolkit::fixFaceOrientation@bool, fixFaceOrientation>(false) call without calling the 
      <link OdGiShellToolkit::clear, clear()> method generates incorrect results.
  */
  virtual bool fixFaceOrientation( const OdGiShellFaceOrientationCallback* pCallback, bool bRestoreModel = true ) = 0;
  
  /** \details
    Retrieves the tolerance for the <link OdGiShellToolkit, shell toolkit> object.
    
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGeTol.html">OdGeTol</exref> object that contains the <link OdGiShellToolkit, shell toolkit> tolerance.
    \remarks 
    The <exref target="https://docs.opendesign.com/tkernel/OdGeTol.html">OdGeTol</exref> object is returned via reference; 
    therefore, the tolerance value can be modified outside the <link OdGiShellToolkit, shell toolkit> object.
  */
  virtual OdGeTol& tolerance() = 0;
  
  /** \details
    Retrieves the tolerance access for the <link OdGiShellToolkit, shell toolkit> object.
    
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGeTol.html">OdGeTol</exref> object that contains the <link OdGiShellToolkit, shell toolkit> tolerance.
  */
  virtual const OdGeTol& tolerance() const = 0;
  
  /** \details
    Requests the number of vertices from the <link OdGiShellToolkit, shell toolkit> object.
    \returns An unsigned 32-bit integer that contains the number of vertices.
  */
  virtual OdUInt32 numVertices() const = 0;
  
  /** \details
    Requests the array of shell vertices from the <link OdGiShellToolkit, shell toolkit> object.
    \returns A pointer to the first <exref target="https://docs.opendesign.com/tkernel/OdGePoint3d.html">element</exref> of the vertex array.
  */
  virtual const OdGePoint3d* vertices() const = 0;
  
  /** \details
    Requests the size of the face list from the <link OdGiShellToolkit, shell toolkit> object.
    
    \returns An unsigned 32-bit integer value that contains the face list size.
  */
  virtual OdUInt32 faceListSize() const = 0;
  
  /** \details
    Requests the face list from the <link OdGiShellToolkit, shell toolkit> object.
    The face list contains the number of vertices in the first element and indices of vertices that belong to the face in other elements. 
    Vertex indices refer to the elements of the shell vertex array.
    \returns A pointer to the first element of the face list.
  */
  virtual const OdInt32* faceList() const = 0;
  
  /** \details
    Retrieves the sharp edges of the shell.
    
    \param edges              [out] An array of <link OdGiShellToolkit::OdGiShellEdgeDescription, OdGiShellEdgeDescription> objects. The method fills this array with information about sharp edges and returns it to the calling subroutine.
    \param bOnlyCount         [in] A flag value that specifies whether the toolkit checks only the number of connected faces or considers face orientation as well.
    \param bIgnoreZeroHoldes  [in] A flag value that indicates whether flat holes are included in the result array.

    \remarks
    A flat hole is a closed contour that consists of sharp edges that are parallel to each other.
  */
  virtual void getSharpEdges( OdArray< OdGiShellEdgeDescription >& edges, bool bOnlyCount = true, bool bIgnoreZeroHoldes = false ) const = 0;
  
  /** \details
    Retrieves the singular edges of the shell.
    
    \param edges      [out] An array of <link OdGiShellToolkit::OdGiShellEdgeDescription, OdGiShellEdgeDescription> objects. The method fills this array with information about singular edges and returns it to the calling subroutine.
    \param bOnlyCount [in] A flag value that specifies whether the toolkit checks only the number of connected faces or considers face orientation as well.
  */
  virtual void getSingularEdges( OdArray< OdGiShellToolkit::OdGiShellEdgeDescription >& edges, bool bOnlyCount = true ) const = 0;
  
  /** \details
    Retrieves incorrectly oriented faces.
    
    \param faces           [out] An array of <link OdGiShellToolkit::OdGiShellFaceDescription, OdGiShellFaceDescription> objects. 
                                 The method fills this array with information about incorrectly oriented faces and returns it to the calling subroutine.
    \param bAddNotOriented [in] A flag value that specifies whether the toolkit also includes non-oriented faces in the resulting array.
  */
  virtual void getIncorrectOrientedFaces( OdArray< OdGiShellFaceDescription >& faces, bool bAddNotOriented = true ) const = 0;
  
  /** \details
    Provides access to incorrectly oriented faces.
    
    \param pCallback       [in] A pointer to an <link OdGiShellToolkit::OdGiShellFaceOrientationCallback, OdGiShellFaceOrientationCallback> object.
    \param faces           [out] An array of <link OdGiShellToolkit::OdGiShellFaceDescription, OdGiShellFaceDescription> objects. 
                                 The method fills this array with information about incorrectly oriented faces and returns it to the calling subroutine.
    \param bAddNotOriented [in] A flag value that specifies whether the toolkit also includes non-oriented faces in the resulting array.
  */
  virtual void getIncorrectOrientedFaces( const OdGiShellFaceOrientationCallback* pCallback, OdArray< OdGiShellFaceDescription >& faces, bool bAddNotOriented = true ) const = 0;
  
  /** \details
    Provides access to the original face description.
    
    \param nFaceOffset  [in] An offset of the face in the face list
                             (that is returned by the <link OdGiShellToolkit::faceList@const, faceList(), faceList()> method).
    \param result       [out] A reference to an <link OdGiShellToolkit::OdGiShellOriginalFaceDescription, OdGiShellOriginalFaceDescription> object that contains the face description.
                              The method fills this object with information about the face and returns it to the calling subroutine.
    \returns A Boolean value that is equal to true if the original face description is found; otherwise, the method returns false.
  */
  virtual bool getOriginalFaceDescription( OdUInt32 nFaceOffset, OdGiShellOriginalFaceDescription& result ) const = 0;
  
  /** \details
    Generates a list of edges with a crease angle that exceeds the threshold value.
    
    \param edges  [out] An array of <link OdGiShellToolkit::OdGiShellEdgeDescription, OdGiShellEdgeDescription> objects.
                        The method fills this array with information about edges and returns it to the calling subroutine.
    \param dAngle [in] The threshold value of the crease angle.
    \remarks
    The method returns pairs of <link OdGiShellToolkit::OdGiShellEdgeDescription, OdGiShellEdgeDescription> objects; 
    each pair describes the same edge but on different faces.
  */
  virtual void filterEdgesByCreaseAngle( OdArray< OdGiShellToolkit::OdGiShellEdgeDescription >& edges, double dAngle ) const = 0;
  
  /** \details
    Requests the number of non-degenerated, non-triangulated faces.    
    \returns An unsigned 32-bit integer value that contains the number of faces with more than three points.
  */
  virtual OdUInt32 numNonTriangleFaces() const = 0;
  
  /** \details
    Triangulates non-degenerated, non-triangulated faces.
  */
  virtual void triangulate() = 0;

  /** \details
    Calculates face normals for the shell.

    \param normals [out]  An array that stores face normals (represented with 
    <exref target="https://docs.opendesign.com/tkernel/OdGeVector3d.html">OdGeVector3d</exref> objects).

    \returns A Boolean value that is equal to true if all calculated normals are non-zero; otherwise, the method returns false.

    \remarks
    * This method calculates face normals according to the face plane and the face orientation. 
    * A normal index matches the face in the face list. 
    * A normal can be zero when the face is degenerated or not flat.
  */
  virtual bool calculateFaceNormals( OdArray< OdGeVector3d >& normals ) const = 0;

  /** \details
    Calculates vertex average normals for the shell.

    \param normals [out] An array that stores the calculation results
                        (normals are represented with <exref target="https://docs.opendesign.com/tkernel/OdGeVector3d.html">OdGeVector3d</exref> objects).

    \returns A Boolean value that is equal to true if all calculated normals are non-zero; otherwise, the method returns false.

    \remarks
    * A normal index matches the vertex index in the vertex list.
    * A normal being calculated as normalized is the sum of all face normals that contain vertices.
    * A normal can be zero if a vertex is isolated or faces are not oriented in the same direction.
  */
  virtual bool calculateAverageVertexNormals( OdArray< OdGeVector3d >& normals ) const = 0;

  /** \details
    A data type that represents a pointer to a callback function for vertex normal calculation within custom applications.

    \param pToolkit     [in] A pointer to the current <link OdGiShellToolkit, shell toolkit> instance.
    \param nVertexIndex [in] An index of the vertex that is being processed.

    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGeVector3d.html">OdGeVector3d</exref> object that represents the vertex normal.

    \remarks
    The implementation of the callback function must provide a normalized non-zero result.
  */
  typedef OdGeVector3d( *OdGiCalculateNormalCallback )( OdGiShellToolkit* pToolkit, OdUInt32 nVertexIndex );

  /** \details
    Calculates vertex average normals for the shell.

    \param normals          [out] An array that stores the calculation results
                                  (normals are represented with <exref target="https://docs.opendesign.com/tkernel/OdGeVector3d.html">OdGeVector3d</exref> objects).
    \param creaseAngelLimit [in] A crease angle limit.
    \param pCallback        [in] A pointer to the callback function for the custom normal calculation (NULL by default).

    \returns A Boolean value that is equal to true if all calculated normals are non-zero; otherwise, the method returns false.

    \remarks
    * A normal index matches the vertex index in the vertex list.
    * A normal being calculated as normalized is the sum of all face normals that contain a vertex only if all angles between the face normals are less than the specified limit value.
      Otherwise, the callback function is called to calculate the normal. If the callback function is not specified, a zero normal for the vertex is returned.
    * A normal can be zero when the vertex is isolated or faces are not oriented in the same direction. It can also be zero when the angle between the face normals is greater than the specified limit value and the callback function is not specified.

  */
  virtual bool calculateAverageVertexNormals( OdArray< OdGeVector3d >& normals, double creaseAngelLimit, OdGiCalculateNormalCallback pCallback = NULL ) const = 0;
  
  /** \details
    Calculates the visibility of the shell edges according to the crease angle.
    \param visibilities   [out] An array of Boolean values that contain edge visibility flag values.
                                The method fills it with visibility flag values and returns it to the calling subroutine.
    \param creaseAngle    [in]  A crease angle limit.

    \returns The true value if the visibility flag values for edges are successfully calculated; otherwise, the method returns false.
    \remarks
    * Sharp and singular edges are visible. 
    * Edges with an angle between connected face normals that is greater than the crease angle are visible too.
    * For a single shell, the method generates a ready-to-use array of visibility flag values.
    */
  virtual bool calculateEdgeVisibilitiesByCreaseAngle( OdArray< bool >& visibilities, double creaseAngle ) const = 0;

  /** \details
  Calculates the visibility of the shell edges according to the crease angle.
  \param visibilities     [out] An array of Boolean values that contain edge visibility flag values.
                                The method fills it with visibility flag values and returns it to the calling subroutine.
  \param creaseAngle      [in]  A crease angle limit.
  \param options          [in]  <link OdGiShellToolkit::OdGiShellEdgeVisibilityOptions, Visibility generation options>.

  \returns The true value if the visibility flag values for edges are successfully calculated; otherwise, the method returns false.
  \remarks
  * Sharp and singular edges are visible. 
  * Edges with an angle between connected face normals that is greater than the crease angle are visible too.
  * For multi-shell cases, the method generates data that contains connections with the original input.
  * When two faces have a common visible edge, its visibility is represented in the output array with a single value if the 
    <link OdGiShellToolkit::OdGiShellEdgeVisibilityOptions::bDuplicateEdges, bDuplicateEdges option> is equal to false; 
    otherwise, the visibility is represented with two values (for AB and BA edges).
  */
  virtual bool calculateEdgeVisibilitiesByCreaseAngle( OdArray< OdGiShellEdgeVisibilityDescription >& visibilities, double creaseAngle, const OdGiShellEdgeVisibilityOptions& options = OdGiShellEdgeVisibilityOptions() ) const = 0;
};
/** \details
  A data type that represents a smart pointer to an <link OdGiShellToolkit, OdGiShellToolkit> object.
*/
typedef OdSmartPtr<OdGiShellToolkit> OdGiShellToolkitPtr;

#endif


