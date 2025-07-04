
#pragma once
#include <string>
#include <stdexcept>
class Product {
private:
    std::string name;
    double price;
    int quantity;
    double weight_per_unit;
public:
    Product(const std::string& name, double price, int quantity, double weight_per_unit);
    virtual ~Product() = default;
    const std::string& getname() const;
    double getprice() const;
    int getquantity() const;
    double getweightperunit() const;
    void reducequantity(int amount);
};