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
// Base local context interface

#ifndef ODTRRNDLOCALCONTEXT
#define ODTRRNDLOCALCONTEXT

#include "TD_PackPush.h"

#include "../TrVisRenderClient.h"
#include "nogl/TrRndNoGLExtensionsRegistry.h"

/** \details
    <group ExRender_Windows_Classes> 
*/
#define GLProcedure0(t,a) virtual t no##a() const{ return (t)0; }
#define GLProcedure(t,a,b) virtual t no##a(b) const{ return (t)0; }
#define GLFunction0(t,a) virtual t no##a() const {}
#define GLFunction(t,a,b) virtual t no##a(b) const {}
#define GLFunction2(t,a,b,c) virtual t no##a(b,c) const {}
#define GLFunction3(t,a,b,c,d) virtual t no##a(b,c,d) const {}
#define GLFunction4(t,a,b,c,d,e) virtual t no##a(b,c,d,e) const {}
#define GLFunction5(t,a,b,c,d,e,f) virtual t no##a(b,c,d,e,f) const {}
#define GLFunction6(t,a,b,c,d,e,f,g) virtual t no##a(b,c,d,e,f,g) const {}
#define GLFunction7(t,a,b,c,d,e,f,g,h) virtual t no##a(b,c,d,e,f,g,h) const {}
#define GLFunction9(t,a,b,c,d,e,f,g,h,i,j) virtual t no##a(b,c,d,e,f,g,h,i,j) const {}

struct GLFunctions : public nogl
{
  virtual ~GLFunctions(){};
  virtual void glesSafeDrawArrays(GLenum mode, GLint first, GLsizei count) const
  {
    noglDrawArrays(mode, first, count);
  };
  virtual bool noglDrawSimplePoint(const GLfloat *pPoint) const { return false; }
  virtual bool noglDrawSimplePoint(const GLdouble *pPoint) const { return false; }
  virtual bool noglDrawSimpleLine(const GLfloat *pPoint0, const GLfloat *pPoint1) const { return false; }
  virtual bool noglDrawSimpleLine(const GLdouble *pPoint0, const GLdouble *pPoint1) const { return false; }
  virtual bool noglDrawSimpleIndexedPoint(GLuint id) const { return false; }
  virtual bool noglDrawSimpleIndexedLine(GLuint id0, GLuint id1) const { return false; }
  virtual bool noglWireframeMode(bool bEnable) const { return false; }
#include "nogl/TrRndNoGLContextHolderFunctionsList.inl"
};

class OdTrRndNoGLShaderState;
class OdTrRndLocalContext : public OdRxObject, public GLFunctions
{
    virtual void CreateExtensionRegistry() const{};
  public:
    struct DrawBufferLayout
    { enum { kMaxDrawBuffers = 4 };
#if defined(_MSC_VER) && (_MSC_VER < 1900)
    GLenum m_nBuf[kMaxDrawBuffers];
#else
    GLenum m_nBuf[kMaxDrawBuffers] = { 0 };
#endif
      int numBufs() const
      { int nBufs = 1;
        for (int nBuf = 1; nBuf < kMaxDrawBuffers; nBuf++)
        { if (m_nBuf[nBuf]) nBufs++; else break; }
        return nBufs;
      }
#if defined(_MSC_VER) && (_MSC_VER < 1900)
      DrawBufferLayout()
      {
        for (unsigned int i = 0; i < kMaxDrawBuffers; i++)
        {
          m_nBuf[i] = 0;
        }
      }

      DrawBufferLayout(GLenum buf0, GLenum buf1 = 0, GLenum buf2 = 0, GLenum buf3 = 0)
      {
        for (unsigned int i = 0; i < kMaxDrawBuffers; i++)
        {
          switch (i)
          {
            case 0:  m_nBuf[i] = buf0; break;
            case 1:  m_nBuf[i] = buf1; break;
            case 2:  m_nBuf[i] = buf2; break;
            case 3:  m_nBuf[i] = buf3; break;
            default: m_nBuf[i] = 0;
          }
        }
      }
#else
      DrawBufferLayout() = default;
      DrawBufferLayout(GLenum buf0, GLenum buf1 = 0, GLenum buf2 = 0, GLenum buf3 = 0)
        : m_nBuf{ buf0, buf1, buf2, buf3 } { }
#endif
    };
    struct ReadBufferLayout
    { GLenum m_nBuf = 0;
      ReadBufferLayout() = default;
      ReadBufferLayout(GLenum buf)
        : m_nBuf(buf) { }
    };
  protected:
    //mutable OdRxObjectPtr m_pExtensionsRegistry;
    mutable OdTrRndNoGLExtensionsRegistry *m_pExtensionsRegistry;
  public:
    OdTrRndLocalContext() : m_pExtensionsRegistry(NULL){ }
    virtual ~OdTrRndLocalContext()
    {
      if (m_pExtensionsRegistry)
        delete m_pExtensionsRegistry;
      m_pExtensionsRegistry = NULL;
    }

