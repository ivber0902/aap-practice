#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>

long long MOD = 998244353;
long long p3[100001];

long long w(int m, int u, int v)
{
  if (u == v) return 0;
  if (std::abs(u - v) == 1) return (p3[m] - 1) / 2;
  return (p3[m] - 1) % MOD;
}

std::array<long long, 3> cg(std::vector<int> x, int k)
{
  std::array<long long, 3> g = {0, 0, 0};
  for (int i = 0; i < k; i++)
  {
    std::array<long long, 3> ng = g;
    int a = x[i] - 1;
    for (int c = 0; c < 3; c++)
    {
      int other = 3 - a - c;
      if (a == c) ng[c] = g[c];
      else if (std::abs(a - c) == 1)
        ng[c] = (g[other] + 1 + w(i, other, c)) % MOD;
      else ng[c] = (g[c] + 2 * p3[i]) % MOD;
    }
    g = ng;
  }
  return g;
}

int main()
{
  p3[0] = 1;
  for (int i = 1; i < 100001; i++) p3[i] = (p3[i - 1] * 3) % MOD;
  int t; std::cin >> t;
  while (t--)
  {
    int n; std::cin >> n;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < n; ++i) std::cin >> b[i];

    int k = n - 1;
    while (k >= 0 && a[k] == b[k]) k--;
    if (k < 0)
    {
      std::cout << "0\n";
      continue;
    }

    auto ga = cg(a, k);
    auto gb = cg(b, k);
    int c = 5 - a[k] - b[k];

    long long ans;
    if (abs(a[k] - b[k]) == 1) {
      ans = (ga[c] + gb[c] + 1) % MOD;
    } else {
      ans = (ga[b[k] - 1] + gb[a[k] - 1] + 2 + w(k, b[k], a[k]) ) % MOD;
    }
    std::cout << ans << '\n';
  }
  return 0;
}
