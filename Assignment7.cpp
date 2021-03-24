// Redo the 8 queens 1 dimensional array program with backtracking REMOVING ALL "GOTOs" - but implementing the same algorithm

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

bool ok(int q[], int c)
{
    for (int i = 0; i < c; i++)
    {
        if ((q[i] == q[c]) || (abs(q[c] - q[i]) == (c - i)))
        {
            return false;
        }
    }
    return true;
}

void backtrack(int &c)
{
    c--;
    if (c == -1)
        exit(1);
}

void print(int q[])
{
    static int x = 0;
    x++;
    cout << "Number " << x << ":" << endl;
    int board[8][8] = {0};
    for (int i = 0; i < 8; i++)
    {
        board[q[i]][i] = 1;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << board[i][j] << " ";

        cout << endl;
    }
}

int main()
{
    int q[8];
    q[0] = 0;
    int c = 1;
    bool bt = false;
    while (1)
    {
        while (c < 8)
        {
            if (!bt)
                q[c] = -1;
            bt = false;
            while (q[c] < 8)
            {
                q[c]++;
                while (q[c] == 8)
                {
                    backtrack(c);
                    q[c]++;
                }
                if (ok(q, c))
                    break;
            }
            c++;
        }
        print(q);
        backtrack(c);
        bt = true;
    }
    return 0;
}
