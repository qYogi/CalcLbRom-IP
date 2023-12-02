#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stack>
#include <bits/stdc++.h>
#include <graphics.h>
#include <math.h>

using namespace std;

struct Token {
    long double value; // vvaloate doar pt numere
    char type; // 0 pt numere, "operatori (+/- etc)" pt adunare, scadere etc
};


Token Item; // Obiect de tip Token -- de ex  a = b + 2;, Tokenurile sunt a, =, b, + și 2





stack<Token> stackNumere; // Stiva cu numere
stack<Token> stackOperatii; // Stiva cu operatii

// Fct pt prioritatea op:1 pentru adunare și scădere, 2 pentru înmulțire și împărțire, etc.
int getPriority(char ch){
    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g') return 4;
    if (ch == '^') return 3;
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    else return 0;
} 

//Fct matematica care face calcule
bool mathOperation(stach <Token>& numberStack, stack <Token>& operatorStack, Token& item){
    long double a, b, c;
    a = numberStack.top().value; // luam nr din varful stivei
    numberStack.pop();// Il stergem
    switch (operatorStack.top().type){
    case '+';
        b = numberStack.top().value;
        numberStack.pop();
        c = a + b;
        item.type = '0';
        item.value = c;
        numberStack.push(item);//rezultatul operatiei se insereaza inapoi in stiva
        operatorStack.pop();
        break;
    case '-':
        b = numberStack.top().value;
        numberStack.pop();
        c = b - a;
        item.type = '0';
        item.value = c;
        numberStack.push(item);
        operatorStack.pop();
        break;

    case '*':
        b = numberStack.top().value;
        numberStack.pop();
        c = a * b;
        item.type = '0';
        item.value = c;
        numberStack.push(item);
        operatorStack.pop();
        break;

    case '^':
        b = numberStack.top().value;
        numberStack.pop();
        c = pow(b, a);
        item.type = '0';
        item.value = c;
        numberStack.push(item);
        operatorStack.pop();
        break;

    case '/':
        b = numberStack.top().value;
        if (a == 0) {
            cerr << "\nNu putem împărți la 0!\n";
            return false;
        }
        else {
            numberStack.pop();
            c = (b / a);
            item.type = '0';
            item.value = c;
            numberStack.push(item);
            operatorStack.pop();
            break;
        }
    case 's':
        c = RoundSin(a);
        item.type = '0';
        item.value = c;
        numberStack.push(item);
        operatorStack.pop();
        break;

    case 'c':
        c = RoundCos(a);
        item.type = '0';
        item.value = c;
        numberStack.push(item);
        operatorStack.pop();
        break;
    case 't':
    if (cos(a) == 0) {
        cerr << "\nTangenta nu poate fi calculată pentru acest unghi!\n";
        return false;
    } else {
        c = tan(a);
        item.type = '0';
        item.value = c;
        numberStack.push(item);
        operatorStack.pop();
        break;
    }
    case 'g':
    c = Cot(a);
        item.type = '0';
        item.value = c;
        numberStack.push(item);
        operatorStack.pop();
        break;

    }
    default:
        cerr << "\nEroare: Operatot necunoscut!\n";
        return false;
        break;
    }

    return true;
