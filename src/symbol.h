#pragma once

#include <QList>

class Symbol {
public:
    Symbol(QList<QPointF> points, char symbol);

    QList<QPointF> points() const;
    char symbol() const;

private:
    QList<QPointF> _points;
    char _symbol;
};
