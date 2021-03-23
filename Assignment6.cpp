// Complete the 8 queens 1 dimensional array program with backtracking that we worked on in class.

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int main()
{
    int q[8], c = 0;
    q[0] = 0;
    int x = 0;

nc:
    c++;
    if (c == 8)
        goto print;
    q[c] = -1;

nr:
    q[c]++;
    if (q[c] == 8)
        goto backtrack;
    for (int i = 0; i < c; i++)
    {
        if ((q[i] == q[c]) || (c - i == abs(q[c] - q[i])))
            goto nr;
    }
    goto nc;

backtrack:
    c--;
    if (c == -1)
        return 0;
    goto nr;

print:
    x++;
    cout << "Number " << x << ":" << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (q[i] == j)
            {
                cout << 1;
            }
            else
            {
                cout << 0;
            }
        }
        cout << endl;
    }
    cout << endl;
    goto backtrack;
}
