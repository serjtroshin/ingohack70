#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

//
enum {NaN = -1};
std::vector<int> run_id;
std::vector<std::unordered_set<int>> get_subset(int n, int & m) {
    std::vector<std::unordered_set<int>> subset(n);
    std::unordered_map<int, int> position, run_id_position;
    std::vector<int> line_numbers;
    for (int i = 0; i < n; i++) {
        int cardinality, id;
        std::cin >> cardinality >> id;
        if (run_id_position.find(id) == run_id_position.end()) {
            run_id_position[id] = i;
            run_id.push_back(id);
        }
        for (int j = 0; j < cardinality; j++) {
            int line_num;
            std::cin >> line_num;
            if (position.find(line_num) == position.end()) {
                position[line_num] = m++;
                line_numbers.push_back(line_num);
            }
            subset[i].insert(position[line_num]);
        }
    }
    return subset;
}

template <typename T>
void move(std::set<T> & a, std::set<T> & b, T elem) {
    if (a.find(elem) != a.end()) {
        a.erase(elem);
        b.insert(elem);
    } else {
        b.erase(elem);
        a.insert(elem);
    }
    return;
}

int get_random(std::set<int> & nused) {
    std::set<int>::const_iterator it(nused.begin());
    int r = rand() % nused.size();
    //  std::cout << "RANDOM: " << r << '\n';
    std::advance(it, r);
    return *it;
}

bool can_del(std::vector<long long> & sum_of_ones, std::unordered_set<int> & st) {
    for (auto it : st) {
        if (sum_of_ones[it] <= 1) {
            return 0;
        }
    }
    return 1;
}

void del_all_junk(std::vector<int> & cur_ar) {
    int it = 0, left = 0;
    for (int it = 0; it < cur_ar.size(); it++) {
        if (cur_ar[it] != NaN) {
            cur_ar[left++] = cur_ar[it];
        }
    }
    cur_ar.resize(left);
}

int main() {
    srand(time(0));
    freopen("/Users/istar/Desktop/hack/tests/test1.txt", "r", stdin);
    //  freopen("/Users/istar/Desktop/hack/tests/answers.txt", "w", stdout);
    int n; //  number of rows
    std::cin >> n;
    int m = 0; //  number of different columns
    std::vector<std::unordered_set<int>> subset = get_subset(n, m);
    const int ITER_CNT = 10; // число запусков программы
    long long min_ans = INT_MAX; //   размер минимального покрытия
    std::vector<long long> preprocessing_sum_of_ones(m, 0);
    for (int i = 0; i < n; i++) {
        for (auto elem : subset[i]) {
            preprocessing_sum_of_ones[elem] += 1;
        }
    }
    int calc_sum_of_local_answers = 0;
    std::vector<int> best_ans_vec;
    for (int _ = 0; _ < ITER_CNT; ++_) {
        double TIME_START = (double)clock() / CLOCKS_PER_SEC;
        bool flag = 1;
        long long cur_ans = n; // !
        std::vector<int> curr_unused;
        std::vector<int> not_deleted;
        std::vector<long long> sum_of_ones(m, 0);
        sum_of_ones = preprocessing_sum_of_ones;
        for (int i = 0; i < n; i++) {
            curr_unused.push_back(i);
        }
        while (flag) {
            std::random_shuffle(curr_unused.begin(), curr_unused.end());
            bool was = 0;
            for (int j = 0; j < curr_unused.size(); ++j) {
                if (can_del(sum_of_ones, subset[curr_unused[j]])) {
                    for (auto it : subset[curr_unused[j]]) {
                        sum_of_ones[it]--;
                    }
                    was = 1;
                    cur_ans--;
                } else {
                    not_deleted.push_back(curr_unused[j]);  //   чтобы вывести ответ
                }
                curr_unused[j] = NaN;
            }
            del_all_junk(curr_unused);
            if (!was)
                flag = 0;
        }
        double TIME_END = (double)clock() / CLOCKS_PER_SEC;
        calc_sum_of_local_answers += cur_ans;
        std::cout << "TIME(sec) " << TIME_END - TIME_START << '\n';
        if (cur_ans < min_ans) {
            min_ans = cur_ans;
            best_ans_vec = not_deleted;
        }
        std::cout << "cur_ans = " << cur_ans << '\n';
    }
    std::cout << "Minimal subset " << min_ans << '\n';
    std::cout << std::endl;
    std::cout << "n, m = " << n << ' ' << m << '\n';
    std::cout << " mean answer is " << calc_sum_of_local_answers * 1.0 / ITER_CNT << '\n';
    std::cout << "-------------\n";
    std::cout << "TESTIDS:\n";
    for (auto it : best_ans_vec) {
        std::cout << run_id[it] << ' ';
    }
    std::cout << '\n';
    return 0;
}