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
#ifndef __DG_LINKSET_H__
#define __DG_LINKSET_H__

#include "DgApplicationData.h"
#include "DgElementIterator.h"

class OdDgLinkNode;
typedef OdSmartPtr<OdDgLinkNode> OdDgLinkNodePtr;

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLinkNode : public OdRxObject
{
  public:
    ODRX_DECLARE_MEMBERS(OdDgLinkNode);

    enum OdDgLinkNodeType
    {
      kUnknownLink     = 0,
      kFolderLink      = 1,
      kFileLink        = 2,
      kModelLink       = 3,
      kRegionLink      = 4,
      kPDFRegionLink   = 5,
      kExcelSheetLink  = 6,
      kWordHeadingLink = 7,
      kWordRegionLink  = 8,
      kURLLink         = 9
    };

  public:
    virtual OdDgLinkNodeType getType() const = 0;
    virtual bool             getValidFlag() const = 0;
    virtual OdString         getName() const = 0;
    virtual void             setName( const OdString& strName ) = 0;

    virtual bool             clone( OdDgLinkNodePtr& pRet ) const = 0;
    virtual bool             isEqual( const OdDgLinkNodePtr& obj ) const = 0;
};

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgUnknownLinkNode : public OdDgLinkNode
{
  public:
    ODRX_DECLARE_MEMBERS(OdDgUnknownLinkNode);

    virtual OdDgLinkNodeType getType() const = 0;
    virtual OdString         getName() const = 0;
    virtual void             setName( const OdString& strName ) = 0;

    virtual OdString                 getHandlerName() const = 0;
    virtual void                     setHandlerName( const OdString& strHandlerName ) = 0;
    virtual OdString                 getHandler() const = 0;
    virtual void                     setHandler( const OdString& strHandler ) = 0;
    virtual bool                     getValidFlag() const = 0;
    virtual void                     setValidFlag( bool bSet ) = 0;

    virtual bool             clone( OdDgLinkNodePtr& pRet ) const = 0;
    virtual bool             isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgUnknownLinkNode> OdDgUnknownLinkNodePtr;

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgFolderLinkNode : public OdDgLinkNode
{
public:
  ODRX_DECLARE_MEMBERS(OdDgFolderLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;
  virtual OdString         getName() const = 0;
  virtual void             setName( const OdString& strName ) = 0;
  virtual bool             getValidFlag() const = 0;

  virtual OdUInt32         getChildCount() const = 0;
  virtual OdDgLinkNodePtr  getChild( OdUInt32 uIndex ) = 0;
  virtual void             addChild( const OdDgLinkNodePtr pChild ) = 0;
  virtual void             deleteChild( OdUInt32 uIndex ) = 0;

  virtual bool             clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool             isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgFolderLinkNode> OdDgFolderLinkNodePtr;

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgFileLinkNode : public OdDgLinkNode
{
public:
  ODRX_DECLARE_MEMBERS(OdDgFileLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;
  virtual OdString         getName() const = 0;
  virtual void             setName( const OdString& strName ) = 0;

  virtual OdString         getFileName() const = 0;
  virtual void             setFileName( const OdString& strFileName ) = 0;
  virtual OdString         getFullPath() const = 0;
  virtual void             setFullPath( const OdString& strPath ) = 0;
  virtual bool             getValidFlag() const = 0;
  virtual void             setValidFlag( bool bSet ) = 0;
  virtual bool             getRelativeFileLinkFlag() const = 0;
  virtual void             setRelativeFileLinkFlag(bool bSet) = 0;

  virtual bool             clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool             isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgFileLinkNode> OdDgFileLinkNodePtr;

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgModelLinkNode : public OdDgFileLinkNode
{
public:

  enum OdDgModelLinkNodeType
  {
    kUnknownModel = 0,
    kDesignModel  = 1,
    kSheetModel   = 2
  };
public:
  ODRX_DECLARE_MEMBERS(OdDgModelLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;

  virtual OdDgModelLinkNodeType getModelType() const = 0;
  virtual void                  setModelType( OdDgModelLinkNodeType uType ) = 0;
  virtual OdString              getModelTypeName() const = 0;
  virtual void                  setModelTypeName( const OdString& strModelTypeName ) = 0;
  virtual OdString              getModelName() const = 0;
  virtual void                  setModelName( const OdString& strModelName ) = 0;

  virtual bool          clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool          isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgModelLinkNode> OdDgModelLinkNodePtr;

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgRegionLinkNode : public OdDgFileLinkNode
{
public:

  enum OdDgRegionLinkNodeType
  {
    kUnknownRegion = 0,
    kReference     = 1,
    kSavedView     = 2
  };
public:
  ODRX_DECLARE_MEMBERS(OdDgRegionLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;

  virtual OdDgRegionLinkNodeType getRegionType() const = 0;
  virtual void           setRegionType( OdDgRegionLinkNodeType uType ) = 0;
  virtual OdString       getRegionTypeName() const = 0;
  virtual void           setRegionTypeName( const OdString& strRegionTypeName ) = 0;
  virtual OdString       getModelName() const = 0;
  virtual void           setModelName( const OdString& strModelName ) = 0;
  virtual OdString       getRegionName() const = 0;
  virtual void           setRegionName( const OdString& strRegionName ) = 0;

  virtual bool           clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool           isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgRegionLinkNode> OdDgRegionLinkNodePtr;

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgPdfRegionInfoItem
{
  public:

    enum OdDgPdfRegionType
    {
      kUnknownRegion = 0,
      kBookmark      = 1,
      kHeading       = 2
    };

  public:

    OdDgPdfRegionInfoItem();

    OdDgPdfRegionType getRegionType() const;
    void              setRegionType( OdDgPdfRegionType uType );
    OdString          getRegionTypeName() const;
    void              setRegionTypeName( const OdString& strRegionTypeName );
    OdString          getRegionName() const;
    void              setRegionName( const OdString& strRegionName );
    OdUInt32          getSequenceNumber() const;
    void              setSequenceNumber( OdUInt32 uNumber );

  private:

    OdDgPdfRegionType m_uType;
    OdString          m_strRegionName;
    OdString          m_strRegionTypeName;
    OdUInt32          m_uSequenceNumber;
};

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgPdfRegionLinkNode : public OdDgFileLinkNode
{
public:
  ODRX_DECLARE_MEMBERS(OdDgPdfRegionLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;

  virtual OdUInt32              getPdfInfoItemCount() const = 0;
  virtual OdDgPdfRegionInfoItem getPdfInfoItem( OdUInt32 uIndex ) const = 0;
  virtual void                  setPdfInfoItem( OdUInt32 uIndex, const OdDgPdfRegionInfoItem& item ) = 0;
  virtual void                  addPdfInfoItem( const OdDgPdfRegionInfoItem& item ) = 0;
  virtual void                  deletePdfInfoItem( OdUInt32 uIndex ) = 0;

  virtual bool          clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool          isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgPdfRegionLinkNode> OdDgPdfRegionLinkNodePtr;
//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgExcelSheetLinkNode : public OdDgFileLinkNode
{
public:
  ODRX_DECLARE_MEMBERS(OdDgExcelSheetLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;
  virtual OdString      getSheetName() const = 0;
  virtual void          setSheetName( const OdString& strSheetName ) = 0;
  virtual bool          clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool          isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgExcelSheetLinkNode> OdDgExcelSheetLinkNodePtr;

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgWordHeadingInfoItem
{
public:

  enum OdDgWordHeadingItemType
  {
    kUnknown       = 0,
    kBookmark      = 1,
    kHeading       = 2
  };

public:

  OdDgWordHeadingInfoItem();

  OdDgWordHeadingItemType getType() const;
  void              setType( OdDgWordHeadingItemType uType );
  OdString          getTypeName() const;
  void              setTypeName( const OdString& strTypeName );
  OdString          getName() const;
  void              setName( const OdString& strName );
  OdUInt32          getSequenceNumber() const;
  void              setSequenceNumber( OdUInt32 uNumber );
  OdUInt32          getWordHeadingStyle() const;
  void              setWordHeadingStyle( OdUInt32 uStyle );

private:

  OdDgWordHeadingItemType m_uType;
  OdString                m_strName;
  OdString                m_strTypeName;
  OdUInt32                m_uSequenceNumber;
  OdUInt32                m_uStyle;
};

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgWordHeadingLinkNode : public OdDgFileLinkNode
{
public:
  ODRX_DECLARE_MEMBERS(OdDgWordHeadingLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;

  virtual OdUInt32                getInfoItemCount() const = 0;
  virtual OdDgWordHeadingInfoItem getInfoItem( OdUInt32 uIndex ) const = 0;
  virtual void                    setInfoItem( OdUInt32 uIndex, const OdDgWordHeadingInfoItem& item ) = 0;
  virtual void                    addInfoItem( const OdDgWordHeadingInfoItem& item ) = 0;
  virtual void                    deleteInfoItem( OdUInt32 uIndex ) = 0;
  virtual bool            clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool            isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgWordHeadingLinkNode> OdDgWordHeadingLinkNodePtr;

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgWordRegionLinkNode : public OdDgFileLinkNode
{

public:
  ODRX_DECLARE_MEMBERS(OdDgWordRegionLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;

  virtual OdDgWordHeadingInfoItem::OdDgWordHeadingItemType getRegionType() const = 0;
  virtual void                   setRegionType( OdDgWordHeadingInfoItem::OdDgWordHeadingItemType uType ) = 0;
  virtual OdString               getRegionTypeName() const = 0;
  virtual void                   setRegionTypeName( const OdString& strRegionTypeName ) = 0;
  virtual OdString               getRegionName() const = 0;
  virtual void                   setRegionName( const OdString& strRegionName ) = 0;
  virtual bool           clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool           isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgWordRegionLinkNode> OdDgWordRegionLinkNodePtr;

//---------------------------------------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgURLLinkNode : public OdDgLinkNode
{
public:
  ODRX_DECLARE_MEMBERS(OdDgURLLinkNode);

  virtual OdDgLinkNodeType getType() const = 0;
  virtual OdString         getName() const = 0;
  virtual void             setName( const OdString& strName ) = 0;

  virtual OdString         getURL() const = 0;
  virtual void             setURL( const OdString& strURL ) = 0;
  virtual bool             getValidFlag() const = 0;
  virtual void             setValidFlag( bool bSet ) = 0;

  virtual bool             clone( OdDgLinkNodePtr& pRet ) const = 0;
  virtual bool             isEqual( const OdDgLinkNodePtr& pObj ) const = 0;
};

typedef OdSmartPtr<OdDgURLLinkNode> OdDgURLLinkNodePtr;

//--------------------------------------------------------------

class OdDgLinkSet;
typedef OdSmartPtr<OdDgLinkSet> OdDgLinkSetPtr;

//--------------------------------------------------------------

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLinkSet : public OdDgApplicationData
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLinkSet);

public:

  enum
  {
    kSignature = 0x5842
  };

  OdString getName() const;
  void setName( OdString& strName );

  OdUInt32 getLinkNodeCount() const;
  OdDgLinkNodePtr getLinkNode( OdUInt32 uIndex );
  void     addLinkNode( const OdDgLinkNodePtr& pLinkNode );
  void     deleteLinkNode( OdUInt32 uIndex );
};

/** \details

  Corresponding C++ library: TG_Db
  <group OdDg_Classes>
*/
class TG_EXPORT OdDgLinkSetTable : public OdDgElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLinkSetTable);
public:

  void add( OdDgElementPtr pLinkSet);

  OdDgElementIteratorPtr createIterator( bool atBeginning = true, bool skipDeleted = true ) const;

  OdDgElementId getAt( const OdString& strLinkSetName );
};

typedef OdSmartPtr<OdDgLinkSetTable> OdDgLinkSetTablePtr;

#endif // __DG_LINKSET_H__
