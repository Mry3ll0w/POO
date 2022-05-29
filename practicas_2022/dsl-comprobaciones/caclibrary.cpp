/*
 * DSL para la comprobación estática de código fuente C++ 
 * para las prácticas de POO.
 * ©2012 Los profesores de POO.
 */

#include "caclibrary.h"
#include <iostream>
using namespace std;

static llvm::cl::OptionCategory MyToolCategoryFind("check options");
static llvm::cl::OptionCategory MyToolCategoryExe("check options");

checkCode::checkCode(int argc, const char **argv, string fileClass, string help)
{
  setHelper(help);
  if (argc < 2) {
    llvm::outs() << "The file to be checked has not been indicated.\n"
		 << getHelper() + "\n";
    exit(EXIT_SUCCESS);
  }
  else {
    string option = argv[1];
    if (option.compare("--help") == 0) {
      llvm::outs() << getHelper() + "\n";
      exit(EXIT_SUCCESS);
    }
  }

  listSources = getListSources(argc, argv);

  string file_name = "control.tmp";
  string command =  "echo | clang -E -v -x c++ - 2>&1 |"
    " sed -n '/<...> search starts here/,/End of search list./p' |"
    " sed 's/End of search list.//g' |"
    " sed 's/#include <...> search starts here://g' >" + file_name;

  list<string> lstr = headers_read(file_name, command);

  command =  "echo | LANG=C cpp -v -x c++ - 2>&1 |"
    " sed -n '/<...> search starts here/,/End of search list./p' |"
    " sed 's/End of search list.//g' |"
    " sed 's/#include <...> search starts here://g' >" + file_name;

  list<string> lstr_clang = headers_read(file_name, command);
  lstr.insert(lstr.end(), lstr_clang.begin(), lstr_clang.end());

  argv1 = new const char*[lstr.size()+argc];
  argv2 = new const char*[lstr.size()+argc];

  for(int i = 0; i< argc; i++)
    argvs.push_back(argv[i]);

  argc1 = argc;
  argc2 = argc;
  for(auto pos = lstr.begin(); pos != lstr.end(); pos++) {
    argvs.push_back((*pos).c_str());
    argc1++;
    argc2++;
  }

  command = "rm " + file_name  + " > /dev/null 2>&1";
  system(command.c_str());

  this->fileClass = fileClass;
}

list<string> headers_read(string file_name, string command)
{
  int res = system(command.c_str());
  ifstream read_file;

  read_file.open(file_name.c_str(), std::ifstream::in);
  list<string> lstr;

  if (read_file.is_open() && res == 0) {
    string s;
    getline(read_file, s);

    while (! read_file.eof()) {
      if(s != "") {
	std::size_t first = s.find_first_not_of(' ');
	s = s.substr(first);
	lstr.push_back(string("-isystem" + s));
      }
      getline(read_file, s);
    }
    read_file.close();
  }
  return lstr;
}


/*
**
** Run methods
**
*/
void checkCode::check()
{
  int i = 0;
  for (std::vector<string>::iterator it = argvs.begin() ;
       it != argvs.end(); ++it) {
    argv2[i] = (*it).c_str();
    i++;
  }

  CommonOptionsParser OptionsParser(argc2, argv2, MyToolCategoryExe);
  ClangTool Tool(OptionsParser.getCompilations(), p);
  Tool.run(newFrontendActionFactory(&Finder).get());
  e.postRun();
}

/*
**
** GET methods
**
*/
MatchFinder checkCode::getFinder()
{
  return Finder;
}

string checkCode::getHelper()
{
  return helper;
}

list<string> checkCode::getListSources(int argc, const char **argv)
{
  int fixed = 0;
  for(int i = 2; i < argc; i++) {
    string arg = argv[i];
    if(arg.compare("--")==0) {
      fixed = argc - i;
      break;
    }
  }
  unsigned startSources = 1;
  string file = "";
  while(unsigned(argc - fixed) > startSources) {
    file = (string(argv[startSources]));
    it = find(listSources.begin(), listSources.end(), file);
    if(listSources.empty() || it == listSources.end()) {
      listSources.push_back(file);
    }
    startSources++;
  }
  return listSources;
}

