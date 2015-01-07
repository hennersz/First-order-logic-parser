//
//  yourfile.c
//  Parser
//
//  Created by Henry Mortimer on 09/12/2014.
//  Copyright (c) 2014 Henry Mortimer. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yourfile.h"

#define e -1
#define a -2

///////////////////////////////////////////////////////////////

char* segment(char* g, int i ,int j)
{
    int length = j-i;
    char* section = (char*)malloc(sizeof(char)*length);
    
    for (int x = 0; x < length; x++)
    {
        *(section + x) = *(g + i + x);
    }
    return section;
}

//////////////////Char checkers/////////////////////////////////

int varChar(char x)
{
    if (x=='x'|| x=='y'|| x=='z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int quantChar(char x)
{
    if (x == 'A' || x == 'E')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int predChar(char x)
{
    if (x == 'X')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int bc(char x)
{
    if (x == 'v' || x == '^' || x == '>')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int negChar(char x)
{
    if (x == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

////////////////////////////////////////////////////////

int vartonum(char x)
{
    if (x == 'x')
    {
        return 0;
    }
    else if(x == 'y')
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

//////////////binary formula stuff///////////////////////
char bin(char* g)
{
    int brackets = 0, i = 0;
    char connector = 'e';
    
    while (!bc(connector))
    {
        if (*(g+i) == '(')
        {
            brackets++;
        }
        else if ( *(g+i) == ')')
        {
            brackets--;
        }
        else if (brackets == 1 && bc(*(g+i)))
        {
            connector = *(g+i);
        }
        i++;
    }
    return connector;
}

int binAdr(char* g)
{
    int brackets = 0;
    int connector = 0;
    long length = strlen(g);
    
    for (int i = 0; i<length; i++)
    {
        if (*(g+i) == '(')
        {
            brackets++;
        }
        else if ( *(g+i) == ')')
        {
            brackets--;
        }
        else if (brackets == 1 && bc(*(g+i)))
        {
            connector = i;
        }
    }
    
    return connector;
}

char* partOne(char* g)
{
    int i = 1;
    int j = binAdr(g);
    return segment(g,i,j);
}

char* partTwo(char* g)
{
    int i = binAdr(g)+1;
    int j = (int)strlen(g)-1;
    return segment(g, i, j);
}
////////////////////////formula type checkers/////////////////////////////////////////////

int isAtom(char* g)
{
    if(predChar(*g) && *(g+1)=='[' && varChar(*(g+2)) && varChar(*(g+3)) && *(g+4)==']' && strlen(g)==5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isBin(char* g)
{
    long n = strlen(g);
    int binChar = 0;
    int brackets = 0;
    for (int i =0; i<n; i++)
    {
        if (*(g+i)=='(')
        {
            brackets++;
        }
        if (*(g+i)==')')
        {
            brackets--;
        }
        if(bc(*(g+i)) && brackets==1)
        {
            binChar++;
        }
        if (brackets==0 && i<n-1)
        {
            return 0;
        }
    }
    if(brackets==0 && binChar==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isNegation(char* g)
{
    if (negChar(*g))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isQuantifier(char* g)
{
    if (quantChar(*g) && varChar(*(g+1)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isFormula(char* g)
{
    if (isAtom(g))
    {
        return 1;
    }
    else if (isBin(g))
    {
        if(isFormula(partOne(g)) && isFormula(partTwo(g)))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (isNegation(g))
    {
        int end = (int)strlen(g);
        if (isFormula(segment(g,1,end)))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (isQuantifier(g))
    {
        int end = (int)strlen(g);
        if (isFormula(segment(g,2,end)))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int parse(char* g)
{
    if(isFormula(g))
    {
        if(predChar(*g))
        {
            return 1;
        }
        else if (negChar(*g))
        {
            return 2;
        }
        else if (*g == '(')
        {
            return 3;
        }
        else if(*g == 'E')
        {
            return 4;
        }
        else
        {
            return 5;
        }
    }
    else
    {
        return 0;
    }
}


///////////////////////////////// formula evaluation ////////////////////////////////////////

int eval(char *fmla, int edges[no_edges][2], int size, int V[3])
{
    return 0;
}

int evalBound(char *fmla, int edges[no_edges][2], int size, int V[3])
{
    int startNode = V[vartonum(varChar(*(fmla+2)))];
    int endNode = V[vartonum(varChar(*(fmla+3)))];
    for (int i = 0; i < size; i++)
    {
        if(edges[i][0]==startNode && edges[i][1]==endNode)
        {
            return 1;
        }
    }
    return 0;
}
int evalPred(char *fmla, int edges[no_edges][2], int size, int V[3])
{
    return evalBound(fmla, edges, size, V);
}

int evalBin(char *fmla, int edges[no_edges][2], int size, int V[3])
{
    if (bin(fmla)=='^')
    {
        return (eval(partOne(fmla), edges, size, V) && eval(partTwo(fmla), edges, size, V));
    }
    else if (bin(fmla)=='v')
    {
        return (eval(partOne(fmla), edges, size, V) || eval(partTwo(fmla), edges, size, V));
    }
    else
    {
        if(eval(partOne(fmla), edges, size, V) && !eval(partTwo(fmla), edges, size, V))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int evalNeg(char *fmla, int edges[no_edges][2], int size, int V[3])
{
    char* rest = segment(fmla, 1, (int)strlen(fmla));
    return(!eval(rest, edges, size, V));
}

int evalQuant(char *fmla, int edges[no_edges][2], int size, int V[3])
{
    return 0;
}

/////////////////////////////////////// Utility functions///////////////////////////////////////

void printString(char* string)
{
    for(int i = 0; i<strlen(string); i++)
    {
        printf("%c", *(string+i));
    }
}

int* copyVars(int* old)
{
    int* new = malloc(sizeof(int)*3);
    for (int i = 0; i<3; i++)
    {
        *(new+i)= *(old+i);
    }
    return new;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int no_edges;
int main(void)
{
    char *name=malloc(50);
    printf("Enter a formula:");
    scanf("%s", name);
    int p=parse(name);
    switch(p)
    {
        case 0: printf("Not a formula");break;
        case 1: printf("An atomic formula");break;
        case 2: printf("A negated formula");break;
        case 3: printf("A binary connective formula");break;
        case 4: printf("An existential formula");break;
        case 5: printf("A universal formula");break;
        default: printf("Not a formula");break;
    }
    printf("\n");
    return 0;
}