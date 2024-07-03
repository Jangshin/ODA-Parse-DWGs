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

#ifndef _FLATTENEDVIEWSHELPER_DEFINED
#define _FLATTENEDVIEWSHELPER_DEFINED

#include "DbSectionHLRHelper.h"
#include "DbHatch.h"

/** \details
  This struct contains entyty symbology (layer, color, line type, line weight, line type scale and transparency).

  <group OdDb_Classes>
*/
struct DBENT_EXPORT OdDbHLRCurveProperties
{
  OdDbHLRCurveProperties();
  void applyToEntity(OdDbEntity* pEnt, const OdDbDatabase* pDb) const;
  OdDbObjectId     idLayer;
  OdCmColor        color;
  OdDb::LineWeight lineWeight;
  OdDbObjectId     idLineType;
  double           dLineTypeScale;
  OdCmTransparency transparency;
};

//====================================================================================================

/** \details
  This struct contains hatch pattern and curve properties for secdtoion hatch geometry.

  <group OdDb_Classes>
*/
struct DBENT_EXPORT OdDbSectionHatchPatternSettings
{
  OdDbSectionHatchPatternSettings();
  OdDbHLRCurveProperties      hatchCurveProperties;
  OdString                    strPatternName;
  OdDbHatch::HatchPatternType patternType;
  OdHatchPattern              userDefinedPattern;
  double                      dPatternAngle;
  double                      dPatternScale;
};

//====================================================================================================

