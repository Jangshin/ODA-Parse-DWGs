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

#ifndef __ODGI_DGLINETYPE_H__
#define __ODGI_DGLINETYPE_H__

#include "Gi/GiNonEntityTraits.h"
#include "Gi/GiLinetype.h"
#include "Gi/GiExport.h"

#include "TD_PackPush.h"

/** \details
    Represents a dash of a linetype.
    <group OdGi_Classes>
*/
struct OdGiDgLinetypeDash
{
  /** \details
    Represents information about a dash.
  */
  struct DashInfo
  {
    /** \details
      Represents width modes for a stroke.
    */
    enum StrokeWidthMode
    {
      /** Width settings are ignored. The stroke is displayed without width. */
      kLsNoWidth    = 0,
      /** The stroke is displayed with the specified widths. */
      kLsWidthLeft  = 1,
      /** Only the left half of the stroke is displayed with the specified widths. */
      kLsWidthRight = 2,
      /** Only the right half of the stroke is displayed with the specified widths. */
      kLsWidthFull  = 3
    };
    
    /** \details
      Represents caps types for start and end of a stroke.
    */
    enum StrokeCapsType
    {
      /** Caps are closed. */
      kLsCapsClosed   = 0,
      /** Caps are open. */
      kLsCapsOpen     = 1,
      /** Caps are extended. */
      kLsCapsExtended = 2,
      /** Caps are displayed as hexagons. */
      kLsCapsHexagon  = 3,
      /** Caps are displayed as octagons. */
      kLsCapsOctagon  = 4,
      /** Caps are displayed as decagons. */
      kLsCapsDecagon  = 5,
      /** Caps are displayed as arcs. */
      kLsCapsArc      = 30
    };
    
    /** \details
      Represents various flags for a stroke.
    */
    enum Flags
    {
      /** If true, the stroke is a dash, otherwise it is a gap. */
      kFlagDash                    = (1 << 0),
      /** If true, the stroke runs through the corner, otherwise it can be broken at element vertices. */
      kFlagPassCorner              = (1 << 1),
      /** If true, the stroke can be scaled by the linetype scale, otherwise it bypasses the vertex and continues straight to the nearest point on the element. */
      kFlagCanBeScaled             = (1 << 2),
      /** If true, the stroke is inverted in the first repetition of the stroke pattern (at the origin of the element). */
      kFlagInvertStrokeInFirstCode = (1 << 3),
      /** If true, the stroke is inverted in the last repetition of the stroke pattern (at the end of the element). */
      kFlagInvertStrokeInLastCode  = (1 << 4),
      /** If true, the stroke width is increasing towards stroke end. */
      kFlagIncreasingTaper         = (1 << 5),
      /** If true, the stroke width is decreasing towards stroke end. */
      kFlagDecreasingTaper         = (1 << 6),
      kFlagBaseStrokeDash          = (1 << 7)
    };

    /** Flags for a stroke. */
    OdUInt32        m_uFlags;
    /** Stroke length. */
    double          m_dLength;
    /** Stroke start width. */
    double          m_dStartWidth;
    /** Stroke end width. */
    double          m_dEndWidth;
    /** Stroke width mode. */
    StrokeWidthMode m_lsWidthMode;
    /** Stroke caps type. */
    StrokeCapsType  m_lsCapsType;

    /** \details
      Default constructor for the DashInfo structure.
    */
    DashInfo()
      : m_uFlags(0)
      , m_dLength(0.0)
      , m_dStartWidth(0.0)
      , m_dEndWidth(0.0)
      , m_lsWidthMode(kLsNoWidth)
      , m_lsCapsType(kLsCapsClosed)
    { }

    /** \details
      Returns the length of a stroke.
      \returns
      stroke length as double value.
    */
    double getLength() const { return m_dLength; }
    
    /** \details
      Sets the length of a stroke.

      \param dLength [in] Length of stroke.
    */
    void setLength(double dLength) { m_dLength = dLength; }

    /** \details
      Returns the start width of a stroke.
      \returns
      start width of a stroke as double value.
    */
    double getStartWidth() const { return m_dStartWidth; }
    
    /** \details
      Sets the start width of a stroke.

      \param dWidth [in] Width value in units.
    */
    void setStartWidth(double dWidth) { m_dStartWidth = dWidth; }

    /** \details
      Returns the end width of a stroke.
      \returns
      end width of a stroke as double value.
    */
    double getEndWidth() const { return m_dEndWidth; }
    
    /** \details
      Sets the end width of a stroke.

      \param dWidth [in] Width value in units.
    */
    void setEndWidth(double dWidth) { m_dEndWidth = dWidth; }

    /** \details
      Returns the dash flag of a stroke.

      \returns
      true if the stroke is dashed, or false if the stroke is a gap.
    */
    bool getDashFlag() const { return GETBIT(m_uFlags, kFlagDash); }
    
    /** \details
      Sets the dash flag of a stroke.

      \param bSet [in] Set to true for a dash, false for a gap.
    */
    void setDashFlag(bool bSet) { SETBIT(m_uFlags, kFlagDash, bSet); }

    /** \details
      Returns the bypass corner flag of a stroke.

      \returns
      false if the stroke can be broken at element vertices, true if it runs through the corner.
    */
    bool getByPassCornerFlag() const { return GETBIT(m_uFlags, kFlagPassCorner); }
    
    /** \details
      Sets the bypass corner flag of a stroke.

      \param bSet [in] Value of the flag. True - the stroke runs through the corner, false - the stroke is broken at element vertices.
    */
    void setByPassCornerFlag(bool bSet) { SETBIT(m_uFlags, kFlagPassCorner, bSet); }

    /** \details
      Returns the can-be-scaled flag of a stroke.

      \returns
      true if the stroke can be scaled by the linetype scale. 
      Otherwise the stroke bypasses the vertex and continues 
      straight to the nearest point on the element.
    */
    bool getCanBeScaledFlag() const { return GETBIT(m_uFlags, kFlagCanBeScaled); }
    
    /** \details
      Sets the can-be-scaled flag of a stroke.

      \param bSet [in] Value of the flag. True - the stroke can be scaled by the linetype scale, false - the stroke bypasses the vertex and continues straight to the nearest point on the element.
    */
    void setCanBeScaledFlag(bool bSet) { SETBIT(m_uFlags, kFlagCanBeScaled, bSet); }

