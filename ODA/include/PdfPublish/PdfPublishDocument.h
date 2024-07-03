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
// PdfPublishDocument.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_DOCUMENT_INCLUDED_
#define _PDF_PUBLISH_DOCUMENT_INCLUDED_

#include "PdfPublishBaseObject.h"
#include "PdfPublishPage.h"
#include "PdfPublishBookmark.h"
#include "PdfPublishCollection.h"

#include "DbBaseHostAppServices.h"
#include "Pdf/PdfVersion.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements working with a .pdf document created with Publish SDK.
  A document is a container for other elements and controls 
  (such as <link OdPdfPublish::OdPage, pages>, <link OdPdfPublish::OdImage, images>, <link OdPdfPublish::OdLink, links>, 
  <link OdPdfPublish::OdAnnotation, annotations>, and so on).
*/
class PDFPUBLISH_TOOLKIT OdDocument : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdDocument();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdDocument);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details 
    Destroys the Publish SDK document.
  */
  virtual ~OdDocument();

  /** \details
    Sets PDF format version for the Publish SDK document.
    \param version  [in] Value of the <link OdPDF::PDFFormatVersions, PDF format version> to be set.
    \remarks
    The default value is OdPDF::PDFFormatVersions::kPDFAuto.
  */
  void setVersion(const OdPDF::PDFFormatVersions version);

  /** \details 
    Sets common information about the Publish SDK document.
    \param title    [in] A string that contains the document title.
    \param author   [in] A string that contains the document author.
    \param subject  [in] A string that contains the document subject.
    \param creator  [in] A string that contains information about the document creator.
  */
  void setInformation(const OdString& title, const OdString& author, const OdString& subject, const OdString& creator);
  
  /** \details 
    Adds a new JavaScript scenario to the Publish SDK document.
    \param name         [in] A name of a JavaScript scenario.
    \param source       [in] Source code text of a JavaScript scenario.
    \param source_type  [in] JavaScript scenario source type.
    \remarks 
    The script name must be unique in the set of document scripts. 
    \sa
    <link OdPdfPublish::Source::Type, Source::Type enumeration>.
  */
  void addJavaScript(const OdString& name, const OdString& source, const Source::Type source_type = Source::kCode);
  
  /** \details 
    Adds a new icon <link OdPdfPublish::OdImage, image> to the Publish SDK document.
    \param name   [in] A name of an icon image.
    \param image [in] A smart pointer to an image object.
    
    \sa 
    <link OdPdfPublish::OdImage, OdImage class>.
  */
  void addIconImage(const OdString& name, const OdImagePtr& image);
  
  /** \details 
    Adds a new <link OdPdfPublish::OdPage, page> to the Publish SDK document.
    \param page [in] A smart pointer to the OdPage object that should be added.
    
    \sa 
    <link OdPdfPublish::OdPage, OdPage class>.
  */
  void addPage(const OdPagePtr& page);

  /** \details
    Adds a new attachment file to the ODA Publish document.  

    \param file  [in] A smart pointer to a attached file object.
    \remarks
    Ignored if the Collection is set.
  */
  void addAttachment(const OdAttachedFilePtr& file);

  /** \details
    Sets a collection object to the ODA Publish document.

    \param collection  [in] A smart pointer to a collection object.
  */
  void setCollection(const OdCollectionPtr& collection);

  /** \details
  Sets a new user password for the output PDF document.
  \param user_password [in] A <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains a new value for the output document's user password.
  \remarks
  *Password protection functionality is supported only for PDF versions 1.3 and higher.*
  There are two types of passwords: 
  * User password (Document Open Password) is required to open a PDF document. 
  * Owner password is required to gain full access to the document (owner access). Owner access gives permissions for changing passwords and access permissions for the document. 
  When a password of at least one of these two types is specified, Publish SDK creates an encrypted output document. 
  The type of encryption depends on the PDF version.
  The following rules apply for granting access to PDF document content depending on which passwords and access permissions were specified: 
  * When only the user password is set, <exref target="https://get.adobe.com/reader/">Adobe&reg; Acrobat&reg; Reader&reg;</exref> requires this password to view the document. 
    If the entered password is correct, full access to the document is granted. <link OdPdfPublish::AccessPermissions, Access permissions> are ignored.
    Other applications that read PDF documents take the <link OdPdfPublish::AccessPermissions, access permissions> into account. 
    This means that if the entered user password is correct, the document is opened for viewing (read mode). 
    Other operations can proceed only if appropriate <link OdPdfPublish::AccessPermissions, access permissions> are granted.
  * When only the owner password is specified (the user password is not set), the PDF document can be opened for viewing without entering a password. 
    Other operations are available only if the respective <link OdPdfPublish::AccessPermissions, access permissions> are granted and the owner password is required to proceed with any of the allowed operations.
  * When the owner password is specified and it is not equal to the user password (the user password is also set), the PDF document can be opened for viewing by entering any of the passwords.
    If the user enters the owner password, full access to the document is granted. 
    If the user enters the user password, other operations are allowed only if the respective <link OdPdfPublish::AccessPermissions, access permissions> are granted.
    To proceed with any of these operations, the owner password is required.
  * When both passwords are equal, full access is granted when the entered password is correct. 
  */
  void setUserPassword(const OdString& user_password);

  /** \details
  Sets a new owner password for the output PDF document.
  \param owner_password [in] A <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains a new value for the output document's owner password.
  \remarks
  *Password protection functionality is supported only for PDF versions 1.3 and higher.*
  There are two types of passwords: 
  * User password (Document Open Password) is required to open a PDF document. 
  * Owner password is required to gain full access to the document (owner access). Owner access gives permissions for changing passwords and access permissions for the document. 
  When a password of at least one of these two types is specified, Publish SDK creates an encrypted output document. 
  The type of encryption depends on the PDF version.
  The following rules apply for granting access to PDF document content depending on which passwords and access permissions were specified: 
  * When only the user password is set, <exref target="https://get.adobe.com/reader/">Adobe&reg; Acrobat&reg; Reader&reg;</exref> requires this password to view the document. 
    If the entered password is correct, full access to the document is granted. <link OdPdfPublish::AccessPermissions, Access permissions> are ignored.
    Other applications that read PDF documents take the <link OdPdfPublish::AccessPermissions, access permissions> into account. 
    This means that if the entered user password is correct, the document is opened for viewing (read mode). 
    Other operations can proceed only if the appropriate <link OdPdfPublish::AccessPermissions, access permissions> are granted.
  * When only the owner password is specified (the user password is not set), the PDF document can be opened for viewing without entering a password. 
    Other operations are available only if the respective <link OdPdfPublish::AccessPermissions, access permissions> are granted and the owner password is required to proceed with any of the allowed operations.
  * When the owner password is specified and it is not equal to the user password (the user password is also set), the PDF document can be opened for viewing by entering any of the passwords.
    If the user enters the owner password, full access to the document is granted. 
    If the user enters the user password, other operations are allowed only if the respective <link OdPdfPublish::AccessPermissions, access permissions> are granted.
    To proceed with any of these operations, the owner password is required.
  * When both passwords are equal, full access is granted when the entered password is correct. 
  */
  void setOwnerPassword(const OdString& owner_password);

  /** \details
  Sets new <link OdPdfPublish::AccessPermissions, access permission flags> for the output PDF document.
  \param flags [in] Value of the <link OdPdfPublish::AccessPermissions, access permission flags> to be set.
  */
  void setAccessPermissionFlags(const AccessPermissions::AccessPermissionsFlags flags);

  /** \details
    Appends a new root <link OdPdfPublish::OdBookmark, bookmark> to the PDF document.
    \param bookmark [in] A smart pointer to the <link OdPdfPublish::OdBookmark, OdBookmark> object.

    \sa
    <link OdPdfPublish::OdBookmark, OdBookmark class>.
  */
  void appendRootBookmark(const OdBookmarkPtr bookmark);

  /** \details
    Sets root bookmarks for the PDF document.
    \param bookmarks [in] An array of smart pointers to <link OdPdfPublish::OdBookmark, OdBookmark> objects.
    \remarks
    The method replaces children bookmarks which previously were set for the document.

    \sa
    <link OdPdfPublish::OdBookmark, OdBookmark class>.
  */
  void setRootBookmarks(const OdBookmarkPtrArray& bookmarks);

  /** \details
    Returns PDF format version for the Publish SDK document.
    This method fills the passed the value of the <link OdPDF::PDFFormatVersions, PDF format version> and returns them to a calling subroutine.

    \param version    [out] A placeholder for the PDF format version value.
  */
  void getVersion(OdPDF::PDFFormatVersions& version) const;

  /** \details
    Returns the current common information about the Publish SDK document.
    This method fills the passed strings and returns them to a calling subroutine.

    \param title    [out] A placeholder for the document title.
    \param author   [out] A placeholder for the document author.
    \param subject  [out] A placeholder for the document subject.
    \param creator  [out] A placeholder for the information about the document creator.
  */
  void getInformation(OdString& title, OdString& author, OdString& subject, OdString& creator) const;
  
  /** \details 
    Returns the collection of JavaScript scenarios encapsulated in the Publish SDK document.
    This method fills the passed arrays with names, source code text and source code types, then returns them to a calling subroutine.
    
    \param names        [out] A placeholder for JavaScript scenario names.
    \param sources      [out] A placeholder for JavaScript scenario source code text.
    \param source_types [out] A placeholder for JavaScript scenario source code types.
  */
  void getJavaScripts(OdStringArray& names, OdStringArray& sources, OdSourceTypeArray& source_types) const;
  
  /** \details
    Returns a collection of icon <link OdPdfPublish::OdImage, images> from the Publish SDK document.
    This method fills the passed string array and smart pointer array with image names and pointers to image objects, then returns them to a calling subroutine.
    
    \param names  [out] A placeholder for icon image names.
    \param images [out] A placeholder for an array of smart pointers that point to the document icon images.
    
    \sa 
    <link OdPdfPublish::OdImage, OdImage class>.
  */
  void getIconImages(OdStringArray& names, OdImagePtrArray& images) const;

  /** \details 
    Returns the array of <link OdPdfPublish::OdPage, pages> that the Publish SDK document contains.
    This method fills the passed array with the OdPage object that represents the document pages and returns it to a calling subroutine.
    
    \param pages [out] A placeholder for the document pages array.
    
    \sa 
    <link OdPdfPublish::OdPage, OdPage class>.
  */
  void getPages(OdPagePtrArray& pages) const;

  /** \details
    Returns a collection of attached file object.
    The method fills a passed collection of attached file object and returns it to the calling subroutine.

   \param files  [out]  A placeholder for collection of attached file object.
  */
  void getAttachments(OdAttachedFilePtrArray& files) const;

  /** \details
    Returns the current collection object.
    The method fills a passed collection object and returns it to the calling subroutine.

   \param collection   [out]  A placeholder for collection object.
  */
  void getCollection(OdCollectionPtr& collection) const;

  /** \details
  Retrieves the current user password for the output PDF document.
  \param user_password [out] An <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> object that acts as a placeholder for the current PDF document user password.
  \remarks
  *Password protection functionality is supported only for PDF versiond 1.3 and higher.*
  There are two types of passwords: 
  * User password (Document Open Password) is required to open a PDF document. 
  * Owner password is required to gain full access to the document (owner access). Owner access gives permissions for changing passwords and access permissions for the document. 
  When a password of at least one of these two types is specified, Publish SDK creates an encrypted output document. 
  The type of encryption depends on the PDF version.
  The following rules apply for granting access to PDF document content depending on which passwords and access permissions were specified: 
  * When only the user password is set, <exref target="https://get.adobe.com/reader/">Adobe&reg; Acrobat&reg;  Reader&reg;</exref> requires this password to view the document. 
    If the entered password is correct, full access to the document is granted. <link OdPdfPublish::AccessPermissions, Access permissions> are ignored.
    Other applications that read PDF documents take the <link OdPdfPublish::AccessPermissions, access permissions> into account. 
    This means that if the entered user password is correct, the document is opened for viewing (read mode). 
    Other operations can proceed only if the appropriate <link OdPdfPublish::AccessPermissions, access permissions> are granted.
  * When only the owner password is specified (the user password is not set), the PDF document can be opened for viewing without entering a password. 
    Other operations are available only if the respective <link OdPdfPublish::AccessPermissions, access permissions> are granted, and the owner password is required to proceed with any of the allowed operations.
  * When the owner password is specified and it is not equal to the user password (the user password is also set), the PDF document can be opened for viewing by entering any of the passwords.
    If the user enters the owner password, full access to the document is granted. 
    If the user enters the user password, other operations are allowed only if the respective <link OdPdfPublish::AccessPermissions, access permissions> are granted.
    To proceed with any of these operations, the owner password is required.
  * When both passwords are equal, full access is granted when the entered password is correct. 
  The method fills the passed parameter with the current user password and returns it to a calling subroutine.
  */
  void getUserPassword(OdString& user_password) const;

  /** \details
  Retrieves the current owner password for the output PDF document.
  \param owner_password [out] An <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> object that acts as a placeholder for the current PDF document owner password.
  \remarks
  *Password protection functionality is supported only for PDF versions 1.3 and higher.*
  There are two types of passwords: 
  * User password (Document Open Password) is required to open a PDF document. 
  * Owner password is required to gain full access to the document (owner access). Owner access gives permissions for changing passwords and access permissions for the document. 
  When a password of at least one of these two types is specified, Publish SDK creates an encrypted output document. 
  The type of encryption depends on the PDF version.
  The following rules apply for granting access to PDF document content depending on which passwords and access permissions were specified: 
  * When only the user password is set <exref target="https://get.adobe.com/reader/">Adobe&reg; Acrobat&reg; Reader&reg;</exref> requires this password to view the document. 
    If the entered password is correct, full access to the document is granted. <link OdPdfPublish::AccessPermissions, Access permissions> are ignored.
    Other applications that read PDF documents take the <link OdPdfPublish::AccessPermissions, access permissions> into account. 
    This means that if the entered user password is correct, the document is opened for viewing (read mode). 
    Other operations can proceed only if the appropriate <link OdPdfPublish::AccessPermissions, access permissions> are granted.
  * When only the owner password is specified (the user password is not set), the PDF document can be opened for viewing without entering a password. 
    Other operations are available only if the respective <link OdPdfPublish::AccessPermissions, access permissions> are granted, and the owner password is required to proceed with any of the allowed operations.
  * When the owner password is specified and it is not equal to the user password (the user password is also set), the PDF document can be opened for viewing by entering any of the passwords.
    If the user enters the owner password, full access to the document is granted. 
    If the user enters the user password, other operations are allowed only if the respective <link OdPdfPublish::AccessPermissions, access permissions> are granted.
    To proceed with any of these operations the owner password is required.
  * When both passwords are equal, full access is granted when the entered password is correct. 
  The method fills the passed parameter with the current owner password and returns it to a calling subroutine.
  */
  void getOwnerPassword(OdString& owner_password) const;

  /** \details
  Returns the flag <link OdPdfPublish::AccessPermissions, access permission flags> for the output PDF document.
  \returns A value of the <link OdPdfPublish::AccessPermissions, AccessPermissions> data type that represents the current access permission flags.
  */
  AccessPermissions::AccessPermissionsFlags getAccessPermissionFlags() const;

  /** \details
    Returns root bookmarks for the current bookmark from the PDF document.
    The method fills the passed array with smart pointers to <link OdPdfPublish::OdBookmark, OdBookmark> objects that represents the child bookmarks of the current bookmark and returns it to a calling subroutine.
    \param bookmarks [out] A placeholder for the array of smart pointers to <link OdPdfPublish::OdBookmark, OdBookmark> objects.

    \sa
    <link OdPdfPublish::OdBookmark, OdBookmark class>.
  */
  void getRootBookmarks(OdBookmarkPtrArray& bookmarks) const;

  /** \details
    Sets a new application services object for the document.
    \param pHostApp [in] A pointer to a database application services object.
  */
  void setHostServices(OdDbBaseHostAppServices* pHostApp);

  /** \details
    Gets the current application services object for the document.
    \return Returns a pointer to the database application services object.
  */
  OdDbBaseHostAppServices* appServices() const;
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdDocument, OdDocument> object.
*/
SMARTPTR(OdDocument);

}
#endif // _PDF_PUBLISH_DOCUMENT_INCLUDED_