/*
**
** SET methods
**
*/
string checkCode::setFunctions(vector<string> functionNames)
{
  string functions = "";
  unsigned int size = functionNames.size();
  for (unsigned int i = 0 ; i < size; ++i) {
    functions = functions + functionNames[i];
    if (i != size-1) {
      functions = functions + "|";
    }
  }
  return functions;
}

void checkCode::setHelper(string help)
{
  helper = help;
}

void checkCode::setCorrectMessage(string message)
{
  e.setCorrectMessage(message);
}

void checkCode::setIncorrectMessage(string message)
{
  e.setIncorrectMessage(message);
}

/*
**
** CHECKING
**
*/

// ----------------------- CHECK CLASSES ---------------------
void checkCode::classWithName(string className, string message)
{
  e.setClasses(className, message);
  Finder.addMatcher(classWithName_Matcher(className), &e);
}

void checkCode::apply_class(const MatchFinder::MatchResult &Result)
{
  if (const clang::CXXRecordDecl *Node =
      Result.Nodes.getNodeAs<clang::CXXRecordDecl>("classWithName")) {
    map<string,bool>::iterator it = classes.find(Node->getNameAsString());
    if(it != classes.end())
      it->second = true;
  }
}

bool checkCode::findClass(vector<string> className)
{
  int i = 0;
  for (std::vector<string>::iterator it = argvs.begin();
       it != argvs.end(); ++it)
    argv1[i++] = (*it).c_str();

  CommonOptionsParser OptionsParser(argc1, argv1, MyToolCategoryFind);
  p = OptionsParser.getSourcePathList();
  bool validFile = false;
  string posAux = "";
  if (fileClass == "") {}
  else {
    for(list<string>::iterator pos = listSources.begin();
	pos != listSources.end(); pos++) {
      posAux = *pos;
      posAux = posAux.substr(posAux.rfind("/") + 1);
      if(posAux == fileClass) {
        p.clear();
        p.push_back(*pos);
        validFile = true;
        break;
      }
    }
  }
  if(validFile==true) {
    MatchFinder FinderClase;
    for(vector<string>::iterator it = className.begin() ;
	it != className.end(); ++it) {
      FinderClase.addMatcher(classWithName_Matcher(*it), this);
      classes.insert(std::pair<string,bool>(*it,false));
    }
    ClangTool Tool(OptionsParser.getCompilations(),p);
    Tool.run(newFrontendActionFactory(&FinderClase).get());
    for(std::pair<const string,bool>& c : classes)
      class_found = class_found && c.second;
    if (this->foundClass())
      return class_found = true;
    else
      return class_found = false;
  }
  else {
    llvm::outs() << "--------------------\n";
    llvm::outs()<<"The file indicated '" + fileClass +
      "' to apply the checks has not been found in the parameters.\n";
    llvm::outs() << "********************\n";
    return false;
  }
}

bool checkCode::foundClass()
{
  return class_found;
}

void checkCode::run(const MatchFinder::MatchResult &Result)
{
  Context = Result.Context;
  Rewrite.setSourceMgr(Context->getSourceManager(), Context->getLangOpts());
  apply_class(Result);
}

// ----------------------- CHECK CONSTRUCTORS ---------------------
void checkCode::defaultConstructor(string className, bool exist,
				   string notFoundMessage)
{
  e.setDefaultConstructors(className, exist, notFoundMessage);
  Finder.addMatcher(defaultConstructor_Matcher(className), &e);
}

void checkCode::copyConstructor(string className, bool exist,
				string notFoundMessage)
{
  e.setCopyConstructors(className, exist, notFoundMessage);
  Finder.addMatcher(copyConstructor_Matcher(className), &e);
}

void checkCode::moveConstructor(string className, bool exist,
				string notFoundMessage)
{
  e.setMoveConstructors(className, exist, notFoundMessage);
  Finder.addMatcher(moveConstructor_Matcher(className), &e);
}

