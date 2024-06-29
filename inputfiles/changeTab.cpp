/*
 * @Description: 转换格式，从空格转换为制表符
 * @Author: Duawieh
 * @Email: DuawiehPublic@outlook.com
 * @Date: 2024-06-24 17:01:41
 * @LastEditors: Duawieh
 * @LastEditTime: 2024-06-24 17:17:08
 */
# include <bits/stdc++.h>
using namespace std;

string s;

int main() {
    freopen("Attendence.in", "r", stdin);
    freopen("Attendence.out", "w", stdout);

    int cnt = 0;

    do {
        getline(cin, s);
        for (char c : s) {
            if (c == ' ') cout << '\t';
            else cout << c;
        }
        cout << '\n';
        cnt++;
    }
    while (cnt <= 24);
    return 0;
}