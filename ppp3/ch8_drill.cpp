/*
  Programming: Principles and Practice using C++ (3rd edition), 2024 - Bjarne Stroustrup
  
  8. Technicalities: Classes, etc.
  
  Drill

  2024/12/20

  This program is expressed a date in C++.

  Leap years are ignored.

  if exceed month or day, adding next year or month.
  ex) 2022/2/28 => next, 2022/3/1
      2022/12/31 => next, 2023/1/1

  year / month / day.
  date are valid 0/1/1 ~ INT_MAX(2147483647)/12/31.
*/

#include <iostream>
#include "ppp_copy.h"

namespace chr {  // chrono
  struct year {
    int y;
  };
  enum class month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
  };
  class date {
  public:
    date(year yy, month mm, int dd) : y{yy}, m{mm}, d{dd} { }

    year ret_year()   const { return y; }
    month ret_month() const { return m; }
    int ret_day()     const { return d; }

    void add_day();
    void add_month();
    void add_year();
  private:
    year y;
    month m;
    int d;
  };

  int to_int(month m) { return static_cast<int>(m); }

  bool is_valid(const date& dd)
  {
    if (dd.ret_year().y > 0 && dd.ret_year().y <= 2147483647 && to_int(dd.ret_month()) > 0 && to_int(dd.ret_month()) < 13 && dd.ret_day() > 0)
    {
      switch (dd.ret_month()) {
      case month::jan: case month::mar: case month::may: case month::jul: case month::aug: case month::oct: case month::dec: {
        if (dd.ret_day() > 31)
          return false;
        return true;
      }
      case month::apr: case month::jun: case month::sep: case month::nov: {
        if (dd.ret_day() > 30) 
          return false;
        return true;
      }
      case month::feb: {
        if (dd.ret_day() > 28)
          return false;
        return true;
      }
      }
    }
    return false;
  }

  void date::add_day()
  {
    ++d;
    switch (m) {
    case month::jan: case month::mar: case month::may: case month::jul: case month::aug: case month::oct: case month::dec: {
      if (d > 31) {
        d = 1;
        add_month();
      }
      break;
    }
    case month::apr: case month::jun: case month::sep: case month::nov: {
      if (d > 30) {
        d = 1;
        add_month();
      }
      break;
    }
    case month::feb: {
      if (d > 28) {
        d = 1;
        add_month();
      }
      break;
    }
    }
  }
  void date::add_month()
  {
    //m = (m == month::dec) ? month::jan : (month {to_int(m) + 1});
    if (m == month::dec) {
      m = month::jan;
      add_year();
    }
    else {
      m = month {to_int(m) + 1};
    }
  }
  void date::add_year()
  {
    if (y.y < 2147483647) {
      ++y.y;
    }
    else {
      ppp3::error("chr::date::add_year: valid years are 2147483647.");
    }
  }  

  std::ostream& operator<<(std::ostream& os, chr::date& dd)
  {
    // operator overloading, print date.
    return os << dd.ret_year().y << '/' << to_int(dd.ret_month()) << '/' << dd.ret_day();
  }



/////////////////////////////////////////////////////////////////////////////////
/********************************** Test ***************************************/
/////////////////////////////////////////////////////////////////////////////////
  void calculate_date()
  {
    chr::date today { chr::year{2020}, chr::month::feb, 2 };
    if (chr::is_valid(today)) {
      chr::date tomorrow = today;
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();
      tomorrow.add_day();  // 2/28
      tomorrow.add_day();  // 3/1, 윤년 무시
      std::cout << "today: " << today << '\n'
                << "tomorrow: " << tomorrow << '\n';

      tomorrow.add_month();
      tomorrow.add_month();
      tomorrow.add_month();
      tomorrow.add_month();
      tomorrow.add_month();
      tomorrow.add_month();
      tomorrow.add_month();
      tomorrow.add_month();
      tomorrow.add_month();  // 2020/12/1
      tomorrow.add_month();  // 2021/1/1
      std::cout << "today: " << today << '\n'
                << "tomorrow: " << tomorrow << '\n';

      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();
      tomorrow.add_year();  // 2041/1/1
      std::cout << "today: " << today << '\n'
                << "tomorrow: " << tomorrow << '\n';

      chr::date date_2099_12_31 {chr::year{2099}, chr::month::dec, 31};
      std::cout << "result: " << date_2099_12_31 << '\n';
      date_2099_12_31.add_day();
      std::cout << "result: " << date_2099_12_31 << '\n';

      chr::date last_date {chr::year{2147483647}, chr::month::dec, 31};
      std::cout << "LAST: " << last_date << '\n';
      //last_date.add_day();
      //std::cout << "LAST(?): " << last_date << '\n';
    }
    else {
      ppp3::error("chr::is_valid: unable date.");
    }
  }
/////////////////////////////////////////////////////////////////////////////////
/******************************** Test area ************************************/
/////////////////////////////////////////////////////////////////////////////////
}

int main()
{
  try {
    chr::calculate_date();
    return 0;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return -1;
  }
  catch (...) {
    std::cerr << "exception." << '\n';
    return -2;
  }
}