    /** \details
      Returns the InvertStrokeInFirstCode flag of a stroke.

      \returns
      true if the stroke is inverted in the first repetition of 
      the stroke pattern (at the origin of the element), false otherwise.
    */
    bool getInvertStrokeInFirstCodeFlag() const { return GETBIT(m_uFlags, kFlagInvertStrokeInFirstCode); }
    
    /** \details
      Sets the InvertStrokeInFirstCode flag of a stroke.

      \param bSet [in] Value of the flag. True - the stroke is inverted in the first repetition of the stroke pattern (at the origin of the element), false - not inverted.
    */
    void setInvertStrokeInFirstCodeFlag(bool bSet) { SETBIT(m_uFlags, kFlagInvertStrokeInFirstCode, bSet); }

    /** \details
      Returns the InvertStrokeInLastCode flag of a stroke.

      \returns
      true if the stroke is inverted in the last repetition of 
      the stroke pattern (at the end of the element), false otherwise.
    */
    bool getInvertStrokeInLastCodeFlag() const { return GETBIT(m_uFlags, kFlagInvertStrokeInLastCode); }
    
    /** \details
      Sets the InvertStrokeInLastCode flag of a stroke.

      \param bSet [in] Value of the flag. True - the stroke is inverted in the last repetition of the stroke pattern (at the end of the element), false - not inverted.
    */
    void setInvertStrokeInLastCodeFlag(bool bSet) { SETBIT(m_uFlags, kFlagInvertStrokeInLastCode, bSet); }

    /** \details
      Returns the width mode of a stroke.

      \returns
      One of the following values:
      *kLsNoWidth - Width settings are ignored. The stroke is displayed without width.
      *kLsWidthFull - The stroke is displayed with the specified widths.
      *kLsWidthLeft - Only the left half of the stroke is displayed with the specified widths.
      *kLsWidthRight - Only the right half of the stroke is displayed with the specified widths.
    */
    StrokeWidthMode getWidthMode() const { return m_lsWidthMode; }
    
    /** \details
      Sets the width mode of a stroke.

      \param iMode [in] Width mode value.
      \remarks
      iMode parameter can have one of the following values:
      *kLsNoWidth - Width settings are ignored. The stroke is displayed without width.
      *kLsWidthFull - The stroke is displayed with the specified widths.
      *kLsWidthLeft - Only the left half of the stroke is displayed with the specified widths.
      *kLsWidthRight - Only the right half of the stroke is displayed with the specified widths.
    */
    void setWidthMode(StrokeWidthMode iMode) { m_lsWidthMode = iMode; }

    /** \details
      Returns the increasing taper flag of a stroke.

      \returns
      true if endWidth > startWidth, false otherwise.
    */
    bool getIncreasingTaperFlag() const { return GETBIT(m_uFlags, kFlagIncreasingTaper); }
    
    /** \details
      Sets the increasing taper flag of a stroke.

      \param bSet [in] Value of flag. True - width of a stroke is increasing towards dash end (endWidth > startWidth). If it is false and endWidth > startWidth, then endWidth = startWidth.
    */
    void setIncreasingTaperFlag(bool bSet) { SETBIT(m_uFlags, kFlagIncreasingTaper, bSet); }

    /** \details
      Returns the decreasing taper flag of a stroke.

      \returns
      true if startWidth > endWidth, false otherwise.
    */
    bool getDecreasingTaperFlag() const { return GETBIT(m_uFlags, kFlagDecreasingTaper); }
    
    /** \details
      Sets the decreasing taper flag of a stroke.

      \param bSet [in] Value of flag. True - width of a stroke is decreasing towards dash end (startWidth > endWidth). If it is false and startWidth > endWidth, then endWidth = startWidth.
    */
    void setDecreasingTaperFlag(bool bSet) { SETBIT(m_uFlags, kFlagDecreasingTaper, bSet); }

    
    bool getBaseStrokeDashFlag() const { return GETBIT(m_uFlags, kFlagBaseStrokeDash); }
    void setBaseStrokeDashFlag(bool bSet) { SETBIT(m_uFlags, kFlagBaseStrokeDash, bSet); }

    bool isDashOrBaseStrokeDash() const { return GETBIT(m_uFlags, kFlagDash | kFlagBaseStrokeDash); }

    /** \details
      Returns the start and end caps type of a stroke.
      \returns
      caps type used for start and end of a stroke.
    */
    StrokeCapsType getCapsType() const { return m_lsCapsType; }
    
    /** \details
      Sets the start and end caps type of a stroke.

      \param iType [in] Value of caps type.
    */
    void setCapsType(StrokeCapsType iType) { m_lsCapsType = iType; }
  } m_dash;
  struct ShapeInfo
  {
    enum SymbolPosOnStroke
    {
      kLsNoSymbol         = 0,
      kLsAtOriginOfStroke = 1,
      kLsAtEndOfStroke    = 2,
      kLsAtCenterOfStroke = 3
    };
    enum Flags
    {
      kFlagSymbolAtElementOrigin        = (1 << 0),
      kFlagSymbolAtElementEnd           = (1 << 1),
      kFlagSymbolAtEachVertex           = (1 << 2),
      kFlagMirrorSymbolForReversedLines = (1 << 3),
      kFlagAbsoluteRotationAngle        = (1 << 4),
      kFlagDoNotScaleElement            = (1 << 5),
      kFlagDoNotClipElement             = (1 << 6),
      kFlagNoPartialStrokes             = (1 << 7),
      kFlagPartialOriginBeyondEnd       = (1 << 8),
      kFlagUseSymbolColor               = (1 << 9),
      kFlagUseSymbolWeight              = (1 << 10)
    };

    OdUInt32                 m_uFlags;
    OdDbStub                *m_pSymbol;
    SymbolPosOnStroke        m_lsPos;
    OdGiLinetypeDash::offset m_offset;
    double                   m_dRotation;
    double                   m_dScale;

    /** \details
      Default constructor for the ShapeInfo structure.
    */
    ShapeInfo()
      : m_uFlags(0)
      , m_pSymbol(NULL)
      , m_lsPos(kLsNoSymbol)
      , m_dRotation(0.0)
      , m_dScale(0.0)
    {
      m_offset.x = m_offset.y = 0.0;
    }

    /** \details
      Return a sumbol ID.
      \returns
      Pointer to a sumbol ID.
    */
    OdDbStub *getSymbolId() const { return m_pSymbol; }
    
    /** \details
      Sets a sumbol ID.
      
      \param pStub [in] Pointer to the symbol ID.
    */
    void setSymbolId(OdDbStub *pStub) { m_pSymbol = pStub; }

