#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <assert.h>
#include <string>
using namespace std;

//Tokenizer

// Token Types
enum tokentype { KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST };

// keyWord
enum keyword { CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN, CHAR, VOID, VAR, STATIC, FIELD, LET, DO, IF, ELSE, WHILE, RETURN, TRUE, FALSE, null, THIS };

class JackTokenizer
{
public:
	// Constructor
	JackTokenizer(string inputFile); // Opens the input file and gets ready to tokenize it
	// Destructor
	~JackTokenizer();
	
	// Methods
	bool hasMoreTokens(void); // Do we have more tokens in the input?
	void advance(void); // Gets the next token from the input and makes it the current token. This method is only called if hasMoreTokens is true. Initially there is no current token.
	tokentype tokenType(void); // Returns the type of the current token
	keyword keyWord(void); // Returns the keyword which is the current token. Should be called only when tokenType is KEYWORD
	char symbol(void); // Returns the character which is the current token. Should be called only when tokenType is SYMBOL
	string identifier(void); // Returns the identifier which is the current token. Should be called only when tokenType is IDENTIFIER
	int intVal(void); // Returns the integer value of the current token. Should be called only when tokenType is INT_CONST
	string stringVal(void); // Returns the string value of the current token, without the double quotes. Should be called only when tokenType is STRING_CONST
	string getCurrentToken(void); // Returns the currentToken
	void updateCurrentToken(void); // Drops off the first character of currentToken_
	
private:
	ifstream fin_;
	string currentToken_;
	
};

// helper functions
namespace helper
{
	bool isInt(string currentToken)
	{
		if(currentToken.empty()) { return false; } // make sure the string is not empty
		for(int i=0;i<currentToken.length();i++)
		{
			if(currentToken[i] != '0' && currentToken[i] != '1' && currentToken[i] != '2' && currentToken[i] != '3' && currentToken[i] != '4' && currentToken[i] != '5'
				&& currentToken[i] != '6' && currentToken[i] != '7' && currentToken[i] != '8' && currentToken[i] != '9') { return false; }
		}
		// number is an int, check the range
		int temp = stoi(currentToken);
		assert(temp >= 0 && temp <= 32767);
		return true; // int is in range, return true
	}
}

// Constructor
JackTokenizer::JackTokenizer(string inputFile)
{
	fin_.open(inputFile.c_str());
	if(!fin_.is_open())
	{
		cerr << "JackTokenizer: Failed to open input file.\n";
	}
	currentToken_="";
}

// Destructor
JackTokenizer::~JackTokenizer()
{
	if(fin_.is_open())
		fin_.close();
}

// Methods
bool JackTokenizer::hasMoreTokens(void)
{
	return !fin_.eof();
}

void JackTokenizer::advance(void)
{
	if(hasMoreTokens())
		fin_ >> currentToken_;
	// Handling comments
	while(currentToken_ == "//" || currentToken_ == "/*" || currentToken_ == "/**")
	{
		if(currentToken_ == "/*" || currentToken_ == "/**")
		{
			int endcomment;
			do
			{
				getline(fin_,currentToken_);
				endcomment = currentToken_.find("*/");
			} while(endcomment == -1);
			fin_ >> currentToken_;
		}
		else
		{
			getline(fin_,currentToken_); // get the rest of the line and trash it
			fin_ >> currentToken_; // get first token of next line
		}
	}
}

tokentype JackTokenizer::tokenType(void)
{
	if(currentToken_ == "class" || currentToken_ == "constructor" || currentToken_ == "function" || currentToken_ == "method" ||
		currentToken_ == "field" || currentToken_ == "static" || currentToken_ == "var" || currentToken_ == "int" || currentToken_ == "char" ||
		currentToken_ == "boolean" || currentToken_ == "void" || currentToken_ == "true" || currentToken_ == "true;" || currentToken_ == "true)" || currentToken_ == "true);" ||
		currentToken_ == "false" || currentToken_ == "false;" || currentToken_ == "false)" || currentToken_ == "false);" || currentToken_ == "null" || currentToken_ == "null;" || currentToken_ == "null)" || currentToken_ == "null);" ||
		currentToken_ == "this" || currentToken_ == "this;" || currentToken_ == "this)" || currentToken_ == "this);" || currentToken_ == "let" || currentToken_ == "do" || currentToken_ == "if" || currentToken_ == "else" ||
		currentToken_ == "while" || currentToken_ == "return" || currentToken_ == "return;") { return KEYWORD; }
	else if(currentToken_[0] == '{' || currentToken_[0] == '}' || currentToken_[0] == '(' || currentToken_[0] == ')' || currentToken_[0] == '[' || currentToken_[0] == ']'
		 || currentToken_[0] == '.' || currentToken_[0] == ',' || currentToken_[0] == ';' || currentToken_[0] == '+' || currentToken_[0] == '-' || currentToken_[0] == '*'
		 || currentToken_[0] == '/' || currentToken_[0] == '&' || currentToken_[0] == '|' || currentToken_[0] == '<' || currentToken_[0] == '>' || currentToken_[0] == '='
		 || currentToken_[0] == '~') { return SYMBOL; }
	else if(helper::isInt(currentToken_.substr(0,1))) { return INT_CONST; }
	else if(currentToken_[0] == '"') { return STRING_CONST; }
	else if(!helper::isInt(currentToken_.substr(0,1))) { return IDENTIFIER; } // variable name does not start with a number
	else { cerr << "Token is not a token type.\n"; }
}

