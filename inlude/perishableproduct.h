#include "../inlude/product.h"
#include "../inlude/expirable.h"
#include <ctime>
using namespace std;
class Perishableproduct : public Product, public Expirable {
    int expirydate;
public:
    Perishableproduct(const std::string& name, double price, int quantity, double weight_per_unit, int expirationdate);
    bool isexpired() const override;
};
