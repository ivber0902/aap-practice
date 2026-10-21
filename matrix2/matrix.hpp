#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>

size_t checked_size(size_t n, size_t m);
void check_ptr(const int* p, size_t length, const char* message);
void check_sequence(const int* const* b, size_t s, size_t length);
int checked_add(int x, int y);
int checked_mul(int x, int y);

int* create_matrix(size_t n, size_t m);
void destroy_matrix(int* a) noexcept;
int** create_sequence(size_t s, size_t n, size_t m);
void destroy_sequence(int** b, size_t s) noexcept;

void read_matrix(size_t n, size_t m, int* a);
void read_sequence(size_t s, size_t n, size_t m, int* const* b);
void print_matrix(size_t n, size_t m, const int* a);

// C = A + B
void sum(size_t n, size_t m, int* c, const int* a, const int* b);
// A + B
int* sum(size_t n, size_t m, const int* a, const int* b);
// A += B
void add(size_t n, size_t m, int* a, const int* b);

// C = A * B
void mul(int* c, const int* a, size_t n1, size_t m1, const int* b, size_t m2);
// A * B
int* mul(const int* a, size_t n1, size_t m1, const int* b, size_t m2);

// B[0]*A + B[1]*A + ... + B[s-1]*A
void sum_of_mul(size_t n, int* c, const int* a, const int* const* b, size_t s);
int* sum_of_mul(size_t n, const int* a, const int* const* b, size_t s);

// (B[0]*A) * (B[1]*A) * ... * (B[s-1]*A)
void mul_of_mul(size_t n, int* c, const int* a, const int* const* b, size_t s);
int* mul_of_mul(size_t n, const int* a, const int* const* b, size_t s);

// (B[0]+A) * (B[1]+A) * ... * (B[s-1]+A)
void mul_of_sum(size_t n, int* c, const int* a, const int* const* b, size_t s);
int* mul_of_sum(size_t n, const int* a, const int* const* b, size_t s);

#endif
