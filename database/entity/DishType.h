#ifndef DISHTYPE_H
#define DISHTYPE_H
#include <string>

class DishType {
public:
    long get_id() const;

    void set_id(long id);

    std::string get_name() const;

    void set_name(const std::string &name);

private:
    long id;
    std::string name;
};


#endif //DISHTYPE_H
