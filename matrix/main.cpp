#include <cstddef>
#include <iostream>
#include <new>
#include <utility>

enum class ErrorCode : int
{
  success = 0,
  input_error = 1,
  allocation_error = 2
};

struct Matrix
{
  size_t rows = 0;
  size_t columns = 0;
  int** field = nullptr;

  Matrix(size_t r = 0, size_t c = 0):
    rows(r),
    columns(c)
  {
    field = new int*[rows];
    size_t created = 0;
    try
    {
      for (; created < rows; created++)
      {
        field[created] = new int[columns];
      }
    }
    catch (...)
    {
      rows = created;
      free();
      throw;
    }
  }

  ~Matrix()
  {
    free();
  }

  void free() noexcept
  {
    for (size_t i = 0; i < rows; ++i)
    {
      delete[] field[i];
    }
    delete[] field;
    field = nullptr;
    rows = 0;
    columns = 0;
  }

  Matrix(const Matrix&) = delete;
  Matrix& operator=(const Matrix&) = delete;

  Matrix(Matrix&& other) noexcept:
    rows(std::exchange(other.rows, 0)),
    columns(std::exchange(other.columns, 0)),
    field(std::exchange(other.field, nullptr))
  {}

  friend void swap(Matrix& a, Matrix& b) noexcept
  {
    std::swap(a.rows, b.rows);
    std::swap(a.columns, b.columns);
    std::swap(a.field, b.field);
  }

  Matrix& operator=(Matrix&& other) noexcept
  {
    swap(*this, other);
    return *this;
  }

  bool read()
  {
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < columns; j++)
      {
        if (!(std::cin >> field[i][j]))
        {
          return false;
        }
      }
    }
    return true;
  }

  void print() const
  {
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < columns; j++)
      {
        std::cout << field[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }

  Matrix transposed() const
  {
    Matrix result(columns, rows);
    for (size_t j = 0; j < columns; j++)
    {
      for (size_t i = 0; i < rows; i++)
      {
        result.field[j][i] = field[i][j];
      }
    }
    return result;
  }
};

int main()
{
  size_t rows = 0, columns = 0;
  if (!(std::cin >> rows >> columns))
  {
    return static_cast< int >(ErrorCode::input_error);
  }

  try
  {
    Matrix matrix(rows, columns);

    if (!matrix.read())
    {
      return static_cast< int >(ErrorCode::input_error);
    }

    Matrix transposed = matrix.transposed();
    transposed.print();
  }
  catch (const std::bad_alloc&)
  {
    return static_cast< int >(ErrorCode::allocation_error);
  }

  return static_cast< int >(ErrorCode::success);
}
