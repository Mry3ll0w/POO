/* -*-c++-*-
 * Cabecera para el DSL de las comprobaciones estáticas de código fuente
 * en las prácticas de POO.
 * ©2021 Los profesores de POO
*/
#ifndef CHECKCODE_H_
#define CHECKCODE_H_

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

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

#include "execute.h"

using namespace std;

class checkCode : public MatchFinder::MatchCallback {
public:
  checkCode(int argc, const char **argv, string fileClass = "",
	    string help = "Modo de empleo: ./main (*).cpp -- -std=c++11");

/****************************************************************************
**
** PUBLIC FUNCTIONS
**
****************************************************************************/

/*
- Method: void setCorrectMessage(string message)

- Utility: Method for setting the message that will be shown at the end of the check when all the checks have passed.

- Parameters:
---string message: string with the message to be shown.
*/
  void setCorrectMessage(string message);

/*
- Method: void setIncorrectMessage(string message)

- Utility: Method for setting the message that will be shown at the end of the check when at least one check has failed.

- Parameters:
---string message: string with the message to be shown.
*/
  void setIncorrectMessage(string message);

/*
- Method: void check()

- Utility: Method that has to be called after indicating a set of checks to execute them.
*/
  void check();


/****************************************************************************
**
** COMMON PARAMETERS
** Parameters that are shared for all or several of the available methods.
**
****************************************************************************/
/*
---string message: Optionally, you can include a parameter with the message
                   to be shown when the check fails. If this parameter is
                   not included, a default message will be shown.

---bool exist: By default, a check validates the existence of an element
               in the code. With this parameter, this behavior can be inverted
       	       to validate that an element does not exist in the code.
               By default, the parameter is set to "true".

---string constant: This parameter can be usedTo indicate whether a method is
              constant (in this case, "const") or not (in this case, "noconst");

*/

/****************************************************************************
**
** COMMON CONSIDERATIONS
**
****************************************************************************/
/*
- A particular method is identified by:
  1) the class to which it belongs.
  2) its name.
  3) a list of types of its parameters (and no by its names).
  4) whether it is constant or not.

- If the method is an overloaded operator, the name will be the word "operator"
  followed by the operator without leaving any spaces in between. 
  For example "operator+=".

- Regarding the types, the original type has to be indicated, that is, without
  taking into account typedef or alias. For example:

     typedef unsigned long myType;

     int method (myType parameter);

  The type of "parameter" is "unsigned long" and no "myType".

- In some parameters of some of these checks, it is allowed to introduce "?"
  (interrogation mark) to indicate that the parameter does not have to be taken
  into account. This is mainly useful when that information is not known.

  For example, if "{"?"}" is set as the list of parameters of a method,
  the check will not adhere to a particular method, but it will try to match
  all the methods with the same name in the indicated class 
  (regardless of their parameters).

  In the descriptions of the checks in this file, this property 
  is indicated with (?).

  Note: In the case of setting "?" as argument of a parameter 
  to indicate the list of parameters of a method, the check will not take 
  into account the parameter list. We have to distinguish between this case
  and the situation of a method without parameters; that case is indicated 
  with an empty list {}.

- In some parameters of some of these checks, it is allowed to use a
  regular exprression. This is mainly useful when the name of the element
  to be searched is not fixed.

  For expalme, if "A.*" is set as the name of a class, the check will apply 
  to all the classes whose name starts with "A".

  In the descriptions of the checks in this file, this property is indicated 
  with (*).

*/
/****************************************************************************
**
** CLASSES
** Checks about classes.
**
****************************************************************************/
/*
- Method: bool findClass(vector<string> className)

- Utility: Method to check the existence of a class.
           Return "true" if it was found, otherwise it will return "false".
           The check is executed individally when is invoked, so that it can be
           used as first condition before applying other checks on the
           same class.

- Parameters:
---vector<string> className (*): vector of strings with the name of the 
   classes to be searched.

- Example:
	if (findClass({"A"})){
		check1();
		check2();
		...
	}
	else{
		cout << "Class not found."<<endl;
	}
*/
  bool findClass(vector<string> className);

/*
- Method: void classWithName(string className, string message)

- Utility: Method to check the existence of a class. 
  Unlike the check "findClass", this check is executed when the method 
  "check" is invoked.

- Parameters:
---string className (*): string with the name of the class to be searched.

- Example:

  class A { ... };

  classWithName(A);    Pass
  classWithName(B);    Fail
*/
  void classWithName(string className, string message = "CLASS NOT FOUND.");


/*******************************************************************************
**
** CONSTRUCTORS
** Checks about constructors in a class.
**
*******************************************************************************/

/*
- Method: void defaultConstructor(string className, bool exist, string message)

- Utility: Method to verify that a class has a default constructor defined.

- Parameters:
---string className (*): string with the name of the class to be searched.

- Example:

  class A { A() { ... } };
  class B { B() = default; };
  class C { C(Type)  { ... } };

  defaultConstructor("A");      Pass
  defaultConstructor("B");      Pass
  defaultConstructor("C",false) Pass
  defaultConstructor("C");      Fail

*/
  void defaultConstructor(string className, bool exist = true,
			  string message = "DEFAULT CONSTRUCTOR NOT FOUND.");

/*
- Method: void listInitializerConstructor(string className, 
         vector<string> parameters, vector<string> initializers, string message)

- Utility: Method to verify that a class has a constructor that makes use 
           of an initializer list.

- Parameters:
---string className (*): string with the name of the class to be searched.
---vector<string> parameters (?): vector of strings with the types 
                                  of the parameters of the constructor.
---vector<string> initializers (?): vector of strings with the types 
   of the attributes that are initialized in the initializer list 
   of the constructor.

- Example:

  class A {
  	int x;
  	A() { x = 0; }
  };
  class B {
  	int x;
  	B() : x(0) { ... }
  };

  listInitializerConstructor("A", {"?"}, {"int"});    Fail
  listInitializerConstructor("B", {"?"}, {"int"});    Pass

*/
  void listInitializerConstructor(string className, vector<string> parameters,
				  vector<string> initializers,
				  string message = "CLASS WITH THE SPECIFIED"
				  " CONSTRUCTOR AND INITIALIZATION LIST "
				  "NOT FOUND.");

/*
- Method: void copyConstructor(string className, bool exist, string message)

- Utility: Method to verify that a class has a copy constructor defined.

- Parameters:
---string className (*): string with the name of the class to be searched.

- Example:

  class A { ...
  	A(const A&) { ... }
  ... };
  class B { ...
  	B(const B&) = default;
  ... };

  class C { ...
  	C(const C&) = delete;
  ... };

  copyConstructor("A"); 	Pass
  copyConstructor("B"); 	Pass
  copyConstructor("C"); 	Fail

*/
  void copyConstructor(string className, bool exist = true,
		       string message = "COPY CONSTRUCTOR NOT FOUND.");

/*
- Method: void moveConstructor(string className, bool exist, string message)

- Utility: Method to verify that a class has a move constructor defined.

- Parameters:
---string className (*): string with the name of the class to be searched.

- Example:

  class A { ...
  	A(const A&&) { ... }
  ... };
  class B { ...
  	B(const B&&) = default;
  ... };

  class C { ...
  	C(const C&&) = delete;
  ... };


  moveConstructor("A"); Pass
  moveConstructor("B"); Pass
  moveConstructor("C"); Fail
*/
  void moveConstructor(string className, bool exist = true,
		       string message = "MOVE CONSTRUCTOR NOT FOUND.");

/*
- Method: void destructor(string className, bool exist, string message)

- Utility: Method to verify that a class has a destructor defined.

- Parameters:
---string className (*): string with the name of the class to be searched.

- Example:

  class A { ...
  	~A() { ... }
  ... };
  class B { ...
  	~B() = default;
  ... };
  class C { ...
   	...
  ... };

  destructor("A");  Pass
  destructor("B");  Pass
  destructor("C");  Fail
*/
  void destructor(string className, bool exist = true,
		  string message = "DESTRUCTOR NOT FOUND.");

/*
- Method: void destructorDeleteMember(string className, 
                                  vector<string> memberNames, string message)

- Utility: Method to verify that a member in the destructor is deleted.

- Parameters:
---string className (*): string with the name of the class to be searched.
---vector<string> memberName (*): vector of strings with the names of the
                members to which the delete operator is applied.

- Example:

	class A{
		myType* a;
		A(): a{new myType()}{ ... }
		~A() {delete a;}
	};

	class B{
		myType* b;
		B(): b{new myType()} { ... }
		~B() {}
	};

	destructorDeleteMember("B", {"b"}); 	Fail
	destructorDeleteMember("A", {"a"}); 	Pass

*/
  void destructorDeleteMember(string className, vector<string> memberNames,
			      string message =
			      "MEMBER VARIABLE NOT DELETED IN DESTRUCTOR.");

/*
- Method: void numberOfConstructors(string className, unsigned int constructors,
                                    bool lenient, string message)

- Utility: Method to verify that a class has a number of constructors.

- Parameters:
---string className (*): string with the name of the class to be searched.
---unsigned int constructors: integer with the number of constructor 
   of the class.
---lenient: boolean indicating whether it is allowed a number of constructors 
   equal or greater (true) or only an equal number of constructors (false). 
   By default it is set to "false".

- Example:

	class A{
		A() { ... }
		A(const A&) { ... }
	};

	numberOfConstructors("A", 2, false);    Pass
	numberOfConstructors("A", 1, true);     Pass
	numberOfConstructors("A", 1, false);    Fail
*/
  void numberOfConstructors(string className, unsigned int constructors,
			    bool lenient = false, string message =
			    "INCORRECT NUMBER OF CONSTRUCTORS.");

/*
- Method: void methodWithDynamicCast(string methodName, 
            vector<string> parameters, string className, string constant, 
            unsigned int numberdc, bool lenient, string message)

- Utility: Method to verify that a method uses a dynamic cast with an 
           origin and destination types.

- Parameters:
---string methodName (*): string with the name of the method 
   that should use the dynamic cast.
---vector<string> parameters: vector of strings with the parameters 
   of the method to be searched.
---string constant: string indicating whether the method is constant or not.
---string className: string with the name of the class of the method.
---string originType: string indicating the origin type of the dynamic cast.
---string dstType: string indicating the destination type of the dynamic cast.

- Example:

	class A{
		void method(myType2 *t2, myType3 *t3);
	};

	void A::method(myType2 *t2, myType3 *t3){
		myType1 *t1 = dynamic_cast<myType1*>(t2);
		myType1 *t1 = dynamic_cast<myType1*>(t3);
	}

	methodWithDynamicCast("method",{"class myType2 *","class myType3 *"},
        "A","noconst","class myType2 *", "class myType1 *");	Pass
	methodWithDynamicCast("method",{"class myType2 *","class myType3 *"},
        "A","noconst","class myType3 *", "class myType1 *");	Pass
	methodWithDynamicCast("method",{"class myType2 *","class myType3 *"},
        "A","noconst","class myType1 *", "class myType1 *");	Fail
	methodWithDynamicCast("method",{"class myType2 *","class myType3 *"},
        "A","noconst","class myType3 *", "class myType2 *");	Fail

*/
  void methodWithDynamicCast(string methodName, vector<string> parameters,
			     string className, string constant,
			     string originType, string dstType,
			     string message =
			     "INCORRECT NUMBER OF DYNAMIC_CAST");

/*
- Method: void explicitSpecifiedConstructor(string className, 
            vector<string> parameters, string message);

- Utility: Method to verify that a constructor is marked as "explicit".

- Parameters:
---string className (*): string with the name of the class to be searched.
---vector<string> parameters (?): vector of strings with the types 
     of the parameters of the constructor.

- Example:

	class A{
		A(myType1 a) { ... }
		explicit A(myType2 a) { ... }
	};

	explicitSpecifiedConstructor("A", {"myType1"}); Fail
	explicitSpecifiedConstructor("A", {"myType2"}); Pass

*/
  void explicitSpecifiedConstructor(string className, vector<string> parameters,
				    string message =
				    "EXPLICIT CONSTRUCTOR NOT FOUND.");

/****************************************************************************
**
** EXCEPTIONS
** Checks about exceptions.
**
****************************************************************************/

/*
- Method: void takeException(vector<string> exception, string message);

- Utility: Method to verify if an exceptions is thrown.

- Parameters:
---vector<string> className: vector of strings with the name of the exceptions.

- Example:

	class A{
		void method1() { ... }
	}

	void A::method2() {
		...
		throw Exception1(...);
	}

	takeException({"Exception1"});	Pass
	takeException({"Exception2"});	Fail

*/
  void takeException(vector<string> exceptionClasses, string message
		     = "EXCEPTION NOT FOUND");

/****************************************************************************
**
** VARIABLES
** Checks about members of a class.
**
****************************************************************************/

/*
- Method: void memberVariable(string className, vector<string> memberNames, 
            vector<string> constant, string message)

- Utility: Method to verify if a class has an attribute.

Parameters:
---string className (*): string with the name of the class to be searched.
---vector<string> memberName (*): vector of strings with the names 
                  of the attributes to be searched.
---vector<string> constant (?): vector of strings indicating 
                  whether the attributes are constant or not.

- Example:

	class A{
		Type a
		const Type b;
	};

	memberVariable("A", {"a", "b"}, {"noconst", "const"}); 	Pass
	memberVariable("A", {"a", "b"}, {"?", "?"});		Pass
	memberVariable("A", {"c"}, {"?"}); 			Fail
	memberVariable("A", {"a"}, {"const"});			Fail

*/
  void memberVariable(string className, vector<string> memberNames,
		      vector<string> constant, vector<bool> exist,
		      string message = "MEMBER VARIABLE NOT FOUND.");

/*
- Method: void staticVariable(string className, vector<string> variableNames, 
            string message)

- Utility: Method to verify the existence of a static variable in a class.

- Parameters:
---string className (*): string with the name of the class to be searched.
---vector<string> variableNames (*): vector of strings with the names of the 
      static variables to be searched.
---vector<string> constant (?): vector of strings indicating whether 
      the variables are constant or not.
- Example:

	class A{
		static const Type a
		static Type b;
		const Type c;
	};

	staticVariable("A", {"a", "b"}, {"const", "noconst"});      Pass
	staticVariable("A", {"a", "b"}, {"const", "const"});        Fail
	staticVariable("A", {"a", "b"}, {"noconst", "noconst"});    Fail
	staticVariable("A", {"c"}, {"const"});                      Fail
	staticVariable("A", {"a", "c"}, {"const", "const"});        Fail
*/
  void staticVariable(string className, vector<string> variableNames,
		      vector<string> constant,
		      string message = "STATIC CONST VARIABLE NOT FOUND.");

/*
- Method: void releaseVariable(string message)

- Utility: Method to verify that all the variables created with "new", 
           are later deleted with "delete".

- Example:

	{
		Type* a = new Type();
		...
		delete a;
	}

    Pass

	{
		Type* a = new Type();
		...
	}

    Fail

*/
  void releaseVariable(string message = "NOT ALL VARIABLES RELEASED.");

/*
- Method: void allPrivateVariableMember(string className, string message)

- Utility: Method to verify that all variable members in a class are private.

- Parameters:
---string className (*): string with the name of the class to be searched.

- Example:
	class A{
	public:
		Type1 a;
		Type2 b;
	private:
		Type3 c;
	};

	class B{
	private:
		Type1 a;
		Type2 b;
		Type3 c;
	};

	allPrivateVariableMember("A"); Fail
	allPrivateVariableMember("B"); Pass
*/
  void allPrivateVariableMember(string className,
				string message = "PUBLIC MEMBER FOUND.");

/*
- Method: void memberVariableAccessLevel(string className, 
            vector<string> memberNames, string level, string message)

- Utility: Method to verify that a class has an attribute with a 
           specific access level.

Parameters:
---string className (*): string with the name of the class to be searched.
---vector<string> memberName (*): vector of strings with the names
      of attributes to be searched.
---string level: string with the access level (public, protected, private).

- Example

	class A{
	public:
		Type1 a1;
		Type2 a2;
	private:
		Type3 b;
	};

	class B{
	private:
		Type1 a1;
		Type2 a2;
		Type3 a3;
	};

	memberVariableAccessLevel("A", {"a1", "a2", "b"}, "public");    Fail
	memberVariableAccessLevel("A", {"a.*"}, "public");              Pass
	memberVariableAccessLevel("A", {"b"}, "private");               Pass
	memberVariableAccessLevel("A", {".*"}, "private");              Pass
	memberVariableAccessLevel("B", {".*"}, "private");              Pass

*/
  void memberVariableAccessLevel(string className, vector<string> memberNames,
				 string level, string message =
				 "MEMBER VARIABLE WITH THAT ACCESS LEVEL"
				 " NOT FOUND.");

/*****************************************************************************
**
** METHODS
** Checks about methods of a class.
**
*****************************************************************************/

/*
- Method: void method(vector<string> methodNames, 
            vector<vector<string>> parameters, string className, 
            vector<string> constant,string message)

- Utility: Method to verify the existence of a method.

- Parameters:
---vector<string> methodNames (*): vector of strings with the names 
      of the methods to be searched.
---vector<vector<string> > parameters (?): vector of vector of strings 
      with the types of the method parameters to be searched.
---string className (*): string with the name of the class where the methods
      have to be searched.
---vector<string> constant (?): vector of strings indicating whether 
      the methods are constant or not.

- Example:

	class A{
		void method1(Type1, Type2) { ... }
		void method2() { ... }
	};

	method({"method1", "method2"}, {{"Type1", "Type2"}, {}}, "A", {"?", "?"}); Pass
	method({"method3"}, {{"?"}}, "A");                                         Fail

*/
  void method(vector<string> methodNames, vector<vector<string>> parameters,
	      string className, vector<string> constant = {"?"},
	      string message="METHOD NOT FOUND.");

/*
- Method: void methodWithReferencedMemberVariable(vector<string> methodNames,
            vector<vector<string> > parameters, string className, 
            vector<string> constant, string usedVariable, string message)

- Utility: Method to verify that a method references a member variable.

- Parameters:
---vector<string> methodNames (*): vector of strings with the names 
         of the methods to be searched.
---vector<vector<string> > parameters (?): vector of vector of strings 
         with the types of the parameters of the methods to be searched.
---string className (*): string with the name of the class where the 
         methods have to be searched.
---vector<string> constant (?): vector of strings indicating whether 
         the methods are constant or not.
---vector<string> usedVariables: vector of strings with the names of 
         the attributes that are referenced by the methods.

- Example:

	class A{
		int a;
		void method1() {
			...
			a = 3;
			...
		}
		void method2(){
			...
			// 'a' not used
		}
	};

	methodWithReferencedMemberVariable({"method1"}, {{"?"}}, "A", {"?"},
          {"a"}); Pass
	methodWithReferencedMemberVariable({"method2"}, {{"?"}}, "A", {"?"}, 
          {"a"}); Fail

*/
  void methodWithReferencedMemberVariable(vector<string> methodNames,
					  vector<vector<string> > parameters,
					  string className,
					  vector<string> constant,
					  vector<string> usedVariables,
					  string message =
					  "METHOD WITH REFERENCED MEMBER "
					  "VARIABLE NOT FOUND.");

/*
- Method: void methodWithReferencedMethod(tor<string> mainMethodNames, 
            vector<vector<string> > mainMethodparameters, string mainClassName,
            vector<string> mainConstant, vector<string> usedMethodName, 
            vector<vector<string> > usedMethodparameters, string usedClassName,
            vector<string> usedConstant, string message);

- Utility: Method to verify that a method references another method.

- Parameters:
---vector<string> mainMethodNames (*): vector of strings with the names 
    of the main methods to be searched.
---vector<vector<string> > mainMethodparameters (?): vector of vector of strings
     with the types of the parameters of the main methods.
---string mainClassName (*): string with the name of the class where the main 
     methods have to be searched.
---vector<string> mainConstant (?): vector of strings indicating whether the 
     main methods are constant or not.
---vector<string> usedMethodNames (*): vector of strings with the name of 
     the methods to be searched that are referenced by the main methods.
---vector<vector<string> > usedMethodparameters (?): vector of vector of 
     strings with the types of the parameters of the referenced methods.
---string usedClassName (*): string with the name of the class where the 
     referenced methods have to be searched.
---vector<string> usedConstant (?): vector of strings indicating whether 
     the referenced methods are constant or not.

- Example:

	class A{
		void method3() { ... }
		void method1(){
			...
			method3();
			...
		}
		void method2(){
			...
			// 'method3' not used
		}
	};

	methodWithReferencedMethod({"method1"}, {{"?"}}, "A", {"?"}, 
              {"method3"}, {{"?"}}, "A", {"?"}); Pass
	methodWithReferencedMethod({"method2"}, {{"?"}}, "A", {"?"}, 
              {"method3"}, {{"?"}}, "A", {"?"}); Fail

*/
  void methodWithReferencedMethod(vector<string> mainMethodNames,
				  vector<vector<string>> mainMethodparameters,
				  string mainClassName,
				  vector<string> mainConstant,
				  vector<string> usedMethodName,
				  vector<vector<string>> usedMethodparameters,
				  string usedClassName,
				  vector<string> usedConstant,
				  string message =
				  "METHOD WITH REFERENCED METHOD NOT FOUND.");

/*
- Method:  void noExceptMethod(vector<string> methodNames, 
             vector<vector<string> > parameters, string className, 
             vector<string> constant, string message)

- Utility: Method to verify that a method is marked as "noexcept"

- Parameters:
---vector<string> methodNames (*): vector of strings with the names 
     of the methods to be searched.
---vector<string> parameters (?): vector of vector of strings with the 
     types of the parameters of the methods to be searched.
---string className (*): string with the name of the class where the 
     methods have to be searched.
---vector<string> constant (?): vector of strings indicating whether the 
     methods are constant or not.

- Example:

	class A{
		void method1() { ... }
		void method2() noexcept { ... }
	};

	noExceptMethod({"method1"}, {{"?"}}, "A", {"?"}); Fail
	noExceptMethod({"method2"}, {{"?"}}, "A", {"?"}); Pass

*/
  void noExceptMethod(vector<string> methodNames,
		      vector<vector<string>> parameters,
		      string className, vector<string> constant = {"?"},
		      string message = "noexcept METHOD NOT FOUND.");

/*
- Method:  void inlineMethod(vector<string> methodNames, 
             vector<vector<string> > parameters, string className, 
             vector<string> constant, string message)

- Utility: Method to verify that a method is marked as "inline"

- Parameters:
---vector<string> methodNames (*): vector of strings with the name 
         of the methods to be searched.
---vector<string> parameters (?): vector of vector of strings with 
         the types of the parameters of the methods to be searched.
---string className (*): string with the name of the class where
         the methods have to be searched.
---vector<string> constant (?): vector of strings indicating whether 
         the methods are constant or not.

- Example:

	class A{
		void method1(){...}
		void method2();
		void method3();
	};

	void A::method2(){...}
	inline void A::method3(){...}

	inlineMethod({"method1"}, {{"?"}}, "A", {"?"});               Pass
	inlineMethod({"method1", method2"}, {{"?"}, {"?"}}, "A", {"?","?"});Pass
	inlineMethod({"method3"}, {{"?"}}, "A", {"?"});               Fail
	inlineMethod({"method2", method3"}, {{"?"}, {"?"}}, "A", {"?","?"});Fail

*/
  void inlineMethod(vector<string> methodNames,
		    vector<vector<string>> parameters, string className,
		    vector<string> constant = {"?"},
		    string message = "INLINE METHODS NOT FOUND.");

/*
- Method:  void defaultArgumentsInMethod(vector<string> methodNames, 
             vector<vector<string> > parameters, string className, 
             vector<string> constant, vector<unsigned int> defaultArgs, 
             string message)

- Utility: Method to verify that a method of a class has a number 
           of default arguments.

- Parameters:
---vector<string> methodNames (*): vector of strings with the names 
      of the methods to be searched.
---vector<vector<string> > parameters (?): vector of vector of strings 
      with the types of the parameters of the methods to be searched.
---string className (*): string with the name of the class where the
       methods have to be searched.
---vector<string> constant (?): vector of strings indicating whether 
       the methods are constant or not.
---vector<unsigned int> numDefaultArgs: vector of integers indicating 
       the number of default arguments that the methods should have.
---vector<vector<string> > defaultArgs: vector of vector of strings indicating
       the default arguments.

- Example:

	class A{
		void method1(Type1 a=0) { ... }
		void method2(Type1, Type2=0) { ... }
	};

	defaultArgumentsInMethod({"method1"}, {{"Type1"}}, "A", {"?"}, {1});Pass
	defaultArgumentsInMethod({"method2"}, {{"Type1", "Type2"}}, "A", {"?"},
	                          {2});          Fail
	defaultArgumentsInMethod({"method2"}, {{"Type1", "Type2"}}, "A", {"?"},
                                  {1}, {"0"});   Pass
	defaultArgumentsInMethod({"method2"}, {{"Type1", "Type2"}}, "A", {"?"},
	                          {1}, {"?"});   Pass

*/
  void defaultArgumentsInMethod(vector<string> methodNames,
				vector<vector<string>> parameters,
				string className,
				vector<string> constant = {"?"},
				vector<unsigned int> numDefaultArgs = {0},
				vector<vector<string>> defaultArgs={{"?"}},
				string message =
				"DEFAULT ARGUMENTS IN METHODS NOT FOUND.");

/*
- Method:  void deletedMethod(vector<string> methodNames, 
             vector<vector<string>> parameters, string className, 
             vector<string> constant, string message);

- Utility: Method to verify that a method of a class is marked as "= delete"

- Parameters:
---vector<string> methodNames (*): vector of strings with the names 
        of the methods to be searched.
---vector<string> parameters (?): vector of vector of strings with the types
        of the parameters of the methods to be searched.
---string className (*): string with the name of the class where the methods 
        have to be searched.
---vector<string> constant (?): vector of strings indicating whether the
        methods are constant or not.

- Example:

	class A{
		A() { ... }
		A(const A &) = delete
	};

	deletedMethod({"A"}, {{"?"}}, "A", {"?"});                 Fail
	deletedMethod({"A"}, {{"const class A &"}}, "A", {"?"});   Pass

*/

