#include "mylibs.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mkp make_pair
int test = 0;
struct cost_t {
    int ore = 0;
    int clay = 0;
    int obs = 0;
    int get(int n) {
        if (n == 0)
            return ore;
        if (n == 1)
            return clay;
        if (n == 2)
            return obs;
        assert(0 == 1);
    }
    void prt() {
        cout << "<" << ore << "," << clay << "," << obs << ">" << endl;
    }
};
const int MAGIC = 32;
struct plan_t {
    int id;
    unordered_map<string, int> dp[MAGIC + 1];
    cost_t c[4];
    int max_res[3] = {0};
    void init() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                max_res[i] = max(max_res[i], c[j].get(i));
            }
        }
    }
    string produce(string a) {
        string res = a;
        for (int i = 0; i < 4; i++) {
            res[4 + i] += a[i];
        }
        return res;
    }
    int okay_for_robot(string a, int idx) {
        for (int i = 0; i < 3; i++)
            if (a[4 + i] < c[idx].get(i))
                return 0;
        return 1;
    }
    string pay_robot(string a, int idx) {
        string r = a;
        for (int i = 0; i < 3; i++)
            r[4 + i] -= c[idx].get(i);
        // r[idx]+=1;
        return r;
    }
    void prt(string a) {
        for (int i = 0; i < 7; i++)
            printf("<%d>", a[i]);
        printf("\n");
    }
    int can_prune(int day_left, int best, int current) {
        int tmp = (day_left - 1) * day_left / 2;
        if (best - current >= tmp)
            return 1;
        return 0;
    }
    void insert(int idx, string a) {
        int v = a[7];
        a[7] = 0;
        if (dp[idx].find(a) == dp[idx].end()) {
            dp[idx][a] = v;
        } else if (dp[idx][a] < v) {
            dp[idx][a] = v;
        }
    }
    int solve() {
        string a(8, 0);
        a[0] = 1; // first 4 is machine, last 4 is resource
        insert(0, a);
        int best = 0;
        vector<string> cands;
        for (int i = 0; i < MAGIC; i++) {
            int days_left = MAGIC - i - 1;

            printf("<day %d size=%d>\n", i, (int)dp[i].size());
            string mmax(7, 0);
            for (auto &pr : dp[i]) {
                auto a = pr.first;
                for (int j = 0; j < 7; j++) {
                    mmax[j] = max(mmax[j], a[j]);
                }
            }
            for (int j = 0; j < 7; j++) {
                printf("[%d]", mmax[j]);
            }
            printf("\n");

            for (auto &pr : dp[i]) {
                auto a = pr.first;
                a[7] = pr.second;
                cands.clear();
                string a2 = produce(a);
                cands.push_back(a2);
                for (int j = 0; j < 4; j++) {
                    if (okay_for_robot(a, j)) {
                        string b = pay_robot(a, j);
                        string b2 = produce(b);
                        b2[j] += 1;
                        int skip = 0;
                        // if num of machine is larger then resource consum skip this candidate
                        for (int idx = 0; idx < 3; idx++) {
                            if (b2[idx] > max_res[idx])
                                skip = 1;
                        }
                        if (!skip)
                            cands.push_back(b2);
                    }
                }
                for (auto &cand : cands) {
                    for (int idx = 0; idx < 3; idx++) {
                        // once your produce >= consume, and current >= consume, throw extra resouce away
                        if (cand[idx] >= max_res[idx] && cand[4 + idx] >= max_res[idx])
                            cand[4 + idx] = max_res[idx];
                        
                        // stronger version of above, if your current + product in future >= you can consume in the left days, throw extra resource aways
                        if(cand[4 + idx]    >=   days_left * max_res[idx]  - days_left* cand[idx] +max_res[idx] ){
                            cand[4+idx]= days_left * max_res[idx]  - days_left* cand[idx] +max_res[idx];
                        }
                    }

                    // convert type4 robot to resource direcly based on day left
                    if (cand[3] > 0) {
                        cand[7] += days_left * cand[3];
                        cand[3] = 0;
                    }
                    best = max((int)cand[7], best);

                    // if in the flowing days, each day you get a new type4 robot, you still can't catch the best
                    // then skip it;
                    if (!can_prune(days_left, best, cand[7])) {
                        insert(i + 1, cand);
                    }
                }
            }
        }
        return best;
    }
};
vector<plan_t> plans;
int main() {
    auto lines = readlines();
    for (auto line : lines) {
        plan_t plan;
        sscanf(line.c_str(), "Blueprint %d:", &plan.id);
        auto eachs = split_s(line, "Each ");
        prt_arr(eachs);
        cost_t c[4];

        sscanf(eachs[1].c_str(), "ore robot costs %d ore", &c[0].ore);
        sscanf(eachs[2].c_str(), "clay robot costs %d ore", &c[1].ore);
        sscanf(eachs[3].c_str(), "obsidian robot costs %d ore and %d clay", &c[2].ore, &c[2].clay);
        sscanf(eachs[4].c_str(), "geode robot costs %d ore and %d obsidian", &c[3].ore, &c[3].obs);
        for (int i = 0; i < 4; i++) {
            c[i].prt();
            plan.c[i] = c[i];
        }
        plans.push_back(plan);
    }
    long product = 1;
    for (int i = 0; i < min((int)plans.size(), 3); i++) {
        plans[i].init();
        printf("---%d--\n",i);
        int r = plans[i].solve();
        printf("<%d>\n", r);
        product *= r;
    }
    printf("product=%ld\n", product);
    return 0;
}
