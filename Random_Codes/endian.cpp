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

int main() {
  int a = 1;
  char *cptr = (char *) &a;

  printf("%d\n", *cptr);
  cptr++;
  printf("%d\n", *cptr);
  cptr++;
  printf("%d\n", *cptr);
  cptr++;
  printf("%d\n", *cptr);

  return 0;
}
