/*
 * Fichero para el DSL de comprobaciones estáticas de código fuente en C++
 * para las prácticas de POO.
 * ©2021 Los profesores de POO.
 */

#include "matchers.h"

/*
**
** CLASSES
**
*/

DeclarationMatcher classWithName_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxRecordDecl(matchesName(className)).bind("classWithName");
  return matcher;
}

DeclarationMatcher dynamic_cast_Matcher(string methodName, string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  unless(isImplicitMethod()),
		  forEachDescendant(
				    cxxDynamicCastExpr(
						       hasDescendant(
				     implicitCastExpr().bind("dynamic_type")
								     )
						       ).bind("dynamic_method")
				    ),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).bind("classWithDynamicCast")
			  )
		  ).bind("methodWithDynamicCast");
  return matcher;
}

/*
**
** CONSTRUCTORS
**
*/

DeclarationMatcher defaultConstructor_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxConstructorDecl(
		       isDefaultConstructor(),
		       unless(isImplicit()),
		       ofClass(
			       cxxRecordDecl(
					     matchesName(className),
					     unless(isTemplateInstantiation())
					     ).bind(
						 "classWithDefaultConstructor")
			       )
		       ).bind("defaultConstructor");
  return matcher;
}

DeclarationMatcher copyConstructor_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxConstructorDecl(
		       isCopyConstructor(),
		       unless(isDefaulted()),
		       unless(isImplicit()),
		       ofClass(
			       cxxRecordDecl(
					     matchesName(className),
					     unless(isTemplateInstantiation())
					     ).bind("classWithCopyConstructor")
			       )
		       ).bind("copyConstructor");
  return matcher;
}

DeclarationMatcher moveConstructor_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxConstructorDecl(
		       isMoveConstructor(),
		       unless(isDefaulted()),
		       unless(isImplicit()),
		       ofClass(
			       cxxRecordDecl(
					     matchesName(className),
					     unless(isTemplateInstantiation())
					     ).bind("classWithMoveConstructor")
			       )
		       ).bind("moveConstructor");
  return matcher;
}

DeclarationMatcher destructor_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxDestructorDecl(
		      unless(isImplicitDestructor()),
		      ofClass(
			      cxxRecordDecl(
					    matchesName(className),
					    unless(isTemplateInstantiation())
					    ).bind("classWithDestructor")
			      )
		      ).bind("Destructor");
  return matcher;
}

DeclarationMatcher destructorDeleteMember_Matcher(string className,
						  string memberName)
{
  DeclarationMatcher matcher =
    cxxDestructorDecl(hasDescendant(cxxDeleteExpr(hasDescendant(memberExpr(
		      hasDeclaration(fieldDecl(matchesName(memberName)).
				     bind("deleteMember"))))
						  ).bind("deleteExpression")
				    ),
		      unless(isImplicitDestructor()),
		      ofClass(
			      cxxRecordDecl(
					    matchesName(className),
					    unless(isTemplateInstantiation())
					    ).bind("classWithDeleteMember")
			      )
		      );
  return matcher;
}

DeclarationMatcher listInitializerConstructor_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxConstructorDecl(
		       hasAnyConstructorInitializer(
						    cxxCtorInitializer()
						    ),
		       ofClass(
			       cxxRecordDecl(
					     matchesName(className),
					     unless(isTemplateInstantiation())).
			       bind("classWithListInitializerConstructor")
			       )
		       ).bind("listInitializerConstructor");
  return matcher;
}

DeclarationMatcher numberOfConstructor_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxConstructorDecl(
		       unless(isImplicit()),
		       unless(isDeleted()),
		       ofClass(
			       cxxRecordDecl(
					     matchesName(className),
					     unless(isTemplateInstantiation())
					     ).bind("classWithConstructor")
			       )
		       ).bind("foundConstructor");
  return matcher;
}

DeclarationMatcher explicitSpecifiedConstructor_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxConstructorDecl(
		       unless(isImplicit()),
		       ofClass(
			       cxxRecordDecl(
					     matchesName(className),
					     unless(isTemplateInstantiation())).
			       bind("classWithExplicitSpecifiedConstructor")
			       )
		       ).bind("explicitSpecifiedConstructor");
  return matcher;
}