keyword JackTokenizer::keyWord(void)
{
	assert(tokenType() == KEYWORD);
	if(currentToken_ == "class") 
	{
		return CLASS;
	}
	else if(currentToken_ == "method") 
	{
		return METHOD;
	}
	else if(currentToken_ == "function") 
	{
		return FUNCTION;
	}
	else if(currentToken_ == "constructor")
	{
		return CONSTRUCTOR;
	}
	else if(currentToken_ == "int")
	{
		return INT;
	}
	else if(currentToken_ == "boolean") 
	{
		return BOOLEAN;
	}
	else if(currentToken_ == "char")
	{
		return CHAR;
	}
	else if(currentToken_ == "void")
	{
		return VOID;
	}
	else if(currentToken_ == "var")
	{
		return VAR;
	}
	else if(currentToken_ == "static") 
	{
		return STATIC;
	}
	else if(currentToken_ == "field")
	{
		return FIELD;
	}
	else if(currentToken_ == "let")
	{
		return LET;
	}
	else if(currentToken_ == "do") 
	{
		return DO;
	}
	else if(currentToken_ == "if")
	{
		return IF;
	}
	else if(currentToken_ == "else") 
	{
		return ELSE;
	}
	else if(currentToken_ == "while") 
	{
		return WHILE;
	}
	else if(currentToken_ == "return" || currentToken_ == "return;") 
	{
		return RETURN;
	}
	else if(currentToken_ == "true" || currentToken_ == "true;" || currentToken_ == "true)" || currentToken_ == "true);") 
	{
		if(currentToken_ == "true")
			currentToken_ = "";
		else if(currentToken_ == "true;")
			currentToken_ = ";";
		else if(currentToken_=="true)")
			currentToken_ = ")";
		else
			currentToken_=");";
		return TRUE;
	}
	else if(currentToken_ == "false" || currentToken_ == "false;" || currentToken_ == "false)" || currentToken_ == "false);") 
	{
		if(currentToken_ == "false")
			currentToken_ = "";
		else if(currentToken_ == "false;")
			currentToken_ = ";";
		else if(currentToken_=="false)")
			currentToken_ = ")";
		else
			currentToken_=");";
		return FALSE;
	}
	else if(currentToken_ == "null" || currentToken_ == "null;" || currentToken_ == "null)" || currentToken_ == "null);") 
	{
		if(currentToken_=="null")
			currentToken_="";
		else if(currentToken_ == "null;")
			currentToken_ = ";";
		else if(currentToken_=="null)")
			currentToken_=")";
		else
			currentToken_=");";
		return null;
	}
	else if(currentToken_ == "this" || currentToken_ == "this;" || currentToken_=="this)" || currentToken_=="this);") 
	{
		if(currentToken_=="this")
			currentToken_="";
		else if(currentToken_ == "this;")
			currentToken_ = ";";
		else if(currentToken_=="this)")
			currentToken_=")";
		else
			currentToken_=");";
		return THIS;
	}
}

char JackTokenizer::symbol(void)
{
	assert(tokenType() == SYMBOL);
	return currentToken_[0];
}

string JackTokenizer::identifier(void) // identifier will perform an update on currentToken_
{
	assert(tokenType() == IDENTIFIER);
	string returnString;
	int dot = currentToken_.find(".");
	int parens = currentToken_.find("(");
	int braket = currentToken_.find("[");
	int endparens = currentToken_.find(")");
	int endbraket = currentToken_.find("]");
	int comma = currentToken_.find(",");
	int semi = currentToken_.find(";");
	int eq = currentToken_.find("=");
	if(dot > -1)
	{
		returnString += currentToken_.substr(0,dot);
		currentToken_ = currentToken_.substr(dot, currentToken_.length());
	}
	else if(braket > -1 && braket < parens) // if braket comes before parens then take this as priority
	{
		returnString += currentToken_.substr(0,braket);
		currentToken_ = currentToken_.substr(braket, currentToken_.length());
	}
	else if(parens > -1 && parens < braket) // else if parens is less than braket, then take this
	{
		returnString += currentToken_.substr(0,parens);
		currentToken_ = currentToken_.substr(parens, currentToken_.length());
	}
	else if(braket > -1)
	{
		returnString += currentToken_.substr(0,braket);
		currentToken_ = currentToken_.substr(braket, currentToken_.length());
	}
	else if(parens > -1)
	{
		returnString += currentToken_.substr(0,parens);
		currentToken_ = currentToken_.substr(parens, currentToken_.length());
	}
	else if(endparens > -1)
	{
		returnString += currentToken_.substr(0,endparens);
		currentToken_ = currentToken_.substr(endparens, currentToken_.length());
	}
	else if(endbraket > -1)
	{
		returnString += currentToken_.substr(0,endbraket);
		currentToken_ = currentToken_.substr(endbraket, currentToken_.length());
	}
	else if(comma > -1)
	{
		returnString += currentToken_.substr(0,comma);
		currentToken_ = currentToken_.substr(comma, currentToken_.length());
	}
	else if(eq > -1)
	{
		returnString += currentToken_.substr(0,eq);
		currentToken_ = currentToken_.substr(eq,currentToken_.length());
	}
	else if(semi > -1) // semi is last because a statement always ends in semicolon
	{
		returnString += currentToken_.substr(0,semi);
		currentToken_ = currentToken_.substr(semi, currentToken_.length());
	}
	else
	{
		returnString = currentToken_;
		currentToken_ = "";
	}
	return returnString;
}

