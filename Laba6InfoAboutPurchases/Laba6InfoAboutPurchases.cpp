#include <iostream>
#include <string>

using namespace std;

struct Product {
    string productName;
    int amount;
    double unitPrice;
};


struct Order {
    int orderNumber;
    string customerName;
    int year, month, day;
    Product products[10];
};


double getTotalOrderCost(Order* orders, int amountOrders) {
    double totalCost = 0;

    int day, month, year;

    cout << "Type date to get total order cost. \nDay: ";
    cin >> day;

    cout << "Month: ";
    cin >> month;

    cout << "Year: ";
    cin >> year;



    for (int i = 0; i < amountOrders; i++) {
        if (orders[i].day == day && orders[i].month == month && orders[i].year == year) {
            int amountProducts = sizeof(orders[i].products) / sizeof(orders[i].products[0]);


            for (int j = 0; j < amountProducts; j++) {
                int quantityProduct = orders[i].products[j].amount;
                int priceProduct = orders[i].products[j].unitPrice;

                totalCost += quantityProduct * priceProduct;
            }
        }
        else {
            continue;
        }
    };

    return totalCost;
};

bool wasBoughtAlone(Order* orders, int amountOrders) {
    string productName;

    int aloneCount = 0;
    int withOthersCount = 0;

    cout << endl << "Type product name to get info about purchases: ";
    cin >> productName;

    for (int i = 0; i < amountOrders; i++) {
        int amountProducts = sizeof(orders[i].products) / sizeof(orders[i].products[0]);

        for (int j = 0; j < amountProducts; j++) {
            if (orders[i].products[j].productName == productName) {
                if (amountProducts == 1) {
                    aloneCount++;
                }
                else {
                    withOthersCount++;
                }
            }
            else {
                continue;
            }
        }
    }

    return aloneCount > withOthersCount;
}



void calcTotalPurchasePerMonth(Order* orders, int amountOrders) {
    string customerName;

    cout << endl << "Type customer name to find all his purchase per month: ";
    cin >> customerName;

    double totalPerMonth[12]{};

    for (int i = 0; i < amountOrders; i++) {
        if (orders[i].customerName == customerName) {
            int monthIndex = orders[i].month - 1;
            int amountProducts = sizeof(orders[i].products) / sizeof(orders[i].products[0]);

            for (int j = 0; j < amountProducts; j++) {
                totalPerMonth[monthIndex] += orders[i].products[j].amount * orders[i].products[j].unitPrice;
            }
        }
        else {
            continue;
        }
    }


    for (int i = 0; i < 12; i++) {
        cout << "Total purchase by " << customerName << " for " << i + 1 << " month: " << totalPerMonth[i] << "$" << endl;
    }


}

int main() {
    int amountOrders;

    cout << "How much orders?: ";

    cin >> amountOrders;

    Order* orders = new Order[amountOrders];

    for (int i = 0; i < amountOrders; i++) {
        int orderNumberMassive, yearMassive, monthMassive, dayMassive, amountProducts;

        string customerNameMassive;


        cout << endl << "Order #" << i + 1 << endl << "Type order number: ";
        cin >> orderNumberMassive;

        cout << "Type customer name: ";
        cin >> customerNameMassive;

        cout << "Type day: ";
        cin >> dayMassive;

        cout << "Type month: ";
        cin >> monthMassive;

        cout << "Type year: ";
        cin >> yearMassive;

        orders[i] = { orderNumberMassive, customerNameMassive, yearMassive, monthMassive, dayMassive };


        cout << "Type how much product in orders(max 10): ";
        cin >> amountProducts;

        if (amountOrders > 10) {
            cout << "Failure. Max amount orders 10";
            return 0;
        }
        else {
            for (int j = 0; j < amountProducts; j++) {
                string productNameMassive;
                int amountProduct;
                double unitPriceProduct;

                cout << endl << "Product #" << j + 1 << endl << "Type product name: ";
                cin >> productNameMassive;

                cout << "Type quantity product: ";
                cin >> amountProduct;

                cout << "Type price product: ";
                cin >> unitPriceProduct;

                orders[i].products[j].productName = productNameMassive;
                orders[i].products[j].amount = amountProduct;
                orders[i].products[j].unitPrice = unitPriceProduct;

            }
        }

        cout << "Succesful" << endl;

    }

    double totalOrderCost = getTotalOrderCost(orders, amountOrders);

    cout << endl << endl << "Total order cost = " << totalOrderCost;

    bool wasBougthAloneOrWith = wasBoughtAlone(orders, amountOrders);

    if (wasBougthAloneOrWith) {
        cout << endl << endl << "Product bougth alone more often";
    }
    else {
        cout << endl << endl << "Product bouth with other more often";
    }

    calcTotalPurchasePerMonth(orders, amountOrders);

    return 0;
}