void checkCode::listInitializerConstructor(string className,
					   vector<string> parameters,
					   vector<string> initializers,
					   string message)
{
  e.setInitializers(className, parameters, initializers, message);
  Finder.addMatcher(listInitializerConstructor_Matcher(className), &e);
}

void checkCode::destructor(string className, bool exist, string message)
{
  e.setDestructors(className, exist, message);
  Finder.addMatcher(destructor_Matcher(className), &e);
}

void checkCode::destructorDeleteMember(string className,
				       vector<string> memberNames,
				       string message)
{
  for (unsigned int i = 0 ; i < memberNames.size(); i++) {
    e.setDeleteMembers(className, memberNames[i], message);
    Finder.addMatcher(destructorDeleteMember_Matcher(className, memberNames[i]),
		      &e);
  }
}

void checkCode::numberOfConstructors(string className,
				     unsigned int constructors, bool lenient,
				     string message)
{
  e.setConstructors(className, constructors, lenient, message);
  Finder.addMatcher(numberOfConstructor_Matcher(className), &e);
}

void checkCode::methodWithDynamicCast(string methodName,
				      vector<string> parameters,
				      string className, string constant,
				      string originType, string dstType,
				      string message)
{
  e.setDynamicCast(methodName,parameters,constant,className,originType,dstType,
		   message);
  Finder.addMatcher(dynamic_cast_Matcher(methodName,className),&e);
}

void checkCode::explicitSpecifiedConstructor(string className,
					     vector<string> parameters,
					     string message)
{
  e.setExplicitSpecifiedConstructors(className, parameters, message);
  Finder.addMatcher(explicitSpecifiedConstructor_Matcher(className), &e);
}

void checkCode::takeException(vector<string> exceptionClasses, string message)
{
  for (unsigned int i = 0 ; i < exceptionClasses.size(); i++) {
    e.setTakeExceptions(exceptionClasses[i], message);
    Finder.addMatcher(takeException_Matcher(exceptionClasses[i]), &e);
  }
}

// ----------------------- CHECK VARIABLES ---------------------
void checkCode::memberVariable(string className,vector<string> memberNames,
			       vector<string> constant, vector<bool> exist,
			       string message)
{
  for (unsigned int i = 0 ; i < memberNames.size(); i++) {
    e.setMembers(className, memberNames[i], constant[i], exist[i], message);
    Finder.addMatcher(member_Matcher(className, memberNames[i]), &e);
  }
}

void checkCode::staticVariable(string className, vector<string> variableNames,
			       vector<string> constant, string message)
{
  for (unsigned int i = 0 ; i < variableNames.size(); i++) {
    e.setStaticVariables(className, variableNames[i], constant[i], message);
    Finder.addMatcher(staticVariable_Matcher(className, variableNames[i]), &e);
  }
}

void checkCode::releaseVariable(string message)
{
  e.setReleasedVariables(message);
  Finder.addMatcher(variableNew_Matcher(), &e);
  Finder.addMatcher(variableDelete_Matcher(), &e);
}

void checkCode::allPrivateVariableMember(string className, string message)
{
  e.setClassWithAllPrivateMembers(className, message);
  Finder.addMatcher(allPrivateMember_Matcher(className), &e);
}

void checkCode::memberVariableAccessLevel(string className,
					  vector<string> memberNames,
					  string level, string message)
{
  for (unsigned int i = 0 ; i < memberNames.size(); i++) {
    e.setMembersAccessLevel(className, memberNames[i], level, message);
    Finder.addMatcher(memberVariableAccessLevel_Matcher(className,
							memberNames[i]), &e);
  }
}

// ----------------------- CHECK METHODS ---------------------
void checkCode::method(vector<string> methodNames,
		       vector<vector<string>> parameters, string className,
		       vector<string> constant, string message)
{
  if(methodNames.size() == parameters.size())
    for (unsigned int i = 0 ; i < methodNames.size(); i++) {
      e.setMethodsWithName(methodNames[i], className, parameters[i],
			   constant[i], message);
      Finder.addMatcher(method_Matcher(methodNames[i], className), &e);
    }
  else
    llvm::outs() << "checkCode::method => different number of methodNames"
      " and parameters.\n";
}