int JackTokenizer::intVal(void)
{
	assert(tokenType() == INT_CONST);
	string returnInt;
	returnInt += currentToken_[0];
	currentToken_ = currentToken_.substr(1,currentToken_.length());
	while(helper::isInt(currentToken_.substr(0,1)))
	{
		returnInt += currentToken_[0];
		currentToken_ = currentToken_.substr(1,currentToken_.length());
	}	
	return stoi(returnInt);
}

string JackTokenizer::stringVal(void)
{
	assert(tokenType() == STRING_CONST);
	currentToken_ = currentToken_.substr(1,currentToken_.length()-1); // "Drop the first quote"
	int endQuote = currentToken_.find('"');
	if(endQuote == -1) // if the end quote is not found in the currentToken_, find it.
	{
		char c;
		fin_.get(c);
		while(c != '"')
		{
			currentToken_ += c;
			fin_.get(c);
		}
		string returnString = currentToken_;
		currentToken_ = "";
		return returnString;
	}
	else // if endQuote is found, return the string in before the end quote and update the currentToken_ to be the rest of the string after the end quote
	{
		string returnString = currentToken_.substr(0,endQuote);
		currentToken_ = currentToken_.substr(endQuote+1,currentToken_.length()-(endQuote+1));
		return returnString;
	}
}

string JackTokenizer::getCurrentToken(void)
{
	return currentToken_;
}

void JackTokenizer::updateCurrentToken(void)
{
	currentToken_ = currentToken_.substr(1,currentToken_.length());
}

//Symbol Table

namespace symboltable
{
	enum Kind { STATIC, FIELD, ARG, VAR, NONE };
	
	struct ST
	{
		string type;
		Kind kind;
		int index;
	};
}

class SymbolTable
{
public:	
	// Constructor
	SymbolTable(); // Creates a new empty symbol table
	
	// Methods
	void startSubroutine(void); // Starts a new subroutine scope (resets the subroutine's symbol table)
	void define(string name, string type, symboltable::Kind kind); // Defines a new identifier of a given name, type, and kind and assigns it a running index. symboltable::STATIC and FIELD have class scope, ARG and VAR have subroutine scope
	int varCount(symboltable::Kind kind); // Returns the number of variables of the given kind already defined in the current scope
	symboltable::Kind kindOf(string name); // Returns the kind of the named identifier in the current scope. If the identifier is unknown in the current scope, returns NONE
	string typeOf(string name); // Returns the type of the named identifier in the current scope
	int indexOf(string name); // Returns the index assigned to the named identifier

	
private:
	map<string, symboltable::ST> class_scope_; // hash table for class scope
	map<string, symboltable::ST> subroutine_scope_; // hash table for subroutine scope
	int static_count_; // keeps a running index of static variables for class scope
	int field_count_; // keeps a running index of field variables for class scope
	int arg_count_; // keeps a running index of argument variables for subroutine scope
	int var_count_; // keeps a running index of var variables for subroutine scope
};

// helper method
bool isKey(map<string, symboltable::ST> & scope, string key)
{
	return !(scope.find(key) == scope.end());
}

SymbolTable::SymbolTable() // all private variables initialized as ""empty"
{
	class_scope_.clear();
	subroutine_scope_.clear();
	static_count_ = 0;
	field_count_ = 0;
	arg_count_ = 0;
	var_count_ = 0; 
}

void SymbolTable::startSubroutine(void) // resets the subroutine's symbol table
{
	subroutine_scope_.clear();
	arg_count_ = 0;
	var_count_ = 0; 
}

void SymbolTable::define(string name, string type, symboltable::Kind kind)
{
	if(kind == symboltable::STATIC)
	{
		class_scope_[name].type = type;
		class_scope_[name].kind = kind;
		class_scope_[name].index = static_count_;
		static_count_++;
	}
	else if(kind == symboltable::FIELD)
	{
		class_scope_[name].type = type;
		class_scope_[name].kind = kind;
		class_scope_[name].index = field_count_;
		field_count_++;
	}
	else if(kind == symboltable::ARG)
	{
		subroutine_scope_[name].type = type;
		subroutine_scope_[name].kind = kind;
		subroutine_scope_[name].index = arg_count_;
		arg_count_++;
	}
	else if(kind == symboltable::VAR)
	{
		subroutine_scope_[name].type = type;
		subroutine_scope_[name].kind = kind;
		subroutine_scope_[name].index = var_count_;
		var_count_++;
	}
}

int SymbolTable::varCount(symboltable::Kind kind)
{
	switch(kind)
	{
		case symboltable::STATIC:
			return static_count_;
		case symboltable::FIELD:
			return field_count_;
		case symboltable::ARG:
			return arg_count_;
		case symboltable::VAR:
			return var_count_;
		default:
			return -1;
	}
}

symboltable::Kind SymbolTable::kindOf(string name)
{
	if(isKey(class_scope_, name))
		return class_scope_[name].kind;
	else if(isKey(subroutine_scope_, name))
		return subroutine_scope_[name].kind;
	else
		return symboltable::NONE;
}

string SymbolTable::typeOf(string name)
{
	if(isKey(class_scope_, name))
		return class_scope_[name].type;
	else if(isKey(subroutine_scope_, name))
		return subroutine_scope_[name].type;
	else
		return "";
}

int SymbolTable::indexOf(string name)
{
	if(isKey(class_scope_, name))
		return class_scope_[name].index;
	else if(isKey(subroutine_scope_, name))
		return subroutine_scope_[name].index;
	else
		return -1;
}

//VM Writer

namespace vmwriter
{
	enum Segment { CONST, ARG, LOCAL, STATIC, THIS, THAT, POINTER, TEMP };
	enum Command { ADD, SUB, NEG, EQ, GT, LT, AND, OR, NOT };
	
