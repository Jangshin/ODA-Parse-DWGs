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

#ifndef __OD_GI_CUBE_MAP__
#define __OD_GI_CUBE_MAP__

#include "Gi/GiExport.h"
#include "Gi/GiRasterImage.h"
#include "OdArray.h"

#include "TD_PackPush.h"

/** \details
    Represents set of separate raster image tiles as single raster image.

    Corresponding C++ library: TD_Gi

    \remarks
    Transforming an image does not affect the orignal image.
    Supports only true color raster images. Raster images with palette is not supported.
    <group OdGi_Classes>
    \sa
    <link gi_raster_images, Work with Raster Images>
*/
class ODGI_EXPORT OdGiPatchworkRasterImage : public OdGiRasterImageParam
{
  OdUInt32 m_nWidth, m_nHeight;
  OdString m_fileName;
  ImageSource m_imSrc;
  TransparencyMode m_trMode;
  ODCOLORREF m_backgroundColor;
  OdUInt8 m_bkColorEncoded[4] = {};
  struct RIEntry { OdGiRasterImagePtr m_pOrig; OdInt32 m_nPosX = 0, m_nPosY = 0; OdUInt32 m_pixWidth = 0, m_pixHeight = 0;
                   bool isInside(OdUInt32 nScanline, OdUInt32 nPix) const { return OdInt32(nScanline) >= m_nPosY && nScanline < m_nPosY + m_pixHeight &&
                                                                                   OdInt32(nPix) >= m_nPosX && nPix < m_nPosX + m_pixHeight; }
                   OdUInt32 yLoc(OdUInt32 nScanline) const { return nScanline - m_nPosY; }
                   OdUInt32 xLoc(OdUInt32 nPix) const { return nPix - m_nPosX; } };
  OdArray<RIEntry> m_rasterImages;
protected:
  const RIEntry *findEntry(OdUInt32 nScanline, OdUInt32 nPixel) const;
  void encodeBkColor();
public:
  /** \details
    Default constructor for the OdGiRasterImageWrapper class.
  */
  OdGiPatchworkRasterImage();
  /** \details
    Destructor for the OdGiRasterImageWrapper class.
  */
  virtual ~OdGiPatchworkRasterImage();

  /** \details
    Creates an OdGiRasterImageAlphaChannelAdder object with the specified parameters.
    \param nWidth [in] Raster image width.
    \param nHeight [in] Raster image height.
    \param bkColor [in] Background color.
    \returns
    Returns a SmartPointer to the newly created object.
  */
  static OdGiRasterImagePtr createObject(OdUInt32 nWidth, OdUInt32 nHeight, ODCOLORREF bkColor = 0);

  /** \details
    Sets final raster image dimensions.
    \param uWidth [in] Raster image width.
    \param uHeight [in] Raster image height.
  */
  void setRasterDimensions(OdUInt32 uWidth, OdUInt32 uHeight) { m_nWidth = uWidth; m_nHeight = uHeight; }

  /** \details
    Sets raster image background color.
    \param bkColor [in] Background color.
  */
  void setBackgroundColor(ODCOLORREF bkColor) { m_backgroundColor = bkColor; if (!m_rasterImages.empty()) encodeBkColor(); }
  /** \details
    Retrieves raster image background color.
    \returns Background color.
  */
  ODCOLORREF backgroundColor() const { return m_backgroundColor; }

  /** \details
    Adds original OdGiRasterImage object to specified position inside final raster image.
    \param pRaster [in] Pointer to the original image object.
    \param nPosX [in] X-axis position.
    \param nPosY [in] Y-axis position.
  */
  void addRasterImage(const OdGiRasterImage* pRaster, OdInt32 nPosX, OdInt32 nPosY);
  /** \details
    Removes original OdGiRasterImage object from final raster image.
    \param pRaster [in] Pointer to the original image object.
  */
  void removeRasterImage(const OdGiRasterImage *pRaster);

