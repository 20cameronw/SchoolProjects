#include "rewards.h"

// Main function
// rewardManagement function asks user for number of points awarded for a given shopping amount. 
// Get the products available, and print them to the user. Use this function to count how many products exist.
// Have the manager select a gift, store their input as a string selectedGift.
// Have the manager select the value needed to purchase product as a gift in reward points.
// Save the redeemable gift in file redeemableGifts.txt
// After the manager has entered at least one redeemable gift, continue looping
// until the manager inputs 0 to add stop the process of addingredeemable gifts. 
// No parameters.
// Return 0 on program end. 
int main() {
    rewardManagement();
    getProducts();
    
    int response = 1; // 1 is True, 0 is False
    string selectedGift = selectGift();
    float giftValue = valueOfGift(selectedGift);
    saveRedeemableGifts(selectedGift, giftValue);
    while(response == 1){
        cout << "Would you like to add another gift to the list of redeemable gifts?\n";
        cout << "Enter (1) for Yes, enter (0) for No, and exit.\n";
        cin >> response;
        if(response == 1){
            string selectedGift = selectGift();
            float giftValue = valueOfGift(selectedGift);
            saveRedeemableGifts(selectedGift, giftValue);
        }
    }
    return 0;
}