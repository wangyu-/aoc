#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int test=1;
#else
int test=0;
#endif

int main()
{
    char c='A';
    int a=c+c+c+c+c+c;
    cout<<a<<endl;
    /*
    foor(int i=0;i<26;i++)
    {
            p['a'+i]=i+1;
            p['A'+i]=i+27;
    }
    int sum=0;
    for (int i=0;;i++) {
            char s1[1000];
            char s2[1000];
            char s3[1000];
            int h1[128]={0};
            int h2[128]={0};
            if(scanf("%s %s %s",s1,s2,s3)!=3) break;
            int len1=strlen(s1);
            int len2=strlen(s2);
            int len3=strlen(s3);
            for(int j=0;j<len1;j++)
            {
                    h1[s1[j]]++;
            } 
            for(int j=0;j<len2;j++)
            {
                    h2[s2[j]]++;
            }
            for(int j=0;j<len3;j++)
            {
                    char c=s3[j];
                    if(h1[c]&&h2[c])
                    {
                            int tmp= p[c];
                            printf("<%d>\n",tmp);
                            sum+=tmp;
                            break;
                    }
            }
    }
    printf("%d\n",sum);*/
    return 0;
}
