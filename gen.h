#ifndef GEN_H
#define GEN_H

#include <QString>
#include <QVector>
#include <random>
#include <chrono>
#include <climits>

class Gen {
public:
    qint64 RandomNumber(qint64 L=LLONG_MIN, qint64 R=LLONG_MAX); // num generator
    QVector<qint64> RandomList(int N, qint64 L=LLONG_MIN, qint64 R=LLONG_MAX); // list generator
    QVector<QVector<qint64>> RandomMatrix(int N, int M, qint64 L=LLONG_MIN, qint64 R=LLONG_MAX);
    QString RandomString(int N, QString char_set); // random string case=0(lower), case=1(upper), else(both);
    QVector<int> RandomPermutation(int N, bool zero_base=false);
    QVector<QVector<int>> RandomTree(int V, bool weighted=false, int L=INT_MIN, int R=INT_MAX, bool zero_base=false); // tree generator
    QVector<QVector<int>> RandomGraph(int V, int E, bool weighted=false, int L=INT_MIN, int R=INT_MAX, bool connected=false, bool self_loop=false, bool multi_edge=false, bool zero_base=false);

private:
    inline qint64 random(qint64 L = LLONG_MIN, qint64 R = LLONG_MAX) {
        std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        if (L > R) std::swap(L, R);
        std::uniform_int_distribution<qint64> generator(L, R);
        return generator(rng);
    }
};

#endif // GEN_H
