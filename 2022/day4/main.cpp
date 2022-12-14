#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int test=1;
#else
int test=0;
#endif

int fully_contains(int a,int b,int c, int d)
{
    if(b<=d &&a>=c  || b>=d &&a<=c) return 1;
    return 0;
}
int overlap(int a,int b,int c, int d)
{
    if(c>=a &&c<=b  ||c>=a &&c<=b) return 1;
    if(a>=c&&a<=d  || b>=c&&b<=d) return 1;
    return 0;
}

int main()
{
    int ans=0;
    for (int i=0;;i++) {
	int a,b,c,d;
	if(scanf("%d-%d,%d-%d",&a,&b,&c,&d)!=4) break;
	if(overlap(a,b,c,d)) ans++;
    }
    printf("%d\n",ans);
    return 0;
}
