﻿#include <memory>
#include <string>

#include "Common.h"
#include "DumpDecl.h"
#include <clang/AST/Decl.h>

using namespace DcLib;

LOG_DECISION_DEFAULT(false);

// clang-format off

DumpDecl::DumpDecl() {
  AppCxt &AppCxt = AppCxt::getInstance();
  LOG_DECISION_CHANGE(AppCxt.MemoBoard.Config.GetData()->Debug.Log.bDumpDecl);
}

void DumpDecl::SetSourceManager(const SourceManager *pSm) { this->m_pSm = (SourceManager *)pSm; }

bool DumpDecl::PrintDecl(Decl *pDecl) {
  if (!pDecl) {
    return false;
  }

  DcLib::Log::Out(INFO_ALL, "");
  DcLib::Log::Out(INFO_ALL, "V==start line====================================================================V");

  if (isa<Decl>(pDecl)) {
    _PrintDecl(dyn_cast<Decl> (pDecl));
  }

  if (isa<EnumConstantDecl>(pDecl)) {
    _PrintEnumConstantDecl(dyn_cast<EnumConstantDecl> (pDecl));
  }

  if (isa<EnumDecl>(pDecl)) {
    _PrintEnumDecl(dyn_cast<EnumDecl> (pDecl));
  }

  if (isa<RecordDecl>(pDecl)) {
    _PrintRecordDecl(dyn_cast<RecordDecl> (pDecl));
  }

  if (isa<ValueDecl>(pDecl)) {
    _PrintValueDecl(dyn_cast<ValueDecl> (pDecl));
  }

  if (isa<FieldDecl>(pDecl)) {
    _PrintFieldDecl(dyn_cast<FieldDecl> (pDecl));
  }

  if (isa<VarDecl>(pDecl)) {
    _PrintVarDecl(dyn_cast<VarDecl> (pDecl));
  }

  if (isa<FunctionDecl>(pDecl)) {
    _PrintFunctionDecl(dyn_cast<FunctionDecl> (pDecl));
  }

  if (isa<ParmVarDecl>(pDecl)) {
    _PrintParmVarDecl(dyn_cast<ParmVarDecl> (pDecl));
  }

  if (isa<TypedefDecl>(pDecl)) {
    _PrintTypedefDecl(dyn_cast<TypedefDecl> (pDecl));
  }

  DcLib::Log::Out(INFO_ALL, "----------------------------------------------------------------------------------");
  // Keep this as the last.
  if (isa<NamedDecl>(pDecl)) {
    _PrintNamedDecl(dyn_cast<NamedDecl> (pDecl));
  }

  DcLib::Log::Out(INFO_ALL, "^==end line=======================================================================^");
  return true;
}

void DumpDecl::_PrintNamedDecl(NamedDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "NamedDecl.getNameAsString()                   = %s", pDecl->getNameAsString().c_str());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.getDeclName()                       = %s", pDecl->getDeclName().getAsString().c_str());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.getDeclKindName()                   = %s", pDecl->getDeclKindName());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.getQualifiedNameAsString()          = %s", pDecl->getQualifiedNameAsString().c_str());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isCanonicalDecl()                   = %d", pDecl->isCanonicalDecl());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isCXXClassMember()                  = %d", pDecl->isCXXClassMember());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isCXXInstanceMember()               = %d", pDecl->isCXXInstanceMember());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isDefinedOutsideFunctionOrMethod()  = %d", pDecl->isDefinedOutsideFunctionOrMethod());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isDeprecated()                      = %d", pDecl->isDeprecated());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isExternallyDeclarable()            = %d", pDecl->isExternallyDeclarable());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isExternallyVisible()               = %d", pDecl->isExternallyVisible());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isFirstDecl()                       = %d", pDecl->isFirstDecl());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isFromASTFile()                     = %d", pDecl->isFromASTFile());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isFunctionOrFunctionTemplate()      = %d", pDecl->isFunctionOrFunctionTemplate());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isImplicit()                        = %d", pDecl->isImplicit());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isInAnonymousNamespace()            = %d", pDecl->isInAnonymousNamespace());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isInStdNamespace()                  = %d", pDecl->isInStdNamespace());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isInvalidDecl()                     = %d", pDecl->isInvalidDecl());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isLinkageValid()                    = %d", pDecl->isLinkageValid());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isLocalExternDecl()                 = %d", pDecl->isLocalExternDecl());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isModulePrivate()                   = %d", pDecl->isModulePrivate());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isOutOfLine()                       = %d", pDecl->isOutOfLine());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isParameterPack()                   = %d", pDecl->isParameterPack());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isReferenced()                      = %d", pDecl->isReferenced());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isTemplated()                       = %d", pDecl->isTemplated());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isTemplateDecl()                    = %d", pDecl->isTemplateDecl());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isTemplateParameter()               = %d", pDecl->isTemplateParameter());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isTemplateParameterPack()           = %d", pDecl->isTemplateParameterPack());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isThisDeclarationReferenced()       = %d", pDecl->isThisDeclarationReferenced());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isTopLevelDeclInObjCContainer()     = %d", pDecl->isTopLevelDeclInObjCContainer());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isUnavailable()                     = %d", pDecl->isUnavailable());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isUsed()                            = %d", pDecl->isUsed());
  DcLib::Log::Out(INFO_ALL, "NamedDecl.isWeakImported()                    = %d", pDecl->isWeakImported());
}

