#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <math.h>
#include <limits.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;

#define si(x) scanf("%d", &x)
#define sl(x) scanf("%ld", &x)
#define sll(x) scanf("%lld", &x)
#define sc(x) scanf("%c", &x)
#define ss(x) scanf("%s", x)
#define f(i, a, b) for(i = a; i < b; i++)

struct Data {
  char c;
  double d;
  int a;
  char c2;
};

struct BetterData {
  char c, c2;
  int a;
  double d;
};

int main() {
  printf("char: %lu\nint: %lu\ndouble: %lu\n", sizeof(char), sizeof(int), sizeof(double));

  printf("Size of data: %lu\n", sizeof(Data));
  printf("Size of better data: %lu\n", sizeof(BetterData));
  return 0;
}
