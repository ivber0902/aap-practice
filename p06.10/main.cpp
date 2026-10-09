#include <cstddef>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

void increaseNumbers(int*& numbers, size_t& length)
{
  if (length > std::numeric_limits<size_t>::max() / 2)
  {
    throw std::length_error("increaseNumbers: size overflow");
  }

  const size_t newLength = length * 2;
  int* newNumbers = new int[newLength]();

  for (size_t i = 0; i < length; i++)
  {
    newNumbers[i] = numbers[i];
  }
  for (size_t i = length; i < newLength; i++)
  {
    newNumbers[i] = 0;
  }

  delete[] numbers;
  numbers = newNumbers;
  length = newLength;
}

bool readNumbers(int*& numbers, size_t& length)
{
  size_t i = 0;
  while (true)
  {
    if (!(std::cin >> numbers[i]))
    {
      if (std::cin.eof())
      {
        break;
      }
      return false;
    }
    i++;
    if (i == length)
    {
      increaseNumbers(numbers, length);
    }
  }
  length = i;
  return true;
}

void printNumbers(const int* numbers, size_t n)
{
  for (size_t i = 0; i < n; i++)
  {
    std::cout << numbers[i] << " ";
  }
  std::cout << "\n";
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

int main()
{
  size_t length = 1;

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
