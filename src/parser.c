#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "parser.h"
#include <math.h>

float parser(){
    char expression[100];
    while(getchar() != '\n');
    printf("Enter your expression: \n");
    fgets(expression,100,stdin);
    const char *pos = expression;
    float result = parser_additive(&pos);
    if (result == INFINITY){
        printf("Error: You cant divide by 0!\n");
    }else{
        printf("Wynik: %.2f\n", result);
    }
    return 0;    
}

void skip_spaces(const char **pos){
    while (**pos == ' '){
        (*pos)++;
    }
}

float parser_number(const char **pos){
    skip_spaces(pos);
    char *end_ptr;
    float number = strtof(*pos, &end_ptr);
    if (end_ptr == *pos){
        printf("Syntax error!");
        return NAN;
    }
    *pos = end_ptr;
    return number;
}

float parser_multiplicative(const char **pos){
    float result_mul = parser_power(pos);
    skip_spaces(pos);
    while (**pos == '*' || **pos == '/'){
        char operator = **pos;
        (*pos)++;
        float next_number = parser_power(pos);
        if (operator == '*'){
            result_mul = result_mul * next_number;
        }else{
            if (next_number == 0){
                return INFINITY;
            }
            result_mul = result_mul / next_number;
        }
    }
    return result_mul;
}

float parser_additive(const char **pos){
    float result_add = parser_multiplicative(pos);
    skip_spaces(pos);
    while (**pos == '+' || **pos == '-'){
        char operator = **pos;
        (*pos)++;
        float next_number = parser_multiplicative(pos);
        if (operator == '+'){
            result_add = result_add + next_number;
        }else{
            result_add = result_add - next_number;
        }
    }
    return result_add;
}

float parser_power(const char **pos){
    float result_pow = parser_primary(pos);
    skip_spaces(pos);
    if (**pos == '^'){
        (*pos)++;
        float power = parser_power(pos);
        result_pow = pow(result_pow,power);
    }
    return result_pow;
}

float parser_primary(const char **pos){
    skip_spaces(pos);
    if (**pos == '-'){
        (*pos)++;
        if (**pos == '\0'){
            return NAN;
        }
        float result1 = parser_primary(pos);
        return -result1;
    }else if (**pos == '+'){
        (*pos)++;
        if (**pos == '\0'){
            return NAN;
        }
        float result2 = parser_primary(pos);
        return result2;
    }else{
        if (**pos == '('){
            (*pos)++;
            if (**pos == '\0'){
                return NAN;
            }
            float result3 = parser_additive(pos);
            if (**pos == ')'){
                (*pos)++;
                return result3;
            }else{
                return NAN;
            }
        }else{
            return parser_number(pos);
        }   
    }
}