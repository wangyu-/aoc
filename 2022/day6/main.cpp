#include <bits/stdc++.h>
int a,b;
int main(){
        std::string str;
        std::cin>>str;
        b=13;
        bool found=false;
        std::set<char> s;
        while(!found){
                printf("<a=%d b=%d>\n",a,b);
                for(int i=a;i<=b;i++){
                        auto it = s.insert(str[i]);
                        if(it.second==false){ //didn't insert, item already in set
                                a=a+1;
                                b=a+13;
                                s.clear();
                                break;
                        }
                }
                if(b>str.size()){std::cout<<"oops"<<std::endl;return 0;}
                if(s.size()==14)found=true;
        }
        std::cout<<b+1;
}
