#include "gen.h"
#include <set>
#include <algorithm>
#include <cassert>
#include <QChar>
#include <QRandomGenerator>
#include <algorithm>

// Random number generator
qint64 Gen::RandomNumber(qint64 L, qint64 R) {
    return random(L, R);
}

// Random string generator
QString Gen::RandomString(int N, QString char_set) {
    QString s;
    while (N--) {
        s.push_back(char_set[random(0, char_set.size() - 1)]);
    }
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(s.begin(), s.end(), rng);
    return s;
}

// Random list generator
QVector<qint64> Gen::RandomList(int N, qint64 L, qint64 R) {
    if (L > R) std::swap(L, R);
    QVector<qint64> v;
    while (N--) {
        v.append(random(L, R));
    }
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(v.begin(), v.end(), rng);
    return v;
}

// Random matrix generator
QVector<QVector<qint64>> Gen::RandomMatrix(int N, int M, qint64 L, qint64 R) {
    if (L > R) std::swap(L, R);
    QVector<QVector<qint64>> mat(N, QVector<qint64>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            mat[i][j] = random(L, R);
        }
    }
    return mat;
}

// Random permutation generator
QVector<int> Gen::RandomPermutation(int N, bool zero_base) {
    QVector<int> v(N);
    for (int i = 0; i < N; ++i) {
        v[i] = i + !zero_base;
    }
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(v.begin(), v.end(), rng);
    return v;
}

// Random tree generator
QVector<QVector<int>> Gen::RandomTree(int V, bool weighted, int L, int R, bool zero_base) {
    QVector<QVector<int>> edges;
    if (L > R) std::swap(L, R);
    for (int i = 2; i <= V; ++i) {
        QVector<int> e = { int(random(1, i - 1)), i };
        if (weighted) e.append(random(L, R));
        edges.append(e);
    }
    QVector<int> perm(V + 1); // re-naming vertices
    for (int i = 1; i <= V; ++i) {
        perm[i] = i;
    }
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(perm.begin() + 1, perm.end(), rng);

    std::shuffle(edges.begin(), edges.end(), rng); // random order of edges

    for (auto &edge : edges) {
        if (random(0, 1)) {
            std::swap(edge[0], edge[1]); // random order of two vertices
        }
        edge[0] = perm[edge[0]] - zero_base;
        edge[1] = perm[edge[1]] - zero_base;
    }
    return edges;
}

// Random graph generator
QVector<QVector<int>> Gen::RandomGraph(int V, int E, bool weighted, int L, int R, bool connected, bool self_loop, bool multi_edge, bool zero_base) {
    std::multiset<QPair<int, int>> edges;
    assert(V > 0 && E >= 0);
    assert(!connected || (V > 0 && E >= V - 1));

    if (self_loop) {
        int mx = V;
        if (connected) {
            mx = std::max(0, E - V - 1);
        }
        if (random(1, 10) <= 8) mx = random(0, mx / 2);
        else mx = random(0, mx);
        while (mx--) {
            int a;
            do {
                a = random(1, V);
            } while (!multi_edge && edges.count(qMakePair(a, a)));
            edges.insert(qMakePair(a, a));
        }
    }

    if (!connected) {
        while (edges.size() < static_cast<size_t>(E)) {
            int a, b;
            do {
                a = random(1, V), b = random(1, V);
                if (a > b) std::swap(a, b);
            } while ((!multi_edge && edges.count(qMakePair(a, b))) || a == b);
            edges.insert(qMakePair(a, b));
        }
    } else {
        for (int i = 2; i <= V; ++i) {
            int mx = E - V + i - edges.size();
            if (i != V) {
                mx = random(1, mx);
            }
            if (!multi_edge) {
                mx = std::min(mx, i - 1);
            }
            while (mx--) {
                int a;
                do {
                    a = random(1, i - 1);
                } while (!multi_edge && edges.count(qMakePair(a, i)));
                edges.insert(qMakePair(a, i));
            }
        }
    }

    QVector<int> perm(V + 1); // re-naming vertices
    for (int i = 1; i <= V; ++i) {
        perm[i] = i;
    }
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(perm.begin() + 1, perm.end(), rng);

    QVector<QVector<int>> g;
    for (const auto &edge : edges) {
        int a = edge.first, b = edge.second;
        if (random() % 2) {
            std::swap(a, b); // random order of two vertices
        }
        QVector<int> e = { perm[a] - zero_base, perm[b] - zero_base };
        if (weighted) {
            e.append(random(L, R));
        }
        g.append(e);
    }
    return g;
}
