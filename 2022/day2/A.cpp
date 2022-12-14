#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
int main(int argc, char * argv[])
{
        if(isatty(fileno(stdin))) {   
                // if the input is from a tty, print the content of 2.in
                // execl("/bin/cat","cat","2.in", NULL);
                printf("%s %s\n", argv[0],argv[1]);
        }
        else {
                // otherwise, run the problem solver, and read from stdin
                vector<pair<char,char> > v;
                for (int i=0;;i++) {
                        char a[11],b[11];
                        if(scanf("%s %s",a,b)!=2) break;
                        v.push_back(pair<char,char>(a[0],b[0]));
                }
                if(v.size()>0)
                {
                        long score_sum=0;
                        for(int idx=0;idx<int(v.size());idx++){
                                char opp= v[idx].first;
                                char me= v[idx].second -'X' + 'A';
                                int score1= me-'A'+1;
                                int score2= opp==me? 3:0;
                                if( (me-opp+3) %3 ==1 ) score2+=6;
                                //printf("%c %c %d %d\n", opp,me,score1,score2);
                                score_sum+=score1+score2;
                        }
                        printf("%ld\n", score_sum);
                }
        }
        return 0;
}
