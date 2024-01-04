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
char rezultatFinal[400] = "", input[100] = "", separator[]=" ", sirprelucrat[300] = "", propozitie[300], *p, semn;
int i=0,j=0, numbers[100], countNumere = 0, countOperatii = 0, counter = 0, aparitii_zero = 0;
bool isNumber=false, isParenthesis=false, isParanthesisPtSemne=false, DupaVirgula=true, isZero, isRatio=true;
Token item; // Obiect de tip Token -- de ex  a = b + 2;, Tokenurile sunt a, =, b, + și 2
int operand = 0, previous = 0, distanta = 0;
string numar;



stack<Token> stackNumere; // Stiva cu numere
stack<Token> stackOperatii; // Stiva cu operatii

double Sin(double x) { //rotunjim valoarea sinusului
	return (round(sin(x) * 10000000) / 10000000);
}

double Cos(double x) { //rotunjim valoarea cosinusului
	return (round(cos(x) * 10000000) / 10000000);
}

double ctg(double x) { //functie pt calcului cotangentei
	double a = Cos(x);
	double b = Sin(x);
	return (a / b);
}

// Fct pt prioritatea op:1 pentru adunare și scădere, 2 pentru înmulțire și împărțire, etc.
int getPriority(char ch){
    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g') return 4;
    if (ch == '^') return 3;
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    else return 0;
}

//Fct matematica care face calcule
bool mathOperation(stack <Token>& numberStack, stack <Token>& operatorStack, Token& item){
    long double a, b, c;
    a = numberStack.top().value; // luam nr din varful stivei
    numberStack.pop();// Il stergem
    switch (operatorStack.top().type){
    case '+':
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
        c = Sin(a);
        item.type = '0';
        item.value = c;
        numberStack.push(item);
        operatorStack.pop();
        break;

    case 'c':
        c = Cos(a);
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
    if (Sin(a) == 0) {
			cerr << "\nArgument gresit pentru cotangent!\n";
			return false;
		}
		else {
			c = ctg(a);
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

    return true;

    }

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

string formatareZerouri(string a, int lungime)
{
    string format = "";
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i] != '0') break;
        else format += a[i];
    }
    return format;
}

string formatareNumarIntreg(string a, int lungime)
{
    if (verificareIntreg(a, lungime)) return a;
    string format = "";
    for (int i = 0; i < lungime; ++i)
        if (a[i] == '.' || a[i] == ',') return format;
        else format += a[i];
}

string formatareDupaVirgula(string a, int lungime)
{
    string formatAuxiliar = formatareNumarIntreg(a, lungime);
    int numarIntregLungime = formatAuxiliar.size();
    string format = "";
    for (int i = numarIntregLungime + 1; i < lungime; ++i)
        if (a[i] == '(') return format;
        else format += a[i];
    return format;
}

