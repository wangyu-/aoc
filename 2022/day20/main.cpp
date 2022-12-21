#include "mylibs.h"
#include <cassert>
#include <vector>
#define pii pair<int, int>
#define pll pair<long, long>
#define mkp make_pair
int test = 0;
vector<pll> arr;
void prt()
{
    for(int i=0;i<ssize(arr);i++)
    {
        printf("<%ld>", arr[i].second);
    }
    printf("\n");
}
int main() {

    auto lines = readlines();
    int cnt=0;
    for (auto line : lines) {
        long a=stol(line);
        cout<<":"<<a<<endl;
        arr.push_back( mkp (cnt,a *811589153l) );
        cnt++;
    }
    //prt();
    int nnn=10;
    while(nnn--)
    {
        for(int i=0;i<ssize(arr);i++){
            printf("\n[%d]\n",i);
            long real_pos=-1;
            for(int j=0;j<ssize(arr);j++)
            {
                if( arr[j].first==i) {
                    real_pos=j;
                    break;
                }
            }
            assert(real_pos!=-1);
            printf("[real_pos=%ld]\n",real_pos);
            long n=arr[real_pos].second;
            int sign=1;
            long M=ssize(arr)-1;
            if(n==0) continue;

            long des= real_pos+ n + M;
            while(des <0) 
                des+= (abs(des)/M +1)*M;
            des%=M;

            printf("<des=%ld>\n",des);
            
            if(des==real_pos) continue;
            if(des==0) des= M;
            if(des>real_pos) { n=des-real_pos;}
            else {
                n=real_pos-des; sign=-1;
                } 

            //if(n<0) {sign=-1; n=-n;}
            //n=(n+M)%M;
            printf("[sign=%d n=%ld]\n",sign,n);
            while(n--)
            {
                long next= real_pos + sign;
                //int next= (real_pos+ sign +M)%M;
                swap(arr[real_pos], arr[next] );
                real_pos= next;
            }
            printf("after step %d\n",i);
            //prt();

        }
    }
    int zero_pos=-1;
    for(int i=0;i<ssize(arr);i++)
    {
        if(arr[i].second==0) {zero_pos=i; break;}
    }
    int M2=ssize(arr);

    printf("%ld\n",arr[(zero_pos+1000)%M2 ].second);
    printf("%ld\n",arr[(zero_pos+2000)%M2 ].second);
    printf("%ld\n",arr[(zero_pos+3000)%M2 ].second);

    printf("ans=%ld\n",arr[(zero_pos+1000)%M2 ].second+arr[(zero_pos+2000)%M2 ].second+ arr[(zero_pos+3000)%M2 ].second);

    return 0;
}
