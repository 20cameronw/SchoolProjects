#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
using namespace std;

// Global variables
int numPoints = 0;
float shoppingAmount = 0.0;
int numProducts = 0;

// Function declarations
void rewardManagement();
void getPoints();
void getProducts();
string selectGift();
int valueOfGift(string);
void saveRedeemableGifts(string, float);

// Reward Management function
// Open the reward management text file and overwrite it each time.
// Call the getPoints function to get user input for points awarded per shopping amount.
// Write user input to the file, then close file.
// No parameters.
// No return values.
void rewardManagement() {
    // open rewardManagement file, overwrite it each time.
    ofstream myfile("pointsAwardedPerAmount.txt", ofstream::trunc);
    getPoints();
    myfile << numPoints << '\n' << shoppingAmount << '\n';
    myfile.close();
}

// Get Points function
// Prompt user for number of points to be given per purchase
// Prompt user for amount needed to recieve one reward point.
// No parameters.
// No return values.
void getPoints() {
    cout << "Please input integer (x) number of points awarded for a given shopping amount float (y)\n";
    cout << "Number of points: ";
    // while not an int, sanitize input, and continue until user inputs correct data type
    while (!(cin >> numPoints)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input enter again." << endl;
    }
    //cin >> numPoints;
    cout << "Shopping amount: ";
    cin >> shoppingAmount;
    while(!(cin >> shoppingAmount)) {
        cin.clear();
        cin.ignore(6, '\n');
        cout << "Entered shopping amount was not of type float. Try again.\n";
    }
}

// Get Products function
// Open the products text file, check that products actually exist. 
// If products exist, iterate through each field in file, and print to user. 
// numProducts is lines in file. Each product has 4 lines. 
// Divide numProducts by 4 lines to get actual number of products in file. 
// Print the number of products in file to user.
// No parameters.
// No return values.
void getProducts() {
    ifstream myfile;
    string product, productNum, field;
    myfile.open("products.txt");
    if (myfile.peek() == EOF) { 
        cout << "No products currently exist.\n";
    } else {
        cout << "Available products listed below: \n";
        while(myfile >> product >> productNum >> field) {
            cout << product << " " << productNum << " " << field << '\n';
            numProducts++;
        }
    }
    cout << "Number of products: " << numProducts / 4 << '\n';
}

// Select Gift function
// Function for manager to select a valid product to be selected as a gift to be purchased with reward points.
// Prompt user to input a valid product number
// If product number invalid, stay in this state until user gives valid product number.
// Print to user the product they've selected
// Return the string of the product. 
string selectGift() {
    int productNumber = 0;
    string product = "product ";
    cout << "Please enter a valid Product number (as an integer) to be selected as a gift: \n";
    // validate input, make sure input is int, or continue to loop.
    while (!(cin >> productNumber)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input enter again." << endl;
    }
    // validate the user input matches an existing product
    while (productNumber > numProducts / 4 || productNumber == 0) {
        cout << "Product # " << productNumber << " does not exist. Try again.\n";
        cout << "Please enter a valid Product number to be selected as a gift: \n";
        cin >> productNumber;
    }
    product += to_string(productNumber);
    cout << product << '\n';
    return product;
}

// Value of Gift function
// Function to get user input on how many reward points gift should be worth.
// Prompt user to input the reward points needed to redeem a gift. 
// Reutrn the reward points needed to purchase gift as a float. 
// Parameters: string of the gift to assign reward value to.
// Return: the reward value as a float.
int valueOfGift(string selectedGift) {
    int giftValue;
    cout << "Please enter the number of reward points needed to redeem ";
    cout << selectedGift << ": ";
    cin >> giftValue;
    return giftValue;
}

// Save Redeemable Gifts function
// Function to save a selected gift and gift value to redeemableGifts.txt
// Parameters: string of the selected gift, float of the giftValue.
// No return values. 
void saveRedeemableGifts(string selectedGift, float giftValue) {
    ofstream myfile("redeemableGifts.txt", ofstream::trunc);
    myfile << selectedGift << " " << giftValue << '\n';
}