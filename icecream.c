#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BALLS 3

#define TASTES 5

enum tastes
{
  C,
  N,
  V,
  P,
  F
};

#define SECOND(a, b, ...) b
#define IS_PROBE(...) SECOND(__VA_ARGS__, 0)
#define PROBE() ~, 1

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a##__VA_ARGS__

#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define _NOT_0 PROBE()
#define BOOL(x) NOT(NOT(x))

#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)
#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...) _IF_0_ELSE
#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define EMPTY()

#define EVAL(...) EVAL1024(__VA_ARGS__)
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()

#define FIRST(a, ...) a
#define HAS_ARGS(...) BOOL(FIRST(_END_OF_ARGUMENTS_ __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0

#define MAP(m, first, ...)                                                 \
  m(first, __VA_ARGS__)                                                    \
      IF_ELSE(HAS_ARGS(__VA_ARGS__))(                                      \
          DEFER2(_MAP)()(m, __VA_ARGS__))(/* Do nothing, just terminate */ \
      )
#define _MAP() MAP

#define PP_NARG(...) \
  PP_NARG_(, ##__VA_ARGS__, PP_RSEQ_N())
#define PP_NARG_(...) \
  PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(                                     \
    z, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,       \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
    _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
    _61, _62, _63, N, ...) N
#define PP_RSEQ_N()                           \
  63, 62, 61, 60,                             \
      59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
      49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
      39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
      29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
      19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
      9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define TIMES(...) EVAL(MAP(TIME2FOR, __VA_ARGS__))

#define TIME2FOR(x, ...)                     \
  for (int CAT(i, PP_NARG(__VA_ARGS__)) = 0; \
       CAT(i, PP_NARG(__VA_ARGS__)) < x;     \
       CAT(i, PP_NARG(__VA_ARGS__))++)

int main(int argc, char **argv)
{
  int combi[200][TASTES];
  FILE *f = fopen("combinations.txt", "w");
  TIMES(TASTES, TASTES, TASTES, TASTES, TASTES)
  {
    fprintf(f, "%i %i %i %i %i\n", i4, i3, i2, i1, i0);
  }

  fclose(f);
  return 0;
}