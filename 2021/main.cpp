#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int test=1;
#else
int test=0;
#endif

int main()
{
    int cnt=0;
    int old;
    int a=0;
    int lg_cnt=0;
    for (int i=0;;i++) {
	old=a;
	if(scanf("%d",&a)!=1) break;
	if(i && a>old) lg_cnt++;
	cnt++;
	printf("<%d>\n",cnt);
    }
    printf("<<<%d>>>",lg_cnt);
    return 0;
}