	string segment2String(Segment seg)
	{
		switch(seg)
		{
			case CONST:
				return "constant";
			case ARG:
				return "argument";
			case LOCAL:
				return "local";
			case STATIC:
				return "static";
			case THIS:
				return "this";
			case THAT:
				return "that";
			case POINTER:
				return "pointer";
			case TEMP:
				return "temp";
		}
	}
	
	string command2String(Command com)
	{
		switch(com)
		{
			case ADD:
				return "add";
			case SUB:
				return "sub";
			case NEG:
				return "neg";
			case EQ:
				return "eq";
			case GT:
				return "gt";
			case LT:
				return "lt";
			case AND:
				return "and";
			case OR:
				return "or";
			case NOT:
				return "not";
		}
	}
};
namespace vm=vmwriter;


class VMWriter
{
public:
	// Constructor
	VMWriter(string fileName); // Creates a new file and prepares it for writing.
	
	// Methods
	void writePush(vm::Segment segment, int index); // Writes a VM push command
	void writePop(vm::Segment segment, int index); // Writes a VM pop command
	void writeArithmetic(vm::Command command); // Writes a VM arithmetic command
	void writeLabel(string label); // Writes a VM label comand
	void writeGoto(string label); // Writes a VM goto command
	void writeIf(string label); // Writes a VM if-goto command
	void writeCall(string name, int nArgs); // Writes a VM call command
	void writeFunction(string name, int nLocals); // Writes a VM function command
	void writeReturn(void); // Writes a VM return command
	void close(void); // Closes the output file
	
private:
	ofstream fout_;
};

VMWriter::VMWriter(string fileName)
{
	fout_.open(fileName.c_str());
}

void VMWriter::close(void)
{
	if(fout_.is_open())
		fout_.close();
}

void VMWriter::writePush(vm::Segment segment, int index)
{
	fout_ << "push " << vm::segment2String(segment) << " " << index << endl;
}

void VMWriter::writePop(vm::Segment segment, int index)
{
	fout_ << "pop " << vm::segment2String(segment) << " " << index << endl;
}

void VMWriter::writeArithmetic(vm::Command command)
{
	fout_ << vm::command2String(command) << endl;
}

void VMWriter::writeLabel(string label)
{
	fout_ << "label " << label << endl;
}

void VMWriter::writeGoto(string label)
{
	fout_ << "goto " << label << endl;
}

void VMWriter::writeIf(string label)
{
	fout_ << "if-goto " << label << endl;
}

void VMWriter::writeCall(string name, int nArgs)
{
	fout_ << "call " << name << " " << nArgs << endl;
}

void VMWriter::writeFunction(string name, int nLocals)
{
	fout_ << "function " << name << " " << nLocals << endl;
}

void VMWriter::writeReturn(void)
{
	fout_ << "return" << endl;
}

//Compilation Engine

class CompilationEngine
{
public:
	// Constructor
	CompilationEngine(JackTokenizer * JT, VMWriter * VM, SymbolTable * ST); // Creates a new compilation engine with the given input and out. The next routine called must be compileClass()
	// Destructor
	~CompilationEngine();
	
	// Methods
	void compileClass(void); // Compiles a complete class
	void compileClassVarDec(void); // Compiles a static declaration or a field declaration
	void compileSubroutine(void); // Compiles a complete method, function, or constructor
	void compileParameterList(void); // Compiles a (possibly empty) parameter list, not including the enclosing "()"
	void compileSubroutineBody(void); // Compiles subroutine body
	void compileVarDec(void); // Compiles a var declaration
	void compileStatements(void); // Compiles a sequence of statements, not including the enclosing {}.
	void compileDo(void); // Compiles a do statement
	void compileLet(void); // Compiles a let statement
	void compileWhile(void); // Compiles a while statement
	void compileReturn(void); // Compiles a return statement
	void compileIf(void); // Compiles an if statement, possible with a trailing else clause
	void compileExpression(void); // Compiles an expression
	void compileTerm(void); // Compiles a term.  Uses a single lookahead
	void compileExpressionList(void); // Compiles a (possibly empty) comma-separated list of expressions
	
private:
	JackTokenizer * JT_;
	SymbolTable * ST_;
	VMWriter * VM_;
	string currentFunctionName_;
	keyword subroutineType_;
	string className_;
	int numArgs_;
	int labelNum_;
};

namespace CEhelper
{
	string keyWord2String(keyword Key)
	{
		switch(Key)
		{
			case CLASS:
				return "class";
			case METHOD:
				return "method";
			case FUNCTION:
				return "function";
			case CONSTRUCTOR:
				return "constructor";
			case INT:
				return "int";
			case BOOLEAN:
				return "boolean";
			case CHAR:
				return "char";
			case VOID:
				return "void";
			case VAR:
				return "var";
			case STATIC:
				return "static";
			case FIELD:
				return "field";
			case LET:
				return "let";
			case DO:
				return "do";
			case IF:
				return "if";
			case ELSE:
				return "else";
			case WHILE:
				return "while";
			case RETURN:
				return "return";
			case TRUE:
				return "true";
			case FALSE:
				return "false";
			case null:
				return "null";
			case THIS:
				return "this";
		}
	}
	
	symboltable::Kind keyWord2Kind(keyword Key)
	{
		switch(Key)
		{
			case STATIC:
				return symboltable::STATIC;
			case FIELD:
				return symboltable::FIELD;
			case VAR:
				return symboltable::VAR;
		}
	}
	
