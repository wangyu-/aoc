#include "mylibs.h"
#include <array>
#include <cassert>
using namespace std;
#define pii pair<int, int>
#define pll pair<long, long>
#define mkp make_pair
int test = 0;
const int MAXN = 999;

const int R = 0;
const int D = 1;
const int L = 2;
const int U = 3;

int EDGE_SIZE = -1;

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
        if (y && !x)
            return 0;
        else if (x && !y)
            return 1;
        else
            assert(0 == 1);
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

struct Face {
    Pnt3D corners[4]; // 4 corners, each has a coordinate in 3D. upper-right has idx zero
    bool resolved = 0;
};

map<Pnt, Face> faces;

map<int, map<int, char>> mat;
Pnt dir[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
Pnt start = {-1, -1};
int dir_idx = 0;
int y_size = -1, x_size = -1;

struct Info {
    Pnt face;
    int new_dir;
    Info() = default;
    Info(Pnt a, int b) {
        face = a;
        new_dir = b;
    }
};
set<Pnt> all_possible;
map<Pnt, map<int, Info>> hard;

void add_case(Pnt a, int dir1, Pnt b, int dir2) {
    all_possible.insert(a);
    all_possible.insert(b);

    hard[a][dir1] = Info{b, (dir2 + 2) % 4};
    // hard[b][dir2]= Info{a,  (dir1+2)%4};
};

bool same_edge(Pnt3D a, Pnt3D b, Pnt3D c, Pnt3D d) {
    return (a == c && b == d) || (a == d && b == c);
}
void init() {
    for (auto it1 = faces.begin(); it1 != faces.end(); it1++) {
        auto &face1 = it1->second;
        for (auto it2 = faces.begin(); it2 != faces.end(); it2++) {
            auto &face2 = it2->second;
            if (it2 == it1)
                continue;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (same_edge(face1.corners[i], face1.corners[(i + 1) % 4], face2.corners[j], face2.corners[(j + 1) % 4])) {
                        add_case(it1->first, i, it2->first, j);
                    }
                }
            }
        }
    }
    /*
    add_case(Pnt{0,2},R, Pnt{2,1},R);
    add_case(Pnt{0,2},D, Pnt{1,1},R);
    add_case(Pnt{0,2},U, Pnt{3,0},D);

    add_case(Pnt{0,1},L, Pnt{2,0},L);
    add_case(Pnt{0,1},U, Pnt{3,0},L);

    add_case(Pnt{1,1},L, Pnt{2,0},U);

    add_case(Pnt{2,1},D, Pnt{3,0},R);*/
}

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

