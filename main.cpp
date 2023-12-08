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
char rezultatFinal[400] = "";
int operand = 0, previous = 0;


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
    ////////////////////////////////////////////////////
    ////////TRANNSFORMAREA DIN NR IN CUVinte////////////
    ////////////////////////////////////////////////////

bool verificareIntreg(string a, int lungime)
{
    for (int i = 0; i < lungime; ++i)
        if (a[i] == ',' || a[i] == '.')
            return false;
    return true;
}

bool verificarePerioada(string a, int lungime)
{
    for (int i = 0; i < lungime; ++i)
        if (a[i] == '(')
            return true;
    return false;
}




////////////////////////////////////////////////////
    ///////////TRANSFORMARE NR IN CUVINTE///////////////
    ////////////////////////////////////////////////////

void afisareCaz1(string a, int Start, int Final) {
    switch (a[Start]) {
        case '0':
            strcat(rezultatFinal, "");
            break;
        case '1':
            strcat(rezultatFinal, " o");
            break;
        case '2':
            strcat(rezultatFinal, " doua");
            break;
        case '6':
            strcat(rezultatFinal, " sai");
    }
}

void afisareCifra(const string& a, int Start, int Final) {
    vector<string> sirCifra = {"zero", "unu", "doi", "trei", "patru", "cinci", "sase", "sapte", "opt", "noua"};

    for (int i = Start; i <= Final; ++i) {
        strcat(rezultatFinal, sirCifra[a[i] - '0'].c_str());// am înlocuit sirCifra[a[i] - '0'] cu sirCifra[a[i] - '0'].c_str() pentru a converti
                                                       // string într-un const char* înainte de a folosi strcat().
        if (i != Final) {
            strcat(rezultatFinal, " ");
        }
    }
}

void afisareCaz2(string a, int Start, int Final) {
    switch (a[Start]) {
        case '0':
            strcat(rezultatFinal, "");
            break;
        default:
            strcat(rezultatFinal, " si ");
            afisareCifra(a, Start, Start);
            break;
    }
}

void afisareZecilor(const string& a, int Start, int Final) {
    vector<string> sirZecilor = {"zece", "unsprezece", "doisprezece", "treisprezece", "paisprezece", "cincisprezece", "saisprezece", "saptesprezece", "optsprezece", "nouasprezece"};

    if (a[Start] == '1' && Start < a.size() && Final < a.size()) {
        int num = a[Final] - '0';
        strcat(rezultatFinal, sirZecilor[num].c_str());
    } else {
        switch (a[Start]) {
            case '2':
                afisareCaz1(a, Start, Start);
                strcat(rezultatFinal, "zeci");
                afisareCaz2(a, Final, Final);
                break;
            case '3':
            case '4':
            case '5':
            case '7':
            case '8':
            case '9':
                afisareCifra(a, Start, Start);
                strcat(rezultatFinal, "zeci");
                afisareCaz2(a, Final, Final);
                break;
            case '6':
                afisareCaz1(a, Start, Start);
                strcat(rezultatFinal, "zeci");
                afisareCaz2(a, Final, Final);
                break;
        }
    }
}
void afisareSutelor(string a, int Start, int Final) {
    int nonZerouriPozitie = Final + 1;
    for (int i = Start + 1; i <= Final; ++i) {
        if (a[i] != '0') {
            nonZerouriPozitie = i;
            break;
        }
    }

    switch (a[Start]) {
        case '1':
            afisareCaz1(a, Start, Start);
            strcat(rezultatFinal, " suta ");
            break;
        case '2':
            afisareCaz1(a, Start, Start);
            strcat(rezultatFinal, " sute ");
            break;
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':

            afisareCifra(a, Start, Start);
            strcat(rezultatFinal, " sute ");
            break;
    }

    string nou = a.substr(nonZerouriPozitie, Final - nonZerouriPozitie + 1);

    switch (nou.size()) {
        case 1:
            afisareCifra(nou, 0, nou.size() - 1);
            break;
        case 2:
            afisareZecilor(nou, 0, nou.size() - 1);
            break;
    }
}

