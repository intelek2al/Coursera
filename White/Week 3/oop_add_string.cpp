#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SortedStrings {
    public:
        void AddString(const string& s) {
            vect.push_back(s);
        }
        vector<string> GetSortedStrings() {
            SortVect();
            return vect;
        }
    private:
        void SortVect() {
            sort(begin(vect), end(vect));
        }
        vector<string> vect;
};

void PrintSortedStrings(SortedStrings& strings) {
    for (const string& s : strings.GetSortedStrings()) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    SortedStrings strings;
    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);

    strings.AddString("second");
    PrintSortedStrings(strings);
    return 0;
}

