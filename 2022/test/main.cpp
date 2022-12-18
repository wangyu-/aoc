#include <bits/stdc++.h>
//#include "mylibs.h"
using namespace std;
#define pii pair<int,int>
#define mkp make_pair
int test=0;
struct pnt_t {
    int y,x;
    pnt_t () =default;
    pnt_t (int a,int b):y(a),x(b){}

    bool operator == (pnt_t b) const{
	printf("compare!! %d %d\n",b.y,b.x);
	//printf("compare! %d %d %d %d\n",y,x,b.y,b.x);
	int r= y==b.y&& x==b.x;
	//printf("<%d>",r);
	return r;
    }
    
    bool operator < (const pnt_t &b) const{
	if(y!=b.y) return y<b.y;
	return x<b.x;
    }
};


struct pnt_hash{
    size_t operator () (const pnt_t & a) const
	{
	    //return a.y+a.x;
	    return a.y*1000000007 +a.x;
	}
};
struct pnt_hash2{
    size_t operator () (const pnt_t & a) const
	{
	    //return a.y+a.x;
	    return a.y*1000000007 +a.x;
	}
};

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
	//st.max_load_factor(0.2);
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
	    printf("---begin---\n");
	    pnt_t ab= pnt_t{a.y+rr.y,a.x+rr.x};
	    //printf("<ins %d %d>\n",ab.y,ab.x);
	    ub=min(ub, ab.y);
	    assert(st.find(ab)==st.end());
	    int before= (int)st.size();
	    printf("<insert %d,%d>\n",ab.y,ab.x);
	    st.insert(ab);
	    int after=(int)st.size();
	    pnt_hash h;
	    if(after!=before+1) {
		printf("<after=%d before=%d   %d,%d   h=%ld>", after,before,ab.y,ab.x,  h(ab));
	    }
	    assert(after==before+1);
	    printf("----end----\n\n");
	}
    }

    void gc2() {
	unordered_set<pnt_t,pnt_hash> tmp;
	for(auto e:st) {
	    tmp.insert(e);
	}
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
    //printf("<len=%d>",(int)jet.size());
    for(int i=0;i<(int)pntss.size();i++){
	shape_t shape;
        shapes[i].pnts=pntss[i];
	shapes[i].init();
    }

    long left=1000000000000;
    for(int i=0;left>0;i++,left--){

	
	int type= i%5;
	pnt_t now = pnt_t{room.ub-4, 2};
	for(int j=0;;j++)
	{
	    pnt_t next2= pnt_t {now.y+1,now.x};
	    if(room.conflict(next2,type)) {
		assert(!room.conflict(now,type));
		room.ins(now,type);
		break;
	    }else {
		if(test)printf("<after fall, now %d %d>\n",now.y,now.x);
		now=next2;
	    }
	}
    }
    room.gc2();
    return 0;
}