  void deletedMethod(vector<string> methodNames,
		     vector<vector<string>> parameters,
		     string className, vector<string> constant = {"?"},
		     string message = "DELETED METHODS NOT FOUND.");

/*
- Method:  void defaultedMethod(vector<string> methodNames, 
             vector<vector<string>> parameters, string className, 
             vector<string> constant, string message);

- Utility: Method to verify that a method of a class is marked as "= default"

- Parameters:
---vector<string> methodNames (*): vector of strings with the names 
      of the methods to be searched.
---vector<string> parameters (?): vector of vector of strings with the types 
      of the parameters of the methods to be searched.
---string className (*): string with the name of the class where the 
      methods have to be searched.
---vector<string> constant (?): vector of strings indicating whether the
      methods are constant or not.

- Example:

	class A{
		A() { ... }
		A(const A &) = default
	};

	defaultedMethod({"A"}, {{"?"}}, "A", {"?"});                   Fail
	defaultedMethod({"A"}, {{"const class A &"}}, "A", {"?"});     Pass

*/
  void defaultedMethod(vector<string> methodNames,
		       vector<vector<string>> parameters,
		       string className, vector<string> constant = {"?"},
		       string message = "DEFAULTED METHODS NOT FOUND.");

/*
- Method:  void virtualMethod(vector<string> methodNames,
              vector<vector<string>> parameters, string className, 
              vector<string> constant, string message);

- Utility: Method to verify that a method of a class is virtual

- Parameters:
---vector<string> methodNames (*): vector of strings with the names 
     of the methods to be searched.
---vector<string> parameters (?): vector of vector of strings with the types 
     of the parameters of the methods to be searched.
---string className (*): string with the name of the class where the 
     methods have to be searched.
---vector<string> constant (?): vector of strings indicating whether the 
     methods are constant or not.

- Example:

	class A{
		A() { ... }
		virtual A(const A &)
	};

	virtualMethod({"A"}, {{"?"}}, "A", {"?"});                 Fail
	virtualMethod({"A"}, {{"const class A &"}}, "A", {"?"});   Pass

*/

