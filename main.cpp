#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;



int main() {
    freopen("/Users/istar/Desktop/hack/tests/test1.txt", "r", stdin);
    int n;
    cin >> n;
    vector<unordered_set<int>> subset(n);
    unordered_map<int, int> position, run_id_position;
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
            }
            subset[i].insert(position[line_num]);
        }
    }
    int current = m;
    vector<bool> used(m);
    vector<int> ans;
    std::cout << "OK1\n";
    while (current > 0) {
        std::cout << current << '\n';
        int cur_best = 0, best_index = -1, cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt = 0;
            for (int j = 0; j < m; j++) {
                if (!used[j] && subset[i].count(j) != 0) {
                    cnt++;
                }
            }
            if (cnt > cur_best) {
                cur_best = cnt;
                best_index = i;
            }
        }
        for (auto it = subset[best_index].begin();
             it != subset[best_index].end(); it++) {
            used[*it] = 1;
        }
        current -= cur_best;
        ans.push_back(best_index);
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << run_id[ans[i]] << ' ';
    }
    cout << endl;
}