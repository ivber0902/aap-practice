#include "matrix.hpp"

void move_to(size_t length, int* c, int* r) noexcept
{
  for (size_t k = 0; k < length; k++)
  {
    c[k] = r[k];
  }
  destroy_matrix(r);
}

int* identity(size_t n)
{
  int* c = new int[checked_size(n, n)]();
  for (size_t i = 0; i < n; i++)
  {
    c[i * n + i] = 1;
  }
  return c;
}

int* sum(size_t n, size_t m, const int* a, const int* b)
{
  const size_t length = checked_size(n, m);
  check_ptr(a, length, "sum: a is null");
  check_ptr(b, length, "sum: b is null");
  int* c = create_matrix(n, m);
  try
  {
    for (size_t k = 0; k < length; k++)
    {
      c[k] = checked_add(a[k], b[k]);
    }
  }
  catch (...)
  {
    destroy_matrix(c);
    throw;
  }
  return c;
}

void sum(size_t n, size_t m, int* c, const int* a, const int* b)
{
  const size_t length = checked_size(n, m);
  check_ptr(c, length, "sum: c is null");
  move_to(length, c, sum(n, m, a, b));
}

void add(size_t n, size_t m, int* a, const int* b)
{
  sum(n, m, a, a, b);
}

int* mul(const int* a, size_t n1, size_t m1, const int* b, size_t m2)
{
  check_ptr(a, checked_size(n1, m1), "mul: a is null");
  check_ptr(b, checked_size(m1, m2), "mul: b is null");
  int* c = create_matrix(n1, m2);
  try
  {
    for (size_t i = 0; i < n1; i++)
    {
      for (size_t j = 0; j < m2; j++)
      {
        int acc = 0;
        for (size_t k = 0; k < m1; k++)
        {
          acc = checked_add(acc, checked_mul(a[i * m1 + k], b[k * m2 + j]));
        }
        c[i * m2 + j] = acc;
      }
    }
  }
  catch (...)
  {
    destroy_matrix(c);
    throw;
  }
  return c;
}

void mul(int* c, const int* a, size_t n1, size_t m1, const int* b, size_t m2)
{
  const size_t length = checked_size(n1, m2);
  check_ptr(c, length, "mul: c is null");
  move_to(length, c, mul(a, n1, m1, b, m2));
}

int* sum_of_mul(size_t n, const int* a, const int* const* b, size_t s)
{
  const size_t length = checked_size(n, n);
  check_ptr(a, length, "sum_of_mul: a is null");
  check_sequence(b, s, length);
  int* c = new int[length]();
  int* t = nullptr;
  try
  {
    t = create_matrix(n, n);
    for (size_t i = 0; i < s; i++)
    {
      mul(t, b[i], n, n, a, n);
      add(n, n, c, t);
    }
  }
  catch (...)
  {
    destroy_matrix(t);
    destroy_matrix(c);
    throw;
  }
  destroy_matrix(t);
  return c;
}

void sum_of_mul(size_t n, int* c, const int* a, const int* const* b, size_t s)
{
  const size_t length = checked_size(n, n);
  check_ptr(c, length, "sum_of_mul: c is null");
  move_to(length, c, sum_of_mul(n, a, b, s));
}

int* mul_of_mul(size_t n, const int* a, const int* const* b, size_t s)
{
  const size_t length = checked_size(n, n);
  check_ptr(a, length, "mul_of_mul: a is null");
  check_sequence(b, s, length);
  int* c = identity(n);
  int* t = nullptr;
  try
  {
    t = create_matrix(n, n);
    for (size_t i = 0; i < s; i++)
    {
      mul(t, b[i], n, n, a, n);
      mul(c, c, n, n, t, n);
    }
  }
  catch (...)
  {
    destroy_matrix(t);
    destroy_matrix(c);
    throw;
  }
  destroy_matrix(t);
  return c;
}

void mul_of_mul(size_t n, int* c, const int* a, const int* const* b, size_t s)
{
  const size_t length = checked_size(n, n);
  check_ptr(c, length, "mul_of_mul: c is null");
  move_to(length, c, mul_of_mul(n, a, b, s));
}

int* mul_of_sum(size_t n, const int* a, const int* const* b, size_t s)
{
  const size_t length = checked_size(n, n);
  check_ptr(a, length, "mul_of_sum: a is null");
  check_sequence(b, s, length);
  int* c = identity(n);
  int* t = nullptr;
  try
  {
    t = create_matrix(n, n);
    for (size_t i = 0; i < s; i++)
    {
      sum(n, n, t, b[i], a);
      mul(c, c, n, n, t, n);
    }
  }
  catch (...)
  {
    destroy_matrix(t);
    destroy_matrix(c);
    throw;
  }
  destroy_matrix(t);
  return c;
}

void mul_of_sum(size_t n, int* c, const int* a, const int* const* b, size_t s)
{
  const size_t length = checked_size(n, n);
  check_ptr(c, length, "mul_of_sum: c is null");
  move_to(length, c, mul_of_sum(n, a, b, s));
}
