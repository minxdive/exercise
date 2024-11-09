/*
  PPP3 Chapter 5, 연습문제 5
  
  비트 논리 표현식을 위한 문법을 작성
*/

/////////////////////////////////////////////////////////////////////
/*
  비트 연산 계산기 24/11/08
  
  비트 연산의 순서
  0. ()
  1. -(Minus)
  2. ~(Complment)
  3. !(Not)
  4. <<, >>(Shift)
  5. &(And)
  6. ^(Xor)
  7. |(Or)

  !: 논리(true 1, false 0) Not
  ~: 비트 Not

  Expression 표현식 <ㅡㅡㅡㅡㅡㅡㅡㅡㅡ
  ->  or_term()                    |
    ->  xor_term()                 |
      ->  and_term()               |
        ->  shift_term()           |
          ->  not_term()           |
            ->  complement_term()  |
              -> minus_term()      |
                ->  Primary 기본식 ㅡ  

  (), ~, <<, >>, &, ^, |, !, (-) 계산 구현

  전제 조건: 입력한 모든 수는 정수 입니다.

  결과: !~20 & -44 | 88 >> 2 ^ 9 << (4 & (3 | ~2)) = 134
*/
/////////////////////////////////////////////////////////////////////

#include <iostream>

void error(std::string e);
void error(std::string s1, std::string s2);
int expression();

/////////////////////////////////////////////////////////////////////
/*                          토큰, 스트림                             */
/////////////////////////////////////////////////////////////////////
class Token {              // 수, 기호 등의 단위들을 다루는 토큰
public:
  char kind;               // 수, 기호를 나타냅니다.
  int value;               // 숫자일때, 그 값을 나타냅니다.
  Token(char k) : kind(k), value(0) {}  // 초기화 생성자 리스트
  Token(char k, int v) : kind(k), value(v) {}
};
class Token_stream {       // 토큰들의 스트림을 제어합니다.
public:
  Token_stream() : full(false) {}
  Token get();             // 토큰을 스트림으로 가져옵니다.
  void putback(Token t);   // 토큰을 스트림에 다시 넣습니다.
private:
  bool full;               // 토큰이 할당되어있는지 확인
  Token buffer{'0'};       // 버퍼
}; Token_stream ts;        // 토큰 스트림 객체 ts

Token Token_stream::get() {
  if (full) {              // 토큰 존재 시, 제거
    full = false;
    return buffer;
  }
  char kind = 0;
  std::cin >> kind;
  if (!std::cin >> kind) error("Token_stream::get(): 입력되지 않았습니다.");
  
  switch (kind) {
  case 'e': case '=':       // e: 종료, =: 결과
  case '(': case ')': case '~':  // (), complement, and, xor, or, not, minus
  case '&': case '^': case '|': case '!': case '-':
    return Token{kind};
  case '<': case '>':  {    // shift
    std::cin.ignore(1);
    return Token{kind};
  }
  case '0': case '1': case '2':
  case '3': case '4': case '5':
  case '6': case '7': case '8':
  case '9': {
    std::cin.putback(kind);  // 수를 다시 cin 에 넣고
    int val = 0;
    std::cin >> val;         // int 형 변수에 넣어줌
    return Token{'8', val};  // '8' 은 수를 나타내는 문자
  }
  default:
    error("Token_stream::get(): 잘못된 토큰입니다.");
    exit(-1);
  }
}
void Token_stream::putback(Token t) {
  if (full) error("Token_stream::putback(): 버퍼가 가득찼습니다.");
  buffer = t;
  full = true;
}


/////////////////////////////////////////////////////////////////////
/*************************   비트 연산   ****************************/
/////////////////////////////////////////////////////////////////////

int primary() {            // (), 숫자 처리
  Token t = ts.get();
  while (1) {
    switch (t.kind) {
    case '(': {
      int lval = expression();
      t = ts.get();
      if (t.kind != ')') error("primary(): ')' 가 없습니다.");
      return lval;
    } 
    case '8':              // 숫자는 '8' 로 표현
      return t.value;
    case '!': case '~': case '-': {  // not, complement, minus
      ts.putback(t);       // 스트림에 다시 넣기
      return t.value;
    }
    case 'e':              // 종료
      exit(0);
    default:
      error("primary(): 잘못된 요소입니다.");
      exit(-1);
    }
  }
}
int minus_term() {        // 마이너스 처리
  int lval = primary();
  Token t = ts.get();
  while (1) {
    switch (t.kind) {
    case '-':
      lval = -primary();
      t = ts.get();
      break;
    default:
      ts.putback(t);
      return lval;
    }
  }
}
int complement_term() {    // ~ complement 연산자 처리
  int lval = minus_term();
  Token t = ts.get();      // 토큰 가져오기
  while (1) {
    switch (t.kind) {
    case '~':
      lval = ~minus_term();
      t = ts.get();
      break;
    default:
      ts.putback(t);
      return lval;
    }
  }
}
int not_term() {           // ! not 연산자 처리
  int lval = complement_term();
  Token t = ts.get();
  while (1) {
    switch (t.kind) {
    case '!':
      lval = !complement_term();
      t = ts.get();
      break;
    default:
      ts.putback(t);
      return lval;
    }
  }
}
int shift_term() {         // <<, >> shift 연산자 처리
  int lval = not_term();
  Token t = ts.get();
  while (1) {
    switch (t.kind) {
    case '<':
      lval = lval << not_term();
      t = ts.get();
      break;
    case '>':
      lval = lval >> not_term();
      t = ts.get();
      break;
    default:
      ts.putback(t);
      return lval;
    }
  }
}
int and_term() {           // & and 연산자 처리
  int lval = shift_term();
  Token t = ts.get();
  while (1) {
    switch (t.kind) {
    case '&':
      lval = lval & shift_term();
      t = ts.get();
      break;
    default:
      ts.putback(t);
      return lval;
    }
  }
}
int xor_term() {           // ^ xor 연산자 처리
  int lval = and_term();
  Token t = ts.get();
  while (1) {
    switch (t.kind) {
    case '^':
      lval = lval ^ and_term();
      t = ts.get();
      break;
    default:
      ts.putback(t);
      return lval;
    }
  }
}
int or_term() {           // | or 연산자 처리
  int lval = xor_term();
  Token t = ts.get();
  while (1) {
    switch (t.kind) {
    case '|':
      lval = lval | xor_term();
      t = ts.get();
      break;
    default:
      ts.putback(t);
      return lval;
    }
  }
}
int expression() {
  int lval = or_term();
  return lval;
}

/////////////////////////////////////////////////////////////////////

int main() {
  try {
    std::cout << "PPP3 Chapter 5, 연습문제 5, 비트 논리 표현식을 위한 문법\n"
              << "계산하고 싶은 식을 입력하세요. 결과: =, 종료: e" << std::endl;
    int val = 0;
    while (std::cin) {
      Token t = ts.get();
      if (t.kind == 'e') break;
      if (t.kind == '=') {
        std::cout << "결과 = " << val << '\n';
      } else {
        ts.putback(t);
      }
      val = expression();
    }
    return 0;
  } catch (std::exception& e) {
    std::cerr << "에러: " << e.what() << '\n';
    return -1;
  } catch (...) {
    std::cerr << "예외\n";
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
void error(std::string s1, std::string s2) {
  throw std::runtime_error{s1+s2};
}
