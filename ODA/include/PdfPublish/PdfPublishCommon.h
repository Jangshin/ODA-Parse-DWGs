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


#ifndef _PDFPUBLISH_COMMON_INCLUDED_
#define _PDFPUBLISH_COMMON_INCLUDED_

#include "OdaCommon.h"

/** \details 
Contains declarations for Publish SDK.
<group TD_Namespaces>
*/
namespace OdPdfPublish {

  /** \details 
  Contains declarations representing the result of the publishing operations.
  Values declared within this enumeration are returned by <link !!OVERLOADED_Methods_exportPdf_OdPdfPublish::OdFile, exportPdf methods> 
  of the <link OdPdfPublish::OdFile, OdFile> class.
  */
  enum PdfPublishResult
  {
    eOk                       = 0,          // Operation successfully finished.
    eInternalError            = 1,          // An internal error occurred during the operation.
    eEmptyInputArray          = 2,          // The input array is empty.
    eNotSortedArray           = 3,          // The input array is not sorted.
    eDuplicatedElement        = 4,          // A duplication of elements was found.
    eNullDocument             = 5,          // Tried to process the operation with a null smart pointer to the Publish SDK document.
    eKeyNotFound              = 6,          // The specified key value is not found.
    eNullBaseName             = 7,          // The name of the base object is null.
    eNotImplementedYet        = 8,          // The feature currently is not implemented.
    exOdError                 = 0x00020000, // ODA base class error occured during the operation.
    //DOM-IGNORE-BEGIN
    // For internal use only.
    eLastErrorNum             = 0xFFFF
    //DOM-IGNORE-END
  };

  /** \details 
  Contains declarations related to activation of an <link OdPdfPublish::OdAnnotation, annotation>.
  */
  namespace Activation {
    
    /** \details 
    Determines how an <link OdPdfPublish::OdAnnotation, annotation> can be activated.
    */
    enum When {
      kExplicit,  // Annotation stays inactive until it is directly activated by a user or a script.
      kOpened,    // Annotation is activated when its page is opened.
      kVisible    // Annotation is activated when its page becomes visible.
    };
  }

  /** \details 
  Contains declarations related to deactivation of an <link OdPdfPublish::OdAnnotation, annotation>.
  */
  namespace Deactivation {
    
    /** \details 
    Determines how an <link OdPdfPublish::OdAnnotation, annotation> can be deactivated.
    */
    enum When {
      kExplicit,    // Annotation stays active until it is directly deactivated by a user or a script.
      kClosed,      // Annotation is deactivated when its page is closed.
      kNotVisible   // Annotation is deactivated when its page becomes invisible.
    };
  }

  /** \details 
  Contains page settings for Publish SDK documents.
  */
  namespace Page {
    
    /** \details 
    Page formats (sizes) supported by Publish SDK. 
    */
    enum Format {
      kA4 = 0,    // Format A4 (842 points width, 1190 points height).
      kA3,        // Format A3 (595 points width, 842 points height).
      kP11x17,    // Format P11x17.
      kA5,        // Format A5.
      kB4JIS,     // Format B4JIS.
      kB5JIS,     // Format B5JIS.
      kExecutive, // Format Executive.
      kLegal,     // Format Legal.
      kLetter,    // Format Letter.
      kTabloid,   // Format Tabloid.
      kB4ISO,     // Format B4ISO.
      kB5ISO,     // Format B5ISO.
      kCustom,    // Custom format.
      //DOM-IGNORE-BEGIN
      // For internal use only.
      kLastFormat
      //DOM-IGNORE-END
    };

    /** \details 
    Page orientations supported by Publish SDK. 
    */
    enum Orientation {
      kPortrait = 0,  // Portrait orientation.
      kLandscape,     // Landscape orientation.

      //DOM-IGNORE-BEGIN
      // For internal use only.
      kLastOrientation
      //DOM-IGNORE-END
    };

    /** \details 
    Paper measurement units supported by Publish SDK. 
    */
    enum PaperUnits
    {
      kInches         = 0,   // Inch measurement units.
      kMillimeters    = 1,   // Millimeter measurement units.
      kPixels         = 2    // Pixel measurement units.
    };
  }

  /** \details 
  Contains camera settings for Publish SDK documents.
  */
  namespace Camera {
    
    /** \details 
    Camera projection types supported by Publish SDK. 
    */
    enum Projection {
      kOrthographic = 0,  // Orthographic camera projection.
      kPerspective        // Perspective camera projection.
    };
  }

