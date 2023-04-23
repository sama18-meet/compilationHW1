#include "tokens.hpp"
#include <fstream>
#include <iostream>


std::string tokenName(enum tokentype token);
void findAndReplace(std::string& str, const std::string& find, const std::string& replace);
void fixASCIIEscapeSeq(std::string& str);

int main()
{
	int token;
    std::ofstream outfile("out.txt");
	while ((token = yylex())) {
        if (token == ERROR) {
            exit(1);
        }
        outfile << yylineno << " " << tokenName((enum tokentype)token) << " ";
        if (token == COMMENT) {
            outfile << "//";
        }
        else if (token == STRING) {
            std::string str(yytext);
            findAndReplace(str, "\\n", "\n");
            findAndReplace(str, "\\r", "\r");
            findAndReplace(str, "\\t", "\t");
            findAndReplace(str, "\\\\", "\\");
            findAndReplace(str, "\\\"", "\"");
            fixASCIIEscapeSeq(str);


            outfile << str;
        }
        else {
            outfile << yytext;
        }
        outfile << "\n";
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
        case OVERRIDE:
            return "OVERRIDE";
    }
    exit(1);
    return "ERROR";
}


void findAndReplace(std::string& str, const std::string& find, const std::string& replace) {
    size_t pos = 0;
    while ((pos = str.find(find, pos)) != std::string::npos) {
         str.replace(pos, find.length(), replace);
         pos += replace.length();
    }
}

void fixASCIIEscapeSeq(std::string& str) {
    size_t pos = 0;
    while ((pos = str.find("\\x", pos)) != std::string::npos) {
        std::string hexval = str.substr(pos+2, pos+4);
        int c_numerical_val = (int)std::stoul(hexval, nullptr, 16);
        char c[2] = {(char)c_numerical_val, '\0'};
        str.replace(pos, 4, c);
        pos++;
    }
}
