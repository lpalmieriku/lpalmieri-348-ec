#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int count(string line, char elem) {
    int c = 0;
    for (int i=0; i < line.length(); i++) {
        if (line[i] == elem) c++;
    }
    return c;
}

int find(string line, char elem) {
    for (int i=0; i < line.length(); i++) {
        if (line[i] == elem) return i;
    }
    return -1;
}

double findNum(char elem) {
    char nums[] = {'0','1','2','3','4','5','6','7','8','9'};
    double decimals[] = {0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
    for (int i=0; i < 10; i++) {
        if (nums[i] == elem) return decimals[i];
    }
    return -1;
}

double extractNumeric(string str_num) {
    bool has_sign, has_decimal;
    double num, place;
    char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','+','-'};
    int i, sign, sign_count = count(str_num, '+') + count(str_num, '-'), length = str_num.length();
    if (sign_count > 1 || count(str_num, '.') > 1) {
        return -999999.99;
    }
    if (str_num[0] == '+' or str_num[0] == '-') {
        has_sign = true;
        i = 1;
        sign = str_num[0] == '-' ? -1 : 1;
    }
    else {
        has_sign = false;
        sign = 1;
        i = 0;
    }
    if (find(str_num, '.') > -1) {
        int n = find(str_num, '.') - i;
        place = pow(10.0, n-1);
    }
    else {
        int n = has_sign ? length-1 : length;
        place = pow(10.0, n-1);
    }
    for (i; i < length; i++) {
        if (find(letters, str_num[i]) > -1) {
            return 999999.99;
        }
        if (str_num[i] == '.') continue;
        if (has_sign) {
            num = i==1 ? place : num + place*findNum(str_num[i]);
        }
        else {
            num = i==0 ? place : num + place*findNum(str_num[i]);
        }
        place /= 10;
    }
    return num*=sign;
}

int main()
{
    string user_num[];
    cout << "Enter a string (or 'END' to quit): ";
    cin >> user_num;
    while (user_num != "END") {
        double num = extractNumeric(user_num);
        if (num != -999999.99) cout << "The input is: " << fixed << setprecision(4) << num;
        else cout << "The input is invalid!";
        cout << "Enter a string (or 'END' to quit): ";
        cin >> user_num;
    }
}