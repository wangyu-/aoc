#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int test=1;
#else
int test=0;
#endif

int main()
{
    vector<pair<char,char>> v;
    for (int i=0;;i++) {
            char a[11],b[11];
            if(scanf("%s %s",a,b)!=2) break;
            v.push_back(pair<char,char>(a[0],b[0]));
    }

    char xtoc[128];
    long score_sum=0;
    for(int idx=0;idx<int(v.size());idx++){
            char opp= v[idx].first;
            char me= v[idx].second -'X' + 'A';

            int score1= me-'A'+1;
            int score2= opp==me? 3:0;
            if(opp=='A'&&me=='B') score2+=6;
            else if(opp=='B'&&me=='C') score2+=6;
            else if(opp=='C'&&me=='A') score2+=6;

            //printf("%c %c %d %d\n", opp,me,score1,score2);

            score_sum+=score1+score2;
    }
    printf("%ld\n", score_sum);
    return 0;
}