    virtual void createContext(OdTrVisRenderClient *pDevice) = 0;
    virtual void updateContext(OdTrVisRenderClient * /*pDevice*/) { }
    virtual void destroyContext() = 0;

    virtual bool isContextCreated() const = 0;

    virtual void makeCurrentContext() = 0;

    virtual bool pushCurrentContext() { return false; }
    virtual bool popCurrentContext() { return false; }

    virtual void presentContext() = 0;

    virtual bool isExtensionBasedEmulation() const { return false; }
    virtual bool isExtensionSupported(const char * /*pExtensionName*/) { return false; }
    virtual void *acquireExtensionFunctionPtr(const char * /*pFunctionName*/) { return NULL; }

    // Search OpenGL extension in cross-platform way using our own extensions registry
    OdTrRndNoGLExtensionsRegistry &extensionsRegistry() const
    {
      if (m_pExtensionsRegistry == NULL)
        CreateExtensionRegistry();
      return *m_pExtensionsRegistry;
    }

    virtual OdTrRndNoGLShaderState* CreateShaderState() const {return NULL;};

    // Returns active draw buffer layout or nullptr if layouts doesn't supported.
    virtual const DrawBufferLayout *activeDrawBufferLayout() const { return NULL; }
    // Return true if active draw buffer layout is fully compatible with specified layout.
    virtual bool isDrawBufferLayoutCompatible(const DrawBufferLayout & /*dbl*/) const { return true; }
    // Change active draw buffer layout. Return previous active layout state.
    virtual DrawBufferLayout changeDrawBufferLayout(const DrawBufferLayout & /*dbl*/) { return DrawBufferLayout(); }

    // Returns active read buffer layout or nullptr if layouts doesn't supported.
    virtual const ReadBufferLayout *activeReadBufferLayout() const { return NULL; }
    // Return true if active read buffer layout is fully compatible with specified layout.
    virtual bool isReadBufferLayoutCompatible(const ReadBufferLayout & /*rbl*/) const { return true; }
    // Change active read buffer layout. Return previous active layout state.
    virtual ReadBufferLayout changeReadBufferLayout(const ReadBufferLayout & /*rbl*/) { return ReadBufferLayout(); }
};

typedef OdSmartPtr<OdTrRndLocalContext> OdTrRndLocalContextPtr;

/** \details
    <group ExRender_Windows_Classes> 
*/
class OdTrRndLocalContextStub : public OdTrRndLocalContext
{
  public:
    OdTrRndLocalContextStub() : OdTrRndLocalContext() { }
    ~OdTrRndLocalContextStub() { }

    virtual void createContext(OdTrVisRenderClient * /*pDevice*/) { }
    virtual void destroyContext() { }

    virtual bool isContextCreated() const { return true; }

    virtual void makeCurrentContext() { }

    virtual void presentContext() { }
};

/** \details
    <group ExRender_Windows_Classes> 
*/
class OdTrRndDrawBufferLayout
{
  protected:
    OdTrRndLocalContext *m_pLc;
    OdTrRndLocalContext::DrawBufferLayout m_prevLayout;
public:
    OdTrRndDrawBufferLayout(OdTrRndLocalContext *pLc, const OdTrRndLocalContext::DrawBufferLayout &changeLayout)
      : m_pLc(nullptr)
    {
      if (!pLc->isDrawBufferLayoutCompatible(changeLayout))
        m_prevLayout = pLc->changeDrawBufferLayout(changeLayout), m_pLc = pLc;
    }
    ~OdTrRndDrawBufferLayout()
    {
      if (m_pLc)
        m_pLc->changeDrawBufferLayout(m_prevLayout);
    }
};

/** \details
    <group ExRender_Windows_Classes> 
*/
class OdTrRndReadBufferLayout
{
  protected:
    OdTrRndLocalContext *m_pLc;
    OdTrRndLocalContext::ReadBufferLayout m_prevLayout;
  public:
    OdTrRndReadBufferLayout(OdTrRndLocalContext *pLc, const OdTrRndLocalContext::ReadBufferLayout &changeLayout)
      : m_pLc(nullptr)
    {
      if (!pLc->isReadBufferLayoutCompatible(changeLayout))
        m_prevLayout = pLc->changeReadBufferLayout(changeLayout), m_pLc = pLc;
    }
    ~OdTrRndReadBufferLayout()
    {
      if (m_pLc)
        m_pLc->changeReadBufferLayout(m_prevLayout);
    }
};

#include "TD_PackPop.h"

#endif // ODTRRNDLOCALCONTEXT