DeclarationMatcher takeException_Matcher(string exceptionClass)
{
  DeclarationMatcher matcher =
    functionDecl
    (
     unless
     (
      isImplicitFunction()),
     hasDescendant
     (
      cxxThrowExpr
      (
       forEachDescendant
       (
	cxxConstructExpr
	(
	 hasDeclaration
	 (
	  cxxMethodDecl
	  (
	   ofClass
	   (
	    cxxRecordDecl
	    (
	     hasName(exceptionClass)).bind("exceptionClass")
	    )
	   )
	  )
	 )
	)
       ).bind("exception")
      )
     );
return matcher;
}

/*
**
** VARIABLES
**
*/

DeclarationMatcher member_Matcher(string className, string memberName)
{
  DeclarationMatcher matcher =
    cxxRecordDecl(
		  has(fieldDecl(matchesName(memberName)).bind("foundMember")),
		  matchesName(className),
		  unless(isTemplateInstantiation())
		  ).bind("foundClass");
  return matcher;
}

DeclarationMatcher staticVariable_Matcher(string className, string variableName)
{  
  DeclarationMatcher matcher =
    cxxRecordDecl(
		  has(varDecl(matchesName(variableName))
		      .bind("foundStaticVariable")),
		  matchesName(className),
		  unless(isTemplateInstantiation())
		  ).bind("foundClass");
  return matcher;
}

DeclarationMatcher variableNew_Matcher()
{
  DeclarationMatcher matcher =
    functionDecl(
		 unless(isImplicitFunction()),
		 forEachDescendant(varDecl(has(cxxNewExpr()))
				   .bind("variable_new"))
		 );
  return matcher;
}

DeclarationMatcher variableDelete_Matcher()
{
  DeclarationMatcher matcher =
    functionDecl(
		 unless(isImplicitFunction()),
		 forEachDescendant(cxxDeleteExpr(hasDescendant(declRefExpr(
		    to(varDecl().bind("variable_delete"))))))
	   	);
	return matcher;
}

DeclarationMatcher allPrivateMember_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxRecordDecl(
		  has(fieldDecl(isPublic())),
		  matchesName(className),
		  unless(isTemplateInstantiation())
		  ).bind("classWithAllPrivateMember");
  return matcher;
}

DeclarationMatcher memberVariableAccessLevel_Matcher(string className,
						     string memberName)
{
  DeclarationMatcher matcher =
    cxxRecordDecl(
		  forEachDescendant(
				    fieldDecl(matchesName(memberName))
				    .bind("foundMemberVariableAccessLevel")),
		  matchesName(className),
		  unless(isTemplateInstantiation())
		  ).bind("foundClassAccessLevel");
  return matcher;
}


/*
**
** FRIEND MEMBERS
**
*/

DeclarationMatcher notFriendMember_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxRecordDecl(
		  matchesName(className),
		  hasDescendant(
				friendDecl()
				),
		  unless(isTemplateInstantiation())
		  ).bind("classWithFriendMember");
  return matcher;
}

DeclarationMatcher friendFunction_Matcher(string functionName, string className)
{
  DeclarationMatcher matcher =
    cxxRecordDecl(
		  hasDescendant(
				friendDecl(
					   has(
					       functionDecl(
						matchesName(functionName)
						    ).bind("friendFunction")
					       )
					   )
				),
		  matchesName(className),
		  unless(isTemplateInstantiation())
		  ).bind("classWithFriendFunction");
  
  return matcher;
}


DeclarationMatcher friendClass_Matcher(string className,
				       string friendClassName)
{
  DeclarationMatcher matcher =
    cxxRecordDecl(
		  hasDescendant(
				friendDecl(
					   
					   ).bind("friendClass")
				),
		  matchesName(className),
		  unless(isTemplateInstantiation())
		  ).bind("classWithFriendClass");
  
  return matcher;
}

/*
**
** METHODS
**
*/