    /** \details
      Returns the symbol origin position on a stroke.
      \returns
      One of the following values:
      *kLsNoSymbol - Skips symbol draw.
      *kLsAtOriginOfStroke - Symbol at the start stroke.
      *kLsAtEndOfStroke - Symbol at the end stroke.
      *kLsAtCenterOfStroke - Symbol at the center stroke.
    */
    SymbolPosOnStroke getSymbolPosOnStroke() const { return m_lsPos; }
    
    /** \details
      Sets the symbol origin position on a stroke.

      \param iMode [in] Symbol position on a stroke mode.
    */
    void setSymbolPosOnStroke(SymbolPosOnStroke iMode) { m_lsPos = iMode; }

    /** \details
      Returns the SymbolAtElementOrigin flag.

      \returns
      true if the symbol displays one time at the start point of the element or segment, false otherwise.
    */
    bool getSymbolAtElementOriginFlag() const { return GETBIT(m_uFlags, kFlagSymbolAtElementOrigin); }
    
    /** \details
      Sets the SymbolAtElementOrigin flag.

      \param bSet [in] Value of the flag. If true, the symbol displays one time at the start point of the element or segment.
    */
    void setSymbolAtElementOriginFlag(bool bSet) { SETBIT(m_uFlags, kFlagSymbolAtElementOrigin, bSet); }

    /** \details
      Returns the SymbolAtElementEnd flag.

      \returns
      true if the symbol displays one time at the end point of the element or segment, false otherwise.
    */
    bool getSymbolAtElementEndFlag() const { return GETBIT(m_uFlags, kFlagSymbolAtElementEnd); }
    
    /** \details
      Sets the SymbolAtElementEnd flag.

      \param bSet [in] Value of the flag. If true, the symbol displays one time at the end point of the element or segment.
    */
    void setSymbolAtElementEndFlag(bool bSet) { SETBIT(m_uFlags, kFlagSymbolAtElementEnd, bSet); }

    /** \details
      Returns the SymbolAtEachVertex flag.

      \returns
      true if the symbol displays on each vertex position of the element, false otherwise.
    */
    bool getSymbolAtEachVertexFlag() const { return GETBIT(m_uFlags, kFlagSymbolAtEachVertex); }
    
    /** \details
      Sets the SymbolAtEachVertex flag.

      \param bSet [in] Value of the flag. If true, the symbol displays on each vertex position of the element.
    */
    void setSymbolAtEachVertexFlag(bool bSet) { SETBIT(m_uFlags, kFlagSymbolAtEachVertex, bSet); }

    /** \details
      Returns the MirrorSymbolForReversedLines flag.

      \returns
      true if the mirror transformation is applied to symbols if the direction of the line is reversed.
      \remarks
      A reversed line direction is the opposite direction from the x-axis (or the y-axis 
      if the direction is perpendicular to the x-axis, or the z-axis if the direction is parallel 
      to the z-axis).
    */
    bool getMirrorSymbolForReversedLinesFlag() const { return GETBIT(m_uFlags, kFlagMirrorSymbolForReversedLines); }
    
    /** \details
      Sets the MirrorSymbolForReversedLines flag.

      \param bSet [in] Value of the flag. If true, the mirror transformation is applied to symbols if the direction of the line is reversed.
    */
    void setMirrorSymbolForReversedLinesFlag(bool bSet) { SETBIT(m_uFlags, kFlagMirrorSymbolForReversedLines, bSet); }

    /** \details
      Returns the AbsoluteRotationAngle flag.

      \returns
      true if the symbol rotation doesn't depend on the segment direction.
    */
    bool getAbsoluteRotationAngleFlag() const { return GETBIT(m_uFlags, kFlagAbsoluteRotationAngle); }
    
    /** \details
      Sets the AbsoluteRotationAngle flag.

      \param bSet [in] Value of the flag. If true, the symbol rotation doesn't depend on the segment direction.
    */
    void setAbsoluteRotationAngleFlag(bool bSet) { SETBIT(m_uFlags, kFlagAbsoluteRotationAngle, bSet); }

    /** \details
      Returns the DoNotScaleElement flag.

      \returns
      true if the symbol doesn't scale by the linetype scale.
    */
    bool getDoNotScaleElementFlag() const { return GETBIT(m_uFlags, kFlagDoNotScaleElement); }
    
    /** \details
      Sets the DoNotScaleElement flag.

      \param bSet [in] Value of the flag. If true, the symbol doesn't scale by the linetype scale.
    */
    void setDoNotScaleElementFlag(bool bSet) { SETBIT(m_uFlags, kFlagDoNotScaleElement, bSet); }

    /** \details
      Returns the DoNotClipElement flag.

      \returns
      true if the symbol is not clipped at the end of the element.
    */
    bool getDoNotClipElementFlag() const { return GETBIT(m_uFlags, kFlagDoNotClipElement); }
    
    /** \details
      Sets the DoNotClipElement flag.

      \param bSet [in] Value of the flag. If true, the symbol is not clipped at the end of the element.
    */
    void setDoNotClipElementFlag(bool bSet) { SETBIT(m_uFlags, kFlagDoNotClipElement, bSet); }

    /** \details
      Returns the NoPartialStrokes flag.

      \returns
      true if the skip symbol is drawn on partial strokes.
    */
    bool getNoPartialStrokesFlag() const { return GETBIT(m_uFlags, kFlagNoPartialStrokes); }
    
    /** \details
      Sets the NoPartialStrokes flag.

      \param bSet [in] Value of the flag. If true, the skip symbol is drawn on partial strokes.
    */
    void setNoPartialStrokesFlag(bool bSet) { SETBIT(m_uFlags, kFlagNoPartialStrokes, bSet); }

    /** \details
      Returns the PartialOriginBeyondEnd flag.

      \returns
      true if the symbol origin is beyond the end of partial strokes.
    */
    bool getPartialOriginBeyondEndFlag() const { return GETBIT(m_uFlags, kFlagPartialOriginBeyondEnd); }
    
    /** \details
      Sets the PartialOriginBeyondEnd flag.

      \param bSet [in] Value of the flag. If true, the symbol origin is beyond the end of partial strokes.
    */
    void setPartialOriginBeyondEndFlag(bool bSet) { SETBIT(m_uFlags, kFlagPartialOriginBeyondEnd, bSet); }

