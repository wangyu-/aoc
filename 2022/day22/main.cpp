#include "bits/stdc++.h"
using namespace std;
#define mkp make_pair
int test = 0;

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

struct Pnt {
    int y, x;
    Pnt() = default;
    Pnt(int a, int b) : y(a), x(b) {}
    bool operator==(const Pnt &b) const {
        return y == b.y && x == b.x;
    }
    bool operator<(const Pnt &b) const {
        if (y != b.y)
            return y < b.y;
        return x < b.x;
    }
    Pnt operator+(const Pnt &b) const {
        return Pnt{y + b.y, x + b.x};
    }
    int &operator[](int idx) {
        assert(idx >= 0 && idx < 2);
        return idx == 0 ? y : x;
    }
    Pnt operator/(int a) {
        return Pnt{y / a, x / a};
    }
    Pnt operator%(int a) {
        return Pnt{y % a, x % a};
    }
    int nonzero_axis() {
        if (y && !x) return 0;
        else if (x && !y) return 1;
        else assert(0 == 1);
    }
};

struct Pnt3D {
    int z, y, x;
    Pnt3D() = default;
    Pnt3D(int a, int b, int c) : z(a), y(b), x(c){};
    int &operator[](int idx) {
        assert(idx >= 0 && idx < 3);
        if (idx == 0)
            return z;
        else if (idx == 1)
            return y;
        else
            return x;
    }
    bool operator==(const Pnt3D &b) const {
        return z == b.z && y == b.y && x == b.x;
    }
};

struct Face { //surface
    Pnt3D corners[4]; // 4 corners, each has a coordinate in 3D. 
    // to map with direct easily, upper-right has idx zero
    bool resolved = 0;
    map <int, pair<Pnt, int>> mapping; // maps direction on this face to another face
};

int EDGE_SIZE = -1;
map<Pnt, Face> faces; // all surfaces
map<int, map<int, char>> mat; // stores the input
int y_size = -1, x_size = -1; // input size

Pnt dir[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
Pnt start = {-1, -1};
int dir_idx = 0; //starting dir's idx

// calculate the coordiante of 4 corner of each faces by flood fill.
void flood_fill(Pnt face_id) {
    auto &face = faces[face_id];
    int invariant_axis = -1;
    for (int i = 0; i < 3; i++) {
        int all_same = 1;
        for (int j = 1; j <= 3; j++) {
            if (face.corners[j][i] != face.corners[0][i]) {
                all_same = 0;
                break;
            }
        }
        if (all_same) {
            invariant_axis = i;
            break;
        }
    }
    assert(invariant_axis != -1);
    for (int i = 0; i < 4; i++) {
        Pnt next_face_id = face_id + dir[i];
        if (faces.find(next_face_id) == faces.end() || faces[next_face_id].resolved) {
            continue;
        }
        auto &next_face = faces[next_face_id];
        next_face.resolved = 1;
        // adjecent corner's idx on the new face
        int near_corner1 = (i + 2 + 1) % 4;
        int near_corner2 = (i + 2) % 4;

        int far_corner1 = i;
        int far_corner2 = (i + 1) % 4;

        next_face.corners[near_corner1] = face.corners[far_corner1];
        next_face.corners[near_corner2] = face.corners[far_corner2];

        next_face.corners[far_corner1] = face.corners[far_corner1];
        next_face.corners[far_corner1][invariant_axis] ^= 1;

        next_face.corners[far_corner2] = face.corners[far_corner2];
        next_face.corners[far_corner2][invariant_axis] ^= 1;
        flood_fill(next_face_id);
    }
};

bool same_edge(Pnt3D a, Pnt3D b, Pnt3D c, Pnt3D d) {
    return (a == c && b == d) || (a == d && b == c);
}

// find matching edges, and generate mapping info
void generate_mapping() {
    for (auto it1 = faces.begin(); it1 != faces.end(); it1++) {
        auto &face1 = it1->second;
        for (auto it2 = faces.begin(); it2 != faces.end(); it2++) {
            auto &face2 = it2->second;
            if (it2 == it1)
                continue;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (same_edge(face1.corners[i], face1.corners[(i + 1) % 4], face2.corners[j], face2.corners[(j + 1) % 4])) {
                        face1.mapping[i] =  mkp(it2->first, (j + 2) % 4);
                    }
                }
            }
        }
    }
}

