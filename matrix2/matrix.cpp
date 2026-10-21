#include "matrix.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

size_t checked_size(size_t n, size_t m)
{
  if (m != 0 && n > std::numeric_limits< size_t >::max() / m)
  {
    throw std::length_error("matrix size overflow");
  }
  return n * m;
}

void check_ptr(const int* p, size_t length, const char* message)
{
  if (length != 0 && p == nullptr)
  {
    throw std::invalid_argument(message);
  }
}

void check_sequence(const int* const* b, size_t s, size_t length)
{
  if (s != 0 && b == nullptr)
  {
    throw std::invalid_argument("sequence is null");
  }
  for (size_t i = 0; i < s; i++)
  {
    check_ptr(b[i], length, "sequence element is null");
  }
}

int to_int(long long r, const char* message)
{
  if (r > std::numeric_limits< int >::max() || r < std::numeric_limits< int >::min())
  {
    throw std::overflow_error(message);
  }
  return static_cast< int >(r);
}

int checked_add(int x, int y)
{
  return to_int(static_cast< long long >(x) + y, "int overflow in addition");
}

int checked_mul(int x, int y)
{
  return to_int(static_cast< long long >(x) * y, "int overflow in multiplication");
}

int* create_matrix(size_t n, size_t m)
{
  return new int[checked_size(n, m)];
}

void destroy_matrix(int* a) noexcept
{
  delete[] a;
}

int** create_sequence(size_t s, size_t n, size_t m)
{
  int** b = new int*[s]();
  try
  {
    for (size_t i = 0; i < s; i++)
    {
      b[i] = create_matrix(n, m);
    }
  }
  catch (...)
  {
    destroy_sequence(b, s);
    throw;
  }
  return b;
}

void destroy_sequence(int** b, size_t s) noexcept
{
  if (b == nullptr)
  {
    return;
  }
  for (size_t i = 0; i < s; i++)
  {
    destroy_matrix(b[i]);
  }
  delete[] b;
}

void read_matrix(size_t n, size_t m, int* a)
{
  const size_t length = checked_size(n, m);
  check_ptr(a, length, "read_matrix: a is null");
  for (size_t k = 0; k < length; k++)
  {
    if (!(std::cin >> a[k]))
    {
      throw std::invalid_argument("read_matrix: bad input");
    }
  }
}

void read_sequence(size_t s, size_t n, size_t m, int* const* b)
{
  check_sequence(b, s, checked_size(n, m));
  for (size_t i = 0; i < s; i++)
  {
    read_matrix(n, m, b[i]);
  }
}

void print_matrix(size_t n, size_t m, const int* a)
{
  check_ptr(a, checked_size(n, m), "print_matrix: a is null");
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < m; j++)
    {
      std::cout << a[i * m + j] << ' ';
    }
    std::cout << '\n';
  }
}