    /** \details
      Returns the UseSymbolColor flag.

      \returns
      true if the color from the symbol definition is used to draw the symbol.
      Otherwise the element color is used.
    */
    bool getUseSymbolColorFlag() const { return GETBIT(m_uFlags, kFlagUseSymbolColor); }
    
    /** \details
      Sets the UseSymbolColor flag.

      \param bSet [in] Value of the flag. If true, the color from the symbol definition is used to draw the symbol. If false, the element color is used.
    */
    void setUseSymbolColorFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseSymbolColor, bSet); }

    /** \details
      Returns the UseSymbolWeight flag.

      \returns
      true if the lineweight from the symbol definition is used to draw the symbol.
      Otherwise the element lineweight is used.
    */
    bool getUseSymbolWeightFlag() const { return GETBIT(m_uFlags, kFlagUseSymbolWeight); }
    
    /** \details
      Sets the UseSymbolWeight flag.

      \param bSet [in] Value of the flag. If true, the lineweight from the symbol definition is used to draw the symbol. If false, the element lineweight is used.
    */
    void setUseSymbolWeightFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseSymbolWeight, bSet); }

    /** \details
      Returns the offset of a symbol from the origin point.
      
      \param x [out] Receives an offset by the x axis.
      \param y [out] Receives an offset by the y axis.
    */
    void getOffset(double &x, double &y) const { x = m_offset.x; y = m_offset.y; }
    
    /** \details
      Sets the offset of a symbol from the origin point.

      \param x [in] Offset by the x axis.
      \param y [in] Offset by the y axis.
    */
    void setOffset(double x, double y) { m_offset.x = x; m_offset.y = y; }

    /** \details
      Returns the rotation of a symbol from the origin point.
      \returns
      rotation angle in radians.
    */
    double getRotationAngle() const { return m_dRotation; }
    
    /** \details
      Sets the rotation of a symbol from the origin point.

      \param dRotAngle [in] Rotation angle in radians of the symbol from the origin point.
    */
    void setRotationAngle(double dRotAngle) { m_dRotation = dRotAngle; }

    /** \details
      Returns the symbol scale.
      \returns
      symbol scale.
    */
    double getSymbolScale() const { return m_dScale; }
    
    /** \details
      Sets a symbol scale.

      \param dScale [in] Scale of a symbol.
    */
    void setSymbolScale(double dScale) { m_dScale = dScale; }
  } m_shape;

  /** \details
    Default constructor for the OdGiDgLinetypeDash class.
  */
  OdGiDgLinetypeDash()
    : m_dash()
    , m_shape()
  {
  }
};

/** \details
  The data type that represents an array of <link OdGiDgLinetypeDash, OdGiDgLinetypeDash> objects.
*/
typedef OdArray<OdGiDgLinetypeDash> OdGiDgLinetypeDashArray;

/** \details
    Represents a linetype item.
    <group OdGi_Classes>
*/
struct OdGiDgLinetypeItem
{
  /** \details
    Represents flags for a linetype item.
  */
  enum Flags
  {
    /** If true, the phase value is a fraction, otherwise the phase value is a shift. */
    kFlagAutoPhase              = (1 << 0),
    /** If true, a limit is used, otherwise there is no limit to the iteration for the pattern. */
    kFlagUseIterationLimit      = (1 << 1),
    /** If true, the pattern is restarted for every segment, otherwise the pattern continues to be drawn on the next segment. */
    kFlagSingleSegmentMode      = (1 << 2),
    /** If true, the center of the pattern is the same as the center of the line or line segment. Shift and fraction values are ignored. */
    kFlagCenterStretchPhaseMode = (1 << 3),
    kFlagStandardLinetype       = (1 << 4),
    kFlagComputeStandardScale   = (1 << 5)
  };

  /** Flags for a linetype item.*/
  OdUInt32                m_uFlags;
  /** Linetype item length.*/
  double                  m_dLength;
  /** Fraction shift or distance shift value of a stroke. */
  double                  m_dPhase;
  /** The iteration limit of a linetype item.*/
  OdUInt32                m_nMaxIterations;
  /** Vertical offset of a linetype item.*/
  double                  m_dOffset;
  /** Array of linetype dashes.*/
  OdGiDgLinetypeDashArray m_dashes;

  /** \details
    Default constructor for the OdGiDgLinetypeItem class.
  */
  OdGiDgLinetypeItem()
    : m_uFlags(0)
    , m_dLength(0.0)
    , m_dPhase(0.0)
    , m_nMaxIterations(1)
    , m_dOffset(0.0)
  {
  }

  /** \details
    Returns the length of an item.
    \returns
    length of an item.
  */
  double getLength() const { return m_dLength; }
  
  /** \details
    Sets the length of an item.
    
    \param dLen [in] Length of an item.
  */
  void setLength(double dLen) { m_dLength = dLen; }

  /** \details
    Returns the fraction or shift value of a stroke.

    \returns
    the value that is a fraction, if the auto phase flag is set, otherwise 
    returns the value that is a shift distance.
    \remarks
    - Shift is an offset of the stroke pattern in units relative to the 
    start of the line or line segment.
    - Fraction is an offset of the stroke pattern in a percent of the pattern 
    length relative to the start of the line or line segment.
    - The value is ignored if the center stretch phase mode is on.
  */
  double getPhase() const { return m_dPhase; }
  
  /** \details
    Sets the fraction or shift value of a stroke.

    \param dPhase [in] Value of the distance shift in units or value of the fraction shift.
  */
  void setPhase(double dPhase) { m_dPhase = dPhase; }

  /** \details
    Returns the phase mode of a stroke.

    \remarks
    true if the phase value is a fraction, otherwise the phase value is a shift.
  */
  bool getAutoPhaseFlag() const { return GETBIT(m_uFlags, kFlagAutoPhase); }
  
  /** \details
    Sets the phase mode of a stroke.

    \param bSet [in] Value of the flag. True for fraction mode and false for phase mode.
  */
  void setAutoPhaseFlag(bool bSet) { SETBIT(m_uFlags, kFlagAutoPhase, bSet); }

  /** \details
    Returns the iteration limit flag of a stroke.

    \returns
    true if a limit is used, otherwise there is no limit to the iteration for the pattern.
  */
  bool getUseIterationLimitFlag() const { return GETBIT(m_uFlags, kFlagUseIterationLimit); }
  
