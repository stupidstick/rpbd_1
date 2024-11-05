//
// Created by stupi on 04.11.2024.
//

#include "Menu.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ostream>
#include <set>

#define ITEMS_PER_PAGE 20

using namespace std;

void printEnterAction() {
    cout << "Enter action: ";
}

Menu::Menu() {
    this->odbcTemplate = new OdbcTemplate();
    this->cookGateway = new CookGateway(odbcTemplate);
    this->dishCookingGateway = new DishCookingGateway(odbcTemplate);
    this->dishGateway = new DishGateway(odbcTemplate);
    this->dishToProductGateway = new DishToProductGateway(odbcTemplate);
    this->dishTypeGateway = new DishTypeGateway(odbcTemplate);
    this->healthCertGateway = new HealthCertGateway(odbcTemplate);
    this->passportGateway = new PassportGateway(odbcTemplate);
    this->productGateway = new ProductGateway(odbcTemplate);
    this->recipeGateway = new RecipeGateway(odbcTemplate);
}

Menu::~Menu() {
    delete this->cookGateway;
    delete this->dishCookingGateway;
    delete this->dishGateway;
    delete this->dishToProductGateway;
    delete this->dishTypeGateway;
    delete this->dishToProductGateway;
    delete this->dishTypeGateway;
    delete this->healthCertGateway;
    delete this->passportGateway;
    delete this->productGateway;
    delete this->recipeGateway;
    delete this->odbcTemplate;
}

void Menu::run() {
    while (true) {
        cout << "Main menu" << endl;
        cout << "1. Dish type menu" << endl;
        cout << "2. Dish menu" << endl;
        cout << "3. Recipe menu" << endl;
        cout << "4. Products menu" << endl;
        cout << "0. Exit" << endl;
        printEnterAction();
        int action = readAction();
        switch (action) {
            case 1: {
                runDishTypeMenu();
                break;
            }
            case 2: {
                runDishMenu();
                break;
            }
            case 3: {
                runProductsMenu();
            }
            case 0: {
                return;
            }
        }
    }
}

int Menu::readAction() {
    int v;
    while (true) {
        cin >> v;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
        } else {
            return v;
        }
    }
}

void Menu::runDishTypeMenu() {
    while (true) {
        cout << "Dish type menu" << endl;
        cout << "1. Insert dish type" << endl;
        cout << "2. Delete dish type" << endl;
        cout << "3. Update dish type" << endl;
        cout << "4. Print all dish types" << endl;
        cout << "0. Exit" << endl;
        printEnterAction();

        switch (readAction()) {
            case 1: {
                cout << "Enter dish type: ";
                string name;
                getline(cin >> ws, name);
                dishTypeGateway->insert(name);
                break;
            }
            case 2: {
                cout << "Delete dish type" << endl;
                vector<DishType> dishTypes = dishTypeGateway->findAll();
                cout << left << setw(10) << "N" << setw(20) << "Dish type" << endl;
                paginate(dishTypes.size(), [dishTypes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishTypes[i].get_name() << endl;
                });

                int n;
                cout << "Enter dish N to remove: ";
                cin >> n;
                if (n <= 0 || n > dishTypes.size()) {
                    cout << "Invalid dish number" << endl;
                    break;
                }
                dishTypeGateway->remove(dishTypes[n - 1].get_id());
                break;
            }
            case 3: {
                cout << "Update dish type" << endl;
                vector<DishType> dishTypes = dishTypeGateway->findAll();
                cout << left << setw(10) << "N" << setw(20) << "Dish type" << endl;
                paginate(dishTypes.size(), [dishTypes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishTypes[i].get_name() << endl;
                });

                int n;
                cout << "Enter dish N to update: ";
                cin >> n;
                if (n <= 0 || n > dishTypes.size()) {
                    cout << "Invalid dish number" << endl;
                    break;
                }

                cout << "Old dish type: " << dishTypes[n - 1].get_id() << endl;
                cout << "Enter new dish type: ";
                string name;
                getline(cin >> ws, name);
                dishTypeGateway->update(dishTypes[n - 1].get_id(), name);
                break;
            }
            case 4: {
                cout << "All dish types:" << endl;
                cout << left << setw(10) << "N" << setw(20) << "Dish type" << endl;
                vector<DishType> dishTypes = dishTypeGateway->findAll();
                paginate(dishTypes.size(), [dishTypes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishTypes[i].get_name() << endl;
                });
                break;
            }
            case 0: {
                return;
            }
        }
    }
}