string formatarePerioada(string a, int lungime)
{
    int poz = lungime;
    string format = "";
    for (int i = 0; i < lungime; ++i)
        if (a[i] == '(')
        {
            poz = i + 1;
            break;
        }
    for (int i = poz; i < lungime - 1; ++i)
        format += a[i];
    return format;
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
void afisareNumar(string a, int lungime)
{
    switch (lungime)
    {
    case 1:
        afisareCifra(a, 0, lungime - 1);
        break;
    case 2:
        afisareZecilor(a, 0, lungime - 1);
        break;
    case 3:
        afisareSutelor(a, 0, lungime - 1);
        break;
    case 4:
        afisareMiilor(a, 0, lungime - 1);
        break;
    case 5:
        afisareMiilor(a, 0, lungime - 1);
        break;
    case 6:
        afisareMiilor(a, 0, lungime - 1);
        break;
    case 7:
        afisareMilioane(a, 0, lungime - 1);
        break;
    case 8:
        afisareMilioane(a, 0, lungime - 1);
        break;
    case 9:
        afisareMilioane(a, 0, lungime - 1);
        break;
    }

}


//////////////////////////////////////////////
/////////////////////////////////////////////
////////////////////////////////////////////////////
void cifre(char *p, int &operand, int &precedent)
{
    char cuvant[100];
    strcpy(cuvant,"zero");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+0;
    strcpy(cuvant,"unu");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+1;
    strcpy(cuvant,"doi");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+2;
    strcpy(cuvant,"doua");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+2;
    strcpy(cuvant,"trei");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+3;
    strcpy(cuvant,"patru");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+4;
    strcpy(cuvant,"cinci");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+5;
    strcpy(cuvant,"sase");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+6;
    strcpy(cuvant,"sapte");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+7;
    strcpy(cuvant,"opt");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+8;
    strcpy(cuvant,"noua");
    if (strcmp(p,cuvant)==0)
        precedent=precedent+9;

}

void zecimale(char*p, int &operand, int &precedent)
{
    char cuvant[100];
    short int gasit=0;
    strcpy(cuvant, "zece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+10;
        gasit=1;
    }
    strcpy(cuvant, "unsprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+11;
        gasit=1;
    }
    strcpy(cuvant, "doisprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+12;
        gasit=1;
    }
    strcpy(cuvant, "treisprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+13;
        gasit=1;
    }
    strcpy(cuvant, "paisprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+14;
        gasit=1;
    }
    strcpy(cuvant, "cincisprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+15;
        gasit=1;
    }
    strcpy(cuvant, "saisprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+16;
        gasit=1;
    }
    strcpy(cuvant, "saptesprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+17;
        gasit=1;
    }
    strcpy(cuvant, "optsprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+18;
        gasit=1;
    }
    strcpy(cuvant, "nouasprezece");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+19;
        gasit=1;
    }
    strcpy(cuvant, "douazeci");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+20;
        gasit=1;
    }
    strcpy(cuvant, "treizeci");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+30;
        gasit=1;
    }
    strcpy(cuvant, "patruzeci");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+40;
        gasit=1;
    }
    strcpy(cuvant, "cincizeci");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+50;
        gasit=1;
    }
    strcpy(cuvant, "saizeci");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+60;
        gasit=1;
    }
    strcpy(cuvant, "saptezeci");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+70;
        gasit=1;
    }
    strcpy(cuvant, "optzeci");
    if (strcmp(p,cuvant)==0)
    {
        precedent=precedent+80;
        gasit=1;
    }
    strcpy(cuvant, "nouazeci");
    if (strcmp(p,"nouazeci")==0)
    {
        precedent=precedent+90;
        gasit=1;
    }
    if (gasit==0)
        cifre(p,operand,precedent);
}

void sute(char *p, int &operand, int &precedent, int &intermediar)
{
    char cuvant[100];
    int gasit=0;
    strcpy(cuvant, "suta");
    if (strcmp(p,cuvant)==0)
    {
        intermediar=100;
        gasit=1;
        precedent=0;
    }
    strcpy(cuvant, "sute");
    if (strcmp(p,cuvant)==0)
    {
        intermediar=precedent*100;
        gasit=1;
        precedent=0;
    }

    if (gasit==0)
        zecimale(p,operand,precedent);
}

void mii(char *p, int &operand, int &precedent, int &intermediar)
{
    char cuvant[100];
    int gasit=0;
    strcpy(cuvant, "mie");
    if (strcmp(p,cuvant)==0)
    {
        operand=operand+1000;
        gasit=1;
    }
    strcpy(cuvant, "mii");
    if (strcmp(p,cuvant)==0 && intermediar!=0 || strcmp(p,cuvant)==0 && precedent!=0)
    {
        if (precedent!=0)
        {
            intermediar=intermediar+precedent;
            precedent=0;
        }
        operand=operand+intermediar*1000;
        intermediar=0;
        gasit=1;
    }
    if (gasit==0)
        sute(p,operand,precedent,intermediar);
}

void milioane(char *p, int &operand, int &precedent, int &intermediar)
{
    char cuvant[100];
    int gasit=0;
    strcpy(cuvant, "milion");
    if (strcmp(p,cuvant)==0)
    {
        operand=operand+1000000;
        gasit=1;
    }
    strcpy(cuvant, "milioane");
    if (strcmp(p,cuvant)==0 && intermediar!=0 || strcmp(p,cuvant)==0 && precedent!=0)
    {
        if (precedent!=0)
        {
            intermediar=intermediar+precedent;
            precedent=0;
        }
        operand=operand+intermediar*1000000;
        gasit=1;
        intermediar=0;
    }
    if (gasit==0)
        mii(p,operand,precedent,intermediar);
}



    ////////////////////////////////////////////////
    /////////Transformarea din cuvinte in numar/////
    ////////////////////////////////////////////////


