#include <bits/stdc++.h>
using namespace std;
vector<string> string_to_vec(const char * s,const char * sp) {
        vector<string> res;
        string str=s;
        char *p = strtok ((char *)str.c_str(),sp);
        while (p != NULL)
        {
                res.push_back(p);
                //printf ("%s\n",p);
                p = strtok(NULL, sp);
        }
        return res;
}
long cc=1;
struct monkey_t {
    vector<int> items;
    char op;
    int b;
    
    int td;
    int t1;
    int t2;

    int cnt=0;

    int new_value(long x)
	{
	    if(op=='*') return (x*b)%cc;
	    if(op=='+') return (x+b)%cc;
	    if(op=='^') return (x*x)%cc;
	    assert(0==1);
	}

    int tat(int x)
	{
	    if(x%td==0) return t1;
	    else return t2;
	}
};
vector<monkey_t> mks;
int main(){
    int ans=0;
    vector<string> input;
    for(int i=0;;i++){
	char s[1000];
	if(gets(s)==NULL) break;
	if(strlen(s)<5) continue;
        input.push_back(s);
        printf("<%s>",s);
    }
    assert(input.size()%6==0);

    for(int i=0;i<(int)input.size();i+=6) {
	monkey_t mk;
	string line1= input[i+1];
	line1= string_to_vec(line1.c_str(),":\n")[1];
	auto nums= string_to_vec(line1.c_str(),", ");
	for(auto n : nums) {
	    mk.items.push_back(stoi(n.c_str()));
	    //printf("<%s>",n.c_str());
	}
	string line2= input[i+2];
	char s[10]; int d=-100;
	sscanf(line2.c_str(), "  Operation: new = old %s %d",s,&d);
	mk.op=s[0];mk.b=d;
	if(d==-100) mk.op='^';
	//printf("<%c %d>",mk.op,mk.b);
	string line3=input[i+3];
	sscanf(line3.c_str(),"  Test: divisible by %d", &mk.td);
	cc*=mk.td;
	string line4=input[i+4];
	sscanf(line4.c_str(),"    If true: throw to monkey %d", &mk.t1);
	string line5=input[i+5];
	sscanf(line5.c_str(),"    If false: throw to monkey %d", &mk.t2);
	//printf("[%d %d %d]",mk.td,mk.t1,mk.t2);
	mks.push_back(mk);
    }

    printf("<<<cc==%ld>>>\n",cc);

    for (int round=0;round<10;round++)
    {
	printf("--------round begin---------\n");
	for(auto &mk: mks) {
	    for (auto &item : mk.items) printf("<%d>",item);
	    printf("\n");
	}
	for(int mi=0;mi<(int)mks.size();mi++) {
	    auto & mk= mks[mi];
	    for(auto item: mk.items) {
		
		int new_value= mk.new_value(item);
		//new_value/=3;
		int des= mk.tat(new_value);
		mks[des].items.push_back(new_value);
		mk.cnt++;
	    }
	    mk.items.clear();
	}
    }

    for (auto &mk: mks)
    {
	printf("<<cnt=%d>>\n",mk.cnt);
    }
    return 0;
}