  /** \details
    Sets the iteration limit flag of a stroke.

    \param bSet [in] Value of flag. If true, a limit is used, otherwise there is no limit to the iteration for the pattern.
   */
  void setUseIterationLimitFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseIterationLimit, bSet); }

  /** \details
    Returns the single segment mode flag of a stroke.

    \returns
    true if the pattern is restarted for every segment, otherwise
    the pattern continues to be drawn on the next segment.
  */
  bool getSingleSegmentModeFlag() const { return GETBIT(m_uFlags, kFlagSingleSegmentMode); }
  
  /** \details
    Sets the iteration single segment mode flag of a stroke.

    \param bSet [in] Value of flag. If true, the pattern is restarted for every segment, otherwise the pattern continues to be drawn on the next segment.
  */
  void setSingleSegmentModeFlag(bool bSet) { SETBIT(m_uFlags, kFlagSingleSegmentMode, bSet); }

  /** \details
    Returns the center stretch phase mode flag of a stroke.

    \returns
    true if the center of the pattern is the same as the center of 
    the line or line segment. Shift and fraction values are ignored.
  */
  bool getCenterStretchPhaseModeFlag() const { return GETBIT(m_uFlags, kFlagCenterStretchPhaseMode); }
  
  /** \details
    Sets the center stretch phase mode flag of a stroke.

    \param bSet [in] Value of flag. If true if the center of the pattern is the same as the center of the line or line segment.
  */
  void setCenterStretchPhaseModeFlag(bool bSet) { SETBIT(m_uFlags, kFlagCenterStretchPhaseMode, bSet); }

  
  bool getStandardLinetypeFlag() const { return GETBIT(m_uFlags, kFlagStandardLinetype); }
  void setStandardLinetypeFlag(bool bSet) { SETBIT(m_uFlags, kFlagStandardLinetype, bSet); }

  bool getComputeStandardScaleFlag() const { return GETBIT(m_uFlags, kFlagComputeStandardScale); }
  void setComputeStandardScaleFlag(bool bSet) { SETBIT(m_uFlags, kFlagComputeStandardScale, bSet); }

  /** \details
    Returns the iteration limit of an item.
    \returns
    Maximun number of iterations.
  */
  OdUInt32 getMaxIterations() const { return m_nMaxIterations; }
  
  /** \details
    Sets the iteration limit of an item.

    \param iMaxNum [in] Iteration limit value.
  */
  void setMaxIterations(OdUInt32 iMaxNum) { m_nMaxIterations = iMaxNum; }

  /** \details
    Sets the vertical offset of a linetype item.
    \returns
    vertical offset.
  */
  double getYOffset() const { return m_dOffset; }
  
  /** \details
    Sets the vertical offset of a linetype item.

    \param dYOffset [in] Vertical offset of a linetype item.
  */
  void setYOffset(double dYOffset) { m_dOffset = dYOffset; }

  /** \details
    Returns a number of dashes for this item.
    \returns
    Number of dashes.
  */
  OdUInt32 numDashes() const { return m_dashes.size(); }
  
  /** \details
    Sets a number of dashes for this item.

    \param count [in] Count of dashes.
  */
  void setNumDashes(OdUInt32 count) { m_dashes.resize(count); }

  /** \details
    Returns a dash at the specified index.
    
    \param index [in] Dash index.
    \param dash  [out] Receives the dash.
  */
  void dashAt(OdUInt32 index, OdGiDgLinetypeDash& dash) const { dash = m_dashes.at(index); }
  
  /** \details
    Returns a dash at the specified index.
    
    \param index [in] Dash index.
    \returns
    Reference to a OdGiDgLinetypeDash struct that represents a linetype dash.
  */
  const OdGiDgLinetypeDash& dashAt(OdUInt32 index) const { return m_dashes.at(index); }

  // void setDashAt(OdUInt32 /*index*/, double /*value*/) { throw OdError(eNotImplementedYet); }
  
  /** \details
    Sets a dash at the specified index.
    
    \param index [in] Dash index.
    \param dash  [in] Linetype dash to set.
  */
  void setDashAt(OdUInt32 index, const OdGiDgLinetypeDash& dash) { m_dashes[index] = dash; }

  /** \details
    Returns an array of dashes.
    
    \param dashes [out] Receives an array of dashes.
  */
  void dashes(OdGiDgLinetypeDashArray& dashes) const { dashes = m_dashes; }
  
  /** \details
    Sets an array of dashes.
    
    \param dashes [in] Array of dashes to set.
  */
  void setDashes(const OdGiDgLinetypeDashArray& dashes) { m_dashes = dashes; }
};

/** \details
  The data type that represents an array of <link OdGiDgLinetypeItem, OdGiDgLinetypeItem> objects.
*/
typedef OdArray<OdGiDgLinetypeItem> OdGiDgLinetypeItemArray;

/** \details
    Represents a linetype.
    <group OdGi_Classes> 
*/
class OdGiDgLinetype
{
  enum
  {
    kByBlock            = 1,
    kByLayer            = 2
  };

  OdUInt32                m_uFlags;
  OdGiDgLinetypeItemArray m_items;
  double                  m_dPatLength;
public:
  /** \details
    Default constructor for the OdGiDgLinetype class.
  */
  OdGiDgLinetype()
    : m_uFlags(0)
    , m_dPatLength(0.0)
  {
  }

  /** \details
    Checks whether this linetype is continues, i.e. is displayed as a solid line.
    \returns
    true if this linetype has no elements, false otherwise. 
  */
  bool isContinuous() const { return m_items.empty(); }

  /** \details
    Checks whether this linetype is defined by block.
    \returns
    true if this linetype is defined by block, false otherwise. 
  */
  bool isByBlock() const { return GETBIT(m_uFlags, kByBlock); }
  
  /** \details
    Sets the ByBlock flag of a linetype.
    
    \param value [in] Value of the flag.
  */
  void setByBlock(bool value) { SETBIT(m_uFlags, kByBlock, value); }

  /** \details
    Checks whether this linetype is defined by block.
    \returns
    true if this linetype is defined by block, false otherwise. 
  */
  bool isByLayer() const { return GETBIT(m_uFlags, kByLayer); }
  
  /** \details
    Sets the setByLayer flag of a linetype.
    
    \param value [in] Value of the flag.
  */
  void setByLayer(bool value) { SETBIT(m_uFlags, kByLayer, value); }

  /** \details
    Returns pattern length of a linetype.
    \returns
    Pattern length of a linetype.
  */
  double patternLength() const { return m_dPatLength; }
  
