#include <bits/stdc++.h>
#include "mylibs.h"
using namespace std;
#define pii pair<int,int>
#define mkp make_pair
string jet;
int test=0;
vector<vector<pnt_t> > pntss= {
    {{0,0},{0,1},{0,2},{0,3}},
    {{-1,0},{-1,1},{-1,2},{0,1},{-2,1}},
    {{0,0},{0,1},{0,2},{-1,2},{-2,2}},
    {{0,0},{-1,0},{-2,0},{-3,0}},
    {{0,0},{0,1},{-1,0},{-1,1}}
};
struct shape_t
{
    vector<pnt_t> pnts;
    int lm=0;
    int rm=-1;
    void init() {
	for(int i=0;i<(int)pnts.size();i++){
	    rm=max(rm, pnts[i].x);
	}
    }
} shapes[5];

struct room_t
{
    int ub=0;
    int last_gc=-1;
    unordered_set<pnt_t,pnt_hash> st;
    room_t(){
	st.max_load_factor(0.2);
    }
    int oob(pnt_t a, int type){
	if(a.x<0) return 1;
	if(a.x+ shapes[type].rm >=7) return 1;
	return 0;
    }
    int conflict(pnt_t a,int type){
	for(auto rr: shapes[type].pnts) {
	    pnt_t ab= pnt_t{a.y+rr.y,a.x+rr.x};
	    if(ab.y>=0) return 1;
	    if(st.find(ab)!=st.end()) {
		return 1;
	    }
	}
	return 0;
    }
    
    void ins(pnt_t a,int type){
	for(auto rr: shapes[type].pnts) {
	    pnt_t ab= pnt_t{a.y+rr.y,a.x+rr.x};
	    //printf("<ins %d %d>\n",ab.y,ab.x);
	    ub=min(ub, ab.y);
	    assert(st.find(ab)==st.end());
	    st.insert(ab);	    
	}
    }

    void gc() {
	if( st.size()<10000 ) return;
	
	int magic=10;
	for(int x=0;x<7;x++) {
	    pnt_t p= pnt_t{ub+magic,x};
	    if(st.find(p)==st.end()) return;
	}
	//printf("gc!!\n");
	decltype(st) tmp;
	for(auto &e:st) {
	    if(e.y <= ub+magic) tmp.insert(e);
	}
	st.clear();
	for(auto &e:tmp) st.insert(e);
    }

    void prt(int n)
	{
	    printf("------\n");
	    for(int y=ub;y< ub+n;y++){
		for(int x=0;x<7;x++) {
		    pnt_t p= pnt_t{y,x};
		    if(st.find(p)!=st.end()){
			printf("#");
		    }else{
			printf(".");
		    }
		}
		printf("\n");
	    }
	}
    
}room;

vector<int> a;
int check_eq(int idx1,int idx2,int len)
{
    for(int i=0;i<len;i++) {
	if(a[idx1+i]!=a[idx2+i]) {
	    return 0;
	}
    }
    return 1;
}
int check_cycle(){
    //printf("[begin check]\n");
    int len=(int)a.size();
    const int min_window=100;
    for(int i=1;i<(int)a.size();i++){
	int idx2= len-min_window;
	int idx1= len-i- min_window;

	if(idx1<0) {
	    //printf("[end check]\n");
	    return -1;
	}
	if(check_eq(idx1,idx2,min_window)!=0) {
	    printf("<cycle= %d>\n",i);
	    return i;
	}
	
    }
    assert(0==1);
    return -1;
}
long get_csum(int n){
    long long sum=0;
    for(int i=0;i<n;i++) {
	sum+=a[(int)a.size()-i-1];
    }
    return sum;
}
void prt_sample()
{
    printf("\n\n[");
    for(int j=0;j<(int)a.size();j++) {
	if(j) printf(",");
	printf("%d",a[j]);
    }
    printf("]\n");
}
int main(){
    auto lines=readlines();
    jet=lines[0];
    printf("<len=%d>",(int)jet.size());
    for(int i=0;i<(int)pntss.size();i++){
	shape_t shape;
        shapes[i].pnts=pntss[i];
	shapes[i].init();
    }

    int cnt=0;
    int last_ub= 0;
    int lcm=jet.size()*5;

    int last_check_size=1;
    long left=1000000000000;
    long delta=0;
    for(int i=0;left>0;i++,left--){
	room.gc();
	if(i%(lcm) ==0 )
	{
	    if(i%(10*lcm)==0) {
		//room.prt(50);
	    }
	    a.push_back(last_ub-room.ub);
	    last_ub=room.ub;
	    if((int)a.size() >= last_check_size*1.5) {
		printf("<<current i=%d %d %d>>\n",i,(int)room.st.size(),(int)a.size());
		last_check_size=(int)a.size();
		int c=check_cycle();
		if(c!=-1) {
		    //prt_sample();
		    auto c_sum=get_csum(c);
		    printf("[c_sum=%ld]\n",c_sum);
		    printf("[left=%ld real_cycle=%ld]", left, (long) c*lcm);
		    
		    delta= left/(c*lcm) *c_sum;
		    left%=(c*lcm);
		    printf("[new left=%ld]\n",left);
		    if(left==0) break;
		}
	    }
	}
	
	if(test) room.prt(50); 
	int type= i%5;
	pnt_t now = pnt_t{room.ub-4, 2};

	for(int j=0;;j++)
	{
	    if(test)printf("<j:%d>\n",j);
	    char c= jet[cnt%jet.size()]; cnt++;
	    if(test)printf("<%d>",cnt);
	    pnt_t dir1;
	    if(c=='<') {
		dir1.x=-1,dir1.y=0;
	    }else {
		dir1.x=1,dir1.y=0;
	    }
	    //assert(!room.conflict(now,type));
	    pnt_t next1= pnt_t {now.y+ dir1.y, now.x+ dir1.x};
	    if(!room.oob(next1,type ) && !room.conflict(next1,type)) {
		now=next1;
	    }
	    if(test)printf("[after push %c, now %d %d]\n",c,now.y,now.x);
		
	    pnt_t next2= pnt_t {now.y+1,now.x};
	    if(room.conflict(next2,type)) {
		room.ins(now,type);
		break;
	    }else {
		if(test)printf("<after fall, now %d %d>\n",now.y,now.x);
		now=next2;
	    }
	}
    }

    printf("<ans=%d   delta=%ld    final=%ld>\n",room.ub,delta, room.ub-delta);
    return 0;
}