/** \details
  This class implements wrapper of helper to create flatterned and section geometry by
  hidden line remover and section modeller.

  <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbFlattenViewsHelper
{
  public:
    /** \details
      Constructor of OdDbFlattenViewsHelper.

      \param pDb [in] database to initialize defaults for section and flattened view geometry.
    */
    OdDbFlattenViewsHelper( OdDbDatabase* pDb );

    /** \details
      Destructor of OdDbFlattenViewsHelper.
    */
    virtual ~OdDbFlattenViewsHelper();

    /** \details
      Returns database to initialize flattened and section geometry after creation.
    */
    OdDbDatabase* database() const;

    /** \details
      Set projection direction and section plane to create flattened and section geometry.

      \param ptBase [in]  Base point to define section plane.
      \param vrDir [in]  Normal vector of section plane and direction for flattened view and section creation.
      \param vrUp [in]  Up vector direction for flattened view and section creation.

      \remarks
      Returns eInvalidInput if direction vector is zero length or up vector is not perpendicular to 
      direction vector. Otherwise returns eOk.
    */
    OdResult          setProjectionPlane(const OdGePoint3d& ptBase, const OdGeVector3d& vrDir, const OdGeVector3d& vrUp);

    /** \details
      Returns base point to define section plane.
    */
    OdGePoint3d   projectionBase() const;

    /** \details
      Returns normal vector of section plane and direction for flattened view and section creation.
    */
    OdGeVector3d  projectionDirection() const;

    /** \details
      Returns up vector direction for flattened view and section creation.
    */
    OdGeVector3d  projectionUp() const;

    /** \details
      Returns include tangental edges flag.
    */
    bool          includeTangentalEdgesFlag() const;

    /** \details
      Set include tangental edges flag.
    */
    void          setIncludeTangentalEdgesFlag(bool bSet);

    /** \details
      Set tangential edges angle.

      \param dAngle [in]  The specified angle.
    */
    void          setTangentalEdgesAngle(double dAngle);

    /** \details
      Set entities to create flattened and section geometry.

      \param arr3dObjects [in]  Array of object ids to be used in construction flattened view or section geometry.

      \remarks
      Returns eInvalidInput if no one entity from array is supported. Otherwise returns eOk.
      Method skip all non-supported entities.
    */
    OdResult      setEntities(const OdDbObjectIdArray& arr3dObjects);

    /** \details
      Returns array of entity ids to create flattened views and section geometry.
    */
    const OdArray<OdDbObjectId>& getEntities() const;

    /** \details
      Returns 3d object extents of supported entity ids.
    */
    OdGeExtents3d getExtents() const;

    /** \details
     Calculate flattened views and section geometry.

     \param bCreateSection [in] Use section plane to cut 3d objects and create section hatches.
     \param bCreateHiddenLines [in] Create hidden line geometry.

      \remarks
     Returns eNotInitializedYet if no one entity was set to helper. Otherwise returns eOk.
    */
    OdResult      createSectionHLR(bool bCreateSection, bool bCreateHiddenLines);

    /** \details
     Apply symbology and hatch pattern settings to section and flattened view geometry and 
     add it to block table record.

     \param pOwner [in] Pointer to block table record to add section and flattened view geometry.
     \param matTransform [in] Additional transformation to be applied to section and flattened view geometry.

      \remarks
     Returns eNullObjectPointer if block table record pointer is NULL,
     eWrongDatabase if block table record database and internal helper database is not initialized,
     eNotInitializedYet if no one entity was set to helper. Otherwise returns eOk.
     If database of layer or line type from symbology differs of database of block table record the
     layer and the line type will be wblock cloned to database of block table record.
    */
    OdResult      addToBlock(OdDbBlockTableRecord* pOwner, const OdGeMatrix3d& matTransform = OdGeMatrix3d::kIdentity);

    /** \details
      Returns visible edges geometry properties.
    */
    const OdDbHLRCurveProperties& foregroundCurveProperties() const;

    /** \details
      Set visible edges geometry curve properties.

      \param curveSymb [in] visible edges curve properties
    */
    void               setForegroundCurveProperties(const OdDbHLRCurveProperties& curveProp);

    /** \details
      Returns hidden edges geometry curve properties.
    */
    const OdDbHLRCurveProperties& obscuredCurveProperties() const;

    /** \details
      Set hidden edges geometry curve properties.

      \param curveSymb [in] hidden edges curve properties.
    */
    void               setObscuredCurveProperties(const OdDbHLRCurveProperties& curveProp);

    /** \details
      Returns section hatch settings.
    */
    const OdDbSectionHatchPatternSettings& sectionHatchSettings() const;

    /** \details
      Set section hatch settings.

      \param patternSettings [in] section hatch settings.
    */
    void               setSectionHatchSettings(const OdDbSectionHatchPatternSettings& patternSettings);

    /** \details
     Returns non-dbro hatches of created by createSectionHLR method section.

     \param arrHatches [out] result entities.
     \param bSetProperties [in] set hatch pattern settings to section hatches.

      \remarks
     Returns false if section geometry was not created.
    */
    bool          getSectionHatches(OdRxObjectPtrArray& arrHatches, bool bSetProperties) const;

    /** \details
     Returns non-dbro hidden line geometry of created by createSectionHLR method flattened view geometry.

     \param arrHiddenLines [out] result entities.
     \param bSetProperties [in] set curve properties to hidden geometry.

      \remarks
     Returns false if flattened view geometry was not created.
    */
    bool          getHiddenLines(OdRxObjectPtrArray& arrHiddenLines, bool bSetProperties) const;

    /** \details
     Returns non-dbro visible line geometry of created by createSectionHLR method flattened view geometry.

     \param arrVisibleLines [out] result entities.
     \param bSetProperties [in] set curve properties to visible geometry.

      \remarks
     Returns false if flattened view geometry was not created.
    */
    bool          getVisibleLines(OdRxObjectPtrArray& arrVisibleLines, bool bSetProperties) const;

private:
  OdDbSectionHLRHelperPtr         m_pSectionHLRHelper;
  OdDbHLRCurveProperties          m_foregroundProperties;
  OdDbHLRCurveProperties          m_obscuredProperties;
  OdDbSectionHatchPatternSettings m_sectionHatchSettings;
};

//////////////////////////////////////////////////////////////////////////

#endif  /* _FLATTENEDVIEWSHELPER_DEFINED */
