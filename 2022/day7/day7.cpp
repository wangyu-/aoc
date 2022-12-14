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
struct node_t{
        string name;
        node_t * fa;
        long weight=0;
        long sum=0;
        map<string,node_t *> cld;
};
node_t * root;
node_t * current;
int ident=0;
long super_sum=0;
long dfs(node_t * node)
{
        ident++;
        for(int i=0;i<ident;i++) printf("  ");
        printf("<%s weight=%ld>\n", node->name.c_str(),node->weight);
        node->sum=node->weight;
        for(auto it= node->cld.begin();it!=node->cld.end();it++){
                node->sum+=dfs(it->second);
        }
        for(int i=0;i<ident;i++) printf("  ");
        printf("<%s sum=%ld>\n", node->name.c_str(),node->sum);
        ident--;
        if(node->sum<=100000) {
                super_sum+=node->sum;
        }
        return node->sum;
}
long goal;
long current_best=1e9;
void dfs2(node_t * node)
{
        if(node->sum >= goal)
        {
                current_best=min(current_best, node->sum);
        }
        for(auto it= node->cld.begin();it!=node->cld.end();it++){
                dfs2(it->second);
        }
}
int main(){
        int ans=0;
        vector< string> lines;
        for(int i=0;;i++){
                char s[10000];
                if(gets(s) == NULL ) break;
                lines.push_back(s);
        }
        for(int i=0;i<(int)lines.size();i++)
        {
                auto line= lines[i];
                auto vec=string_to_vec(line.c_str(),"\n ");
                if(vec[0]=="$") {
                        if(vec[1]=="cd") {
                                if(vec[2]=="/"){
                                        root= new node_t;
                                        root->fa=nullptr;
                                        root->name="/";
                                        current = root;
                                }
                                else if(vec[2]!=".."){
                                        printf("<entering %s>",vec[2].c_str());
                                        current->cld[vec[2]]=new node_t;
                                        auto p= current->cld[vec[2]];
                                        p->fa=current;
                                        p->name=vec[2];
                                        current=p;
                                }
                                else {
                                        current=current->fa;
                                }
                        } 
                        else if (vec[1] == "ls")
                        {
                                int cnt=0;
                                for(int j=i+1;j<(int)lines.size();j++)
                                {
                                        auto line2=lines[j];
                                        auto vec2=string_to_vec(line2.c_str(),"\n ");
                                        if(vec2[0]=="dir") continue;
                                        if(vec2[0]=="$") break;
                                        printf("<<%s>>",line2.c_str());
                                        int size=-1;
                                        sscanf(vec2[0].c_str(),"%d",&size);
                                        assert(size!=-1);
                                        //if(size==-1) break;
                                        current->weight+=size;
                                        printf("add <%s %d>\n",current->name.c_str(),size);
                                        cnt++; 
                                }
                                //i+=cnt;
                        }
                }
        }
        dfs(root);
        printf("ans1=%ld\n",super_sum);
        long disk_size= 70000000;
        long need_space=30000000;
        long total_sum= root->sum;
        long current_free= 70000000 - total_sum;
        long more_free_need= need_space - current_free;
        goal=more_free_need;
        dfs2(root);
        printf("ans2=%ld\n",current_best);
        return 0;
}
