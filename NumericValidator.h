#ifndef NUMERICVALIDATOR_H
#define NUMERICVALIDATOR_H
#include <QValidator>
#include <QRegularExpression>
class NumericValidator: public QValidator{
public:
    NumericValidator(QObject *parent = nullptr) : QValidator(parent) {}

    State validate(QString &input, int &pos) const override {
        QRegularExpression re("^$|^-?[0-9]+$"); // Match any number of digits
        QRegularExpressionMatch match = re.match(input);
        if (match.hasMatch() && match.capturedLength() == input.length())
            return Acceptable;
        else
            return Invalid;
    }
};

#endif // NUMERICVALIDATOR_H
