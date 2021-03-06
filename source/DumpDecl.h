#ifndef __LEARN_IT_H__
#define __LEARN_IT_H__

#include "clang/AST/Decl.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Tooling/Tooling.h"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace clang;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::driver;
using namespace clang::tooling;

class DumpDecl {
private:
  SourceManager *m_pSm;

public:
  DumpDecl();
  void SetSourceManager(const SourceManager *pSm);
  bool PrintDecl(Decl *pDecl);

private:
  void _PrintNamedDecl(NamedDecl *pDecl);
  void _PrintValueDecl(ValueDecl *pDecl);
  void _PrintFieldDecl(FieldDecl *pDecl);
  void _PrintVarDecl(VarDecl *pDecl);
  void _PrintFunctionDecl(FunctionDecl *pDecl);
  void _PrintParmVarDecl(ParmVarDecl *pDecl);
  void _PrintRecordDecl(RecordDecl *pDecl);
  void _PrintTypedefDecl(TypedefDecl *pDecl);
  void _PrintEnumConstantDecl(EnumConstantDecl *pDecl);
  void _PrintEnumDecl(EnumDecl *pDecl);
  void _PrintDecl(Decl *pDecl);
  void _PrintSrcLocStr(Decl *pDecl);
};

#endif // __LEARN_IT_H__
