/*
 *	Name: [023] JSON Parse
 *	Author: Mega Show
 *	Date: 2016.12.25
 */

#include "json_parse.h"
#include <stdlib.h>

/* TokenReader */

TokenType peekNextToken(const char *begin){
    switch(*begin){
        case '\"': return JS_STRING;
        case 't':
        case 'f': return JS_BOOLEAN;
        case 'n': return JS_NULL;
        case '{': return JS_OBJECT_BEGIN;
        case '}': return JS_OBJECT_END;
        case '[': return JS_ARRAY_BEGIN;
        case ']': return JS_ARRAY_END;
        case ',': return JS_COMMA;
        case ':': return JS_COLON;
        default: if(*begin >= '0' && *begin <= '9') return JS_NUMBER;
    }
    return ERR;
}

ErrCode skipToken(const char* begin, const char **next_token_begin){}

Number readNumber(const char *begin, const char **next_token_begin){
    while(**next_token_begin >= '0' && **next_token_begin <= '9')
        (*next_token_begin)++;
    if(**next_token_begin == '.')
        (*next_token_begin)++;
    while(**next_token_begin >= '0' && **next_token_begin <= '9')
        (*next_token_begin)++;
    double var = atof(begin);
    return var;
}

String readString(const char *begin, const char **next_token_begin){
    (*next_token_begin)++;
    while(**next_token_begin != '\"')
        (*next_token_begin)++;
    String str;
    str.begin = begin + 1;
    str.end = (*next_token_begin) - 1;
    (*next_token_begin)++;
    return str;
}

Boolean readBoolean(const char *begin, const char **next_token_begin){
    if(*begin == 't'){
        (*next_token_begin) += 4;
        return true;
    }
    (*next_token_begin) += 5;
    return false;
}

int readNull(const char *begin, const char **next_token_begin){
    (*next_token_begin) += 4;
}

/* End TokenReader */

ErrCode jsonParse(const char* json_str){
    TokenStack stack;
    TokenType t;
    TokenStack_init(&stack);
    while(*json_str){
        t = peekNextToken(json_str);
        switch(t){
            case JS_STRING:
                printIndent(stack.top_ptr + 1);
                if(TokenStack_top(&stack) == JS_OBJECT_BEGIN){
                    printKey();
                    TokenStack_push(&stack, JS_KEY);
                }
                else if(TokenStack_top(&stack) == JS_KEY){
                    TokenStack_pop(&stack);
                }
                printString(readString(json_str, &json_str));
                break;
            case JS_NUMBER:
                printIndent(stack.top_ptr + 1);
                if(TokenStack_top(&stack) == JS_KEY)
                    TokenStack_pop(&stack);
                printNumber(readNumber(json_str, &json_str));
                break;
            case JS_BOOLEAN:
                printIndent(stack.top_ptr + 1);
                if(TokenStack_top(&stack) == JS_KEY)
                    TokenStack_pop(&stack);
                printBoolean(readBoolean(json_str, &json_str));
                break;
            case JS_NULL:
                printIndent(stack.top_ptr + 1);
                if(TokenStack_top(&stack) == JS_KEY)
                    TokenStack_pop(&stack);
                readNull(json_str, &json_str);
                printNull();
                break;
            case JS_COMMA:
                json_str++;
                break;
            case JS_ARRAY_BEGIN:
                printIndent(stack.top_ptr + 1);
                json_str++;
                printArray();
                TokenStack_push(&stack, JS_ARRAY_BEGIN);
                break;
            case JS_ARRAY_END:
                json_str++;
                TokenStack_pop(&stack);
                if(TokenStack_top(&stack) == JS_KEY)
                    TokenStack_pop(&stack);
                break;
            case JS_OBJECT_BEGIN:
                printIndent(stack.top_ptr + 1);
                json_str++;
                printObject();
                TokenStack_push(&stack, JS_OBJECT_BEGIN);
                break;
            case JS_OBJECT_END:
                json_str++;
                TokenStack_pop(&stack);
                if(TokenStack_top(&stack) == JS_KEY)
                    TokenStack_pop(&stack);
                break;
            case JS_COLON:
                json_str++;
                break;
        }
    }
    return SUCCESS;
}
