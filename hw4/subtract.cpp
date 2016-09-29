#include "interval.h"

using namespace std;

int wrapPosToNeg(int n) {
  return -32 + (n%32);
}

int wrapNegToPos(int n) {
  return 32 + (n%32);
}

interval interval::operator-(const interval &other) {
  // maximum gap
  int LOW = lo - other.hi;

  // minimum gap
  int HIGH = hi - other.lo;

  // wrap-around if LOW>MAX or max<MIN
  if (LOW > interval::MAX) {
    LOW = wrapPosToNeg(LOW);
  } else if (LOW < interval::MIN) {
    LOW = wrapNegToPos(LOW);
  }

  // wrap-around if HIGH>MAX or max<MIN
  if (HIGH > interval::MAX) {
    HIGH = wrapPosToNeg(HIGH);
  } else if (HIGH < interval::MIN) {
    HIGH = wrapNegToPos(HIGH);
  }

  // case1: for single-point intervals (a, a) - (b, b) = (a-b, a-b)
  // we can return the wrapped values too, because result.lo == result.hi
  // we never encounter low>high in result
  if ((lo==hi) && (other.lo==other.hi)) {
    return interval(LOW, HIGH);
  }

  // case2: if LOW>=HIGH, this means either one or both values wrapped
  if (LOW >= HIGH) {
    return top();
  }

  // case3: when LOW<+HIGH, either none of the values wrapped around or both wrapped around
  // return the most precise result
  if (LOW <= HIGH) {
    return interval(LOW, HIGH); 
  }

  // for all other cases, return the top
  return top();
}

