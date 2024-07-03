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

#ifndef OD_SECTIONSYMBOL_H
#define OD_SECTIONSYMBOL_H

#include "DbViewSymbol.h"
#include "TD_PackPush.h"

/** \details
    This class represents Section Symbol entities.

    Corresponding C++ library: AcModelDocObj
    <group OdModelDocObj_Classes> 
*/
class MODELDOCOBJ_EXPORT OdDbSectionSymbol : public OdDbViewSymbol
{
public:
  ODDB_DECLARE_MEMBERS(OdDbSectionSymbol);

  /** \details
    Default constructor. Creates an OdDbSectionSymbol instance.
  */
  OdDbSectionSymbol();
  ~OdDbSectionSymbol();

  /** \details
    Returns the number of points in the section line of this Section Symbol entity.
  */
  int sectionPointsCount() const;


  /** \details
    Gets the section line point at the specified index. 

    \param idx [in]  Index of the section line vertex.
    \param pt [out]  Receives the point at the index idx.

    \returns
    eOk value if successful, eOutOfRange if idx is out of range (idx > sectionPointsCount()).
  */
  OdResult getSectionPointAt(int idx, OdGePoint3d& pt) const;

  /** \details
    Gets the section vertex bulge parameter at the specified index. 

    \param idx [in]  Index of the section symbol vertex.
    \param bulge [out]  Receives the bulge at the index idx.

    \returns
    eOk value if successful, eOutOfRange if idx is out of range (idx > sectionPointsCount()).
  */
  OdResult getBulgeAt(int idx, double& bulge) const;

  /** \details
    Gets the identifier at the specified vertex index. 

    \param idx [in]  Index of the section symbol vertex.
    \param sName [out]  Receives the string that represents identifier.

    \returns
    eOk value if successful, eOutOfRange if idx is out of range (idx > sectionPointsCount()).
  */
  OdResult getIdentifierAt(int idx, OdString& sName) const;


  /** \details
    Gets the identifier offset value from the specified vertex. 

    \param idx [in]  Index of the section symbol vertex.
    \param offset [out]  Receives the offset value.
    \param pIsFixed [out] Optional flag indicating that identifier position is fixed.

    \returns
    eOk value if successful, eOutOfRange if  idx is out of range (idx > sectionPointsCount()).
  */
  OdResult getIdentifierOffsetAt(int idx, OdGeVector3d& offset, bool* pIsFixed = nullptr) const;

  /** \details
    Checks whether the view direction of the section symbol is left.

    \returns
    Returns true only if the view direction is left, and false otherwise.
  */
  bool isViewDirectionLeft() const;
  void setViewDirectionLeft(bool bLeft);

  /** \details
    Checks whether the section symbol defines a half or full section.

    \returns
    Returns true only if the section symbol defines a half section cut, false for full sections.
  */
  bool isHalfSection() const;
  void setIsHalfSection(bool bHalf);

  // Methods to use internal only :

  /** \details
    Appends new point of section line.

    \param pt [in]  Point of the section line.
    \param bulge [in]  Value of bulge.

    \returns
    eOk value if successful.
  */
  OdResult addSectionPoint(const OdGePoint3d& pt, double bulge = 0);

  /** \details
    Removes point of section line at specified index.

    \param idx [in]  Index of the section symbol point to remove.

    \returns
    eOk value if successful.
  */
  OdResult removeSectionPointAt(int idx);

  /** \details
    Modifies point by index.

    \param idx [in]  Index of the section symbol vertex.
    \param pt [in]  New value of point.
    \param bulge [in]  Value of bulge.

    \returns
    eOk value if successful, eOutOfRange if idx is out of range (idx > sectionPointsCount()).
  */
  OdResult setSectionPointAt(int idx, const OdGePoint3d& pt, double bulge = 0);

 /** \details
    Modifies identifier name by index.

    \param idx [in]  Index of the section symbol vertex.
    \param name [in]  Name of identifier.

    \returns
    eOk value if successful, eOutOfRange if idx is out of range (idx > sectionPointsCount()).
 */
  OdResult setIdentifierNameAt(int idx, const OdString & name);

 /** \details
    Modifies identifier offset by index.

    \param idx [in]  Index of the section symbol vertex.
    \param offset [in]  Value of identifier's offset.

    \returns
    eOk value if successful, eOutOfRange if idx is out of range (idx > sectionPointsCount()).
 */
  OdResult setIdentifierOffsetAt(int idx, const OdGeVector3d& offset);

protected:
  /** \details
      Notification from section view style. Invalidates Gs cache.
  */
  virtual void modified(const OdDbObject* pObject) ODRX_OVERRIDE;

  // OdDbObject methods :
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler) ODRX_OVERRIDE;
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const ODRX_OVERRIDE;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler) ODRX_OVERRIDE;
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const ODRX_OVERRIDE;

  // OdDbEntity methods :
  virtual void subSetDatabaseDefaults(OdDbDatabase* db, bool doSubents) ODRX_OVERRIDE;

  // OdGiDrawable methods :
  virtual bool subWorldDraw(OdGiWorldDraw* pWorldDraw) const ODRX_OVERRIDE;

  // OdDbEntity methods :
  virtual OdResult subTransformBy( const OdGeMatrix3d& xfm ) ODRX_OVERRIDE;

public:
  // Methods to use internal only :

  /** \details
    Sets section points.
  
    \param pts [in] Section points to set.
    \returns eOk - if successful, corresponding error type - otherwise.
  */
  OdResult setSectionPoints(const OdGePoint3dArray& pts);

  /** \details
    Sets section points.
  
    \param pts    [in] Section points to set.
    \param bulges [in] Bulges to set.
    \returns eOk - if successful, corresponding error type - otherwise.
    \remarks
      Currently is not implemented.
  */
  OdResult setSectionPoints(const OdGePoint3dArray& pts, const OdGeDoubleArray& bulges);

  /** \details
    Clears the section points.
  */
  void clearSectionPoints();

  /** \details
    Sets labels names.
  
    \param names [in] Names to set.
    \returns eOk - if successful, corresponding error type - otherwise.
    \remarks
      Currently is not implemented.
  */
  OdResult setLabelNames(const OdStringArray& names);

  /** \details
    Sets labels offsets.
  
    \param offsets [in] Offsets to set.
    \returns eOk - if successful, corresponding error type - otherwise.
  */
  OdResult setLabelOffsets(const OdGeVector3dArray& offsets);

  /** \details
    Resets labels offsets.
  
    \param bAllOffsets [in] true - for reset all, false - otherwise.
  */
  void resetLabelOffsets(bool bAllOffsets = true, int iVertex = -1);

  /** \details
    Flips direction of the section.
  
    \returns true - if successful, false - otherwise.
  */
  bool flipDirection();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbSectionSymbol object pointers.
*/
typedef OdSmartPtr<OdDbSectionSymbol> OdDbSectionSymbolPtr;

#include "TD_PackPop.h"

#endif // OD_SECTIONSYMBOL_H
