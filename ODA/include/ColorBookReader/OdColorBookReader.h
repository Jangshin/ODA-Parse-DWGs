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

#ifndef OD_COLOR_BOOK_READER_H_
#define OD_COLOR_BOOK_READER_H_

#include "OdaCommon.h"
#include "CmColorBase.h"
#include "OdColorBook.h"


/** \details
    Reader for a color books.
    <group Other_Classes>
  */
class OD_TOOLKIT_EXPORT OdColorBookReaderRGB8
{
public:
  /** \details
    Creates a new instance of a object with default parameters.
  */
  OdColorBookReaderRGB8();

  /** \details
    Destroys the object.
  */
  ~OdColorBookReaderRGB8();

  /** \details
    Read book from physical file on disk.

    \param filePath [in]            String with full path to file.
    \param book     [out[optional]] Pointer to get a copy of readed book.

    \returns 
    * eOk                  if book readed successful.
    * eInvalidInput        if filePath is empty.
    * eSecErrorReadingFile if file not read.
    * eAlreadyInGroup      if book with the same name is readed and stored in the current reader.
    
    \remarks
    Pointer to memory where will be placed copy of a readed book.
  */
  OdResult readBook(const OdString& filePath, OdColorBookRGB8* book = 0);

  /** \details
    Read book from memory stream.

    \param filePath [in]            Pointer to memory stream.
    \param len      [in]            Memoty stream length.
    \param book     [out[optional]] Pointer to get a copy of readed book.

    \returns
    * eOk                  if book readed successful.
    * eInvalidInput        if filePath is empty.
    * eSecErrorReadingFile if file not read.
    * eAlreadyInGroup      if book with the same name is readed and stored in the current reader.

    \remarks
    Pointer to memory where will be placed copy of a readed book.
  */
  OdResult readBook(const char* stream, const OdUInt32 len, OdColorBookRGB8* book = 0);

  /** \details
    Remove book from a reader storage.

    \param bookName [in]   String with name of book.

    \returns
    * eOk                  if book removed successful.
    * eKeyNotFound         if storage do not contain book with such name.
  */
  OdResult removeBook(const OdString& bookName);

  /** \details
    Search a color.

    \param color     [out]  The result of the found color
    \param colorName [in]   String with name of a color.
    \param colorBook [in]   String with name of a book.

    \returns
    * eOk                  if color search successful.
    * eKeyNotFound         if storage do not contain the book with such name.
    * eBadColor            if book do not contain color with such name.
  */
  OdResult getColor(OdCmEntityColor& color, const OdString& colorName, const OdString& colorBook) const;

  /** \details
    Search a book.

    \param book      [out]  Return the copy of the found book.
    \param bookName  [in]   String with name of a book.

    \returns
    * eOk                  if book search successful.
    * eKeyNotFound         if storage do not contain the book with such name.
  */
  OdResult getBook(OdColorBookRGB8& book, const OdString& bookName) const;

  /** \details
    Search a book.

    \param book      [out]  Return the pointer to the found book.
    \param bookName  [in]   String with name of a book.

    \returns
    * eOk                  if book search successful.
    * eKeyNotFound         if storage do not contain the book with such name.
  */
  OdResult getBook(const OdColorBookRGB8*& book, const OdString& bookName) const;

  /** \details
    Get an iterator to the beginning of the book store.

    \returns a const itarator to first book in the storage.
  */
  ConstBookIterator begin()     const { return m_books->begin(); };

  /** \details
    Get an iterator to the end of the book store.

    \returns a const itarator to next after last book in book storage.
  */
  ConstBookIterator end()       const { return m_books->end(); };

  /** \details
    Get a pointer to the book storage.

    \returns a const pointer to a book storage.
  */
  const BooksMap* getBooksMap() const { return m_books; };

  /** \details
    Remove all book from a book storage.
  */
  void clear() { m_books->clear(); };

protected:
  /** \details
    Storage for a readed books.
  */
  OdSharedPtr<BooksMap> m_books;
};


#endif