  /** \details
    Returns number of underlying raster images.
    \returns Number of raster images.
  */
  OdUInt32 numRasterImages() const { return m_rasterImages.size(); }
  /** \details
    Returns underlying raster image at specified index.
    \param nRaster [in] Raster image index.
    \returns Original raster image.
  */
  const OdGiRasterImage *getRasterImage(OdUInt32 nRaster, OdInt32 *pPosX = nullptr, OdInt32 *pPosY = nullptr) const
  {
    if (pPosX) *pPosX = m_rasterImages[nRaster].m_nPosX;
    if (pPosY) *pPosY = m_rasterImages[nRaster].m_nPosY;
    return m_rasterImages[nRaster].m_pOrig;
  }

  /** \details
    Retrieves the image width in pixels of this RasterImage object.
    \returns
    image width in pixels.
  */
  OdUInt32 pixelWidth() const;
  /** \details
    Retrieves the image height in pixels of this RasterImage object.
    \returns
    image height in pixels.
  */
  OdUInt32 pixelHeight() const;
  /** \details
    Retrieves the default image resolution in pixels per unit of this RasterImage object. 

    \param xPelsPerUnit [out]  Receives the pixels per unit value (x direction). 
    \param yPelsPerUnit [out]  Receives the pixels per unit value (y direction).
    \returns
    units that are used to measure image dimensions.
    \remarks If the returned value is kNone, then xPelsPerUnit and yPelsPerUnit are not set.
  */
  Units defaultResolution(double& xPelsPerUnit, double& yPelsPerUnit) const;
  /** \details
    Retrieves the number of bits per pixel used for colors by this RasterImage object.
    \returns
    number of bits per pixel that represents color depth.
  */
  OdUInt32 colorDepth() const;
  /** \details
    Retrieves the number of colors in the palette of this RasterImage object.
    \returns
    number of colors in the palette.
  */
  OdUInt32 numColors() const;
  /** \details
    Retrieves the color for the specified index from the palette of this RasterImage object.
    \param colorIndex [in]  Color index.
    \returns
    color at the specified index as ODCOLORREF (OdUInt32) value.
  */
  ODCOLORREF color(OdUInt32 colorIndex) const;
  /** \details
    Retrieves the size (in bytes) of the palette data of this RasterImage object.
    \returns
    number of bytes that represents palette data size.
  */
  OdUInt32 paletteDataSize() const;
  /** \details
    Retrieves the size (in bytes) of the palette data of this RasterImage object.
    \param bytes [out]  Receives the palette data.
    
    \remarks
    It is up to the caller to allocate sufficient memory for the palette data.
  */
  void paletteData(OdUInt8* bytes) const;
  /** \details
    Retrieves the scanline size of this RasterImage object.
    
    \remarks
    This function returns the number of bytes between the beginning of scanline N and
    the beginning of scanline N+1 (taking into account any padding that is added to the 
    end of the scanline).
  */
  OdUInt32 scanLineSize() const;
  /** \details
    Retrieves the specified set of scanlines in BMP format from this RasterImage object,
    or the pixel data in BMP format for this RasterImage object.

    \param scnLines [out]  Receives the scanline data.
    \param firstScanline [in]  Index of first scanline to retrieve.
    \param numLines [in]  Number of scanlines to retrieve.

    \remarks
    * The number of accessible scanlines is equal to the value returned by pixelHeight().
    * The number of accessible bytes in a scanline is equal to the value returned by scanLineSize().
    * The scanline returned by firstScanline == 0 is the first scanline in the image.
    * The scanline returned by firstScanline == (pixelHeight() - 1) is the last scanline in the image.

    \remarks
    It us up to the caller to allocate sufficient memory for the scanline data.
  */
  void scanLines(OdUInt8* scnLines, OdUInt32 firstScanline, OdUInt32 numLines = 1) const;
  /** \details
    Retrieves the set of scanlines.

    \returns
    set of scanlines.
    \remarks
    Implementation of this function is optional; NULL can be returned
    if it is inconvenient to implement. The caller must take
    into account that the return value can be NULL. If this
    method returns NULL, scanlines can be accessed by a second version
    of the scanLines() method with arguments where a memory buffer for
    scalines data is preallocated by the caller.
  */
  const OdUInt8* scanLines() const;
  /** \details
    Retrieves the pixel format for this RasterImage object.

    \returns
    the pixel format of the palette,
    unless there is no palette, in which case it returns
    the pixel format of the image itself.
  */
  PixelFormatInfo pixelFormat() const;
  /** \details
    Retrieves the scanline alignment, in bytes, for this RasterImage object.
    Example:
    scanLinesAlignment() returns 4 for Windows BMP.
    \returns
    scanline alignment as OdUInt32 value.
  */
  OdUInt32 scanLinesAlignment() const;
  /** \details
    Retrieves the index of transparent color in the image.

    \returns
    transparent color.
    \remarks If there is no transparent color, -1 should be returned.
  */
  int transparentColor() const;
  /** \details
    Retrieves the image source.
    \returns
    image source represented by a value from the ImageSource enumeration.
  */
  ImageSource imageSource() const;
  /** \details
    Retrieves the image source file name.
    \returns
    full path to a file from which image is loaded.
  */
  const OdString &sourceFileName() const;
  /** \details
    Retrieves the transparency mode for 32bpp formats.
    \returns
    transparency mode represented by a value from the TransparencyMode enumeration.
  */
  TransparencyMode transparencyMode() const;
  /** \details
    Retrieves the ParamType bitflags with which parameters are supported by this interface.
    \returns
    bitflags that represent supported parameters.
  */
  OdUInt32 supportedParams() const;
  /** \details
    Sets an image source.
    \param source [in]  New image source value.
  */
  void setImageSource(ImageSource source);
  /** \details
    Sets an image source file name.
    \param fileName [in]  New value for image source file name.
  */
  void setSourceFileName(const OdString &fileName);
  /** \details
    Sets an image transparency mode.
    \param mode [in]  New transparency mode value.
  */
  void setTransparencyMode(TransparencyMode mode);
  /** \details
    Retrieves the user-end implementation of raster image functionality.
    \remarks
    If not overridden by a user-end raster image implementation, always returns null.
  */
  void* imp() const;
  /** \details
    Creates a *clone* of this object, and returns a pointer to the *clone*.
    \returns
    smart pointer to the cloned object.
  */
  OdRxObjectPtr clone() const;
  /** \details
    Copies data of a source object to the current object.

    \param pSource [in] Input source object.
  */
  void copyFrom(const OdRxObject *pSource);
};

