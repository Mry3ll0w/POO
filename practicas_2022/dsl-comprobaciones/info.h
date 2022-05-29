/* -*-c++-*-
 * Cabecera del DSL de comprobación estática de código fuente de las
 * prácticas de POO.
 * ©2021 Los profesores de POO
 */
#ifndef INFO_H_
#define INFO_H_

#include <string>
#include <vector>

using namespace std;

class Info{
public:
  //CONSTRUCTOR
  explicit Info(string n, string m, bool f, bool exist = true)
    :name(n), message(m), found(f), exist(exist) {}
  /*
  **
  ** SET METHODS
  **
  */
  //General set methods
  void setName(string n) { name = n; }
  void setClass(string c) { ofClass = c;	}
  void setMessage(string m) { message = m; }
  void setFound(bool f) { found = f; }
  void setValid(bool v) { valid = v; }
  void setExist(bool e) { exist = e; }
  //Number of constructors set methods
  void setNumberOfConstructors(unsigned int c) { numberOfConstructors = c; }
  void setExpectedConstructors(unsigned int c) { expectedConstructors = c; }
  void setLenient(bool b) { lenient = b; }
  //Cons or no const methods set methods
  void setConstant(string c) { constant = c; }
  void setUsedConstant(string c) { usedConstant = c; }
  //Searching methods set methods
  void setParameters(vector<string> p) { parameters = p; }
  void setDefaultParams(vector<string> p) { defaultParams = p; }
  void setUsedParameters(vector<string> p) { usedParameters = p; }
  void setInitializers(vector<string> i) { initializers = i; }
  void setUsedFunction(string usedF) { usedFunction = usedF; }
  void setUsedClass(string usedC) { usedClass = usedC; }
  void setFriendClass(string friendC) { friendClass = friendC; }
  void setLevel(string l) { level = l; }
  void setNumDefaultArguments(unsigned int num) { numDefaultArguments = num; }
  void setDefaultArguments(vector<string> dfargs) { defaultArguments = dfargs; }
  void setMemberVariable(string variable) { memberVariable = variable; }
  /*
  **
  ** GET METHODS
  **
  */
  //General get methods
  string getName() { return name; }
  string getClass() { return ofClass; }
  string getMessage() { return message;	}
  bool getFound() { return found; }
  bool getValid() { return valid; }
  bool getExist() { return exist; }
  //Number of constructors get methods
  unsigned int getNumberOfConstructors() { return numberOfConstructors;	}
  unsigned int getExpectedConstructors() { return expectedConstructors;	}
  bool getLenient() { return lenient; }
  //Const or no const methods get methods
  string getConstant() { return constant; }
  string getUsedConstant() { return usedConstant; }
  //Searching methods get methods
  vector<string> getParameters() { return parameters; }
  vector<string> getDefaultParams() { return defaultParams; }
  vector<string> getUsedParameters() { return usedParameters; }		
  vector<string> getInitializers() { return initializers; }
  string getUsedFunction() { return usedFunction; }
  string getUsedClass() { return usedClass; }
  string getFriendClass() { return friendClass; }
  string getLevel() { return level; }
  unsigned int getNumDefaultArguments() { return numDefaultArguments; }
  vector<string> getDefaultArguments() { return defaultArguments; }
  string getMemberVariable() { return memberVariable; }
private:
  //General members
  string name,
    ofClass,
    message;
  bool found = false,
    valid = false,
    exist = true;
  //Number of constructors members
  unsigned int numberOfConstructors = 0,
    expectedConstructors = 0;
  bool lenient = false;
  //Searching methods.
  vector<string> parameters,
    defaultParams,
    usedParameters,
    initializers;
  string usedFunction,
    constant,
    usedConstant,
    usedClass,
    friendClass,
    level,
    memberVariable;
  unsigned int numDefaultArguments;
  vector<string> defaultArguments;
};

#endif // INFO_H_
