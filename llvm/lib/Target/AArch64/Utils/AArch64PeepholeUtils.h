//===-- AArch64PeepholeUtils.h - AArch64 peephole helpers -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Small helpers shared by AArch64 machine peepholes.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_AARCH64_UTILS_AARCH64PEEPHOLEUTILS_H
#define LLVM_LIB_TARGET_AARCH64_UTILS_AARCH64PEEPHOLEUTILS_H

#include "llvm/CodeGen/MachineRegisterInfo.h"

namespace llvm {

/// Follow vreg \c COPY definitions to the source register.
/// Stops at the first non-\c COPY def or a copy from a physical register.
inline Register lookThroughCopies(Register Reg,
                                  const MachineRegisterInfo &MRI) {
  const MachineInstr *MI;
  while (Reg.isVirtual() && (MI = MRI.getUniqueVRegDef(Reg)) && MI->isCopy() &&
         MI->getOperand(1).isReg()) {
    Register Src = MI->getOperand(1).getReg();
    if (!Src.isVirtual())
      break;
    Reg = Src;
  }
  return Reg;
}

} // end namespace llvm

#endif // LLVM_LIB_TARGET_AARCH64_UTILS_AARCH64PEEPHOLEUTILS_H
