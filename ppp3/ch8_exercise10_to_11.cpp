/*
  Programming: Principles and Practice using C++ (3rd edition), 2024 - Bjarne Stroustrup
  
  8. Technicalities: Classes, etc.
  
  Drill

  2024/12/20
  2024/12/23, add leapyear.
              add zeller's congruence.
              add work_day(mon, tue, wed, thu, fri)

  This program is expressed a date in C++.

  Leap years are ignored. => 24/12/23 update, add leapyear.

  if exceed month or day, adding next year or month.
  ex) 2022/2/28 => next, 2022/3/1
      2022/12/31 => next, 2023/1/1

  year / month / day.
  date are valid 1/1/1 ~ INT_MAX(2147483647)/12/31.
*/

#include <iostream>
#include "ppp_copy.h"

namespace chr {  // chrono
  class date;
  bool is_valid(date& dd);

  struct year {
    int y;
  };
  enum class month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
  };
  enum class days {
    sun = 1, mon = 2, tue = 3, wed = 4, thu = 5, fri = 6, sat = 0
  };
  class date {
  public:
    date(year yy, month mm, int dd) : y{yy}, m{mm}, d{dd} 
    { 
      if (!is_valid(*this)) {
        std::cout << "unable date, reset 2020/1/1.\n";
        y.y = 2020;
        m = month::jan;
        d = 1;
        day = days::wed;
      }
      else {
        day = zeller_cgrc();
      }
    }

    year ret_year()   const { return y; }
    month ret_month() const { return m; }
    int ret_day()     const { return d; }
    std::string what_days() const;

    void add_day();
    void add_month();
    void add_year();

    days zeller_cgrc();

    void next_workday();
  private:
    year y;
    month m;
    int d;
    days day;
  };

  int leapyear(date& dd);
  int to_int(month m);
  std::ostream& operator<<(std::ostream& os, chr::date& dd);
  
/////////////////////////////////////////////////////////////////////////////////
/********************************** Test ***************************************/
// you implement to main.cpp.
/////////////////////////////////////////////////////////////////////////////////
  void calculate_date();
/////////////////////////////////////////////////////////////////////////////////
/******************************** Test area ************************************/
/////////////////////////////////////////////////////////////////////////////////
}

int chr::leapyear(date& dd)
{
  if (dd.ret_year().y % 100 == 0) {
    if (dd.ret_year().y % 400 == 0) {
      return 29;
    }
    else {
      return 28;
    }
  }
  else if (dd.ret_year().y % 4 == 0) {
    return 29;
  }
  return 28;
}
int chr::to_int(month m) { return static_cast<int>(m); }

bool chr::is_valid(date& dd)
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
      if (dd.ret_day() > leapyear(dd))
        return false;
      return true;
    }
    }
  }
  return false;
}

void chr::date::add_day()
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
    if (d > leapyear(*this)) {
      d = 1;
      add_month();
    }
    break;
  }
  }
  day = zeller_cgrc();
}
void chr::date::add_month()
{
  //m = (m == month::dec) ? month::jan : (month {to_int(m) + 1});
  if (m == month::dec) {
    m = month::jan;
    add_year();
  }
  else {
    m = month {to_int(m) + 1};
  }
  day = zeller_cgrc();
}
void chr::date::add_year()
{
  if (y.y < 2147483647) {
    ++y.y;
    day = zeller_cgrc();
  }
  else {
    ppp3::error("chr::date::add_year: valid years are 2147483647.");
  }
}  

std::ostream& chr::operator<<(std::ostream& os, chr::date& dd)
{
  // operator overloading, print date.
  return os << dd.ret_year().y << '/' << to_int(dd.ret_month()) << '/' << dd.ret_day() << ", " << dd.what_days();
}

chr::days chr::date::zeller_cgrc()
{
  int dy = d;
  int mn = to_int(m);
  if (mn == 1) {
    dy -= 1;
    mn = 13;
  }
  else if (mn == 2) {
    dy -= 1;
    mn = 14;
  }
  int k = y.y % 100;
  int j = y.y / 100;

  return days { (dy + ((mn+1)*26)/10 + k + (k/4) + (j/4) -(2*j)) % 7 };
}

std::string chr::date::what_days() const
{
  switch (day) {
  case chr::days::sun:
    return "sunday";
  case chr::days::mon:
    return "monday";
  case chr::days::tue:
    return "tuesday";
  case chr::days::wed:
    return "wednesday";
  case chr::days::thu:
    return "thursday";
  case chr::days::fri:
    return "friday";
  case chr::days::sat:
    return "saturday";
  }
  return "";
}

void chr::date::next_workday()
{
  switch (day) {
  case chr::days::sun: case chr::days::mon: case chr::days::tue: case chr::days::wed: case chr::days::thu: {
    add_day();
    day = zeller_cgrc();
    break;
  }
  case chr::days::fri: {
    add_day();
    add_day();
    add_day();
    day = zeller_cgrc();
    break;
  }
  case chr::days::sat: {
    add_day();
    add_day();
    day = zeller_cgrc();
    break;
  }
  }
}

void chr::calculate_date()
{
  chr::date today { chr::year{2024}, chr::month::dec, 20 };
  std::cout << today << '\n';

  today.next_workday();
  std::cout << today << '\n';

  today.add_day();
  std::cout << today << '\n';
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
