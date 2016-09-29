#include "interval.h"

using namespace std;

// find max of two numbers
int max(int a, int b) {
  return (a>=b)?a:b;
}


// find min of two numbers
int min(int a, int b) {
  return (a<=b)?a:b;
}

interval interval::operator&(const interval &other) {

  // case1: if both intervals are equal
  // we get the precise bound for upper value
  // However, we need to find the bound for lower value
  // basically, testing for leading 1's here
  if (*this == other) {
    if (lo>=0 && hi>=0) {
      return interval(0, hi);
    } else if (lo<=-1 && lo>=-2) {
      return interval(-2, hi);
    } else if (lo<=-1 && lo>=-4) {
      return interval(-4, hi);
    } else if (lo<=-1 && lo>=-8) {
      return interval(-8, hi);
    } else if (lo<=-1 && lo>=-16) {
      return interval(-16, hi);
    } else {
      return interval(interval::MIN, hi);
    }
  }
  
  // case2: AND with (0, 0) gives (0, 0)
  if ((lo==0 && hi==0) || (other.lo==0 && other.hi==0)) {
    return interval(0, 0);
  }
  
  // case3: single-point ranges where lo==hi
  if (lo==hi && other.lo == other.hi) {
    return interval(lo & other.lo, hi & other.hi);
  }
  
  // case4: both ranges are positive,
  // find min(max(r1), max(r2)); return [0, min]
  if ((lo>=0 && hi>=0) && (other.lo>=0 && other.hi>=0)) {
    return interval(0, min(max(lo, hi), max(other.lo, other.hi)));
  }
  
  // case5: 4-leading zeros, return range [0,3]
  if ((lo>=0 && hi<=3) || (other.lo>=0 && other.hi<=3)) {
    return interval(0, 3);
  }
  
  // case6: 3-leading zeros, return range [0,7]
  if ((lo>=0 && hi<=7) || (other.lo>=0 && other.hi<=7)) {
    return interval(0, 7);
  }
  
  // case7: 2-leading zeros, return [0, 15]
  if ((lo>=0 && hi<=15) || (other.lo>=0 && other.hi<=15)) {
    return interval(0, 15);
  }
  
  // case8: if either interval is completely positive, return [0, MAX]
  if ((lo>=0 && hi>=0) || (other.lo>=0 && other.hi>=0)) {
    return interval(0, interval::MAX);
  }
  
  // case9: both intervals are negative, return negative interval [MIN, 0]
  if ((lo<0 && hi<=0) && (other.lo<0 && other.hi<=0)) {
    return interval(interval::MIN, 0);
  }
  
  // case10: for all other cases, return top
  return top();

}