void prt(Pnt cur, Pnt next) {
    char save1 = mat[cur.y][cur.x];
    mat[cur.y][cur.x] = '@';
    char save2 = mat[next.y][next.x];
    mat[next.y][next.x] = '%';

    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            printf("%c", mat[y][x]);
        }
        printf("\n");
    }
    mat[cur.y][cur.x] = save1;
    mat[next.y][next.x] = save2;
}
pair<Pnt, int> next_ne2(Pnt cur, int dir_idx) {
    Pnt face;
    face.y = cur.y / EDGE_SIZE;
    face.x = cur.x / EDGE_SIZE;
    Pnt rel;
    rel.y = cur.y % EDGE_SIZE;
    rel.x = cur.x % EDGE_SIZE;

    Pnt next_rel = rel;
    next_rel = next_rel + dir[dir_idx];

    bool same_face = (next_rel.y < EDGE_SIZE && next_rel.y >= 0 && next_rel.x < EDGE_SIZE && next_rel.x >= 0);

    if (same_face || hard[face].find(dir_idx) == hard[face].end()) // still same face; or no special rul
    {
        Pnt res = cur + dir[dir_idx];
        // printf("normal move %d\n",same_face);
        return mkp(res, dir_idx);
    }

    int new_dir = hard[face][dir_idx].new_dir;
    Pnt new_face = hard[face][dir_idx].face;

    Pnt new_rel = trans(rel, dir_idx, new_dir);

    Pnt res{new_face.y * EDGE_SIZE, new_face.x * EDGE_SIZE};
    res = res + new_rel;

    printf("\nspecial move!!\n");
    printf("before: <%d,%d> (%d,%d) (%d,%d) %d\n", cur.y, cur.x, cur.y / EDGE_SIZE, cur.x / EDGE_SIZE,
           cur.y % EDGE_SIZE, cur.x % EDGE_SIZE, dir_idx);
    printf("after: <%d,%d> (%d,%d) (%d,%d) %d\n", res.y, res.x, res.y / EDGE_SIZE, res.x / EDGE_SIZE,
           res.y % EDGE_SIZE, res.x % EDGE_SIZE, new_dir);
    // prt(cur,res);
    return mkp(res, new_dir);
};

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
int main() {
    auto lines = readlines();
    // lines.pop_back();
    string inst = lines[ssize(lines) - 1];
    printf("%s\n", inst.c_str());
    lines.pop_back();
    lines.pop_back();
    int max_col = 0;
    for (auto line : lines) {
        max_col = max<int>(max_col, ssize(line));
    }
    printf("<max_col=%d>\n", max_col);
    int point_cnt = 0;
    for (int i = 0; i < ssize(lines); i++) {
        for (int j = 0; j < max_col; j++) {
            mat[i][j] = (j < ssize(lines[i]) ? lines[i][j] : ' ');
            if (mat[i][j] != ' ') {
                point_cnt++;
            }
        }
    }
    assert(point_cnt % 6 == 0);
    EDGE_SIZE = sqrt(point_cnt / 6) + 0.5;
    assert(EDGE_SIZE * EDGE_SIZE == point_cnt / 6);

    y_size = ssize(lines);
    x_size = max_col;

    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size; j++) {
            if (mat[i][j] != ' ') {
                faces[Pnt{i / EDGE_SIZE, j / EDGE_SIZE}];
            }
        }
    }

    printf("<sizes= %d %d>\n", y_size, x_size);

    for (int x = 0; x < max_col; x++) {
        if (mat[0][x] == '.') {
            start = Pnt{0, x};
            break;
        }
    }
    auto &start_face = faces[start / EDGE_SIZE];
    start_face.resolved = 1;
    start_face.corners[0] = Pnt3D{1, 0, 1};

    for (int i = 1; i <= 3; i++) {
        start_face.corners[i] = start_face.corners[i - 1];
        start_face.corners[i].y += dir[i].y;
        start_face.corners[i].x += dir[i].x;
    }

    flood_fill(start / EDGE_SIZE);
    init();

    for (auto pr : faces) {
        printf("face <%d,%d>:\n", pr.first.y, pr.first.x);
        assert(pr.second.resolved);
        for (int i = 0; i < 4; i++) {
            printf("(%d,%d,%d) ", pr.second.corners[i].z, pr.second.corners[i].y, pr.second.corners[i].x);
        }
        printf("\n");
    }

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
        // printf("current=<%d,%d>  <%d,%d> dir=%d\n",cur.y,cur.x, cur.y/MAGIC,cur.x/MAGIC ,face);
        // printf("<ins= %s>\n",ins.c_str());
        if (ins == "L") {
            dir_idx = (dir_idx - 1 + 4) % 4;
            continue;
        } else if (ins == "R") {
            dir_idx = (dir_idx + 1 + 4) % 4;
            continue;
        }
        int nmoves = stoi(ins);
        while (nmoves--) {
            // printf("<<<%d>>>\n",face);
            auto res = next_ne2(cur, dir_idx);
            auto next = res.first;
            // printf("<<<%d %d>>>\n",next.y,next.x);
            if (next.y < 0 || next.y >= y_size || next.x < 0 || next.x >= x_size) {
                printf("oops\n");
                exit(-1);
            }
            if (all_possible.find(Pnt{next.y / EDGE_SIZE, next.x / EDGE_SIZE}) == all_possible.end()) {
                printf("<<%d,%d>>\n", next.y / EDGE_SIZE, next.x / EDGE_SIZE);
                printf("oops2\n");
                exit(-1);
            }
            if (mat[next.y][next.x] == '#') {
                break;
            } else {
                cur = next;
                dir_idx = res.second;
            }
        }
    }
    printf("current=<%d,%d> face=%d\n", cur.y, cur.x, dir_idx);

    printf("<%d %d %d>\n", cur.y + 1, cur.x + 1, dir_idx);
    printf("<ans=%d>\n", (cur.y + 1) * 1000 + (cur.x + 1) * 4 + dir_idx);

    return 0;
}
