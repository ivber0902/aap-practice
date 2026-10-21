#include "matrix.hpp"

#include <iostream>
#include <new>
#include <stdexcept>

enum class ErrorCode : int
{
  success = 0,
  input_error = 1,
  allocation_error = 2,
  overflow_error = 3
};

int main()
{
  long long int n_in = 0, s_in = 0;
  if (!(std::cin >> n_in >> s_in) || n_in < 0 || s_in < 0)
  {
    return static_cast< int >(ErrorCode::input_error);
  }
  const size_t n = static_cast< size_t >(n_in);
  const size_t s = static_cast< size_t >(s_in);

  int* a = nullptr;
  int** b = nullptr;
  int* result = nullptr;
  ErrorCode code = ErrorCode::success;

  try
  {
    a = create_matrix(n, n);
    read_matrix(n, n, a);
    b = create_sequence(s, n, n);
    read_sequence(s, n, n, b);

    result = sum_of_mul(n, a, b, s);
    std::cout << "sum_of_mul:\n";
    print_matrix(n, n, result);
    destroy_matrix(result);
    result = nullptr;

    result = mul_of_mul(n, a, b, s);
    std::cout << "mul_of_mul:\n";
    print_matrix(n, n, result);
    destroy_matrix(result);
    result = nullptr;

    result = mul_of_sum(n, a, b, s);
    std::cout << "mul_of_sum:\n";
    print_matrix(n, n, result);
    destroy_matrix(result);
    result = nullptr;
  }
  catch (const std::bad_alloc&)
  {
    code = ErrorCode::allocation_error;
  }
  catch (const std::length_error&)
  {
    code = ErrorCode::allocation_error;
  }
  catch (const std::invalid_argument&)
  {
    code = ErrorCode::input_error;
  }
  catch (const std::overflow_error&)
  {
    code = ErrorCode::overflow_error;
  }

  destroy_matrix(result);
  destroy_sequence(b, s);
  destroy_matrix(a);
  return static_cast< int >(code);
}
