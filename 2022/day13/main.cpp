#include <bits/stdc++.h>
using namespace std;
char mp[1000][1000];
int y_size=0;
int x_size=0;
int dir_y[]={-1,1,0,0};
int dir_x[]={0,0,-1,1};
int oob(int y,int x)
{
    if(y<0 || y>= y_size) return 1;
    if(x<0 || x>= x_size) return 1;
    return 0;
}
int move_able(int y1,int x1, int y2,int x2)
{
    if(oob(y2,x2)) return 0;
    return 1;
    if(mp[y2][x2] <= mp[y1][x1] + 1) return 1;
    return 0;
}
int start_x=-1, start_y=-1;
int goal_x=-1,goal_y=-1;
class hhh {
public:
    size_t operator()(const pair<int,int>& p) const
    {
        return p.first*1000+p.second;
    }
};
unordered_set<pair<int,int>, hhh> st[10000];
int main(){
    for(int i=0;;i++){
	if(scanf("%s",mp[i])!=1) break;
	y_size++;
    }
    x_size=strlen(mp[0]);
    for(int y=0;y<y_size;y++) {
	for(int x=0;x<x_size;x++) {
	    if(mp[y][x]=='S') {
		mp[y][x]='a';
		start_y=y;
		start_x=x;
	    }
	    if(mp[y][x]=='E'){
		mp[y][x]='z';		
		goal_y=y;
		goal_x=x;
	    }
	}
    }
    st[0].insert(make_pair(start_y,start_x));
    for(int i=1;i<10000;i++){
	printf("===%d=== %d\n",i,(int)st[i-1].size());
	for(auto p: st[i-1]) {
	    for(int j=0;j<4;j++){
		auto np=make_pair(p.first+dir_y[j],p.second+dir_x[j]);
		if (!move_able(p.first, p.second, np.first,np.second)) continue;
		st[i].insert(np);
	    }
	}
	if(st[i].find(make_pair(goal_y,goal_x))!=st[i].end() ) {
	    //printf("<ans=%d>\n",i);
	    //break;
	}
    }
    return 0;
}
