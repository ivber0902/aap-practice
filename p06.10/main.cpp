#include <cstddef>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

bool readNumbers(int* numbers, size_t length)
{
  for (int* p = numbers; p < numbers + length; p++)
  {
    if (!(std::cin >> *p))
    {
      return false;
    }
  }
  return true;
}

int sum(const int* numbers, size_t length)
{
  int result = 0;
  for (size_t i = 0; i < length; i++)
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

void printNumbers(const int* numbers, size_t n)
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
  if (n <= 0)
  {
    return 1;
  }
  size_t length = static_cast<size_t>(n);

  int* numbers = nullptr;
  try
  {
    numbers = new int[length];
  }
  catch (const std::bad_alloc&)
  {
    return 2;
  }

  if (!readNumbers(numbers, length))
  {
    delete[] numbers;
    return 1;
  }

  int s = 0;
  double average = 0;
  try
  {
    s = sum(numbers, length);
    average = static_cast<double>(s) / length;
  }
  catch (...)
  {
    delete[] numbers;
    return 3;
  }

  printNumbers(numbers, length);
  std::cout << "average = " << average << "\nsum = " << s << "\n";

  delete[] numbers;
  return 0;
}
