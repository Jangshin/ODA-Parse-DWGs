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


#ifndef __OD_GI_PATTERNATTRIBUTES__
#define __OD_GI_PATTERNATTRIBUTES__

#include "TD_PackPush.h"

#include "Gi/GiExport.h"

#include "Int32Array.h"
#include "Ge/GeDoubleArray.h"

#include "Ge/GePoint2dArray.h"
#include "Ge/GeVector2dArray.h"

#include "Ge/GePoint3dArray.h"

class OdGeMatrix3d;
class OdGeScale2d;

/** \details
    This class calculates arrays of pattern attributes for meshes and shells.

    <group OdGi_Classes>
*/
class ODGI_EXPORT OdGiPatternAttribs
{
public:
  /** \details
      Default constructor for the OdGiPatternAttribs class.
      Sets surface and transformation to NULL, swap flag to false and u derivative scale to 1.
    */
  OdGiPatternAttribs();

  /** \details
     Checks if pattern attributes arrays are empty.

     \remarks
     Returns true if some of arrays is empty.
   */
  bool isEmpty() const;

  /** \details
     Clears all pattern attributes arrays.
  */
  void clear();

  /** \details
     Calculates all patterns attributes arrays.

     \param pSrf             [in]  Surface.
     \param faceFillOrigin   [in]  Patterns origin.
     \param rotAngle         [in]  Global rotation angle for all patterns.
     \param basePts          [in]  Array of patterns base points.
     \param angles           [in]  Array of patterns angles.
     \param offsets          [in]  Array of pattern offsets.
     \param faceList         [in]  Array of integers defining triangles.
     \param vertexList       [in]  Array of mesh vertices.
     \param trMidPts         [in]  Array of mesh triangles middle points in parametric space (uv).
     \param annotationScales [in]  Array of annotation scales.
     \param globalScaleUv    [in]  Global scale for u and v parameters.
     \param swapUv           [in]  Swap u and v parameters flag.
     \param uDerScale        [in]  U derivative scale parameter.
     \param pTransfMx        [in]  Pointer to model to world transformation matrix.
     \remarks
    * The arrays basePts, angles, offsets and annotationScales must contain the same number of elements.
    * The array trMidPts must contain the same number as there are triangles.
    * The array vertexList must contain the same number as there are vertices.
     \remarks
    * The results are stored in arrays fillOriginArr, fillDirectionArr, fillOffsetDirectionArr,
      fillDashesScaleArr, fillOffsetScaleArr which have the size equal to angles.size() * faceList.logicalLength() / 4.
   */
  void calcAttribs(const OdGeSurface* pSrf, const OdGePoint2d& faceFillOrigin, double rotAngle,
                   const OdGePoint2dArray& basePts, const OdGeDoubleArray& angles, const OdGeVector2dArray& offsets,
                   const OdInt32Array& faceList, const OdGePoint3dArray& vertexList,
                   const OdGePoint2dArray& trMidPts, const OdGeDoubleArray& annotationScales,
                   const OdGeScale2d& globalScaleUv, bool swapUv, double uDerScale,
                   const OdGeMatrix3d* pTransfMx);

  /** \details
     Calculates angle between curves.

     \param pSrf      [in]  Surface.
     \param swapUv    [in]  Swap u and v parameters flag.
     \param uDerScale [in]  U derivative scale parameter.
     \param uvPt      [in]  Curves starting point in parametric space.
     \param dir       [in]  Second curve direction in parametric space.
     \param mirror    [in]  Mirror second curve direction flag.
     \returns
     Angle between curves on surface
     \remarks
    * First curve direction is (1, 0)
   */
  double calcAngleBetweenCurves(const OdGeSurface* pSrf, bool swapUv, double uDerScale, const OdGePoint2d& uvPt, const OdGeVector2d& dir, bool mirror);

  /** Array of patterns origins. */
  OdGePoint2dArray fillOriginArr;

  /** Array of patterns directions. */
  OdGeVector2dArray fillDirectionArr;

  /** Array of patterns offset directions. */
  OdGeVector2dArray fillOffsetDirectionArr;

  /** Array of patterns dashes directions scale. */
  OdGeDoubleArray fillDashesScaleArr;

  /** Array of patterns offset directions scale. */
  OdGeDoubleArray fillOffsetScaleArr;

private:

  void init(const OdGeSurface* pSrf, bool swapUv, double uDerScale, const OdGeMatrix3d* pTransfMx = NULL);

  void resize(unsigned int nTr, unsigned int nLines, const OdGePoint2d& orig, double rotAngle, double sc);

  bool calcAttribsInt(const OdGePoint2d& faceFillOrigin, double rotAngle,
                      const OdGePoint2dArray& basePts, const OdGeDoubleArray& angles, const OdGeVector2dArray& offsets,
                      const OdInt32Array& faceList, const OdGePoint3dArray& vertexList,
                      const OdGePoint2dArray& trMidPts, const OdGeDoubleArray& annotationScale,
                      const OdGeScale2d& scaleUv);

  OdGePoint3d srfEvalPoint(const OdGePoint2d& uvPt, OdGeVector3d& derU, OdGeVector3d& derV, OdGeVector3d* pNrml = NULL) const;

  OdGeCurve3d* srfMakeIsoparamCurve(bool byU, double param) const;

  double calcAngleBetweenCurvesIntMirror(const OdGePoint2d& uvPt, const OdGeVector2d& dir_, bool mirror, OdGeMatrix2d* pFffMx = NULL) const;
  double calcAngleBetweenCurvesInt(const OdGePoint2d& uvPt, const OdGeVector2d& dir, OdGeMatrix2d* pFffMx) const;

  bool isUnitScaling() const;

  const OdGeSurface* m_pSrf;
  double m_uDerScale;
  bool m_swapUv;

  const OdGeMatrix3d* m_pTransfMx;
};

#endif // __OD_GI_PATTERNATTRIBUTES__