  /** \details
    Sets the pattern length of a linetype.
    
    \param dPatLen [in] Pattern length.
  */
  void setPatternLength(double dPatLen) { m_dPatLength = dPatLen; }

  /** \details
    Returns a number of items in a pattern.
    \returns
    Number of linetype items.
  */
  OdUInt32 numItems() const { return m_items.size(); }
  
  /** \details
    Sets the number of items in a pattern.
    
    \param count [in] Number of items.
  */
  void setNumItems(OdUInt32 count) { m_items.resize(count); }

  /** \details
    Returns a linetype item at the specified index.
    
    \param index [in] Item index.
    \param item  [out] Receives the linetype item.
  */
  void itemAt(OdUInt32 index, OdGiDgLinetypeItem& item) const { item = m_items.at(index); }
  
  /** \details
    Returns a linetype item at the specified index.
    
    \param index [in] Item index.
    \returns
    Reference to a linetype item.
  */
  const OdGiDgLinetypeItem& itemAt(OdUInt32 index) const { return m_items.at(index); }

  /** \details
    Sets a linetype item at the specified index.
    
    \param index [in] Item index.
    \param item  [in] Linetype item to set.
  */
  void setItemAt(OdUInt32 index, const OdGiDgLinetypeItem& item) { m_items[index] = item; }

  /** \details
    Returns an array of linetype items that compose a pattern.
    
    \param items [out] Receives an array of linetype items.
  */
  void items(OdGiDgLinetypeItemArray& items) const { items = m_items; }
  
  /** \details
    Set an array of linetype items that compose a pattern replacing old items.
    
    \param items [in] Array of linetype items to set.
  */
  void setItems(const OdGiDgLinetypeItemArray& items) { m_items = items; }
};

/** \details
    Represents Dgn-specific line style modifiers.
    <group OdGi_Classes>
*/
struct OdGiDgLinetypeModifiers
{
  /** \details
    Represents various flags for a linetype modifiers.
  */
  enum Flags
  {
    /** Use dash scale. */
    kFlagUseDashScale              = (1 << 0),
    /** Use gap scale. */
    kFlagUseGapScale               = (1 << 1),
    /** Use dash scale. */
    kFlagUseWidth                  = (1 << 2),
    /** Use end width. */
    kFlagUseEndWidth               = (1 << 3),
    /** Use shifting. */
    kFlagUseShift                  = (1 << 4),
    /** Use fraction shifting. */
    kFlagUseFractionShift          = (1 << 5),
    kFlagUseCenteredShift          = (1 << 6),
    kFlagTrueWidth                 = (1 << 7),
    /** Override the "break at corners" behavior of a stroke bypass. */
    kFlagOverrideBreakAtCorners    = (1 << 8),
    /** Override the "run through corners" behavior of a stroke bypass. */
    kFlagOverrideRunThroughCorners = (1 << 9),

    kFlagsWidthMask                = (kFlagUseWidth | kFlagUseEndWidth),
    kFlagsShiftMask                = (kFlagUseShift | kFlagUseFractionShift | kFlagUseCenteredShift),
    kFlagsCornersMask              = (kFlagOverrideBreakAtCorners | kFlagOverrideRunThroughCorners)
  };

  /** \details
    Width modes of a stroke.
  */
  enum WidthMode
  {
    /** No width. */
    kLsNoWidth = 0,
    /** Constant width. */
    kLsWidthConstant,
    /** Width is tapered. */
    kLsWidthTapered
  };
  
  /** \details
    Linetype shift modes.
  */
  enum ShiftMode
  {
    /** No shift. */
    kLsNoShift = 0,
    /** Use offset of the stroke pattern in units relative to the start of the line or line segment. */
    kLsShiftDistance,
    /** Use offset of the stroke pattern in a percent of the pattern length relative to the start of the line or line segment. */
    kLsShiftFraction,
    kLsShiftCentered
  };
  /** \details
    Bypass corner behavior of a stroke.
  */
  enum CornersMode
  {
    /** Defined by a line style. */
    kLsCornersFromLS = 0,
    /** Stroke can be broken at element vertices. */
    kLsBreakAtCorners,
    /** Stroke runs through the corners. */
    kLsRunThroughCorners
  };

  /** Modifiers flags. */
  OdUInt32 m_uFlags;
  /** Dash scale. */
  double m_dDashScale;
  /** Gap scale. */
  double m_dGapScale;
  /** Start stroke width. */
  double m_dWidth;
  /** End stroke width. */
  double m_dEndWidth;
  /** Fraction shift or distance shift value of a stroke. */
  double m_dPhase;

  /** \details
    Default constructor for the OdGiDgLinetypeModifiers class.
  */
  OdGiDgLinetypeModifiers()
    : m_uFlags(0)
    , m_dDashScale(1.0)
    , m_dGapScale(1.0)
    , m_dWidth(0.0)
    , m_dEndWidth(0.0)
    , m_dPhase(0.0)
  {
  }

  /** \details
    Returns a flag that indicates whether to use dash scale.
    \returns
    true if kFlagUseDashScale flag is set, false otherwise.
  */
  bool getDashScaleFlag() const { return GETBIT(m_uFlags, kFlagUseDashScale); }
  
