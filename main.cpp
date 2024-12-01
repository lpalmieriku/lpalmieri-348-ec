/*
Author: Lena Palmieri
KUID: 3115099
Date: 11/30/24
Lab: Extra Credit
Last Modified: 11/30/24
Purpose: Allows the user to enter any integer or float and the program outputs the corresponding double.
*/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

//Returns the number of a given element in a specified string
int count(string line, char elem) {
    int c = 0;
    for (int i=0; i < line.length(); i++) {
        if (line[i] == elem) c++;
    }
    return c;
}

//Returns the index of a given element in a specified string
//If the element is not found, -1 is returned
int find(string line, char elem) {
    for (int i=0; i < line.length(); i++) {
        if (line[i] == elem) return i;
    }
    return -1;
}

//Returns the corresponding double value for a given char
//If the double is not found, then -1 is returned
double findNum(char elem) {
    char nums[] = {'0','1','2','3','4','5','6','7','8','9'};
    double decimals[] = {0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
    for (int i=0; i < 10; i++) {
        if (nums[i] == elem) return decimals[i];
    }
    return -1;
}

//Returns the converted double of a string
//If the string is invalid, -999999.99 is returned
double extractNumeric(string str_num) {
    bool has_sign, has_decimal;
    double num, place;
    char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','+','-'};
    int i, sign, sign_count = count(str_num, '+') + count(str_num, '-'), length = str_num.length();
    //Checks if there are multiple signs or decimal points in the given string
    //Returns invalid string if this is true
    if (sign_count > 1 || count(str_num, '.') > 1) {
        return -999999.99;
    }
    //Checks to see if the first index of the string has a sign value
    //If so the starting index for the number has changed and the sign is added to the double
    if (str_num[0] == '+' or str_num[0] == '-') {
        has_sign = true;
        i = 1;
        sign = str_num[0] == '-' ? -1 : 1;
    }
    //If not, the double is positive and the number starts at index 0
    else {
        has_sign = false;
        sign = 1;
        i = 0;
    }
    //Checks if there is a decimal point in the string
    //If so, the starting power changes because the decimal point counts as a place value
    if (find(str_num, '.') > -1) {
        int n = find(str_num, '.') - i;
        place = pow(10.0, n-1);
    }
    //If no decimal point, than we also account for the sign and adjust the starting place value as needed
    else {
        int n = has_sign ? length-1 : length;
        place = pow(10.0, n-1);
    }
    //Loops through the remaining string to create the double
    for (i; i < length; i++) {
        //Checks if the current character is a letter and if so returns an invalid string
        if (find(letters, str_num[i]) > -1) {
            return -999999.99;
        }
        //Checks if the current character is a decimal point and if so, skip the remaining loop code
        if (str_num[i] == '.') continue;
        //If the input string had a sign, we start at a different place value
        //Each digit we find the double that corresponds to the charcater, multiply it by the current place value and add it to the final double
        //This process is repeated for each digit apart from the first one since we do not add to it
        if (has_sign) {
            num = i==1 ? place*findNum(str_num[i]) : num + place*findNum(str_num[i]);
        }
        else {
            num = i==0 ? place*findNum(str_num[i]) : num + place*findNum(str_num[i]);
        }
        //When we move to the next digit we divide the place by 10 to move to the next place value
        place /= 10;
    }
    return num*=sign;
}

int main()
{
    //Obtains the starting string from the user and stores it in a char array
    char user_num[22];
    cout << "Enter a string (or 'END' to quit): ";
    cin >> user_num;
    //Keeps asking the user for a new double until they enter 'END'
    while (user_num[0] != 'E') {
        //Converts the string to a double and prints it to the user
        double num = extractNumeric(user_num);
        //IF the user gives an invalid string, tell the user it is inavlid, otherwise print it
        if (num != -999999.99) cout << "The input is: " << fixed << setprecision(4) << num;
        else cout << "The input is invalid!";
        cout << "\nEnter a string (or 'END' to quit): ";
        cin >> user_num;
    }
}