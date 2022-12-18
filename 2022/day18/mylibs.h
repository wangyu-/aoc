#include <bits/stdc++.h>
using namespace std;

struct pnt_t {
    int y,x;
    pnt_t () =default;
    //pnt_t (const pnt_t &b):y(b.y),x(b.x){}OD
    pnt_t (int a,int b):y(a),x(b){}
    /*pnt_t &operator =(const pnt_t &b) {
	this->y=b.y;this->x=b.x;
	return *this;
	}*/

    bool operator == (const pnt_t &b) const{
	return y==b.y&& x==b.x;
    }
    
    bool operator < (const pnt_t &b) const{
	if(y!=b.y) return y<b.y;
	return x<b.x;
    }
};



struct pnt_hash{
    size_t operator () (const pnt_t & a) const
	{
	    return a.y*10 +a.x;
	}
};

vector<string> readlines()
{
    vector<string> res;
    string s;
    while(getline(cin,s)) {
	res.push_back(s);
    }
    return res;
}
string trim(const string &str, const string &in_sp)
{
    deque<char> q(str.begin(),str.end());
    unordered_set<char> sp;
    for(auto c: in_sp) sp.insert(c);
    while(!q.empty() && sp.find(q.front())!=sp.end()) {
	q.pop_front();
    }
    while(!q.empty() && sp.find(q.back())!=sp.end()) {
	q.pop_back();
    }
    return string(q.begin(),q.end());
}
vector<string> split_c(const string &str,const string &in_sp)
{
    vector<string> res;
    unordered_set<char> sp;
    for(auto c: in_sp) sp.insert(c);
    string current;
    for(auto c: str){
	if(sp.find(c)==sp.end()) {
	    current+= c;
	}else{
	    if(!current.empty()) {
		res.push_back(current);
		current.clear();
	    }
	}
    }
    if(!current.empty()) res.push_back(current);
    return res;
}
vector<string> split_s(const string &str,const string &sp)
{
    vector<string> res;
    size_t i=0, pos;
    for(;;i=pos + sp.length()){
	pos=str.find(sp,i);
	if(pos==string::npos) {
	    res.push_back(str.substr(i,pos));
	    break;
	}
	else {
	    res.push_back(str.substr(i,pos-i));
	}
    }
    return res;
}
template <typename T>
void prt_arr(const T &arr)
{
    for(int i=0;i<(int)arr.size();i++){
	cout<<"<"<<arr[i]<<">";
    }
    cout<<endl;
}
template <typename T>
T my_slice(const T &arr, int begin,int end)
{
    if(end<0) end =(int) arr.size() +end;
    T new_arr (arr.begin()+begin,arr.begin()+end);
    return new_arr;
}
