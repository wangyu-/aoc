#include "bits/stdc++.h"
#include "mylibs.h"
#include <cassert>
#include <cstdio>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

Pnt dir[4][3]= {
    {{-1,0}, {-1,-1},{-1,1}},
    {{1,0}, {1,-1},{1,1}},
    {{0,-1}, {-1,-1},{1,-1}},
    {{0,1}, {-1,1},{1,1}}
};

unordered_set<Pnt,PntHash> mat;
unordered_map<Pnt,int,PntHash> des;
int g_idx=0;
bool has_adj(Pnt cur)
{
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++){
            if(i==0 && j==0 ) continue;
                if(mat.find(Pnt{cur.y+i, cur.x+j})!=mat.end()) return 1;
        }
    return 0;
}
bool dir_ok(Pnt cur, int idx) {
    for(int i=0;i<3;i++){
        if(mat.find( cur+ dir[idx][i])!= mat.end()) {
            return 0;
        }
    }
    return 1;
}
int get_dir(Pnt cur){
    for(int i=0;i<4;i++) {
        int real_idx= (i+g_idx)%4;
        if(dir_ok(cur, real_idx)) return real_idx;
    }
    return -1;

}
void insert_des(Pnt a)
{
    if(des.find(a)==des.end()) {
        des[a]=0;
    }
    des[a]++;
}
const int inf=1000*1000*1000;
int y_low=inf,y_high=-inf,x_low=inf,x_high=-inf;
void stat()
{
    y_low=inf,y_high=-inf,x_low=inf,x_high=-inf;
    for(auto p:mat) {
        if( p.y <y_low) y_low=p.y;
        if(p.y>y_high) y_high=p.y;
        if(p.x< x_low) x_low=p.x;
        if(p.x>x_high) x_high=p.x;
    }
}
void prt() {
    for(int i=y_low;i<=y_high;i++) {
        for(int j=x_low;j<=x_high;j++) {
            if( mat.find(Pnt{i,j})==mat.end()) {
                printf(".");
            }else printf("#");
        }
        printf("\n");
    }
    printf("\n");
}
int main() {
    auto lines=readlines();
    for(int i=0;i<sz(lines);i++){
        for(int j=0;j<sz(lines[i]);j++) {
            if(lines[i][j]=='#'){
                mat.insert(Pnt{i,j});
            }
        }
    }

    for(int round=1;;round++){
        des.clear();

        for(auto p : mat) {
            int idx=-1; 
            if(has_adj(p))
                idx= get_dir(p);
            if (idx==-1) continue; 
            Pnt new_p= p +dir[idx][0];
            insert_des( new_p);
        }

        int cnt=0;
        decltype(mat) mat_new;
        for(auto p : mat) {
            int idx=-1; 
            if(has_adj(p))
                idx= get_dir(p);
            if(idx==-1)  {mat_new.insert( p); continue;}
            Pnt new_p= p +dir[idx][0];
            assert((des.find(new_p)!=des.end()));
            if(des[new_p] == 1) {
                cnt++;
                mat_new.insert(new_p);
            }
            else mat_new.insert(p);
        }
        if(cnt==0) {
            printf("<<ans2=%d>>\n",round);
            break;
        }
        mat=mat_new;
        stat();
        //printf("-------\n");
        //
        prt();
        g_idx++;
    }
    stat();
    long ans= (y_high-y_low+1l) *(x_high-x_low+1l) -sz(mat);
    //printf("<ans=%ld>\n",ans);


    return 0;
}
