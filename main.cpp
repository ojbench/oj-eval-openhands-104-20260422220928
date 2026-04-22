// Problem 104 - 采购
// BFS from start and from home, sum distances via any shop (4). Prints -1 if unreachable.
#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n columns, m rows
    if(!(cin >> n >> m)) return 0;
    vector<int> grid; grid.reserve((size_t)m * n);
    pair<int,int> S = {-1,-1}, T = {-1,-1};
    vector<pair<int,int>> shops;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int x; cin >> x;
            grid.push_back(x);
            if(x==2) S={i,j};
            else if(x==3) T={i,j};
            else if(x==4) shops.emplace_back(i,j);
        }
    }
    if(S.first==-1 || T.first==-1 || shops.empty()){
        cout << -1 << '\n';
        return 0;
    }
    auto idx = [n](int r,int c){ return r*n + c; };
    const int INF = -1;
    vector<int> distS(m*n, INF), distT(m*n, INF);

    auto can = [&](int r,int c){ return r>=0 && r<m && c>=0 && c<n && grid[idx(r,c)]!=1; };

    // BFS from S
    {
        deque<int> q;
        distS[idx(S.first,S.second)] = 0;
        q.push_back(idx(S.first,S.second));
        while(!q.empty()){
            int u = q.front(); q.pop_front();
            int r = u / n, c = u % n;
            int d = distS[u];
            const int dr[4] = {-1,1,0,0};
            const int dc[4] = {0,0,-1,1};
            for(int k=0;k<4;k++){
                int nr=r+dr[k], nc=c+dc[k];
                if(can(nr,nc)){
                    int v = idx(nr,nc);
                    if(distS[v]==INF){
                        distS[v]=d+1;
                        q.push_back(v);
                    }
                }
            }
        }
    }
    // BFS from T
    {
        deque<int> q;
        distT[idx(T.first,T.second)] = 0;
        q.push_back(idx(T.first,T.second));
        while(!q.empty()){
            int u = q.front(); q.pop_front();
            int r = u / n, c = u % n;
            int d = distT[u];
            const int dr[4] = {-1,1,0,0};
            const int dc[4] = {0,0,-1,1};
            for(int k=0;k<4;k++){
                int nr=r+dr[k], nc=c+dc[k];
                if(can(nr,nc)){
                    int v = idx(nr,nc);
                    if(distT[v]==INF){
                        distT[v]=d+1;
                        q.push_back(v);
                    }
                }
            }
        }
    }

    long long ans = LLONG_MAX;
    for(auto &p: shops){
        int v = idx(p.first,p.second);
        if(distS[v]!=INF && distT[v]!=INF){
            ans = min(ans, (long long)distS[v] + distT[v]);
        }
    }
    if(ans==LLONG_MAX) cout << -1 << '\n';
    else cout << ans << '\n';
    return 0;
}