  /** \details 
  Contains light settings for Publish SDK documents.
  */
  namespace Lighting
  {
  
    /** \details 
    Light modes supported by Publish SDK. 
    */
    enum Mode {
      kDefault = 0,   // Default light mode. Currently is not applied.
      kArtwork,       // Light mode is inherited from the annotation.
      kNone,          // No light mode is used.
      kWhite,         // White light mode is used.
      kDay,           // Day light mode is used.
      kBright,        // Bright light mode is used.
      kPrimaryColor,  // Primary color light mode is used.
      kNight,         // Night light mode is used.
      kBlue,          // Blue light mode is used.
      kRed,           // Red light mode is used.
      kCube,          // Cube light mode is used.
      kCADOptimized,  // Optimized light from CAD is used.
      kHeadlamp       // Head lamp light mode is used.
    };
  }
  
  /** \details 
  Contains rendering settings for Publish SDK documents.
  */
  namespace Rendering
  {
    /** \details 
    Rendering modes supported by Publish SDK. 
    */
    enum Mode {
      kDefault = 0,                   // Default rendering mode. Currently is not applied.
      kSolid,                         // Textured and lighted faces are rendered.
      kSolidWireframe,                // Textured, lighted faces and monochrome tessellation edges are rendered.
      kSolidOutline,                  // Textured, lighted faces and monochrome silhouette edges are rendered.
      kBoundingBox,                   // Monochrome bounding box edges are rendered.
      kTransparent,                   // Textured and lighted transparent faces are rendered.
      kTransparentWireframe,          // Textured, lighted transparent faces and monochrome tessellation edges are rendered.
      kTransparentBoundingBox,        // Monochrome bounding box transparent faces are rendered.
      kTransparentBoundingBoxOutline, // Monochrome edges and bounding box transparent faces are rendered. 
      kIllustration,                  // Monochrome unlighted faces and silhouette edges are rendered. 
      kShadedIllustration,            // Textured, lighted highly emissive faces and monochrome silhouette edges are rendered.
      kWireframe,                     // Monochrome tessellation edges are rendered. 
      kShadedWireframe,               // Interpolated and lighted tessellation edges are rendered.
      kHiddenWireframe,               // Monochrome faces and tessellation edges are rendered. 
      kVertices,                      // Monochrome vertices are rendered.
      kShadedVertices                 // Colored and lighted vertices are rendered.
    };
  }

    /** \details 
    Contains declarations for user <link OdPdfPublish::OdArtwork, artwork> support in Publish SDK. 
    */
  namespace Artwork {
  
    /** \details 
    The <link OdPdfPublish::OdArtwork, artwork> object animation styles. 
    */
    enum AnimationStyle {
      kNone,  // No animation style. Application allows other ways of animation control, for example through JavaScript.
      kLoop,  // Animation loop. Application plays the animation in an infinite loop.
      kBounce // Animation forward and backward loop. In each loop iteration, the animation first is played forward, then backward.
    };
    
    /** \details 
    The <link OdPdfPublish::OdArtwork, artwork> object default view options. 
    */
    enum ViewPreference {
      kNative,  // Use default view from .prc data (if .prc data exists).
      kPDF      // Use default view from .pdf data (if .pdf data exists).
    };
    
    /** \details 
    Options (such as background color, lighting and rendering modes) used for displaying views. 
    */
    enum DisplayPreference {
      kDefined, // Use view settings.
      kRuntime  // Use application display runtime settings. In this mode settings are not applied to the default view.
    };
  }

    /** \details 
    Contains declarations for border options in Publish SDK. 
    */
  namespace Border {
  
    /** \details 
    Border line thickness types. 
    */
    enum Thickness {
      kThin,    // Border line is thin.
      kMedium,  // Border line has medium thickness.
      kWide     // Border line is wide.
    };
    
    /** \details 
    Border line styles. 
    */
    enum Style {
      kSolid,         // The border is solid.
      kDashed,        // The border is dashed.
      kBeveled,       // The border is bevelled.
      kInset,         // The border is inset.
      kUnderlined     // The border is underlined.
    };
  }

    /** \details 
    Contains declarations for text entity options in Publish SDK. 
    */
  namespace Text {
  
    /** \details 
    Font styles. 
    */
    enum FontStyle {
      kRegular,     // Normal font style. 
      kBold,        // Text appears as bold. 
      kItalic,      // Text appears as italic. 
      kBoldItalic   // Text appears as bold and italic. 
    };
    