  /** \details
    Sets the flag that indicates whether to use dash scale.

    \param bSet [in] Value of flag.
  */
  void setDashScaleFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseDashScale, bSet); }

  /** \details
    Returns a dash scale factor.
    \returns
    Dash scale factor.
  */
  double getDashScale() const { return m_dDashScale; }
  
  /** \details
    Sets a dash scale factor.

    \param dScale [in] Dash scale factor.
  */
  void setDashScale(double dScale) { m_dDashScale = dScale; }

  /** \details
    Returns a flag that indicates whether to use dash scale.
    \returns
    true if kFlagUseDashScale flag is set, false otherwise.
  */
  bool getGapScaleFlag() const { return GETBIT(m_uFlags, kFlagUseGapScale); }
  
  /** \details
    Sets the flag that indicates whether to use gap scale.

    \param bSet [in] Value of flag.
  */
  void setGapScaleFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseGapScale, bSet); }

  /** \details
    Returns a gap scale factor.
    \returns
    Gap scale factor.
  */
  double getGapScale() const { return m_dGapScale; }
  
  /** \details
    Sets a gap scale factor.

    \param dScale [in] Gap scale factor.
  */
  void setGapScale(double dScale) { m_dGapScale = dScale; }

  /** \details
    Returns a flag that indicates whether to use start stroke width.
    \returns
    true if kFlagUseWidth flag is set, false otherwise.
  */
  bool getWidthFlag() const { return GETBIT(m_uFlags, kFlagUseWidth); }
  
  /** \details
    Sets the flag that indicates whether to use start stroke width.

    \param bSet [in] Value of flag.
  */
  void setWidthFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseWidth, bSet); }

  /** \details
    Returns start stroke width value.
    \returns
    Start stroke width.
  */
  double getWidth() const { return m_dWidth; }
  
  /** \details
    Sets a start stroke width value.

    \param dWidth [in] Start width value.
  */
  void setWidth(double dWidth) { m_dWidth = dWidth; }

  /** \details
    Returns a flag that indicates whether to use end stroke width.
    \returns
    true if kFlagUseEndWidth flag is set, false otherwise.
  */
  bool getEndWidthFlag() const { return GETBIT(m_uFlags, kFlagUseEndWidth); }
  
  /** \details
    Sets the flag that indicates whether to use end stroke width.

    \param bSet [in] Value of flag.
  */
  void setEndWidthFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseEndWidth, bSet); }

  /** \details
    Returns end stroke width value.
    \returns
    End stroke width.
  */
  double getEndWidth() const { return m_dEndWidth; }
  
  /** \details
    Sets a end stroke width value.

    \param dEndWidth [in] End width value.
  */
  void setEndWidth(double dEndWidth) { m_dEndWidth = dEndWidth; }
  
  /** \details
    Returns width mode of a linetype.
    \returns
    One of the following values:
    * kLsNoWidth - No width.
    * kLsWidthConstant - Constant width.
    * kLsWidthTapered - Width is tapered.
  */
  WidthMode getWidthMode() const;
  
  /** \details
    Sets width mode of a linetype.

    \param mode [in] Width mode.
  */
  void setWidthMode(WidthMode mode);

  /** \details
    Returns a flag that indicates whether to use linetype shift.
    \returns
    true if kFlagUseShift flag is set, false otherwise.
  */
  bool getShiftFlag() const { return GETBIT(m_uFlags, kFlagUseShift); }
  
  /** \details
    Sets the flag that indicates whether to use linetype shift.

    \param bSet [in] Value of flag.
  */
  void setShiftFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseShift, bSet); }

  /** \details
    Returns a flag that indicates whether to use linetype fraction shift.
    \returns
    true if kFlagUseFractionShift flag is set, false otherwise.
  */
  bool getFractionShiftFlag() const { return GETBIT(m_uFlags, kFlagUseFractionShift); }
  
  /** \details
    Sets the flag that indicates whether to use linetype fraction shift.

    \param bSet [in] Value of flag.
  */
  void setFractionShiftFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseFractionShift, bSet); }

  bool getCenteredShiftFlag() const { return GETBIT(m_uFlags, kFlagUseCenteredShift); }
  void setCenteredShiftFlag(bool bSet) { SETBIT(m_uFlags, kFlagUseCenteredShift, bSet); }

  /** \details
    Returns the fraction or shift value of a stroke resource.

    \returns
    the value that is a fraction, if the auto phase flag is set, otherwise 
    returns the value that is a shift distance.
    \remarks
    - Shift is an offset of the stroke pattern in units relative to the 
    start of the line or line segment.
    - Fraction is an offset of the stroke pattern in a percent of the pattern 
    length relative to the start of the line or line segment.
    - The value is ignored if the center stretch phase mode is on.
  */
  double getPhase() const { return m_dPhase; }
  
  /** \details
    Sets the fraction or shift value of a stroke.

    \param dPhase [in] Value of the distance shift in units or value of the fraction shift.
  */
  void setPhase(double dPhase) { m_dPhase = dPhase; }

  /** \details
    Returns the shift mode of a linetype.

    \returns
    One of the following values:
    * kLsNoShift - No shift.
    * kLsShiftDistance - Use offset of the stroke pattern in units relative to the start of the line or line segment.
    * kLsShiftFraction - Use offset of the stroke pattern in a percent of the pattern length relative to the start of the line or line segment.
    * kLsShiftCentered - 
  */
  ShiftMode getShiftMode() const;
  
  /** \details
    Sets the shift mode of a linetype pattern.

    \param mode [in] Shift mode of a pattern.
  */
  void setShiftMode(ShiftMode mode);

  bool getTrueWidthFlag() const { return GETBIT(m_uFlags, kFlagTrueWidth); }
  void setTrueWidthFlag(bool bSet) { SETBIT(m_uFlags, kFlagTrueWidth, bSet); }

  /** \details
    Returns a flag that indicates whether to override the "break at corners" behavior of a stroke.
    \returns
    true if kFlagOverrideBreakAtCorners flag is set, false otherwise.
  */
  bool getBreakAtCornersFlag() const { return GETBIT(m_uFlags, kFlagOverrideBreakAtCorners); }
  
  /** \details
    Sets a flag that specifies whether to override the "break at corners" behavior of a stroke.

    \param bSet [in] Value of flag.
  */
  void setBreakAtCornersFlag(bool bSet) { SETBIT(m_uFlags, kFlagOverrideBreakAtCorners, bSet); }

  /** \details
    Returns a flag that indicates whether to override the "run through corners" behavior of a stroke.
    \returns
    true if kFlagOverrideRunThroughCorners flag is set, false otherwise.
  */
  bool getRunThroughCornersFlag() const { return GETBIT(m_uFlags, kFlagOverrideRunThroughCorners); }
  
  /** \details
    Sets a flag that specifies whether to override the "run through corners" behavior of a stroke.

    \param bSet [in] Value of flag.
  */
  void setRunThroughCornersFlag(bool bSet) { SETBIT(m_uFlags, kFlagOverrideRunThroughCorners, bSet); }

  /** \details
    Returns corners bypass mode of a stroke.
    \returns
    One of the following values:
    * kLsCornersFromLS - Defined by a line style.
    * kLsBreakAtCorners - Stroke can be broken at element vertices.
    * kLsRunThroughCorners - Stroke runs through the corners.
  */
  CornersMode getCornersMode() const;
  
  /** \details
    Sets the corners bypass mode of a stroke.

    \param mode [in] Corners bypass mode.
  */
  void setCornersMode(CornersMode mode);

  /** \details
    Equality for the OdGiDgLinetypeModifiers class.

    \param lsMod [in] Linetype modifiers to compare.
    \returns
    true if all the following conditions are met:
    * Flags are equal.
    * Dash scale values are equal.
    * Start stroke width values are equal.
    * End stroke width values are equal.
    * Linetype phase values are equal.
  */
  bool operator==(const OdGiDgLinetypeModifiers& lsMod) const;
  
  /** \details
    Inequality for the OdGiDgLinetypeModifiers class.

    \param lsMod [in] Linetype modifiers to compare.
    \returns
    true if at least one of the following conditions are met:
    * Flags are equal.
    * Dash scale values are equal.
    * Start stroke width values are equal.
    * End stroke width values are equal.
    * Linetype phase values are equal.
  */
  bool operator!=(const OdGiDgLinetypeModifiers& lsMod) const;
};

