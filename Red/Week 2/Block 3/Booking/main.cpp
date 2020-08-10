#include <iostream>
#include <map>
#include <set>
#include <deque>

using namespace std;

struct Room
{
    long long int time;
    int client_id;
    int room_count;
};

bool operator<(const Room &lhs, const Room &rhs) // дописать для всей рабочей структуры
{
    return lhs.time < rhs.time;
}

class Booking
{

public:
    Booking() = default;
    ~Booking() = default;
    void Book(const Room &data, const string &hotel)
    {
        auto it = (table[hotel].insert(data)).first;
        users[hotel][data.client_id]++;
        CheckBooks(hotel, it);
    }
    int Clients(const string &hotel)
    {
        int cl = 0;
        // for ()
        return cl;
    }

private:
    map<string, set<Room>> table;
    map<string, map<int, int>> users;
    template <typename Iterator>
    void CheckBooks(const string &hotel, const Iterator &current)
    {
        if (current != table[hotel].begin())
        {
            auto it = (current - 1);
            for (; it != table[hotel].begin(); it--)
            {
                if (it->time + 86400 <= current->time)
                {
                    it++;
                    break;
                }
            }
            for (auto i = table[hotel].begin(); i != it;)
            {
                users[hotel][i->client_id]--;
                if (users[hotel][i->client_id] == 0)
                {
                    i = users[hotel].erase(i->client_id);
                    continue;
                }
                i++;
            }

            table[hotel].erase(table[hotel].begin(), it);
        }
    }
};

int main()
{
    string request;
    int n;
    Booking bk;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> request;
        if (request == "BOOK")
        {
            long long int time;
            string hotel;
            int client_id;
            int room_count;
            cin >> time >> hotel >> client_id >> room_count;
            bk.Book({time, client_id, room_count}, hotel);
        }
    }
}