    /** \details 
    Text justification values. 
    */
    enum Justification {
      kLeft,    // Left text justification.
      kRight,   // Right text justification.
      kCenter   // Center text justification.
    };
    
    /** \details 
    Text rotation options. 
    */
    enum Rotation {
      kNone,                        // Horizontally allocated text, no rotation.
      kCounterClockwise90Degrees,   // Counter-clockwise rotation 90 degrees relative to the horizontal position.
      kCounterClockwise180Degrees,  // Counter-clockwise rotation 180 degrees relative to the horizontal position.
      kCounterClockwise270Degrees   // Counter-clockwise rotation 270 degrees relative to the horizontal position.
    };
    
    /** \details 
    Built-in fonts supported by Publish SDK. 
    */
    enum StandardFontsType 
    {
      kTimesRoman,            // Normal Times Roman font.
      kHelvetica,             // Normal Helvetica font.
      kCourier,               // Normal Courier font.
      kSymbol,                // Normal Symbol font.
      kTimesBold,             // Bold Times Roman font.
      kHelveticaBold,         // Bold Helvetica font.
      kCourierBold,           // Bold Courier font.
      kZapfDingbats,          // Normal ZapfDingbats font.
      kTimesItalic,           // Italic Times Roman font.
      kHelveticaOblique,      // Oblique Helvetica font.
      kCourierOblique,        // Oblique Courier font.
      kTimesBoldItalic,       // Bold and italic combination of the Times Roman font.
      kHelveticaBoldOblique,  // Bold and oblique combination of the Helvetica font.
      kCourierBoldOblique     // Bold and oblique combination of the Courier font.
    };
    
    /** \details 
    Types of data storage supported by Publish SDK. 
    */
    enum StorageType
    {
      kBuiltIn, // Built-in data storage.
      kExplicit // Explicit data storage.
    };
    
    /** \details 
    Text languages supported by Publish SDK. 
    */    
    enum Language
    {
      kASCII,               // ASCII Text.
      kEastEuropeanRoman,   // East European Roman.
      kCyrillic,            // Cyrillic.
      kGreek,               // Greek.
      kTurkish,             // Turkish.
      kHebrew,              // Hebrew.
      kArabic,              // Arabic.
      kBaltic,              // Baltic.
      kChineseTraditional,  // Traditional Chinese.
      kChineseSimplified,   // Simplified Chinese.
      kJapanese,            // Japanese.
      kKorean,              // Korean.
      kDefault              // Default language.
    };
  }

  /** \details 
  Contains declarations for <link OdPdfPublish::OdText, label> behavior options in Publish SDK. 
  */
  namespace Label {
    
    /** \details 
    <link OdPdfPublish::OdText, Label> positions relative to the icon.
    */
    enum Position
    {
      kLabelOnly, // Only label is displayed.
      kIconOnly,  // Only label icon is displayed.
      kTop,       // The label is positioned at the top of the icon associated with it (i.e above the icon).
      kBottom,    // The label is positioned at the bottom of icon associated with it (i.e under the icon).
      kLeft,      // The label is positioned at the left edge of the icon associated with it.
      kRight,     // The label is positioned at the right edge of the icon associated with it.
      kOnTop      // The label is positioned on top of the icon associated with it.
    };
  }

  /** \details 
  Contains declarations for highlighting options in Publish SDK. 
  */
  namespace Highlighting {
    
    /** \details 
    Highlighting modes that can be applied to Publish SDK objects. 
    The highlighting mode determines how a control appears after a user clicks it.
    */
    enum Mode
    {
      kNone,    // No highlighting.
      kInvert,  // Inverts highlighting colors within the control.
      kOutline, // Creates an outline border around the control.
      kPush     // Content area appears on the page.
    };
  }

  /** \details 
  Contains declarations for image options in Publish SDK. 
  */
  namespace Image {
    
    /** \details 
    Image formats supported by Publish SDK. 
    */
    enum Format
    {

