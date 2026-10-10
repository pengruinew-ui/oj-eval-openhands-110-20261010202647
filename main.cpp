#include <iostream>
#include <cstdlib>
using namespace std;

class Date {
private:
    int _year, _month, _day;
    static bool isLeap(int y) {
        return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    }
    static int monthDays(int y, int m) {
        static const int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2 && isLeap(y)) return 29;
        return mdays[m];
    }
    bool valid(int y, int m, int d) const {
        if (y < 1900 || y > 2030) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > monthDays(y,m)) return false;
        return true;
    }
    void normalize() {
        // ensure date is within range after operations
        while (true) {
            int md = monthDays(_year, _month);
            if (_day > md) {
                _day -= md;
                _month++;
                if (_month > 12) { _month = 1; _year++; }
                continue;
            }
            if (_day < 1) {
                _month--;
                if (_month < 1) { _month = 12; _year--; }
                _day += monthDays(_year, _month);
                continue;
            }
            break;
        }
    }
public:
    Date(): _year(1900), _month(1), _day(1) {}
    Date(int y, int m, int d) {
        if (valid(y,m,d)) { _year=y; _month=m; _day=d; }
        else { _year=1900; _month=1; _day=1; }
    }
    // prefix ++
    Date& operator++() {
        _day++;
        normalize();
        return *this;
    }
    // postfix ++
    Date operator++(int) {
        Date tmp = *this;
        ++(*this);
        return tmp;
    }
    // prefix --
    Date& operator--() {
        _day--;
        normalize();
        return *this;
    }
    // postfix --
    Date operator--(int) {
        Date tmp = *this;
        --(*this);
        return tmp;
    }
    // addition of days
    Date operator+(int days) const {
        Date res = *this;
        res._day += days;
        res.normalize();
        return res;
    }
    // subtraction of days
    Date operator-(int days) const {
        Date res = *this;
        res._day -= days;
        res.normalize();
        return res;
    }
    // difference between dates (absolute days)
    static long long toOrdinal(const Date& d) {
        long long days = 0;
        for (int y = 1900; y < d._year; ++y) {
            days += isLeap(y) ? 366 : 365;
        }
        for (int m = 1; m < d._month; ++m) {
            days += monthDays(d._year, m);
        }
        days += d._day - 1;
        return days;
    }
    int operator-(const Date& other) const {
        long long a = toOrdinal(*this);
        long long b = toOrdinal(other);
        long long diff = (a > b) ? (a - b) : (b - a);
        return static_cast<int>(diff);
    }
    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }
    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << "-" << d._month << "-" << d._day;
        return os;
    }
    void out() const {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

void Test() {
    int op;
    if(!(cin>>op)) return;
    int yy, mm, dd;
    if (op == 1 || op == 0) {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main(){
    Test();
    return 0;
}