	vm::Segment kind2Segment(symboltable::Kind kind)
	{
		switch(kind)
		{
			case symboltable::STATIC:
				return vm::STATIC;
			case symboltable::FIELD:
				return vm::THIS;
			case symboltable::ARG:
				return vm::ARG;
			case symboltable::VAR:
				return vm::LOCAL;
		}
	}
}

CompilationEngine::CompilationEngine(JackTokenizer * JT, VMWriter * VM, SymbolTable * ST)
{
	JT_ = JT;
	VM_ = VM;
	ST_ = ST;
	numArgs_=0;
	labelNum_=0;
	compileClass();
}

CompilationEngine::~CompilationEngine()
{
	VM_->close();
	cout << "Compilation Complete!" << endl;
}

void CompilationEngine::compileClass(void)
{
	JT_->advance();
	assert(JT_->keyWord() == CLASS);
	JT_->advance();
	assert(JT_->tokenType() == IDENTIFIER);
	className_ = JT_->identifier();
	JT_->advance();
	assert(JT_->symbol() == '{');
	JT_->advance();
	while((JT_->tokenType() == KEYWORD) && (JT_->keyWord() == STATIC || JT_->keyWord() == FIELD || JT_->keyWord() == CONSTRUCTOR || JT_->keyWord() == FUNCTION || JT_->keyWord() == METHOD || JT_->keyWord() == VOID))
	{
		switch(JT_->keyWord())
		{
			case STATIC:
			case FIELD:
				compileClassVarDec();
				break;
			case CONSTRUCTOR:
			case FUNCTION:
			case METHOD:
				compileSubroutine();
				break;
			default:
				break;
		}
	}
	assert(JT_->symbol() == '}');
}

void CompilationEngine::compileClassVarDec(void)
{
	string name, type;
	symboltable::Kind kind;
	// kind is either static or field
	kind = CEhelper::keyWord2Kind(JT_->keyWord());
	JT_->advance();

	if(JT_->tokenType() == KEYWORD) 
	{
		type = CEhelper::keyWord2String(JT_->keyWord());
		JT_->advance();
	}
	else if(JT_->tokenType() == IDENTIFIER) // a class name
	{
		type = JT_->identifier();
		JT_->advance();
	}
	while(JT_->getCurrentToken() != ";")
	{
		switch(JT_->tokenType())
		{
			case IDENTIFIER: // var name
				name = JT_->identifier();
				ST_->define(name, type, kind); // add it to symbol table
				break;
			case SYMBOL:
				JT_->updateCurrentToken(); // just eat the symbols
				break;
		}
		if(JT_->getCurrentToken() == "")
			JT_->advance();
	}
	assert(JT_->symbol() == ';');
	JT_->advance();
}

void CompilationEngine::compileSubroutine(void)
{
	ST_->startSubroutine();
	subroutineType_ = JT_->keyWord();
	JT_->advance();
	if(subroutineType_ == METHOD)
		ST_->define("this",className_,symboltable::ARG); // first argument of a method is always "this"
	string returnType;
	if(JT_->tokenType() == KEYWORD)
	{
		returnType = CEhelper::keyWord2String(JT_->keyWord());
		JT_->advance();
	}
	else if(JT_->tokenType() == IDENTIFIER)
	{
		returnType = JT_->identifier();
		JT_->advance();
	}
	if(JT_->tokenType() == IDENTIFIER)
	{
		currentFunctionName_ = className_ + "." + JT_->identifier();
		if(JT_->getCurrentToken() == "")
			JT_->advance();
		else if(JT_->symbol() == '(')
		{
			JT_->updateCurrentToken();
			if(JT_->getCurrentToken()=="")
				JT_->advance();
			compileParameterList();
		}
		if(JT_->getCurrentToken() == ")")
		{
			JT_->updateCurrentToken();
		}
		if(JT_->getCurrentToken() == "")
			JT_->advance();
		if(JT_->getCurrentToken() == "{")
			compileSubroutineBody();
	}
	JT_->advance();
}

void CompilationEngine::compileParameterList(void)
{
	string name, type;
	symboltable::Kind kind = symboltable::ARG;
	int SM = 0;
	while(JT_->getCurrentToken() != ")")
	{
		switch(JT_->tokenType())
		{
			case KEYWORD:
				if(SM == 0) 
				{
					type = CEhelper::keyWord2String(JT_->keyWord());
					JT_->advance();
					SM=1;
				}
				break;
			case IDENTIFIER:
				if(SM==1)
				{
					name = JT_->identifier();
					ST_->define(name, type, kind);
					SM=0;
				}
				else if(SM==0)
				{
					type = JT_->identifier(); // user-defined type
					JT_->advance();
					SM=1;
				}
				break;
			case SYMBOL:
				JT_->updateCurrentToken();
				SM=0;
				break;
		}
		if(JT_->getCurrentToken() == "")
			JT_->advance();
	}
}

void CompilationEngine::compileSubroutineBody(void)
{
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	while(JT_->keyWord() == VAR)
		compileVarDec();
	int nLocals = ST_->varCount(symboltable::VAR);
	VM_->writeFunction(currentFunctionName_, nLocals);
	if(subroutineType_ == CONSTRUCTOR)
	{
		VM_->writePush(vm::CONST,ST_->varCount(symboltable::FIELD));
		VM_->writeCall("Memory.alloc", 1);
		VM_->writePop(vm::POINTER,0);
	}
	else if(subroutineType_ == METHOD) // sets base of this segment properly, so that this one function is available to all instances of the class
	{
		VM_->writePush(vm::ARG, 0); // push "this" of calling object
		VM_->writePop(vm::POINTER, 0); // set "this" of method to the calling object
	}
	if(JT_->keyWord() == LET || JT_->keyWord() == IF || JT_->keyWord() == ELSE || JT_->keyWord() == WHILE || JT_->keyWord() == DO || JT_->keyWord() == RETURN)
		compileStatements();
	assert(JT_->symbol() == '}');
}

