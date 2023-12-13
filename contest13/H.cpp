#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

class Point {
 private:
  long long x_coord_;
  long long y_coord_;

 public:
  Point(long long x_coord, long long y_coord)
      : x_coord_(x_coord), y_coord_(y_coord){};
  [[nodiscard]] long long GetXCoord() const { return x_coord_; }
  [[nodiscard]] long long GetYCoord() const { return y_coord_; }
};

class Vector {
 private:
  long long x_coord_;
  long long y_coord_;

 public:
  Vector(Point point)
      : x_coord_(point.GetXCoord()), y_coord_(point.GetYCoord()){};
  Vector(Point point_1, Point point_2)
      : x_coord_(point_2.GetXCoord() - point_1.GetXCoord()),
        y_coord_(point_2.GetYCoord() - point_1.GetYCoord()){};
  [[nodiscard]] long double GetLenght() const {
    return std::sqrt(x_coord_ * x_coord_ + y_coord_ * y_coord_);
  }
  Vector operator+(Vector vec) const {
    return {{x_coord_ + vec.x_coord_, y_coord_ + vec.y_coord_}};
  }
  [[nodiscard]] long long GetX() const { return x_coord_; }
  [[nodiscard]] long long GetY() const { return y_coord_; }
  long long operator*(Vector vec) const {
    return x_coord_ * vec.x_coord_ + y_coord_ * vec.y_coord_;
  }
  [[nodiscard]] long long VectorProduct(Vector vec) const {
    return x_coord_ * vec.y_coord_ - y_coord_ * vec.x_coord_;
  }
  [[nodiscard]] long double GetSquare(Vector vec) const {
    return std::abs(VectorProduct(vec) / static_cast<long double>(2));
  }
};

class Direct {
 private:
  Point point_1_;
  Point point_2_;

 public:
  Direct(Point point_1, Point point_2) : point_1_(point_1), point_2_(point_2){};
  [[nodiscard]] Point GetPoint1() const { return point_1_; }
  [[nodiscard]] Point GetPoint2() const { return point_2_; }
};

long double Squaring(long double numb) { return numb * numb; }

long double DistanceDirect(Direct direct, Point point) {
  long double coord_a_x = direct.GetPoint1().GetXCoord();
  long double coord_a_y = direct.GetPoint1().GetYCoord();
  long double coord_b_x = direct.GetPoint2().GetXCoord();
  long double coord_b_y = direct.GetPoint2().GetYCoord();
  long double coord_c_x = point.GetXCoord();
  long double coord_c_y = point.GetYCoord();
  long double stat_1 = std::abs((coord_b_y - coord_a_y) * coord_c_x -
                                (coord_b_x - coord_a_x) * coord_c_y +
                                coord_b_x * coord_a_y - coord_b_y * coord_a_x);
  long double stat_2 = std::sqrt(Squaring(coord_b_y - coord_a_y) +
                                 Squaring(coord_b_x - coord_a_x));
  return stat_1 / stat_2;
}

long double DistanceRay(Direct direct, Point point) {
  long double coord_a_x = direct.GetPoint1().GetXCoord();
  long double coord_a_y = direct.GetPoint1().GetYCoord();
  long double coord_b_x = direct.GetPoint2().GetXCoord();
  long double coord_b_y = direct.GetPoint2().GetYCoord();
  long double coord_c_x = point.GetXCoord();
  long double coord_c_y = point.GetYCoord();
  long double stat_x =
      (coord_a_x * Squaring(coord_b_y - coord_a_y) +
       coord_c_x * Squaring(coord_b_x - coord_a_x) +
       (coord_b_y - coord_a_y) * (coord_b_x - coord_a_x) *
           (coord_c_y - coord_a_y)) /
      (Squaring(coord_b_y - coord_a_y) + Squaring(coord_b_x - coord_a_x));
  long double stat_y = ((coord_b_x - coord_a_x) * (coord_c_x - stat_x)) /
                           (coord_b_y - coord_a_y) +
                       coord_c_y;
  if ((coord_a_x > coord_b_x && coord_a_x < stat_x) ||
      (coord_a_x < coord_b_x && coord_a_x > stat_x)) {
    return std::sqrt(Squaring(coord_a_x - coord_c_x) +
                     Squaring(coord_a_y - coord_c_y));
  }
  if (coord_a_x == coord_b_x) {
    if ((coord_a_y > coord_b_y && coord_a_y < stat_y) ||
        (coord_a_y < coord_b_y && coord_a_y > stat_y)) {
      return std::sqrt(Squaring(coord_a_x - coord_c_x) +
                       Squaring(coord_a_y - coord_c_y));
    }
  }
  return DistanceDirect(direct, point);
}