      kUnknown  = -1, // The format is unknown.
      kBMP,           // A bitmap image.
      kICO,           // An icon image.
      kJPEG,          // A .jpeg image.
      kJNG,           // A .jng image.
      kKOALA,         // A .koala image.
      kLBM,           // An .lbm image.
      kIFF,           // An .iff image.
      kMNG,           // An .mgn image.
      kPBM,           // A .pbm image.
      kPBMRAW,        // A raw .pbm image.
      kPCD,           // A .pcd image.
      kPCX,           // A .pcx image.
      kPGM,           // A .pgm image.
      kPGMRAW,        // A raw .pgm image.
      kPNG,           // A .png image.
      kPPM,           // A .ppm image.
      kPPMRAW,        // A raw .ppm image.
      kRAS,           // A .ras image.
      kTARGA,         // A .targa image.
      kTIFF,          // A .tiff image.
      kWBMP,          // A .wbmp image.
      kPSD,           // A .psd (Adobe Photoshop) image.
      kCUT,           // A .cut image.
      kXBM,           // A .xbm image.
      kXPM,           // A .xpm image.
      kDDS,           // A .dds image.
      kGIF,           // A .gif image.
      kHDR,           // A .hdr image.
      kFAXG3,         // A .faxg3 image.
      kSGI,           // An .sgi image.
      kEXR,           // A .exr image.
      kJ2K,           // A .j2k image.
      kJP2,           // A .jp2 image.
      kPFM,           // A .pfm image.
      kPICT,          // A .pict image.
      kRAW            // A raw image.
    };
  }

  /** \details 
  Contains declarations for action handling in Publish SDK. 
  */
  namespace Action {
    
    /** \details 
    Action types that can be handled by Publish SDK. 
    */
    enum Type
    {
      kCursorEnter    = 0, // The cursor enters into a control.
      kCursorExit     = 1, // The cursor exits from a control.
      kButtonPressed  = 2, // A button is pressed (but not released).
      kButtonReleased = 3, // A pressed button is released.
      kInputFocus     = 4, // A control gets the focus.
      kLoseFocus      = 5, // A control loses the focus.
      kPageOpened     = 6, // A page is opened.
      kPageClosed     = 7, // A page is closed.
      kPageVisible    = 8, // A page becomes visible (is shown).
      kPageInvisible  = 9  // A page becomes invisible (is hidden).
    };
  }

  /** \details 
  Contains declarations for geometry options in Publish SDK. 
  */
  namespace Geometry {
    
    /** \details 
    PDF line caps supported by Publish SDK. 
    */
    enum PDFLineCap
    {
      kLineCapNotSet        = -1, // Line cap is not set.
      kButtCap              = 0,  // Butt line cap.
      kRoundCap             = 1,  // Round line cap.
      kProjectingSquareCap  = 2   // Projecting square line cap.
    };

    /** \details 
    PDF line joins supported by Publish SDK. 
    */
    enum PDFLineJoin
    {
      kLineJoinNotSet = -1, // Line join is not set.
      kMiterJoin      = 0,  // Miter line join.
      kRoundJoin      = 1,  // Round line join.
      kBevelJoin      = 2   // Bevel line join.
    };

    /** \details 
    PDF finish rules supported by Publish SDK. 
    */
    enum PDFFinishRule
    {
      kFillNotSet  = 0,   // Finish rule is not set.
      kEnd         = 1,   // End of the path.
      kStroke      = 2,   // Stroke the path.
      kClose       = 4,   // Close the path.
      kFillEvenOdd = 8,   // Fill the path using the even-odd rule to determine the region to fill.
      kFillNonZero = 16   // Fill the path using the nonzero winding number rule to determine the region to fill. Any subpaths that are open are implicitly closed before being filled.
    };
  }

  /** \details 
    Types of JavaScript source code.
  */
  namespace Source {
    /** \details 
      JavaScript source code type supported by Publish SDK.
    */    
    enum Type
    {
      kCode     = 0, // Source code text.
      kFileName = 1  // Name of the source code file.
    };
  }

  /** \details 
    CAD definitions and CAD references options.
  */
  namespace CAD {
    /** \details
      Color policies supported by Publish SDK for CAD definitions and references.
    */
    enum ColorPolicy
    {
      kNoPolicy   = 0,  // No color policy. A drawing is exported with its native color palette (as is).
      kMono       = 1,  // Drawing is exported to a monochrome .pdf file.
      kGrayscale  = 2   // Drawing is exported to a grayscale .pdf file. Native colors are converted into grayscale
    };
  }

  /** \details
  Contains declarations of access permission options for a PDF document.
  */
  namespace AccessPermissions {
    /** \details
    Enumerates access permission flags for a PDF document.
    */
    enum AccessPermissionsFlags
    {
      /** Allows copying or other ways of extracting text and graphics from the document.*/
      kAllowExtract = 1,
      
      /** Allows inserting, rotating, and deleting pages from a document, creating bookmarks, and creating thumbnail images, even when the kAllowModifyOther flag is not set.*/
      kAllowAssemble = 2,
      
