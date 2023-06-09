#include "tokens.hpp"
#include <fstream>
#include <iostream>

#define MAX_STRING_LENGTH

using std::cout;
using std::endl;

std::string tokenName(enum tokentype token);
std::string findEscapedString(const std::string& str);
int replaceEscape(std::string& str);

int main()
{
	int token;
  //  std::ofstream cout("out.txt");
	while ((token = yylex())) {
        if (token == ERROR) {
            exit(1);
        }
        if(token==ESCAPE||token==UNCLOSED_STR||token==ERR_CHAR)
        
        {

                if(token==UNCLOSED_STR)
        {
            cout<< "Error unclosed string\n";
            exit(0);
        }
        else if(token==ESCAPE)
        {  std::string str(yytext);
        std::string s=findEscapedString(str);
          
            cout<<"Error undefined escape sequence "<<s<<"\n";
            exit(0);
       
        }
        else{
cout<<"Error ";
  std::string str(yytext);
 if(str.find(':') != std::string::npos)
{ cout<<":"<<"\n";}
else if(str.find('!') != std::string::npos)
          
     { cout<<"!"<<"\n";}     
          
      else if(str.find('\\') != std::string::npos)
          
     { cout<<"\\"<<"\n";}
     
        else if(str.find('#') != std::string::npos)
          
     { cout<<"#"<<"\n";}   

          else if(str.find('_') != std::string::npos)
          
     { cout<<"_"<<"\n";} 

               else if(str.find('.') != std::string::npos)
          
     { cout<<"."<<"\n";}    
     
     else if(str.find('\'') != std::string::npos)
          
     { cout<<"'"<<"\n";}  

     else if(str.find('@') != std::string::npos)
          
     { cout<<"@"<<"\n";}  

 else if(str.find('~') != std::string::npos)
          
     { cout<<"~"<<"\n";}  

      else if(str.find('/') != std::string::npos)
          
     { cout<<"/"<<"\n";}  

  else if(str.find('?') != std::string::npos)
          
     { cout<<"?"<<"\n";}  
            exit(0);

        }

        }
        else 
        {

        cout << yylineno << " " << tokenName((enum tokentype)token) << " ";
        if (token == COMMENT) {
            cout << "//";
        }
     
        else if (token == STRING) {
            std::string str(yytext);
            str = str.substr(0, str.length()-1);
            int len = replaceEscape(str);
            cout << str.substr(0, len);
        }
        else {
            cout << yytext;
        }
        }
        
        cout << "\n";
	}
	return 0;
}


std::string tokenName(enum tokentype token) {
    switch (token) {
        case VOID:
            return "VOID";
        case INT:
            return "INT";
        case BYTE:
            return "BYTE";
        case B:
            return "B";
        case BOOL:
            return "BOOL";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case NOT:
            return "NOT";
        case TRUE:
            return "TRUE";
        case FALSE:
            return "FALSE";
        case RETURN:
            return "RETURN";
        case IF:
            return "IF";
        case ELSE:
            return "ELSE";
        case WHILE:
            return "WHILE";
        case BREAK:
            return "BREAK";
        case CONTINUE :
            return "CONTINUE";
        case SC:
            return "SC";
        case COMMA:
            return "COMMA";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case LBRACE:
            return "LBRACE";
        case RBRACE:
            return "RBRACE";
        case ASSIGN:
            return "ASSIGN";
        case RELOP:
            return "RELOP";
        case BINOP:
            return "BINOP";
        case COMMENT:
            return "COMMENT";
        case ID:
            return "ID";
        case NUM:
            return "NUM";
        case STRING:
            return "STRING";
            case UNCLOSED_STR:
            return "UNCLOSED_STR";
            case ESCAPE:
            return "ESCAPE";
        case OVERRIDE:
            return "OVERRIDE";
    }
    exit(1);
    return "ERROR";
}

std::string findEscapedString(const std::string& str){
    
    std::string return_string="";

    for(int i=0;i<str.length()-1;i++) {
        if(str[i]=='\\'&&(str[i+1]!='r')&&(str[i+1]!='n')&&(str[i+1]!='t'))
        {
            int len;
            if (str[i+1] == 'x') {
                if (str[i+3] == '"') {
                    len = 2;
                } else {
                    len = 3;
                }
            } else {
                len = 1;
            }
            return_string=str.substr(i+1,len);
            return return_string;
        }
   }
   return return_string;
}

int replaceEscape(std::string& str) {
    size_t pos = 0;
    while ((pos = str.find("\\", pos)) != std::string::npos) {
        if (str[pos+1] == '0') {
            return pos;
        }
        else if (str[pos+1] == 'n') {
            str.replace(pos, 2, "\n");
            pos+=1;
        }
        else if (str[pos+1] == 'r') {
            str.replace(pos, 2, "\r");
            pos+=1;
        }
        else if (str[pos+1] == 't') {
            str.replace(pos, 2, "\t");
            pos+=1;
        }
        else if (str[pos+1] == '\"') {
            str.replace(pos, 2, "\"");
            pos+=1;
        }
        else if (str[pos+1] == '\\') {
            str.replace(pos, 2, "\\");
            pos+=1;
        }
        else if (str[pos+1] == 'x') {
            std::string hexval = str.substr(pos+2, 2);
            if (hexval == "00") { return pos; }
            int c_numerical_val = (int)std::stoul(hexval, nullptr, 16);
            char c[2] = {(char)c_numerical_val, '\0'};
            str.replace(pos, 4, c);
            pos++;
        }

    }
    return str.length();
}

