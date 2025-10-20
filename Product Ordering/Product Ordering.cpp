#include <iostream>
using namespace std;

const int MAX_PRODUCTS = 5;

class OrderingSystem {
private:
    int productID[MAX_PRODUCTS];
    string productName[MAX_PRODUCTS];
    double price[MAX_PRODUCTS];
    int availableQuantity[MAX_PRODUCTS];
    int orderedQuantity[MAX_PRODUCTS];
    int productCount;

public:

    class ProductNotFoundException {};      // product code is wrong
    class InsufficientStockException {};    // product quantity is exceeding
    class InvalidQuantityException {};      // product quantity is negative
    class ExcessiveCancellationException {};    // cancelation quantity of product is less than products itself

    OrderingSystem() {
        productCount = 0;
        for (int i = 0; i < MAX_PRODUCTS; i++) {
            productID[i] = 0;
            productName[i] = "";
            price[i] = 0.0;
            availableQuantity[i] = 0;
            orderedQuantity[i] = 0;
        }
    }

    void addProduct(int id, string name, double pr, int qty) {
        if (productCount < MAX_PRODUCTS) {
            productID[productCount] = id;
            productName[productCount] = name;
            price[productCount] = pr;
            availableQuantity[productCount] = qty;
            orderedQuantity[productCount] = 0;
            productCount++;
        }
    }

    int findProductIndex(int id) {
        for (int i = 0; i < productCount; i++) {
            if (productID[i] == id)
                return i;
        }
        throw ProductNotFoundException();
    }

    void placeOrder(int id, int quantity) {
        int index = findProductIndex(id);

        if (quantity <= 0)
            throw InvalidQuantityException();

        if (quantity > availableQuantity[index])
            throw InsufficientStockException();

        availableQuantity[index] -= quantity;
        orderedQuantity[index] += quantity;

        cout << "Order placed successfully!" << endl;
        cout << "Product: " << productName[index] << endl;
        cout << "Quantity ordered: " << quantity << endl;
        cout << "Total price: PKR" << (price[index] * quantity) << endl;
        cout << "Remaining stock: " << availableQuantity[index] << endl;
    }

    void cancelOrder(int id, int quantity) {
        int index = findProductIndex(id);

        if (quantity > orderedQuantity[index])
            throw ExcessiveCancellationException();

        availableQuantity[index] += quantity;
        orderedQuantity[index] -= quantity;

        cout << "Order cancelled successfully!" << endl;
        cout << "Product: " << productName[index] << endl;
        cout << "Quantity cancelled: " << quantity << endl;
        cout << "Updated stock: " << availableQuantity[index] << endl;
    }

    void viewAllProducts() {
        for (int i = 0; i < productCount; i++) {
            cout << "\nProduct ID: " << productID[i] << endl;
            cout << "Name: " << productName[i] << endl;
            cout << "Price: " << price[i] << endl;
            cout << "Available Quantity: " << availableQuantity[i] << endl;
            cout << "Ordered Quantity: " << orderedQuantity[i] << endl;
        }
    }
};

int main() {
    OrderingSystem Osystem;

    Osystem.addProduct(101, "Laptop", 900, 10);
    Osystem.addProduct(102, "Mouse", 125, 50);
    Osystem.addProduct(103, "Keyboard", 400, 30);

    cout << "\nPlacing a valid order: " << endl;
    try {
        Osystem.placeOrder(101, 2);                              // <---
    }
    catch (OrderingSystem::ProductNotFoundException) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::InsufficientStockException) {
        cout << "Exception: Insufficient stock!" << endl;
    }
    catch (OrderingSystem::InvalidQuantityException) {
        cout << "Exception: Invalid quantity! Must be positive." << endl;
    }

    cout << "\nPlacing order for exceeding quantity: " << endl;
    try {
        Osystem.placeOrder(101, 20);
    }
    catch (OrderingSystem::ProductNotFoundException) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::InsufficientStockException) {        // <---
        cout << "Exception: Insufficient stock!" << endl;
    }
    catch (OrderingSystem::InvalidQuantityException) {
        cout << "Exception: Invalid quantity! Must be positive." << endl;
    }

    cout << "\nPlacing order with 0 quantity: " << endl;
    try {
        Osystem.placeOrder(102, 0);
    }
    catch (OrderingSystem::ProductNotFoundException) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::InsufficientStockException) {
        cout << "Exception: Insufficient stock!" << endl;
    }
    catch (OrderingSystem::InvalidQuantityException) {                      // <---
        cout << "Exception: Invalid quantity! Must be positive." << endl;
    }

    cout << "\nCancelling 5 Laptops when only 2 were ordered: " << endl;
    try {
        Osystem.cancelOrder(101, 5);
    }
    catch (OrderingSystem::ProductNotFoundException) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::ExcessiveCancellationException) {                        // <---
        cout << "Exception: Cannot cancel more than ordered quantity!" << endl;         
    }

    cout << "\nViewing details of all orders: " << endl;
    try {
        Osystem.viewAllProducts();
    }
    catch (OrderingSystem::ProductNotFoundException) {
        cout << "Exception: Product not found!" << endl;        
    }



    //==============================================




    cout << "\nPlacing order for wrong product id: " << endl;
    try {
        Osystem.placeOrder(999, 1);
    }
    catch (OrderingSystem::ProductNotFoundException) {              //<----
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::InsufficientStockException) {
        cout << "Exception: Insufficient stock!" << endl;
    }
    catch (OrderingSystem::InvalidQuantityException) {
        cout << "Exception: Invalid quantity! Must be positive." << endl;
    }

    system("pause>0");
    return 0;
}