void Menu::runDishMenu() {
    while (true) {
        cout << "Dish menu" << endl;
        cout << "1. Insert dish" << endl;
        cout << "2. Delete dish" << endl;
        cout << "3. Update dish" << endl;
        cout << "4. Print all dishes" << endl;
        cout << "0. Exit" << endl;
        printEnterAction();

        switch (readAction()) {
            case 1: {
                vector<DishType> dishTypes = dishTypeGateway->findAll();
                if (dishTypes.empty()) {
                    cout << "Add the food types first." << endl;
                    break;
                }
                vector<Product> products = productGateway->findAll();
                if (products.empty()) {
                    cout << "Add products first" << endl;
                }

                cout << "Enter dish name: ";
                string name;
                getline(cin >> ws, name);

                cout << "Enter dish weight (g)";
                long dishWeight;
                cin >> dishWeight;

                cout << "Enter dish image url: " << endl;
                string imageUrl;
                getline(cin >> ws, imageUrl);

                cout << "Dish types:" << endl;
                cout << left << setw(10) << "N" << setw(20) << "Dish type" << endl;
                paginate(dishTypes.size(), [dishTypes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishTypes[i].get_name() << endl;
                });

                int dishTypeN;
                cout << "Enter dish type N: ";
                cin >> dishTypeN;
                if (dishTypeN <= 0 || dishTypeN > dishTypes.size()) {
                    cout << "Invalid dish type number" << endl;
                    break;
                }

                cout << "Products: " << endl;
                cout << left << setw(10) << "N" << setw(20) << "Product" << endl;
                paginate(products.size(), [products](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << products[i].get_name() << endl;
                });

                vector<Product> productsToAdd = vector<Product>();
                int productN;
                cout << "Enter product N or -1 to stop" << endl;
                while (true) {
                    cin >> productN;
                    if (productN == -1) {
                        break;
                    }
                    productsToAdd.push_back(products[productN]);
                }
                if (productsToAdd.empty()) {
                    cout << "Products is empty" << endl;
                    break;
                }


                Dish dish = dishGateway->insert(name, dishWeight, imageUrl, dishTypes[dishTypeN - 1].get_id());
                for (int i = 0; i < productsToAdd.size(); i++) {
                    dishToProductGateway->insert(dish.get_id(), productsToAdd[i].get_id());
                }

                cout << "Dish: name = " << dish.get_name() << ", weight: " << dishWeight << ", image url: " << imageUrl
                        << ", type: " << dishTypes[dishTypeN - 1].get_name() << endl;
                break;
            }
            case 2: {
                cout << "Delete dish" << endl;
                vector<Dish> dishes = dishGateway->findAll();
                cout << left << setw(10) << "N" << setw(20) << "Dish" << endl;
                paginate(dishes.size(), [dishes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishes[i].get_name() << endl;
                });

                int n;
                cout << "Enter dish N to remove: ";
                cin >> n;
                if (n <= 0 || n > dishes.size()) {
                    cout << "Invalid dish N" << endl;
                    break;
                }

                vector<DishToProduct> dishToProducts = dishToProductGateway->findAll();
                for (auto dishToProduct: dishToProducts) {
                    if (dishToProduct.get_dish_id() == dishes[n - 1].get_id()) {
                        dishToProductGateway->remove(dishToProduct.get_id());
                    }
                }

                dishGateway->remove(dishes[n - 1].get_id());
                break;
            }
            case 3: {
                vector<DishType> dishTypes = dishTypeGateway->findAll();
                if (dishTypes.empty()) {
                    cout << "Add the food types first." << endl;
                    break;
                }
                vector<Product> products = productGateway->findAll();
                if (products.empty()) {
                    cout << "Add products first";
                    break;
                }

                cout << "Update dish" << endl;
                vector<Dish> dishes = dishGateway->findAll();
                cout << left << setw(10) << "N" << setw(20) << "Dish" << endl;
                paginate(dishes.size(), [dishes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishes[i].get_name() << endl;
                });

                int n;
                cout << "Enter dish N to update: ";
                cin >> n;
                if (n <= 0 || n > dishes.size()) {
                    cout << "Invalid dish N" << endl;
                    break;
                }

                string name, imageUrl;
                long weight;

                cout << "Enter new dish name: ";
                getline(cin >> ws, name);

                cout << "Enter new dish weight (in grams): ";
                cin >> weight;

                cout << "Enter new image URL: ";
                getline(cin >> ws, imageUrl);

                cout << "Dish types:" << endl;
                cout << left << setw(10) << "N" << setw(20) << "Dish type" << endl;
                paginate(dishTypes.size(), [dishTypes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishTypes[i].get_name() << endl;
                });

                int dishTypeN;
                cout << "Enter dish type N: ";
                cin >> dishTypeN;
                if (dishTypeN <= 0 || dishTypeN > dishTypes.size()) {
                    cout << "Invalid dish type number" << endl;
                    break;
                }

                vector<Product> productsToAdd = vector<Product>();
                int productN;
                cout << "Enter product N or -1 to stop" << endl;
                while (true) {
                    cin >> productN;
                    if (productN == -1) {
                        break;
                    }
                    productsToAdd.push_back(products[productN]);
                }
                if (productsToAdd.empty()) {
                    cout << "Products is empty" << endl;
                    break;
                }

                vector<DishToProduct> dishToProducts = dishToProductGateway->findAll();
                for (auto dishToProduct: dishToProducts) {
                    if (dishToProduct.get_dish_id() == dishes[n - 1].get_id()) {
                        dishToProductGateway->remove(dishToProduct.get_id());
                    }
                }

                for (auto product: productsToAdd) {
                    dishToProductGateway->insert(dishes[n - 1].get_id(), product.get_id());
                }
                dishGateway->update(dishes[n - 1].get_id(), name, weight, imageUrl, dishTypes[dishTypeN - 1].get_id());
            }
            case 4: {
                cout << "All dishes:" << endl;
                cout << left << setw(10) << "N" << setw(20) << "Dish" << setw(20) << "Dish type" << setw(20) <<
                        "Products" << endl;
                vector<Dish> dishes = dishGateway->findAll();
                vector<DishToProduct> dishesToProducts = dishToProductGateway->findAll();
                vector<Product> products = productGateway->findAll();

                paginate(dishes.size(), [dishes, dishesToProducts, products](int i) {
                    auto currentDish = dishes[i];

                    cout << left << setw(10) << i + 1 << setw(20) << currentDish.get_name() << setw(20) << endl;
                    for (auto dishToProduct: dishesToProducts) {
                        if (dishToProduct.get_dish_id() == currentDish.get_id()) {
                            for (auto product: products) {
                                if (product.get_id() == dishToProduct.get_product_id()) {
                                    cout << product.get_name() << " ";
                                }
                            }
                        }
                    }
                });
                break;
            }
            case 0: {
                return;
            }
        }
    }
}

