#include "../inlude/Cart.h"
#include "../inlude/perishableproduct.h"
#include <iomanip>
#include <iostream>
Cart::Cart() = default;
void Cart::additem(shared_ptr<Product> product, int quantity) {
    if (quantity <= 0) {
        throw invalid_argument("Quantity must be positive.");
    }
    if (product->getquantity() < quantity) {
        throw runtime_error("Not enough stock for " + product->getname() + ". Available: " + to_string(product->getquantity()));
    }
    bool found = false;
    for (auto& item : items) {
        if (item.first->getname() == product->getname()) {
            item.second += quantity;
            found = true;
            break;
        }
    }
    if (!found) {
        items[product] = quantity;
    }
}
void Cart::removeitem(shared_ptr<Product> product, int quantity) {
    if (quantity <= 0) {
        throw invalid_argument("Quantity to remove must be positive.");
    }
    bool found = false;
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->first->getname() == product->getname()) {
            found = true;
            if (it->second <= quantity) {
                items.erase(it);
            } else {
                it->second -= quantity;
            }
            break;
        }
    }
    if (!found) {
        throw runtime_error("Product not found in cart: " + product->getname());
    }
}
double Cart::gettotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.first->getprice() * item.second;
    }
    return total;
}
bool Cart::isempty() const {
    return items.empty();
}
const map<shared_ptr<Product>, int>& Cart::getcontents() const {
    return items;
}
void Cart::checkout() {
    if (isempty()) {
        throw runtime_error("Cannot checkout, cart is empty.");
    }
    cout << "\n--- Processing Checkout ---" << endl;
    bool hasExpiredItems = false;
    double totalWeightGrams = 0.0;
    const double shippingCost = 30.00;
    for (const auto& item : items) {
        auto product = item.first;
        int quantityInCart = item.second;
        totalWeightGrams += product->getweightperunit() * quantityInCart;
        auto perishable = dynamic_pointer_cast<Perishableproduct>(product);
        if (perishable && perishable->isexpired()) {
            cout << "  WARNING: " << product->getname() << " is expired and will be checked out." << endl;
            hasExpiredItems = true;
        }
    }
    cout << "\n** Shipment notice **" << endl;
    for (const auto& item : items) {
        auto product = item.first;
        int quantityInCart = item.second;
        cout << fixed << setprecision(0) << quantityInCart << "x "
                  << product->getname() << " " << product->getweightperunit() << "g" << endl;
    }
    cout << fixed << setprecision(1) << "Total package weight " << totalWeightGrams / 1000.0 << "kg" << endl;
    cout << "\n** Checkout receipt **" << endl;
    for (const auto& item : items) {
        auto product = item.first;
        int quantityInCart = item.second;
        cout << fixed << setprecision(0) << quantityInCart << "x "
                  << product->getname() << " " << fixed << setprecision(2) << product->getprice() * quantityInCart << endl;
    }
    cout << "--------------------" << endl;
    double subtotal = gettotal();
    double finalAmount = subtotal + shippingCost;
    cout << "Subtotal          $" << fixed << setprecision(2) << subtotal << endl;
    cout << "Shipping          $" << fixed << setprecision(2) << shippingCost << endl;
    cout << "Amount            $" << fixed << setprecision(2) << finalAmount << endl;
    for (const auto& item : items) {
        auto product = item.first;
        int quantityInCart = item.second;
    }
    items.clear();
    cout << "Checkout complete! Your cart is now empty." << endl;
    if (hasExpiredItems) {
        cout << "Please note: Some expired items were included in this checkout." << endl;
    }
}