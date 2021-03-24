#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

void backtrack(int &c)
{
    c--;
    if (c == -1)
    {
        exit(1);
    }
}

void print(int q[])
{
    static int x = 0;
    x++;
    cout << "Number " << x << ":" << endl;
    cout << "MP   WP" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " " << i << "    " << q[i] << endl;
    }
    cout << endl;
}

bool ok(int q[], int c)
{

    int mp[3][3] = {
        {0, 2, 1},
        {0, 2, 1},
        {1, 2, 0}};
    int wp[3][3] = {
        {2, 1, 0},
        {0, 1, 2},
        {2, 0, 1}};

    int currentMan, currentWomen, newMan, newWomen;

    for (int i = 0; i < c; i++)
    {
        currentMan = i;
        currentWomen = q[i];
        newMan = c;
        newWomen = q[c];
        if (newWomen == currentWomen)
        {
            return false;
        }
    }

    for (int i = 0; i < c; i++)
    {
        currentMan = i;
        currentWomen = q[i];
        newMan = c;
        newWomen = q[c];

        if (mp[currentMan][currentWomen] > mp[currentMan][newWomen] &&
            wp[newWomen][currentMan] < wp[newWomen][newMan])
        {
            return false;
        }

        if (mp[newMan][currentWomen] < mp[newMan][newWomen] &&
            wp[currentWomen][newMan] < wp[currentWomen][currentMan])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int q[3];
    q[0] = 0;
    int c = 0;
    bool bt = false;

    while (true)
    {
        while (c < 3)
        {
            if (!bt)
                q[c] = -1;
            while (q[c] < 3)
            {
                q[c]++;
                if (q[c] == 3)
                {
                    backtrack(c);
                    continue;
                }
                if (ok(q, c))
                    break;
            }
            c++;
            bt = false;
        }
        print(q);
        backtrack(c);
        bt = true;
    }

    return 0;
}
