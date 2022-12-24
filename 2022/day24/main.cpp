#include "bits/stdc++.h"
#include "mylibs.h"
#include <cassert>
#include <cstdio>
#include <iterator>
#include <string>
using namespace std;
#define mkp make_pair
#define sz(x) ((int)x.size())
int test = 0;

Pnt dir[5]= {
    {0,1},
    {1,0},
    {0,-1},
    {-1,0},
    {0,0}
};

unordered_set<Pnt,PntHash> blz[4];

int y_size=0;
int x_size=-1;

struct Item{
    Pnt pos;
    int step;
};
map<char,int> ctod;

unordered_map<int, unordered_map<Pnt, bool,PntHash> > visited;
Pnt g_st;
Pnt g_des;

int okay(Pnt pos, int step){
    if(! (pos==g_st)  &&! (pos==g_des)) {
        if(pos.y<0||pos.y>= y_size) return 0;
        if(pos.x<0||pos.x>= x_size) return 0;
    }
    for(int i=0;i<4;i++)
    {
        for(auto b: blz[i]){
            b= b+ dir[i] *step;
            b.y%=y_size; b.y+=y_size; b.y%=y_size;
            b.x%=x_size; b.x+=x_size; b.x%=x_size;
            //printf("<step=%d  %d,%d>\n", step, b.y,b.x);
            if(b==pos) {
                return 0;
            }
        }
    }
    return 1;
}
Item solve(Item init, Pnt des)
{
    queue<Item> q;
    Item start=init ; 
    visited[start.step][start.pos];
    q.push(start);
    while(!q.empty()){
        //printf("!\n");
        Item e= q.front();
        q.pop();
        for(int i=0;i<5;i++) {
            Item e2=  e;
            e2.step++;
            e2.pos=e2.pos+dir[i];
            if(okay(e2.pos, e2.step) ) {
                if(e2.pos==des) {
                    //printf("<ans=%d>\n",e2.step);
                    return e2;
                }
                if(visited[e2.step].find(e2.pos)==visited[e2.step].end())
                {
                    visited[e2.step][e2.pos];
                    q.push(e2);
                }
            }
        }
    }
    assert(0==1);
}
int main() {
    ctod['>']=0;ctod['v']=1;
    ctod['<']=2;ctod['^']=3;
    auto lines=readlines();
    y_size=sz(lines)-2;
    x_size=sz(lines[0])-2;
    printf("size=<%d,%d>\n",y_size,x_size);
    g_des.y=y_size;
    g_des.x=x_size-1;
    g_st.y=-1;
    g_st.x=0;
    for(int y=1;y<sz(lines);y++){
        for(int x=1;x<sz(lines[y]);x++){
            char c=lines[y][x];
            if(ctod.find(c)!=ctod.end()) {
                blz[ctod[c]].insert(Pnt{y-1,x-1});
                //printf("<%d,%d>\n", y-1,x-1);
            }
        }
    }

    Item state0; state0.step=0; state0.pos=g_st;
    Item state1= solve(state0,g_des);
    printf("<ans1=%d>\n",state1.step);
    Item state2= solve(state1, g_st);
    Item state3= solve(state2, g_des);
    printf("<ans2=%d>\n",state3.step);

    return 0;
}
