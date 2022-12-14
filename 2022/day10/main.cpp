#include <bits/stdc++.h>
using namespace std;
int cycle=0;
int value=1;
map<int,int >mp;
long sum=0;
int record(){
    // for problem1
    if(mp.find(cycle)!=mp.end()){
	//1printf("cycle=%d value=%d\n",cycle,value);
	sum+=cycle*value;
    }
    // for problem 2
    int row= (cycle -1)/40;
    int col= (cycle -1)%40;
    if(col==0) printf("\n");
    if(abs(value -col)<=1) printf("# ");
    else printf(". ");
    return 0;
}
int main(){
    int ans=0;
    for(int i=20;i<=220;i+=40){
	mp[i]=1;
    }
    for(int i=0;;i++){
        char s[10];int d;
        if(scanf("%s",s)!=1) break;
	string str=s;
	if(str== "noop"){
	    cycle+=1;
	    record();
	}
	else if(str=="addx"){
	    scanf("%d",&d);
	    cycle+=1;
	    record();
	    cycle+=1;
	    record();
	    value+=d;
	}
	else {
	    assert(0==1);
	}
	
    }
    printf("\n<ans=%ld>\n",sum);
    return 0;
}