void DumpDecl::_PrintValueDecl(ValueDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "ValueDecl.isWeak()                            = %d", pDecl->isWeak());
}

void DumpDecl::_PrintFieldDecl(FieldDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "FieldDecl.isBitField()                        = %d", pDecl->isBitField());
  DcLib::Log::Out(INFO_ALL, "FieldDecl.isAnonymousStructOrUnion()          = %d", pDecl->isAnonymousStructOrUnion());
}

void DumpDecl::_PrintVarDecl(VarDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "VarDecl.isExternC()                           = %d", pDecl->isExternC());
  DcLib::Log::Out(INFO_ALL, "VarDecl.isInExternCContext()                  = %d", pDecl->isInExternCContext());
  DcLib::Log::Out(INFO_ALL, "VarDecl.isInExternCXXContext()                = %d", pDecl->isInExternCXXContext());
  DcLib::Log::Out(INFO_ALL, "VarDecl.isLocalVarDecl()                      = %d", pDecl->isLocalVarDecl());
  DcLib::Log::Out(INFO_ALL, "VarDecl.isLocalVarDeclOrParm()                = %d", pDecl->isLocalVarDeclOrParm());
  DcLib::Log::Out(INFO_ALL, "VarDecl.isFunctionOrMethodVarDecl()           = %d", pDecl->isFunctionOrMethodVarDecl());
  DcLib::Log::Out(INFO_ALL, "VarDecl.isStaticDataMember()                  = %d", pDecl->isStaticDataMember());
  DcLib::Log::Out(INFO_ALL, "VarDecl.isFileVarDecl()                       = %d", pDecl->isFileVarDecl());
  DcLib::Log::Out(INFO_ALL, "VarDecl.hasInit()                             = %d", pDecl->hasInit());
}

void DumpDecl::_PrintFunctionDecl(FunctionDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.getNameInfo()                    = %s", pDecl->getNameInfo().getAsString().c_str());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isDefined()                      = %d", pDecl->isDefined());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isThisDeclarationADefinition()   = %d", pDecl->isThisDeclarationADefinition());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.doesThisDeclarationHaveABody()   = %d", pDecl->doesThisDeclarationHaveABody());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isVariadic()                     = %d", pDecl->isVariadic());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isVirtualAsWritten()             = %d", pDecl->isVirtualAsWritten());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isPure()                         = %d", pDecl->isPure());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isDefaulted()                    = %d", pDecl->isDefaulted());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.hasPrototype()                   = %d", pDecl->hasPrototype());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isMain()                         = %d", pDecl->isMain());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isExternC()                      = %d", pDecl->isExternC());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isInExternCContext()             = %d", pDecl->isInExternCContext());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isInExternCXXContext()           = %d", pDecl->isInExternCXXContext());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isGlobal()                       = %d", pDecl->isGlobal());
  DcLib::Log::Out(INFO_ALL, "FunctionDecl.isInlined()                      = %d", pDecl->isInlined());
}

void DumpDecl::_PrintParmVarDecl(ParmVarDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "ParmVarDecl.isObjCMethodParameter()           = %d", pDecl->isObjCMethodParameter());
  DcLib::Log::Out(INFO_ALL, "ParmVarDecl.hasDefaultArg()                   = %d", pDecl->hasDefaultArg());
  DcLib::Log::Out(INFO_ALL, "ParmVarDecl.hasUnparsedDefaultArg()           = %d", pDecl->hasUnparsedDefaultArg());
  DcLib::Log::Out(INFO_ALL, "ParmVarDecl.hasInheritedDefaultArg()          = %d", pDecl->hasInheritedDefaultArg());
}