void Menu::runRecipeMenu() {
    while (true) {
        cout << "Dish menu" << endl;
        cout << "1. Insert recipe" << endl;
        cout << "2. Delete recipe" << endl;
        cout << "3. Update recipe" << endl;
        cout << "4. Print all recipes" << endl;
        cout << "0. Exit" << endl;
        printEnterAction();

        switch (readAction()) {
            case 1: {
                vector<Dish> dishes = dishGateway->findAll();
                if (dishes.empty()) {
                    cout << "Add dishes first";
                }

                cout << "Dishes:" << endl;
                cout << left << setw(10) << "N" << setw(20) << "Dish" << endl;
                paginate(dishes.size(), [dishes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishes[i].get_name() << endl;
                });

                int dishN;
                cout << "Enter dish type N: ";
                cin >> dishN;
                if (dishN <= 0 || dishN > dishes.size()) {
                    cout << "Invalid dish number" << endl;
                    break;
                }
                Dish dish = dishes[dishN - 1];

                long cookingTime;
                cout << "Enter cooking time: " << endl;
                cin >> cookingTime;
                if (cookingTime <= 0) {
                    cout << "Invalid cooking time" << endl;
                    break;
                }

                string cookingTechnology;
                cout << "Enter cooking technology: ";
                getline(cin >> ws, cookingTechnology);

                recipeGateway->insert(cookingTime, cookingTechnology, dish.get_id());

                break;
            }
            case 2: {
                vector<Recipe> recipes = recipeGateway->findAll();
                vector<Dish> dishes = dishGateway->findAll();

                cout << "Recipes: " << endl;
                cout << left << setw(10) << "N" << setw(20) << "Cooking time" << setw(20) << "Cooking technology" <<
                        setw(20) << "Dish" << endl;
                paginate(recipes.size(), [recipes, dishes](int i) {
                    Recipe currentRecipe = recipes[i];
                    cout << left << setw(10) << i + 1 << setw(20) << currentRecipe.get_cooking_time() << setw(20) <<
                            currentRecipe.get_cooking_technology() << setw(20);
                    for (auto dish: dishes) {
                        if (dish.get_id() == currentRecipe.get_dish_id()) {
                            cout << dish.get_name() << endl;
                            break;
                        }
                    }
                });

                int recipeN;
                cout << "Enter recipe type N: ";
                cin >> recipeN;
                if (recipeN <= 0 || recipeN > recipes.size()) {
                    cout << "Invalid recipe number" << endl;
                    break;
                }
                Recipe recipe = recipes[recipeN - 1];
                recipeGateway->remove(recipe.get_id());
                break;
            }
            case 3: {
                vector<Dish> dishes = dishGateway->findAll();
                vector<Recipe> recipes = recipeGateway->findAll();
                cout << "Recipes: " << endl;
                cout << left << setw(10) << "N" << setw(20) << "Cooking time" << setw(20) << "Cooking technology" <<
                        setw(20) << "Dish" << endl;
                paginate(recipes.size(), [recipes, this](int i) {
                    Recipe currentRecipe = recipes[i];
                    cout << left << setw(10) << i + 1 << setw(20) << currentRecipe.get_cooking_time() << setw(20) <<
                            currentRecipe.get_cooking_technology() << setw(20) << dishGateway->findById(
                                currentRecipe.get_dish_id())->get_name();
                });

                int recipeN;
                cout << "Enter recipe type N: ";
                cin >> recipeN;
                if (recipeN <= 0 || recipeN > recipes.size()) {
                    cout << "Invalid recipe number" << endl;
                    break;
                }
                Recipe recipe = recipes[recipeN - 1];

                long cookingTime;
                cout << "Enter cooking time: " << endl;
                cin >> cookingTime;
                if (cookingTime <= 0) {
                    cout << "Invalid cooking time" << endl;
                    break;
                }

                string cookingTechnology;
                cout << "Enter cooking technology: ";
                getline(cin >> ws, cookingTechnology);

                cout << "Dishes:" << endl;
                cout << left << setw(10) << "N" << setw(20) << "Dish" << endl;
                paginate(dishes.size(), [dishes](int i) {
                    cout << left << setw(10) << i + 1 << setw(20) << dishes[i].get_name() << endl;
                });

                int dishN;
                cout << "Enter dish type N: ";
                cin >> dishN;
                if (dishN <= 0 || dishN > dishes.size()) {
                    cout << "Invalid dish number" << endl;
                    break;
                }
                Dish dish = dishes[dishN - 1];
                recipeGateway->update(recipe.get_id(), cookingTime, cookingTechnology, dish.get_id());
                break;
            }
            case 4: {
                vector<Recipe> recipes = recipeGateway->findAll();
                paginate(recipes.size(), [recipes, this](int i) {
                    paginate(recipes.size(), [recipes, this](int i) {
                        Recipe currentRecipe = recipes[i];
                        cout << left << setw(10) << i + 1 << setw(20) << currentRecipe.get_cooking_time() << setw(20) <<
                                currentRecipe.get_cooking_technology() << setw(20) << dishGateway->findById(
                                    currentRecipe.get_dish_id())->get_name();
                    });
                });
            }
            case 0: {
                break;
            }
        }
    }
}