DeclarationMatcher method_Matcher(string methodName, string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  unless(isImplicitMethod()),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).bind("classWithMethod")
			  )
		  ).bind("methodWithName");
  return matcher;
}

DeclarationMatcher methodWithReferencedVariable_Matcher(string methodName,
							string className,
							string usedVariable)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  forEachDescendant(
				    memberExpr(
					       hasDeclaration(
	       fieldDecl(matchesName(usedVariable)).bind("referencedVariable")
							      )
					       )
				    ),
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).bind("classWithMethodVariable")
			  )
		  ).bind("methodWithReferencedVariable");
  return matcher;
}

DeclarationMatcher functionWithReferencedMethod_Matcher(string mainFunctionName,
							string usedMethodName,
							string usedClassName)
{
  DeclarationMatcher matcher =
    functionDecl
    (
     matchesName(mainFunctionName),
     anyOf
     (
      hasDescendant
      (
       memberExpr
       (
	hasDeclaration
	(
	 cxxMethodDecl
	 (
	  anyOf
	  (
	   matchesName(usedMethodName),
	   hasName(usedMethodName)
	   ),
	  ofClass(
		  cxxRecordDecl(
				matchesName(usedClassName),
				unless(isTemplateInstantiation())
				).bind("classOfReferencedMethodByFunction")
		  )
	  ).bind("usedMethodByFunction")
	 )
	)
       ),
      hasDescendant
      (
       cxxOperatorCallExpr
       (
	hasDeclaration(
		       cxxMethodDecl(
				     anyOf(
					   matchesName(usedMethodName),
					   hasName(usedMethodName)
					   ),
				     ofClass
				     (
				      cxxRecordDecl
				      (
				       matchesName(usedClassName),
				       unless(isTemplateInstantiation())
				       )
				      .bind("classOfReferencedMethodByFunction")
				      )
				     ).bind("usedMethodByFunction")
		       )
	)
       )
      )
     ).bind("mainFunctionWithReferencedMethod");
  return matcher;
}

DeclarationMatcher methodWithReferencedMethod_Matcher(string mainMethodName,
						      string mainClassName,
						      string usedMethodName,
						      string usedClassName)
{

  // llvm::outs()<< "Matcher: " << mainMethodName << " - "
  // << usedMethodName << "\n";

  DeclarationMatcher matcher =
    cxxMethodDecl
    (
     unless(isImplicitFunction()),
     anyOf(
	   forEachDescendant
	   (
	    memberExpr
	    (
	     hasDeclaration
	     (
	      cxxMethodDecl
	      (
	       anyOf
	       (
		matchesName(usedMethodName),
		hasName(usedMethodName)
		),
	       ofClass
	       (
		cxxRecordDecl
		(
		 matchesName(usedClassName),
		 unless(isTemplateInstantiation())
		 ).bind("classOfReferencedMethod")
		)
	       ).bind("usedMethod")
	      )
	     )
	    ),
	   forEachDescendant
	   (
	    cxxOperatorCallExpr
	    (
	     hasDeclaration
	     (
	      cxxMethodDecl
	      (
	       anyOf
	       (
		matchesName(usedMethodName),
		hasName(usedMethodName)
		),
	       ofClass(
		       cxxRecordDecl(
				     matchesName(usedClassName),
				     unless(isTemplateInstantiation())
				     ).bind("classOfReferencedMethod")
		       )
	       ).bind("usedMethod")
	      )
	     )
	    )
	   ),
     matchesName(mainMethodName),
     ofClass(
	     cxxRecordDecl(
			   matchesName(mainClassName),
			   unless(isTemplateInstantiation())
			   ).bind("classWithReferencedMethod")
	     )
     ).bind("mainMethod");
  return matcher;
}

DeclarationMatcher noExceptMethod_Matcher(string methodName, string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  unless(isImplicitMethod()),
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).bind("classWithNoExceptMethod")
			  )
		  ).bind("noExceptMethod");
  return matcher;
}

DeclarationMatcher inlineMethod_Matcher(string methodName, string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  unless(isImplicitMethod()),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).bind("classWithInlineMethod")
			  )
		  ).bind("inlineMethod");
  return matcher;
}


