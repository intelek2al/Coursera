#include <iostream>

using namespace std;

class ReversibleString {
    public:
        ReversibleString () {
            str = "";
        }
        ReversibleString (const string& s) {
            str = s;
        }
        void Reverse () {
            int n = str.length();
            
            for (int i = 0; i < n / 2; i++) 
                swap(str[i], str[n - i - 1]); 
        }
        string ToString() const {
            return str;
        }
    private:
        string str;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;
  
  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;
  
  return 0;
}
