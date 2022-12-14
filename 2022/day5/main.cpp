#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int test=1;
#else
int test=0;
#endif

string s=
R"AABB(
    [B]             [B] [S]
    [M]             [P] [L] [B] [J]
    [D]     [R]     [V] [D] [Q] [D]
    [T] [R] [Z]     [H] [H] [G] [C]
    [P] [W] [J] [B] [J] [F] [J] [S]
[N] [S] [Z] [V] [M] [N] [Z] [F] [M]
[W] [Z] [H] [D] [H] [G] [Q] [S] [W]
[B] [L] [Q] [W] [S] [L] [J] [W] [Z]
 1   2   3   4   5   6   7   8   9
 )AABB";
int main()
{
    vector<string> input;
    string line;
    for(int i=0;i<s.size();i++)
    {
            if(s[i]=='\n') {
                    input.push_back(line);
                    line.clear();
                    continue;
            }
            line+=s[i];
    };

    string data[1000];
    int max_idx=-1;
    for(int i=0;i<input.size()-1;i++){
            for(int j=1;j<input[i].size();j+=4){
                    int idx= (j-1)/4;
                    max_idx=max(max_idx,idx);
                    if(input[i][j]!=' ')data[(j-1)/4].push_back(input[i][j]);
            }
    }
    for(int i=0;i<=max_idx;i++){
        reverse(data[i].begin(),data[i].end());
    }
    int ans=0;
    for (int i=0;;i++) {
	int n,a,b;
	if(scanf("move %d from %d to %d\n",&n,&a,&b)!=3) break;
        a--; b--;
        string tmp;
        for(int j=0;j<n;j++)
        {
                char c= data[a].back();
                data[a].pop_back();
                tmp.push_back(c);
                //data[b].push_back(c);
        }
        reverse(tmp.begin(),tmp.end());
        for(int j=0;j<tmp.size();j++)
        {
                data[b].push_back(tmp[j]);
        }
    }
    for(int i=0;i<=max_idx;i++)
    printf("<%s>\n",data[i].c_str());
    return 0;
}
