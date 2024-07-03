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
// PdfPublishStickyNote.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_STICKIY_NOTE_INCLUDED_
#define _PDF_PUBLISH_STICKIY_NOTE_INCLUDED_

#include "PdfPublishBaseObject.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements functionality for work with a sticky note in a PDF document created with Publish SDK.
  A sticky note allows specification of an icon on the page that, when is clicked, displays a popup window with text information.
*/
class PDFPUBLISH_TOOLKIT OdStickyNote : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdStickyNote();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdStickyNote);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END
 
  /** \details
    Destroys the sticky note object.
  */
  virtual ~OdStickyNote();

  /** \details
    Sets the <link OdPdfPublish::StickyNotes::StickyNoteTypes, type> of the sticky note object.
    \param type [in] A new <link OdPdfPublish::StickyNotes::StickyNoteTypes, type> for the sticky note object.
    \remarks
    The <link OdPdfPublish::StickyNotes::StickyNoteTypes, type> determines predefined icon to be displayed when the sticky note is rendered.
  */
  void setStickyNoteType(const StickyNotes::StickyNoteTypes& type);

  /** \details
    Sets the location of the popup window where the sticky note object appears.
    \param popup_location [in] A <exref target="https://docs.opendesign.com/tkernel/ODRECT.html">rectangle</exref> that specifies the page area where the popup window appears.
  */
  void setPopupLocation(const OdRect& popup_location);

  /** \details
    Sets a new value of the popup window flag for the sticky note object.
    The popup window flag determines whether a reader application displays the sticky note object when opens the PDF document (equals true).
    Otherwise, the reader application doesn't display the sticky note (equals false). 
    Default value of the flag equals false.
    \param state  [in] A new flag value.
  */
  void setOpen(const bool state);

  /** \details
    Sets the content displayed in the popup window for the sticky note object.
    \param value [in] A <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains the displayed contents.
  */
  void setContents(const OdString& value);

  /** \details
    Sets the title of the popup window for the sticky note object.
    \param value [in] A <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains the title of the popup window.
    \remarks
    Usually, the popup window title contains the name of the user who has added the note.
  */
  void setTitle(const OdString& value);

  /** \details
    Sets the description of the sticky note object.
    \param value [in] A <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains the description of the sticky note object.
    \remarks
    A reader application display the description only when a user views the sticky note properties.
  */
  void setDescription(const OdString& value);

  /** \details
    Sets the creation date and time of the sticky note object.
    \param value [in] An <exref target="https://docs.opendesign.com/tkernel/OdTimeStamp.html">OdTimeStamp</exref> object that contains the date and time of the sticky note object creation.
  */
  void setCreationDate(const OdTimeStamp& value);

  /** \details
    Sets the icon opacity for the sticky note object.
    \param value [in] A new opacity value.
    \remarks
    The opacity value should be in the range between 0 and 100. Default value is 100.
  */
  void setOpacity(const OdUInt8& value);

  /** \details
    Sets the color of the sticky note object.
    \param color [in] A new color value.
    \remarks
    The color value affects the icon and the frame of the popup window that displays the sticky note content.
  */
  void setColor(const ODCOLORREF color);
  
  /** \details
    Sets a new value of the lock flag for the sticky note. 
    The lock flag determines whether a user can not edit the content of the sticky note object (equals true); otherwise, a user can edit the sticky note object content (equals false).
    \param state [in] A new flag value.
  */
  void setLock(const bool state);
  
  /** \details
    Sets a new value of the <link OdPdfPublish::StickyNotes::StickyNoteMarkedStates, marked state> for the sticky object. 
    \param marked_state [in] A new value of the <link OdPdfPublish::StickyNotes::StickyNoteMarkedStates, marked state>.
    \remarks
    Default marked state value equals to the <link OdPdfPublish::StickyNotes::StickyNoteMarkedStates::kUnmarkedState, kUnmarkedState>.
  */
  void setMarkedState(const StickyNotes::StickyNoteMarkedStates& marked_state);

  /** \details
    Sets the <link OdPdfPublish::StickyNotes::StickyNoteReviewStates, review status> for the sticky note object.
    \param review_state [in] A new <link OdPdfPublish::StickyNotes::StickyNoteReviewStates, review status> for the sticky note object.
    \remarks
    Default review status equals to the <link OdPdfPublish::StickyNotes::StickyNoteReviewStates::kNone, kNone> value.
  */
  void setReviewState(const StickyNotes::StickyNoteReviewStates& review_state);

  /** \details
    Returns the <link OdPdfPublish::StickyNotes::StickyNoteTypes, type> of the sticky note object.
    The method fills a passed instance of the <link OdPdfPublish::StickyNotes::StickyNoteTypes, StickyNoteTypes enumeration> value with the current type of the sticky note object and returns it to a calling subroutine.
    \param type [out] A placeholder for the <link OdPdfPublish::StickyNotes::StickyNoteTypes, type> of the sticky note object.
  */
  void getStickyNoteType(StickyNotes::StickyNoteTypes& type) const;

  /** \details
    Returns the location of the popup window that displays the sticky note object's content.
    The method fills the content of the passed <exref target="https://docs.opendesign.com/tkernel/ODRECT.html">OdRect</exref> instance with location data and returns it to a calling subroutine.
    \param popup_location [out] A placeholder for the <exref target="https://docs.opendesign.com/tkernel/ODRECT.html">rectangle</exref> that represents the location of the popup window.
  */
  void getPopupLocation(OdRect& popup_location) const;

  /** \details
    Returns the current value of the popup window flag for the sticky note object.
    The popup window flag determines whether a reader application displays the sticky note object when opens the PDF document (equals true).
    Otherwise, the reader application doesn't display the sticky note (equals false). 
    \param state  [out] A placeholder for the popup window flag's value.
    \remarks
    The method fills a passed boolean value with the current value of the popup window flag and returns it to a calling subroutine.
  */
  void getOpen(bool& state) const;

  /** \details
    Returns the content displayed in the popup window for the sticky note object.
    The method fills a passed <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> object with the popup window content and returns it to a calling subroutine.
    \param value [out] A placeholder for the <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains the popup window content for the sticky note object.
  */
  void getContents(OdString& value) const;

  /** \details
    Returns the title of the popup window for the sticky note object.
    The method fills a passed <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> object with the popup window's title and returns it to a calling subroutine.
    \param value [in] A placeholder for the <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains the title of the popup window.
    \remarks
    Usually, the popup window title contains the name of the user who has added the note.
  */
  void getTitle(OdString& value) const;

  /** \details
    Returns the description of the sticky note object.
    The method fills a passed <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> object with the sticky note description and returns it to a calling subroutine.
    \param value [in] A placeholder for the <exref target="https://docs.opendesign.com/tkernel/OdString.html">string</exref> that contains the description of the sticky note object.
    \remarks
    A reader application display the description only when a user views the sticky note properties.
  */
  void getDescription(OdString& value) const;

  /** \details
    Returns the creation date and time of the sticky note object.
    The method fills a passed <exref target="https://docs.opendesign.com/tkernel/OdTimeStamp.html">OdTimeStamp</exref> object with the sticky note object's creation date and time and returns it to a calling subroutine.
    \param value [in] A placeholder for the <exref target="https://docs.opendesign.com/tkernel/OdTimeStamp.html">OdTimeStamp</exref> object that contains the date and time of the sticky note object creation.
    \returns true if creation date and time are set; otherwise, creation date and time are not set and method returns false.
  */
  bool getCreationDate(OdTimeStamp& value) const;

  /** \details
    Returns the icon opacity for the sticky note object.
    The method fills a passed unsigned 8-bit integer value with the opacity value and returns it to a calling subroutine.
    \param value [in] A placeholder for the opacity value.
    \remarks
    The opacity value should be in the range between 0 and 100. Default value is 100.
  */
  void getOpacity(OdUInt8& value) const;

  /** \details
    Returns the current color of the sticky note object.
    The method fills a passed ODCOLORREF value with the sticky note object's color and returns it to a calling subroutine.
    \param color [in] A placeholder for the color value.
    \remarks
    The color value affects the icon and the frame of the popup window that displays the sticky note content.
  */
  void getColor(ODCOLORREF& color) const;
  
  /** \details
    Returns the current value of the lock flag for the sticky note. 
    The lock flag determines whether a user can not edit the content of the sticky note object (equals true); otherwise, a user can edit the sticky note object content (equals false).
    \param state [in] A placeholder for the current flag value.
    \remarks 
    The method fills a passed boolean value with the current value of the lock flag and returns it to a calling subroutine.
  */
  void getLock(bool& state) const;

  /** \details
    Returns the current value of the <link OdPdfPublish::StickyNotes::StickyNoteMarkedStates, marked state> for the sticky object. 
    The method fills the passed value of the <link OdPdfPublish::StickyNotes::StickyNoteMarkedStates, StickyNoteMarkedStates enumeration> with the current value of the marked state and returns it to a calling subroutine.
    \param marked_state [in] A placeholder for the current value of the <link OdPdfPublish::StickyNotes::StickyNoteMarkedStates, marked state>.
    \remarks
    Default marked state value equals to the <link OdPdfPublish::StickyNotes::StickyNoteMarkedStates::kUnmarkedState, kUnmarkedState>.
  */
  void getMarkedState(StickyNotes::StickyNoteMarkedStates& marked_state) const;

  /** \details
    Retrieves the <link OdPdfPublish::StickyNotes::StickyNoteReviewStates, review status> for the sticky note object.
    The method fills a passed value of the <link OdPdfPublish::StickyNotes::StickyNoteReviewStates, StickyNoteReviewStates enumeration> with the current value of the review status and returns it to a calling subroutine.
    \param review_state [in] A placeholder for the <link OdPdfPublish::StickyNotes::StickyNoteReviewStates, review status> value.
    \remarks
    Default review status equals to the <link OdPdfPublish::StickyNotes::StickyNoteReviewStates::kNone, kNone> value.
  */
  void getReviewState(StickyNotes::StickyNoteReviewStates& review_state) const;
  
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdStickyNote, OdStickyNote> object.
*/
SMARTPTR(OdStickyNote);

}
#endif // _PDF_PUBLISH_STICKIY_NOTE_INCLUDED_

