// Adding BIG Integers
//     In C++ an int is in the range 0 to 65535. But what if we need to add larger integers? Say we want
//     compute the sum 2345566777844567+ 9999988777765768009998. You task in this assignment
//     is to make this happen.
//
//     Write a function
//         string add(string a, string b)
//     where a and b are strings representing integers and the function add(a,b) returns a string
//     representing their sum. Strings a and b can have a maximum of 100 characters.
//
//     Write a main program that loops asking the user for the two numbers a and b. The program
//     should terminate if the user enters “done” what asked for “number” a. 


#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string add(string a, string b)
{
    string x = "";
    int numDigitsA = a.length();
    int numDigitsB = b.length();

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int y = 0;
    for (int i = 0; i < numDigitsA; i++)
    {
        int z = ((a[i] - '0') + (b[i] - '0') + y);
        x.push_back(z % 10 + '0');
        y = z / 10;
    }

    for (int i = numDigitsA; i < numDigitsB; i++)
    {
        int z = ((b[i] - '0') + y);
        x.push_back(z % 10 + '0');
        y = z / 10;
    }

    if (y)
        x.push_back(y + '0');

    reverse(x.begin(), x.end());

    return x;
}

int main()
{
    string a;
    string b;

    while (1)
    {
        cout << "Value of A (tpye 'done' to exit): ";
        cin >> a;

        if (a.compare("done") == 0)
        {
            break;
        }

        cout << "Value of B: ";
        cin >> b;

        cout << add(a, b) << endl;
    }
    return 0;
}
