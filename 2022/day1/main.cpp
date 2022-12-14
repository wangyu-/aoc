#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int test=1;
#else
int test=0;
#endif

int main()
{
    long long sum=0;
    long long ans=-1;
    vector<long long> v;
    for (int i=0;;i++) {
        int a;
        if(scanf("%d",&a)!=1) break;
        if(a!=-1){
	    sum+=a;
        }else{
	    v.push_back(sum);
                //ans=max(sum,ans);
                sum=0;
        }

    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    printf("<<<%lld>>>", v[0]+v[1]+v[2]);
    return 0;
}
