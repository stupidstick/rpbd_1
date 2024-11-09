//
// Created by stupi on 04.11.2024.
//

#include "Menu.h"

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <set>

#include "../utils/DateStringValidator.h"

#define ITEMS_PER_PAGE 20

using namespace std;

void printEnterAction() {
    cout << "Enter action: ";
}

void printTableHeader(const vector<string> &columns) {
    cout << left << setw(10) << "N";
    for (const auto &column: columns) {
        cout << setw(20) << column;
    }
    cout << endl;
}

void paginate(int size, const function<void(int)> &func) {
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
        cout << "5. Cook menu" << endl;
        cout << "6. Dish cooking menu" << endl;
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
                runRecipeMenu();
                break;
            }
            case 4: {
                runProductsMenu();
                break;
            }
            case 5: {
                runCookMenu();
                break;
            }
            case 6: {
                runDishCookingMenu();
                break;
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
                DishType dishType = dishTypes[n - 1];

                boolean dishTypeUsed = false;
                vector<Dish> dishes = dishGateway->findAll();
                for (Dish dish: dishes) {
                    if (dish.get_dish_type_id() == dishType.get_id()) {
                        dishTypeUsed = true;
                        break;
                    }
                }
                if (dishTypeUsed) {
                    cout << "Dish type used in dishes." << endl;
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

void Menu::printDishes(const vector<Dish> &dishes) {
    cout << "All dishes:" << endl;
    cout << left << setw(10) << "N" << setw(20) << "Dish" << setw(20) << "Dish type" << setw(20) <<
            "Products" << endl;
    vector<DishToProduct> dishesToProducts = dishToProductGateway->findAll();

    paginate(dishes.size(), [dishes, dishesToProducts, this](int i) {
        auto currentDish = dishes[i];
        DishType dishType = dishTypeGateway->findById(currentDish.get_dish_type_id()).value();

        cout << left << setw(10) << i + 1 << setw(20) << currentDish.get_name() << setw(20) << dishType.
                get_name();
        for (auto dishToProduct: dishesToProducts) {
            if (dishToProduct.get_dish_id() == currentDish.get_id()) {
                Product product = productGateway->findById(dishToProduct.get_product_id()).value();
                cout << product.get_name() << " ";
            }
        }
        cout << endl;
    });
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
                    break;
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
                    if (productN <= 0 || productN > products.size()) {
                        cout << "Invalid product number" << endl;
                    } else {
                        productsToAdd.push_back(products[productN - 1]);
                    }
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
                Dish dish = dishes[n - 1];

                boolean containsInAnotherTable = false;
                vector<Recipe> recipes = recipeGateway->findAll();
                for (auto recipe: recipes) {
                    if (recipe.get_dish_id() == dish.get_id()) {
                        containsInAnotherTable = true;
                        break;
                    }
                }
                if (containsInAnotherTable) {
                    cout << "Dish contains in recipes" << endl;
                    break;
                }

                vector<DishCooking> dishCookings = dishCookingGateway->findAll();
                for (auto dishCooking: dishCookings) {
                    if (dishCooking.get_dish_id() == dish.get_id()) {
                        containsInAnotherTable = true;
                        break;
                    }
                }
                if (containsInAnotherTable) {
                    cout << "Dish contains in dish cookings" << endl;
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
                printDishes(dishes);

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

                printProducts(products);
                vector<Product> productsToAdd = vector<Product>();
                int productN;
                cout << "Enter product N or -1 to stop" << endl;
                while (true) {
                    cin >> productN;
                    if (productN == -1) {
                        break;
                    }
                    if (productN <= 0 || productN > products.size()) {
                        cout << "Invalid product number" << endl;
                    } else {
                        productsToAdd.push_back(products[productN - 1]);
                    }
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
                break;
            }
            case 4: {
                printDishes(dishGateway->findAll());
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
        cout << "Recipe menu" << endl;
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

                printTableHeader({"Cooking time", "Cooking Technology", "Dish"});
                paginate(recipes.size(), [recipes, this](int i) {
                    Recipe currentRecipe = recipes[i];
                    cout << left
                            << setw(10) << i + 1
                            << setw(20) << currentRecipe.get_cooking_time()
                            << setw(20) << currentRecipe.get_cooking_technology()
                            << setw(20) << dishGateway->findById(currentRecipe.get_dish_id())->get_name();
                });
                cout << endl;

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
                printTableHeader({"Cooking time", "Cooking Technology", "Dish"});
                paginate(recipes.size(), [recipes, this](int i) {
                    Recipe currentRecipe = recipes[i];
                    cout << left
                            << setw(10) << i + 1
                            << setw(20) << currentRecipe.get_cooking_time()
                            << setw(20) << currentRecipe.get_cooking_technology()
                            << setw(20) << dishGateway->findById(currentRecipe.get_dish_id())->get_name();
                });
                cout << endl;

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
                printTableHeader({"Cooking time", "Cooking Technology", "Dish"});
                vector<Recipe> recipes = recipeGateway->findAll();
                paginate(recipes.size(), [recipes, this](int i) {
                    Recipe currentRecipe = recipes[i];
                    cout << left
                            << setw(10) << i + 1
                            << setw(20) << currentRecipe.get_cooking_time()
                            << setw(20) << currentRecipe.get_cooking_technology()
                            << setw(20) << dishGateway->findById(currentRecipe.get_dish_id())->get_name();
                });
                cout << endl;
                break;
            }
            case 0: {
                return;
            }
        }
    }
}

void Menu::printProducts(vector<Product> products) {
    cout << "Products: " << endl;
    printTableHeader({"Products", "Caloric content", "Weight", "Price"});
    paginate(products.size(), [products, this](int i) {
        Product currentProduct = products[i];
        cout << left << setw(10) << i + 1 << setw(20) << currentProduct.get_name() << setw(20) <<
                currentProduct.get_caloric_content() << setw(20) << currentProduct.get_weight() << setw(20)
                << currentProduct.get_price() << endl;
    });
}

void Menu::runProductsMenu() {
    while (true) {
        cout << "Products menu" << endl;
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
                break;
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
                break;
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
                break;
            }
            case 4: {
                printProducts(productGateway->findAll());
                break;
            }
            case 0: {
                return;
            }
        }
    }
}