void verificare(char *p) {
    char *operatii[] = {"suma", "adunat", "adunarea", "adunarii", "sumei",
                        "plus", "scader", "diferenta", "diferentei", "minus",
                        "produs", "inmultir", "inmultit", "ori", "putere",
                        "raport", "impartirea", "impartirei", "impartirii", "impartit",
                        "sin", "cos", "tan", "cot", "(", ")", "unu", "doi", "trei",
                        "patru", "cinci", "sase", "sapte", "opt", "noua", "zero", "doua",
                        "zece", "douazeci", "treizeci", "patruzeci", "cincizeci", "saizeci",
                        "saptezeci", "optzeci", "nouazeci", "sut", "mie", "mii", "milion",
                        "milioane", "unsprezece", "doisprezece", "treisprezece", "paisprezece",
                        "cincisprezece", "saisprezece", "saptesprezece", "optsprezece", "nouasprezece",
                        "cu", "?"};

    char *simbol[] = {"+", "+", "+", "+", "+", "plus", "-", "-", "-", "minus",
                      "*", "*", "*", "*", "^", "/", "/", "/", "/", "/", "s", "c",
                      "t", "g", "(", ")", "", "", "", "", "", ",", "", "", "", "",
                      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                      "", "", "", "", "", "", "", "", "", "", "", "", "?"};

    int numOperatii = sizeof(operatii) / sizeof(operatii[0]);

    for (int i = 0; i < numOperatii; ++i) {
        if (strstr(p, operatii[i])) {
            if (strlen(simbol[i]) > 0) {
                strcat(sirprelucrat, simbol[i]);
                strcat(sirprelucrat, separator);
            } else {
                if (strstr(p, ",")) {
                    p[strlen(p) - 1] = '\0';
                    strcat(sirprelucrat, p);
                    strcat(sirprelucrat, separator);
                    strcat(sirprelucrat, ",");
                    strcat(sirprelucrat, separator);
                } else {
                    strcat(sirprelucrat, p);
                    strcat(sirprelucrat, separator);
                }
            }
            break;
        }
    }
}