DeclarationMatcher defaultArgumentsInMethod_Matcher(string methodName,
						    string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  unless(isImplicitMethod()),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).
			  bind("classWithDefaultArgumentsInMethod")
			  )
		  ).bind("defaultArgumentsInMethod");
  return matcher;
}

DeclarationMatcher deletedMethod_Matcher(string methodName, string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  isDeleted(),
		  unless(isImplicitMethod()),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).bind("classWithDeletedMethod")
			  )
		  ).bind("deletedMethod");
  return matcher;
}

DeclarationMatcher defaultedMethod_Matcher(string methodName, string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  isDefaulted(),
		  unless(isImplicitMethod()),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).bind("classWithDefaultedMethod")
			  )
		  ).bind("defaultedMethod");
  return matcher;
}

DeclarationMatcher virtualMethod_Matcher(string methodName, string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  anyOf(
			matchesName(methodName),
			hasName(methodName)
			),
		  isVirtual(),
		  unless(isImplicitMethod()),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).bind("classWithVirtualMethod")
			  )
		  ).bind("virtualMethod");
  return matcher;
}

/*
**
** OPERATORS
**
*/

DeclarationMatcher copyAssignmentOperator_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  isCopyAssignmentOperator(),
		  unless(isDefaulted()),
		  unless(isImplicit()),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					)
			  .bind("classWithCopyAssignmentOperator")
			  )
		  ).bind("copyAssignmentOperator");
  return matcher;
}

DeclarationMatcher moveAssignmentOperator_Matcher(string className)
{
  DeclarationMatcher matcher =
    cxxMethodDecl(
		  isMoveAssignmentOperator(),
		  unless(isDefaulted()),
		  unless(isImplicit()),
		  ofClass(
			  cxxRecordDecl(
					matchesName(className),
					unless(isTemplateInstantiation())
					).
			  bind("classWithMoveAssignmentOperator")
			  )
		  ).bind("moveAssignmentOperator");
  return matcher;
}

DeclarationMatcher functionWithReferencedFuntion_Matcher
(string mainFunctionName, string usedFunctionName)
{
  DeclarationMatcher matcher =
    functionDecl(
		 matchesName(mainFunctionName),
		 hasDescendant
		 (
		  declRefExpr
		  (
		   to
		   (
		    functionDecl
		    (matchesName(usedFunctionName)).bind("usedFunction")
		    )
		   )
		  ),
		 unless(isImplicitFunction())
		 ).bind("mainFunction");
  return matcher;
}

DeclarationMatcher methodWithReferencedFuntion_Matcher(string mainMethodName,
						       string mainClassName,
						       string usedFunctionName)
{
  DeclarationMatcher matcher =
    cxxMethodDecl
    (
     unless(isImplicitFunction()),
     hasDescendant
     (
      declRefExpr
      (
       to
       (
	functionDecl(matchesName(usedFunctionName))
	.bind("usedFunctionForMainMethod")
	)
       )
      ),
     matchesName(mainMethodName),
     ofClass(
	     cxxRecordDecl(
			   matchesName(mainClassName),
			   unless(isTemplateInstantiation())
			   ).bind("mainClassWithReferencedFunction")
	     )
     ).bind("mainMethodWithReferencedFunction");
  return matcher;
}

DeclarationMatcher functionName_Matcher(string functionName)
{
  DeclarationMatcher matcher =
    functionDecl(
		 matchesName(functionName),
		 unless(isImplicitFunction())
		 ).bind("functionWithName");
  return matcher;
}

/*
**
** HEADERS
**
*/

DeclarationMatcher invocationsFromHeader_Matcher(string nameFunction)
{
  DeclarationMatcher matcher =
    functionDecl
    (
     unless(isImplicitFunction()),
     forEachDescendant
     (
      declRefExpr
      (
       to
       (
	functionDecl
	(
	 hasName(nameFunction)
	 ).bind("functionCalled")
	)
       ).bind("refFunction")
      )
     );
  return matcher;
}