void afisareMiilor(const string& a, int Start, int Final) {
    int nonZerouriPozitie = Final + 1;
    for (int i = Start + (Final - 2); i <= Final; ++i) {
        if (a[i] != '0') {
            nonZerouriPozitie = i;
            break;
        }
    }
//10309
    switch (Final + 1) {
        case 4:
            switch (a[Start]) {
                case '1':
                    afisareCaz1(a, Start, Start);
                    strcat(rezultatFinal, " mie ");
                    break;
                case '2':
                    afisareCaz1(a, Start, Start);
                    strcat(rezultatFinal, " mii ");
                break;
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    afisareCifra(a, Start, Start);
                    strcat(rezultatFinal, " mii ");
                    break;
            }
            break;
        case 5:
            switch (a[Start]) {
                case '1':
                    afisareZecilor(a, Start, Start + 1);
                    strcat(rezultatFinal, " mii ");
                    break;
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    afisareZecilor(a, Start, Start + 1);
                    strcat(rezultatFinal, " de mii ");
                    break;
            }
            break;
        case 6:
            switch (a[Start]) {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    afisareSutelor(a, Start, Start + 2);
                    if (a[Start + 1] == '1' || (a[Start + 1] == '0' && a[Start + 2] != '0'))
                        strcat(rezultatFinal, " mii ");
                    else
                        strcat(rezultatFinal, " de mii ");
                    break;
            }
            break;
    }
    string nou = a.substr(nonZerouriPozitie, Final - nonZerouriPozitie + 1);
    int lungime_nou = nou.size();

    switch (lungime_nou) {
        case 1:
            afisareCifra(nou, 0, lungime_nou - 1);
            break;
        case 2:
            afisareZecilor(nou, 0, lungime_nou - 1);
            break;
        case 3:
            afisareSutelor(nou, 0, lungime_nou - 1);
            break;
    }
}
void afisareMilioane(const string& a, int Start, int Final){
    int nonZerouriPozitie = Final + 1;
    for (int i = Start + (Final - 5); i <= Final; ++i)
        if (a[i] != '0')
        {
            nonZerouriPozitie = i;
            break;
        }
    switch (Final + 1)
    {
    case 7:
        switch (a[Start])
        {
        case '1':
            strcat(rezultatFinal," un milion ");
            break;
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            afisareCifra(a, Start, Start);
            strcat(rezultatFinal," milioane");
            break;
        }
        break;
    case 8:
        switch (a[Start])
        {
        case '1':
            afisareZecilor(a, Start, Start + 1);
            strcat(rezultatFinal," milioane");
            break;
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            afisareZecilor(a, Start, Start + 1);
            strcat(rezultatFinal," de milioane");
            break;
        }
        break;
    case 9:
        switch (a[Start])
        {
        case '1':
            afisareSutelor(a, Start, Start + 2);
            if (a[Start + 1] == '1' || (a[Start + 1] == '0' && a[Start + 2] != '0'))
                strcat(rezultatFinal," milioane");
            else
                strcat(rezultatFinal," de milioane");
            break;
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            afisareSutelor(a, Start, Start + 2);
            if (a[Start + 1] == '1' || (a[Start + 1] == '0' && a[Start + 2] != '0'))
                strcat(rezultatFinal," milioane");
            else
                strcat(rezultatFinal," de milioane");
            break;
        }
        break;
    }
    string nou = "";
    Start = nonZerouriPozitie;
    for (int i = Start; i <= Final; ++i)
        nou = nou + a[i];
    int lungime_nou = nou.size();

    switch (lungime_nou) {
        case 1:
            afisareCifra(nou, 0, lungime_nou - 1);
            break;
        case 2:
            afisareZecilor(nou, 0, lungime_nou - 1);
            break;
        case 3:
            afisareSutelor(nou, 0, lungime_nou - 1);
            break;
        case 4:
        case 5:
        case 6:

            afisareMiilor(nou, 0, lungime_nou - 1);
            break;
    }
    }



// int main() {
//     string input1 = "21";
//     string input2 = "123456";

//     afisareMiilor(input2, 0, input2.length() - 1);
//     cout << rezultatFinal <<endl;

//     return 0;
// }


    return true;
