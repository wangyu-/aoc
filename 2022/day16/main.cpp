#include <bits/stdc++.h>
#include "mylibs.h"
using namespace std;
#define pii pair<int,int>
#define mkp make_pair

struct valv_t{
    string name;
    int idx;
    int ps_idx=-1;
    int rate;
    vector<string> tos;
    vector<int> tosi;
};
vector<valv_t> valvs;
map<string,int> nti;
map<string,int> nti_ps;
int get_byte(int a,int n) {
    return (a>>n)&0x1;
}
void set_byte(int &a,int n) {
    a|= (1<<n);
}
const int MOD=2;
int opt[MOD][60][60][32768];

struct item_t{
    int left;
    int pos;
    int pos2;
    int state;
    long long score=0;
};
int main(){
    auto lines=readlines();
    int ps_cnt=0;
    int start_pos=-1;
    for(auto line: lines) {
	valv_t valv;
	char s[10]; int rate=-1;
	sscanf(line.c_str(),"Valve %s has flow rate=%d",s,&rate);
	string tmp= split_s(line,"to valve")[1];
	auto tos= split_c(tmp,", s");
	prt_arr(tos);
	valv.name=s; valv.rate=rate;valv.tos=tos;
	valv.idx=(int)valvs.size();
	nti[valv.name]=valv.idx;
	if(rate>0) {
	    nti_ps[valv.name]=ps_cnt;
	    valv.ps_idx=ps_cnt;
	    ps_cnt++;
	}
	if(valv.name=="AA") {
	    start_pos=valv.idx;
	}
	printf("<%s %d %d %d>",valv.name.c_str(),valv.rate,valv.idx,valv.ps_idx);
	valvs.push_back(valv);
    }
    for(auto & valv: valvs) {
	for(auto to : valv.tos) {
	    valv.tosi.push_back(nti[to]);
	}
    }
    memset(opt,-1,sizeof(opt));
    item_t st; st.pos=start_pos; st.pos2=start_pos; st.left=26; st.state=0;
    opt[26%MOD][start_pos][start_pos][0]=0;
    deque<item_t> q;
    long long mmax=0;
    q.push_back(st);
    vector<item_t> cands;
    cands.reserve(100);
    int cnt=0;
    while(!q.empty()) {
	cnt++;
	item_t e= q.front();
	q.pop_front();

	if(e.score < opt[e.left%MOD][e.pos][e.pos2][e.state]) {
	    continue;
	}
	
	if(cnt%1000000==0){
	    printf("current_step=%d, left=%d best= %lld\n",cnt,e.left,mmax);
	}
	int cur_pos=e.pos;
	if(e.left==0) continue;

	cands.clear();
	
	if(valvs[cur_pos].ps_idx!=-1 && get_byte(e.state, valvs[cur_pos].ps_idx)==0) {
	    item_t e2=e;
	    e2.left--;
	    set_byte(e2.state, valvs[cur_pos].ps_idx);
	    e2.score+= e2.left* valvs[cur_pos].rate;
	    cands.push_back(e2);
	}
	for(auto  to: valvs[cur_pos].tosi) {
	    item_t e2=e;
	    e2.left--;
	    e2.pos= to;
	    cands.push_back(e2);
	}

	for(auto e2: cands)
	{
	    int cur_pos2=e2.pos2;
	    if(valvs[cur_pos2].ps_idx!=-1 && get_byte(e2.state, valvs[cur_pos2].ps_idx)==0) {
		item_t e3=e2;
		set_byte(e3.state, valvs[cur_pos2].ps_idx);
		e3.score+= e3.left* valvs[cur_pos2].rate;
		mmax= max(mmax,e3.score);
		//if(e3.pos >e3.pos2) swap(e3.pos,e3.pos2);
		if(e3.score > opt[e3.left%MOD][e3.pos][e3.pos2][e3.state])  {
		    q.push_back(e3);
		    opt[e3.left%MOD][e3.pos][e3.pos2][e3.state] = e3.score;
		} 	   
	    }
	    for(auto to: valvs[cur_pos2].tosi) {
		item_t e3=e2;
		e3.pos2= to;
		//if(e3.pos >e3.pos2) swap(e3.pos,e3.pos2);
		if(e3.score > opt[e3.left%MOD][e3.pos][e3.pos2][e3.state])  {
		    q.push_back(e3);    
		    opt[e3.left%MOD][e3.pos][e3.pos2][e3.state] = e3.score;
		}
	    }
	}
    }
    printf("<ans=%lld>\n", mmax);
    return 0;
}
