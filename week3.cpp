//OverRancid#0590
#include <bits/stdc++.h>    //Parental Advisory
using namespace std;       //Explicit Content
#define ever ;;

typedef struct badFloat{
    int S, X[8], M[23];
}badFloat;

typedef struct scamHex{
    bool negative;
    string m, d;
}scamHex;

typedef struct BCD{
    vector<bitset<4>> m, d;
}BCD;

const int BIAS = 127;

string digits = "0123456789ABCDEF";
map<char, int> value;
map<int, bitset<4>> grayC;

void show(badFloat answer){
    cout << answer.S << " ";
    for(int i=0; i<8; i++){
        cout << answer.X[i];
    }cout << " ";
    for(int i=0; i<23; i++){
        cout << answer.M[i];
    }cout << "\n"; 
}

void show(scamHex answer){
    if(answer.negative){
        cout << "-";
    }
    answer.m.size()? cout << answer.m: cout << "0";
    cout << ".";
    answer.d.size()? cout << answer.d: cout << "0";
    cout << endl; 
}

void show(BCD answer){
    for(auto x: answer.m){
        cout << x << " ";
    }
    cout << ". ";
    for(auto x: answer.d){
        cout << x << " ";
    }    
    cout << endl;
}

unsigned hex2dec(string str){
    const unsigned base = 16;
    unsigned long long sum = 0LL, n = str.size();
    int i;
    for(i=n-1; i>=0; i--){
        sum += value[str[i]]*((int)(pow(base, n-1-i)+1e-9)); 
    }
    unsigned answer = sum;
    return answer;
}

badFloat FP2bF(double x){
    badFloat var;
    x>=0?  var.S = 0: var.S = 1;
    
    x=abs(x);
    int curr = (int)(log2(x)+1e-9), i;
    x/= (1<<curr);
    x--;
    curr += BIAS;

    for(i=7; i>=0; i--){
        var.X[i] = curr%2;
        curr/=2;
    }

    double temp;
    for(i=0; i<23; i++){
        temp = pow(2, -(i+1));
        if(temp<=x){
            var.M[i] = 1;
            x -= temp;
        }
        else{
            var.M[i] = 0;
        }
    }
    return var;
}

double bF2FP(badFloat var){
    double number = 1;
    int i, exp = 0;
    for(i=0; i<23; i++){
        number += var.M[i] * pow(2, -(i+1));
    }
    for(i=0; i<8; i++){
        exp += var.X[i] * 1<<(7-i);
    }
    if(exp==0){
        //denormal number
        number-=1;
    }
    exp -= BIAS;
    number *= pow(2, exp);
    if(var.S){
        number *= -1;
    }
    return number;
}

badFloat dec2bF(unsigned n){
    badFloat var;
    int i;

    for(i=22; i>=0; i--){
        var.M[i] = n&1;
        n/=2;
    }
    for(i=7; i>=0; i--){
        var.X[i] = n&1;
        n/=2;
    }
    var.S = n&1;
    return var;
}

scamHex FP2sH(double x){
    scamHex hax;
    x>0? hax.negative = false: hax.negative = true;
    x = abs(x);
    int bigG = (int)(log2(x)+1e-9)/4, count;
    double sub = floor(pow(16, bigG)+1e-9);
    while(sub>=1){
        count = 0;
        while(x-sub>=0){
            count++;
            x-=sub;
        }
        if(hax.m.size()||count)
            hax.m.push_back(digits[count]);
        sub/=16;
    }
    double dSub = pow(16, -1);
    while(x>0){
        count = 0;
        while(x-dSub>=0){
            count++;
            x-=dSub;
        }
        hax.d.push_back(digits[count]);
        dSub/=16;
    }
    return hax;
}

bitset<4> notKnapSack(int target, int a3, int a2, int a1, int a0){
    bitset<4> answer = 0;
    int sum = 0, x=1;
    while(sum != target){
        answer = x;
        x++;
        sum =  a0*answer[0] + a1*answer[1] + a2*answer[2] + a3*answer[3];
    }
    return answer;
}

