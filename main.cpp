#include <iostream>
#include <memory>
#include <iomanip>
#include "inlude/product.h"
#include "inlude/perishableproduct.h"
#include "inlude/cart.h"
#include "checkout.h"
using namespace std;
int main() {
    try {
        auto apple = std::make_shared<Product>("Apple", 1.50, 100, 150.0);
        auto banana = std::make_shared<Product>("Banana", 0.75, 50, 120.0);
        Cart cart;
        cart.additem(apple, 2);
        cart.additem(banana, 1);
        cart.checkout();

    } catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
        return 1;
    }
    return 0;
}