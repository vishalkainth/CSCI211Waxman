#include <iostream>
#include <cmath>

using namespace std;

void backtrack(int &c)
{
    c--;
    if (c == -1)
        exit(1);
}

bool ok(int q[8], int y, int z)
{
    int adj[8][5] = {{-1}, 
                    {0, -1}, 
                    {1, -1}, 
                    {0, 1, 2, -1}, 
                    {1, 2, 3, -1}, 
                    {2, 4, -1}, 
                    {0, 3, 4, -1}, 
                    {3, 4, 5, 6, -1}};
    for (int i = 0; i < y; i++)
        if (z == q[i])
            return false;
    for (int i = 0; i < sizeof(adj[y]); i++)
    {
        int adjacent = adj[y][i];
        if (adjacent == -1)
            break;
        if (abs(q[adjacent] - z) == 1)
            return false;
    }

    return true;
}

void print(int q[8], int x)
{
    cout << "Number " << x << ": " << endl;
    cout << " " << q[1] << q[2] << " " << endl;
    cout << q[0] << q[3] << q[4] << q[5] << endl;
    cout << " " << q[6] << q[7] << " " << endl;
}

int main()
{
    int q[8] = {0};
    int x = 0;
    int c = 1;
    q[0] = 1;
    while (true)
    {
        if (c == 8)
        {
            print(q, ++x);
            backtrack(c);
            continue;
        }
        while (c < 8)
        {
            q[c]++;
            if (q[c] > 8)
            {
                q[c] = 0;
                backtrack(c);
                break;
            }
            if (ok(q, c, q[c]))
            {
                c++;
            }
        }
    }
    return 0;
}