void checkCode::methodWithReferencedMemberVariable
(vector<string> methodNames, vector<vector<string>> parameters,
 string className, vector<string> constant, vector<string> usedVariables,
 string message)
{
  if(methodNames.size() == parameters.size()
     && methodNames.size() == usedVariables.size())
    for (unsigned int i = 0 ; i < methodNames.size(); i++) {
      e.setMethodsWithReferencedVariable(methodNames[i], className,
					 parameters[i], constant[i],
					 usedVariables[i], message);
      Finder.addMatcher(methodWithReferencedVariable_Matcher(methodNames[i],
							     className,
							     usedVariables[i]),
			&e);
    }
  else
    llvm::outs() << "checkCode::methodWithReferencedMemberVariable =>"
      " different number of methodNames, parameters and usedVariables.\n";
}

void checkCode::noExceptMethod(vector<string> methodNames,
			       vector<vector<string>> parameters,
			       string className, vector<string> constant,
			       string message)
{
  if(methodNames.size() == parameters.size())
    for (unsigned int i = 0 ; i < methodNames.size(); i++) {
      e.setNoExceptMethods(methodNames[i], parameters[i], className,
			   constant[i], message);
      Finder.addMatcher(noExceptMethod_Matcher(methodNames[i], className), &e);
    }
  else
    llvm::outs() << "checkCode::noExceptMethod => "
      "different number of methodNames and parameters.\n";
}

void checkCode::inlineMethod(vector<string> methodNames,
			     vector<vector<string>> parameters,
			     string className, vector<string> constant,
			     string message)
{
  if(methodNames.size() == parameters.size())
    for (unsigned int i = 0 ; i < methodNames.size(); i++) {
      e.setInlineMethods(methodNames[i], parameters[i], className,
			 constant[i], message);
      Finder.addMatcher(inlineMethod_Matcher(methodNames[i], className), &e);
    }
  else
    llvm::outs() << "checkCode::inlineMethod =>"
      " different number of methodNames and parameters.\n";
}

void checkCode::defaultArgumentsInMethod(vector<string> methodNames,
					 vector<vector<string>> parameters,
					 string className,
					 vector<string> constant,
					 vector<unsigned int> numDefaultArgs,
					 vector<vector<string>> defaultArgs,
					 string message)
{
  if(methodNames.size() == parameters.size()) {
    for (unsigned int i = 0 ; i < methodNames.size(); i++) {
      if(numDefaultArgs[i] == 0 || numDefaultArgs[i] == defaultArgs[i].size()) {
	e.setDefaultArgumentsInMethod(methodNames[i], parameters[i],
				      className, constant[i], numDefaultArgs[i],
				      defaultArgs[i], message);
	Finder.addMatcher(defaultArgumentsInMethod_Matcher(methodNames[i],
							   className), &e);
      }
      else
	llvm::outs() << "checkCode::defaultArgumentsInMethod => "
	  "numDefaultArgs and defaultArgs do not match.\n";
    }
  }
  else
    llvm::outs() << "checkCode::defaultArgumentsInMethod =>"
      " different number of methodNames and parameters.\n";
}

void checkCode::deletedMethod(vector<string> methodNames,
			      vector<vector<string>> parameters,
			      string className, vector<string> constant,
			      string message)
{
  if(methodNames.size() == parameters.size()) {
    for (unsigned int i = 0 ; i < methodNames.size(); i++) {
      e.setDeletedMethods(methodNames[i], className, parameters[i],
			  constant[i], message);
      Finder.addMatcher(deletedMethod_Matcher(methodNames[i], className), &e);
    }
  }
  else
    llvm::outs() << "checkCode::deletedMethod =>"
      " different number of methodNames and parameters.\n";
}

void checkCode::defaultedMethod(vector<string> methodNames,
				vector<vector<string>> parameters,
				string className, vector<string> constant,
				string message)
{
  if(methodNames.size() == parameters.size()) {
    for (unsigned int i = 0 ; i < methodNames.size(); i++) {
      e.setDefaultedMethods(methodNames[i], className, parameters[i],
			    constant[i], message);
      Finder.addMatcher(defaultedMethod_Matcher(methodNames[i], className), &e);
    }
  }
  else
    llvm::outs() << "checkCode::defaultedMethod => "
      "different number of methodNames and parameters.\n";
}

