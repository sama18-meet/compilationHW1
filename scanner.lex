
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
string_chars    ([^\\\"\n\r]|(\\\\)|(\\\")|(\\n)|(\\r)|(\\t)|(\\0)|(\\x{hex_digit}{hex_digit}))


%x IN_STRING
%x RIGHT_PAST_NUM 

%%
void                            return VOID;
int                             return INT;
byte                            return BYTE;
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
\+|\-|\*|\\                     return BINOP; /// need test
\/\/[^\n\r]*                    return COMMENT; /// need test
{letter}({letter}|{digit})*     return ID; /// need test
0|([1-9]{digit}*)               {/* BEGIN(RIGHT_PAST_NUM); */return NUM; }
{whitespace}+                   ;
\"                              { BEGIN(IN_STRING); }
.                               { fprintf(stderr, "Error %c\n", *yytext); exit(0); }


<IN_STRING>{string_chars}*      { return STRING; }
<IN_STRING>\"                   { BEGIN(INITIAL); }
<IN_STRING>[\n\r]+              { fprintf(stderr, "Error unclosed string\n"); exit(0); }
<IN_STRING>\\x[^\"]\"           { fprintf(stderr, "Error undefined escape sequence x%c\n", yytext[2]); exit(0); }
<IN_STRING>\\x[^\"][^\"]        { fprintf(stderr, "Error undefined escape sequence x%c%c\n", yytext[2], yytext[3]); exit(0); }
<IN_STRING>\\.                  { fprintf(stderr, "here!Error undefined escape sequence %c\n", yytext[1]); exit(0); }




 /* <RIGHT_PAST_NUM>b               { BEGIN(INITIAL); return B; }
<RIGHT_PAST_NUM>{whitespace}+   BEGIN(INITIAL); /// need test */

%%