  void virtualMethod(vector<string> methodNames,
		     vector<vector<string>> parameters, string className,
		     vector<string> constant = {"?"},
		     string message = "VIRTUAL METHODS NOT FOUND.");

/****************************************************************************
**
** OPERATORS
** Checks about class operators.
**
****************************************************************************/

/*
- Method: void copyAssignmentOperator(string className, bool exist, 
                 string message)

- Utility: Method to verify the existence of the copy assignment operator.

- Parameters:
---string className (*): string with the name of the class to be searched.
---bool exist: Boolean indicating the existence of the copy assignment operator.

-Example:

	class A{
		A& operator=(const A&) { ... }
	};

	class B{

	};

	copyAssignmentOperator("A", true);     Pass
	copyAssignmentOperator("A", false);    Fail

	copyAssignmentOperator("B", false);    Pass
	copyAssignmentOperator("B", true);     Fail

*/
  void copyAssignmentOperator(string className, bool exist,
			      string message =
			      "COPY ASSIGNMENT OPERATOR NOT FOUND.");

/*
- Method: void moveAssignmentOperator(string className, bool exist, 
                 string message)

- Utility: Method to verify the existence of the move assignment operator.

- Parameters:
---string className (*): string with the name of the class to be searched.
---bool exist: Boolean indicating the existence of the move assignment operator.

-Example:

	class A{
		A& operator=(const A&&) { ... }
	};

	class B{

	};

	moveAssignmentOperator("A", true);	Pass
	moveAssignmentOperator("A", false); 	Fail
	moveAssignmentOperator("B", false); 	Pass
	moveAssignmentOperator("B", true); 	Fail
*/
  void moveAssignmentOperator(string className, bool exist = true,
			      string message =
			      "MOVE ASSIGNMENT OPERATOR NOT FOUND.");

/****************************************************************************
**
** FUNCTIONS
** Checks about functions.
**
****************************************************************************/

/*
- Method:  void function(vector<string> functionNames, 
             vector<vector<string> > parameters, string message)

- Utility: Method to verify the existence of a function

- Parameters:
---vector<string> functionNames (*): vector of strings with the name 
     of the functions to be searched.
---vector<vector<string> > parameters (?): vector of vector of strings 
     with the types of the parameters of the functions to be searched.

- Example:

  {
     void function1(Type1 parameter){
     ...
     }
  }

  function({"function1"}, {{"Type1"}}, {"?"}); Pass
  function({"function1"}, {{"?"}}, {"?"});     Pass
  function({"function2"}, {{"?"}}, {"?"});Fail ('function2' does not exist)

*/
  void function(vector<string> functionNames,
		vector<vector<string>> parameters,
		string message = "FUNCTION NOT FOUND.");

/*
- Method: void methodWithReferencedFunction(vector<string> mainMethodNames, 
                 vector<vector<string>> mainMethodparameters, 
                 string mainClassName, vector<string> mainConstant, 
                 vector<string> usedFunctionNames, 
                 vector<vector<string>> usedFunctionParameters, string message)

- Utility: Method to verify that a method references a function.

- Parameters:
---vector<string> mainMethodNames (*): vector of strings with the names 
       of the main methods to be searched.
---vector<vector<string> > mainMethodparameters (?): vector of vector 
       of strings with the names of the types of the parameters with 
       the main methods to be searched.
---string mainClassName (*): string with the name of the class where 
       the main methods have to be searched.
---vector<string> mainConstant (?): vector of strings indicating whether 
       the main methods are constant or not.
---vector<string> usedFunctionNames (*): vector of strings with the names 
      of the functions to be searched that are referenced by the main functions.
---vector<vector<string> > usedFunctionParameters (?): vector of vector 
      strings with the types of the parameters of the referenced functions.

- Example:

	class A {
		void method1(){
			...
			function1();
			...
		}
	};

	void function1(){
		...
	}


	methodWithReferencedFunction({"method1"}, {{"?"}}, "A", {"?"}, 
            {"function1"}, {{"?"}}); Pass
	methodWithReferencedFunction({"method1"}, {{"?"}}, "A", {"?"}, 
            {"function2"}, {{"?"}}); Fail


*/
  void methodWithReferencedFunction(vector<string> mainMethodNames,
				    vector<vector<string>> mainMethodparameters,
				    string mainClassName,
				    vector<string> mainConstant,
				    vector<string> usedFunctionNames,
				    vector<vector<string>> usedFunctionParams,
				    string message =
				    "FUNCTION WITH REFERENCED FUNCTION"
				    " NOT FOUND.");
/*
- Method: void functionWithReferencedMethod(vector<string> mainFunctionNames, 
             vector<vector<string>> mainFunctionParameters, 
             vector<string> usedMethodNames, 
             vector<vector<string>> usedMethodparameters, 
	     string usedClassName, vector<string> usedConstant,  string message)

- Utility: Method to verify that a function is referenced by a method.

- Parameters:
---vector<string> mainFunctionNames (*): vector of strings with the names 
     of the main functions to be searched.
---vector<vector<string> > mainFunctionParameters (?): vector of vector 
     of strings with the types of the parameters 
     of the main functions to be searched.
---vector<string> usedMethodNames (*): vector of strings with the name 
     of the method to be searched that are referenced by the main method.
---vector<vector<string> > usedMethodparameters (?): vector of vector 
     of strings with the types of the parameters 
     of the referenced methods to be searched.
---string usedClassName (*): string with the name of the class where 
     the referenced methods have to be searched.
---vector<string> usedConstant (?): vector of strings indicating whether 
     the referenced methods are constant or not.

- Example:

	class A {
		void method1() {
			...
		}
	};

	void function1(){
		...
		method1()
		...
	}


	functionWithReferencedMethod({"function1"}, {{"?"}}, {"method1"}, 
             {{"?"}}, "A", {"?"}); Pass
	functionWithReferencedMethod({"function1"}, {{"?"}}, {"method2"}, 
             {{"?"}}, "A", {"?"}); Fail


*/
  void functionWithReferencedMethod(vector<string> mainFunctionNames,
				    vector<vector<string>> mainFunctionParams,
				    vector<string> usedMethodNames,
				    vector<vector<string>> usedMethodParams,
				    string usedClassName,
				    vector<string> usedConstant,
				    string message =
				    "FUNCTION WITH REFERENCED METHOD"
				    " NOT FOUND.");

/*
- Method: void functionWithReferencedFunction(vector<string> mainFunctionNames,
                 vector<vector<string>> mainFunctionParameters, 
                 vector<string> usedFunctionNames, 
                 vector<vector<string>> usedFunctionParameters, string message)

- Utility: Method to verify that a function is referenced by a function.

- Parameters:
---vector<string> mainFunctionNames (*): vector of strings with the names 
     of the main functions to be searched.
---vector<vector<string> > mainFunctionParameters (?): vector of vector 
     of strings with the types of the parameters 
     of the main functions to be searched.
---vector<string> usedFunctionNames (*): vector of strings with the names 
     of the functions to be searched that are referenced by the main functions.
---vector<vector<string> > usedFunctionParameters (?): vector of vector 
     of strings with the types of the parameters 
     of the referenced functions to be searched.

- Example:


		void function3() { ... }
		void function1(){
			...
			function3();
			...
		}
		void function2(){
			...
			// 'function3' not used
		}


	functionWithReferencedFunction({"function1"}, {{"?"}}, {"function3"}, 
	    {{"?"}}); Pass
	functionWithReferencedFunction({"function2"}, {{"?"}}, {"function3"}, 
	    {{"?"}}); Fail


*/
  void functionWithReferencedFunction(vector<string> mainFunctionNames,
				      vector<vector<string>> mainFunctionParams,
				      vector<string> usedFunctionNames,
				      vector<vector<string>> usedFunctionParams,
				      string message =
				      "FUNCTION WITH REFERENCED FUNCTION"
				      " NOT FOUND.");

/****************************************************************************
**
** HEADERS
** Checks about the correct inclusion of headers.
**
****************************************************************************/
/*
- Method:  void invocationsFromHeaders(vector<string> functionNames, 
                  string headerName, bool exist, string message);

- Utility: Method to verify whether the correct header has been included 
               when certain functions are referenced.

- Parameters:
---vector<string> functionNames: vector of strings with the name 
      of the functions to be searched.
---string headerName: string with the name of the header.
---bool exist: boolean indicating that the functions should be taken from 
      the header (true) or not (false).

- Example:

	header.h:
		void function1();
		void function2();
	code.cpp:
		#include "header.h"
		...
		function1();
		...
		function2();
		...
		function3();

	invocationsFromHeaders({"function1", "function2"}, "header.h",true);Pass
	invocationsFromHeaders({"function3"}, "header.h", false);  Pass
	invocationsFromHeaders({"function3"}, "header.h", true);   Fail
	invocationsFromHeaders({"function2", "function3"}, "header.h",true);Fail

*/
  void invocationsFromHeaders(vector<string> functionNames,
			      string headerName, bool exist = true,
			      string message =
			      "A PROBLEM WITH THE INCLUDED HEADERS WAS FOUND.");

/*
- Method:  void fileIncludedHeader(string headerName, vector<string> fileNames,
                   string message);

- Utility: Method to verify that a header has been included 
             in any of the indicated files.

- Parameters:
---string headerName: string with the name of the header to be searched.
---vector<string> fileNames: vector of strings with the name of the files 
      where the header has to be searched.

- Example:

	file1.cpp:
		#include "header1.h"
	file2.cpp:
		#include "header2.h"
	file3.cpp:
		#include "header1.h"

	fileIncludedHeader("header1.h", {"file1.cpp", "file3.cpp"}); Pass
	fileIncludedHeader("header2.h", {"file1.cpp"});              Fail
	fileIncludedHeader("header2.h", {"file1.cpp", "file3.cpp"}); Fail

*/
  void fileIncludedHeader(string headerName, vector<string> fileNames,
			  string message =
			  "HEADER IS NOT INCLUDED IN ANY OF THE FILES");

/*
- Method: void guardClauses(string fileName, string message)

- Utility: Method to verify that the guard clause is included.

- Parameters:
---string fileName: string with the name of the file where the guard clause 
       has to be searched.

- Example:

	code1.h:
	...

	code2.h:
	#ifndef GUARD
	#define GUARD
	...
	#endif

	guardClauses("code1.h"); Fail
	guardClauses("code2.h"); Pass

*/
  void guardClauses(string fileName,
		    string message="THE GUARD CLAUSE IS NOT FOUND IN THE FILE");

/****************************************************************************
**
** FRIEND MEMBERS
** Checks about the existence of friends members in a class.
**
****************************************************************************/
/*
- Method:  void notFriendMember(string className, string message);

- Utility: Method to verify that there not exist any friend member in a class.

- Parameters:
---string className (*): string with the name of the class to be searched.

- Example:

	class A{
		...
	};

	class B{
		friend void method();
	};

	class C{
		friend A;
	};

	class D{
		friend A;
		friend void method();
	}

	notFriendMember("A"); Pass
	notFriendMember("B"); Fail
	notFriendMember("C"); Fail
	notFriendMember("D"); Fail

*/
  void notFriendMember(string className,
		       string message = "FRIEND MEMBER IS NOT FOUND.");

/*
- Method: void friendFunction(vector<string> functionNames, 
           vector<vector<string>> parameters, string className, string message)

- Utility: Method to verify that a function's been marked as friend of a class.

- Parameters:
---vector<string> functionNames (*): vector of strings with the names 
     of the functions to be searched.
---vector<vector<string> > parameters (?): vector of vector of strings 
     with the types of the parameters of the functions to be searched.
---string className (*): string with the name of the class where the 
     desired functions have to be searched.


-Example:


	void function();

	class A{
		void method();
	};

	class B{
		friend void funcion();
	};

	friendFunction({"function"}, {{"?"}}, "A", {"?"}); Fail
	friendFunction({"function"}, {{"?"}}, "B", {"?"}); Pass

*/
  void friendFunction(vector<string> functionNames,
		      vector<vector<string>> parameters,
		      string className,
		      string message="FRIEND FUNCTION NOT FOUND.");
  
/*
- Method: void friendClass(string className, vector<string> friendClassesNames,
                   string message)

- Utility: Method to verify that a class has been marked as friend 
             of another one.

- Parameters:
---string className (*): string with the name of the class where the 
      friend classes has to be searched.
---vector<string> friendClassesNames (*): vector of strings with the 
      names of the friend classes to be searched.

- Example:

	class A{
		...
	};

	class B{
		friend class A;
	};

	friendClass("B", {"A"}); Pass
	friendClass("A", {"B"}); Fail

*/

