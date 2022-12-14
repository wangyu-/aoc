#include <bits/stdc++.h>
using namespace std;

char f[1000][1000];
char v[1000][1000];
int y_size,x_size;
struct point_t{
    int x, y;
    int dir_x, dir_y;
    point_t() = default;
    point_t(int a,int b,int c,int d):x(a),y(b),dir_x(c),dir_y(d){};
};
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int oob(int y,int x){
    if(y>=y_size||y<0) return 1;
    if(x>=x_size||x<0) return 1;
    return 0;
}
int main(){
    for(int i=0;;i++){
	if(scanf("%s",f[i])!=1) break;
	y_size++;
    }
    x_size= strlen(f[0]);
    vector<point_t> start_vec;
    for(int x=0;x<x_size;x++){
	start_vec.push_back(point_t{x,0,0,1});
	start_vec.push_back(point_t{x,y_size-1,0,-1});
    }
    for(int y=0;y<y_size;y++){
	start_vec.push_back(point_t{0,y,1,0});
	start_vec.push_back(point_t{x_size-1,y,-1,0});
    }
    for(int i=0;i<(int)start_vec.size();i++) {
	auto &pnt = start_vec[i];
	int max_h= f[pnt.y][pnt.x];
	v[pnt.y][pnt.x]=1;
	for(int j=1;;j++) {
	    int new_y=pnt.y+pnt.dir_y*j;
	    int new_x=pnt.x+pnt.dir_x*j;
	    if( oob (new_y,new_x) ) break3;
	    if (f[new_y][new_x] > max_h) {
		max_h=f[new_y][new_x];
		v[new_y][new_x]=1;
	    }
	}
    }
    int vis_cnt=0;
    for(int y=0;y<y_size;y++)
	for(int x=0;x<x_size;x++)
	    if(v[y][x]) vis_cnt++;
    printf("%d",vis_cnt);
    return 0;
}
