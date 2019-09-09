#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Analysis/CGSCCPassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/Analysis/DomTreeUpdater.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
using namespace llvm;

namespace {
    struct Hi : public ModulePass {
        static char ID;
        Hi() : ModulePass(ID) {}

        bool runOnModule(Module &M) override {
            errs() << "Hi: " << '\n';

            // get the function to be cloned
            Function *OldFunc = M.getFunction("another_function");

            // get necessary info about the function
            FunctionType *ftype = OldFunc->getFunctionType();

            // insert new function
            M.getOrInsertFunction("the_new_function", ftype);

            // set parameters to clone OldFunction into NewFunction
            ValueToValueMapTy VMap;

            // create new function
            Function *NewFunction = CloneFunction(OldFunc, VMap);
            NewFunction->setName("the_new_another_function");

            // check if the function was cloned properly
            // for (auto &F : M) {
            //     errs() << F.getName() << '\n';
            // }

            M.dump();

            return true;
        }
    };
}

char Hi::ID = 0;
static RegisterPass<Hi> X("hi", "Hi World Pass", false, false);

// static llvm::RegisterStandardPasses Y(
//     llvm::PassManagerBuilder::EP_EarlyAsPossible,
//     [](const llvm::PassManagerBuilder &Builder,
//        llvm::legacy::PassManagerBase &PM) { PM.add(new Hi()); });