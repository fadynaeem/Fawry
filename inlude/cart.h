#ifndef CART_H
#define CART_H
#include "Product.h"
#include <map>
#include <memory>
using namespace std;
class Cart {
private:
    map<shared_ptr<Product>, int> items;
public:
    Cart();
    void additem(shared_ptr<Product> product, int quantity);
    void removeitem(shared_ptr<Product> product, int quantity);
    double gettotal() const;
    bool isempty() const;
    const map<shared_ptr<Product>, int>& getcontents() const;
    void checkout();
};
#endif