void PrelucrareaPropozitiei (int variabila){

    p = strtok(propozitie,separator);
    while (p)
    {
        verificare(p);
        p = strtok(NULL, separator);
    }
    //cout<<sirprelucrat<<endl;
    p = strtok(sirprelucrat,separator);
    while (p)
    {
        if (strstr(p,"unu") || strstr(p,"doi") || strstr(p,"trei") || strstr(p,"patru") || strstr(p,"cinci") || strstr(p,"sase") || strstr(p,"sapte") || strstr(p,"opt") || strstr(p,"noua") ||
        strstr(p,"zero") || strstr(p,"doua") || strstr(p,"zece") || strstr(p,"douazeci") || strstr(p,"treizeci") || strstr(p,"patruzeci") || strstr(p,"cincizeci") || strstr(p,"saizeci") ||
        strstr(p,"saptezeci")||strstr(p,"optzeci")||strstr(p,"nouazeci")||strstr(p,"sut")||strstr(p,"mie")||strstr(p,"mii")||strstr(p,"milion")||strstr(p,"milioane")||
        strstr(p,"unsprezece") || strstr(p,"doisprezece") || strstr(p,"treisprezece") || strstr(p,"paisprezece") || strstr(p,"cincisprezece") || strstr(p,"saisprezece") ||
        strstr(p,"saptesprezece") || strstr(p,"optsprezece") || strstr(p,"nouasprezece"))
        {
            if (strstr (p,"zero"))
                isZero=true;
            isNumber=true;
            milioane(p,operand,previous);
        }
        else
        {
            if (strstr(p, "+")) { input[i]='+';i++;}
            if (strstr(p, "-")) { input[i]='-';i++;}
            if (strstr(p, "*")) { input[i]='*';i++;}
            if (strstr(p, "/")) { input[i]='/';i++;}
            if (strcmp(p, "s")==0) { input[i]='s';i++;}
            if (strcmp(p, "c")==0) { input[i]='c';i++;}
            if (strcmp(p, "t")==0) { input[i]='t';i++;}
            if (strcmp(p, "g")==0) { input[i]='g';i++;}
            if (strstr(p, "(")) { input[i]='(';i++;}
            if (strstr(p,",")) if (isNumber) {input[i]='n';i++;}
            if (strstr(p,")"))
            {
                isParenthesis=true;
                isParanthesisPtSemne=true;
                distanta=1;
                if (isNumber)
                {
                    input[i]='n';i++;
                    input[i]=')';i++;
                }
                else {input[i]=')'; i++;}
            }
            if (strstr(p,"?")) if (isNumber) {input[i]='n';i++;}
            if (strstr(p, "plus"))
            {
                if (isNumber)
                {
                    input[i]='n';i++; input[i]='+';i++;
                }
                if (isParanthesisPtSemne && distanta==1)
                {
                    {input[i]='+'; i++; isParanthesisPtSemne=false; distanta=0;}
                }
                else if (distanta>2) {distanta=0; isParanthesisPtSemne=false;}
            }
            if (strstr(p, "minus"))
            {
                if (isNumber)
                {
                    input[i]='n';i++; input[i]='-';i++;
                }
                if (isParanthesisPtSemne && distanta==1)
                {
                    {input[i]='-'; i++; isParanthesisPtSemne=false; distanta=0;}
                }
                else if (distanta>2) {distanta=0; isParanthesisPtSemne=false;}
            }
            if (strstr(p, "ori"))
            {
                if (isNumber)
                {
                    input[i]='n';i++; input[i]='*';i++;
                }
                if (isParanthesisPtSemne && distanta==1)
                {
                    {input[i]='*'; i++; isParanthesisPtSemne=false; distanta=0;}
                }
                else if (distanta>2) {distanta=0; isParanthesisPtSemne=false;}
            }
            if (strstr(p, "impartit"))
            {
                if (isNumber)
                {
                    input[i]='n';i++; input[i]='/';i++;
                }
                if (isParanthesisPtSemne && distanta==1)
                {
                    {input[i]='/'; i++; isParanthesisPtSemne=false; distanta=0;}
                }
                else if (distanta>2) {distanta=0; isParanthesisPtSemne=false;}
            }
            if (strstr(p, "^"))
            {
                if (isNumber)
                {
                    input[i]='n';i++;input[i]='^';i++; goto IesireDinIf;
                }
                if (isParanthesisPtSemne && distanta==1)
                {
                    {input[i]='^'; i++; isParanthesisPtSemne=false; distanta=0;goto IesireDinIf;}
                }
                else {input[i]='^'; i++;}
            }
            IesireDinIf:
            if (strstr(p,"cu"))
            {
                if(isParenthesis) goto OmitemParanteza;
                if (isNumber) {input[i]='n';i++;}
            }
            OmitemParanteza:
            isParenthesis=false;
            isNumber=false;
            if (previous!=0)
                operand=operand+previous;

            if (operand!=0 || isZero)
            {
                isZero=false;
                numbers[counter]=operand;
                counter++;
                operand=0;
                previous=0;

            }

        }
        p=strtok(NULL, separator);
    }

            if (previous!=0)
                operand=operand+previous;

            if (operand!=0||isZero)
            {
                isZero=false;
                numbers[counter]=operand;
                counter++;
                operand=0;
                previous=0;

            }

}


////////////////////////////////////////////////////////////
////////////Calcularea sirului cu operator in fata//////////
// \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ ///

