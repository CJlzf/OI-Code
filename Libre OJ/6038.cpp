#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#define N 300002
using namespace std;
vector<int> p[N];
int head[N], ver[N * 2], nxt[N * 2], l;
int type, n, q, i, fa[N], size[N], a[N], b[N], dis[N], f[N][22], dep[N], ans;
int read() {
    char c = getchar();
    int w = 0;
    while (c < '0' || c > '9') c = getchar();
    while (c <= '9' && c >= '0') {
        w = w * 10 + c - '0';
        c = getchar();
    }
    return w;
}
void insert(int x, int y) {
    l++;
    ver[l] = y;
    nxt[l] = head[x];
    head[x] = l;
}
int find(int x) {
    if (x != fa[x])
        fa[x] = find(fa[x]);
    return fa[x];
}
int LCA(int u, int v) {
    if (dep[u] > dep[v])
        swap(u, v);
    int tmp = dep[v] - dep[u];
    for (int i = 0; (1 << i) <= tmp; i++) {
        if ((1 << i) & tmp)
            v = f[v][i];
    }
    if (u == v)
        return u;
    for (int i = 19; i >= 0; i--) {
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    }
    return f[u][0];
}
void dfs(int x, int pre) {
    dep[x] = dep[pre] + 1;
    f[x][0] = pre;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (y != pre)
            dfs(y, x);
    }
}
void merge(int u, int v) {
    int tu = u, tv = v;
    u = find(u), v = find(v);
    if (size[u] > size[v])
        swap(u, v), swap(tu, tv);
    fa[u] = v;
    size[v] += size[u];
    insert(tu, tv);
    insert(tv, tu);
    dfs(tu, tv);
    for (int j = 0; j <= 19; j++) {
        for (int i = 0; i < p[u].size(); i++) f[p[u][i]][j + 1] = f[f[p[u][i]][j]][j];
    }
    for (int i = 0; i < p[u].size(); i++) p[v].push_back(p[u][i]);
    p[u].clear();
    int dis1 = dis[u], dis2 = dis[v];
    int dis3 = dep[a[u]] + dep[a[v]] - 2 * dep[LCA(a[u], a[v])];
    int dis4 = dep[a[u]] + dep[b[v]] - 2 * dep[LCA(a[u], b[v])];
    int dis5 = dep[b[u]] + dep[a[v]] - 2 * dep[LCA(b[u], a[v])];
    int dis6 = dep[b[u]] + dep[b[v]] - 2 * dep[LCA(b[u], b[v])];
    int maxx = max(max(dis1, dis2), max(max(dis3, dis4), max(dis5, dis6)));
    dis[v] = maxx;
    if (maxx == dis1)
        a[v] = a[u], b[v] = b[u];
    else if (maxx == dis3)
        b[v] = a[v], a[v] = a[u];
    else if (maxx == dis4)
        a[v] = a[u];
    else if (maxx == dis5)
        b[v] = a[v], a[v] = b[u];
    else if (maxx == dis6)
        a[v] = b[u];
}
int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }
int main() {
    type = read();
    n = read();
    q = read();
    for (i = 1; i <= n; i++) size[i] = dep[i] = 1, fa[i] = a[i] = b[i] = i;
    for (i = 1; i <= n; i++) p[i].push_back(i);
    for (i = 1; i <= q; i++) {
        int t = read();
        if (t == 1) {
            int u = read(), v = read();
            if (type == 1)
                u ^= ans, v ^= ans;
            merge(u, v);
        } else {
            int v = read();
            if (type == 1)
                v ^= ans;
            int fa = find(v);
            ans = max(dist(v, a[fa]), dist(v, b[fa]));
            printf("%d\n", ans);
        }
    }
    return 0;
}