string readField(const string &fieldName) {
    cout << "Enter " << fieldName << ":";
    string str;
    getline(cin >> ws, str);
    return str;
}

void Menu::printCooks(vector<Cook> cooks) {
    printTableHeader({
        "Name", "Middle name", "Surname", "Passport series", "Passport number", "Department code",
        "Issuer authority name", "Date of issue", "Address", "Health cert number", "Health cert receipt date"
    });
    paginate(cooks.size(), [this, cooks](int i) {
        Cook currentCook = cooks[i];
        Passport currentPassport = passportGateway->findById(currentCook.get_passport_id()).value();
        HealthCert healthCert = healthCertGateway->findById(currentCook.get_health_cert_id()).value();

        cout << left
                << setw(10) << i + 1
                << setw(20) << currentPassport.get_first_name()
                << setw(20) << currentPassport.get_middle_name()
                << setw(20) << currentPassport.get_last_name()
                << setw(20) << currentPassport.get_series()
                << setw(20) << currentPassport.get_number()
                << setw(20) << currentPassport.get_departmnet_code()
                << setw(20) << currentPassport.get_issuer_authority_name()
                << setw(20) << currentPassport.get_date_of_issue()
                << setw(20) << currentCook.get_address()
                << setw(20) << healthCert.get_number()
                << setw(20) << healthCert.get_receipt_date()
                << endl;
    });
}

