// Complete the "dumb" 8 queens program that we looked at in lecture. Use the 1 dimensional array representation.

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

bool ok(int q[8])
{
    for (int c = 7; c > 0; c--)
    {
        int r = 0;
        r = q[c];

        for (int i = 1; i <= c; i++)
        {
            if (q[c - i] == r)
                return false;
            else if (q[c - i] == r - i)
                return false;
            else if (q[c - i] == r + i)
                return false;
        }
    }
    return true;
}

void print(int q[8], int x)
{
    cout << "Number " << x << ":" << endl;
    int board[8][8] = {0};

    for (int j = 0; j < 8; j++)
    {
        board[q[j]][j] = 1;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{

    int q[8] = {0};
    int x = 1;
    for (int i0 = 0; i0 < 8; i0++)
        for (int i1 = 0; i1 < 8; i1++)
            for (int i2 = 0; i2 < 8; i2++)
                for (int i3 = 0; i3 < 8; i3++)
                    for (int i4 = 0; i4 < 8; i4++)
                        for (int i5 = 0; i5 < 8; i5++)
                            for (int i6 = 0; i6 < 8; i6++)
                                for (int i7 = 0; i7 < 8; i7++)
                                {
                                    q[0] = i0;
                                    q[1] = i1;
                                    q[2] = i2;
                                    q[3] = i3;
                                    q[4] = i4;
                                    q[5] = i5;
                                    q[6] = i6;
                                    q[7] = i7;

                                    if (ok(q))
                                        print(q, x++);

                                    q[0] = -1;
                                    q[1] = -1;
                                    q[2] = -1;
                                    q[3] = -1;
                                    q[4] = -1;
                                    q[5] = -1;
                                    q[6] = -1;
                                    q[7] = -1;
                                }
    return 0;
}