long double DistanceSection(Direct direct, Point point) {
  long double coord_a_x = direct.GetPoint1().GetXCoord();
  long double coord_a_y = direct.GetPoint1().GetYCoord();
  long double coord_b_x = direct.GetPoint2().GetXCoord();
  long double coord_b_y = direct.GetPoint2().GetYCoord();
  long double coord_c_x = point.GetXCoord();
  long double coord_c_y = point.GetYCoord();
  long double stat_x =
      (coord_a_x * Squaring(coord_b_y - coord_a_y) +
       coord_c_x * Squaring(coord_b_x - coord_a_x) +
       (coord_b_y - coord_a_y) * (coord_b_x - coord_a_x) *
           (coord_c_y - coord_a_y)) /
      (Squaring(coord_b_y - coord_a_y) + Squaring(coord_b_x - coord_a_x));
  long double stat_y = ((coord_b_x - coord_a_x) * (coord_c_x - stat_x)) /
                           (coord_b_y - coord_a_y) +
                       coord_c_y;
  if (coord_a_x == coord_b_x) {
    if (stat_y > coord_a_y && stat_y > coord_b_y) {
      if (coord_a_y > coord_b_y) {
        return std::sqrt(Squaring(coord_a_x - coord_c_x) +
                         Squaring(coord_a_y - coord_c_y));
      }
      return std::sqrt(Squaring(coord_b_x - coord_c_x) +
                       Squaring(coord_b_y - coord_c_y));
    }
    if (stat_y < coord_a_y && stat_y < coord_b_y) {
      if (coord_a_y > coord_b_y) {
        return std::sqrt(Squaring(coord_b_x - coord_c_x) +
                         Squaring(coord_b_y - coord_c_y));
      }
      return std::sqrt(Squaring(coord_a_x - coord_c_x) +
                       Squaring(coord_a_y - coord_c_y));
    }
    return DistanceDirect(direct, point);
  }
  if (stat_x > coord_a_x && stat_x > coord_b_x) {
    if (coord_a_x > coord_b_x) {
      return std::sqrt(Squaring(coord_a_x - coord_c_x) +
                       Squaring(coord_a_y - coord_c_y));
    }
    return std::sqrt(Squaring(coord_b_x - coord_c_x) +
                     Squaring(coord_b_y - coord_c_y));
  }
  if (stat_x < coord_a_x && stat_x < coord_b_x) {
    if (coord_a_x > coord_b_x) {
      return std::sqrt(Squaring(coord_b_x - coord_c_x) +
                       Squaring(coord_b_y - coord_c_y));
    }
    return std::sqrt(Squaring(coord_a_x - coord_c_x) +
                     Squaring(coord_a_y - coord_c_y));
  }
  return DistanceDirect(direct, point);
}

long long Rotate(Direct direct, Point point) {
  return (direct.GetPoint2().GetXCoord() - direct.GetPoint1().GetXCoord()) *
             (point.GetYCoord() - direct.GetPoint2().GetYCoord()) -
         (direct.GetPoint2().GetYCoord() - direct.GetPoint1().GetYCoord()) *
             (point.GetXCoord() - direct.GetPoint2().GetXCoord());
}

long long Cwadrat(long long number) { return number * number; }