void Menu::runCookMenu() {
    while (true) {
        cout << "Cook menu" << endl;
        cout << "1. Add cook" << endl;
        cout << "2. Delete cook" << endl;
        cout << "3. Update cook" << endl;
        cout << "4. Print all cooks" << endl;
        cout << "0. Exit" << endl;
        switch (readAction()) {
            case 1: {
                string surname = readField("surname");
                string name = readField("name");
                string middleName = readField("middle name");
                string passportSeries = readField("passport series");
                string passportNumber = readField("passport number");
                string departmentCode = readField("department code");
                string issuerAuthorityName = readField("issuer authority name");
                string passportDateOfIssue = readField("date of issue in YYYY-MM-DD format");
                if (DateStringValidator::validateDate(passportDateOfIssue) == false) {
                    cout << "Invalid date" << endl;
                    break;
                }
                string address = readField("address");
                string healthCertNumber = readField("health cert number");
                string healthCertReceiptDate = readField("date of issue in YYYY-MM-DD format");

                Passport passport = passportGateway->insert(name, surname, middleName, passportSeries, passportNumber,
                                                            departmentCode,
                                                            issuerAuthorityName, passportDateOfIssue);
                HealthCert healthCert = healthCertGateway->insert(healthCertNumber, healthCertReceiptDate);
                cookGateway->insert(address, passport.get_id(), healthCert.get_id());
                break;
            }
            case 2: {
                vector<Cook> cooks = cookGateway->findAll();
                printCooks(cooks);

                int cookN;
                cout << "Enter cook N: ";
                cin >> cookN;
                if (cookN <= 0 || cookN > cooks.size()) {
                    cout << "Invalid cook N" << endl;
                    break;
                }
                Cook cook = cooks[cookN - 1];

                boolean containsInAnotherTable = false;
                vector<DishCooking> dishCookings = dishCookingGateway->findAll();
                for (auto dishCooking: dishCookings) {
                    if (dishCooking.get_cook_id() == cook.get_id()) {
                        containsInAnotherTable = true;
                        break;
                    }
                }
                if (containsInAnotherTable) {
                    cout << "Dish contains in dish cookings" << endl;
                    break;
                }

                cookGateway->remove(cook.get_id());
                passportGateway->remove(cook.get_passport_id());
                healthCertGateway->remove(cook.get_health_cert_id());
                break;
            }
            case 3: {
                vector<Cook> cooks = cookGateway->findAll();
                printCooks(cooks);

                int cookN;
                cout << "Enter cook N: ";
                cin >> cookN;
                if (cookN <= 0 || cookN > cooks.size()) {
                    cout << "Invalid cook N" << endl;
                    break;
                }

                Cook cook = cooks[cookN - 1];

                string surname = readField("surname");
                string name = readField("name");
                string middleName = readField("middle name");
                string passportSeries = readField("passport series");
                string passportNumber = readField("passport number");
                string departmentCode = readField("department code");
                string issuerAuthorityName = readField("issuer authority name");
                string passportDateOfIssue = readField("date of issue in YYYY-MM-DD format");
                if (DateStringValidator::validateDate(passportDateOfIssue) == false) {
                    cout << "Invalid date" << endl;
                    break;
                }
                string address = readField("address");
                string healthCertNumber = readField("health cert number");
                string healthCertReceiptDate = readField("date of issue in YYYY-MM-DD format");

                Passport passportToUpdate;
                for (auto passport: passportGateway->findAll()) {
                    if (cook.get_passport_id() == passport.get_id()) {
                        passportToUpdate = passport;
                        break;
                    }
                }

                HealthCert healthCertToUpdate;
                for (auto healthCert: healthCertGateway->findAll()) {
                    if (cook.get_health_cert_id() == healthCert.get_id()) {
                        healthCertToUpdate = healthCert;
                        break;
                    }
                }
                healthCertGateway->update(healthCertToUpdate.get_id(), healthCertNumber, healthCertReceiptDate);
                passportGateway->update(passportToUpdate.get_id(), name, surname, middleName, passportSeries,
                                        passportNumber, departmentCode, issuerAuthorityName,
                                        passportDateOfIssue);
                cookGateway->update(cook.get_id(), address, passportToUpdate.get_id(), healthCertToUpdate.get_id());
                break;
            }
            case 4: {
                vector<Cook> cooks = cookGateway->findAll();
                printCooks(cooks);
                break;
            }
            case 0: {
                return;
            }
        }
    }
}

void Menu::printDishCookings(vector<DishCooking> dishCookings) {
    printTableHeader({"Cook", "Dish", "Dish type", "Servings count", "Cooking date"});
    paginate(dishCookings.size(), [dishCookings, this](int i) {
        DishCooking dishCooking = dishCookings[i];
        Cook cook = cookGateway->findById(dishCooking.get_cook_id()).value();
        Passport passport = passportGateway->findById(cook.get_passport_id()).value();
        Dish dish = dishGateway->findById(dishCooking.get_dish_id()).value();
        DishType dishType = dishTypeGateway->findById(dish.get_dish_type_id()).value();
        cout << left
                << setw(10) << i + 1
                 << passport.get_last_name() << " " << passport.get_first_name() << " " << passport.
                get_middle_name()
                << setw(20) << dish.get_name()
                << setw(20) << dishType.get_name()
                << setw(20) << dishCooking.get_servings_count()
                << setw(20) << dishCooking.get_cooking_date()
                << endl;
    });
}

