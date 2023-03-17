/*
Есть несколько катеров и большая группа людей. Для каждого катера известны его вместимость и цена на билет. Для каждого человека известно, на каких катерах он предпочел бы прокатиться. Требуется распределить людей по катерам на одну морскую прогулку так, чтобы суммарная стоимость, потраченная на билеты, была минимальна.
Входные данные

Два числа n
и k (1≤n≤10^6, 1≤k≤100) - количество катеров и людей. n строк по два числа в каждой - s, c (0≤s≤100, 0≤c≤10^6) - количество мест в катере и стоимость одного билета. Далее k строк, в каждой из которых дано число t - количество катеров, которые подходят текущему человеку, после чего следует список номеров этих катеров. Все номера в пределах от 1 до n

, каждый номер встречается не более одного раза.
Выходные данные

Одно число - суммарная стоимость одной прогулки, либо −1
, если всех людей рассадить по катерам не получится.
*/

#include <bits/stdc++.h>
#define sz(x) int32_t(x.size())

using namespace std;


class Dinica {
private :
    int64_t source , estuary;
public :


    const int64_t INF = 2e18 + 7;

    class Edge {
    public :
        int64_t from = 0;
        int64_t to = 0;
        int64_t cap = 0;
        int64_t flow = 0;
        int64_t cost = 0;
        explicit Edge(int64_t cap = 0 , int64_t from = 0 , int64_t to = 0 , int64_t flow = 0 , int64_t cost = 0) {
            this -> cap = cap;
            this -> from = from;
            this -> to = to;
            this -> flow = flow;
            this -> cost = cost;
        }
    };


    vector < vector < int64_t > > g;
    vector < Edge > e;
    vector < int64_t > point64_t;
    vector < int64_t > lvl;


    void AddEdge(int64_t from , int64_t to , int64_t cap , int64_t flow , int64_t cost) {
        g[from].push_back(sz(e));
        e.emplace_back(cap , from , to , flow , cost);
        g[to].push_back(sz(e));
        e.emplace_back(0 , to , from , -flow , -cost);
    }


    explicit Dinica(int64_t siz = 1) {
        lvl.resize(siz);
        point64_t.resize(siz);
        g.resize(siz);
        this -> estuary = siz - 1;
        this -> source = 0;
    }


    int64_t ans = 0;
    int64_t num = 0;


    bool Ford() {
        if (num == 0) {
            return false;
        }
        int64_t d[estuary + 1];
        int64_t pr[estuary + 1];

        fill(d , d + estuary + 1 , INF);
        fill(pr , pr + estuary + 1 , 0);

        d[source] = 0;
        bool ok = true;

        while (ok) {
            ok = false;
            for (int i = 0; i < sz(e); i++) {
                auto it = e[i];
                if (d[it.to] > d[it.from] + it.cost && it.cap - it.flow > 0) {
                    ok = true;
                    d[it.to] = d[it.from] + it.cost;
                    pr[it.to] = i;
                }
            }
        }

        if (d[estuary] == INF) {
            return false;
        }

        int64_t id = estuary;
        int64_t cnt = num;

        while (id != 0) {
            cnt = min({ cnt , e[pr[id]].cap - e[pr[id]].flow });
            id = e[pr[id]].from;
        }

        id = estuary;
        while (id != 0) {
            ans += e[pr[id]].cost * cnt;
            e[pr[id]].flow += cnt;
            e[(pr[id] ^ 1)].flow -= cnt;
            id = e[pr[id]].from;
        }

        num -= cnt;
        return true;

    }

    int64_t Solve(int64_t cnt) {
        num = cnt;
        while (Ford());
        return ans;
    }

    [[nodiscard]] int64_t GetSource() const {
        return this -> source;
    }

    [[nodiscard]] int64_t GetEstuary() const {
        return this -> estuary;
    }

    ~Dinica() = default;

};
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n , k;
    cin >> n >> k;

    pair < int64_t , int64_t > boat[n + 1];
    Dinica D(1000);
    for (int i = 1; i <= n; i++) {
        int64_t s , c;
        cin >> s >> c;
        boat[i] = {s , c};
    }


    for (int i = n + 1; i <= n + k; i++) {
        D.AddEdge(D.GetSource() , i , 1 , 0 , 0);
    }

    for (int i = 1; i <= k; i++) {
        int64_t num;
        cin >> num;
        for (int j = 1; j <= num; j++){
            int64_t x;
            cin >> x;
            D.AddEdge(i + n , x , 1LL , 0LL , boat[x].second);
        }
    }

    for (int i = 1; i <= n; i++) {
        D.AddEdge(i , D.GetEstuary() , boat[i].first , 0LL , 0LL);
    }

    int64_t l = D.Solve(k);
    if (D.num != 0) {
        cout << -1;
    } else {
        cout << l;
    }
    return 0;
}