inline OdGiDgLinetypeModifiers::WidthMode OdGiDgLinetypeModifiers::getWidthMode() const
{
  switch (m_uFlags & kFlagsWidthMask)
  {
    case kFlagUseWidth:   return kLsWidthConstant;
    case kFlagsWidthMask: return kLsWidthTapered;
    default:              return kLsNoWidth;
  }
}

inline void OdGiDgLinetypeModifiers::setWidthMode(OdGiDgLinetypeModifiers::WidthMode mode)
{
  switch (mode)
  {
    case kLsWidthConstant: SETBIT_1(m_uFlags, kFlagUseWidth); SETBIT_0(m_uFlags, kFlagUseEndWidth); break;
    case kLsWidthTapered:  SETBIT_1(m_uFlags, kFlagsWidthMask); break;
    default: SETBIT_0(m_uFlags, kFlagsWidthMask);
  };
}

inline OdGiDgLinetypeModifiers::ShiftMode OdGiDgLinetypeModifiers::getShiftMode() const
{
  switch (m_uFlags & kFlagsShiftMask)
  {
    case kFlagUseShift:                         return kLsShiftDistance;
    case kFlagUseShift | kFlagUseFractionShift: return kLsShiftFraction;
    case kFlagUseShift | kFlagUseCenteredShift: return kLsShiftCentered;
    default:                                    return kLsNoShift;
  }
}

inline void OdGiDgLinetypeModifiers::setShiftMode(OdGiDgLinetypeModifiers::ShiftMode mode)
{
  switch (mode)
  {
    case kLsShiftDistance: SETBIT_1(m_uFlags, kFlagUseShift); SETBIT_0(m_uFlags, kFlagUseFractionShift | kFlagUseCenteredShift); break;
    case kLsShiftFraction: SETBIT_1(m_uFlags, kFlagUseShift | kFlagUseFractionShift); SETBIT_0(m_uFlags, kFlagUseCenteredShift); break;
    case kLsShiftCentered: SETBIT_1(m_uFlags, kFlagUseShift | kFlagUseCenteredShift); SETBIT_0(m_uFlags, kFlagUseFractionShift); break;
    default: SETBIT_0(m_uFlags, kFlagsShiftMask);
  }
}

inline OdGiDgLinetypeModifiers::CornersMode OdGiDgLinetypeModifiers::getCornersMode() const
{
  switch (m_uFlags & kFlagsCornersMask)
  {
    case kFlagOverrideBreakAtCorners:    return kLsBreakAtCorners;
    case kFlagOverrideRunThroughCorners: return kLsRunThroughCorners;
    default:                             return kLsCornersFromLS;
  }
}

inline void OdGiDgLinetypeModifiers::setCornersMode(OdGiDgLinetypeModifiers::CornersMode mode)
{
  switch (mode)
  {
    case kLsBreakAtCorners:    SETBIT_1(m_uFlags, kFlagOverrideBreakAtCorners); SETBIT_0(m_uFlags, kFlagOverrideRunThroughCorners); break;
    case kLsRunThroughCorners: SETBIT_0(m_uFlags, kFlagOverrideBreakAtCorners); SETBIT_1(m_uFlags, kFlagOverrideRunThroughCorners); break;
    default:                   SETBIT_0(m_uFlags, kFlagsCornersMask);
  }
}

inline bool OdGiDgLinetypeModifiers::operator ==(const OdGiDgLinetypeModifiers& lsMod) const
{
  return (m_uFlags == lsMod.m_uFlags) &&
         (m_dDashScale == lsMod.m_dDashScale) && (m_dGapScale == lsMod.m_dGapScale) &&
         (m_dWidth == lsMod.m_dWidth) && (m_dEndWidth == lsMod.m_dEndWidth) &&
         (m_dPhase == lsMod.m_dPhase);
}

inline bool OdGiDgLinetypeModifiers::operator !=(const OdGiDgLinetypeModifiers& lsMod) const
{
  return (m_uFlags != lsMod.m_uFlags) ||
         (m_dDashScale != lsMod.m_dDashScale) || (m_dGapScale != lsMod.m_dGapScale) ||
         (m_dWidth != lsMod.m_dWidth) || (m_dEndWidth != lsMod.m_dEndWidth) ||
         (m_dPhase != lsMod.m_dPhase);
}

/** \details
    Represents Dgn-specific linetype traits.
    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiDgLinetypeTraits : public OdGiDrawableTraits
{
  public:
    ODRX_DECLARE_MEMBERS(OdGiDgLinetypeTraits);

    /** \details
      Retrieves pattern items for a Dgn-specific linetype.

      \param items [out] Receives pattern items.
    */
    virtual void items(OdGiDgLinetypeItemArray& items) const = 0;
    
    /** \details
      Sets pattern items for a Dgn-specific linetype.

      \param items [in] Pattern items.
    */
    virtual void setItems(const OdGiDgLinetypeItemArray& items) const = 0;

    /** \details
      Retrieves pattern length of a Dgn-specific linetype.

      \returns
      Pattern length in drawing units.
    */
    virtual double patternLength() const = 0;
    
    /** \details
      Sets pattern length of a Dgn-specific linetype.

      \param dPatLen [in] Pattern length in drawing units.
    */
    virtual void setPatternLength(double dPatLen) = 0;

    /** \details
      Retrieves Dgn-specific linetype scale.

      \returns
      Scale factor of the linetype.
    */
    virtual double scale() const = 0;
    
    /** \details
      Sets scale factor for a Dgn-specific linetype.

      \param dScale [in] Scale factor.
    */
    virtual void setScale(double dScale) = 0;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGiDgLinetypeTraits object pointers.
*/
typedef OdSmartPtr<OdGiDgLinetypeTraits> OdGiDgLinetypeTraitsPtr;

#include "TD_PackPop.h"

#endif // __ODGI_DGLINETYPE_H__
