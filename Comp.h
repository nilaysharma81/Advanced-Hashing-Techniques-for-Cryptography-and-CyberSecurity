#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    void ms(std::vector<int>& v, int l,int r);
    void merge(std::vector<int>& v, int l,int m, int r);
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
int dbs=0;
bool univ=true;
    
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