/** \details
    ODA Cube Map (OCM) files reader.

    Corresponding C++ library: TD_Gi
    \sa
    <exref target="https://docs.opendesign.com/tv/gi_raster_image_cube_maps.html">Visualize Cube Maps</exref>
*/
class ODGI_EXPORT OdGiOCMReader
{
  public:
    /** \details
      OCM raster image loader.
    */
    struct RasterLoader
    {
      /** \details
        Loads an OCM by the specified file name.
        
        \param fileName [in] Input file name of a raster image.
        \returns
        Smart pointer to a loaded image.
      */
      virtual OdGiRasterImagePtr load(const OdString &fileName) = 0;
    };
  protected:
    OdGiRasterImagePtr loadRastrec(const OdString &streamName, const OdString &fileName, RasterLoader *pLoader);
  public:
    static OdString substituteFileName(const OdString &streamName, const OdString &fileName);
  public:
    /** \details
      Loads an OCM using the specified stream buffer and raster loader.
      
      \param pStreamBuf [in] Stream buffer.
      \param pLoader    [in] OCM raster image loader.
      \returns
      Smart pointer to a loaded OCM.
    */
    OdGiRasterImagePtr load(OdStreamBuf &pStreamBuf, RasterLoader *pLoader = nullptr);
};

#include "TD_PackPop.h"

#endif //  __OD_GI_CUBE_MAP__
