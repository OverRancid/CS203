//OverRancid#0590
#include <bits/stdc++.h>    //Parental Advisory
using namespace std;       //Explicit Content
#define ever ;;

int log_2(int x){
    return 31 - __builtin_clz(x);
}

bitset<32> dec2bin(unsigned n){
    //passing unsigned doesn't make a difference because of 'circular' nature of binary notation.
    bitset<32> arr;
    int i;
    for(i=0; i<32; i++){
        arr[i] = n&1;
        n/=2;
    }
    return arr;
}

bool checkOverflow(bitset<32> x, bitset<32> y, bitset<32> sum){
    if(x[31]!=y[31])
        return false;
    if(x[31]!=sum[31])
        return true;
    return false;
    //as discussed in class.
}

int bin2dec(bitset<32> &arr){
    int answer = 0;
    int i;
    for(i=0; i<32; i++){
        if(arr[i]){
            answer += 1<<i;
        }
    }
    //takes advantage of signed integer overflow
    return answer;
}

bitset<32> two_compl(int x){
    //comment out the bitflip code to test mapping function
    bitset<32> answer;
    if(x>=0){
        return dec2bin(x);
    }

    //bit flip method
    answer = dec2bin(-x-1);
    for(int i=0; i<32; i++){
        answer[i] = !answer[i];
    }
    return answer;

    //mapping function method
    long long temp = UINT32_MAX+1 - x; //UINT32_MAX+1 = 1<<32
    return dec2bin(int(temp));

    //both seem equally easy to impliment.    
}

bitset<32> one_compl(int x){
    //comment out the bitflip code to test mapping function
    bitset<32> answer; 
    if(x>=0){
        return dec2bin(x);
    }

    //bitflip method
    answer = dec2bin(-x);
    for(int i=0; i<32; i++){
        answer[i] = !answer[i];
    }
    return answer;

    //mapping function method
    long long temp = UINT32_MAX - x; 
    return dec2bin((int)temp);
    
    //both seem equally easy to impliment.
}

bitset<32> binAdd(int x, int y){
    bitset<32> num1, num2, ans;
    num1 = dec2bin(x);
    num2 = dec2bin(y);
    int carry = 0, i; 
    for(i=0; i<32; i++){
        ans[i] = (num1[i]+num2[i]+carry)%2;
        carry = (num1[i]+num2[i]+carry)/2;
    }
    if(checkOverflow(num1, num2, ans)){
        cout << "Signed Integer Overflow.\natleast 33 bits needed.\n" << endl;
    }
    return ans;
}

//premission was taken from a LA before writing this function this way.
bitset<32> binSub(int x, int y){
    return binAdd(x, -y);
}

void geniusPrint(bitset<32> x){
    for(int i=31; i>=0; i--){
        cout << x[i];
        if(i%4==0){
            cout << ' ';
        }
    }
    cout << endl;
}

void accuracy(){
    int x, y, answer;
    bitset<32> ans;
    x = rand()%1001 - 500;
    y = rand()%1001 - 500;

    int sum = x+y;
    ans = binAdd(x, y);
    answer = bin2dec(ans);
    if(answer!=sum){
        cout << "error in binAdd" << endl;
    }
    else{
        cout << "binAdd exceuted successfully" << endl;
    }

    sum = x-y;
    ans = binSub(x, y);
    answer = bin2dec(ans);
    if(answer!=sum){
        cout << "error in binSub" << endl;
    }
    else{
        cout << "binSub excecuted successfully" << endl;
    } 
}

int main(){
    ios_base::sync_with_stdio(false); //fastIO
    //cin.tie(NULL);  cout.tie(NULL);
    srand(time(nullptr));   
    int ins;
    int n, minDigits;
    bitset<32> answer;
    int ans, x, y;
    //google good variable names;

    cout << "menu:\n(1):1's Complement\n(2):2's Complement\n(3):Addition\n(4):Subtraction\n(5):Accuracy Test\n";

    for(ever){ 
        cout << endl;
        cin >> ins;
        switch(ins){
        case 1:
            cout << "enter a number: ";
            cin >> n;
            n? minDigits=log_2(abs(n))+2: minDigits=1;    
            cout << "Minimum number of digits: " << minDigits << endl;
            answer = one_compl(n);
            cout << "One's Complement: 0b";
            geniusPrint(answer);
            break;
        case 2:
            cout << "enter a number: ";
            cin >> n;
            n? minDigits=log_2(abs(n))+2: minDigits=1; 
            cout << "Minimum number of digits: " << minDigits << endl;
            answer = two_compl(n);
            cout << "Two's Complement: 0b";
            geniusPrint(answer);  
            break;
        case 3:
            cout << "enter two numbers: ";
            cin >> x >> y;
            answer = dec2bin(x); 
            cout << "First Number:\t";
            geniusPrint(answer);
            answer = dec2bin(y);
            cout << "Second Number:\t";
            geniusPrint(answer);
            answer = binAdd(x, y);
            cout << "Binary Sum:\t";
            geniusPrint(answer);
            ans = bin2dec(answer);
            cout << "Decimal Sum:\t" << ans << endl;
            break;
        case 4:
            cout << "enter two numbers: ";
            cin >> x >> y;
            answer = dec2bin(x); 
            cout << "First Number:\t";
            geniusPrint(answer);
            answer = dec2bin(y);
            cout << "Second Number:\t";
            geniusPrint(answer);
            answer = binSub(x, y);
            cout << "Binary Difference:\t";
            geniusPrint(answer);
            ans = bin2dec(answer);
            cout << "Decimal Difference:\t" << ans << endl;
            break;
        case 5:
            accuracy();
            break;
        default:
            return 0;
        }
    }
}