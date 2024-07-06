#ifndef VARIABLE_H
#define VARIABLE_H
#include <QString>
#include <QSet>
class Variable{
public:
    QString name;
    long long L, R;
    bool int_type = 1;//if 1 int type if 0 char type
    QString char_subset;
    QSet<QString> used_by;
};
class Data_Structure{
public:
    QString name;
    Variable *size_var=nullptr, *size_var_2=nullptr;
    QString char_set;
    int _case=0;
    bool ispermutation=0, zero_base=0, weighted=0, connected=0, self_loop=0, multi_edge=0, istree=0;
    long long L, R;
};

#endif // VARIABLE_H
