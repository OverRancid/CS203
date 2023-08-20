//OverRancid#0590
//#include "fastMath.hpp"
#include <bits/stdc++.h>    //Parental Advisory
using namespace std;       //Explicit Content

string digits = "0123456789ABCDEF";
map<char, int> value;

long long power(int a, int b){
    long long x = 1;
    for(; b; b/=2, a*=a){
        if(b%2)
            x*=a;
    }
    return x;
}

bitset<32> dec2bin(unsigned n){
    bitset<32> arr;
    int i;
    for(i=0; i<32; i++){
        arr[i] = n&1;
        n/=2;
    }
    return arr;
}

unsigned bin2dec(bitset<32> &arr){
    unsigned answer = 0;
    int i;
    for(i=0; i<32; i++){
        if(arr[i]){
            answer += 1<<i;
        }
    }
    return answer;
}

string dec2hex(unsigned n){
    string str;
    while(n){
        str.push_back(digits[n%16]);
        n/=16;
    }
    n = str.size();
    while(n++<8){
        str.push_back('0');
    }
    reverse(str.begin(), str.end());  
    return str;
}

string bin2hex(bitset<32> &arr){
    string str;
    int i, sum;
    for(i=0; i<32; i+=4){
        sum = arr[i] + 2*arr[i+1] + 4*arr[i+2] + 8*arr[i+3];
        str.push_back(digits[sum]);
    }
    reverse(str.begin(), str.end());
    return str;
}

void accuracy(){
    int n = 1000, errCount = 0, x;
    bitset<32> funcGen, stlGen;
    unsigned func_gen, stl_gen, err_count = 0; 
    int i;
    for(i=0; i<n; i++){
        x = rand();
        funcGen = dec2bin(x);
        stlGen = bitset<32>(x);
        if(funcGen!=stlGen){
            errCount++;
            cout << "skill issue at test " << x << '\n';
        }

        func_gen = bin2dec(stlGen);
        stl_gen = stlGen.to_ulong();
        if(func_gen!=stl_gen){
            err_count++;
            cout << "skill issue at test 0b" << stlGen << '\n';
        }
    }
    long double acc = (long double)(1000-errCount)/10;
    long double axx = (long double)(1000-err_count)/10;
    cout << "accuracy dec2bin() = " << acc << "%\n";
    cout << "accuracy bin2dec() = " << axx << "%\n";   
}

unsigned dybase2dec(string str, unsigned base){
    unsigned long long sum = 0LL, n = str.size();
    int i;
    for(i=n-1; i>=0; i--){
        sum += value[str[i]]*power(base, n-1-i);
        if(sum > UINT_MAX){
            cout << "Unsigned Integer Overflow.\n";
            return 0;
        }
    }
    unsigned answer = sum;
    return answer;
}

bitset<32> dybase2bin(string str, unsigned base){
    return dec2bin(dybase2dec(str, base));  //lmao
}

int main(){
    ios_base::sync_with_stdio(false); //fastIO 🤓☝️
    //cin.tie(NULL);  cout.tie(NULL);                  
    srand(time(0)); 
    int i;
    for(i=0; i<16; i++){
        value[digits[i]] = i;
    }
    
    int instruction;
    long long x, limit;
    bitset<32> binx;
    unsigned value;
    string str;

    cout << "Menu:\n(1): dec2bin\n(2): bin2dec\n(3): dec2hex\n(4): bin2hex\n(5): accuracy test\n(6): dybase2dec\n(7): dybase2bin\n(else): break\n";

    while(2==1==0){
        cin >> instruction;
        if(instruction==1){
            cin >> x;
            if(x<0){
                cout << "negative number detected\n\topinion rejected.\n";
            }
            else if(x>UINT_MAX){
                cout << "very large input detected (can't store in 32 bits)\n\tfunction rejected.\n";
            }
            else{
                value = x;
                binx = dec2bin(value);
                cout << "0b" << binx << "\n";
            }
        }
        else if(instruction==2){
            cin >> binx;
            cout << bin2dec(binx) << "\n";
        }
        else if(instruction==3){
            cin >> x;
            if(x<0){
                cout << "negative number detected\n\topinion rejected.\n";
            }
            else if(x>=UINT_MAX){
                cout << "very large input detected (can't store in 32 bits)\n\tfunction rejected.\n";
            }
            else{
                value = x;
                cout << "0x" << dec2hex(value) << "\n"; 
            }
        }
        else if(instruction==4){
            cin >> binx;
            cout << "0x" << bin2hex(binx) << "\n";
        }
        else if(instruction==5){
            accuracy();
        }
        else if(instruction==6){
            cin >> str >> x;
            if(x>16 || x<2){
                cout << "invalid base detected\n\tfunction rejected.\n";
            }
            else{
                limit = power(x, str.size()-1);
                cout << dybase2dec(str, x) << "\n";
            }
        }
        else if(instruction==7){
            cin >> str >> x;
            if(x>16 || x<2){
                cout << "invalid base detected\n\tfunction rejected.\n";
            }
            else{
                limit = power(x, str.size()-1);
                binx = dybase2bin(str, x);
                cout << binx << "\n"; 
            }
        }
        else{
            break;
        }
    }
    cout << endl; //random flush
    return 0;
}   