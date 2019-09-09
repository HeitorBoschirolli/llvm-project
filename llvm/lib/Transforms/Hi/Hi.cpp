#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Analysis/CGSCCPassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
    struct Hi : public ModulePass {
        static char ID;
        Hi() : ModulePass(ID) {}

        bool runOnModule(Module &M) override {
            errs() << "Hi: " << '\n';

            auto ftype = M.getTypeByName("another_function");
            for (auto &F : M) {
                errs() << F.getName() << '\n';
            }

            M.getOrInsertFunction("the_new_function", ftype);

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