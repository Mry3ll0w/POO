/* -*-c++-*-
 * Cabecera para el DSL de comprobaciones estáticas de código fuente
 * de las prácticas de POO.
 * ©2021 Los profesores de POO.
*/
#ifndef EXECUTE_H_
#define EXECUTE_H_

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

#include "info.h"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <fstream>

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include "matchers.h"

class execute : public MatchFinder::MatchCallback, public ASTConsumer,
		public RecursiveASTVisitor<execute>
{

// ----------------------- General ---------------------
public:
  virtual void run(const MatchFinder::MatchResult &Result);
  void postRun();
  bool check_same_decl_canonical(const Decl *c1, const Decl *c2);

private:
  ASTContext *Context;
  Rewriter Rewrite;
  typedef std::multimap<std::string, Info> A;
  typedef A::iterator AI;

/*
**
** GENERAL METHODS
**
*/

public:
  bool foundAll(A a);
  bool foundAny(A a);
  bool anyFoundAndInvalid(A a);
  bool allFoundAndValid(A a);
  void getMessagesOfNotFound(A a);
  void getMessagesOfNotFoundOrInvalid(A a);
  void getMessagesOfFound(A a);
  void getMessagesCheckingExplicitSpecified(A a);
  bool existClass(const CXXRecordDecl *foundClass);
  bool existConstructor(const CXXConstructorDecl *foundConstructor);
  bool existDestructor(const CXXDestructorDecl *foundDestructor);
  bool existDeleteExpression(const CXXDeleteExpr *foundDeleteExpression);
  bool existMethod(const CXXMethodDecl *foundMethod);
  bool existFunction(const FunctionDecl *foundFunction);
  bool existMember(const FieldDecl *foundMember);
  bool existVariable(const VarDecl *foundVariable);

/*
**
** GENERAL CHECK PARAMS
**
*/

public:
  bool checkInitializersConstructor(const CXXConstructorDecl *foundConstructor,
				    std::vector<std::string> parameters);
  bool checkParams(const FunctionDecl *foundFunction,
		   std::vector<std::string> parameters);
  bool checkParamsFunction(const FunctionDecl *foundFunction,
			   std::vector<std::string> parameters);
  bool checkWithoutParams(std::vector<std::string> params);
  bool markedConst(std::string c1, bool c2);
  bool markedDefault(std::string c1, bool c2);
  bool checkDefArgs(const FunctionDecl* function, unsigned int numDefArgs,
		    std::vector<std::string> defArgs);
  bool checkRegularExpresion(std::string str1, std::string str2);

/*
**
** CLASSES
**
*/

// ----------------------- CLASSES ---------------------
public:
  void setClasses(std::string className, std::string message);

private:
  void classWithName(const MatchFinder::MatchResult &Result);
  void hasClass();
  A classes;
  
  /*
  **
  ** CONSTRUCTORS
  **
  */
  
  // ----------------------- DEFAULT CONSTRUCTOR ---------------------

public:
  void setDefaultConstructors(std::string className, bool exist,
			      std::string notFoundMessage);

private:
  void classWithDefaultConstructor(const MatchFinder::MatchResult &Result);
  void hasDefaultConstructor();
  A defaultConstructors;

  // ----------------------- COPY CONSTRUCTOR ---------------------

public:
  void setCopyConstructors(std::string className, bool exist,
			   std::string notFoundMessage);

private:
  void classWithCopyConstructor(const MatchFinder::MatchResult &Result);
  void hasCopyConstructor();
  A copyConstructors;
  
  // ----------------------- MOVE CONSTRUCTORS ---------------------
  
public:
  void setMoveConstructors(std::string className, bool exist,
			   std::string notFoundMessage);

private:
  void classWithMoveConstructor(const MatchFinder::MatchResult &Result);
  void hasMoveConstructor();
  A moveConstructors;

// ----------------------- DESTRUCTOR ---------------------

public:
  void setDestructors(std::string className, bool exist, std::string message);

private:
  void classWithDestructor(const MatchFinder::MatchResult &Result);
  void hasDestructor();
  A destructors;

  // ----------------------- DELETE MEMBERS ---------------------

public:
  void setDeleteMembers(std::string className, std::string memberName,
			std::string message);

private:
  void deleteMember(const MatchFinder::MatchResult &Result);
  void hasDeleteMember();
  A deleteMembers;

  // ----------------------- CLASS WITH CONSTRUCTOR WITH INITIALIZERS --------

public:
  void setInitializers(std::string className,
		       std::vector<std::string> parameters,
		       std::vector<std::string> inits, std::string message);

private:
  void classWithListInitializerConstructor(const MatchFinder::MatchResult
					   &Result);
  A initializers;
  void hasInitializer();

  // ----------------------- NUMBER OF CONSTRUCTORS ---------------------

public:
  void setConstructors(std::string className, unsigned int constructors,
		       bool lenient, std::string message);

private:
  void numberOfConstructor(const MatchFinder::MatchResult &Result);
  void howManyConstructors();
  A constructors;
  
  // ----------------------- EXPLICIT SPECIFIED CONSTRUCTORS ----------------

public:
  void setExplicitSpecifiedConstructors(std::string className,
					std::vector<std::string> parameters,
					std::string message);

private:
  void explicitSpecifiedConstructor(const MatchFinder::MatchResult &Result);
  void hasExplicitSpecifiedConstructor();
  A explicitSpecifiedConstructors;

  // ----------------------- CATCHING EXCEPTIONS ---------------------

public:
  void setTakeExceptions(std::string exceptionClass, std::string message);
  
private:
  void takeException(const MatchFinder::MatchResult &Result);
  void hasTakeException();
  A takeExceptions;
  
  /*
  **
  ** VARIABLES
  **
  */
  
  // ----------------------- MEMBER ---------------------

public:
  void setMembers(std::string className, std::string memberName,
		  std::string constant, bool exist, std::string message);

private:
  void classWithMember(const MatchFinder::MatchResult &Result);
  A members;
  void hasMember();
  
  // ----------------------- STATIC VARIABLE ---------------------

public:
  void setStaticVariables(std::string className, std::string variableName,
			  std::string constant, std::string message);

private:
  void classWithStaticVariable(const MatchFinder::MatchResult &Result);
  A staticVariables;
  void hasStaticVariable();

  // ----------------------- RELEASED VARIABLE ---------------------

public:
  void setReleasedVariables(std::string message);
  bool allReleasedVariables();
  
private:
  void releaseVariable(const MatchFinder::MatchResult &Result);
  std::map<const VarDecl*, bool> variables_new;
  std::string releasedVariableMessage;
  void hasReleasedVariable();

  // ----------------------- PRIVATE MEMBERS ---------------------

public:
  void setClassWithAllPrivateMembers(std::string className,
				     std::string message);

private:
  void classWithAllPrivateMember(const MatchFinder::MatchResult &Result);
  void hasAllPrivateMember();
  A classWithAllPrivateMembers;

  // ----------------------- ACCESS LEVEL VARIABLE MEMBERS ----------

public:
  void setMembersAccessLevel(std::string className, std::string memberName,
			     std::string level, std::string message);

private:
  void classWithVariableMembersAccessLevel(const MatchFinder::MatchResult
					   &Result);
  void hasVariableMembersAccessLevel();
  A variableMembersAccessLevel;

  /*
  **
  ** METHODS
  **
  */
  
  // ----------------------- METHODS WITH NAME---------------------

public:
  void setMethodsWithName(std::string methodName, std::string className,
			  std::vector<std::string> params,
			  std::string constant, std::string message);

private:
  void methodWithName(const MatchFinder::MatchResult &Result);
  A methodsWithName;
  void hasMethodWithName();

  // -------------------- METHODS WITH DEFAULT ARG------------------

public:
  void setMethodsWithDefaultArg(std::string methodName, std::string className,
				std::vector<std::string> params,
				std::vector<std::string> defaults,
				std::string constant, std::string message);

private:
  void methodWithDefaultArg(const MatchFinder::MatchResult &Result);
  A methodsWithDefaultArg;
  void hasMethodWithDefaultArg();
  
  // ----------------------- METHODS WITH REFERENCED VARIABLE---------------

public:
  void setMethodsWithReferencedVariable(std::string methodName,
					std::string className,
					std::vector<std::string> params,
					std::string constant,
					std::string memberVariable,
					std::string message);

private:
  void methodWithReferencedVariable(const MatchFinder::MatchResult &Result);
  A methodsWithReferencedVariable;
  void hasMethodWithReferencedVariable();

// ----------------------- METHODS WITH REFERENCED METHOD---------------------

public:
  void setMethodsWithReferencedMethod(std::string mainMethodName,
				      std::vector<std::string> mainMethodParams,
				      std::string mainClassName,
				      std::string mainConstant,
				      std::string usedMethodName,
				      std::vector<std::string> usedMethodParams,
				      std::string usedClasName,
				      std::string usedConstant,
				      std::string message);

private:
  void methodWithReferencedMethod(const MatchFinder::MatchResult &Result);
  A methodsWithReferencedMethod;
  void hasMethodWithReferencedMethod();

  // ----------------------- METHODS NO EXCEPT---------------------

public:
  void setNoExceptMethods(std::string methodName,
			  std::vector<std::string> params,
			  std::string className, std::string constant,
			  std::string message);

private:
  void noExceptMethod(const MatchFinder::MatchResult &Result);
  A noExceptMethods;
  void hasNoExceptMethod();

  // ----------------------- METHODS INLINE---------------------

public:
  void setInlineMethods(std::string methodName, std::vector<std::string> params,
			std::string className, std::string constant,
			std::string message);

private:
  void inlineMethod(const MatchFinder::MatchResult &Result);
  A inlineMethods;
  void hasInlineMethod();

  // ----------------------- DEFAULT ARGUMENTS IN METHODS ---------------------

public:
  void setDefaultArgumentsInMethod(std::string methodName,
				   std::vector<std::string> params,
				   std::string className, std::string constant,
				   unsigned int numDefaultArgs,
				   std::vector<std::string> defaultArgs,
				   std::string message);

private:
  void defaultArgumentsInMethod(const MatchFinder::MatchResult &Result);
  A defaultArgumentsInMethods;
  void hasDefaultArgumentsInMethod();
  
  // ----------------------- METHODS DELETED ---------------------

public:
  void setDeletedMethods(std::string methodName, std::string className,
			 std::vector<std::string> params, std::string constant,
			 std::string message);
private:
  void deletedMethod(const MatchFinder::MatchResult &Result);
  void hasDeletedMethod();
  A deletedMethods;

  // ----------------------- METHODS DEFAULT ---------------------

public:
  void setDefaultedMethods(std::string methodName, std::string className,
			   std::vector<std::string> params,
			   std::string constant, std::string message);
private:
  void defaultedMethod(const MatchFinder::MatchResult &Result);
  void hasDefaultedMethod();
  A defaultedMethods;
  
  // ----------------------- METHODS VIRTUAL ---------------------
public:
  void setVirtualMethods(std::string methodName, std::string className,
			 std::vector<std::string> params, std::string constant,
			 std::string message);
private:
  void virtualMethod(const MatchFinder::MatchResult &Result);
  void hasVirtualMethod();
  A virtualMethods;
  
  /*
  **
  ** OPERATORS
  **
  */
  
  // ----------------------- COPY ASSIGNMENT OPERATOR ---------------------

public:
  void setCopyAssignmentOperators(std::string className, bool exist,
				  std::string message);

private:
  void classWithCopyAssignmentOperator(const MatchFinder::MatchResult &Result);
  void hasCopyAssignmentOperator();
  A copyAssignmentOperators;
  
  // ----------------------- MOVE ASSIGNMENT OPERATOR ---------------------

public:
  void setMoveAssignmentOperators(std::string className, bool exist,
				  std::string message);

private:
  void classWithMoveAssignmentOperator(const MatchFinder::MatchResult &Result);
  void hasMoveAssignmentOperator();
  A moveAssignmentOperators;

  // ----------------------- FUNCTIONS WITH REFERENCED FUNCTIONS -----------

public:
  void setFunctionsWithReferencedFunction(std::string mainFunctionName,
					  std::vector<std::string>
					  mainFunctionParameters,
					  std::string usedFuncionName,
					  std::vector<std::string>
					  usedFunctionParameters,
					  std::string message);

private:
  void functionWithReferencedFunction(const MatchFinder::MatchResult &Result);
  A functionsWithReferencedFunction;
  void hasFunctionWithReferencedFunction();

  // ----------------------- METHODS WITH REFERENCED FUNCTIONS -----------

public:
  void setMethodsWithReferencedFunction(std::string mainMethodName,
					std::vector<std::string>
					mainMethodParameters,
					std::string mainClassName,
					std::string mainConstant,
					std::string usedFuncionName,
					std::vector<std::string>
					usedFunctionParameters,
					std::string message);

private:
  void methodWithReferencedFunction(const MatchFinder::MatchResult &Result);
  A methodsWithReferencedFunction;
  void hasMethodWithReferencedFunction();
  
  // ----------------------- FUNCTIONS WITH REFERENCED METHODS -----------

public:
  void setFunctionsWithReferencedMethod(std::string mainFunctionName,
					std::vector<std::string>
					mainFunctionParameters,
					std::string usedMethodName,
					std::vector<std::string>
					usedMethodParameters,
					std::string usedConstant,
					std::string usedClass,
					std::string message);

private:
  void functionWithReferencedMethod(const MatchFinder::MatchResult &Result);
  A functionsWithReferencedMethod;
  void hasFunctionWithReferencedMethod();
  
  // ----------------------- FUNCTIONS WITH NAME ---------------------
  
public:
  void setFunctionsWithName(std::string functionName,
			    std::vector<std::string> params,
			    std::string message);

private:
  void functionWithName(const MatchFinder::MatchResult &Result);
  void hasFunctionWithName();
  A functionsWithName;

  /*
  **
  ** HEADERS
  **
  */
  
  // ----------------------- INCLUDED HEADER---------------------

public:
  void setInvocationsFromHeader(std::string functionNames,
				std::string headerName, bool exist,
				std::string message);

private:
  void invocationsFromHeader(const MatchFinder::MatchResult &Result);
  A invocationsFromHeaders;
  void hasInvocationsFromHeader();
  
  // --------------------- FILE INCLUDE HEADER ------------------
public:
  void setFileIncludeHeader(std::vector<std::string> fileName,
			    std::string headerName, std::string message);
private:
  A fileIncludedHeader;
  void hasFileIncludedHeader();
  
  /*
  **
  ** PREPROCESSOR
  **
  */
  
  // ----------------------- PREPROCESSOR ---------------------
public:
  void setGuardClauses(std::string fileName, std::string message);
private:
  A guardClauses;
  void hasGuardClauses();
  
  /*
  **
  ** FRIEND MEMBERS
  **
  */
  
  // ----------------------- NOT FRIEND MEMBERS---------------------
  
public:
  void setNotFriendMembers(std::string className, std::string message);

private:
  void classWithNotFriendMember(const MatchFinder::MatchResult &Result);
  A notFriendMembers;
  void hasNotFriendMember();
  
  // ----------------------- FRIEND FUNCTION ------------------------

public:
  void setFriendFunction(std::string functionName, std::string className,
			 std::vector<std::string> params, std::string message);

private:
  void classWithFriendFunction(const MatchFinder::MatchResult &Result);
  A friendFunctions;
  void hasFriendFunction();
  

  //------------------------ FRIEND CLASS --------------------------

public:
  void setFriendClass(std::string className, std::string friendClassName,
		      std::string message);

private:
  void classWithFriendClass(const MatchFinder::MatchResult &Result);
  A friendClasses;
  void hasFriendClass();
  bool friend_class(const CXXRecordDecl* c1, std::string c2);
  
  //------------------------ DYNAMIC CAST --------------------------
public:
  void setDynamicCast(std::string methodName,
		      std::vector<std::string> parameters,
		      std::string constant, std::string className,
		      std::string originType, std::string dstType,
		      std::string message);
private:
  void methodWithDynamicCast(const MatchFinder::MatchResult &Result);
  A dynamicCast;
  void hasDynamicCast();
  
  /*
  **
  ** FINAL CHECK
  **
  */

  // ----------------------- FINAL CHECK ---------------------
  
public:
  void setCorrectMessage(std::string message);
  std::string getCorrectMessage();
  void setIncorrectMessage(std::string message);
  std::string getIncorrectMessage();
  
private:
  bool correct = true;
  std::string correctMessage, incorrectMessage;
  void isCorrect();
  void showMessages();
  std::set<std::string> messages;
};

#endif //EXECUTE_H_
