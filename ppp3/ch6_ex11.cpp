/*
  PPP3 Chapter6 Exercises 11
  이전 장들의 연습문제를 제시된 규칙에 따라 코드를 정리
 
  피보나치 수열 24/11/15

  피보나치 수열의 규칙
    f0 = 0, f1 = 1, f(n+2) = f(n+1) + f(0)

    f2 = f1 + f0 = 1
    f3 = f2 + f1 = 2
    f4 = f3 + f2 = 3
    f5 = f4 + f3 = 5
    ...

  문법
    calculate
      fibonacci_sequence
      print_fibonacci
*/

/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>  // std::vector

/////////////////////////////////////////////////////////////////////

std::vector<int> fibonacci_table;  // 피보나치 수열을 저장하는 벡터
constexpr int first_term = 1;  // 제 1 항

/////////////////////////////////////////////////////////////////////

// 오류 처리 함수
void error(std::string error_string) {
  throw std::runtime_error{error_string};
} 

// 제 n 항 까지의 피보나치 수열을 vector 에 저장합니다.
// 인수는 1 미만의 수를 받으면 안됩니다.
std::vector<int> fibonacci_sequence(int nth_term) {
  if (nth_term < first_term) {
    error("인수는 1 이상의 수 이여야 합니다.");
  } else if (nth_term > INT_MAX) {
    error("int 형 범위를 초과하였습니다.");
  }
  std::vector<int> table;
  int f0 = 0, f1 = 1, f2 = 0;

  for (size_t i = 0; i < nth_term; ++i) {
    f2 = f1 + f0;
    f0 = f1;
    f1 = f2;
    
    // 오버플로우, 언더플로우 발생 시 반복문 탈출
    if (f2 > INT_MAX || f2 < 1) {
      std::cout << "int 형은 46항 이상에서 오버플로우가 발생합니다.\n";
      break;
    }
    
    table.push_back(f2);
  }

  return table;
}

// 피보나치 수열을 출력
const void print_fibonacci() {
  for (const auto& f : fibonacci_table) {
    std::cout << f << ' ';
  }
  puts("");
}

// 피보나치 수열의 계산, 출력을 처리하는 함수
void calculate() {
  fibonacci_table = fibonacci_sequence(47);
  print_fibonacci();
}

/////////////////////////////////////////////////////////////////////

int main() {
  try {
    calculate();
    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  } catch (...) {
    std::cerr << "exception" << std::endl;
    return -2;
  }

  return 0;
}
