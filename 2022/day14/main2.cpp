#include <bits/stdc++.h>
#include <pasring.h>
using namespace std;
char mat[1000][1000];
struct pnt_t {
    int y,x;
    pnt_t () =default;
    pnt_t (int a,int b):y(a),x(b){}
    bool operator == (pnt_t b){
	return y==b.y&&x==b.x;
    }
};
int sx=500,sy=0;
int oob(pnt_t a){
    if(a.x<0||a.x>=1000) return 1;
    if(a.y<0||a.y>=1000) return 1;
    return 0;
}
int dir_y[]={1,1,1};
int dir_x[]={0,-1,1};
pnt_t get_next(pnt_t old)
{
    pnt_t nxt;
    for(int i=0;i<3;i++) {
	nxt.y=old.y+dir_y[i];
	nxt.x=old.x+dir_x[i];
        if(oob(nxt)) return pnt_t{-1,-1};
	if(mat[nxt.y][nxt.x]=='.') return nxt;
    }
    return old;
}
pnt_t get_final(pnt_t old)
{
    
    while(1)
    {
	pnt_t nxt=get_next(old);
	if(nxt.y==-1) return pnt_t{-1,-1};
	if(nxt==old) return nxt;
	old=nxt;
    }
}
void ppp()
{
    for(int y=0;y<=15;y++){
	for(int x=490;x<510;x++) {
	    printf("%c",mat[y][x]);
	}
	printf("\n");
    }
}
int ff=-1;
int main(){
    auto lines=get_lines();
    memset(mat,'.',sizeof(mat));
    int y_max=0;
    for(auto line : lines) {
	auto ds= split_bc(line," ->\n");
	vector<pnt_t> vec;
	for(auto d:ds) {
	    int y,x;
	    sscanf(d.c_str(),"%d,%d",&x,&y);
	    y_max=max(y_max,y);
	    vec.push_back(pnt_t{y,x});
	}
	printf("<%d>\n",(int)vec.size());
	for(int i=1;i<int(vec.size());i++){
	    pnt_t old= vec[i-1], now= vec[i];
	    assert(old.y!=now.y||old.x!=now.x);
	    if(old.y!=now.y) {
		if(old.y>now.y) swap(old.y,now.y);
		for(int j=old.y;j<=now.y;j++) {
		    mat[j][now.x]='#';
		}
	    }else
	    {
		if(old.x>now.x) swap(old.x,now.x);
		for(int j=old.x;j<=now.x;j++) {
		    mat[now.y][j]='#';
		}
	    }
	}
    }
    ff= y_max+2;
    int cnt=0;
    for(int x=0;x<1000;x++){
	mat[ff][x]='#';
    }
     
    for(;;){
	pnt_t s= pnt_t{sy,sx};
	if(mat[s.y][s.x]=='o') {
	    printf("<real ans=%d>",cnt);
	    break;
	}
	pnt_t ne= get_final(s);
	if(ne.y==-1){
	    assert(0==1);
	    printf("<ans=%d>\n", cnt);
	    break;
	}
	else {
	    mat[ne.y][ne.x]='o';
	    cnt++;
	}
    }
    ppp();
    printf("<floor=%d>\n",ff);
    
    return 0;
}