double calcul(int rezultat)
{
        double nr=-1, rez_impartire;
        bool first=true;
        while(countNumere<i)
        {
            if (input[countNumere]=='(')
            {
                countNumere++;
                calcul(rezultat);
            }
            if (input[countNumere]=='+')
            {
                countNumere++;
                if (input[countNumere]=='n')
                {
                    nr=numbers[countOperatii];
                    countNumere++;
                    countOperatii++;
                    IesireSuma:
                    while (input[countNumere]=='n')
                    {
                        nr=nr+numbers[countOperatii];
                        countNumere++;
                        countOperatii++;
                    }
                   // cout<<nr<<endl;
                }
                if (input[countNumere]=='(')
                {
                    if (nr==-1 && first)
                        {
                            nr=0;
                            first=false;
                        }
                        countNumere++;
                        nr=nr+calcul(rezultat);
                        goto IesireSuma;
                }
                if (input[countNumere]==')')
                {
                    countNumere++;
                    return nr;
                }
                return nr;
            }
            if (input[countNumere]=='-')
            {
                countNumere++;
                if (input[countNumere]=='n')
                {
                    nr=numbers[countOperatii];
                    countNumere++;
                    countOperatii++;
                    IesireDiferenta:
                    while (input[countNumere]=='n')
                    {
                        nr=nr-numbers[countOperatii];
                        countNumere++;
                        countOperatii++;
                    }
                  //  cout<<nr<<endl;
                }
                if (input[countNumere]=='(')
                {
                    if (nr==-1 && first)
                        {
                            countNumere++;
                            nr=calcul(rezultat);
                            first=false;
                            goto PrimuElementDiferenta;
                        }
                    countNumere++;
                    nr=nr-calcul(rezultat);
                    PrimuElementDiferenta:
                    goto IesireDiferenta;
                }
                if (input[countNumere]==')')
                {
                    countNumere++;
                    return nr;
                }
                return nr;
            }
            if (input[countNumere]=='*')
            {
                countNumere++;
                if (input[countNumere]=='n')
                {
                    nr=numbers[countOperatii];
                    countNumere++;
                    countOperatii++;
                    IesireProdus:
                    while (input[countNumere]=='n')
                    {
                        nr=nr*numbers[countOperatii];
                        countNumere++;
                        countOperatii++;
                    }
                //    cout<<nr<<endl;
                }
                if (input[countNumere]=='(')
                {
                    if (nr==-1 && first)
                        {
                            nr=1;
                            first=false;
                        }
                        countNumere++;
                        nr=nr*calcul(rezultat);
                        goto IesireProdus;
                }
                if (input[countNumere]==')')
                {
                    countNumere++;
                    return nr;
                }
                return nr;
            }
            if (input[countNumere]=='/')
            {
                countNumere++;
                if (input[countNumere]=='n')
                {
                    nr=numbers[countOperatii];
                    countNumere++;
                    countOperatii++;
                    IesireRaport:
                    while (input[countNumere]=='n')
                    {
                        if (numbers[countOperatii]==0 && aparitii_zero==0)
                        {
                            cout<<"Nu este posibila impartirea la 0";
                            isRatio=false;
                            aparitii_zero++;
                        }
                        nr=nr/numbers[countOperatii];
                        countNumere++;
                        countOperatii++;
                    }
                  //  cout<<nr<<endl;
                }
                if (input[countNumere]=='(')
                {
                        if (nr==-1 && first)
                        {
                            countNumere++;
                            nr=calcul(rezultat);
                            first=false;
                            goto PrimuElementRaport;
                        }
                        countNumere++;
                        rez_impartire=calcul(rezultat);
                        if (rez_impartire==0 && first==false && aparitii_zero==0)
                        {
                            cout<<"Nu este posibila impartirea la 0";
                            isRatio=false;
                            aparitii_zero++;
                        }
                        nr=nr/rez_impartire;
                        rez_impartire=-1;
                        PrimuElementRaport:
                        goto IesireRaport;
                }
                if (input[countNumere]==')')
                {
                    countNumere++;
                    return nr;
                }
                return nr;
            }
            if (input[countNumere]=='^')
            {
                countNumere++;
                if (input[countNumere]=='n')
                {
                    nr=numbers[countOperatii];
                    countNumere++;
                    countOperatii++;
                    IesirePutere:
                    while (input[countNumere]=='n')
                    {
                        nr=pow(nr,numbers[countOperatii]);
                        countNumere++;
                        countOperatii++;
                    }
                  //  cout<<nr<<endl;
                }
                if (input[countNumere]=='(')
                {
                    if (nr==-1 && first)
                    {
                        countNumere++;
                        nr=calcul(rezultat);
                        first=false;
                        goto PrimuElementPutere;
                    }
                    countNumere++;
                    nr=pow(nr,calcul(rezultat));
                    PrimuElementPutere:
                    goto IesirePutere;
                }
                if (input[countNumere]==')')
                {
                    countNumere++;
                    return nr;
                }
                return nr;
            }
        }
}

