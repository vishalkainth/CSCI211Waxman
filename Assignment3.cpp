// PDF File Provided

#include <iostream>
#include <string>

using namespace std;

bool error(string order)
{
    string team = "";
    for (int i = 0; i < order.size(); i++)
        if (team.find(order[i] > order.size()))
            team = team + order[i];

    if (team.size() <= 1)
        return true;

    int *count = new int[team.size()]();

    for (int i = 0; i < order.size(); i++)
        for (int j = 0; j < team.size(); j++)
            if (order[i] == team[j])
                count[j]++;

    for (int i = 1; i < team.size(); i++)
        if (count[i] != count[0])
        {
            return true;
        }

    return false;
}

void result(string order)
{
    string team = "";

    for (int i = 0; i < order.size(); i++)
        if (team.find(order[i]) > order.size())
            team = team + order[i];

    cout << "There are " << team.size() << " teams." << endl;
    cout << "Each team has " << order.size() / team.size() << " runners." << endl;
    int *count = new int[team.size()]();

    for (int i = 0; i < order.size(); i++)
        for (int j = 0; j < team.size(); j++)
            if (order[i] == team[j])
                count[j] = count[j] + i + 1;

    cout << "Team Score" << endl;

    for (int i = 0; i < team.size(); i++)
        cout << " " << team[i] << " " << (double)count[i] / (order.size() / team.size()) << endl;

    double win = 100;

    int winner = 0;

    for (int i = 0; i < team.size(); i++)
        if (win > (double)count[i] / (order.size() / team.size()))
        {
            win = (double)count[i] / (order.size() / team.size());
            winner = i;
        }

    cout << "The winning team is team " << team[winner] << " with a score of " << win << "." << endl;
}

int main()
{
    string order;

    cout << "Write the results of the race (uppercase only): ";
    cin >> order; 

    while (error(order))
    {
        cout << "Error! Teams do not have the same number of runners. Try again: ";
        cin >> order;
    }

    result(order);
    return 0;
}