void checkCode::virtualMethod(vector<string> methodNames,
			      vector<vector<string>> parameters,
			      string className, vector<string> constant,
			      string message)
{
  if(methodNames.size() == parameters.size()) {
    for (unsigned int i = 0 ; i < methodNames.size(); i++) {
      e.setVirtualMethods(methodNames[i], className, parameters[i],
			  constant[i], message);
      Finder.addMatcher(virtualMethod_Matcher(methodNames[i], className), &e);
    }
  }
  else
    llvm::outs() << "checkCode::deletedMethod =>"
      " different number of methodNames and parameters.\n";
}


// ----------------------- CHECK OPERATORS ---------------------
void checkCode::copyAssignmentOperator(string className, bool exist,
				       string message)
{
  e.setCopyAssignmentOperators(className, exist, message);
  Finder.addMatcher(copyAssignmentOperator_Matcher(className), &e);
}

void checkCode::moveAssignmentOperator(string className, bool exist,
				       string message)
{
  e.setMoveAssignmentOperators(className, exist, message);
  Finder.addMatcher(moveAssignmentOperator_Matcher(className), &e);
}

void checkCode::methodWithReferencedMethod
(vector<string> mainMethodNames, vector<vector<string>> mainMethodparameters,
 string mainClassName, vector<string> mainConstant,
 vector<string> usedMethodNames, vector<vector<string>> usedMethodparameters,
 string usedClassName, vector<string> usedConstant, string message)
{
  if(mainMethodNames.size() == mainMethodparameters.size()
     && usedMethodNames.size() == usedMethodparameters.size()
     && mainMethodNames.size() == usedMethodNames.size()) {
    for (unsigned int i = 0 ; i < mainMethodNames.size(); i++) {
      e.setMethodsWithReferencedMethod(mainMethodNames[i],
				       mainMethodparameters[i], mainClassName,
				       mainConstant[i], usedMethodNames[i],
				       usedMethodparameters[i], usedClassName,
				       usedConstant[i], message);
      Finder.addMatcher(methodWithReferencedMethod_Matcher(mainMethodNames[i], mainClassName, usedMethodNames[i], usedClassName), &e);
    }
  }
  else
    llvm::outs() << "checkCode::methodWithReferencedMethod =>"
      " different number of methodNames and parameters "
      "in the main and used method.\n";
}

void checkCode::methodWithReferencedFunction
(vector<string> mainMethodNames, vector<vector<string>> mainMethodparameters,
 string mainClassName, vector<string> mainConstant,
 vector<string> usedFunctionNames,
 vector<vector<string>> usedFunctionParameters, string message)
{
  if(mainMethodNames.size() == mainMethodparameters.size()
     && usedFunctionNames.size() == usedFunctionParameters.size()
     && mainMethodNames.size() == usedFunctionNames.size()) {
    for (unsigned int i = 0 ; i < mainMethodNames.size(); i++) {
      e.setMethodsWithReferencedFunction(mainMethodNames[i],
					 mainMethodparameters[i],
					 mainClassName, mainConstant[i],
					 usedFunctionNames[i],
					 usedFunctionParameters[i], message);
      Finder.addMatcher(methodWithReferencedFuntion_Matcher
			(mainMethodNames[i], mainClassName,
			 usedFunctionNames[i]), &e);
    }
  }
  else
    llvm::outs() << "checkCode::methodWithReferencedFunction => "
      "different number of functionNames and parameters"
      " in the main and used function.\n";
}

