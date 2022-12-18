#include <bits/stdc++.h>
#include "mylibs.h"
using namespace std;
#define pii pair<int,int>
#define mkp make_pair
int test=0;

const int M=50;
int space[M][M][M];

void ffill(char a,char b,char c)
{
    if(a<0||a>=M) return;
    if(b<0||b>=M) return;
    if(c<0||c>=M) return;
    
    if(space[a][b][c]==-1||space[a][b][c]==1) return;

    space[a][b][c]=-1;
    
    ffill(a-1,b,c);
    ffill(a+1,b,c);
    ffill(a,b+1,c);
    ffill(a,b-1,c);
    ffill(a,b,c+1);
    ffill(a,b,c-1);
}
int main(){
    int cnt=0;
    memset(space,0,sizeof(space));
    auto lines=readlines();
    for(auto line: lines)
    {
	int a,b,c;
	sscanf(line.c_str(),"%d,%d,%d",&a,&b,&c);
	//printf("<%d,%d,%d>",a,b,c);
	a++;b++;c++;
	assert (a>0&&a<M);
	assert( b>0 &&b<M);
	assert (c>0 && c<M);

	space[a][b][c]=1;
    }
    for(int i=1;i<M;i++)
	for(int j=1;j<M;j++)
	    for(int k=1;k<M;k++)
	    {
		if(space[i][j][k]==1){
		    cnt+= space[i-1][j][k] ==0;
		    cnt+= space[i+1][j][k] ==0;
		    cnt+= space[i][j-1][k] ==0;
		    cnt+= space[i][j+1][k] ==0;
		    cnt+= space[i][j][k-1] ==0;
		    cnt+= space[i][j][k+1] ==0;
		}
	    }
    printf("ans1=%d\n",cnt);
    cnt=0;
    ffill(0,0,0);
    for(int i=1;i<M;i++)
	for(int j=1;j<M;j++)
	    for(int k=1;k<M;k++)
	    {
		if(space[i][j][k]==1){
		    cnt+= space[i-1][j][k] ==-1;
		    cnt+= space[i+1][j][k] ==-1;
		    cnt+= space[i][j-1][k] ==-1;
		    cnt+= space[i][j+1][k] ==-1;
		    cnt+= space[i][j][k-1] ==-1;
		    cnt+= space[i][j][k+1] ==-1;
		}
	    }
    printf("ans2=%d\n",cnt);
    //printf("<ans=%d   delta=%ld    final=%ld>\n",room.ub,delta, room.ub-delta);
    return 0;
}
