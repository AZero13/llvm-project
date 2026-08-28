//===- OptimizeStdarg.cpp - Optimize stdarg functions -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This pass analyzes functions that use va_start and sets function attributes
// to communicate to the backend how many GPR and FPR registers are actually
// needed by the va_arg operations. This avoids unconditionally spilling all
// variadic registers in the prologue.
//
//===----------------------------------------------------------------------===//

#include "llvm/CodeGen/OptimizeStdarg.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "optimize-stdarg"

static bool optimizeStdarg(Function &F, const TargetMachine *TM) {
  if (F.isDeclaration() || F.hasOptNone())
    return false;

  bool HasVAStart = false;
  for (const BasicBlock &BB : F) {
    for (const Instruction &I : BB) {
      if (auto *II = dyn_cast<IntrinsicInst>(&I)) {
        if (II->getIntrinsicID() == Intrinsic::vastart) {
          HasVAStart = true;
          break;
        }
      }
    }
    if (HasVAStart)
      break;
  }

  if (!HasVAStart)
    return false;

  const TargetSubtargetInfo *STI = TM->getSubtargetImpl(F);
  const TargetLowering *TLI = STI->getTargetLowering();

  unsigned RequiredGPRs = 0;
  unsigned RequiredFPRs = 0;

  if (TLI->analyzeStdargUsage(F, RequiredGPRs, RequiredFPRs)) {
    F.addFnAttr("va_list_gpr_size", std::to_string(RequiredGPRs));
    F.addFnAttr("va_list_fpr_size", std::to_string(RequiredFPRs));
    return true; // We modified the function by adding attributes
  }

  return false;
}

PreservedAnalyses OptimizeStdargPass::run(Function &F, FunctionAnalysisManager &AM) {
  if (!optimizeStdarg(F, TM))
    return PreservedAnalyses::all();

  PreservedAnalyses PA;
  PA.preserveSet<CFGAnalyses>();
  return PA;
}
