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
// PdfPublishPage.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_PAGE_INCLUDED_
#define _PDF_PUBLISH_PAGE_INCLUDED_

#include "PdfPublishBaseObject.h"
#include "PdfPublishAnnotation.h"
#include "PdfPublishText.h"
#include "PdfPublishImage.h"
#include "PdfPublishTextField.h"
#include "PdfPublishSignatureField.h"
#include "PdfPublishDropDownList.h"
#include "PdfPublishListBox.h"
#include "PdfPublishRadioButton.h"
#include "PdfPublishCheckBox.h"
#include "PdfPublishLink.h"
#include "PdfPublishSlideTable.h"
#include "PdfPublishButton.h"
#include "PdfPublishTable.h"
#include "PdfPublishTableCreator.h"
#include "PdfPublish2dGeometryReference.h"
#include "PdfPublishCADReference.h"
#include "PdfPublishStickyNote.h"
#include "PdfPublishWatermark.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements a page object for a .pdf document created with Publish SDK.
  A page is determined by two properties: format (size of its sides) and orientation (which side aligns horizontally) 
  and can contain a set of different controls and fields (such as <link OdPdfPublish::OdText, text labels>, 
  <link OdPdfPublish::OdAnnotation, annotations>, <link OdPdfPublish::OdTextField, text fields>, <link OdPdfPublish::OdButton, buttons>, 
  <link OdPdfPublish::OdLink, links>, etc.).
