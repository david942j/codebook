struct DomTree {
#define N (200010)
  // Everything is 1-based
  // idom of (s and all nodes unreachable from s) = 0
  int n;
  // n-indexed
  VI G[N]; int idom[N], dfn[N];
  // T-indexed
  VI rG[N], bkt[N];
  int T, par[N], dsu[N], label[N], nfd[N], sdom[N];
  void init(int _n) {
    n = _n;
    FOR1(i, n) G[i].clear(), rG[i].clear(),
      dfn[i] = 0, idom[i] = 0;
    T = 0;
  }
  void add_edge(int x, int y) {
    G[x].pb(y);
  }

  void build(int s) {
    dfs0(s);
    static int idom[N];
    FOR1(i, T) bkt[i].clear(), label[i] = i, sdom[i] = i, dsu[i] = i;
    for(int i=T;i>=2;i--) {
      for(int u: rG[i])
        miz(sdom[i], sdom[eval(u)]);
      bkt[sdom[i]].pb(i);
      dsu[i] = par[i]; // link(i, par[i]);
      for(int v: bkt[par[i]]) {
        const int u = eval(v);
        if(sdom[u] < sdom[v]) idom[v] = u;
        else idom[v] = sdom[v];
      }
      bkt[par[i]].clear();
    }
    for(int i=2;i<=T;i++)
      if(idom[i] != sdom[i])
        idom[i] = idom[idom[i]];
    FOR1(i, T) this->idom[nfd[i]] = nfd[idom[i]];
    // this->idom[s] = s;
  }

  // private area
  inline int eval(int x) { compress(x); return label[x]; }
  int compress(int x) {
    if(dsu[x] == x) return x;
    int ret = compress(dsu[x]);
    if(sdom[label[dsu[x]]] < sdom[label[x]])
      label[x] = label[dsu[x]];
    return dsu[x] = ret;
  }

  void dfs0(int x) {
    ++T;
    dfn[x] = T; nfd[T] = x;
    for(int y: G[x]) {
      if(!dfn[y]) {
        dfs0(y);
        par[dfn[y]] = dfn[x];
      }
      rG[dfn[y]].pb(dfn[x]);
    }
  }
#undef N
} dom;