void Menu::runProductsMenu() {
    while (true) {
        cout << "Dish menu" << endl;
        cout << "1. Insert product" << endl;
        cout << "2. Delete product" << endl;
        cout << "3. Update product" << endl;
        cout << "4. Print all products" << endl;
        cout << "0. Exit" << endl;
        printEnterAction();

        switch (readAction()) {
            case 1: {
                cout << "Enter product name: " << endl;
                string productName;
                getline(cin >> ws, productName);

                cout << "Enter caloric content: " << endl;
                long caloricContent;
                cin >> caloricContent;

                cout << "Enter product weight: " << endl;
                long productWeight;
                cin >> productWeight;

                cout << "Enter product price: " << endl;
                double productPrice;
                cin >> productPrice;

                productGateway->insert(productName, caloricContent, productWeight, productPrice);
            }
            case 2: {
                vector<Product> products = productGateway->findAll();
                cout << "Products: " << endl;
                cout << left << setw(10) << "N" << setw(20) << "Product" << setw(20) << "Caloric content" << setw(20) <<
                        "Weight" << setw(20) << "Price" << endl;
                paginate(products.size(), [products, this](int i) {
                    Product currentProduct = products[i];
                    cout << left << setw(10) << i + 1 << setw(20) << currentProduct.get_name() << setw(20) <<
                            currentProduct.get_caloric_content() << setw(20) << currentProduct.get_weight() << setw(20)
                            << currentProduct.get_price() << endl;
                });

                int productN;
                cout << "Enter product type N: ";
                cin >> productN;
                if (productN <= 0 || productN > products.size()) {
                    cout << "Invalid product number" << endl;
                    break;
                }
                Product productToDelete = products[productN - 1];

                vector<DishToProduct> dishToProducts = dishToProductGateway->findAll();

                boolean existsInDishes = false;
                for (auto currentDishToProduct: dishToProducts) {
                    if (currentDishToProduct.get_product_id() == productToDelete.get_id()) {
                        existsInDishes = true;
                        break;
                    }
                }
                if (existsInDishes) {
                    cout << "Product exists in dishes" << endl;
                    break;
                }

                productGateway->remove(productToDelete.get_id());
            }
            case 3: {
                vector<Product> products = productGateway->findAll();
                cout << "Products: " << endl;
                cout << left << setw(10) << "N" << setw(20) << "Product" << setw(20) << "Caloric content" << setw(20) <<
                        "Weight" << setw(20) << "Price" << endl;
                paginate(products.size(), [products, this](int i) {
                    Product currentProduct = products[i];
                    cout << left << setw(10) << i + 1 << setw(20) << currentProduct.get_name() << setw(20) <<
                            currentProduct.get_caloric_content() << setw(20) << currentProduct.get_weight() << setw(20)
                            << currentProduct.get_price() << endl;
                });

                int productN;
                cout << "Enter product type N: ";
                cin >> productN;
                if (productN <= 0 || productN > products.size()) {
                    cout << "Invalid product number" << endl;
                    break;
                }
                Product productToUpdate = products[productN - 1];

                string name;
                cout << "Enter product name: ";
                getline(cin >> ws, name);

                long caloricContent;
                cout << "Enter caloric content: ";
                cin >> caloricContent;

                long weight;
                cout << "Enter weight: ";
                cin >> weight;

                double price;
                cout << "Enter price: ";
                cin >> price;

                productGateway->update(productToUpdate.get_id(), name, caloricContent, weight, price);
            }
            case 4: {
                vector<Product> products = productGateway->findAll();
                cout << "Products: " << endl;
                cout << left << setw(10) << "N" << setw(20) << "Product" << setw(20) << "Caloric content" << setw(20) <<
                        "Weight" << setw(20) << "Price" << endl;
                paginate(products.size(), [products, this](int i) {
                    Product currentProduct = products[i];
                    cout << left << setw(10) << i + 1 << setw(20) << currentProduct.get_name() << setw(20) <<
                            currentProduct.get_caloric_content() << setw(20) << currentProduct.get_weight() << setw(20)
                            << currentProduct.get_price() << endl;
                });
            }
            case 0: {
                return;
            }
        }
    }
}


void Menu::paginate(int size, const function<void(int)> &func) {
    if (size <= 0) {
        cout << "Elements are missing" << endl;
        return;
    }
    int totalPages = (size + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    for (int currentPage = 0; currentPage < totalPages;) {
        int start = currentPage * ITEMS_PER_PAGE;
        int end = min(start + ITEMS_PER_PAGE, size);

        cout << "Page " << currentPage + 1 << " of " << totalPages << endl;
        for (int i = start; i < end; i++) {
            func(i);
        }

        if (++currentPage >= totalPages) {
            return;
        }

        cout << "'n' to continue, 'q' to quit: ";
        char action;
        cin >> action;
        if (action == 'q') {
            return;
        }
    }
}
