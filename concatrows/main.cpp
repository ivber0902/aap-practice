#include <limits>
#include <iostream>
#include <iomanip>

int** concat_rows(const int* const* lhs, size_t n1, size_t m1, const int* const* rhs, size_t n2, size_t m2) {
  if (lhs == nullptr || rhs == nullptr) {
    throw std::invalid_argument("nullptr");
  }

  if (m1 > std::numeric_limits<size_t>::max() - m2) {
    throw std::bad_array_new_length();
  }

  if (n1 > 0 && m1 > std::numeric_limits<size_t>::max() / n1) {
    throw std::bad_array_new_length();
  }
  if (n2 > 0 && m2 > std::numeric_limits<size_t>::max() / n2) {
    throw std::bad_array_new_length();
  }

  const size_t n_max = n1 > n2? n1: n2;
  const size_t n_min = n1 < n2? n1: n2;

  int** res = nullptr;
  size_t allocated = 0;
  try {
    res = new int* [n_max];
    for (size_t i = 0; i < n_max; i++) {
      if (i < n_min) {
        res[i] = new int[m1 + m2];
      } else {
        res[i] = (n1 == n_max) ? new int[m1] : new int[m2];
      }
      allocated++;
    }
  } catch (...) {
    for (size_t j = 0; j < allocated; j++) {
      delete[] res[j];
    }
    delete[] res;
    throw;
  }

  for (size_t i = 0; i < n_max; i++) {
    if (i < n_min) {
      for (size_t j = 0; j < m1; j++) {
        res[i][j] = lhs[i][j];
      }
      for (size_t j = 0; j < m2; j++) {
        res[i][m1 + j] = rhs[i][j];
      }
    } else {
      const int* src = (n1 == n_max) ? lhs[i] : rhs[i];
      size_t length = (n1 == n_max) ? m1 : m2;
      for (size_t j = 0; j < length; j++) {
        res[i][j] = src[j];
      }
    }
  }
  return res;
}

int main() {
  size_t n1 = 3, m1 = 2;
  int** lhs = new int*[n1];
  for (size_t i = 0; i < n1; i++) {
    lhs[i] = new int[m1];
    for (size_t j = 0; j < m1; j++) {
      lhs[i][j] = i * 10 + j;
    }
  }

  size_t n2 = 2, m2 = 3;
  int** rhs = new int*[n2];
  for (size_t i = 0; i < n2; i++) {
    rhs[i] = new int[m2];
    for (size_t j = 0; j < m2; j++) {
      rhs[i][j] = i + j * 10;
    }
  }

  std::cout << "lhs\n";
  for (size_t i = 0; i < n1; i++) {
    for (size_t j = 0; j < m1; j++) std::cout << std::setw(3) << lhs[i][j] << " ";
    std::cout << "\n";
  }
  std::cout << "\nrhs\n";
  for (size_t i = 0; i < n2; i++) {
    for (size_t j = 0; j < m2; j++) std::cout << std::setw(3) << rhs[i][j] << " ";
    std::cout << "\n";
  }

  int** result = concat_rows(lhs, n1, m1, rhs, n2, m2);

  std::cout << "\n\n";
  size_t res_n = std::max(n1, n2);
  for (size_t i = 0; i < res_n; i++) {
    size_t current_m = (i < std::min(n1, n2)) ? (m1 + m2) : ((n1 > n2) ? m1 : m2);
    for (size_t j = 0; j < current_m; j++) {
      std::cout << std::setw(3) << result[i][j] << " ";
    }
    std::cout << "\n";
  }

  for (size_t i = 0; i < res_n; i++) {
    delete[] result[i];
  }
  delete[] result;

  for (size_t i = 0; i < n1; i++) delete[] lhs[i];
  delete[] lhs;

  for (size_t i = 0; i < n2; i++) delete[] rhs[i];
  delete[] rhs;

  return 0;
}