void CompilationEngine::compileVarDec(void)
{
	string name, type;
	symboltable::Kind kind;
	// kind is var
	kind = CEhelper::keyWord2Kind(JT_->keyWord());
	JT_->advance();
	int SM=0;
	while(JT_->getCurrentToken() != ";")
	{
		switch(JT_->tokenType())
		{
			case KEYWORD:
				if(SM==0)
				{
					type = CEhelper::keyWord2String(JT_->keyWord());
					JT_->advance();
					SM=1;
					break;
				}
			case IDENTIFIER:
				if(SM==1)
				{
					name = JT_->identifier();
					ST_->define(name, type, kind);
					break;
				}
				else if(SM==0)
				{
					type = JT_->identifier();
					JT_->advance();
					SM=1;
					break;
				}
			case SYMBOL:
				JT_->updateCurrentToken();
				break;
		}
		if(JT_->getCurrentToken() == "")
			JT_->advance();
	}
	if(JT_->getCurrentToken() == ";")
	{
		JT_->advance();
	}
}

void CompilationEngine::compileStatements(void)
{
	while((JT_->tokenType() == KEYWORD) && (JT_->keyWord() == LET || JT_->keyWord() == IF || JT_->keyWord() == ELSE || JT_->keyWord() == WHILE || JT_->keyWord() == DO || JT_->keyWord() == RETURN))
	{
		switch(JT_->keyWord())
		{
			case LET:
				compileLet();
				break;
			case DO:
				compileDo();
				break;
			case WHILE:
				compileWhile();
				break;
			case RETURN:
				compileReturn();
				break;
			case IF:
				compileIf();
				break;
		}
	}
}

void CompilationEngine::compileExpression(void)
{
	compileTerm();
	while(JT_->getCurrentToken().substr(0,1) != ";" && JT_->getCurrentToken().substr(0,1) != "}" && JT_->getCurrentToken().substr(0,1) != "]" && JT_->getCurrentToken().substr(0,1) != ")" && JT_->getCurrentToken().substr(0,1) != ",")
	{
		switch(JT_->tokenType())
		{
			char op;
			case SYMBOL:
				op = JT_->symbol();
				JT_->updateCurrentToken();
				if(JT_->getCurrentToken() == "")
					JT_->advance();
				compileTerm();
				switch(op)
				{
					case '+':
						VM_->writeArithmetic(vm::ADD);
						break;
					case '-':
						VM_->writeArithmetic(vm::SUB);
						break;
					case '*':
						VM_->writeCall("Math.multiply",2);
						break;
					case '/':
						VM_->writeCall("Math.divide",2);
						break;
					case '&':
						VM_->writeArithmetic(vm::AND);
						break;
					case '|':
						VM_->writeArithmetic(vm::OR);
						break;
					case '<':
						VM_->writeArithmetic(vm::LT);
						break;
					case '>':
						VM_->writeArithmetic(vm::GT);
						break;
					case '=':
						VM_->writeArithmetic(vm::EQ);
						break;
					case '~':
						VM_->writeArithmetic(vm::NOT);
						break;
				}
				break;
			default:
				compileTerm();
				break;
		}
		if(JT_->getCurrentToken() == "")
			JT_->advance();
	}
}

