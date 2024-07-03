#ifndef INTERVAL_H
#define INTERVAL_H

class interval
{
public:
    double min, max;
    interval() {}
    interval(double min, double max) : min(min), max(max) {}

    double size() const
    {
        return max - min;
    }

    bool contains(double value) const
    {
        return value >= min && value <= max;
    }

    bool surrounds(double value) const
    {
        return value > min && value < max;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, infinity);

#endif