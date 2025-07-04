#include "../inlude/product.h"
Product::Product(const std::string& name, double price, int quantity, double weight_per_unit)
    : name(name), price(price), quantity(quantity), weight_per_unit(weight_per_unit) {}
const std::string& Product::getname() const {
    return name;
}
double Product::getprice() const {
    return price;
}
int Product::getquantity() const {
    return quantity;
}
double Product::getweightperunit() const {
    return weight_per_unit;
}
void Product::reducequantity(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("Amount to reduce cannot be negative");
    }
    if (amount > quantity) {
        throw std::runtime_error("Cannot reduce more than available quantity");
    }
    quantity -= amount;
}