//transfrom point on one face to another face
Pnt trans(Pnt a, int old_dir, int new_dir) {
    int move_axis_old = dir[old_dir].nonzero_axis();
    int move_axis_new = dir[new_dir].nonzero_axis();
    int another_axis_old = move_axis_old ^ 1;
    int another_axis_new = move_axis_new ^ 1;

    bool move_axis_need_invert = dir[old_dir][move_axis_old] * dir[new_dir][move_axis_new] > 0 ? 1 : 0;
    bool another_axis_need_invert = dir[(old_dir + 1) % 4][another_axis_old] * dir[(new_dir + 1) % 4][another_axis_new] > 0 ? 0 : 1;

    Pnt res;
    res[move_axis_new] = a[move_axis_old];
    res[another_axis_new] = a[another_axis_old];

    if (move_axis_need_invert)
        res[move_axis_new] = EDGE_SIZE - 1 - res[move_axis_new];
    if (another_axis_need_invert)
        res[another_axis_new] = EDGE_SIZE - 1 - res[another_axis_new];
    return res;
};

// from current state to next state
pair<Pnt, int> next_state(Pnt cur, int dir_idx) {
    Pnt face_id;
    face_id.y = cur.y / EDGE_SIZE;
    face_id.x = cur.x / EDGE_SIZE;
    
    Pnt rel;
    rel.y = cur.y % EDGE_SIZE;
    rel.x = cur.x % EDGE_SIZE;

    Pnt next_rel = rel;
    next_rel = next_rel + dir[dir_idx];

    bool same_face = (next_rel.y < EDGE_SIZE && next_rel.y >= 0 && next_rel.x < EDGE_SIZE && next_rel.x >= 0);

    if (same_face ) // still same face;
    {
        Pnt res = cur + dir[dir_idx];
        // printf("normal move %d\n",same_face);
        return mkp(res, dir_idx);
    }

    int new_dir = faces[face_id].mapping[dir_idx].second;
    Pnt new_face = faces[face_id].mapping[dir_idx].first;
    Pnt new_rel = trans(rel, dir_idx, new_dir);
    Pnt res{new_face.y * EDGE_SIZE, new_face.x * EDGE_SIZE};
    res = res + new_rel;

    return mkp(res, new_dir);
};


int main() {
    auto lines = readlines();
    // lines.pop_back();
    string inst = lines[ssize(lines) - 1];

    lines.pop_back();
    lines.pop_back();

    y_size = ssize(lines);
    for (auto line : lines) {
        x_size = max<int>(x_size, ssize(line));
    }
    printf("<sizes= %d %d>\n", y_size, x_size);

    int point_cnt = 0;
    for (int i = 0; i < ssize(lines); i++) {
        for (int j = 0; j < x_size; j++) {
            mat[i][j] = (j < ssize(lines[i]) ? lines[i][j] : ' ');
            if (mat[i][j] != ' ') {
                point_cnt++;
            }
        }
    }
    assert(point_cnt % 6 == 0);
    EDGE_SIZE = sqrt(point_cnt / 6) + 0.5;
    assert(EDGE_SIZE * EDGE_SIZE == point_cnt / 6);

    // find start position
    for (int x = 0; x < x_size; x++) {
        if (mat[0][x] == '.') {
            start = Pnt{0, x};
            break;
        }
    }

    // find all existing faces
    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size; j++) {
            if (mat[i][j] != ' ') {
                faces[Pnt{i / EDGE_SIZE, j / EDGE_SIZE}];
            }
        }
    }

    // fill info of the face containing the start point
    auto &start_face = faces[start / EDGE_SIZE];
    start_face.resolved = 1;
    start_face.corners[0] = Pnt3D{1, 0, 1};
    for (int i = 1; i <= 3; i++) {
        start_face.corners[i] = start_face.corners[i - 1];
        start_face.corners[i].y += dir[i].y;
        start_face.corners[i].x += dir[i].x;
    }

    // fill info of other faces by flood fill
    flood_fill(start / EDGE_SIZE);
    // find matching edges use the coordination of corners, and generate direction mapping between faces
    generate_mapping();

    auto walks = split_c(inst, "LR");
    auto turns = split_c(inst, "1234567890");

    vector<string> all;
    for (int i = 0; i < ssize(walks); i++) {
        all.push_back(walks[i]);
        if (i < ssize(turns))
            all.push_back(turns[i]);
    }

    Pnt cur = start;
    for (auto ins : all) {
        if (ins == "L") {
            dir_idx = (dir_idx - 1 + 4) % 4;
            continue;
        } else if (ins == "R") {
            dir_idx = (dir_idx + 1) % 4;
            continue;
        }
        int nmoves = stoi(ins);
        while (nmoves--) {
            // printf("<<<%d>>>\n",face);
            auto res = next_state(cur, dir_idx);
            auto next = res.first;
            if (mat[next.y][next.x] == '#') {
                break;
            } else {
                cur = next;
                dir_idx = res.second;
            }
        }
    }
    printf("<y=%d x=%d dir=%d>\n", cur.y + 1, cur.x + 1, dir_idx);
    printf("<ans=%d>\n", (cur.y + 1) * 1000 + (cur.x + 1) * 4 + dir_idx);

    return 0;
}
