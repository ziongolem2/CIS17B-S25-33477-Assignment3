// Saul Resendiz
// CIS-17B
// Lesson 3 Assignment

#include <iostream>
#include <memory>
#include <stdexcept>

// creating our exception custom classes
class NegativeDepositException : public std::runtime_error 
{
public:
    NegativeDepositException() : std::runtime_error("Cant enter negative amount.") {}
};

class OverdrawException : public std::runtime_error 
{
public:
    OverdrawException() : std::runtime_error("Error. Withdraw amount exceeding balance!") {}
};

class InvalidAccountOperationException : public std::runtime_error 
{
public:
    InvalidAccountOperationException() : std::runtime_error("Cannot perform on closed account!") {}
};

class BankAccount 
{
    // PRIVATE MEMBERS
private:
    std::string accountNumber;
    double balance;
    bool isActive;

public:
    // Creating BankAccount constructor and initializing its acc number, balance, and active status
    BankAccount(const std::string& accNumber, double initbalance) : accountNumber(accNumber), balance(initbalance), isActive(true) {}

    void deposit(double amount) // DEPOSIT
    {
        if (!isActive) {  // If the account is closed - throwing exception
            throw InvalidAccountOperationException();
        }
        if (amount < 0) {  // If depositing less than $0, throw 
            throw NegativeDepositException();
        }
        balance += amount;  // adding the deposit amount to our account balance
    }

    void withdraw(double amount) // WITHDRAW 
    {
        if (!isActive) {  // If the accoutn is closed- throwing exception
            throw InvalidAccountOperationException();
        }
        if (amount > balance) {  // If the user withdraws more than their account balance, throw
            throw OverdrawException();
        }
        balance -= amount;  // Otherwise, subtract the user's account balance by the amount withdrawn
    }

    // Method to get current balance
    double getBalance() const 
    {
        return balance; // RETRIEVES USERS CURRENT BALANCE
    }
    
    void closeAccount() 
    {  // Closes Users account - transactions should raise errors afterwards
        isActive = false;
    }
};

int main() {
    try {
        // Intializing users bank account starting balance
        double startBalance;
        std::cout << "Enter initial deposit: ";
        std::cin >> startBalance;
        
        // Using smartpointer for creating the users account 
        auto userBankAcc = std::make_unique<BankAccount>("99", startBalance);
        std::cout << "Account created successfully!" << std::endl;

        // DEPOSITING MONEY
        std:: cout << "Enter amount to deposit: ";
        double userDepositAmount;
        std::cin >> userDepositAmount;
        userBankAcc->deposit(userDepositAmount);  // Depositing the amount user input 

        // WITHDRAW MONEY
      std::cout << "Enter amount to withdraw: ";
      double userWithdrawAmount;
      std::cin >> userWithdrawAmount;
      userBankAcc->withdraw(userWithdrawAmount);  // Withdrawing user input amount
      
      // CHECK BALANCE
      std::cout << "Current Account Balance: $" << userBankAcc->getBalance() << std::endl;

    // DISPLAIYNG EXCEPTION HANDLING TESTS:
    
    try 
    {   // Overdrawing to demonstrate exception handling
    std::cout << "Clear Overdrawing test: WITHDRAWING $9999!" << std::endl;
    userBankAcc->withdraw(9999); // Should throw 
} catch (const OverdrawException& e) {
    std::cerr << "OverdrawException: " << e.what() << std::endl;
}
     
     // Depositing negative amount to demonstrate exception handling
    try 
    {
    userBankAcc->deposit(-200);  // Should throw 
} catch (const NegativeDepositException& e) {
    std::cerr << "NegativeDepositException: " << e.what() << std::endl;
}

     // Closing users bank account to further demonstrate exception handling
     std::cout << "CLOSING ACCOUNT!" << std::endl;
     userBankAcc->closeAccount();

       // Depositing money into a closed users bank account to demonstrate exception handling
    try 
    {
    std::cout << "Depositing $100 into closed bank account!" << std::endl;
    userBankAcc->deposit(100); // Should throw 
} catch (const InvalidAccountOperationException& e) {
    std::cerr << "InvalidAccountOperationException: " << e.what() << std::endl;
}

// CATCH BLOCKS IN OUR PROGRAM
    } catch (const NegativeDepositException& e) {
        std::cerr << "NegativeDepositException: " << e.what() << std::endl;
    } catch (const OverdrawException& e) {
        std::cerr << "OverdrawException: " << e.what() << std::endl;
    } catch (const InvalidAccountOperationException& e) {
        std::cerr << "InvalidAccountOperationException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General Exception: " << e.what() << std::endl;
    }

    return 0;   // END OF PROGRAM
}
