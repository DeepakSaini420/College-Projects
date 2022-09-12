#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <ctime>
using namespace std;

class Employee{
    int employeeId;
    string employeeName;
    string employeeDesignation;
    string employeePassword;
};

class Transaction{
    public:
        int transactionId;
        int Amount;
        int dateTime;   
        string fromAccount;
        string toAccount;
};

class Account{
    int accountNumber;
    int totalCredit;
    int minReqAmount{2000};
    vector<Transaction> transactions;
    public:
        void addAccount(int accountId){
            this->accountNumber=accountId;
            cout << "Please Credit Some Money:-";
            int intialCredit{0};
            cin >> intialCredit;
            while(intialCredit<minReqAmount){
                cout << "Please Credit at least 2000rs"<<endl;
                cin >> intialCredit;
            }
            this->totalCredit=intialCredit;
        }
        int getAccountNumber(){
            return accountNumber; 
        }
        void dipositAmount(int accountNo=0){
            int amount{0};
            cin >> amount;
            this->totalCredit +=amount;
            cout << "Amount Deposited Successfully"<<endl;
            if(accountNo==0){
                Transaction t;
                t.transactionId = accountNumber++;
                t.fromAccount = "Money";
                t.toAccount = this->accountNumber;
                t.Amount=amount;
                transactions.push_back(t);
            }else{
                Transaction t;
                t.transactionId = accountNo++;
                t.fromAccount = accountNo;
                t.toAccount = this->accountNumber;
                t.Amount = amount;
                transactions.push_back(t);
            }
        }

        void debitAmount(int accountNo=0){
            int amount{0};
            cin >> amount;
            while(totalCredit-amount<minReqAmount){
                cout << "Please Enter Some Less Value"<<endl;
                cin >> amount; 
            }
            this->totalCredit -= amount;
            if(accountNo==0){
                Transaction t;
                t.transactionId = accountNumber++;
                t.fromAccount = this->accountNumber;
                t.toAccount = "ATM";
                t.Amount=amount;
                transactions.push_back(t);
            }else{
                Transaction t;
                t.transactionId = accountNo++;
                t.fromAccount = this->accountNumber;
                t.toAccount = accountNo;
                t.Amount = amount;
                transactions.push_back(t);
            }
        }
        int getTotalCredit(){
            return totalCredit;
        }
        void printTransctions(){
            if(transactions.size()==0) {
                cout << "Transactions:- Null"<<endl;
                return;
            }
            cout << 'Transactions:-[' << endl;
            for(auto x:transactions){
                cout << "              {"<<endl;
                cout << "                   Transaction Id:- "<<x.transactionId<<endl;
                cout << "                   Amount:- "<<x.Amount<<endl;
                cout << "                   From Account:- "<<x.fromAccount<<endl;
                cout << "                   To Account:- "<<x.toAccount<<endl;
                cout << "              },"<<endl;
            }
            cout << ']' << endl;
        }
        friend ostream& operator<<(ostream &o,Account &acc);
};

ostream& operator<<(ostream &o,Account &acc){
    cout << "Account No:- "<< acc.getAccountNumber()<<endl;;
    cout << "Total Amount:- "<<acc.getTotalCredit()<<endl;
    acc.printTransctions();
    return o;
}

class Customer{
    int customerId;
    string customerName;
    string customerPassword;
    public:
        void addCustomer(int id){
            this->customerId = id;
            cin.ignore();
            cout << "Enter Your Full Name:- ";
            string name;
            string password;
            getline(cin,name);
            while(true){
                string cPassword;
                cout << "Enter Your New Password:-";
                getline(cin,password);
                getline(cin,cPassword);
                if(password==cPassword) break;
            }
            this->customerName=name;
            this->customerPassword=password;
        }
        void setCustomerPassword(string password){
            this->customerPassword=password;
        }
        string getCustomerName(){
            return this->customerName;
        }
        int getCustomerId(){
            return this->customerId;
        }
        bool checkPassword(string password){
            return this->customerPassword==password;
        }
};

int getCustomer(vector<Customer> customers,int id){
    /* 
        This Funcion Accept Vector or array of Customer and returns index of a customer
        This Fuction Use Binary Search to find index of a customer because its complexity is o(log n)
        which is better than linear search o(n)
     */
    int s=0;
    int e=customers.size()-1;

    // Implimentation of binary search in customers array
    while (s<=e)
    {
        int mid = (s+e)/2;
        if(customers[mid].getCustomerId()==id){
            return mid;
        }else if(customers[mid].getCustomerId()>id){
            e = mid-1;
        }else{
            s = mid+1;
        }
    }
    

    return -1;
}

void printAccounts(vector<Account> Accounts){
    for(int i=0;i<Accounts.size();i++){
        cout << Accounts[i]<<endl;
    }
}

void start(unordered_map<int,vector<Account>> customerDataBase,vector<Customer> customers,int id,int accountId){
    while(true){
        int option{0};
        cout <<endl;
        cout << "   MAIN MENU:-       "<<endl;
        cout <<endl;
        cout << "1) EMPLOYEE" <<endl;
        cout << "2) CUSTOMER"<<endl;
        cout << endl;
        cout << "Enter Your Options:-";
        cin >> option;
        if(option==1){

        }else if(option==2){
            int opt{0};
            cout << "   CUSTOMER MENU:-"<<endl;
            cout << "1) MAKE AN ACCOUNT"<<endl;
            cout << "2) LOGIN IN"<<endl;
            cout << endl;
            cout << "Enter Your Option:-";
            cin >> opt;
            if(opt==1){
                int customerId{0};
                cout << "Enter Customer Id If Have:-";
                cin >> customerId;
                if(customerId!=-1){
                    Account a;
                    a.addAccount(++accountId);
                    customerDataBase[customerId].push_back(a);
                }else{
                    Customer c;
                    c.addCustomer(++id);
                    Account a;
                    a.addAccount(++accountId);
                    customers.push_back(c);
                    customerDataBase[id] = vector<Account>();
                    customerDataBase[id].push_back(a);
                }
                cout << "Account Added Successfully!"<<endl;
            }else if(opt==2){
                int id;
                cin.ignore();
                cout << "Enter Customer Id:-"<<endl;
                cin >> id;
                int index = getCustomer(customers,id);
                cout << index <<endl;
                if(index>=0){
                    string password;
                    int p{0};
                    cout << "Enter Your Password:- ";
                    cin.ignore();
                    getline(cin,password);
                    while(!customers[index].checkPassword(password)){
                        cout << "Please Enter Correct Password:-";
                        getline(cin,password);
                    }
                    /*TASK:- IMPLEMENT FUNCTIONALITY A CUSTOMER CAN ADD MONEY WIDTHDRAW TRANSFER UPDATE ITS PASSWORD SHOW TRANSCATIONS*/
                    int accNo;
                    printAccounts(customerDataBase[customers[index].getCustomerId()]);
                    cout << "Enter Account No:-";
                    cin >> accNo;
                }else{
                    cout << "No Customer Found!"<<endl;
                }
            }
        }else{
            for(int i=0;i<customers.size();i++){
                cout << customers[i].getCustomerId()<<endl;
            }
            cout << "Thank For Chossing Us!" <<endl;
            break;
        }
    }
}




int main(){
    unordered_map<int,vector<Account>> customerDataBase;
    vector<Customer> customers;
    int id{0},accountId{0};
    start(customerDataBase,customers,id,accountId);
    return 0;
}