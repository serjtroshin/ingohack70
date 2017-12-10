#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std;

// asymptotics O(nm)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("/Users/alexander/desktop/hack/test_big.txt", "r", stdin);
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
    chrono::time_point<std::chrono::system_clock> t0;
    t0 = std::chrono::system_clock::now();
    for (int i = 0; i < n; i++) {
        f[i] = (int) subset[i].size();
    }
    int current = m;
    vector<bool> used(m);
    vector<int> ans;
    while (current > 0) {
        // std::cout << current << ' ' << ans.size() << endl;
        int cur_best = 0, best_index = -1;
        for (int i = 0; i < n; i++) {
            if (f[i] > cur_best) {
                cur_best = f[i];
                best_index = i;
            }
        }
        for (auto it = subset[best_index].begin();
             it != subset[best_index].end(); it++) {
            int pos = *it;
            if (!used[pos]) {
                for (auto obj = v[pos].begin(); obj != v[pos].end(); obj++) {
                    f[*obj]--;
                }
            }
            used[pos] = 1;
        }
        current -= cur_best;
        ans.push_back(best_index);
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << run_id[ans[i]] << ' ';
    }
    cout << endl;
    cout << ((double) chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - t0).count()) << "ms" << endl;
}
