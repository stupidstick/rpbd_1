#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>


class Product {
public:
    long get_id() const;

    void set_id(long id);

    std::string get_name() const;

    void set_name(const std::string &name);

    long get_caloric_content() const;

    void set_caloric_content(long caloric_content);

    long get_weight() const;

    void set_weight(long weight);

    double get_price() const;

    void set_price(double price);

private:
    long id;
    std::string name;
    long caloricContent;
    long weight;
    double price;
};



#endif //PRODUCT_H
