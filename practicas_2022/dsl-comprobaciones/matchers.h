/* -*-c++-*-
 * Cabecera para el DSL de comprobaciones estáticas de código fuente en C++
 * para las prácticas de POO.
 * ©2021 Los profesores de POO.
*/
#ifndef MATCHERS_H_
#define MATCHERS_H_

#undef P1
#undef P2

#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchersInternal.h"
#include "clang/ASTMatchers/ASTMatchersMacros.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/CommandLine.h"
#include "clang/Rewrite/Frontend/Rewriters.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CompilationDatabase.h"

#include <iostream>

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;
using namespace std;


namespace clang{
  namespace ast_matchers{
    AST_MATCHER(clang::CXXDestructorDecl, isImplicitDestructor) {
      return Node.isImplicit();
    }
    AST_MATCHER(clang::CXXRecordDecl, hasCopyConstructorWithConstParam) {
      return Node.hasCopyConstructorWithConstParam();
    }
    AST_MATCHER(clang::CXXMethodDecl, isImplicitMethod) {
      return Node.isImplicit();
    }
    AST_MATCHER(clang::FunctionDecl, isImplicitFunction) {
      return Node.isImplicit();
    }
  }
}

/*
**
** CLASSES
**
*/

DeclarationMatcher classWithName_Matcher(string className);
DeclarationMatcher dynamic_cast_Matcher(string methodName, string className);

/*
**
** CONSTRUCTORS
**
*/

DeclarationMatcher defaultConstructor_Matcher(string className);
DeclarationMatcher copyConstructor_Matcher(string className);
DeclarationMatcher deletedCopyConstructor_Matcher(string className);
DeclarationMatcher deletedConstructor_Matcher(string className);
DeclarationMatcher moveConstructor_Matcher(string className);
DeclarationMatcher destructor_Matcher(string className);
DeclarationMatcher destructorDeleteMember_Matcher(string className,
						  string memberName);
DeclarationMatcher listInitializerConstructor_Matcher(string className);
DeclarationMatcher numberOfConstructor_Matcher(string className);
DeclarationMatcher explicitSpecifiedConstructor_Matcher(string className);
DeclarationMatcher takeException_Matcher(string exceptionClass);

/*
**
** VARIABLES
**
*/

DeclarationMatcher member_Matcher(string className, string memberName);
DeclarationMatcher staticVariable_Matcher(string className,
					  string variableName);
DeclarationMatcher variableNew_Matcher();
DeclarationMatcher variableDelete_Matcher();
DeclarationMatcher allPrivateMember_Matcher(string className);
DeclarationMatcher memberVariableAccessLevel_Matcher(string className,
						     string memberName);

/*
**
** FRIEND MEMBERS
**
*/

DeclarationMatcher notFriendMember_Matcher(string className);
DeclarationMatcher friendFunction_Matcher(string functionName,
					  string className);
DeclarationMatcher friendClass_Matcher(string className,
				       string friendClassName);

/*
**
** METHODS
**
*/

DeclarationMatcher method_Matcher(string methodName, string className);
DeclarationMatcher methodWithReferencedVariable_Matcher(string methodName,
							string className,
							string usedVariable);
DeclarationMatcher methodWithReferencedMethod_Matcher(string mainMethodName,
						      string mainClassName,
						      string usedMethodName,
						      string usedClassName);
DeclarationMatcher noExceptMethod_Matcher(string methodName, string className);
DeclarationMatcher inlineMethod_Matcher(string methodName, string className);
DeclarationMatcher defaultArgumentsInMethod_Matcher(string methodName,
						    string className);
DeclarationMatcher deletedMethod_Matcher(string methodName, string className);
DeclarationMatcher defaultedMethod_Matcher(string methodName, string className);
DeclarationMatcher virtualMethod_Matcher(string methodName, string className);

/*
**
** OPERATORS
**
*/

DeclarationMatcher copyAssignmentOperator_Matcher(string className);
DeclarationMatcher moveAssignmentOperator_Matcher(string className);
DeclarationMatcher functionWithReferencedFuntion_Matcher(string
							 mainFunctionName,
							 string
							 usedFunctionName);
DeclarationMatcher methodWithReferencedFuntion_Matcher(string mainMethodName,
						       string mainClassName,
						       string usedFunctionName);
DeclarationMatcher functionWithReferencedMethod_Matcher(string mainFunctionName,
							string usedMethodName,
							string usedClassName);
DeclarationMatcher functionName_Matcher(string functionName);

/*
**
** HEADERS
**
*/

DeclarationMatcher invocationsFromHeader_Matcher(string nameFunction);

#endif //MATCHERS_H_
