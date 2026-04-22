#ifndef VECT2_HPP
#define VECT2_HPP
#include <iostream>

class vect2 {
    int x, y;
public:
    vect2(); vect2(int x, int y); vect2(const vect2& o); vect2& operator=(const vect2& o); ~vect2();
    int& operator[](int i); const int& operator[](int i) const;
    vect2& operator++(); vect2& operator--(); vect2 operator++(int); vect2 operator--(int);
    vect2& operator+=(const vect2& o); vect2& operator-=(const vect2& o); vect2& operator*=(int t);
    vect2 operator+(const vect2& o) const; vect2 operator-(const vect2& o) const;
    vect2 operator*(int t) const; vect2 operator-() const;
    bool operator==(const vect2& o) const; bool operator!=(const vect2& o) const;
    friend vect2 operator*(int t, const vect2& o);
    friend std::ostream& operator<<(std::ostream& os, const vect2& o);
};

#endif
