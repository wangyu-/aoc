#include <unordered_set>
#include <cstdio>
using namespace std;

struct Point {
    int y,x;
    Point (int a,int b):y(a),x(b){}
    
    bool operator == (const Point &b) const{
	//printf("compare!\n");
	return y==b.y&& x==b.x;
    }
};
struct PointHash{
    size_t operator () (const Point & a) const
	{
	    //return a.y+a.x;
	    return a.y* 1000000007 + a.x;
	}
};
unordered_set<Point,PointHash> st;

int main(){
    st.insert(Point(-3,2));
    st.insert(Point(-4,3));
    PointHash h;
    printf("<%lx>",(unsigned long)h(Point(-3,2)));
	   
    if( st.find(Point(-3,2)) == st.end()){
	printf("WTF!!!\n");
    }
  
    return 0;
}
