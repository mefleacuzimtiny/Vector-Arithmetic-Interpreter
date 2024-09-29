#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int input;
    float calc, upper, lower, soosi;
    cout << "num between 69 and 420? " << endl;
    cin >> input;
    lower = 69;
    upper = 420;
    
    int diff_in = input - lower;
    int diff_lim = upper - lower;
    
    soosi = (diff_in) / (diff_lim);
    calc = (soosi + 1) - (soosi - ((diff_in) % (diff_lim)));
    
    cout << calc << endl;
    
    if (calc == 0){
        cout << "True!" << endl;
    }
    else{
        cout << "False!" << endl;
    }
    
    return 0;
}