
CURRENT BUG: DOESN'T RECOGNIZE EMPTY STRINGS
%{
/* Declarations section */
#include "tokens.hpp"
#include <stdio.h>
%}

%option noyywrap
%option yylineno

whitespace      ([\t\r\n ])
digit           ([0-9])
letter          ([a-zA-Z])
hex_digit       ([0-9A-Fa-f])
string_chars    ([^\\\"\n\r]|(\\\\)|(\\\")|(\\n)|(\\r)|(\\t)|(\\0)|(\\x[0-7]{hex_digit}))


%x IN_STRING
%x RIGHT_PAST_NUM 

%%
void                            return VOID;
int                             return INT;
byte                            return BYTE;
b                               return B;
bool                            return BOOL;
override                        return OVERRIDE;
and                             return AND;
or                              return OR;
not                             return NOT;
true                            return TRUE;
false                           return FALSE;
return                          return RETURN;
if                              return IF;
else                            return ELSE;
while                           return WHILE;
break                           return BREAK;
continue                        return CONTINUE ;
;                               return SC;
,                               return COMMA;
\(                              return LPAREN;
\)                              return RPAREN;
\{                              return LBRACE; // might need care
\}                              return RBRACE; // might need care
=                               return ASSIGN;
==|!=|<|>|<=|>=                 return RELOP; /// need test
\+|\-|\*|\/                     return BINOP; /// need test
\/\/[^\n\r]*                    return COMMENT; /// need test
{letter}({letter}|{digit})*     return ID; /// need test
0|([1-9]{digit}*)               return NUM;
{whitespace}+                   ;
\"                              { BEGIN(IN_STRING); }
.                               { return ERROR; exit(0); }



<IN_STRING>({string_chars}|{letter})*\"    { BEGIN(INITIAL); return STRING; }
<IN_STRING>({string_chars}|{letter})*[\n\r]+              { return UNCLOSED_STR; }
<IN_STRING>({string_chars}|{letter})*\\[^rnt]             {return ESCAPE; }
<IN_STRING>({string_chars}|{letter})*\\x(([^0-7][hex_digit])|([0-7][^hex_digit])|([^0-7][^hex_digit])) {return ESCAPE;}
<IN_STRING>.                  { return UNCLOSED_STR; }



 /* <RIGHT_PAST_NUM>b               { BEGIN(INITIAL); return B; }
<RIGHT_PAST_NUM>{whitespace}+   BEGIN(INITIAL); /// need test */

%%




