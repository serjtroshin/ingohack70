#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <chrono>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<unordered_set<int>> subset(n);
    unordered_map<int, int> position, run_id_position;
    vector<unordered_set<int>> v;
    vector<int> f(n);
    int m = 0;
    vector<int> line_numbers, run_id;
    for (int i = 0; i < n; i++) {
        int cardinality, id;
        cin >> cardinality >> id;
        if (run_id_position.find(id) == run_id_position.end()) {
            run_id_position[id] = i;
            run_id.push_back(id);
        }
        for (int j = 0; j < cardinality; j++) {
            int line_num;
            cin >> line_num;
            if (position.find(line_num) == position.end()) {
                position[line_num] = m++;
                line_numbers.push_back(line_num);
                unordered_set<int> tmp;
                v.push_back(tmp);
            }
            subset[i].insert(position[line_num]);
            v[position[line_num]].insert(i);
        }
    }
    unsigned int cnt = (1u << n);
    int ans = n;
    for (unsigned int i = 0; i < cnt; i++) {
        unordered_set<int> s;
        int cur_ans = 0;
        for (int j = 0; j < n; j++) {
            if ((i & (1u << j)) != 0) {
                cout << '1';
                for (auto it: subset[j]) {
                    s.insert(it);
                }
                cur_ans++;
            } else {
                cout << '0';
            }
        }
        cout << ' ' << cur_ans;
        cout << endl;
        if (s.size() == m) {
            ans = min(ans, cur_ans);
        }
    }
    cout << ans << endl;
}
