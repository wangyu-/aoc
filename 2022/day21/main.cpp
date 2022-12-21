#include "mylibs.h"
#include <cassert>
#include <ratio>
#include <string>
using namespace std;
#define pii pair<int, int>
#define pll pair<long, long>
#define mkp make_pair
int test = 0;

#define M 10000

std::ostream& operator<<(std::ostream& o, const __int128& x) {
    if (x == std::numeric_limits<__int128>::min()) return o << "-170141183460469231731687303715884105728";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << x / 10 << (char)(x % 10 + '0');
}

//map <string,int> values;
struct exp_t{
    string name;
    string a;
    __int128 va;
    string op;
    string b;
    __int128 vb;
    __int128 value;
    int done=0;

    __int128 goal;
    bool has_goal=0;
    void prt()
    {
        if(done==1) return ;
        cout<<name<<":";
        if(a.empty()) cout<<va;
        else cout<<a;
        cout<<" "<<op<<" ";
        if(b.empty()) cout<<vb;
        else cout<<b;
        if(has_goal) {
            cout<<"(goal:"<<goal<<")";
        }
        cout<<endl;
    }
};
map <string, exp_t> exps;

int main() {
    auto lines=readlines();
    //int last=301;
    if(1)
    {
        exps.clear();
        for(auto line :lines){
            auto words= split_s(line, ": ");
            auto exp_str= split_c(words[1], " ");
            if(exp_str.size()==1) {
                exp_t e;
                e.name=words[0];
                e.value= stoi(exp_str[0]);
                e.done=1;
                exps[words[0]]=e;
                //values[words[0]]=stoi(exp[0]);
            }
            else {
                exp_t e;
                e.name=words[0];
                e.a= exp_str[0];
                e.b= exp_str[2];
                e.op= exp_str[1];
                exps[words[0]]=e;
            }
        }

        exps["humn"].value=20000ll;
        exps["humn"].done=0;
        //last*=2;
        while(1){
            int changed=0;
            for( auto it =exps.begin();it!=exps.end();it++)
            {
                if(it->first == "root" && exps[it->second.a].done && exps[it->second.b].done) {
                    cout<<"root1:"<<exps[it->second.a].value<<endl;
                    cout<<"root2:"<<exps[it->second.b].value<<endl;
                    cout<<"------"<<endl;
                    //cout<<it->second.value<<endl;
                    //printf("<ans=%ld>", it->second.value);
                    goto line1;
                }
                if(it->second.done) continue;
                if(it->first== "humn") continue;
                
                if(exps[it->second.a].done  &&  exps[it->second.b].done) {
                    __int128 a,b;__int128 r;
                    a= exps[it->second.a].value;
                    b= exps[it->second.b].value;
                    string op=it->second.op;
                    if(op=="+") r=a+b;
                    else if(op=="-") r=a-b;
                    else if(op=="*") r=a*b;
                    else if(op=="/") r=a/b;
                    else assert(0==1);
                    it->second.done=1;
                    it->second.value=r;
                    changed=1;
                }
            }
            if(!changed) break;
        }
        line1: ;
        for( auto it =exps.begin();it!=exps.end();it++){
            if (it->second.done ==0) {
                string a=it->second.a,op=it->second.op,b=it->second.b;

                if(exps[a].done) {it->second.va= exps[a].value; it->second.a="";}
                if(exps[b].done) {it->second.vb= exps[b].value; it->second.b="";}

                if(it->first=="root") { 
                    it->second.op="=";
                    assert(it->second.b.empty());
                    exps[a].goal=it->second.vb;
                    exps[a].has_goal=1;
                }
            }
        }

        while(1)
        {
            int changed=0;
            for( auto it =exps.begin();it!=exps.end();it++){
                if (it->second.done !=0) continue;
                if(it->second.has_goal && it->first!= "humn") {
                    string a=it->second.a,op=it->second.op, b=it->second.b;
                    it->second.done=2;
                    changed=1;
                    if(it->second.op == "*") {
                        if(a.empty()) {
                            exps[b].goal= it->second.goal /it->second.va;
                            //printf("<<<%s>>>\n",b.c_str());
                            exps[b].has_goal=1;
                        }else {
                            exps[a].goal= it->second.goal /it->second.vb;
                            exps[a].has_goal=1;
                        }
                    }
                    else if(it->second.op == "+") {
                        if(a.empty()) {
                            exps[b].goal= it->second.goal -it->second.va;
                            exps[b].has_goal=1;
                        }else {
                            exps[a].goal= it->second.goal -it->second.vb;
                            exps[a].has_goal=1;
                        }
                    }
                    else if(it->second.op == "-") {
                        if(a.empty()) {
                            exps[b].goal= it->second.va -it->second.goal;
                            exps[b].has_goal=1;
                        }else {
                            exps[a].goal= it->second.vb + it->second.goal;
                            exps[a].has_goal=1;
                        }
                    } else if(it->second.op == "/") {
                        if(a.empty()) {
                            exps[b].goal= it->second.va /it->second.goal;
                            exps[b].has_goal=1;
                        }else {
                            exps[a].goal= it->second.vb * it->second.goal;
                            exps[a].has_goal=1;
                        }
                    }
                }
            }
            if(!changed) break;
        }
        for(auto it=exps.begin();it!=exps.end();it++) {
            //it->second.prt();
        }
    }
    cout<<"ans:"<<exps["humn"].goal<<endl;
    return 0;
}
