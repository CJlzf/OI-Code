#include <iostream>
#include <cstdio>
#define N 100002
using namespace std;
int head[N], ver[N * 2], nxt[N * 2], d[N], l;
int t, x, n, p0, p1, h0, h1, i, f[N][4], ans;
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
    d[x]++;
}
void dfs(int x, int pre) {
    int maxx = 0;
    f[x][0] = f[x][2] = f[x][3] = d[x];
    f[x][1] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (y != pre) {
            dfs(y, x);
            ans = max(ans, f[x][0] + f[y][3] - (x == 1));
            ans = max(ans, f[x][3] + f[y][0] - (x == 1));
            ans = max(ans, f[x][1] + f[y][2]);
            ans = max(ans, f[x][1] + f[y][1] - 1);
            ans = max(ans, f[x][2] + f[y][2] - (x == 1));
            ans = max(ans, f[x][2] + f[y][1] - (x == 1));
            f[x][1] = max(f[x][1], f[y][1]);
            f[x][1] = max(f[x][1], f[y][2] + 1);
            f[x][3] = max(f[x][3], f[x][0] + f[y][2] - 1);
            f[x][3] = max(f[x][3], f[x][2] + f[y][0] - 1);
            f[x][3] = max(f[x][3], f[y][3] + d[x] - 1);
            f[x][3] = max(f[x][3], f[y][0] + maxx + d[x] - 2);
            f[x][3] = max(f[x][3], f[x][0] + f[y][1] - 1);
            f[x][2] = max(f[x][2], f[x][0] + f[y][0] - 1);
            f[x][0] = max(f[x][0], f[y][0] + d[x] - 1);
            f[x][2] = max(f[x][2], f[x][0]);
            f[x][3] = max(f[x][3], f[x][2]);
            maxx = max(maxx, max(f[y][2], f[y][1]));
        }
    }
}
int main() {
    t = read();
    x = read();
    while (t--) {
        if (x == 0)
            n = read();
        else if (x == 1)
            n = read(), p0 = read(), p1 = read();
        else
            n = read(), p0 = read(), p1 = read(), h0 = read(), h1 = read();
        for (i = 1; i < n; i++) {
            int u = read(), v = read();
            insert(u, v);
            insert(v, u);
        }
        for (i = 2; i <= n; i++) d[i]--;
        dfs(1, 0);
        printf("%d\n", ans);
        for (i = 1; i <= n; i++) d[i] = head[i] = 0;
        l = ans = 0;
    }
}
