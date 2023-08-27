//OverRancid#0590
#include <bits/stdc++.h>    //Parental Advisory
using namespace std;       //Explicit Content
const int BIAS = 127;

typedef struct badFloat{
    int S, X[8], M[23];
}badFloat;

badFloat simplify(badFloat x){
    if(x.M[22] && x.M[21]){
        badFloat answer;
        answer.S = x.S;
        int i;
        for(i=0; i<8; i++){
            answer.X[i] = x.X[i];
        }
        i = 22;
        while(x.M[i] && i>=0){
            answer.M[i] = 0;
            i--;
        }
        if(i>=0){
            answer.M[i] = 1;
            i--;
            while(i>=0){
                answer.M[i] = x.M[i];
                i--;
            }
            return answer;
        }
    }
    return x;
}   

bool checkForZ(badFloat x){
    for(int i=0; i<8; i++){
        if(x.X[i])
            return false;
    }
    for(int i=0; i<23; i++){
        if(x.M[i])
            return false;
    }
    return true;
}

bool checkForNAN(badFloat a){
    for(int i=0; i<8; i++){
        if(a.X[i]==0)
            return false;
    }
    for(int i=0; i<23; i++){
        if(a.M[i])
            return true;
    }
    return false;
}

void show(badFloat answer){
    if(checkForNAN(answer)){
        cout << "nan\n";
        return;
    }
    cout << answer.S << " ";
    for(int i=0; i<8; i++){
        cout << answer.X[i];
    }cout << " ";
    for(int i=0; i<23; i++){
        cout << answer.M[i];
    }cout << "\n"; 
}

badFloat FP2bF(double x){
    badFloat var;
    x>=0?  var.S = 0: var.S = 1;
    
    x=abs(x);

    int curr = floor(log2(x)), i;
    if(x==0){
        for(i=0; i<8; i++){
            var.X[i] = 0;
        }
        for(i=0; i<23; i++){
            var.M[i] = 0;
        }
        return var;
    }

    x /= pow(2, curr);
    x--;
    curr += BIAS;

    for(i=7; i>=0; i--){
        var.X[i] = curr%2;
        curr/=2;
    }

    double temp = 0.5;
    for(i=0; i<23; i++){
        if(temp<=x){
            var.M[i] = 1;
            x -= temp;
        }
        else{
            var.M[i] = 0;
        }
        temp /= 2;
    }
    return var;
}

badFloat add(badFloat x, badFloat y){
    if(checkForZ(x))
        return y;
    if(checkForZ(y))
        return x;

    badFloat answer;
    int exp_x = -BIAS, exp_y = -BIAS, i;
    for(i=0; i<8; i++){
        exp_x += (1<<(7-i))*x.X[i];
        exp_y += (1<<(7-i))*y.X[i];
    }
    if(exp_y > exp_x){
        badFloat temp_bF = y;
        y = x;
        x = temp_bF;

        int temp = exp_y;
        exp_y = exp_x;
        exp_x = temp;
    }

    if(x.S == y.S){
        answer.S = y.S;
        int exp_ans = exp_x;
        for(i=0; i<23; i++){
            answer.X[i] = x.X[i];
        }
        if(exp_x == exp_y){
            for(i=0; i<23; i++){
                if(x.M[i]==0 && y.M[i]==0){
                    if(i==22){
                        answer.S = 0;
                        for(int i=0; i<8; i++){
                            answer.X[i] = 0;
                        }
                        for(int i=0; i<23; i++){
                            answer.M[i] = 0;
                        }
                        return answer; 
                    }
                    continue;
                }
                else
                    break;
            }
            exp_ans++;
            for(i=7; i>=0; i--){
                if(answer.X[i]==0){
                    answer.X[i]=1;
                    break;
                }
                else{
                    answer.X[i] = 0;
                    continue;
                }
            }
            int tempA[23] = {}, tempB[23] = {};
            for(i=1; i<23; i++){
                tempA[i] = x.M[i-1];
                tempB[i] = y.M[i-1];
            }
            int carry = 0;
            for(i=22; i>=0; i--){
                answer.M[i] = (tempA[i]+tempB[i]+carry)%2;
                carry = (tempA[i]+tempB[i]+carry)/2;
            }
            return answer;
        }

        int holder[23] = {}, difference = exp_x-exp_y;
        holder[difference-1] = 1;      
        for(i=difference ; i<23; i++){
            holder[i] = y.M[i-difference];
        }

        int carry = 0;
        for(i=22; i>=0; i--){
            answer.M[i] = (holder[i]+x.M[i]+carry)%2;
            carry = (holder[i]+x.M[i]+carry)/2;
        }
        if(carry){
            for(i=22; i>=1; i--){
                answer.M[i] = answer.M[i-1];
            }
            answer.M[0] = 0;
            for(i=7; i>=0; i--){
                if(answer.X[i]==0){
                    answer.X[i] = 1;
                    break;
                }
                else{
                    answer.X[i] = 0;
                }
            }
        }
        return answer;        
    }

    if(exp_x==exp_y){
        int larger = 0;
        for(i=0; i<22; i++){
            if(x.M[i] > y.M[i]){
                larger = 2;
                break;
            }
            else if(x.M[i] < y.M[i]){
                larger = 1;
                break;
            }
        }

        if(larger == 0){
            answer.S = 0;
            for(int i=0; i<8; i++){
                answer.X[i] = 0;
            }
            for(int i=0; i<23; i++){
                answer.M[i] = 0;
            }
            return answer; 
        }
        else if(larger == 1){
            badFloat temp_bF = y;
            y = x;
            x = temp_bF;

            int temp = exp_y;
            exp_y = exp_x;
            exp_x = temp;            
        }

        answer.S = x.S;
        for(i=0; i<23; i++){
            if(x.M[i] != y.M[i]){
                ++i;
                break;
            }
        }
        int exp_answer = exp_x - i + BIAS;
        bool seen = false;
        for(i=22; i>=0; i--){
            if(seen){
                y.M[i] ^= 1;
                continue;
            }
            if(y.M[i])
                seen = true;
        }
        int carry = 0;
        vector<int> tmp(23);
        for(i=22; i>=0; i--){
            tmp[i] = (x.M[i] + y.M[i] + carry)/2;
            carry = (x.M[i] + y.M[i] + carry)%2;
        }
        for(i=0; i<23; i++){
            if(tmp[i]==1){
                ++i;
                break;
            }
        }
        int j;
        for(j=0; i<23; i++, j++){
            answer.M[j] = tmp[i];
        }
        for(; j<23; j++){
            answer.M[j] = 0;
        }
        for(i=7; i>=0; i--){
            answer.X[i] = exp_answer%2;
            exp_answer/=2;
        }           
        return answer;
    }
    int holder[23] = {}, difference = exp_x-exp_y;
    holder[difference-1] = 1;      
    for(i=difference ; i<23; i++){
        holder[i] = y.M[i-difference];
    }

    bool met = false;
    for(i=22; i>=0; i--){
        if(met){
            holder[i] ^= 1;
        }
        else if(holder[i]==1){
            met = true;
            continue;
        }
    }
    answer.S = x.S;
    int carry = 0;
    badFloat hhh;
    for(i=22; i>=0; i--){
            hhh.M[i] = (holder[i]+x.M[i]+carry)%2;
            carry = (holder[i]+x.M[i]+carry)/2;
    }
    for(i=0; i<23, !carry; i++){
        if(hhh.M[i]==1){
            ++i;
            break;
        }
    }
    int exp_answer = exp_x - i + BIAS;
    int j;
    for(j=0; i<23; i++, j++){
        answer.M[j] = hhh.M[i];
    }


    for(i=7; i>=0; i--){
        answer.X[i] = exp_answer%2;
        exp_answer/=2;
    }

    for(; j<23; j++){
        answer.M[j] = 0;
    }
    return answer;
}

