/*
  PPP3 Chapter 5, 연습문제 8
  
  순열, 조합 프로그램 24/11/11

  순열(permutation)은 집합의 순서가 있는 부분 집합입니다. 
  예를 들어, 금고 조합을 선택하고 싶다고 가정해봅시다. 
  가능한 숫자는 60개이고, 조합을 위해 서로 다른 3개의 숫자가 필요합니다. 
  조합에 대한 순열은 P(60, 3)개가 있으며, 
  여기서 P는 P(a, b) = (a!) / ((a - b)!)라는 공식으로 정의됩니다. 
  여기서 !는 팩토리얼 연산자로 사용되며, 예를 들어 4!는 4∗3∗2∗1입니다.

  조합(combination)은 순열과 비슷하지만, 대상의 순서는 중요하지 않습니다. 
  예를 들어, ‘바나나 스플릿’ 선디(sundae)에 다섯 가지 아이스크림 중 
  서로 다른 세 가지 맛을 사용하고 싶다고 하면, 
  바닐라 한 스쿱을 처음 또는 마지막에 놓는 것은 중요하지 않을 것입니다. 
  조합에 대한 공식은 C(a, b) = (P(a, b)) / (b!)입니다.


  결과

  p 60 3
  계산 결과(permutation): 205320

  c 60 3
  계산 결과(combination): 34220
*/

/////////////////////////////////////////////////////////////////////
// 표준 라이브러리
/////////////////////////////////////////////////////////////////////
#include <iostream>

/////////////////////////////////////////////////////////////////////
// 함수의 원형
/////////////////////////////////////////////////////////////////////
void error(std::string e);
double factorial(double a);

/////////////////////////////////////////////////////////////////////
// 순열, 조합, 팩토리얼 함수
/////////////////////////////////////////////////////////////////////

// 순열
// 서로 다른 n개의 원소에서 r(단, 0 < r <= n) 개를 뽑아 순서에 상관있게 배열
// 전제 조건: 인수는 a >= b > 0 이여야 합니다.
double permutation(double a, double b) {
  if (!(b > 0) || !(a >= b)) {          // 전제 조건을 만족하지 않을 경우 오류
    error("인수가 잘못되었습니다.");
  }
  double numerator = factorial(a);      // 분자
  double denominator = factorial(a-b);  // 분모
  double value = numerator / denominator;
  return value;
}

// 조합
// 서로 다른 n개의 원소에서 r(단, 0 < r <= n) 개를 중복 없이, 순서를 고려하지 않고 선택
// 전제 조건: 인수는 a >= b > 0 이여야 합니다.
double combination(double a, double b) {
  if (!(b > 0) || !(a >= b)) {           // 전제 조건을 만족하지 않을 경우 오류
    error("인수가 잘못되었습니다.");
  }
  double numerator = permutation(a, b);  // 분자
  double denominator = factorial(b);     // 분모
  double value = numerator / denominator;
  return value;
} 

// 팩토리얼
// 순열, 조합에서 인수를 미리 검사했음
double factorial(double a) {
  double i = static_cast<double>(a-1);
  if (a == 1 || a == 0) return 1;
  while (i > 1) {
    a *= i;
    --i;
  }
  return a;
}
/////////////////////////////////////////////////////////////////////
// 계산 테스트 함수
/////////////////////////////////////////////////////////////////////
void test_function() {
  std::cout << "PPP3 Chapter 5, 연습문제 8\n"
            << "순열, 조합을 계산하는 프로그램\n"
            << "입력 순서: (p or c, or e), a, b\n"
            << "순열: p, 조합: c, 종료: e, a,b: 수(단, a>=b>0)\n"
            << std::endl;
  char c = 0;
  double a = 0, b = 0;
  std::cin >> c;
  if (c == 'e') return;
  double value = 0;
  std::cin >> a >> b;

  switch (c) {
  case 'p':
    value = permutation(a, b);
    std::cout << "계산 결과(permutation): " << value << '\n';
    return;
  case 'c':
    value = combination(a, b);
    std::cout << "계산 결과(combination): " << value << '\n';
    return;
  default:
    error("입력을 잘못하였습니다.\n입력 순서: (p or c, or e), a, b\n순열: p, 조합: c, 종료: e, a,b: 수(단, a>=b>0)");
    return;
  }
}

/////////////////////////////////////////////////////////////////////

int main() {
  try {
    test_function();
    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << "error: " << e.what() << '\n';
    return -1;
  } catch (...) {
    std::cerr << "exception\n";
    return -2;
  }
  return 0;
}

/////////////////////////////////////////////////////////////////////
// 예외 처리 함수들
/////////////////////////////////////////////////////////////////////

void error(std::string e) {
  throw std::runtime_error{e};
}
