#include <iostream>
#include <string>

using namespace std;

bool IfPalindrom(string word) {
	if (word.length() <= 1) return 1;
	string shortword = word.substr(1, word.length() - 2);
	if ((word[0] == word[word.length() - 1]) && (IfPalindrom(shortword))) {
		return 1;
	}
	else return 0;
}

int main()
{
	string word;
	cin >> word;
	cout << IfPalindrom(word);
	return 0;
}