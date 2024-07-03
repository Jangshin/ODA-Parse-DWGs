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
// GLES2 extensions

#ifndef ODTRRNDNOGLEXTENSIONSREGISTRY
#define ODTRRNDNOGLEXTENSIONSREGISTRY

#include "NoGL.h"

class OdTrRndLocalContext;

class OdTrRndNoGLExtensionsRegistry : public nogl
{
  public:
    enum ExtensionName
    {
      kExtensionNonPow2 = 0,
      kExtensionNonPow2ES,
      kExtensionBGRA,
      kExtensionBGR,
      kExtensionTextureMirroredRepeat,
      kExtensionTextureEdgeClamp,
      kExtensionTextureBorderClamp,
      kExtensionDepthTexture,
      kExtensionDepthTextureCubeMap,
      kExtensionDepth24,
      kExtensionDepth32,
      kExtensionPackedDepthStencil,
      kExtensionStencil8,
      kExtensionTextureHalfFloat,
      kExtensionTextureFloat,
      kExtensionTextureRG,
      kExtensionTextureNorm16,
      kExtensionTextureSNorm,
      kExtensionTextureSNorm16,
      kExtensionFloatBufferClamp,
      kExtensionFragDepth,
      kExtensionDerivatives,
      kExtensionDrawBuffers,
      kExtensionElementIndexUInt,
      kExtensionElementIndexUInt8,
      kExtensionVertexAttribUInt8,
      kExtensionVertexAttribHalfFloat,
      kExtensionGeometryShader,
      kExtensionLayeredRender,
      kExtensionES2Compatibility,
      kExtensionRequiredInternalFmt,
      kExtensionNoWebGLLimits,
      kExtensionCopyBuffer,
      kExtensionCubeMap,
      kExtensionCubeMapSeamless,
      kExtensionUnpackSubimage,
      kExtensionFragmentShaderPrimitiveID,
      kExtensionMapBuffer,
      kExtensionPBO,

      kNumExtensions
    };
    enum FunctionName
    {
      kPfnDrawBuffers = 0,
      kPfnProgramParameteri,
      kPfnFramebufferTexture,
      kPfnClampColor,
      kPfnCopyBufferSubData,
      kPfnMapBuffer,
      kPfnUnmapBuffer,

      kNumFunctions
    };
  protected:
    OdUInt32 m_extensionChecked[kNumExtensions / 32 + 1];
    OdUInt32 m_extensionAvailable[kNumExtensions / 32 + 1];
    OdTrRndLocalContext *m_pLocalContext;
    friend class OdTrRndLocalContext;
  protected:
    OdTrRndNoGLExtensionsRegistry(OdTrRndLocalContext *pLocalContext)
      : m_pLocalContext(pLocalContext)
    {
      for (long nExtReg = 0; nExtReg < kNumExtensions / 32 + 1; nExtReg++)
        m_extensionChecked[nExtReg] = m_extensionAvailable[nExtReg] = 0;
    }
    virtual bool isExtensionSupportedImpl(ExtensionName nExt) = 0;
  public:
    OdTrRndLocalContext *localContext() const { return m_pLocalContext; }
    virtual ~OdTrRndNoGLExtensionsRegistry() { }

    bool isExtensionSupported(ExtensionName nExt)
    { const OdUInt32 nExtReg = nExt / 32, nExtBit = 1 << (nExt % 32);
      if (GETBIT(m_extensionChecked[nExtReg], nExtBit))
        return GETBIT(m_extensionAvailable[nExtReg], nExtBit);
      const bool bExtAvail = isExtensionSupportedImpl(nExt);
      SETBIT_1(m_extensionChecked[nExtReg], nExtBit);
      SETBIT(m_extensionAvailable[nExtReg], nExtBit, bExtAvail);
      return bExtAvail;
    }

    virtual bool isFunctionAvailable(FunctionName nFunc) { return false; }

    // Extension function callers
    // kExtensionDrawBuffers
    virtual void glDrawBuffers(GLsizei n, const GLenum *bufs) { }
    // kExtensionGeometryShader
    virtual void glProgramParameteri(GLuint program, GLenum pname, GLint value) { }
    virtual void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) { }
    // kExtensionFloatBufferClamp
    virtual void glClampColor(GLenum target, GLenum clamp) { }
    // kExtensionCopyBuffer
    virtual void glCopyBufferSubData(GLenum readtarget, GLenum writetarget,
                                     GLintptr readoffset, GLintptr writeoffset,
                                     GLsizeiptr size) { }
    // kExtensionMapBuffer
    virtual void *glMapBuffer(GLenum target, GLenum access) { return nullptr; }
    virtual GLboolean glUnmapBuffer(GLenum target) { return GL_FALSE; }
};

#endif // ODTRRNDNOGLEXTENSIONSREGISTRY