  void friendClass(string className, vector<string> friendClassesName,
		   string message="FRIEND CLASS NOT FOUND");

/****************************************************************************
**
** PRIVATE FUNCTIONS
**
****************************************************************************/
private:

  //Auxiliary
  void apply_class(const MatchFinder::MatchResult &Result);
  list<string> getListSources(int argc, const char **argv);
  bool foundClass();
  string getHelper();
  string setFunctions(vector<string> functionNames);
  void setHelper(string help);

  //Clang
  virtual void run(const MatchFinder::MatchResult &Result);
  MatchFinder getFinder();
  
/****************************************************************************
**
** PRIVATE MEMBERS
**
****************************************************************************/

  //Arguments
  vector<string> argvs;
  int argc1, argc2;
  const char **argv1;
  const char **argv2;

  //Clang
  MatchFinder Finder;
  ASTContext *Context;
  Rewriter Rewrite;
  
  //execute object for the execution
  execute e;
  
  //Auxiliary methods
  string helper, classMessage;
  bool class_found = true;
  map<string, bool> classes;
  string fileClass = "";
  list<string> listSources;
  list<string>::iterator it;
  vector<string> p;

};

/****************************************************************************
**
** ADDITIONAL FUNCTION
**
****************************************************************************/
list<string> headers_read(string file_name, string command);

#endif //CONTROL_H_