void Sort(std::vector<Point>& my_vertex, std::vector<int>& p_ind) {
  int p_ind_0 = p_ind[0];
  auto comp = [&my_vertex, p_ind_0](int v_b, int v_c) {
    Vector vector_1(my_vertex[p_ind_0], my_vertex[v_b]);
    Vector vector_2(my_vertex[p_ind_0], my_vertex[v_c]);
    long long dp = vector_1.VectorProduct(vector_2);
    if (dp == 0) {
      long long d1 =
          vector_1.GetX() * vector_1.GetX() + vector_1.GetY() * vector_1.GetY();
      long long d2 =
          vector_2.GetX() * vector_2.GetX() + vector_2.GetY() * vector_2.GetY();
      return d1 < d2;
    }
    return vector_1.VectorProduct(vector_2) < 0;
  };
  std::sort(p_ind.begin() + 1, p_ind.end(), comp);
}

std::vector<Point> Mbo(std::vector<Point>& my_vertex) {
  int len = int(my_vertex.size());
  std::vector<int> p_ind(len);
  p_ind[0] = 0;
  for (int i = 1; i < len; ++i) {
    p_ind[i] = i;
    if (my_vertex[p_ind[i]].GetXCoord() < my_vertex[p_ind[0]].GetXCoord()) {
      std::swap(p_ind[i], p_ind[0]);
    } else if (my_vertex[p_ind[i]].GetXCoord() ==
               my_vertex[p_ind[0]].GetXCoord()) {
      if (my_vertex[p_ind[i]].GetYCoord() < my_vertex[p_ind[0]].GetYCoord()) {
        std::swap(p_ind[i], p_ind[0]);
      }
    }
  }
  Sort(my_vertex, p_ind);
  std::vector<int> ans_ind;
  ans_ind.push_back(p_ind[0]);
  ans_ind.push_back(p_ind[1]);
  p_ind.push_back(p_ind[0]);
  for (int i = 2; i < len + 1; ++i) {
    while (Rotate({my_vertex[ans_ind[int(ans_ind.size()) - 2]],
                   my_vertex[ans_ind[int(ans_ind.size()) - 1]]},
                  my_vertex[p_ind[i]]) >= 0) {
      ans_ind.pop_back();
      if (ans_ind.size() == 1) {
        break;
      }
    }
    ans_ind.push_back(p_ind[i]);
  }
  p_ind.pop_back();
  ans_ind.pop_back();
  std::vector<Point> ans;
  ans.reserve(ans_ind.size());
  for (int ir : ans_ind) {
    ans.push_back(my_vertex[ir]);
  }
  return ans;
}

long long AreaTriangle(Point v_1, Point v_2, Point v_3) {
  return std::abs((v_2.GetXCoord() - v_1.GetXCoord()) *
                      (v_3.GetYCoord() - v_1.GetYCoord()) -
                  (v_3.GetXCoord() - v_1.GetXCoord()) *
                      (v_2.GetYCoord() - v_1.GetYCoord()));
}

long double Perimeter(std::vector<Point>& my_vector) {
  long double ans = 0;
  my_vector.push_back(my_vector[0]);
  for (int i = 1; i < int(my_vector.size()); ++i) {
    ans += Vector(my_vector[i], my_vector[i - 1]).GetLenght();
  }
  my_vector.pop_back();
  return ans;
}

int main() {
  int len;
  long long coord_x;
  long long coord_y;
  std::cin >> len;
  std::vector<Point> my_vertex;
  for (int i = 0; i < len; ++i) {
    std::cin >> coord_x >> coord_y;
    my_vertex.push_back({coord_x, coord_y});
  }
  std::vector<Point> ans = Mbo(my_vertex);
  std::cout << ans.size() << '\n';
  for (int i = 0; i < int(ans.size()); ++i) {
    std::cout << ans[i].GetXCoord() << ' ' << ans[i].GetYCoord() << '\n';
  }
  long long ans_per = 0;
  for (int i = 2; i < int(ans.size()); ++i) {
    ans_per += AreaTriangle(ans[0], ans[i - 1], ans[i]);
  }
  std::cout << ans_per / 2;
  if (ans_per % 2 == 0) {
    std::cout << ".0";
  } else {
    std::cout << ".5";
  }
}