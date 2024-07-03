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


///////////////////////////////////////////////////////////////////////////////
//
// PdfPublishCADDefinition.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_CADDEFINITION_INCLUDED_
#define _PDF_PUBLISH_CADDEFINITION_INCLUDED_

#include "PdfPublishCommon.h"
#include "PdfPublishBaseObject.h"
#include "DbBaseDatabase.h"
#include "SSet.h"


/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements a CAD definition object in .pdf documents created with Publish SDK.
*/
class PDFPUBLISH_TOOLKIT OdCADDefinition : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdCADDefinition();
  //DOM-IGNORE-END
public:

/** \details
  This class implements a wrapper interface to work with the database for the CAD definition object.
*/
  class DatabaseWrapperInterface
  {
  public:
    /** \details
      Creates a new instance of the DatabaseWrapperInterface object with default parameters.
    */
    DatabaseWrapperInterface() {}

    /** \details
      Destroys the DatabaseWrapperInterface object.
    */
    virtual ~DatabaseWrapperInterface() {}

    /** \details
      Starts a database handling operation.
      \remarks
      Must be called to open the database before publishing its content.
    */
    virtual void startDatabaseHandling() = 0;

    /** \details
      Ends a database handling operation.
      \remarks
      Must be called to close the database after it is published.
    */
    virtual void endDatabaseHandling() = 0;

    /** \details
      Retrieves the database object associated with the DatabaseWrapperInterface object.
      \returns A pointer to the database object.
    */
    virtual OdDbBaseDatabase* getDatabase() = 0;
  };


  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdCADDefinition);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys the CAD definition object.
  */
  virtual ~OdCADDefinition();

  /** \details
    Sets the source database for the CAD definition object.
    \param database [in] A pointer to a database object.
    \remarks
    You can use either the <link OdPdfPublish::OdCADDefinition::setDatabase@OdDbBaseDatabase *, setDatabase()> or <link OdPdfPublish::OdCADDefinition::setDatabaseWrapper@DatabaseWrapperInterface*, setDatabaseWrapper()> method to specify a database for publishing. 
    The <link OdPdfPublish::OdCADDefinition::DatabaseWrapperInterface, DatabaseWrapperInterface> value is reset when the source database is set.
  */
  void setDatabase(OdDbBaseDatabase *database);

  /** \details
    Sets a new <link OdPdfPublish::OdCADDefinition::DatabaseWrapperInterface, DatabaseWrapperInterface> object for the CAD definition object.
    \param database_wrapper [in] A pointer to a database wrapper object.
    \remarks
    You can use either the <link OdPdfPublish::OdCADDefinition::setDatabase@OdDbBaseDatabase *, setDatabase()> or <link OdPdfPublish::OdCADDefinition::setDatabaseWrapper@DatabaseWrapperInterface*, setDatabaseWrapper()> method to specify a database for publishing. 
    The <link OdPdfPublish::OdCADDefinition::DatabaseWrapperInterface, DatabaseWrapperInterface> value is reset when the source database is set.
  */
  void setDatabaseWrapper(DatabaseWrapperInterface* database_wrapper);
  
  /** \details
    Sets the layout name for the CAD definition object.
    \param name [in] A layout name.
  */
  void setLayoutName(const OdString& name);

  /** \details
    Sets the media size for the CAD definition object.
    \param units  [in] A paper unit used for measuring the media size.
    \param width  [in] A width of the media.
    \param height [in] A height of the media.
    \remarks
    The whole drawing will be published (using its extents) and scaled to fit the specified output media size.
  */
  void setMediaSize(const Page::PaperUnits units, const double width, const double height);

  /** \details
    Sets the embedded TTF fonts usage flag value.
    \param state  [in] A new flag value.
    \remarks
    The embedded TTF fonts usage flag determines whether embedded true type fonts should be used (if the flag value is true) or not (if false).
  */
  void setEmbededTrueTypeFonts(const bool state);
  
  /** \details
    Sets the TTF fonts geometry representation flag value.
    \param state  [in] A new flag value.
    \remarks
    The TTF fonts geometry representation flag determines whether true type fonts are represented as geometry (if the flag value is true) or not (if false).
  */
  void setTrueTypeFontAsGeometry(const bool state);
  
  /** \details
    Sets the SHX fonts geometry representation flag value.
    \param state  [in] A new flag value.
    \remarks
    The SHX fonts geometry representation flag determines whether SHX fonts are represented as geometry (if the flag value is true) or not (if false).
  */
  void setSHXTextAsGeometry(const bool state);
  
  /** \details
    Sets the TTF text searchable flag value.
    \param state  [in] A new flag value.
    \remarks
    The TTF text searchable flag determines whether it is possible to search text represented with a true type font (if the flag value is true) or not (if false).
    This flag works only if the TTF fonts geometry representation flag is equal to true.
  */
  void setTextSearchable(const bool state);

  /** \details
    Sets the TTF searchable text as hidden text flag value.
    \param state  [in] A new flag value to be set.
    \remarks
    The TTF searchable text as hidden text flag determines whether it is possible to search with CTRL+F text represented with a true type font (if the flag value is true) or not (if false).
    This flag works only if the TTF fonts geometry representation flag is equal to true.
  */
  void setSearchableTextAsHiddenText(const bool state);

  /** \details
    Sets the TTF searchable text in rendered views flag value.
    \param state  [in] A new flag value to be set.
    \remarks
    The TTF searchable in rendered views flag determines whether it is possible to search with CTRL+F text is exported from rendered views represented with a true type font (if the flag value is true) or not (if false).
  */
  void setSearchableTextInRenderedViews(const bool state);
  
  /** \details
    Sets a value of the flag that determines whether hyperlinks in the CAD definition object should be exported.
    \param state  [in] A new flag value.
    \remarks
    If the hyperlinks should be exported, the flag value is true, otherwise it is equal to false.
  */
  void setExportHyperlinks(const bool state);

  /** \details
    Sets the resolution for the geometry (dots-per-inch, DPI).
    \param dpi  [in] A new resolution value.
  */
  void setGeomDPI(const OdUInt32 dpi);
  
  /** \details
    Sets the resolution for monochrome images (dots-per-inch, DPI).
    \param dpi  [in] A new resolution value.
  */
  void setBWImagesDPI(const OdUInt32 dpi);
  
  /** \details
    Sets the resolution for color images (dots-per-inch, DPI).
    \param dpi  [in] A new resolution value.
  */
  void setColorImagesDPI(const OdUInt32 dpi);

  /** \details
    Sets the measuring flag value.
    \param state [in] A new flag value.
  */
  void setMeasuring(const bool state);

  /** \details
    Sets the color policy for the CAD definition object.
    \param policy  [in] A new color policy.
  */
  void setColorPolicy(const CAD::ColorPolicy policy);

  /** \details
    Sets the simple geometry optimization flag value.
    \param state  [in] A new flag value to be set.
  */
  void setUseSimpleGeomOptimization(const bool state);

  /** \details
    Sets the hidden-line removal flag value. 
    The hidden-line removal flag determines whether the vector hidden-line removal algorithm is used for corresponding viewports (equals true) or not (equals false).
    \param state [in] A new flag value.
  */
  void setUseHLR(bool state);

  /** \details
    Sets the flate compression flag value. 
    The flate compression flag determines whether the compression of internal PDF streams is applied (equals true) or not (equals false).
    \param state [in] A new flag value.
  */
  void setUseFlateCompression(const bool state);

  /** \details
    Sets the DCT(JPG) compression flag value. Default value: true (use DCT compression)
    The DCT compression flag determines whether the additional DCT(JPG) compression is applied for images (equals true) or not (equals false).
    \param state [in] A new flag value.
  */
  void setUseDctCompression(const bool state);

  /** \details
    Sets the DCT compression quality for images. Default value: 50 (50%)
    \param quality [in] A new quality value.
    \remarks
    the compression quality can vary from 10 to 100. If input is lesser than 10, 10 will be set, if greater than 100, so 100 will be set
  */
  void setDctCompressionQuality(const OdUInt16 quality);

  /** \details
    Sets the value of the ASCIIHex encoding flag which determines whether ASCIIHex encoding for internal PDF streams is applied.
    \param state [in] A new flag value.
  */
  void setUseASCIIHexEncoding(const bool state);

  /** \details
    Sets the GsCache flag value. 
    The GsCache flag determines whether the GsCache mechanism is used (equals true) or not (equals false). 
    \param state [in] A new flag value.
  */
  void setUseGsCache(const bool state);

  /** \details
    Sets the multithreaded vectorization flag value.
    This flag determines whether multithreading vectorization is used (equals true) or not (equals false).
    \param state [in] A new flag value.
  */
  void setUseParallelVectorization(const bool state);

  /** \details
    Sets the layer support flag value.
    This flag determines whether PDF layer support is enabled (equals true) or not (equals false).
    \param state [in] A new flag value.
  */
  void setEnableLayers(const bool state);

  /** \details
    Sets the off-layer support flag.
    This flag determines whether adding invisible layers is supported (equals true) or not (equals false).
    \param state [in] A new flag value.
  */
  void setIncludeOffLayers(const bool state);

  /** \details
    Sets a selection set to be exported.
    \param selection [in] A smart pointer to selection set value.
  */
  void setSelectionSet(const OdSelectionSetPtr& selection);

  /** \details
    Retrieves the database associated with the CAD definition object.
    \returns A pointer to the database object.
  */
  OdDbBaseDatabase* getDatabase() const;

  /** \details
    Retrieves the Database Wrapper object associated with the CAD definition object.
    \returns A pointer to the database object.
  */
  DatabaseWrapperInterface* getDatabaseWrapper() const;

  /** \details
    Returns the current layout name for the CAD definition object.
    The method accepts a string value, fills it with the layout name and returns it to a calling subroutine.
    \param name [out] A placeholder for the layout name.
  */  
  void getLayoutName(OdString& name) const;

  /** \details
    Returns the current media size for the CAD definition object.
    The method fills passed values with the paper unit, width and height, then returns them to a calling subroutine.
    \param units  [out] A paper unit used for measuring the media size.
    \param width  [out] A width of the media.
    \param height [out] A height of the media.
    \remarks
    The whole drawing will be published (using its extents) and scaled to fit the specified output media size.
  */
  void getMediaSize(Page::PaperUnits& units, double& width, double& height) const;

  /** \details
    Returns the current value of the embedded TTF fonts usage flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The embedded TTF fonts usage flag determines whether embedded true type fonts should be used (if the flag value is true) or not (if false).
  */
  void getEmbededTrueTypeFonts(bool& state) const;
  
  /** \details
    Returns the current value of the TTF fonts geometry representation flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The TTF fonts geometry representation flag determines whether true type fonts are represented as geometry (if the flag value is true) or not (if false).
  */
  void getTrueTypeFontAsGeometry(bool& state) const;
  
  /** \details
    Returns the current value of the SHX fonts geometry representation flag.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The SHX fonts geometry representation flag determines whether SHX fonts are represented as geometry (if the flag value is true) or not (if false).
  */
  void getSHXTextAsGeometry(bool& state) const;
  
  /** \details
    Returns the current value of the TTF text searchable flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The TTF text searchable flag determines whether it is possible to search text represented with a true type font (if the flag value is true) or not (if false).
    This flag works only if the TTF fonts geometry representation flag is equal to true.
  */
  void getTextSearchable(bool& state) const;

  /** \details
    Returns the current value of the TTF searchable text as hidden text flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The TTF searchable text as hidden text flag determines whether it is possible to search with CTRL+F text represented with a true type font (if the flag value is true) or not (if false).
    This flag works only if the TTF fonts geometry representation flag is equal to true.
  */
  void getSearchableTextAsHiddenText(bool& state) const;

  /** \details
    Returns the current value of the TTF searchable text in rendered views flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    The TTF searchable in rendered views flag determines whether it is possible to search with CTRL+F text is exported from rendered views represented with a true type font (if the flag value is true) or not (if false).
  */
  void getSearchableTextInRenderedViews(bool& state) const;

  /** \details
    Returns the current value of the flag that determines whether hyperlinks in the CAD definition object should be exported.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
    \remarks
    If the hyperlinks should be exported, the flag value is true, otherwise it is equal to false.
  */
  void getExportHyperlinks(bool& state) const;

  /** \details
    Returns the current resolution for the geometry.
    The method fills a passed value with the resolution value and returns it to a calling subroutine.
    \param dpi  [out] A placeholder for the resolution value.
  */
  void getGeomDPI(OdUInt32& dpi) const;
  
  /** \details
    Returns the current resolution for monochrome images.
    The method fills a passed value with the resolution value and returns it to a calling subroutine.
    \param dpi  [out] A placeholder for the resolution value.
  */
  void getBWImagesDPI(OdUInt32& dpi) const;
  
  /** \details
    Returns the current resolution for color images.
    The method fills a passed value with the resolution value and returns it to a calling subroutine.
    \param dpi  [out] A placeholder for the resolution value.
  */
  void getColorImagesDPI(OdUInt32& dpi) const;

  /** \details
    Returns the current measuring flag value.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
  */
  void getMeasuring(bool& state) const;

  /** \details
    Returns the current color policy for the CAD definition object.
    The method fills a passed value with the color policy value and returns it to a calling subroutine.
    \param policy  [out] A placeholder for the current color policy value.
  */
  void getColorPolicy(CAD::ColorPolicy& policy) const;

  /** \details
    Returns the current value of the simple geometry optimization flag.
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
  */
  void getUseSimpleGeomOptimization(bool& state) const;

  /** \details
    Returns the current value of the hidden-line removal flag. 
    This flag determines whether the vector hidden-line removal algorithm is applied for corresponding viewports (equals true) or not (equals false).
    \param state  [out] A placeholder for the flag value.
  */
  void getUseHLR(bool& state) const;

  /** \details
    Returns the current value of the flate compression flag. 
    This flag determines whether the flate compression algorithm is applied for internal PDF streams (equals true) or not (equals false).
    \param state  [out] A placeholder for the flag value.
  */
  void getUseFlateCompression(bool& state) const;

  /** \details
    Returns the current value of the DCT(JPG) compression flag.
    This flag determines whether the DCT compression algorithm is applied for images (equals true) or not (equals false).
    \param state  [out] A placeholder for the flag value.
  */
  void getUseDctCompression(bool& state) const;

  /** \details
    Returns the current value of the DCT(JPG) compression quality.
    The method fills a passed value with the DCT compression quality value and returns it to a calling subroutine.
    \param dpi  [out] A placeholder for the quality value.
  */
  void getDctCompressionQuality(OdUInt16& quality) const;

  /** \details
    Returns the current value of the ASCIIHex encoding flag. 
    This flag determines whether the ASCIIHex encoding of internal PDF streams is applied (equals true) or not (equals false).
    \param state  [out] A placeholder for the flag value.
  */
  void getUseASCIIHexEncoding(bool& state) const;

  /** \details
    Returns the current GsCache flag value. 
    This flag determines whether the GsCache mechanism is applied for internal PDF streams (equals true) or not (equals false).
    The method fills a passed boolean value with the flag value and returns it to a calling subroutine.
    \param state  [out] A placeholder for the flag value.
  */
  void getUseGsCache(bool& state) const;

  /** \details
    Returns the current value of the multithreaded vectorization flag.
    This flag determines whether multithreaded vectorization is used (equals true) or not (equals false).
    \param state  [out] A placeholder for the flag value.
  */
  void getUseParallelVectorization(bool& state) const;

  /** \details
    Returns the current value of the layer support flag.
    This flag determines whether PDF layers are supported (equals true) or not (equals false).
    \param state  [out] A placeholder for the flag value.
  */
  void getEnableLayers(bool& state) const;

  /** \details
    Returns the current value of the invisible layers flag. 
    This flag determines whether adding invisible layers is supported (equals true) or not (equals false).
    \param state  [out] A placeholder for the flag value.
  */
  void getIncludeOffLayers(bool& state) const;

  /** \details
    Returns the current value of selection set. 
    The method fills a passed value and returns it to a calling subroutine.
    \param selection  [out] A placeholder for the smart pointer to selection set value value.
  */
  void getSelectionSet(OdSelectionSetPtr& selection) const;
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdCADDefinition, OdCADDefinition> object.
*/
SMARTPTR(OdCADDefinition);

}
#endif // _PDF_PUBLISH_CADDEFINITION_INCLUDED_

