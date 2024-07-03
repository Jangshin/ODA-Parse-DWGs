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
// GLES2 differential rendering state transitions container

#ifndef ODTRRNDDIFFERENTIALTRANSITION
#define ODTRRNDDIFFERENTIALTRANSITION

#include "TD_PackPush.h"

#include "OdVector.h"
#include "../TrVisStaticSharedPtr.h"

/** \details
  .

  Library: Source code provided.

  <group ExRender_Classes>
*/
class OdTrRndDifferentialTransition
{
  public:
    union Var
    {
      bool m_bool;
      OdInt32 m_int32;
      OdUInt32 m_uint32;
      float m_float;
    };
    struct Op
    {
      OdUInt32 m_opcode;
      Var m_var;
      Op() {}
      Op(OdUInt32 opcode) : m_opcode(opcode) { m_var.m_uint32 = 0; }
      bool operator ==(const Op &op2) const { return (m_opcode == op2.m_opcode) && (m_var.m_uint32 == op2.m_var.m_uint32); }
      bool operator !=(const Op &op2) const { return (m_opcode != op2.m_opcode) || (m_var.m_uint32 != op2.m_var.m_uint32); }
    };
    struct Ops
    {
      Op m_fwd;
      Op m_back;
      bool operator ==(const Ops &op2) const { return (m_fwd == op2.m_fwd) && (m_back == op2.m_back); }
      bool operator !=(const Ops &op2) const { return (m_fwd != op2.m_fwd) || (m_back != op2.m_back); }
    };
  protected:
    OdVector<Ops, OdMemoryAllocator<Ops> > m_ops;
  public:
    OdTrRndDifferentialTransition() { }
    ~OdTrRndDifferentialTransition() { }

    Op make_op(OdUInt32 opcode) { return Op(opcode); }
    Op make_op(OdUInt32 opcode, bool val) { Op op(opcode); op.m_var.m_bool = val; return op; }
    Op make_op(OdUInt32 opcode, OdInt32 val) { Op op(opcode); op.m_var.m_int32 = val; return op; }
    Op make_op(OdUInt32 opcode, OdUInt32 val) { Op op(opcode); op.m_var.m_uint32 = val; return op; }
    Op make_op(OdUInt32 opcode, float val) { Op op(opcode); op.m_var.m_float = val; return op; }

    void push_ops(const Op &fwd, const Op &back, bool bFwd = true)
    { 
      Ops ops;
      if (bFwd) { ops.m_fwd = fwd; ops.m_back = back; }
      else      { ops.m_fwd = back; ops.m_back = fwd; }
      m_ops.push_back(ops);
    }
    void finalize() { m_ops.setPhysicalLength(m_ops.size()); }

    class Iterator
    {
      bool m_bForward;
      const Ops *m_pOps;
      OdUInt32 m_nOps;
      OdInt32 m_nCaret;
      public:
        Iterator(const OdVector<Ops, OdMemoryAllocator<Ops> > &ops, bool bForward)
          : m_bForward(bForward)
        {
          m_pOps = ops.getPtr(); m_nOps = ops.size();
          m_nCaret = (bForward) ? 0 : OdInt32(m_nOps) - 1;
        }
        bool done() const { return (m_nCaret < 0) || (OdUInt32(m_nCaret) >= m_nOps); }
        bool next() { if (m_bForward) m_nCaret++; else m_nCaret--; return done(); }
        bool back() { if (m_bForward) m_nCaret--; else m_nCaret++; return done(); }
        const Op &op() const { return (m_bForward) ? m_pOps[m_nCaret].m_fwd : m_pOps[m_nCaret].m_back; }
    };
    Iterator iterator(bool bForward) const { return Iterator(m_ops, bForward); }

    bool operator ==(const OdTrRndDifferentialTransition &dt2) const
    { const OdUInt32 opsSize = m_ops.size();
      if (opsSize == dt2.m_ops.size())
      { const Ops *pOps1 = m_ops.getPtr(), *pOps2 = dt2.m_ops.getPtr();
        for (OdUInt32 nOp = 0; nOp < opsSize; nOp++)
        { if (pOps1[nOp] != pOps2[nOp])
            return false; 
        }
        return true;
      }
      return false;
    }
    bool operator !=(const OdTrRndDifferentialTransition &dt2) const
    { const OdUInt32 opsSize = m_ops.size();
      if (opsSize == dt2.m_ops.size())
      { const Ops *pOps1 = m_ops.getPtr(), *pOps2 = dt2.m_ops.getPtr();
        for (OdUInt32 nOp = 0; nOp < opsSize; nOp++)
        { if (pOps1[nOp] != pOps2[nOp])
            return true; 
        }
        return false;
      }
      return true;
    }
};

/** \details
    <group ExRender_Windows_Classes> 
*/
typedef OdSharedPtr<OdTrRndDifferentialTransition> OdTrRndDifferentialTransitionPtr;

#include "TD_PackPop.h"

#endif // ODTRRNDDIFFERENTIALTRANSITION
