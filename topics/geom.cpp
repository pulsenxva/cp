#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
ll MOD = 1e9 + 7;
int p = 239;

struct pt {
  ll x, y;
  pt(ll x_ = 0, ll y_ = 0) {
    x = x_;
    y = y_;
  }
  ll dist2() { return x * x + y * y; }

  // скалярное произведение
  ll dot(pt other) { return x * other.x + y * other.y; }
  // векторное произведение
  ll cross(pt other) { return x * other.y - y * other.x; }
  // угол между векторами
  ld angle(pt other) { return atan2(cross(other), dot(other)); }

  // расположение C относительно AB
  int orientation(pt a, pt b, pt c) {
    ll cross = (b - a).cross(c - a);
    if (cross > 0) return 1;    // левый поворот
    if (cross < 0) return -1;   // правый поворот
    return 0;                   // коллинеарны
  }
  // проверка, лежит ли точка на отрезке
  bool on_segment(pt p, pt a, pt b) {
    return (p - a).cross(b - a) == 0 &&
           (p - a).dot(p - b) <= 0;  // между A и B
  }
  // площадь треугольника (удвоенная)
  ll triangle_area2(pt a, pt b, pt c) {
    return abs((b - a).cross(c - a));
  }

  // площадь любого многоугольника (удвоенная)
  ll polygon_area2(vector<pt>& poly) {
    ll area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
      area += poly[i].cross(poly[(i + 1) % n]);
    }
    return abs(area);  // знак показывает направление обхода
  }
  // пересечение отрезков
  bool segments_intersect(pt a, pt b, pt c, pt d) {
    ll cross1 = (b - a).cross(c - a);
    ll cross2 = (b - a).cross(d - a);
    ll cross3 = (d - c).cross(a - c);
    ll cross4 = (d - c).cross(b - c);

    // быстрая проверка если отрезки пересекаются
    if (cross1 * cross2 < 0 && cross3 * cross4 < 0)
      return true;

    // проверка граничных случаев (концы на отрезках)
    if (cross1 == 0 && on_segment(c, a, b)) return true;
    if (cross2 == 0 && on_segment(d, a, b)) return true;
    if (cross3 == 0 && on_segment(a, c, d)) return true;
    if (cross4 == 0 && on_segment(b, c, d)) return true;

    return false;
  }

  friend pt operator+ (pt a, pt b) {  return pt(a.x+b.x, a.y+b.y); }
  friend pt operator- (pt a, pt b) {  return pt(a.x-b.x, a.y-b.y); }
  friend pt operator* (pt a, ll k) {  return pt(a.x*k, a.y*k); }
  friend ostream& operator<< (ostream& out, pt a) { return out << '('<<a.x<<", "<<a.y<<")"; }
};

int main() {
  pt b(1, 0), a(3, 4);
  pt c = a*2;
  cout << a+b << ' ' << a-b << '\n';
  cout << c.x << ' ' << c.y << '\n';

  cout << "===================\n";
  pt v1(4, 3), v2(-3, 4);
  cout << v1 << ' ' << v2 << '\n';
  cout << v1.dot(v2) << ' ' << v1.cross(v2) << '\n';

  cout << "===================\n";
  double PI = atan2(0, -1);
  cout << PI << '\n';
  ld angle_rad = v1.angle(v2);
  ld angle_deg = angle_rad/PI * 180;
  cout << angle_rad << ' ' << angle_deg << '\n';

  // if a.dot(b) > 0 => <90; a.dot(b) < 0 => >90
  // для точек A, B, C:
  // cross(B-A, C-A) > 0: C левее AB (против часовой)
  // cross(B-A, C-A) < 0: C правее AB (по часовой)
  // cross(B-A, C-A) = 0: A, B, C коллинеарны

}