void CompilationEngine::compileTerm(void)
{
	string id, str_const;
	switch(JT_->tokenType())
	{
		case IDENTIFIER:
			id = JT_->identifier();
			if(JT_->getCurrentToken() != "")
			{
				if(JT_->symbol() == '(') // subroutine call
				{
					JT_->updateCurrentToken();
					if(JT_->getCurrentToken() == "")
						JT_->advance();
					VM_->writePush(vm::POINTER,0); // pushing this
					compileExpressionList(); // push arguments on stack
					if(JT_->symbol() == ')')
					{
						JT_->updateCurrentToken();
						if(JT_->getCurrentToken() == "")
							JT_->advance();
						if(numArgs_ > 0)
							VM_->writeCall(className_+"."+id, numArgs_+1); // numArgs aids in determining how many arguments there are, add another arg for "this"
						else // The only argument is "this"
							VM_->writeCall(className_+"."+id, 1);
						numArgs_=0; // reset for next call
					}
				}
				else if(JT_->symbol() == '.')
				{
					JT_->updateCurrentToken();
					string subroutineName = JT_->identifier();
					if(ST_->kindOf(id)!=symboltable::NONE) // if its an object stored in symboltable then we will call its own methods
					{
						VM_->writePush(CEhelper::kind2Segment(ST_->kindOf(id)),ST_->indexOf(id)); // pushing object's own reference onto stack
						if(JT_->symbol() == '(')
						{
							JT_->updateCurrentToken();
						}
						if(JT_->getCurrentToken() == "")
							JT_->advance();
						compileExpressionList();
						if(JT_->symbol() == ')')
						{
							JT_->updateCurrentToken();
							if(JT_->getCurrentToken() == "")
								JT_->advance();
						}
						VM_->writeCall(ST_->typeOf(id)+"."+subroutineName,numArgs_+1); // call predefined class's method with its own reference pushed onto stack to operate on its own fields
					}
					else // calling a built in class method, and Name already refers to its type
					{
						if(JT_->symbol() == '(')
						{
							JT_->updateCurrentToken();
						}
						if(JT_->getCurrentToken() == "")
							JT_->advance();
						compileExpressionList(); // push arguments onto stack
						if(JT_->symbol() == ')')
						{
							JT_->updateCurrentToken();
							if(JT_->getCurrentToken() == "")
								JT_->advance();
						}
						VM_->writeCall(id+"."+subroutineName,numArgs_); // call built in method
					}
					numArgs_=0;
				}
				else if(JT_->symbol() == '[')
				{
					JT_->updateCurrentToken();
					if(JT_->getCurrentToken() == "")
						JT_->advance();
					compileExpression();
					VM_->writePush(CEhelper::kind2Segment(ST_->kindOf(id)),ST_->indexOf(id));
					VM_->writeArithmetic(vm::ADD);
					if(JT_->symbol() == ']')
					{
						JT_->updateCurrentToken();
					}
					VM_->writePop(vm::POINTER,1); // pop address pointer into pointer 1
					VM_->writePush(vm::THAT,0); // push the value of the address pointer back onto stack
				}
				else
				{
					VM_->writePush(CEhelper::kind2Segment(ST_->kindOf(id)), ST_->indexOf(id));
				}
			}
			else
			{
				VM_->writePush(CEhelper::kind2Segment(ST_->kindOf(id)), ST_->indexOf(id));
			}
			break;
		case INT_CONST:
			VM_->writePush(vm::CONST, JT_->intVal());
			break;
		case STRING_CONST:
			str_const = JT_->stringVal();
			VM_->writePush(vm::CONST,str_const.length());
			VM_->writeCall("String.new",1);
			for(int i=0;i<str_const.length();i++)
			{
				VM_->writePush(vm::CONST,(int)str_const[i]);
				VM_->writeCall("String.appendChar",2);
			}
			break;
		case KEYWORD: // true, false, null, this will automatically update current token when calling keyWord()
			switch(JT_->keyWord())
			{
				case TRUE:
					VM_->writePush(vm::CONST,0);
					VM_->writeArithmetic(vm::NOT);
					break;
				case FALSE:
				case null:
					VM_->writePush(vm::CONST,0);
					break;
				case THIS:
					VM_->writePush(vm::POINTER,0); // this refers to pointer 0
					break;
			}
			break;
		case SYMBOL:
			if(JT_->symbol() == '(')
			{
				JT_->updateCurrentToken();
				if(JT_->getCurrentToken() == "")
					JT_->advance();
				compileExpression();
				assert(JT_->symbol() == ')');
				JT_->updateCurrentToken();
			}
			else //unaryOp term
			{
				char uOp = JT_->symbol();
				JT_->updateCurrentToken();
				if(JT_->getCurrentToken() == "")
					JT_->advance();
				compileTerm();
				switch(uOp)
				{
					case '-':
						VM_->writeArithmetic(vm::NEG);
						break;
					case '~':
						VM_->writeArithmetic(vm::NOT);
						break;
					default:
						cerr << "Not a unary op" << endl;
						break;
				}
			}
			break;
	}
	if(JT_->getCurrentToken() == "")
		JT_->advance();
}

void CompilationEngine::compileExpressionList(void)
{
	while(JT_->getCurrentToken().substr(0,1) != ")")
	{
		compileExpression();
		numArgs_++;
		if(JT_->getCurrentToken().substr(0,1)==",")
		{
			JT_->updateCurrentToken();
			if(JT_->getCurrentToken() == "")
				JT_->advance();
		}
	}
}

void CompilationEngine::compileDo()
{
	JT_->advance();
	string Name = JT_->identifier(); // either subroutineName or className or varName
	if(JT_->symbol() == '(') // Calling own class method, push this as first argument
	{
		JT_->updateCurrentToken();
		if(JT_->getCurrentToken() == "")
			JT_->advance();
		VM_->writePush(vm::POINTER,0); // pushing this
		compileExpressionList();
		if(JT_->symbol() == ')')
		{
			JT_->updateCurrentToken();
			if(JT_->getCurrentToken() == "")
				JT_->advance();
		}
		if(numArgs_ > 0)
			VM_->writeCall(className_+"."+Name,numArgs_+1);
		else // the only argument is "this"
			VM_->writeCall(className_+"."+Name,1);
		numArgs_=0;
	}
	else if(JT_->symbol() == '.') // Jack method, the first pushed argument must be a reference to the object on which the method is supposed to operate
	{
		JT_->updateCurrentToken();
		string subroutineName = JT_->identifier();
		if(ST_->kindOf(Name)!=symboltable::NONE)
		{
			VM_->writePush(CEhelper::kind2Segment(ST_->kindOf(Name)),ST_->indexOf(Name));
			if(JT_->symbol() == '(')
			{
				JT_->updateCurrentToken();
			}
			if(JT_->getCurrentToken() == "")
				JT_->advance();
			compileExpressionList();
			if(JT_->symbol() == ')')
			{
				JT_->updateCurrentToken();
				if(JT_->getCurrentToken() == "")
					JT_->advance();
			}
			VM_->writeCall(ST_->typeOf(Name)+"."+subroutineName,numArgs_+1);
		}
		else // calling a built in class method, and Name already refers to its type
		{
			if(JT_->symbol() == '(')
			{
				JT_->updateCurrentToken();
			}
			if(JT_->getCurrentToken() == "")
				JT_->advance();
			compileExpressionList();
			if(JT_->symbol() == ')')
			{
				JT_->updateCurrentToken();
				if(JT_->getCurrentToken() == "")
					JT_->advance();
			}
			VM_->writeCall(Name+"."+subroutineName,numArgs_);
		}
		numArgs_=0;
	}
	assert(JT_->symbol() == ';');
	JT_->advance();
	VM_->writePop(vm::TEMP,0);
}

