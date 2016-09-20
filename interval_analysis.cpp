#include <iostream>
#include <assert.h>

using namespace std;

class interval {

  // 5-bit signed intervals: valid values for lo and hi are -16..15 and it is
  // required that hi >= lo. the bounds are inclusive.
  int lo, hi;

  // counter for number of wraps
  int counter=0;

  public:
  // asset while setting the interval values
  void set(int low, int high);

  // these functions must trigger an assertion violation when presented with any
  // invalid interval, and must never return an invalid interval

  // requirement: be sound and fully precise
  // the second argument is to be subtracted from the first
  static interval subtract(interval, interval);

  // requirement: be sound and don't always return top
  static interval bitwise_and(interval, interval);

  // print the result interval
  void print(interval);

  // wrap positive overflows to negative
  int wrapPosToNeg(int n);

  // wrap negative overflows to positive
  int wrapNegToPos(int n);
};

void interval::set(int low, int high) {
  assert(-16<=low && low <=15 && "Low value is out of range, must be (-16, 15)");
  assert(-16<=high && high<=15 && "High value is out of range, must be (-16, 15)");
  assert(low<=high && "Low must be less than high");
  lo = low;
  hi = high;
}

int interval::wrapPosToNeg(int n) {
  return -16 + (n%16);
}

int interval::wrapNegToPos(int n) {
  return 16 + (n%16);
}

interval interval::subtract(interval r1, interval r2) {
  interval diff;

  // maximum difference 
  diff.lo = r1.lo - r2.hi;
  // wraparound if MAX<low<MIN
  if (diff.lo>15) {
    diff.lo = diff.wrapPosToNeg(diff.lo);
    diff.counter++;
  } else if (diff.lo<-16) {
    diff.lo = diff.wrapNegToPos(diff.lo);
    diff.counter++;
  }

  // minimum difference
  diff.hi = r1.hi - r2.lo;
  //wrap around if MAX<high<MIN
  if (diff.hi>15) {
    diff.hi = diff.wrapPosToNeg(diff.hi);
    diff.counter++;
  } else if (diff.lo<-16) {
    diff.hi = diff.wrapNegToPos(diff.hi);
    diff.counter++;
  }

  // return precise results
  // case 1: Low>=high and either one value wraps around or both of them arap around, return Top
  // case 2.1: Low<=High and none wrap around, this gives the most precise result
  // case 2.2: Low<=High and both the values wrapped around, again it's the precise result
  // case 3: for all other cases return the top
  if (diff.lo>=diff.hi && (diff.counter==1 || diff.counter==2)) {
    diff.lo = -16;
    diff.hi = 15;
  } else if (diff.lo<=diff.hi && (diff.counter==0 || diff.counter==2)) {
    ; //already precise
  } else {
    diff.lo = -16;
    diff.hi = 15;
  }

  return diff;
}

interval interval::bitwise_and(interval r1, interval r2) {
  interval result;

  if ((r1.lo==0 && r1.hi==0) || (r2.lo==0 && r2.hi==0)) {
    // case1: AND with (0, 0) gives (0, 0)
    result.lo = result.hi = 0;
  } else if ((r1.lo>=0 && r1.hi<=3) || (r2.lo>=0 && r2.hi<=3)) {
    // case2: if any of the ranges is (0,3), its known that top 3 bits will be 0, i.e. 000xx, hence
    // the resulting range should be (0,3)
    result.lo = 0;
    result.hi = 3;
  } else if ((r1.lo>=0 && r1.hi<=7) || (r2.lo>=0 && r2.hi<=7)) {
    // case2: if any of the ranges is (0,7), its known that top 2 bits will be 0, i.e. 00xxx, hence
    // the resulting range should be (0,7)
    result.lo = 0;
    result.hi = 7;
  } else if ((r1.lo>=0 && r1.hi>=0) || (r2.lo>=0 && r2.hi>=0)) {
    // case2: if either interval is completely positive, then return positive range only (0,15)
    result.lo = 0;
    result.hi = 15;
  } else if ((r1.lo<0 && r1.hi<0) && (r2.lo<0 && r2.hi<0)) {
    // case3: both intervals are negative, return just negative interval (-16, -1)
    result.lo = -16;
    result.hi = -1;
  } else {
    // for all other cases, return top
    result.lo = -16;
    result.hi = 15;
  }

  return result;
}

void interval::print(interval result) {
  cout << "(" << result.lo << ", " << result.hi << ")\n";
}

int main () {
  interval range1, range2, result;

  // testing subtract function
  // Test1: full range - full range; low>high and both wrap around
  range1.set(-16, 15);
  range2.set(-16, 15);
  result = result.subtract(range1, range2);
  result.print(result);

  // Test2 : when Low=High and one wraps around
  range1.set(0,1);
  range2.set(-16,15);
  result = result.subtract(range1, range2);
  result.print(result);

  // Test3: Low>High and one wraps around
  range1.set(0, 1);
  range2.set(-16, -15);
  result = result.subtract(range1, range2);
  result.print(result);

  // Test4: low<=high and both wrapped around
  range1.set(5,6);
  range2.set(-16, -15);
  result = result.subtract(range1, range2);
  result.print(result);

  // testing bitwise_and function

  // full range ANDed with full range
  range1.set(-16,15);
  range2.set(-16, 15);
  result = result.bitwise_and(range1, range2);
  result.print(result);

  // test 2 : range1 is positive and range 2 is positive
  range1.set(0,10);
  range2.set(2, 9);
  result = result.bitwise_and(range1, range2);
  result.print(result);

  // test3: range1 is positive and range2 is partially negative
  range1.set(0,10);
  range2.set(-2, 9);
  result = result.bitwise_and(range1, range2);
  result.print(result);


  // test4: range1 is positive and range2 is fully negative
  range1.set(0,10);
  range2.set(-9, -2);
  result = result.bitwise_and(range1, range2);
  result.print(result);

  // test5:both ranges are negative
  range1.set(-10,-4);
  range2.set(-9, -2);
  result = result.bitwise_and(range1, range2);
  result.print(result);

  // test6: one of the ranges is (0, 0)
  range1.set(0, 0);
  range2.set(-10, 10);
  result = result.bitwise_and(range1, range2);
  result.print(result);

  // test 7 : range1 is between (0,3) and range2 is (-16,15)
  range1.set(1,3);
  range2.set(-16, 15);
  result = result.bitwise_and(range1, range2);
  result.print(result);

  // test 8 : range2 is between (0,7) and range1 is (-16,15)
  range1.set(-16,15);
  range2.set(2, 7);
  result = result.bitwise_and(range1, range2);
  result.print(result);

 return 0;
}
