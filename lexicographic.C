#include <iostream>
using namespace std;

void lex(string s, int pos, char max) {
    // The iteration landing on pos = strlen will
    // do the printing.
    if (pos == s.length() - 1) {
        while (s[pos] < max) {
            cout << s << endl;
            s[pos]++;
        }
        return;
    }

    while (s[pos] < max) {
        lex (s, pos + 1, max);
        s[pos]++;

        // for a new character, clear the characters to the right
        for (int j = pos + 1; j < s.length(); j++) {
            s[j] = 'a';
        }
    }
}

int main(void) {
    char max;
    string s;

    cout << "Enter string: ";
    cin >> s;
    cout << "Enter max alphabet: ";
    cin >> max;

    max++;

    lex(s, 0, max);
    
    return 0;
}
