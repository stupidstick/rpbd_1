#include <iostream>
#include <string>

using namespace std;

class DishType {
public:

    DishType(long long id, string name) : id(id), name(move(name)) {
    }

    long long getId() const {
        return id;
    }

    void setId(long long id) {
        this->id = id;
    }

    [[nodiscard]] string getName() const {
        return name;
    }

    void setName(const string &name) {
        this->name = name;
    }

    void display() const {
        cout << "Dish Type ID: " << id << ", Name: " << name << endl;
    }

private:
    long long id;
    string name;
};
