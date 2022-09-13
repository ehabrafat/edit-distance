#include <iostream>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

int mem[500][500]{};
string s1, s2;

int edit_distance(int i, int j) {
	if (i == s1.size()) return s2.size() - j;
	if (j == s2.size()) return s1.size() - i;
	auto& ret = mem[i][j];
	if (ret != -1) return ret;
	if (s1[i] != s2[j])
		return ret = 1 + min(
				edit_distance(i + 1,j + 1), // Change
				min(
					edit_distance(i + 1, j), // Delete
					edit_distance(i, j + 1) // Insert
				) 
			);
	else
		return edit_distance(i + 1, j + 1);
}

void dp_output(int i, int j) {
	if (i == s1.size()) {
		string charsToInsert{ s2.substr(j) };
		if (charsToInsert.empty()) return;
		cout << "Insert ";
		for (int i = 0; i < charsToInsert.size(); ++i) {
			cout << (i > 0 ? ", " : "") << "'" << charsToInsert[i] << "'";
		}
		return;
	}
	if (j == s2.size()) {
		string charsToDelete{ s1.substr(i) };
		if (charsToDelete.empty()) return;
		cout << "Delete ";
		for (int i = 0; i < charsToDelete.size(); ++i) {
			cout << (i > 0 ? ", " : "") << "'" << charsToDelete[i] << "'";
		}
		return;
	}
	if (s1[i] != s2[j]) {
		int opt = edit_distance(i, j);
		int change = 1 + edit_distance(i + 1, j + 1);
		int insert = 1 + edit_distance(i, j + 1);
		int remove = 1 + edit_distance(i + 1, j);
		if (change == opt) {
			cout << "Change '" << s1[i] << "' to '" << s2[j] << "'\n";
			dp_output(i + 1, j + 1);
		}
		else if (insert == opt) {
			cout << "Insert '" << s2[j] << "'\n";
			dp_output(i, j + 1);
		}
		else {
			cout << "Delete '" << s1[i] << "'\n";
			dp_output(i + 1, j);
		}
	}
	else
		dp_output(i + 1, j + 1);

}

void minChange(const string& _s1, const string& _s2) {
	memset(mem, -1, sizeof mem);
	s1 = _s1, s2 = _s2;
	int ans = edit_distance(0, 0);
	dp_output(0, 0);
}


int main() {
    minChange("horse", "ros");
}