      /** Allows adding and modifying annotations (comments), filling interactive form fields, and 
      when the kAllowModifyOther flag is switched on, creating and modifying interactive form fields (including signature fields).*/
      kAllowAnnotateAndForm = 4,
      
      /** Allows filling of existing interactive form fields (including signature fields), even if the kAllowAnnotateAndForm flag is switched off.*/
      kAllowFormFilling = 8,
      
      /** Allows modifying document contents by using operations that are not controlled by the following flags:
      * kAllowAssemble
      * kAllowAnnotateAndForm
      * kAllowFormFilling
      */
      kAllowModifyOther = 16,
      
      /** Allows printing a document to a representation from which an exact digital copy of the PDF content could be generated.*/
      kAllowPrintAll = 32,
      
      /** Allows printing a document with possibly a lower quality level. Ignored if the kAllowPrintAll flag is switched on.*/
      kAllowPrintLow = 64,

      /** The default flag combination.*/
      kDefaultPermissions = kAllowExtract | kAllowFormFilling | kAllowPrintAll
    };
  }

  /** \details
  Contains decralations for working with sticky notes within a PDF document.
  */
  namespace StickyNotes{
    /** \details
    Sticky note types within a PDF document.
    The type determines the predefined icon to be displayed when the sticky note is rendered.
    */
    enum StickyNoteTypes
    {
      /** A sticky note that represents a comment.*/
      kComment,
      /** A sticky note that represents a key.*/
      kKey,
      /** A sticky note that represents a note.*/
      kNote,
      /** A sticky note that represents a help topic.*/
      kHelp,
      /** A sticky note that represents a new paragraph.*/
      kNewParagraph,
      /** A sticky note that represents a paragraph.*/
      kParagraph,
      /** A sticky note that represents an insert.*/
      kInsert,
      /** A sticky note that represents a check. Applicable for Adobe&reg; Reader&reg; only.*/
      kCheck,
      /** A sticky note that represents a checkmark. Applicable for Adobe Reader&reg; only.*/
      kCheckmark,
      /** A sticky note that represents a circle. Applicable for Adobe Reader&reg; only.*/
      kCircle,
      /** A sticky note that represents a cross. Applicable for Adobe Reader&reg; only.*/
      kCross,
      /** A sticky note that represents a crosshairs. Applicable for Adobe Reader&reg; only.*/
      kCrossHairs,
      /** Sticky note type RightArrow. Applicable for Adobe Reader&reg; only.*/
      kRightArrow,
      /** A sticky note that represents a right pointer. Applicable for Adobe Reader&reg; only.*/
      kRightPointer,
      /** A sticky note that represents a star. Applicable for Adobe Reader&reg; only.*/
      kStar,
      /** A sticky note that represents an Up arrow. Applicable for Adobe Reader&reg; only.*/
      kUpArrow,
      /** A sticky note that represents an up-left arrow. Applicable for Adobe Reader&reg; only.*/
      kUpLeftArrow
    };

    /** \details
    Values of the Marked status of a sticky note within a PDF document. 
    */
    enum StickyNoteMarkedStates
    {
      /** The sticky note is marked.*/
      kMarkedState,
      /** The sticky note is not marked.*/
      kUnmarkedState
    };

    /** \details
    Values of the Review status of a sticky note within a PDF document.
    */
    enum StickyNoteReviewStates
    {
      /** The Review status of the sticky note is equal to None.*/
      kNone,
      /** The Review status of the sticky note is equal to Accepted.*/
      kAccepted,
      /** The Review status of the sticky note is equal to Rejected.*/
      kRejected,
      /** The Review status of the sticky note is equal to Cancelled.*/
      kCancelled,
      /** The Review status of the sticky note is equal to Completed.*/
      kCompleted
    };

  }

  /** \details
    Declarations for bookmark support.
  */
  namespace Bookmarks {
    /** \details
      Bookmark types within a PDF document.
    */
    enum BookmarkType
    {
      /** 
        Displays a target point on the specified page defined with its coordinates (left, top) in the upper-left corner of the window. 
        Page content referenced by the bookmark is displayed as scaled according to the zoom factor.
        When the value of the left, top or zoom parameter equals null, it means that the value of the respective parameter remains unchanged.
        When the value of the zoom parameter equals zero (0), it has the same effect as the null value.
      */
      kXYZ,
      
      /** 
        Displays the specified page, scaled both horizontally and vertically to fit all page content in the viewer window.
        When horizontal and vertical scale factors have different values, the smallest is used, and the page is centered in the viewer window in the other dimension. 
      */
      kFit,
      