badFloat sub(badFloat x, badFloat y){
    y.S ^= 1;
    return add(x, y);
}

badFloat mul(badFloat x, badFloat y){
    if(checkForZ(x))
        return x;
    if(checkForZ(y))
        return y;
    badFloat answer;
    int i;
    answer.S = x.S ^ y.S;

    int exp = -BIAS;
    for(i=0; i<8; i++){
        exp += x.X[i] * 1<<(7-i);
        exp += y.X[i] * 1<<(7-i);
    }
    if(exp==-BIAS){
        exp = 0;
    }

    if(x.M[0] && y.M[0])
        exp++;

    for(i=7 ; i>=0; i--){
        answer.X[i] = exp%2;
        exp/=2;
    }

    int64_t num1=1<<24, num2=1<<24;
    for(i=0; i<23; i++){
        num1 += (long long)(x.M[i] * 1<<(23-i));
        num2 += (long long)(y.M[i] * 1<<(23-i));
    }
    int64_t ans = num1*num2;
        
    vector<int> skill;
    while(ans){
        skill.push_back(ans%2);
        ans/=2;
    }
    skill.pop_back();
    for(i=0; i<23; i++){
        answer.M[i] = skill.back();
        skill.pop_back();
    }
    return answer;
}

badFloat divv(badFloat x, badFloat y){
    badFloat answer;
    int i;
    if(checkForZ(y)){
        answer.S = x.S^y.S;
        for(i=0; i<8; i++) answer.X[i] = 1;
        for(i=0; i<23; i++) answer.M[i] = rand()%2;
        return answer;    
    }

    if(checkForZ(x))
        return x;
    
    answer.S = x.S ^ y.S;
    int exp = 0;
    bool zerodetecter = true;
    for(i=0; i<8; i++){
        exp += x.X[i] * 1<<(7-i);
        exp -= y.X[i] * 1<<(7-i);
    }

    long double val_x=1<<24, val_y=1<<24;
    for(i=0; i<23; i++){
        val_x += x.M[i] * 1<<(23-i);
        val_y += y.M[i] * 1<<(23-i);
    }

    long double val_ans = val_x/val_y;
    while(val_ans < 1){
        val_ans*=2;
        exp--;
        if(val_ans==0){
            exp=0;
            val_ans++;
            break;
        }
    }
    val_ans -= 1;
    long double tester = powl(2, -1);
    for(i=0; i<23; i++){
        if(val_ans > tester){
            answer.M[i] = 1;
            val_ans -= tester;
        }
        else{
            answer.M[i] = 0;
        }
        tester/=2;
    }
    exp+=BIAS;
    for(i=7 ; i>=0; i--){
        answer.X[i] = exp%2;
        exp/=2;
    }
    return answer;
}


int main(){
    ios_base::sync_with_stdio(false);
    //cin.tie(NULL); cout.tie(NULL);

    double x, y;
    cin >> x >> y;
    badFloat var1 = simplify(FP2bF(x));
    badFloat var2 = simplify(FP2bF(y));
    
    cout << "Input 1:\t"; show(var1);
    cout << "Input 2:\t"; show(var2);
    cout << "\n";
    cout << "Sum:\t\t"; 
    show(simplify(add(var1, var2)));
    cout << "Difference:\t"; 
    show(simplify(sub(var1, var2)));
    cout << "Product:\t"; 
    show(simplify(mul(var1, var2)));
    cout << "Quotent:\t"; 
    show(simplify(divv(var1, var2)));

    return 0;
}