///////////////////////////////////////////////////////////
/////////Calcularea sirului introdus matematic/////////////
// \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ //

double CalculareaRezultatului (double variabila)
{
        if (input[0]=='+'||input[0]=='-'||input[0]=='*'||input[0]=='/'||input[0]=='^')
    {
        numar = to_string(calcul(1));
        //cout<<numar<<endl;

    }
    else{
    i=0;j=0;

    char Ch; //variabila in care se inscrie caracterul curent prelucrat
    double value;

    while (1) { //Rezolvarea exercitiului prin metoda 1
        Ch = input[i]; i++; //verificam primul simbol
        if (Ch == '\n')break; //daca ajungem la sfarsitul randului iesim din while
        if (Ch == ' ') { //ignorarea spatiilor
            //cin.ignore();
            continue;
        }

            if (Ch == 's') { //daca am citit functia sin
                item.type = 's';
                item.value = 0;
                stackOperatii.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (Ch == 'c') { //daca am citit functia cos
                item.type = 'c';
                item.value = 0;
                stackOperatii.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (Ch == 't') { //daca am citit functia tangenta
                item.type = 't';
                item.value = 0;
                stackOperatii.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
            if (Ch == 'g') { //daca am citit functia cotangenta
                item.type = 'g';
                item.value = 0;
                stackOperatii.push(item); //operatia se insereaza in stiva cu operatii
                continue;
            }
        if (Ch == 'n') { //daca am citit un numar
            value=numbers[j]; j++;
            item.type = '0';
            item.value = value;
            stackNumere.push(item); //numarul se insereaza in stiva cu numere
            continue;
        }
        if (Ch == '+' || Ch == '-' || Ch == '*' || Ch == '/' || Ch == '^') { //daca am citit o operatie
            if (stackOperatii.size() == 0) { //daca stiva cu operatii este vida
                item.type = Ch;
                item.value = 0;
                stackOperatii.push(item); //operatia se insereaza in stiva cu operatii
                //cin.ignore();
                continue;
            }
            if (stackOperatii.size() != 0 && getPriority(Ch) > getPriority(stackOperatii.top().type)) { //daca stiva nu este vida, insa prioritatea operatiei curente este mai mare decat cea din varful stivei
                item.type = Ch;
                item.value = 0;
                stackOperatii.push(item); //operatia se insereaza in stiva cu operatii
                //cin.ignore();
                continue;
            }
            if (stackOperatii.size() != 0 && getPriority(Ch) <= getPriority(stackOperatii.top().type)) {//daca stiva nu este vida, insa prioritatea operatiei curente e mai mica sau egala cu cea din varful stivei
                if (mathOperation(stackNumere, stackOperatii, item) == false) { //daca funtia returneaza 'false' incetam lucrul
                    system("pause");
                    return 0;
                }
                item.type = Ch;
                item.value = 0;
                stackOperatii.push(item); //operatia se insereaza in stiva cu operatii
                //cin.ignore();
                continue;
            }
        }
        if (Ch == '(') { //daca am citit paranteza deschisa
            item.type = Ch;
            item.value = 0;
            stackOperatii.push(item); //operatia se insereaza in stiva cu operatii
            //cin.ignore();
            continue;
        }
        if (Ch == ')') { //daca am citit paranteza inchisa
            while (stackOperatii.top().type != '(') {
                if (mathOperation(stackNumere, stackOperatii, item) == false) { //daca functia returneaza 'false' incetam calculul
                    system("pause");
                    return 0;
                }
                else continue; //daca totul e bine
            }
            stackOperatii.pop();
            //cin.ignore();
            continue;
        }
        else { //daca am citit un caracter straniu
            //cout << "\nAti introdus expresia gresit\n";
            //system("pause");
            break;//return 0;
        }
    }
    while (stackOperatii.size() != 0) { //apelam functia matematica pana cand in stiva cu operatii nu raman 0 elemente
    if (mathOperation(stackNumere, stackOperatii, item) == false) { //daca functia returneaza 'false' incetam calculul
        system("pause");
        return 0;
    }
    else continue; //daca totul e bine
    }
    //cout << "Raspunsul: " << Stack_n.top().value << endl; //afisam rezultatul

    numar = to_string(stackNumere.top().value);
    //cout<<numar<<endl;
    }
}

void TransformareNumarInCuvinte (int variabila)
{
    //string numar;//=to_string(stackNumere.top().value);
    if (numar[0] == '-')
    {
        strcat(rezultatFinal, " minus");
        numar.erase(0, 1);
    }

    int lungime = numar.size();
    //cout<<lungime<<endl;
    lungime=lungime-1;
        while (numar[lungime]=='0' || numar[lungime]=='.' || numar[lungime]==',') //se inlatura zerourile in plus de dupa virgula
        {
            //cout<<"Valoarea actuala: "<<numar[lungime]<<endl;
            if (numar[lungime]=='.' || numar[lungime]==',')
            {
                    numar.erase(lungime,1);
                    goto Virgula;
            }
            numar.erase(lungime,1);
            //cout<<numar<<endl;
            lungime--;
        }
    Virgula:
    //cout<<"Numar final: "<<numar<<endl;
    //cout<<lungime<<endl;
    lungime=lungime+1;
    //cout<<"Lungime finala: "<<lungime<<endl;

    string numarIntreg = formatareNumarIntreg(numar, lungime);
    string numarDupaVirgula = formatareDupaVirgula(numar, lungime);
    string perioada = formatarePerioada(numar, lungime);
    afisareNumar(numarIntreg, numarIntreg.size());
    if (!verificareIntreg(numar, lungime))
    {
        strcat(rezultatFinal, " virgula");
        int lungimeNumarDupaVirgula = numarDupaVirgula.size();
        while (lungimeNumarDupaVirgula)
        {
            string zerouri = formatareZerouri(numarDupaVirgula, numarDupaVirgula.size());
            int lungimeZerouri = zerouri.size();
            while (lungimeZerouri--)
                strcat(rezultatFinal, " zero");
            numarDupaVirgula.erase(0, zerouri.size());
            lungimeNumarDupaVirgula = numarDupaVirgula.size();
            int lungimeNou = min(lungimeNumarDupaVirgula, 9);
            string nou = "";
            for (int i = 0; i < lungimeNou; ++i)
                nou += numarDupaVirgula[i];
            afisareNumar(nou, nou.size());
            numarDupaVirgula.erase(0, nou.size());
            lungimeNumarDupaVirgula = numarDupaVirgula.size();
        }

        if (verificarePerioada(numar, lungime))
        {
            strcat(rezultatFinal, " si");
            int lungimeNumarPerioada = perioada.size();
            while (lungimeNumarPerioada)
            {
                string zerouri = formatareZerouri(perioada, perioada.size());
                int lungimeZerouri = zerouri.size();
                while (lungimeZerouri--)
                    strcat(rezultatFinal, " zero");
                perioada.erase(0, zerouri.size());
                lungimeNumarPerioada = perioada.size();
                int lungimeNou = min(lungimeNumarPerioada, 9);
                string nou = "";
                for (int i = 0; i < lungimeNou; ++i)
                    nou += perioada[i];
                afisareNumar(nou, nou.size());
                perioada.erase(0, nou.size());
                lungimeNumarPerioada = perioada.size();
            }
            strcat(rezultatFinal, " in perioada");
        }
    }
}

int main(){


    cout<<"Introduceti propozitia: "<<endl;

    cin.getline(propozitie,500);

    for(i=0;i<strlen(propozitie);i++)
        propozitie[i]=tolower(propozitie[i]);
    i=0;
    PrelucrareaPropozitiei (1);

    CalculareaRezultatului (1);

    TransformareNumarInCuvinte (1);

    if (isRatio)
        cout<<"Raspunsul:"<<rezultatFinal<<endl;




    return 0;
}
