#include "interval.h"

using namespace std;


void test1() {
  interval a(-32, 31);
  interval b(-32, 31);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test2() {
  interval a(0, 10);
  interval b(2, 29);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test3() {
  interval a(0, 14);
  interval b(-32, 20);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test4() {
  interval a(0, 14);
  interval b(-32, -1);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test5() {
  interval a(0, 30);
  interval b(-32, -1);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test6() {
  interval a(-27, -3);
  interval b(-10, 0);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test7() {
  interval a(1, 1);
  interval b(3, 3);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test8() {
  interval a(0, 0);
  interval b(-32, 31);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test9() {
  interval a(-32, 31);
  interval b(-32, 31);
  interval result = a - b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test10() {
  interval a(3, 3);
  interval b(-2, -2);
  interval result = a - b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test11() {
  interval a(0, 1);
  interval b(-32, 31);
  interval result = a - b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test12() {
  interval a(0, 1);
  interval b(-32, -31);
  interval result = a - b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test13() {
  interval a(5, 6);
  interval b(-32, -31);
  interval result = a - b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test14() {
  interval a(10, 20);
  interval b(6, 8);
  interval result = a - b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test15() {
  interval a(-32, -32);
  interval b(1, 1);
  interval result = a - b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test16() {
  interval a(-31, -30);
  interval b(-31, -30);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test17() {
  interval a(-31, 31);
  interval b(-31, 31);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test18() {
  interval a(-14, 31);
  interval b(-14, 31);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test19() {
  interval a(-14, -2);
  interval b(-14, -2);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test20() {
  interval a(-7, 31);
  interval b(-7, 31);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test21() {
  interval a(-2, 15);
  interval b(-2, 15);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

void test22() {
  interval a(-1, 15);
  interval b(-1, 15);
  interval result = a & b;
  cout << result.lo << " ... " << result.hi << endl;
}

int main() {
  // testing of binaryAnd operation
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test16();
  test17();
  test18();
  test19();
  test20();
  test21();
  test22();

  //testing of subtract operation
  test9();
  test10();
  test11();
  test12();
  test13();
  test14();
  test15();


  return 0;
}
