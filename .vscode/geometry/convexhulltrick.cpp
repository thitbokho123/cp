#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;

struct Segment {
  double x, a, b;

  Segment(double _x, double _a, double _b) { x = _x, a = _a, b = _b; }

  Segment(double _x = 0) { x = _x; }

  bool operator<(const Segment& s) const { return x < s.x; }
};

vector<Segment> segments;

void addLine(double a, double b) {
  while (!segments.empty()) {
    double X = segments.back().x;
    double A = segments.back().a;
    double B = segments.back().b;

    if (X * A + B <= X * a + b) {
      segments.pop_back();
    } else {
      break;
    }
  }

  if (segments.empty()) {
    segments.push_back(Segment(-INF, a, b));
    return;
  }

  double A = segments.back().a;
  double B = segments.back().b;

  if (a == A) return;

  double inter = (b - B) / (A - a);
  segments.push_back(Segment(inter, a, b));
}

double query(double t) {
  int id = upper_bound(segments.begin(), segments.end(), Segment(t)) -
           segments.begin() - 1;
  return segments[id].a * t + segments[id].b;
}

int main() {
  for (int i = 1; i <= n; i++) {
    addLine(a[i], b[i]);
  }
}