*/
class PDFPUBLISH_TOOLKIT OdPage : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdPage();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPage);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END
 
  /** \details
    Destroys a page object.
  */
  virtual ~OdPage();

  /** \details
    Sets the page format.
    
    \param format [in] A new page <link OdPdfPublish::Page::Format, format> value.
    
    \sa
    <link OdPdfPublish::Page::Format, Page::Format enumeration>.
  */
  void setFormat(Page::Format format);
  
  /** \details
    Sets the page orientation.
    
    \param orientation [in] A new page orientation value.
    
    \sa
    <link OdPdfPublish::Page::Orientation, Page::Orientation enumeration>.
  */
  void setOrientation(Page::Orientation orientation);

  /** \details
    Sets a new page size.

    \param units  [in] Paper size units.
    \param width  [out] A paper width value.
    \param height [out] A paper height value.

    \sa
    <link OdPdfPublish::Page::PaperUnits, Page::PaperUnits enumeration>.
  */
  void setPaperSize(const Page::PaperUnits units, const double width, const double height);
  
  /** \details
    Adds a new <link OdPdfPublish::OdAnnotation, annotation> to the page.
    
    \param annotation [in] A smart pointer to an annotation object that should be added.
    \param location   [in] A rectangle that specifies the location of an added annotation within the page. It determines where the annotation will be placed on the page.
    
    \sa
    <link OdPdfPublish::OdAnnotation, OdAnnotation class>.
  */
  void addAnnotation(const OdAnnotationPtr& annotation, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdText, text> label to the page.
    
    \param text       [in] A smart pointer to a text label that should be added.
    \param location   [in] A rectangle that specifies the location of an added text label within the page. It determines where the text will be placed on the page.
    \param rotation   [in] A rotation angle value to be set.
    
    \remarks
    The location determines the bottom left position of the bounding box of text on the page.
    \sa
    <link OdPdfPublish::OdText, OdText class>.
  */
  void addText(const OdTextPtr& text, const OdRect& location, const double rotation = 0.);

  /** \details
    Adds an <link OdPdfPublish::OdImage, image> to the page.
    
    \param image      [in] A smart pointer to an image object that should be added.
    \param location   [in] A rectangle that specifies the location of an added image within the page. It determines where the image will be placed on the page.
    \param rotation   [in] A rotation angle value to be set.

    \sa
    <link OdPdfPublish::OdImage, OdImage class>.
  */
  void addImage(const OdImagePtr& image, const OdRect& location, const double rotation = 0.);

  /** \details
    Adds a <link OdPdfPublish::OdTable, table> to the page.
    
    \param table      [in] A smart pointer to a table object that should be added.
    \param location   [in] A rectangle that specifies the location of an added table within the page. It determines where the table will be placed on the page.
    
    \sa
    <link OdPdfPublish::OdTable, OdTable class>.
  */
  void addTable(const OdTablePtr& table, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdLink, link> to the page.
    
    \param link       [in] A smart pointer to a link object that should be added.
    \param location   [in] A rectangle that specifies the location of an added link within the page. It determines where the link will be placed on the page.
    
    \sa
    <link OdPdfPublish::OdLink, OdLink class>.
  */
  void addLink(const OdLinkPtr& link, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdButton, button control> to the page.
    
    \param button     [in] A smart pointer to a button control that should be added.
    \param location   [in] A rectangle that specifies the location of an added button control within the page. It determines where the button control will be placed on the page.
    
    \sa
    <link OdPdfPublish::OdButton, OdButton class>.
  */
  void addButton(const OdButtonPtr& button, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdTextField, text field> to the page.
    
    \param text_field [in] A smart pointer to a text field object that should be added.
    \param location   [in] A rectangle that specifies the location of an added text field within the page. It determines where the text field will be placed on the page.
    
    \sa
    <link OdPdfPublish::OdTextField, OdTextField class>.
  */
  void addTextField(const OdTextFieldPtr& text_field, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdSlideTable, table with slides> to the page.
    
    \param slide_table [in] A smart pointer to a slide table object that should be added.
    \param location    [in] A rectangle that specifies the location of an added slide table within the page. It determines where the slide table is placed on the page.
    
    \sa
    <link OdPdfPublish::OdSlideTable, OdSlideTable class>.
  */
  void addSlideTable(const OdSlideTablePtr& slide_table, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdCheckBox, checkbox> to the page.
    
    \param check_box [in] A smart pointer to a checkbox object that should be added.
    \param location  [in] A rectangle that specifies the location of an added checkbox within the page. It determines where the checkbox is placed on the page.
    
    \sa
    <link OdPdfPublish::OdCheckBox, OdCheckBox class>.
  */
  void addCheckBox(const OdCheckBoxPtr& check_box, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdRadioButton, radio button> to the page.
    
    \param radio_button [in] A smart pointer to a radio button object that should be added.
    \param location     [in] A rectangle that specifies the location of an added radio button within the page. It determines where the radio button is placed on the page.
    
    \sa
    <link OdPdfPublish::OdRadioButton, OdRadioButton class>.
  */
  void addRadioButton(const OdRadioButtonPtr& radio_button, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdListBox, list box> to the page.
    
    \param list_box     [in] A smart pointer to a list box object that should be added.
    \param location     [in] A rectangle that specifies the location of an added list box within the page. It determines where the list box is placed on the page.
    
    \sa
    <link OdPdfPublish::OdListBox, OdListBox class>.
  */
  void addListBox(const OdListBoxPtr& list_box, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdDropDownList, drop-down list> (combo box) to the page.
    
    \param drop_down_list [in] A smart pointer to a drop-down list object that should be added.
    \param location       [in] A rectangle that specifies the location of an added drop-down list within the page. It determines where the drop-down list is placed on the page.
    
    \sa
    <link OdPdfPublish::OdDropDownList, OdDropDownList class>.
  */
  void addDropDownList(const OdDropDownListPtr& drop_down_list, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdSignatureField, signature field> to the page.
    
    \param signature_field  [in] A smart pointer to a signature field object that should be added.
    \param location         [in] A rectangle that specifies the location of an added signature field within the page. It determines where the signature field is placed on the page.
    
    \sa
    <link OdPdfPublish::OdSignatureField, OdSignatureField class>.
  */
  void addSignatureField(const OdSignatureFieldPtr& signature_field, const OdRect& location);

  /** \details
    Adds a two-dimensional geometry reference to the page.

    \param geom     [in] A smart pointer to the 2D geometry reference to be added.
    \param location [in] A location where to place the geometry.
  */
  void add2dGeometry(const Od2dGeometryReferencePtr& geom, const OdRect& location);

  /** \details
    Adds a two-dimensional geometry reference to the page.

    \param geom     [in] A smart pointer to the 2D geometry reference to be added.
    
    \remarks
    The location and size of the geometry is defined by the transformation matrix in the geometry reference object passed to the method (geom parameter). 
  */
  void add2dGeometry(const Od2dGeometryReferencePtr& geom);

  /** \details
    Adds a CAD reference object to the page.

    \param CADreferense [in] A smart pointer to a CAD reference object.
    \param location     [in] A rectangle that specifies the page area where the CAD reference should be added.

    \sa
    <link OdPdfPublish::OdCADReference, OdCADReference class>.
  */
  void addCADReference(const OdCADReferencePtr& CADreferense, const OdRect& location);

  /** \details
    Adds a CAD reference object to the page.

    \param CADreferense [in] A smart pointer to a CAD reference object.

    \remarks
    The location and size of the CAD object is defined by the transformation matrix in the CAD reference object passed to the method (CADreference parameter).
    
    \sa
    <link OdPdfPublish::OdCADReference, OdCADReference class>.
  */
  void addCADReference(const OdCADReferencePtr& CADreferense);

  /** \details
    Adds a <link OdPdfPublish::OdStickyNote, sticky note> object to the <link OdPdfPublish::OdPage, page>.
    
    \param note     [in] A smart pointer to a <link OdPdfPublish::OdStickyNote, sticky note> object.
    \param location [in] A <link OdPdfPublish::OdRect, rectangle> that specifies the page area where the <link OdPdfPublish::OdStickyNote, sticky note> appears.
    
    \remarks
    The size and appearance of the <link OdPdfPublish::OdStickyNote, sticky note> object icon is predefined and depends on the viewer application. 
    The position of the icon is specified by the center of the specified rectangle.
    
    \sa
    <link OdPdfPublish::OdStickyNote, OdStickyNote class>.
  */
  void addStickyNote(const OdStickyNotePtr& note, const OdRect& location);

  /** \details
    Adds a <link OdPdfPublish::OdWatermark, watermark> label to the page.

    \param watermark  [in] A smart pointer to a <link OdPdfPublish::OdWatermark, watermark object> that should be added.
    \param location   [in] A <link OdPdfPublish::OdRect, rectangle> that specifies the location of the watermark object within the page. It determines where the watermark text is placed on the page.

    \remarks
    The inserted <link OdPdfPublish::OdWatermark, watermark object> is scaled to the location rectangle size.

    \sa
    <link OdPdfPublish::OdWatermark, OdWatermark class>.
  */
  void addWatermark(const OdWatermarkPtr& watermark, const OdRect& location);
 
  /** \details
    Adds a JavaScript scenario for a specified field on the page.

    \param field_name   [in] A field name to add JavaScript scenario.
    \param source       [in] JavaScript scenario source text.
    \param action_type  [in] An action type that triggers the JavaScript scenario.
    \param source_type  [in] A JavaScript scenario source type.

    \remarks
    The field_name parameter should contain the name of a <link OdPdfPublish::OdButton, button>, <link OdPdfPublish::OdCheckBox, checkbox> or 
    other control object. 
    The specified JavaScript scenario runs when the <link OdPdfPublish::Action::Type, event> specified with the action_type occurs.
    
    \sa
    <link OdPdfPublish::Action::Type, Action::Type enumeration>.
    <link OdPdfPublish::Source::Type, Source::Type enumeration>.
  */
  void addJavaScriptActionByField(const OdString& field_name, const OdString& source, const Action::Type action_type, const Source::Type source_type = Source::kCode);

  /** \details
    Returns the current page format.
    
    \param format [out] A placeholder for the <link OdPdfPublish::Page::Format, format> value. 
                        The method stores the format value in this placeholder and returns it to the calling subroutine.
    
    \sa
    <link OdPdfPublish::Page::Format, Page::Format enumeration>.
  */
  void getFormat(Page::Format& format) const;
  
  /** \details
    Returns the current <link OdPdfPublish::Page::Orientation, page orientation> value.
    
    \param orientation [out] A placeholder for the orientation value. 
                             The method stores the page orientation value in this placeholder and returns it to the calling subroutine.
    
    \sa
    <link OdPdfPublish::Page::Orientation, Page::Orientation enumeration>.
  */
  void getOrientation(Page::Orientation& orientation) const;

  /** \details
    Returns the current page size.
    The method fills two passed double values with width and height values, then returns them to a calling subroutine.

    \param units  [in] The <link OdPdfPublish::Page::PaperUnits, paper size> unit.
    \param width  [out] A placeholder for the paper width value.
    \param height [out] A placeholder for the paper height value.

    \sa
    <link OdPdfPublish::Page::PaperUnits, Page::PaperUnits enumeration>.
  */
  void getPaperSize(const Page::PaperUnits units, double& width, double& height) const;

  /** \details
    Returns all <link OdPdfPublish::OdAnnotation, annotations> that the page contains and their locations.
    The method fills two passed arrays with annotation objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param annotations [out] A placeholder for the page annotations array. 
    \param locations   [out] A placeholder for the annotation locations array. 
    
    \sa
    <link OdPdfPublish::OdAnnotation, OdAnnotation class>.
  */
  void getAnnotations(OdAnnotationPtrArray& annotations, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdText, text labels> that the page contains and their locations.
    The method fills three passed arrays with text label objects, their locations, and their rotation angles, then returns these arrays to a calling subroutine. 
    
    \param texts     [out] A placeholder for the page text labels array. 
    \param locations [out] A placeholder for the text label locations array. 
    \param rotations [out] A placeholder for the array of rotation angles for text labels.
    
    \sa
    <link OdPdfPublish::OdText, OdText class>.
  */
  void getTexts(OdTextPtrArray& texts, OdRectArray& locations, OdDoubleArray& rotations) const;

  /** \details
    Returns all <link OdPdfPublish::OdImage, images> that the page contains and their locations.
    The method fills three passed arrays with image objects, their locations, and their rotation angles, then returns these arrays to a calling subroutine. 
    
    \param images      [out] A placeholder for the page images array. 
    \param locations   [out] A placeholder for the image locations array. 
    \param rotations   [out] A placeholder for the array rotation angles for images.
    
    \sa
    <link OdPdfPublish::OdImage, OdImage class>.
  */
  void getImages(OdImagePtrArray& images, OdRectArray& locations, OdDoubleArray& rotations) const;

  /** \details
    Returns all <link OdPdfPublish::OdTable, tables> that the page contains and their locations.
    The method fills two passed arrays with table objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param tables    [out] A placeholder for the page tables array. 
    \param locations [out] A placeholder for the table locations array. 
    
    <link OdPdfPublish::OdTable, OdTable class>.
  */
  void getTables(OdTablePtrArray& tables, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdLink, links> that the page contains and their locations.
    The method fills two passed arrays with link objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param links     [out] A placeholder for the page links array. 
    \param locations [out] A placeholder for the link locations array. 
    
    \sa
    <link OdPdfPublish::OdLink, OdLink class>.
  */
  void getLinks(OdLinkPtrArray& links, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdButton, buttons> that the page contains and their locations.
    The method fills two passed arrays with button objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param buttons   [out] A placeholder for the page buttons array. 
    \param locations [out] A placeholder for the link locations array. 
    
    \sa
    <link OdPdfPublish::OdButton, OdButton class>.
  */
  void getButtons(OdButtonPtrArray& buttons, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdCheckBox, checkboxes> that the page contains and their locations.
    The method fills two passed arrays with checkbox objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param check_boxes [out] A placeholder for the page checkboxes array. 
    \param locations   [out] A placeholder for the checkbox locations array. 
    
    \sa
    <link OdPdfPublish::OdCheckBox, OdCheckBox class>.
  */
  void getCheckBoxes(OdCheckBoxPtrArray& check_boxes, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdRadioButton, radio buttons> that the page contains and their locations.
    The method fills two passed arrays with radio button objects and their locations, then returns these arrays to a calling subroutine.
    
    \param radio_buttons [out] A placeholder for the page radio buttons array. 
    \param locations     [out] A placeholder for the radio button locations array. 
    
    \sa
    <link OdPdfPublish::OdRadioButton, OdRadioButton class>.
  */
  void getRadioButtons(OdRadioButtonPtrArray& radio_buttons, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdListBox, list boxes> that the page contains and their locations.
    The method fills two passed arrays with list box objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param list_boxes [out] A placeholder for the page list boxes array. 
    \param locations  [out] A placeholder for the list box locations array. 
    
    \sa
    <link OdPdfPublish::OdListBox, OdListBox class>.
  */
  void getListBoxes(OdListBoxPtrArray& list_boxes, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdDropDownList, drop-down lists> that the page contains and their locations.
    The method fills two passed arrays with drop-down list objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param drop_down_lists [out] A placeholder for the page drop-down lists array.
    \param locations       [out] A placeholder for the drop-down list locations array.
    
    <link OdPdfPublish::OdDropDownList, OdDropDownList class>.
  */
  void getDropDownLists(OdDropDownListPtrArray& drop_down_lists, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdSignatureField, signature fields> that the page contains and their locations.
    The method fills two passed arrays with signature field objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param signature_fields [out] A placeholder for the page signature fields array. 
    \param locations        [out] A placeholder for the signature field locations array. 
    
    \sa
    <link OdPdfPublish::OdSignatureField, OdSignatureField class>.
  */  
  void getSignatureFields(OdSignatureFieldPtrArray& signature_fields, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdTextField, text fields>, which the page contains, and their locations.
    The method fills two passed arrays with text field objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param text_fields [out] A placeholder for the page text fields array. 
    \param locations   [out] A placeholder for the text field locations array. 
    
    \sa
    <link OdPdfPublish::OdTextField, OdTextField class>.
  */
  void getTextFields(OdTextFieldPtrArray& text_fields, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdSlideTable, slide tables>, which the page contains, and their locations.
    The method fills two passed arrays with slide table objects and their locations, then returns these arrays to a calling subroutine. 
    
    \param slide_tables [out] A placeholder for the page slide tables array. 
    \param locations    [out] A placeholder for the slide table locations array. 
    
    \sa
    <link OdPdfPublish::OdSlideTable, OdSlideTable class>.
  */
  void getSlideTables(OdSlideTablePtrArray& slide_tables, OdRectArray& locations) const;

  /** \details
    Returns all JavaScript scenarios previously added to the page's field.
    The method fills passed arrays with scenario source text, action types and source types, then returns these arrays to a calling subroutine.

    \param field_name   [in] A field name.
    \param sources      [out] A placeholder for JavaScript scenario source text.
    \param action_types [out] An placeholder for action types.
    \param source_types [out] An placeholder for source types.

    \sa
    <link OdPdfPublish::Action::Type, Action::Type enumeration>.
  */
  void getJavaScriptActionsByField(const OdString& field_name, OdStringArray& sources, OdActionTypeArray& action_types, OdSourceTypeArray& source_types) const;

  /** \details
    Returns two-dimensional geometry references previously added to the page.
    The method fills two passed arrays with geometry references and their locations, then returns these arrays to a calling subroutine.

    \param geoms     [out] A placeholder for geometry references array.
    \param locations [out] A placeholder for geometry locations array.
  */
  void get2dGeoms(Od2dGeometryReferencePtrArray& geoms, OdRectArray& locations) const;
  
  /** \details
    Returns all CAD references previously added to the page.
    The method fills two passed arrays with CAD references and their locations, then returns these arrays to a calling subroutine.

    \param CADreferenses [out] A placeholder for CAD references array.
    \param locations     [out] A placeholder for geometry locations array.
  */
  void getCADReferences(OdCADReferencePtrArray& CADreferenses, OdRectArray& locations) const;
  
  /** \details
    Returns an array of <link OdPdfPublish::OdStickyNote, sticky notes> which the <link OdPdfPublish::OdPage, page> contains.
    The method fills two passed arrays with smart pointers to <link OdPdfPublish::OdStickyNote, sticky note> objects and their locations (represented with rectangles), then returns these arrays to a calling subroutine.

    \param notes     [out] A placeholder for the array of smart pointers to <link OdPdfPublish::OdStickyNote, sticky note objects>.
    \param locations [out] A placeholder for the array of <link OdPdfPublish::OdRect, rectangles>, which represent geometry locations of <link OdPdfPublish::OdStickyNote, sticky notes>.
  */
  void getStickyNotes(OdStickyNotePtrArray& notes, OdRectArray& locations) const;

  /** \details
    Returns all <link OdPdfPublish::OdWatermark, watermarks> that the page contains and their locations.
    The method fills two passed arrays with <link OdPdfPublish::OdWatermark, watermark objects> and their locations, then returns these arrays to a calling subroutine.

    \param watermarks [out] A placeholder for the page watermark array.
    \param locations  [out] A placeholder for the watermark locations array.

    \sa
    <link OdPdfPublish::OdWatermark, OdWatermark class>.
  */
  void getWatermarks(OdWatermarkPtrArray& watermarks, OdRectArray& locations) const;
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdPage, OdPage> object.
*/
SMARTPTR(OdPage);

}
#endif // _PDF_PUBLISH_PAGE_INCLUDED_

