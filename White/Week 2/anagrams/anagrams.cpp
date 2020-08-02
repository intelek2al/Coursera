#include <iostream>
#include <map>
#include <vector>

using namespace std;

map<char, int> GetCountedMap(const string word) {
    map<char, int> cont;
    
    for (auto c : word) {
        cont[c]++;
    }
    return cont;
}
bool IsAnag(const vector<string> words) {
    vector<map<char, int>> cont;
    
    for (auto w : words)
        cont.push_back(GetCountedMap(w));
    return cont[0] == cont[1];
}

void ReadWords(vector<string>& s) {
    string w;
    
    s.clear();
    cin >> w;
    s.push_back(w);
    cin >> w;
    s.push_back(w);
}

int main()
{
    int n;
    map<bool, string> res_map = {{true, "YES"}, {false, "NO"}};
    vector<string> words(2); 
    
    cin >> n;
    vector<bool> result;
    
    for (int i = 0; i < n; i++) {
        ReadWords(words);
        result.push_back(IsAnag(words));
    }
    for (auto b : result) {
        cout << res_map[b] << endl;
    }
    return 0;
}