      /** 
        Displays the specified page with the vertical offset from the top edge according to the top parameter, and scales the page content horizontally to fit it in the viewer window. 
        When the top parameter equals the null value, it means that the current value stays unchanged.
      */
      kFitH,
      
      /** 
        Displays the specified page with the horizontal offset from the left edge according to the left parameter, and scales the page content vertically to fit it in the viewer window. 
        When the left parameter equals the null value, it means that the current value stays unchanged.
      */
      kFitV,
      
      /** 
        Displays the specified page and scales the page content to fit it horizontally and vertically in a rectangle defined by left, bottom, right and top coordinates. 
        When horizontal and vertical scale factors have different values, the smallest of them is used. The rectangle is centered in the viewer window in the other dimension.
      */
      kFitR,
      
      /** 
        Displays the specified page and scales the page content to fit it horizontally and vertically in a bounding box. 
        When horizontal and vertical scale factors have different values, the smallest of them is used. The bounding box is centered in the viewer window in the other dimension.
      */
      kFitB,
      
      /** 
        Displays the specified page with the vertical offset from the top edge according to the top parameter, and scales the page content horizontally to fit it in the specified bounding box within the viewer window. 
        When the top parameter equals the null value, it means that the current value stays unchanged.
      */
      kFitBH,
      
      /** 
        Displays the specified page with the horizontal offset from the left edge according to the left parameter, and scales the page content vertically to fit it in the specified bounding box within the viewer window. 
        When the left parameter equals the null value, it means that the current value stays unchanged.
      */
      kFitBV,
    };
  }

  /** \details
    Contains declarations related to carousel button options.
  */
  namespace CarouselButtons {

    /** \details 
      Enumeration that defines the alignment types of carousel buttons.
    */
    enum Alignment
    {
      /** Left alignment for carousel buttons.*/
      kLeft,   
      /** Right alignment for carousel buttons.*/
      kRight,   
      /** Center alignment for carousel buttons.*/
      kCenter,   
      /** Justified alignment for carousel buttons.*/
      kJustified
    };
  }

  /** \details 
  Contains declarations for handling tables within Publish SDK.
  */
  namespace Table {

    /** \details
      Enumeration that defines the alignment types of text alignment in table cells.
    */
    enum TextAlignment
    {
      /** TopLeft alignment for text in table cells.*/
      kTopLeft,
      /** TopRight alignment for text in table cells.*/
      kTopRight,
      /** TopCenter alignment for text in table cells.*/
      kTopCenter,
      /** CenterLeft alignment for text in table cells.*/
      kCenterLeft,
      /** CenterRight alignment for text in table cells.*/
      kCenterRight,
      /** Center alignment for text in table cells.*/
      kCenter,
      /** BottomLeft alignment for text in table cells.*/
      kBottomLeft,
      /** BottomRight alignment for text in table cells.*/
      kBottomRight,
      /** BottomCenter alignment for text in table cells.*/
      kBottomCenter,
    };
  }

  /** \details
  Contains declarations for handling collection within Publish SDK.
  */
  namespace CollectionSchema {

    /** \details
      Enumeration that defines the types of columns in the collection.
    */
    enum ColumnType
    {
      /** Text type for columns in the collection.*/
      kString,
      /** Date type for columns in the collection.*/
      kDate,
      /** Number type for columns in the collection.*/
      kNumber,
      /** File name type for columns in the collection.*/
      kFileName,
      /** Description type for columns in the collection.*/
      kDescription,
      /** Modification date type for columns in the collection.*/
      kModDate,
      /** Creation date type for columns in the collection.*/
      kCreationDate,
      /** File size type for columns in the collection.*/
      kSize,
      /** File compressed size type for columns in the collection.*/
      kCompressedSize,
    };

    /** \details
      Enumeration that defines the types of initial view for the collection.
    */
    enum InitialView
    {
      /** The collection view will be presented in tile mode, with each file in the collection indicated by a small icon.*/
      kTileMode,
      /** The collection view will be presented in detail mode, with all information in the schema dictionary presented in a multi-column format.*/
      kDetailMode,
    };

    /** \details
      Enumeration that defines the types of sort for column items in the collection.
    */
    enum SortOrder
    {
      /** Items are unsorted.*/
      kUnsorted,
      /** Items are sorted in ascending order.*/
      kAscending,
      /** Items are sorted in descending order.*/
      kDescending,
    };
  }

}

#endif // _PDFPUBLISH_COMMON_INCLUDED_


