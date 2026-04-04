#include <stdio.h>
#include "calc.h"

float parser(){
    float fn, sn;
    char op;
    while(getchar() != '\n');
    printf("Wpisz wyrażenie: ");
    scanf(" %f %c %f", &fn, &op, &sn);
    if (op == '+'){
        return add(fn,sn);
    }else if(op == '-'){
        return sub(fn,sn);
    }else if(op == '*'){
        return mul(fn,sn);
    }else if(op == '/'){
        return div(fn,sn);
    }
    return 0;
}

void skip_spaces(const char **pos){
    while (**pos == ' '){
        (*pos)++;
    }
}

const char *expr = "    Hello";
skip_spaces(&expr);