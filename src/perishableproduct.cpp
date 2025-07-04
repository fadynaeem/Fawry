#include "../inlude/perishableproduct.h"
#include "../inlude/product.h"
#include <ctime>
using namespace std;
Perishableproduct::Perishableproduct(const string& name, double price, int quantity, double weight_per_unit, int expirationdate)
    : Product(name, price, quantity, weight_per_unit) {}
bool Perishableproduct::isexpired() const {
    time_t now = time(nullptr);
    tm today = *localtime(&now);
    int currentdate = (today.tm_year + 1900) * 10000
                    + (today.tm_mon + 1) * 100
                    +  today.tm_mday;
    return currentdate > expirydate;
}
