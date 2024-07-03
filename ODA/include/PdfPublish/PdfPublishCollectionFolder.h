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
// PdfPublishCollectionFolder.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_ATTACHED_FOLDER_INCLUDED_
#define _PDF_PUBLISH_ATTACHED_FOLDER_INCLUDED_

#include "PdfPublishBaseObject.h"
#include "PdfPublishImage.h"
#include "StringArray.h"
#include "DoubleArray.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

  class OdAttachedFolder;
  /** \details
    A data type that represents a smart pointer to an <link OdPdfPublish::OdAttachedFolder, OdAttachedFolder> object.
  */
  SMARTPTR(OdAttachedFolder);

/** \details
   This class implements an attached folder entity in .pdf documents created with Publish SDK.
*/
class PDFPUBLISH_TOOLKIT OdAttachedFolder : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdAttachedFolder();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdAttachedFolder);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys an attached folder object.
  */
  virtual ~OdAttachedFolder();

  /** \details
    Sets the displayed name of the attached folder.
    Use IsValid() to check the status of the operation.

    \param name [in] A new displayed name value.
  */
  void setName(const OdString& name);

  /** \details
    Sets the description of the attached folder.

    \param description [in] A new description value.
  */
  void setDescription(const OdString& description);

  /** \details
    Sets the creation date of the attached folder.

    \param creation_date [in] A new creation date value.
  */
  void setCreationDate(const OdTimeStamp& creation_date);

  /** \details
    Sets the modification date of the attached folder.

    \param mod_date [in] A new modification date value.
  */
  void setModDate(const OdTimeStamp& mod_date);

  /** \details
    Sets the thumbnail image of the attached folder.

    \param pImage [in] A smart pointer to a thumbnail raster image object.
  */
  void setThumb(const OdImagePtr& pImage);

  /** \details
    Adds the text collection item for the attached folder.

    \param name [in] A new name of collection item value.
    \param item [in] A new collection item value.
    \remarks
    The name shouldn't contain any special characters or spaces. To display this item, the collection should contain a column with the same name.
  */
  void addTextCollectionItem(const OdString& name, const OdString& item);

  /** \details
    Adds the date collection item for the attached folder.

    \param name [in] A new name of collection item value.
    \param date [in] A new collection item value.
    \remarks
    The name shouldn't contain any special characters or spaces. To display this item, the collection should contain a column with the same name.
  */
  void addDateCollectionItem(const OdString& name, const OdTimeStamp& date);

  /** \details
    Adds the number collection item for the attached folder.

    \param name   [in] A new name of collection item value.
    \param number [in] A new collection item value.
    \remarks
    The name shouldn't contain any special characters or spaces. To display this item, the collection should contain a column with the same name.
  */
  void addNumberCollectionItem(const OdString& name, const double& number);

  /** \details
    Adds the child attached folder object for the attached folder.

    \param folder   [in] A smart pointer to a attached folder object.
  */
  void addChildFolder(const OdAttachedFolderPtr& folder);

  /** \details
    Adds the attached folder object for the attached folder.

    \param file   [in] A smart pointer to a attached file object.
  */
  void addFile(const OdAttachedFilePtr& file);

  /** \details
    Returns the current displayed name of the attached folder.
    The method fills a passed string object and returns it to the calling subroutine.

    \param name [out] A placeholder for displayed name value.
  */
  void getName(OdString& name) const;

  /** \details
    Returns the current description of the attached folder.
    The method fills a passed string object and returns it to the calling subroutine.

    \param description [out] A placeholder for description value.
  */
  void getDescription(OdString& description) const;

  /** \details
    Returns the current creation date of the attached folder.
    The method fills a passed TimeStamp and returns it to the calling subroutine.

    \param creation_date [out] A placeholder for creation date value.
  */
  void getCreationDate(OdTimeStamp& creation_date) const;

  /** \details
    Returns the current modification date of the attached folder.
    The method fills a passed TimeStamp and returns it to the calling subroutine.

    \param mod_date [out] A placeholder for modification date value.
  */
  void getModDate(OdTimeStamp& mod_date) const;

  /** \details
    Returns the current thumbnail raster image object of the attached folder.
    The method fills a passed raster image object and returns it to the calling subroutine.

    \param pOutImage [out] A placeholder for raster image object.
  */
  void getThumb(OdImagePtr& pOutImage) const;

  /** \details
    Returns a collection of text collection item of the attached folder.
    This method fills the passed string array and string array, then returns them to a calling subroutine.

    \param names  [out] A placeholder for collection item names.
    \param images [out] A placeholder for collection item values.
  */
  void getTextCollectionItems(OdStringArray& names, OdStringArray& items) const;

  /** \details
    Returns a collection of date collection item of the attached folder.
    This method fills the passed string array and array of TimeStamp objects, then returns them to a calling subroutine.

    \param names  [out] A placeholder for collection item names.
    \param images [out] A placeholder for date collection item values.
  */
  void getDateCollectionItems(OdStringArray& names, OdArray<OdTimeStamp>& dates) const;

  /** \details
    Returns a collection of number collection item of the attached folder.
    This method fills the passed string array and array of double, then returns them to a calling subroutine.

    \param names  [out] A placeholder for collection item names.
    \param images [out] A placeholder for number collection item values.
  */
  void getNumberCollectionItems(OdStringArray& names, OdDoubleArray& numbers) const;

  /** \details
    Returns a collection of child attached folder of the attached folder.
    This method fills the passed array of smart pointer to OdAttachedFolder, then returns them to a calling subroutine.

    \param folders  [out] A placeholder for collection of attached folder.
  */
  void getChildFolders(OdAttachedFolderPtrArray& folders) const;

  /** \details
    Returns a collection of attached file of the attached folder.
    This method fills the passed array of smart pointer to OdAttachedFile, then returns them to a calling subroutine.

    \param folders  [out] A placeholder for collection of attached file.
  */
  void getFiles(OdAttachedFilePtrArray& files) const;

};

}
#endif // _PDF_PUBLISH_ATTACHED_FOLDER_INCLUDED_

