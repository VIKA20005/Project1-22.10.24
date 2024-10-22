#include <iostream>
#include <string>
#include <map>

class Bankomat {
private:
    std::string id;  
    int currentAmount;  
    int minWithdraw; 
    int maxWithdraw;  
    std::map<int, int> bills;  

public:
    
    Bankomat(std::string id, int minWithdraw, int maxWithdraw)
        : id(id), currentAmount(0), minWithdraw(minWithdraw), maxWithdraw(maxWithdraw) {
        
        bills[100] = 0;
        bills[200] = 0;
        bills[500] = 0;
        bills[1000] = 0;
    }


    void loadBills(int denomination, int count) {
        if (bills.find(denomination) != bills.end() && count > 0) {
            bills[denomination] += count;
            currentAmount += denomination * count;
        }
        else {
            std::cout << "Неверный номинал или количество." << std::endl;
        }
    }

    
    bool withdraw(int amount) {
        if (amount < minWithdraw || amount > maxWithdraw) {
            std::cout << "Сумма снятия вне допустимого диапазона." << std::endl;
            return false;
        }

        if (amount > currentAmount) {
            std::cout << "Недостаточно средств в банкомате." << std::endl;
            return false;
        }


        for (auto it = bills.rbegin(); it != bills.rend(); ++it) {
            while (amount >= it->first && it->second > 0) {
                amount -= it->first;
                it->second--;
            }
        }

        if (amount > 0) {
            std::cout << "Невозможно выдать запрашиваемую сумму." << std::endl;
            return false;
        }

        currentAmount -= (maxWithdraw - amount);
        return true;
    }

    
    std::string toString() const {
        return "Остаток в банкомате: " + std::to_string(currentAmount) + " руб.";
    }
};


int main() {
    Bankomat atm("ATM001", 100, 5000);
    atm.loadBills(100, 10);   
    atm.loadBills(500, 5);    

    std::cout << atm.toString() << std::endl;  
    atm.withdraw(700);  
    std::cout << atm.toString() << std::endl;  
    atm.withdraw(600);  
    std::cout << atm.toString() << std::endl;  

    return 0;
}