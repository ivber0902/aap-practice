#include <cstddef>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

bool readNumbers(int* numbers, int n)
{
  for (int* p = numbers; p < numbers + n; p++)
  {
    if (!(std::cin >> *p))
    {
      return false;
    }
  }
  return true;
}

int sum(const int* numbers, int n)
{
  int result = 0;
  for (size_t i = 0; i < n; i++)
  {
    if ((numbers[i] > 0 && result > std::numeric_limits<int>::max() - numbers[i]) ||
        (numbers[i] < 0 && result < std::numeric_limits<int>::min() - numbers[i]))
    {
      throw std::overflow_error("error while counting sum");
    }
    result += numbers[i];
  }
  return result;
}

void printNumbers(const int* numbers, int n)
{
  for (size_t i = 0; i < n; i++)
  {
    std::cout << numbers[i] << " ";
  }
  std::cout << "\n";
}

int main()
{
  int n = 0;
  if (!(std::cin >> n))
  {
    return 1;
  }
  if (n < 0)
  {
    return 1;
  }
  if (n == 0)
  {
    std::cout << "\n0\n0\n";
    return 0;
  }

  int* numbers = nullptr;
  try
  {
    numbers = new int[n];
  }
  catch (const std::bad_alloc&)
  {
    return 2;
  }
  catch (...)
  {
    return 3;
  }

  if (!readNumbers(numbers, n))
  {
    delete[] numbers;
    return 1;
  }

  int s = 0;
  double average = 0;
  try
  {
    s = sum(numbers, n);
    average = static_cast<double>(s) / n;
  }
  catch (...)
  {
    delete[] numbers;
    return 3;
  }

  printNumbers(numbers, n);
  std::cout << "average = " << average << "\nsum = " << s << "\n";

  delete[] numbers;
  return 0;
}
