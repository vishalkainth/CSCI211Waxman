// Write a program to find and print the first perfect square (i*i) whose last two digits are both odd.

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n;

    for (int i = 0;; i++)
    {
        n = i * i;
        if ((n % 10) / 2 == 1)
        {
            n = n / 10;
            if ((n % 10) / 2 == 1)
            {
                cout << "The two equal integers: " << i << endl;
                cout << "Perfect Square: " << i * i << endl;
                cout << "Last Digit of Perfect Square: " << (i * i) % 10 << endl;
                cout << "Second to Last Digit of Perfect Square: " << (i * i) % 10 % 10 << endl;
                cout << "\nCheck: Square root of the perfect square is " << sqrt(i * i) << ". This problem is impossbile to solve." << endl;
                break;
            }
        }
    }
    return 0;
}