void checkCode::functionWithReferencedMethod
(vector<string> mainFunctionNames,
 vector<vector<string>> mainFunctionParameters, vector<string> usedMethodNames,
 vector<vector<string>> usedMethodparameters, string usedClassName,
 vector<string> usedConstant, string message)
{
  if(mainFunctionNames.size() == mainFunctionParameters.size()
     && usedMethodNames.size() == usedMethodparameters.size()
     && mainFunctionNames.size() == usedMethodNames.size()) {
    for (unsigned int i = 0 ; i < mainFunctionNames.size(); i++) {
      e.setFunctionsWithReferencedMethod(mainFunctionNames[i],
					 mainFunctionParameters[i],
					 usedMethodNames[i],
					 usedMethodparameters[i],
					 usedConstant[i], usedClassName,
					 message);
      Finder.addMatcher(functionWithReferencedMethod_Matcher
			(mainFunctionNames[i], usedMethodNames[i],
			 usedClassName), &e);
    }
  }
  else
    llvm::outs() << "checkCode::functionWithReferencedMethod =>"
      " different number of functionNames and parameters"
      " in the main and used function.\n";
}

void checkCode::functionWithReferencedFunction
(vector<string> mainFunctionNames,
 vector<vector<string>> mainFunctionParameters,
 vector<string> usedFunctionNames,
 vector<vector<string>> usedFunctionParameters, string message)
{
  if(mainFunctionNames.size() == mainFunctionParameters.size()
     && usedFunctionNames.size() == usedFunctionParameters.size()
     && mainFunctionNames.size() == usedFunctionNames.size()) {
    for (unsigned int i = 0 ; i < mainFunctionNames.size(); i++) {
      e.setFunctionsWithReferencedFunction
	(mainFunctionNames[i], mainFunctionParameters[i], usedFunctionNames[i],
	 usedFunctionParameters[i], message);
      Finder.addMatcher(functionWithReferencedFuntion_Matcher
			(mainFunctionNames[i], usedFunctionNames[i]), &e);
    }
  }
  else
    llvm::outs() << "checkCode::functionWithReferencedFunction => "
      "different number of functionNames and parameters"
      " in the main and used function.\n";
}

void checkCode::function(vector<string> functionNames,
			 vector<vector<string>> parameters, string message)
{
  if(functionNames.size() == parameters.size())
    for (unsigned int i = 0 ; i < functionNames.size(); i++) {
      e.setFunctionsWithName(functionNames[i], parameters[i], message);
      Finder.addMatcher(functionName_Matcher(functionNames[i]), &e);
    }
  else
    llvm::outs() << "checkCode::function =>"
      " different number of functionNames and parameters.\n";
}

// ----------------------- CHECK HEADERS ---------------------
void checkCode::invocationsFromHeaders(vector<string> functionNames,
				       string headerName, bool exist,
				       string message)
{
  for (unsigned int i = 0 ; i < functionNames.size(); i++) {
    e.setInvocationsFromHeader(functionNames[i], headerName, exist, message);
    Finder.addMatcher(invocationsFromHeader_Matcher(functionNames[i]), &e);
  }
}

void checkCode::fileIncludedHeader(string headerName, vector<string> fileNames,
				   string message)
{
  e.setFileIncludeHeader(fileNames, headerName, message);
}

void checkCode::guardClauses(string fileName, string message)
{
  e.setGuardClauses(fileName, message);
}


// ----------------------- FRIEND MEMBERS ---------------------
void checkCode::notFriendMember(string className, string message)
{
  e.setNotFriendMembers(className, message);
  Finder.addMatcher(notFriendMember_Matcher(className), &e);
}

void checkCode::friendFunction(vector<string> functionNames,
			       vector<vector<string>> parameters,
			       string className, string message)
{
  if(functionNames.size() == parameters.size())
    for (unsigned int i = 0 ; i < functionNames.size(); i++) {
      e.setFriendFunction(functionNames[i], className, parameters[i], message);
      Finder.addMatcher(friendFunction_Matcher(functionNames[i],className), &e);
    }
  else
    llvm::outs() << "checkCode::friendFunction => "
      "different number of functionNames and parameters.\n";
}

void checkCode::friendClass(string className, vector<string> friendClassesNames,
			    string message)
{
  for (unsigned int i = 0 ; i < friendClassesNames.size(); i++) {
    e.setFriendClass(className, friendClassesNames[i], message);
    Finder.addMatcher(friendClass_Matcher(className, friendClassesNames[i]),&e);
  }
}
