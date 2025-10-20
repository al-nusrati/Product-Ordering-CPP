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
    // Exception classes
    class ProductNotFound {};
    class InsufficientStock {};
    class InvalidQuantity {};
    class ExcessiveCancellation {};

    // Constructor
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

    // Add product
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

    // Find product index
    int findProductIndex(int id) {
        for (int i = 0; i < productCount; i++) {
            if (productID[i] == id)
                return i;
        }
        throw ProductNotFound();
    }

    // Place an order
    void placeOrder(int id, int quantity) {
        int index = findProductIndex(id);

        if (quantity <= 0)
            throw InvalidQuantity();

        if (quantity > availableQuantity[index])
            throw InsufficientStock();

        availableQuantity[index] -= quantity;
        orderedQuantity[index] += quantity;

        cout << "Order placed successfully!" << endl;
        cout << "Product: " << productName[index] << endl;
        cout << "Quantity ordered: " << quantity << endl;
        cout << "Total price: $" << (price[index] * quantity) << endl;
        cout << "Remaining stock: " << availableQuantity[index] << endl;
    }

    // Cancel an order
    void cancelOrder(int id, int quantity) {
        int index = findProductIndex(id);

        if (quantity > orderedQuantity[index])
            throw ExcessiveCancellation();

        availableQuantity[index] += quantity;
        orderedQuantity[index] -= quantity;

        cout << "Order cancelled successfully!" << endl;
        cout << "Product: " << productName[index] << endl;
        cout << "Quantity cancelled: " << quantity << endl;
        cout << "Updated stock: " << availableQuantity[index] << endl;
    }

    // View all products
    void viewAllProducts() {
        cout << "\n=== All Products ===" << endl;
        for (int i = 0; i < productCount; i++) {
            cout << "\nProduct ID: " << productID[i] << endl;
            cout << "Name: " << productName[i] << endl;
            cout << "Price: $" << price[i] << endl;
            cout << "Available Quantity: " << availableQuantity[i] << endl;
            cout << "Ordered Quantity: " << orderedQuantity[i] << endl;
        }
    }
};

int main() {
    OrderingSystem system;

    // Add products to system
    system.addProduct(101, "Laptop", 999.99, 10);
    system.addProduct(102, "Mouse", 25.50, 50);
    system.addProduct(103, "Keyboard", 75.00, 30);

    cout << "=== Online Product Ordering System ===" << endl;

    // Test 1: Place valid order
    cout << "\n--- Test 1: Place order for 2 Laptops (ID: 101) ---" << endl;
    try {
        system.placeOrder(101, 2);
    }
    catch (OrderingSystem::ProductNotFound) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::InsufficientStock) {
        cout << "Exception: Insufficient stock!" << endl;
    }
    catch (OrderingSystem::InvalidQuantity) {
        cout << "Exception: Invalid quantity! Must be positive." << endl;
    }

    // Test 2: Place order exceeding available quantity
    cout << "\n--- Test 2: Place order for 20 Laptops (ID: 101) ---" << endl;
    try {
        system.placeOrder(101, 20);
    }
    catch (OrderingSystem::ProductNotFound) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::InsufficientStock) {
        cout << "Exception: Insufficient stock!" << endl;
    }
    catch (OrderingSystem::InvalidQuantity) {
        cout << "Exception: Invalid quantity! Must be positive." << endl;
    }

    // Test 3: Place order with zero quantity
    cout << "\n--- Test 3: Place order for 0 Mice (ID: 102) ---" << endl;
    try {
        system.placeOrder(102, 0);
    }
    catch (OrderingSystem::ProductNotFound) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::InsufficientStock) {
        cout << "Exception: Insufficient stock!" << endl;
    }
    catch (OrderingSystem::InvalidQuantity) {
        cout << "Exception: Invalid quantity! Must be positive." << endl;
    }

    // Test 4: Cancel more than ordered quantity
    cout << "\n--- Test 4: Cancel 5 Laptops (only 2 were ordered) ---" << endl;
    try {
        system.cancelOrder(101, 5);
    }
    catch (OrderingSystem::ProductNotFound) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::ExcessiveCancellation) {
        cout << "Exception: Cannot cancel more than ordered quantity!" << endl;
    }

    // Test 5: View product details
    cout << "\n--- Test 5: View details of all products ---" << endl;
    try {
        system.viewAllProducts();
    }
    catch (OrderingSystem::ProductNotFound) {
        cout << "Exception: Product not found!" << endl;
    }

    // Test 6: Try to access non-existent product
    cout << "\n--- Test 6: Place order for non-existent product (ID: 999) ---" << endl;
    try {
        system.placeOrder(999, 1);
    }
    catch (OrderingSystem::ProductNotFound) {
        cout << "Exception: Product not found!" << endl;
    }
    catch (OrderingSystem::InsufficientStock) {
        cout << "Exception: Insufficient stock!" << endl;
    }
    catch (OrderingSystem::InvalidQuantity) {
        cout << "Exception: Invalid quantity! Must be positive." << endl;
    }

    return 0;
}