#include <cstddef>
#include <limits>
#include <new>
#include <stdexcept>
#include <iostream>
#include <iomanip>

bool add_overflow(int a, int b) {
    if (b > 0 && a > std::numeric_limits<int>::max() - b) return true;
    if (b < 0 && a < std::numeric_limits<int>::min() - b) return true;
    return false;
}

int * extend(const int * ptr_a, size_t k, size_t d, int filler)
{
  if (ptr_a == nullptr) {
    throw std::invalid_argument("ptr_a nullptr");
  }
  if (d < k) {
    throw std::invalid_argument("d < k");
  }
  int* res = nullptr;
  try {
    res = new int[d]();
  }
  catch (...) {
    throw std::bad_array_new_length();
  }
  for (size_t i = 0; i < k; i++)
  {
    res[i] = ptr_a[i];
  }

  for (size_t i = k; i < d; i++)
  {
    res[i] = filler;
  }

  return res;
}

void extend(int** ptr_a, size_t k, size_t d, int filler)
{
  if (ptr_a == nullptr) {
    throw std::invalid_argument("ptr_a nullptr");
  }
  if (d < k) {
    throw std::invalid_argument("d < k");
  }
  int* res = nullptr;
  try {
    res = new int[d]();
  }
  catch (...) {
    throw std::bad_array_new_length();
  }
  for (size_t i = 0; i < k; i++)
  {
    res[i] = (*ptr_a)[i];
  }

  for (size_t i = k; i < d; i++)
  {
    res[i] = filler;
  }

  delete[] *ptr_a;
  *ptr_a = res;
}

int * add_row(const int * ptr_a, size_t n, size_t m, int filler)
{
  if (ptr_a == nullptr) {
    throw std::bad_alloc();
  }
  if (n > std::numeric_limits<size_t>::max() - 1) {
      throw std::bad_array_new_length();
  }
  if (m != 0 && n + 1 > std::numeric_limits<size_t>::max() / m) {
      throw std::bad_array_new_length();
  }

  int* res = nullptr;
  try {
    res = new int[(n + 1) * m]();
  }
  catch (...) {
    throw std::bad_array_new_length();
  }
  for (size_t i = 0; i < n * m; i++)
  {
    res[i] = ptr_a[i];
  }

  for (size_t i = n * m; i < (n+1) * m; i++)
  {
    res[i] = filler;
  }

  return res;
}

int * add_col(const int * ptr_a, size_t n, size_t m, int filler)
{
  if (ptr_a == nullptr) {
    throw std::bad_alloc();
  }
  if (m > std::numeric_limits<size_t>::max() - 1) {
      throw std::bad_array_new_length();
  }
  if (n != 0 && m + 1 > std::numeric_limits<size_t>::max() / n) {
      throw std::bad_array_new_length();
  }

  int* res = nullptr;
  try {
    res = new int[(m + 1) * n]();
  }
  catch (...) {
    throw std::bad_array_new_length();
  }
  for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++) {
          res[i * (m + 1) + j] = ptr_a[i * m + j];
      }
      res[i * (m + 1) + m] = filler;
  }

  return res;
}

int * transposed(const int * ptr_a, size_t n, size_t m)
{
  if (ptr_a == nullptr) {
    throw std::invalid_argument("ptr_a nullptr");
  }

  if (n != 0 && m > std::numeric_limits<size_t>::max() / n) {
      throw std::bad_array_new_length();
  }
  int* res = nullptr;
  try {
    res = new int[n*m]();
  }
  catch (...) {
    throw std::bad_array_new_length();
  }

  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < m; j++)
    {
      res[j * n + i] = ptr_a[i * m + j];
    }
  }

  return res;
}

int * concat_rows(const int* a, std::size_t n, std::size_t m1, const int* b, std::size_t m2) {
  if (a == nullptr || b == nullptr) {
    throw std::bad_alloc();
  }
  if (add_overflow(m1, m2)) {
    throw std::bad_array_new_length();
  }
  if (n != 0 && m1+m2 > std::numeric_limits<size_t>::max() / n) {
      throw std::bad_array_new_length();
  }
  int* res = nullptr;
  try {
    res = new int[(m1+m2) * n]();
  }
  catch (...) {
    throw std::bad_array_new_length();
  }
  for (size_t i = 0; i < n; i++)
  {
    for (int j = 0; j < m1; j++) {
      res[i * (m1+m2) + j] += a[i * m1 + j];
    }
    for (int j = 0; j < m2; j++) {
      res[i * (m1+m2) + j + m1] += b[i * m2 + j];
    }
  }
  return res;
}

int * concat_cols(const int* a, std::size_t n1, std::size_t m, const int* b, std::size_t n2) {
  if (a == nullptr || b == nullptr) {
    throw std::bad_alloc();
  }
  if (add_overflow(n1, n2)) {
    throw std::bad_array_new_length();
  }
  if (m > std::numeric_limits<size_t>::max() / (n1+n2)) {
      throw std::bad_array_new_length();
  }
  int* res = nullptr;
  try {
    res = new int[m * (n1+n2)]();
  }
  catch (...) {
    throw std::bad_array_new_length();
  }
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < m; j++) {
        res[i * m + j] += a[i * m + j];

    }
  }

  for (int i = n1; i < n1+n2; i++) {
    for (int j = 0; j < m; j++) {
        res[i * m + j] += b[(i-n1) * m + j];

    }
  }
  return res;
}

void add_col(int** a, size_t n, size_t m, int filler)
{
  if (a == nullptr) {
    throw std::invalid_argument("a nullptr");
  }
  for (size_t i = 0; i < n; i++) {
    int* new_row = nullptr;
    try {
        new_row = new int[m + 1];
    } catch (...) {
        throw std::bad_alloc();
    }
    for (size_t j = 0; j < m; j++) {
        new_row[j] = a[i][j];
    }
    new_row[m] = filler;
    delete[] a[i];
    a[i] = new_row;
  }
}

void print_matrix(const int* ptr_a, std::size_t n, std::size_t m)
{
    if (ptr_a == nullptr) {
        std::cout << "(null)\n";
        return;
    }

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < m; j++) {
            std::cout << std::setw(2) << ptr_a[i * m + j];
            if (j + 1 < m) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    std::cout << '\n';
}



int main()
{
  int a[3 * 4] = {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9, 10, 11, 12
    };
    int b1[2 * 4] = {
        -1,  -2,  -3, -4,
        -5,  -6, -7,  -8
    };

    int b2[3 * 3] = {
        -1,  -2,  -3, -4,
        -5,  -6, -7,  -8, -9
    };

  print_matrix(a, 3, 4);
  print_matrix(add_row(a, 3, 4, -1), 4, 4);
  print_matrix(add_col(a, 3, 4, -1), 3, 5);
  print_matrix(transposed(a, 3, 4), 4, 3);
  print_matrix(concat_rows(a, 3, 4, b2, 3), 3, 7);
  print_matrix(concat_cols(a, 3, 4, b1, 2), 5, 4);

  int** m = new int*[3];
  for (size_t i = 0; i < 3; ++i) {
    m[i] = new int[4];
    for (size_t j = 0; j < 4; ++j) {
      m[i][j] = (i * 4 + j + 1);
    }
  }
  add_col(m, 3, 4, -1);
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 5; ++j) {
      std::cout << std::setw(2) << m[i][j] << " ";
    }
    std::cout << "\n";
  }


  return 0;
}