bitset<4> build_helper(int x, int function){
    switch(function){
        case 1:
            return x;
        case 2:
            return x+3;
        case 3:
            return notKnapSack(x, 5, 2, 1, 1);
        case 4:
            return notKnapSack(x, 6, 4, 2, -3);
        case 5:
            return notKnapSack(x, 8, 4, -2, -1);
        case 6:
            return grayC[x];
    }
}

BCD build(string x, int function){
    int i;
    bool dec = false;
    BCD answer;
    for(i=0; i<x.size(); i++){
        if(x[i]=='.'){
            dec = true;
            continue;
        }
        if(!dec){
            answer.m.push_back(build_helper((int)(x[i]-'0'), function));
        }
        else{
            answer.d.push_back(build_helper((int)(x[i]-'0'), function));
        }
    }
    if(answer.m.size()==0){
        answer.m.push_back(build_helper(0, function));
    }
    if(answer.d.size()==0){
        answer.d.push_back(build_helper(0, function));
    }
    return answer;
}

void question_1(){
    long double X;
    double x;
    int inst;
    cout << "(1): 32 bit\n(2): 64 bit" << endl;
    cin >> inst;
    if(inst==1){
        scanf("%f", &x);
        printf("32 bit:\t0x%" PRIX32 "\n", x);
    }
    else{
        scanf("%Lf", &X);
        printf("64 bit:\t0x%" PRIX64 "\n", X);
    }
}

void question_2A(){
    double x;
    cin >> x;
    badFloat answer = FP2bF(x);
    show(answer);
}

void question_2B(){
    string str;
    cin >> str;
    int i;
    //hex -> decimal -> badFloat -> float point -> scamHex
    badFloat answer = (dec2bF(hex2dec(str)));
    double x = bF2FP(answer);
    scamHex var = FP2sH(x);
    cout << "Original form:\t";
    show(var);
    if(var.negative){
        x += pow(16, 8);
        var = FP2sH(x);
        cout << "Altered form:\t";
        show(var);
    }
    fflush(stdout);
}

void question_3(){
    string x;
    cin >> x;  
    BCD var;
    var = build(x, 1);
    cout << "Bin Coded Dec:\t";
    show(var);

    var = build(x, 2);
    cout << "excess-3:\t";
    show(var);

    var = build(x, 3);
    cout << "5211 Code:\t";
    show(var);

    var = build(x, 4);
    cout << "642-3 Code:\t";
    show(var);

    var = build(x, 5);
    cout << "84-2-1 Code:\t";
    show(var);
    
    var = build(x, 6);
    cout << "Gray Code:\t";
    show(var);
}

int main(){
    ios_base::sync_with_stdio(false);
    //cin.tie(NULL); cout.tie(NULL);
    
    for(int i=0; i<16; i++){
       value[digits[i]] = i;
    }
    grayC.insert(make_pair(0, 0));
    grayC.insert(make_pair(1, 1));
    grayC.insert(make_pair(2, 3));
    grayC.insert(make_pair(3, 2));
    grayC.insert(make_pair(4, 6));
    grayC.insert(make_pair(5, 7));
    grayC.insert(make_pair(6, 5));
    grayC.insert(make_pair(7, 4));
    grayC.insert(make_pair(8, 12));
    grayC.insert(make_pair(9, 13));
 
    int instruction;
    cout << "(1): question 1\n(2): question 2a\n(3): question 2b\n(4): question 3\n" << endl;
    for(ever){
        cin >> instruction;
        switch(instruction){
            case 1:
                question_1();
                break;
            case 2:
                question_2A();
                break;
            case 3:
                question_2B();
                break;
            case 4:
                question_3();
                break;
            default:
                return 0;
        }
        cout << endl;
    }
    return 0;
}