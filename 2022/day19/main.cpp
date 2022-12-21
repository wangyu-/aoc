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
const int MAX_DAY = 32;
struct vec_hash
{
    size_t operator() (const vector<short> v) const{
        size_t r=0;
        for(int i=0;i<(int)v.size();i++){
            r+=(uint)v[i];
            r*=107;
        }
        return r;
    }
};
struct plan_t {
    int id;
    //hash key: (robot1, robot2, robot3, robot4, resouce1,resouce2, resouce3), hash value: resource4 
    //optimization: robot4 is converted into resouce4 in advance, so in the hash table robot4 is always0
    //so it's essentially a 6 dimension hash
    unordered_map<vector<short>, int,vec_hash> dp[MAX_DAY + 1];  
    cost_t c[4];
    int max_res[3] = {0};
    void init() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                max_res[i] = max(max_res[i], c[j].get(i));
            }
        }
    }
    vector<short> produce(vector<short> a) {
        vector<short> res = a;
        for (int i = 0; i < 4; i++) {
            res[4 + i] += a[i];
        }
        return res;
    }
    int okay_for_robot(vector<short> a, int idx) {
        for (int i = 0; i < 3; i++)
            if (a[4 + i] < c[idx].get(i))
                return 0;
        return 1;
    }
    vector<short> pay_robot(vector<short> a, int idx) {
        vector<short> r = a;
        for (int i = 0; i < 3; i++)
            r[4 + i] -= c[idx].get(i);
        // r[idx]+=1;
        return r;
    }
    void prt(vector<short> a) {
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
    void insert(int idx, vector<short> a) {
        int v = a[7];
        a[7] = 0;
        if (dp[idx].find(a) == dp[idx].end()) {
            dp[idx][a] = v;
        } else if (dp[idx][a] < v) {
            dp[idx][a] = v;
        }
    }
    int solve() {
        vector<short> a(8, 0);
        a[0] = 1; // first 4 is machine, last 4 is resource
        insert(0, a);
        int best = 0;
        vector<vector<short>> cands;
        for (int i = 0; i < MAX_DAY; i++) {
            int days_left = MAX_DAY - i - 1;

            printf("<day %d size=%d>\n", i, (int)dp[i].size());
            vector<short> mmax(7, 0);
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
                vector<short> a2 = produce(a);
                cands.push_back(a2);
                for (int j = 0; j < 4; j++) {
                    if (okay_for_robot(a, j)) {
                        vector<short> b = pay_robot(a, j);
                        vector<short> b2 = produce(b);
                        b2[j] += 1;
                        int skip = 0;
                        // prune1: if produce rate (num of robot) is larger than max resource consume, skip
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
                        // prune2: once produce >= consume, and current >= consume, throw extra resouce away
                        if (cand[idx] >= max_res[idx] && cand[4 + idx] >= max_res[idx])
                            cand[4 + idx] = max_res[idx];
                        
                        // prune3: stronger version of above, if your current + product in future >= you can consume in the left days, throw extra resource aways
                        if(cand[4 + idx]    >=   days_left * max_res[idx]  - days_left* cand[idx] +max_res[idx] ){
                            cand[4+idx]= days_left * max_res[idx]  - days_left* cand[idx] +max_res[idx];
                        }
                    }

                    // optimization: convert type4 robot to resource direcly based on day left
                    if (cand[3] > 0) {
                        cand[7] += days_left * cand[3];
                        cand[3] = 0;
                    }
                    best = max((int)cand[7], best);

                    // prune4: if in the flowing days, each day you get a new type4 robot, you still can't catch the best
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