void Menu::runDishCookingMenu() {
    while (true) {
        cout << "Dish cooking menu" << endl;
        cout << "1. Add dish cooking" << endl;
        cout << "2. Delete dish cooking" << endl;
        cout << "3. Update dish cooking" << endl;
        cout << "4. Print all dish cookings" << endl;
        cout << "0. Exit" << endl;
        switch (readAction()) {
            case 1: {
                vector<Cook> cooks = cookGateway->findAll();
                if (cooks.empty()) {
                    cout << "No cooks found" << endl;
                    break;
                }
                vector<Dish> dishes = dishGateway->findAll();
                if (dishes.empty()) {
                    cout << "No dishes found" << endl;
                    break;
                }

                printCooks(cooks);
                cout << "Enter cook N" << endl;
                int cookN;
                cin >> cookN;
                if (cookN <= 0 || cookN > dishes.size()) {
                    cout << "Invalid cook N" << endl;
                    break;
                }

                printDishes(dishes);
                cout << "Enter dish N" << endl;
                int dishN;
                cin >> dishN;
                if (dishN <= 0 || dishN > dishes.size()) {
                    cout << "Invalid dish N" << endl;
                    break;
                }

                cout << "Enter servings count: " << endl;
                int servingsCount;
                cin >> servingsCount;
                if (servingsCount <= 0) {
                    cout << "Invalid servings count" << endl;
                    break;
                }

                string cookingDate = readField("cooking date");
                if (!DateStringValidator::validateDate(cookingDate)) {
                    cout << "Invalid cooking date" << endl;
                }

                dishCookingGateway->insert(servingsCount, cookingDate, cooks[cookN - 1].get_id(),
                                           dishes[dishN - 1].get_id());
                break;
            }
            case 2: {
                vector<DishCooking> dishCookings = dishCookingGateway->findAll();
                printDishCookings(dishCookings);

                cout << "Enter dish cooking N: " << endl;
                int dishCookingN;
                cin >> dishCookingN;
                if (dishCookingN <= 0 || dishCookingN > dishCookings.size()) {
                    cout << "Invalid dish cooking N" << endl;
                    break;
                }
                DishCooking dishCooking = dishCookings[dishCookingN - 1];
                dishCookingGateway->remove(dishCooking.get_id());
                break;
            }
            case 3: {
                vector<Dish> dishes = dishGateway->findAll();
                if (dishes.empty()) {
                    cout << "No dishes found" << endl;
                    break;
                }
                vector<Cook> cooks = cookGateway->findAll();
                if (cooks.empty()) {
                    cout << "No cooks found" << endl;
                    break;
                }

                vector<DishCooking> dishCookings = dishCookingGateway->findAll();
                printDishCookings(dishCookings);

                cout << "Enter dish cooking N: " << endl;
                int dishCookingN;
                cin >> dishCookingN;
                if (dishCookingN <= 0 || dishCookingN > dishCookings.size()) {
                    cout << "Invalid dish cooking N" << endl;
                    break;
                }
                DishCooking dishCooking = dishCookings[dishCookingN - 1];

                printCooks(cooks);
                cout << "Enter cook N" << endl;
                int cookN;
                cin >> cookN;
                if (cookN <= 0 || cookN > dishes.size()) {
                    cout << "Invalid cook N" << endl;
                    break;
                }

                printDishes(dishes);
                cout << "Enter dish N" << endl;
                int dishN;
                cin >> dishN;
                if (dishN <= 0 || dishN > dishes.size()) {
                    cout << "Invalid dish N" << endl;
                    break;
                }

                cout << "Enter servings count: " << endl;
                int servingsCount;
                cin >> servingsCount;
                if (servingsCount <= 0) {
                    cout << "Invalid servings count" << endl;
                    break;
                }

                string cookingDate = readField("cooking date");
                if (!DateStringValidator::validateDate(cookingDate)) {
                    cout << "Invalid cooking date" << endl;
                }

                dishCookingGateway->update(dishCooking.get_id(), servingsCount, cookingDate, cooks[cookN - 1].get_id(),
                                           dishes[dishN - 1].get_id());
                break;
            }
            case 4: {
                printDishCookings(dishCookingGateway->findAll());
                break;
            }
            case 0: {
                return;
            }
        }
    }
}
