#include "symbol.h"

Symbol::Symbol(QList<QPointF> points, char symbol)
        : _points(points), _symbol(symbol) {
}

QList<QPointF> Symbol::points() const {
    return _points;
}

char Symbol::symbol() const {
    return _symbol;
}
