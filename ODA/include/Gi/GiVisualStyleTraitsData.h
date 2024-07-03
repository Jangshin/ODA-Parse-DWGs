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

#ifndef __OD_GI_VISUALSTYLE_TRAITS_DATA__
#define __OD_GI_VISUALSTYLE_TRAITS_DATA__

#include "TD_PackPush.h"

#include "Gi/GiVisualStyleData.h"
#include "TPtr.h"

/** \details
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
*/
class OdGiVisualStyleTraitsData
{
  TPtr<OdGiVisualStyleDataContainer, TObjDelete<OdGiVisualStyleDataContainer>> m_pVisualStyleData;
  const OdGiVisualStyle *m_pRawVisualStylePtr; // Do not access raw pointer data directly.

public:

  /** \details
    Default constructor for the OdGiVisualStyleTraitsData class. Initializes the smart pointer to the associated visual style to NULL.
  */
  OdGiVisualStyleTraitsData(bool bPhysicalCopy = true)
    : m_pVisualStyleData(NULL)
    , m_pRawVisualStylePtr(NULL)
  { if (bPhysicalCopy) m_pVisualStyleData = new OdGiVisualStyleDataContainer; }

  /** \details
    Sets visual style.
    \param visualStyle [in]  Visual style to set.
  */
  void setOdGiVisualStyle(const OdGiVisualStyle& visualStyle)
  {
    m_pRawVisualStylePtr = &visualStyle;
    if (!m_pVisualStyleData.isNull())
      static_cast<OdGiVisualStyle&>(*m_pVisualStyleData) = visualStyle;
  }

  /** \details
    Retrieves the visual style.
  */
  const OdGiVisualStyle& odgiVisualStyle() const
  {
    if (!m_pVisualStyleData.isNull())
      return *m_pVisualStyleData;
    return *m_pRawVisualStylePtr;
  }

  /** \details
    Checks whether visual style is set.
    \returns
    true if pointer to the associated visual style is not NULL, false otherwise.
  */
  bool isOdGiVisualStyleSet() const
  {
    return m_pRawVisualStylePtr != NULL;
  }
  /** \details
    Resets visual style.
  */
  void resetOdGiVisualStyle()
  {
    m_pRawVisualStylePtr = NULL;
  }

  /** \details
    Equality operator for the OdGiVisualStyleTraitsData class.
    The objects are considered equal if both visual styles are set
    and refer to the same visual style, or if both are not set.
    
    \param data2 [in]  Object to compare.
    \returns
    true if object are equal, false otherwise.
  */
  bool operator ==(const OdGiVisualStyleTraitsData &data2) const
  {
    return (isOdGiVisualStyleSet() == data2.isOdGiVisualStyleSet()) &&
           (!isOdGiVisualStyleSet() || (odgiVisualStyle() == data2.odgiVisualStyle()));
  }

  /** \details
    Inequality operator for the OdGiVisualStyleTraitsData class.
    The objects are considered not equal if the equality operator returns false.
    
    \param data2 [in]  Object to compare.
    \returns
    true if objects are not equal, false otherwise.
  */
  bool operator !=(const OdGiVisualStyleTraitsData &data2) const
  {
    return !(*this == data2);
  }

  /** \details
    Assigment operator of the OdGiVisualStyleTraitsData class.
  */
  OdGiVisualStyleTraitsData &operator =(const OdGiVisualStyleTraitsData &data2)
  {
    m_pRawVisualStylePtr = data2.m_pRawVisualStylePtr;
    if (m_pRawVisualStylePtr && !m_pVisualStyleData.isNull())
      static_cast<OdGiVisualStyle &>(*m_pVisualStyleData) = data2.odgiVisualStyle();
    return *this;
  }
};                          

#include "TD_PackPop.h"

#endif // __OD_GI_VISUALSTYLE_TRAITS_DATA__
