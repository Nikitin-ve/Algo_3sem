#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

const double kPi = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::vector<Complex> CVector;

void Fft(CVector& data, bool is_forward) {
  size_t nn = data.size();
  if (nn == 1) {
    return;
  }

  // Разделяем данные на четные и нечетные компоненты
  CVector even(nn / 2);
  CVector odd(nn / 2);
  for (size_t i = 0; i < nn / 2; ++i) {
    even[i] = data[2 * i];
    odd[i] = data[2 * i + 1];
  }

  // Рекурсивное выполнение FFT для четных и нечетных частей
  Fft(even, is_forward);
  Fft(odd, is_forward);

  // Объединяем результаты
  double angle_unit = 2 * kPi / nn * (is_forward ? 1 : -1);
  Complex factor_unit(cos(angle_unit), sin(angle_unit));
  Complex factor = 1;

  for (size_t k = 0; k < nn / 2; ++k) {
    data[k] = even[k] + factor * odd[k];
    data[k + nn / 2] = even[k] - factor * odd[k];
    if (!is_forward) {
      data[k] /= 2;
      data[k + nn / 2] /= 2;
    }
    factor = factor * factor_unit;
  }
}

// Умножает два многочлена, представленных векторами их коэффициентов
CVector MultiplyPolynomials(const CVector& poly_one, const CVector& poly_two) {
  size_t result_size = 1;
  while (result_size < poly_one.size() + poly_two.size()) {
    result_size <<= 1;
  }

  CVector first(result_size, 0);
  CVector second(result_size, 0);

  for (size_t i = 0; i < poly_one.size(); ++i) {
    first[i] = poly_one[i];
  }
  for (size_t i = 0; i < poly_two.size(); ++i) {
    second[i] = poly_two[i];
  }

  Fft(first, true);
  Fft(second, true);

  CVector result(result_size);
  for (size_t i = 0; i < result_size; ++i) {
    result[i] = first[i] * second[i];
  }

  Fft(result, false);
  return result;
}

int main() {
  size_t degree_polynomial_one;
  size_t degree_polynomial_two;
  std::cin >> degree_polynomial_one;
  ++degree_polynomial_one;
  CVector poly_one(degree_polynomial_one);
  for (size_t i = 0; i < degree_polynomial_one; ++i) {
    double coefficient;
    std::cin >> coefficient;
    poly_one[i] = coefficient;
  }

  std::cin >> degree_polynomial_two;
  ++degree_polynomial_two;
  CVector poly_two(degree_polynomial_two);
  for (size_t i = 0; i < degree_polynomial_two; ++i) {
    double coefficient;
    std::cin >> coefficient;
    poly_two[i] = coefficient;
  }

  CVector result = MultiplyPolynomials(poly_one, poly_two);

  // Вывод многочлена
  std::cout << degree_polynomial_one + degree_polynomial_two - 2 << " ";
  for (size_t i = 0; i < degree_polynomial_one + degree_polynomial_two - 1;
       ++i) {
    std::cout << static_cast<int>(std::round(result[i].real())) << " ";
  }
  std::cout << std::endl;

  return 0;
}
