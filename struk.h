#pragma once
const int N = 20;

struct Customer {
    float creditInterest;
    float depositAmount;
    float creditBalance;
};

struct Building {
    Customer cust;
    int buildingType;
    float price;
    char subcontra[N];
};
