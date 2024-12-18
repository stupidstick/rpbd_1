//
// Created by stupi on 03.11.2024.
//

#ifndef DISHTOPRODUCT_H
#define DISHTOPRODUCT_H

class DishToProduct {
public:
    long get_id1() const;

    void set_id(long id);

    long get_dish_id1() const;

    void set_dish_id(long dish_id);

    long get_product_id1() const;

    void set_product_id(long product_id);

    long get_id() const;

    long get_dish_id() const;

    long get_product_id() const;

    long get_products_count() const;

    void set_products_count(long products_count);

private:
    long id;
    long dishId;
    long productId;
    long productsCount;
};


#endif //DISHTOPRODUCT_H
