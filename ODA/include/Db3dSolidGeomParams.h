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

#pragma once

#include "Ge/GeVector3d.h"
#include "DbSweepOptions.h"
#include "DbLoftOptions.h"
#include "DbRevolveOptions.h"
#include <cfloat>

/** \details
  Represents geometry parameters of a OdDb3dSolid object.
  <group !!RECORDS_tdrawings_apiref>
*/
struct OdDb3dSolidGeomParams
{
  virtual ~OdDb3dSolidGeomParams() {}
  OdGeMatrix3d matrix;
};
/** \details
  Represents geometry parameters of a spherical OdDb3dSolid object.
*/
struct OdDb3dSolidSphereParams : public OdDb3dSolidGeomParams
{
  double radius = -1.0;
};
/** \details
  Represents geometry parameters of a cylindrical OdDb3dSolid object.
  <group !!RECORDS_tdrawings_apiref>
*/
struct OdDb3dSolidCylinderParams : public OdDb3dSolidGeomParams
{
  double height = -1.0;
  double majorRadius = -1.0;
  double minorRadius = -1.0;
  bool isElliptical() const { return majorRadius != minorRadius; }
};
/** \details
  Represents geometry parameters of a conical OdDb3dSolid object.
  <group !!RECORDS_tdrawings_apiref>
*/
struct OdDb3dSolidConeParams : public OdDb3dSolidCylinderParams
{
  double topMajorRadius = -1.0;
  bool isTruncated() const { return topMajorRadius != 0.0; }
};
/** \details
  Represents geometry parameters of a toroidal OdDb3dSolid object.
  <group !!RECORDS_tdrawings_apiref>
*/
struct OdDb3dSolidTorusParams : public OdDb3dSolidGeomParams
{
  double majorRadius = -1.0;
  double minorRadius = -1.0;
  bool isDoughnut() const { return OdGreater(majorRadius, minorRadius); }
  bool isApple() const { return majorRadius > 0.0 && OdLess(majorRadius, minorRadius); }
  bool isLemon() const { return majorRadius <= 0.0; }
  bool isVortex() const { return OdEqual(majorRadius, minorRadius); }
  bool isDegenerate() const { return !isDoughnut(); }
};
/** \details
  Represents geometry parameters of a box-shaped OdDb3dSolid object.
*/
struct OdDb3dSolidBoxParams : public OdDb3dSolidGeomParams
{
  double xLen = -1.0;
  double yLen = -1.0;
  double zLen = -1.0;
};
/** \details
  Represents geometry parameters of a wedge-shaped OdDb3dSolid object.
*/
struct OdDb3dSolidWedgeParams : public OdDb3dSolidGeomParams
{
  double xLen = -1.0;
  double yLen = -1.0;
  double zLen = -1.0;
};
/** \details
  Represents geometry parameters of a pyramid-shaped OdDb3dSolid object.
  <group !!RECORDS_tdrawings_apiref>
*/
struct OdDb3dSolidPyramidParams : public OdDb3dSolidGeomParams
{
  double height = -1.0;
  int sides = 0;
  double radius = -1.0;
  double topRadius = -1.0;
  bool isTruncated() const { return topRadius != 0.0; }
};
/** \details
  Represents geometry parameters of an extrusion OdDb3dSolid object.
*/
struct OdDb3dSolidExtrusionParams : public OdDb3dSolidGeomParams
{
  OdGeVector3d direction; //includes height
  OdDbEntity* extrusionEntity = nullptr;
  OdDbSweepOptions options;
};
/** \details
  Represents geometry parameters of a sweep OdDb3dSolid object.
*/
struct OdDb3dSolidSweepParams : public OdDb3dSolidGeomParams
{
  OdDbEntity* sweepEntity = nullptr;
  OdDbEntity* pathEntity = nullptr;
  OdDbSweepOptions options;
};
/** \details
  Represents geometry parameters of a loft OdDb3dSolid object.
*/
struct OdDb3dSolidLoftParams : public OdDb3dSolidGeomParams
{
  OdDbEntityPtrArray crossSectionCurves;
  OdDbEntityPtrArray guideCurves;
  OdDbEntity* pathCurve = nullptr;
  OdDbLoftOptions options;
};
/** \details
  Represents geometry parameters of a revolve OdDb3dSolid object.
*/
struct OdDb3dSolidRevolveParams : public OdDb3dSolidGeomParams
{
  double revolveAngle = -DBL_MAX;
  double startAngle = -DBL_MAX;
  OdGePoint3d axisPoint;
  OdGeVector3d axisDir;
  OdDbEntity* revolveEntity = nullptr;
  OdDbRevolveOptions options;
};
