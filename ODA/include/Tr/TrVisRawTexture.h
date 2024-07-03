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
#ifndef ODTRVISRAWTEXTURE
#define ODTRVISRAWTEXTURE

#include "TD_PackPush.h"
#include "OdPlatform.h"
#include <memory>

/** \details
  This class is a raw texture data. It's a lighter version of OdTrVisTexture. Not requires TR_BASE_LIB. Can be simply converted to OdTrVisTexture.
*/
class OdTrVisRawTexture
{
public:
  /** \details
    Creates a new instance of an object with default parameters.
  */
  OdTrVisRawTexture() {}

  /** \details
    Destroys the object.
  */
  ~OdTrVisRawTexture()
  {
    delete m_pTextureData;
    m_pTextureData = nullptr;
  }

  /** \details
  This function resizes texture.
  \param width [in] new texture width
  \param height [in] new texture height
  \param format [in] new texture format
  */
  void resize(OdUInt32 width, OdUInt32 height, OdUInt32 format)
  {
    m_nWidth = width;
    m_nHeight = height;
    m_format = format;

    OdUInt32 totalSize = size();
    delete m_pTextureData;
    m_pTextureData = new OdUInt8[totalSize];
  }

  /** \details
  Returns the pixel size in the texture.

  \param format [in] Texture format. See OdTrVisTexture::Format
  \returns the pixel size in the texture if the format is correct or 1 otherwise.
  */
  static OdUInt32 pixelSize(OdUInt32 format)
  {
    static const OdUInt8 sizes[] = //enum Format
    { // Basic 8 bit formats
      1,//kRed,
      1,//kAlpha,
      2,//kRG,
      3,//kRGB,
      4,//kRGBA,
      3,//kBGR,
      4,//kBGRA,
      1,//kPalette,

      //Depth/Stencil
      1,//kStencil8,
      2,//kDepth16,
      4,//kDepth24Stencil8,//Most used depth format. getColor() returns only depth value. For stencil data use textureData() function
      4,//kDepth32,

      //16 bit
      2,//kR16,
      4,//kRG16,
      8,//kRGBA16,
      2,//kAlpha16,

      //Float
      4,//kFloatR,
      8,//kFloatRG,
      16,//kFloatRGBA,
      2,//kHalfFloatR,
      4,//kHalfFloatRG,
      8,//kHalfFloatRGBA,

      //Signed normalized
      1,//kRSNorm,
      1,//kAlphaSNorm,
      2,//kRGSNorm,
      4,//kRGBASNorm,
      2,//kR16SNorm,
      2,//kAlpha16SNorm,
      4,//kRG16SNorm,
      8,//kRGBA16SNorm,
    };

    static const OdUInt32 count = sizeof(sizes) / sizeof(sizes[0]);
    ODA_ASSERT_ONCE(format < count);
    if (format >= count)
      return 1;

    return sizes[format];
  }

  /** \details
  Returns the total size of the texture in bytes.

  /returns the total size of the texture in bytes.
  */
  OdUInt32 size() const
  {
    return m_nWidth * m_nHeight * pixelSize(m_format);
  }

  /** \details
  Returns the width of the texture in pixels.

  /returns the width of the texture in pixels.
  */
  OdUInt32 width() const
  {
    return m_nWidth;
  }

  /** \details
  Returns the height of the texture in pixels.

  /returns the height of the texture in pixels.
  */
  OdUInt32 height() const
  {
    return m_nHeight;
  }

  /** \details
  Returns the texture format.

  /returns the texture format.
  */
  OdUInt32 format() const
  {
    return m_format;
  }

  /** \details
  Returns raw texture data.

  /returns raw texture data.
  */
  OdUInt8* data()
  {
    return m_pTextureData;
  }

  /** \details
  Returns raw texture data.

  /returns raw texture data.
  */
  const OdUInt8* data() const
  {
    return m_pTextureData;
  }

private:
  OdUInt8* m_pTextureData = nullptr;
  OdUInt32 m_nWidth = 0;
  OdUInt32 m_nHeight = 0;
  OdUInt32 m_format = 0;
};

typedef std::shared_ptr<OdTrVisRawTexture> OdTrVisRawTexturePtr;


#include "TD_PackPop.h"

#endif