void CompilationEngine::compileLet(void)
{
	JT_->advance();
	string LHSvar = JT_->identifier();
	int isArray = 0;
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	if(JT_->symbol() == '[')
	{
		JT_->updateCurrentToken();
		if(JT_->getCurrentToken() == "")
			JT_->advance();
		compileExpression();
		VM_->writePush(CEhelper::kind2Segment(ST_->kindOf(LHSvar)),ST_->indexOf(LHSvar));
		VM_->writeArithmetic(vm::ADD); // keep address at top of stack until it is needed because if it is popped into pointer 1, it may be overwritten and lost
		if(JT_->symbol() == ']')
		{
			JT_->updateCurrentToken();
			if(JT_->getCurrentToken() == "")
				JT_->advance();
		}
		isArray=1;
	}
	if(JT_->symbol() == '=')
	{
		JT_->updateCurrentToken();
		if(JT_->getCurrentToken() == "")
			JT_->advance();
		compileExpression();
		if(isArray == 1)
			VM_->writePop(vm::TEMP,0); // store result in temp 0
	}
	assert(JT_->symbol() == ';');
	if(isArray==0)
	{
		VM_->writePop(CEhelper::kind2Segment(ST_->kindOf(LHSvar)), ST_->indexOf(LHSvar));
		JT_->advance();
	}
	else
	{
		VM_->writePop(vm::POINTER,1); // pop address pointer into pointer 1
		VM_->writePush(vm::TEMP,0); // push result back onto stack
		VM_->writePop(vm::THAT, 0); // Store right hand side evaluation in THAT 0.
		JT_->advance();
	}
}

void CompilationEngine::compileWhile(void)
{
	stringstream labelTrue, labelFalse;
	labelTrue << "WHILETRUE" << labelNum_;
	labelFalse << "WHILEFALSE" << labelNum_;
	labelNum_++;
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken().substr(0,1) != "(") 
		JT_->advance();
	assert(JT_->symbol() == '(');
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	VM_->writeLabel(labelTrue.str()); // while true label to execute statements again
	compileExpression();
	VM_->writeArithmetic(vm::NOT);
	VM_->writeIf(labelFalse.str()); // If ~(condition) is true, skip the statements and go to the labelFalse, else run statements
	assert(JT_->symbol() == ')');
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	assert(JT_->symbol() == '{');
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	compileStatements();
	VM_->writeGoto(labelTrue.str()); // Go back to labelTrue and check condition
	VM_->writeLabel(labelFalse.str()); // Breaks out of while loop because ~(condition) is true
	assert(JT_->symbol() == '}');
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
}

void CompilationEngine::compileReturn(void)
{
	if(JT_->getCurrentToken() == "return")
	{
		JT_->advance();
		compileExpression();
		assert(JT_->symbol() == ';');
		VM_->writeReturn();
		JT_->advance();
	}
	else if(JT_->getCurrentToken() == "return;")
	{
		VM_->writePush(vm::CONST,0);
		VM_->writeReturn();
		JT_->advance();
	}
}

void CompilationEngine::compileIf(void)
{
	stringstream labelElse, labelContinue;
	labelElse << "IFFALSE" << labelNum_;
	labelContinue << "CONTINUE" << labelNum_;
	labelNum_++;
	JT_->updateCurrentToken();
	JT_->updateCurrentToken(); // done twice since "if" is 2 letters
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	assert(JT_->symbol() == '(');
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	compileExpression();
	VM_->writeArithmetic(vm::NOT);
	VM_->writeIf(labelElse.str());
	assert(JT_->symbol() == ')');
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	assert(JT_->symbol() == '{');
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	compileStatements();
	VM_->writeGoto(labelContinue.str());
	assert(JT_->symbol() == '}');
	JT_->updateCurrentToken();
	if(JT_->getCurrentToken() == "")
		JT_->advance();
	VM_->writeLabel(labelElse.str());
	if(JT_->tokenType() == KEYWORD && JT_->keyWord() == ELSE)
	{
		JT_->updateCurrentToken();
		JT_->updateCurrentToken();
		JT_->updateCurrentToken();
		JT_->updateCurrentToken(); // done 4 times because "else" is 4 letters
		if(JT_->getCurrentToken() == "")
			JT_->advance();
		assert(JT_->symbol() == '{');
		JT_->updateCurrentToken();
		if(JT_->getCurrentToken() == "")
			JT_->advance();
		compileStatements();
		assert(JT_->symbol() == '}');
		JT_->updateCurrentToken();
		if(JT_->getCurrentToken() == "")
			JT_->advance();
	}
	VM_->writeLabel(labelContinue.str());
}

//Compilation

int main(int argc, char *argv[])
{
	if(argc == 1)
		cerr << "Error: No files or directories provided.\n";
	else
	{
		for(int i=2;i<argc;i++)
		{
			string filename = argv[i];
			int dotJack = filename.find(".jack",0);
			if(dotJack == -1) // directory provided
			{
				cout << "Directory support currently not available. Just provide all .jack files separated by a space.\n";
				return(1);
			}
			else
			{
				JackTokenizer JT(filename);
				string outputFile = filename.substr(0,dotJack) + ".vm"; // output a vm file for every jack file.
				VMWriter VM(outputFile);
				SymbolTable ST;
				CompilationEngine CE(&JT,&VM,&ST);
			}
		}
	}
}