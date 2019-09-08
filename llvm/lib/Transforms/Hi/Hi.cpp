#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Analysis/CGSCCPassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
    struct Hi : public CallGraphSCCPass {
        static char ID;
        Hi() : CallGraphSCCPass(ID) {}

        bool runOnSCC(CallGraphSCC &SCC) override {
            errs() << "Hi: ";
            errs().write_escaped(std::to_string(SCC.size())) << '\n';
            errs() << "=============================" << '\n';

            int counter = 0;
            for (CallGraphNode *Node : SCC) {
                errs() << counter++ << '\n';
                Function *F = Node->getFunction();
                // std::string s = F->getName();
                // errs().write_escaped(F->getName()) << '\n';
            }
            return false;
        }
    };
}

char Hi::ID = 0;
static RegisterPass<Hi> X("hi", "Hi World Pass", false, false);

// static llvm::RegisterStandardPasses Y(
//     llvm::PassManagerBuilder::EP_EarlyAsPossible,
//     [](const llvm::PassManagerBuilder &Builder,
//        llvm::legacy::PassManagerBase &PM) { PM.add(new Hi()); });