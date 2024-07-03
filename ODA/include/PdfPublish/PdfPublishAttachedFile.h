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
// OdAttachedFile.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_ATTACHED_FILE_INCLUDED_
#define _PDF_PUBLISH_ATTACHED_FILE_INCLUDED_

#include "PdfPublishBaseObject.h"
#include "PdfPublishImage.h"
#include "StringArray.h"
#include "DoubleArray.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
   This class implements an attached file entity in .pdf documents created with Publish SDK.
*/
class PDFPUBLISH_TOOLKIT OdAttachedFile : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdAttachedFile();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdAttachedFile);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys an attached file object.
  */
  virtual ~OdAttachedFile();

  /** \details
    Sets the displayed name of the attached file.
    Use IsValid() to check the status of the operation.

    \param name [in] A new displayed name value.
  */
  void setName(const OdString& name);

  /** \details
    Sets the description of the attached file.

    \param description [in] A new description value.
  */
  void setDescription(const OdString& description);

  /** \details
    Sets the creation date of the attached file.

    \param creation_date [in] A new creation date value.
  */
  void setCreationDate(const OdTimeStamp& creation_date);

  /** \details
    Sets the modification date of the attached file.

    \param mod_date [in] A new modification date value.
  */
  void setModDate(const OdTimeStamp& mod_date);

  /** \details
    Sets the thumbnail image of the attached file.

    \param pImage [in] A smart pointer to a thumbnail raster image object.
  */
  void setThumb(const OdImagePtr& pImage);

  /** \details
    Adds the text collection item for the attached file.

    \param name [in] A new name of collection item value.
    \param item [in] A new collection item value.
    \remarks
    The name shouldn't contain any special characters or spaces. To display this item, the collection should contain a column with the same name.
  */
  void addTextCollectionItem(const OdString& name, const OdString& item);

  /** \details
    Adds the date collection item for the attached file.

    \param name [in] A new name of collection item value.
    \param date [in] A new collection item value.
    \remarks
    The name shouldn't contain any special characters or spaces. To display this item, the collection should contain a column with the same name.
  */
  void addDateCollectionItem(const OdString& name, const OdTimeStamp& date);

  /** \details
    Adds the number collection item for the attached file.

    \param name   [in] A new name of collection item value.
    \param number [in] A new collection item value.
    \remarks
    The name shouldn't contain any special characters or spaces. To display this item, the collection should contain a column with the same name.
  */
  void addNumberCollectionItem(const OdString& name, const double& number);

  /** \details
    Sets the full filename of the attached file.
    Use IsValid() to check the status of the operation.

    \param filename [in] A new filename value.
    \remarks
    It also sets the displayed name of the file if it hasn't been set previously.
  */
  void setFile(const OdString& filename);

  /** \details
    Sets the full filename of the attached file.
    Use IsValid() to check the status of the operation.

    \param file [in] A smart pointer to a StreamBuf object.
    \remarks
    It also sets the displayed name of the file if it hasn't been set previously, if this information is contained in the StreamBuf.
  */
  void setFileStream(OdStreamBufPtr& file);

  /** \details
    Returns the current displayed name of the attached file.
    The method fills a passed string object and returns it to the calling subroutine.

    \param name [out] A placeholder for displayed name value.
  */
  void getName(OdString& name) const;

  /** \details
    Returns the current description of the attached file.
    The method fills a passed string object and returns it to the calling subroutine.

    \param description [out] A placeholder for description value.
  */
  void getDescription(OdString& description) const;

  /** \details
    Returns the current creation date of the attached file.
    The method fills a passed TimeStamp and returns it to the calling subroutine.

    \param creation_date [out] A placeholder for creation date value.
  */
  void getCreationDate(OdTimeStamp& creation_date) const;

  /** \details
    Returns the current modification date of the attached file.
    The method fills a passed TimeStamp and returns it to the calling subroutine.

    \param mod_date [out] A placeholder for modification date value.
  */
  void getModDate(OdTimeStamp& mod_date) const;

  /** \details
    Returns the current thumbnail raster image object of the attached file.
    The method fills a passed raster image object and returns it to the calling subroutine.

    \param pOutImage [out] A placeholder for raster image object.
  */
  void getThumb(OdImagePtr& pOutImage) const;

  /** \details
    Returns a collection of text collection item of the attached file.
    This method fills the passed string array and string array, then returns them to a calling subroutine.

    \param names  [out] A placeholder for collection item names.
    \param images [out] A placeholder for collection item values.
  */
  void getTextCollectionItems(OdStringArray& names, OdStringArray& items) const;

  /** \details
    Returns a collection of date collection item of the attached file.
    This method fills the passed string array and array of TimeStamp objects, then returns them to a calling subroutine.

    \param names  [out] A placeholder for collection item names.
    \param images [out] A placeholder for date collection item values.
  */
  void getDateCollectionItems(OdStringArray& names, OdArray<OdTimeStamp>& dates) const;

  /** \details
    Returns a collection of number collection item of the attached file.
    This method fills the passed string array and array of double, then returns them to a calling subroutine.

    \param names  [out] A placeholder for collection item names.
    \param images [out] A placeholder for number collection item values.
  */
  void getNumberCollectionItems(OdStringArray& names, OdDoubleArray& numbers) const;

  /** \details
    Returns the current image full filename.
    The method fills a passed string object and returns it to the calling subroutine.

    \param out_filename [out] A placeholder for the full filename.
  */
  void getFile(OdString& out_filename) const;

  /** \details 
    Returns the current StreamBuf object.
    The method fills a passed StreamBuf object and returns it to the calling subroutine.
   
    \param file [out] A placeholder for the StreamBuf object.
  */ 
  void getFileStream(OdStreamBufPtr& file) const;

};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdAttachedFile, OdAttachedFile> object.
*/
SMARTPTR(OdAttachedFile);

}
#endif // _PDF_PUBLISH_ATTACHED_FILE_INCLUDED_

