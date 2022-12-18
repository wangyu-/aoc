#include <bits/stdc++.h>
using namespace std;

struct pnt_t {
    int y,x;
    pnt_t () =default;
    
    pnt_t (int a,int b):y(a),x(b){}
    bool operator == (const pnt_t &other) const{
	return y==other.y&& x==other.x;
    }
    
    bool operator < (const pnt_t &other) const{
	if(y!=other.y) return y<other.y;
	return x<other.x;
    }
};

struct pnt_hash{
    size_t operator () (const pnt_t & a) const
	{
	    return a.y*1000007 +a.x;
	}
};
    
int main(){
    unordered_set<pnt_t,pnt_hash> st;
    for(int i=0;i<1000000;i++) {
	st.insert(pnt_t{-i,i*i});
    }
    cout<<st.size()<<endl;
    
}
