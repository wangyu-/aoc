#include <bits/stdc++.h>
using namespace std;

tuple<int,int> func()
{
    return make_tuple(3,4);
}
int main(){
    auto [x,y]= func();
    cout<<x<<","<<y<<endl;
    /*
        const int inf=1e9;
        vector<int> A={6,2,1,9,3,6,1,6,1,2,3,4,5,6,7,8,9,6,5};
        auto d=vector<int>(A.size(),inf);
        auto f=d;
        unordered_map<int, int>  mp;
        for(int i=(int)A.size() -1;i>=0;i--){
                int a=A[i];
                if(mp.find(a)!=mp.end()) {
                        d[i]=mp[a];
                }
                mp[a]=i;
        }
        for(int i=(int)A.size()-2;i>=0;i--){
                f[i]=min(d[i],f[i+1]);
        }
        auto print_array = [](vector<int> &v) {
                for(int i=0;i<(int)v.size();i++){
                        if(v[i]==inf) printf(" inf");
                        else printf(" %2d ",v[i]);
                }
                printf("\n");
        };
        printf("   ");
        for(int i=0;i<A.size();i++){
                printf(" %2d ",i);
        }
        printf("\n");
        printf("A: "); print_array(A);
        printf("d: "); print_array(d);
        printf("f: "); print_array(f);
    */
}
