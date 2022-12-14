#include <bits/stdc++.h>
using namespace std;
int restrict(int a){
    return (a>=0?1:-1) * min(abs(a),1);
}
pair<int,int> next_tail(int head_y,int head_x, int tail_y, int tail_x){
    if( abs(head_x-tail_x)<=1 && abs(head_y-tail_y)<=1) 
        return make_pair(tail_y,tail_x);
    return make_pair(tail_y + restrict(head_y-tail_y) , tail_x+ restrict(head_x-tail_x));
}
int main(){
    map<char,int> dir_x,dir_y;
    dir_x['D']=0;dir_y['D']=1;
    dir_x['U']=0;dir_y['U']=-1;
    dir_x['L']=-1;dir_y['L']=0;
    dir_x['R']=1;dir_y['R']=0;

    map<pair<int,int>,int> vis;
    int ans;
    vis[make_pair(0,0)]=1;
    vector<pair<int,int> > rope;
    for(int i=0;i<10;i++) rope.push_back(make_pair(0,0));

    for(int i=0;;i++){
        char s[10];int n;
        if(scanf("%s %d",s,&n)!=2) break;
        char c=s[0];
        printf("----new move %c %d---\n",c,n);
        for(int j=0;j<n;j++)
        {
            rope[0].first+=dir_y[c];
            rope[0].second+=dir_x[c];
            for(int k=1;k<=9;k++){
                auto t= next_tail(rope[k-1].first,rope[k-1].second,rope[k].first,rope[k].second);
                rope[k]=t;
            }
            vis[ rope[9]]=1;
        }
    }
    printf("<ans=%d>",(int)vis.size());
    return 0;
}
