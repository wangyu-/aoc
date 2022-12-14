#include <bits/stdc++.h>
using namespace std;
vector<string> get_lines()
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
vector<string> split_bc(const string &str,const string &in_sp)
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
vector<string> split_bs(const string &str,const string &sp)
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
int main(){
    /*
    auto lines=get_lines();
    prt_v(lines);*/
    char a[1000]="abcd abc";
    auto lines2= split_bc(a, " ");
    prt_arr(lines2);
    auto lines3= split_bc(" 1122 33 44 ", " ");
    prt_arr(my_slice(lines3,1,3));
    auto lines4= split_bs("123zong345zongzong", "zong");
    prt_arr(lines4);
    string ss="asdasd";
    prt_arr(trim("  asdasd \n\t", " \n\t"));
    return 0;
}