void DumpDecl::_PrintRecordDecl(RecordDecl *pDecl) {
  char *szTagKind = NULL;
  switch (pDecl->getTagKind()) {
  case TTK_Struct:
    szTagKind = "TTK_Struct";
    break;
  case TTK_Interface:
    szTagKind = "TTK_Interface";
    break;
  case TTK_Union:
    szTagKind = "TTK_Union";
    break;
  case TTK_Class:
    szTagKind = "TTK_Class";
    break;
  case TTK_Enum:
    szTagKind = "TTK_Enum";
    break;
  }

  DcLib::Log::Out(INFO_ALL, "RecordDecl.getTagKind() [switch-case]         = %s", szTagKind);
  DcLib::Log::Out(INFO_ALL, "RecordDecl.hasFlexibleArrayMember()           = %d", pDecl->hasFlexibleArrayMember());
  DcLib::Log::Out(INFO_ALL, "RecordDecl.isAnonymousStructOrUnion()         = %d", pDecl->isAnonymousStructOrUnion());
  DcLib::Log::Out(INFO_ALL, "RecordDecl.hasObjectMember()                  = %d", pDecl->hasObjectMember());
  DcLib::Log::Out(INFO_ALL, "RecordDecl.hasVolatileMember()                = %d", pDecl->hasVolatileMember());
  DcLib::Log::Out(INFO_ALL, "RecordDecl.isLambda()                         = %d", pDecl->isLambda());
}

void DumpDecl::_PrintTypedefDecl(TypedefDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "TypedefDecl");
  // TypedefDecl
  // static bool classof(const Decl *D) { return classofKind(D->getKind()); }
  // static bool classofKind(Kind K) { return K == Typedef; }
}

void DumpDecl::_PrintEnumConstantDecl(EnumConstantDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "EnumConstantDecl");
}

void DumpDecl::_PrintEnumDecl(EnumDecl *pDecl) {
  DcLib::Log::Out(INFO_ALL, "EnumDecl");
}

void DumpDecl::_PrintDecl(Decl *pDecl) {
  // SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  // SourceLocation MyCurrLoc = pDecl->getLocation();
  // SourceLocation MyEndLoc = pDecl->getEndLoc();

  // const char *szBegin = this->m_pSm->getCharacterData(MyBeginLoc);
  // const char *szCurr = this->m_pSm->getCharacterData(MyCurrLoc);
  // const char *szEnd = this->m_pSm->getCharacterData(MyEndLoc);
  // pDecl->
  // DcLib::Log::Out(INFO_ALL, "Decl.getBeginLoc().printToString              = %s",
  // pDecl->getBeginLoc().printToString(*this->m_pSm).c_str()); DcLib::Log::Out(INFO_ALL, " = %s",
  // szBegin); DcLib::Log::Out(INFO_ALL, "Decl.getLocation().printToString              = %s",
  // pDecl->getLocation().printToString(*this->m_pSm).c_str()); DcLib::Log::Out(INFO_ALL, " = %s",
  // szCurr); DcLib::Log::Out(INFO_ALL, "Decl.getEndLoc().printToString                = %s",
  // pDecl->getEndLoc().printToString(*this->m_pSm).c_str()); DcLib::Log::Out(INFO_ALL, " = %s",
  // szEnd);
  DcLib::Log::Out(INFO_ALL, "Decl");
}

void DumpDecl::_PrintSrcLocStr(Decl *pDecl) {
  SourceLocation MyBeginLoc = pDecl->getBeginLoc();
  SourceLocation MyCurrLoc  = pDecl->getLocation();
  SourceLocation MyEndLoc   = pDecl->getEndLoc();

  const char *szBegin = this->m_pSm->getCharacterData(MyBeginLoc);
  const char *szCurr  = this->m_pSm->getCharacterData(MyCurrLoc);
  const char *szEnd   = this->m_pSm->getCharacterData(MyEndLoc);

  DcLib::Log::Out(INFO_ALL, "Decl.getBeginLoc().printToString              = %s",
                  pDecl->getBeginLoc().printToString(*this->m_pSm).c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getLocation().printToString              = %s",
                  pDecl->getLocation().printToString(*this->m_pSm).c_str());
  DcLib::Log::Out(INFO_ALL, "Decl.getEndLoc().printToString                = %s",
                  pDecl->getEndLoc().printToString(*this->m_pSm).c_str());

  if ((szCurr - szBegin) > 0) {
    string Begin2Curr(szBegin, szCurr - szBegin);
    DcLib::Log::Out(INFO_ALL, "Begin2Curr                                    = %s",
                    Begin2Curr.c_str());
  }

  if ((szEnd - szBegin) > 0) {
    string Begin2End(szBegin, szEnd - szBegin);
    DcLib::Log::Out(INFO_ALL, "Begin2End                                     = %s",
                    Begin2End.c_str());
  }
  if (szCurr - szEnd) {
    string Curr2End(szCurr, szCurr - szEnd);
    DcLib::Log::Out(INFO_ALL, "Curr2End                                      = %s",
                    Curr2End.c_str());
  }
}
// clang-format on