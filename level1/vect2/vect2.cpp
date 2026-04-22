#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}
vect2::vect2(int x, int y) : x(x), y(y) {}
vect2::vect2(const vect2& o) : x(o.x), y(o.y) {}
vect2& vect2::operator=(const vect2& o) { if (this != &o) { x = o.x; y = o.y; } return *this; }
vect2::~vect2() {}

int& vect2::operator[](int i) { return i == 0 ? x : y; }
const int& vect2::operator[](int i) const { return i == 0 ? x : y; }

vect2& vect2::operator++() { ++x; ++y; return *this; }
vect2& vect2::operator--() { --x; --y; return *this; }
vect2 vect2::operator++(int) { vect2 t(x, y); ++(*this); return t; }
vect2 vect2::operator--(int) { vect2 t(x, y); --(*this); return t; }

vect2& vect2::operator+=(const vect2& o) { x += o.x; y += o.y; return *this; }
vect2& vect2::operator-=(const vect2& o) { x -= o.x; y -= o.y; return *this; }
vect2& vect2::operator*=(int t) { x *= t; y *= t; return *this; }
vect2 vect2::operator+(const vect2& o) const { return vect2(x + o.x, y + o.y); }
vect2 vect2::operator-(const vect2& o) const { return vect2(x - o.x, y - o.y); }
vect2 vect2::operator*(int t) const { return vect2(x * t, y * t); }
vect2 vect2::operator-() const { return vect2(-x, -y); }

bool vect2::operator==(const vect2& o) const { return x == o.x && y == o.y; }
bool vect2::operator!=(const vect2& o) const { return !(*this == o); }

vect2 operator*(int t, const vect2& o) { return vect2(t * o.x, t * o.y); }
std::ostream& operator<<(std::ostream& os, const vect2& o) { return os << "{" << o[0] << ", " << o[1] << "}"; }
