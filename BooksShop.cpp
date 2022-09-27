// Credits:- Deepak Saini (2010991247)
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/*
	Before Running Code made a txt file named admin.txt in directory where you have .exe file and enter your
	desired username and password like:-
		admin
		password
*/
class Book{
	/*
		This Book Class Have Attribute of Book contains following attributes:-
		1. Name of Book
		2. Publisher Name
		3. Author Name
		4. Price of Book
		5. Stock of Book
		
		It also have member function which use to get and set these Values
	*/
	string nameOfBook;
	string publisher;
	int price;
	int stock;
	public:
		void addPrice(int price){
			this->price=price;
		}
		void addName(string name){
			this->nameOfBook = name;
		}
		void addPublisherName(string name){
			this->publisher=name;
		}
		void setStockOfBook(int stock){
			this->stock=stock;
		}
		string getNameOfBook(){
			return this->nameOfBook;
		}
		string getPublisherName(){
			return this->publisher;
		}
		int getPrice(){
			return this->price;
		}
		int getStock(){
			return this->stock;
		}
		// Here We are doing operator overloading to print our book object using << operator
		friend ostream& operator<<(ostream& o,Book &b);
};

// This is output << overloaded function to print book
ostream& operator<<(ostream& o,Book &b){
	cout << "Name:- "<<b.getNameOfBook()<<endl;
	cout << "Author:- "<<b.getPublisherName()<<endl;
	cout << "Price:- "<< b.getPrice()<<endl;
	cout << "Stock:- "<<b.getStock()<<endl;
	return o;
}

bool addBook(Book &b,int stock,vector<Book> &books){
	/*
		This Function Accept Three arguments:-
		1. Book object Refrence.
		2. Stock of Book.
		3. Customer Book array
		
		This Function Check if the stock present in the shop or not
		if it is not present it return a boolean value of false or 
		if it is present it return a boolean value of true
	*/
	if(b.getStock()>=stock){
		
		// Updating the stock of book in shop
		b.setStockOfBook(b.getStock()-stock);
		
		// Creating a new book object bk to append this object to the customer cart
		Book bk;
		bk.addName(b.getNameOfBook());
		bk.addPrice(b.getPrice());
		bk.addPublisherName(b.getPublisherName());
		bk.setStockOfBook(stock);
		
		// appending book to our array
		books.push_back(bk);
		return true;
	}else{
		return false;
	}
}


int getTotalPrice(vector<Book> &books){
	/*
		This function accept a vector of Book and calculate
		price of the books and return that price
	*/
	int total{0};
	for(int i=0;i<books.size();i++){
		total = total + books[i].getPrice() * books[i].getStock();
	}
	return total;
}

void printBooks(vector<Book> &books){
	// This function print Books of the customer
	for(int i=0;i<books.size();i++){
		cout << "====================="<<endl;
		cout << books[i];
		cout << "====================="<<endl;
	}
	cout <<'\n'<<endl;
}


void printBill(vector<Book> &books,ofstream &myfile1){
	// This function print bill of the customer and update bill.txt file
	int total = getTotalPrice(books);
	for(int i=0;i<books.size();i++){
		cout << "====================="<<endl;
		cout << books[i];
		cout << "====================="<<endl;
		myfile1 <<"==================================="<<'\n';
		myfile1 << "Name:- "<< books[i].getNameOfBook() <<'\n';
		myfile1 << "Publisher:- "<< books[i].getPublisherName() <<'\n';
		myfile1 << "Price:- "<< books[i].getPrice() <<'\n';
		myfile1 << "Stock:- "<< books[i].getStock() <<'\n';
		myfile1 <<"==================================="<<'\n';
	}
	cout <<'\n'<<endl;
	cout << "Total Price:- "<<total <<endl;
	myfile1 << "Total Price:- "<< total <<'\n';
}

bool isBookPresent(vector<Book> &shopBook,string Name,int stock){
	/*
		Check if book present in array or not
		return True if Book already prenset and return false if book is not present
	*/
	for(int i=0;i<shopBook.size();i++){
		if(shopBook[i].getNameOfBook()==Name){
			shopBook[i].setStockOfBook(shopBook[i].getStock()+stock);
			return true;
		}
	}
	return false;
}

void deleteBook(vector<Book> &customerCart,vector<Book> &shopBook){
	/*
		This Function Take's Two input Customer Cart vector and shopBook vector
		Working:-
			This Function Take input from user to enter name of book
			if book present in cart it will use erase function of vector
			and delete that element from the vector and update stock variable 
			and after that our function itrate over shoopBook vector and add
			deleted book stock to shopBook stock array
	*/
	if(customerCart.size()==0){
		cout << "Please Add Some Books in Cart!"<<endl;
	}
	cin.ignore(1,'\n');
	cout << "Enter Name of Book:-";
	string nameOfBook;
	getline(cin,nameOfBook);
	int idx{-INT_MAX},stock{0};
	for(int i=0;i<customerCart.size();i++){
		if(customerCart[i].getNameOfBook()==nameOfBook){
			stock = customerCart[i].getStock();
			customerCart.erase(customerCart.begin()+i);
			idx=i;
			break;
		}
	}
	for(int i=0;i<shopBook.size();i++){
		if(shopBook[i].getNameOfBook()==nameOfBook){
			shopBook[i].setStockOfBook(shopBook[i].getStock()+stock);
		}
	}
	cout << "Book Deleted From Cart!"<<endl;
}

bool isOwner(string username,string password){
	/*
		This Function read admin.txt or credentials file
		Working:-
			In this function we are reading a file line by line
			and adding a line in tp string and comparing string with 
			username and password that we inputed if check is incremented
			by 2 and if our check is 2 it means we are legit person to access
			and return true and if check is less than 2 it return false
	*/
	fstream newfile;
	newfile.open("admin.txt",ios::in);
	int check{0};
	if(newfile.is_open()){
      	string tp;
      	while(getline(newfile, tp)){
        	if(tp==username){
        		check++;
			}if(tp==password){
				check++;
			}
      	}
	}
	newfile.close(); 
	if(check==2){
		return true;
	}else{
		return false;
	}
}

void startProgram(vector<Book> &shopBook,vector<Book> &customerCart){
	ofstream myfile1;
	myfile1.open("bill.txt");
	while(true){
		int type{0};
		bool flag{false};
		cout << "========================"<<endl;
		cout << "1) Shop Onwer"<<endl;
		cout << "2) Customer"<<endl;
		cout << "========================"<<endl;
		cout << "Enter Number:- ";
		cin >> type;
		if(type<0){
			cout << "Please Enter a valid input"<<endl;
		}else if(type==1){
			string userName,Password;
			cout <<endl;
			cin.ignore(1,'\n');
			cout << "Enter Username of Admin:- ";
			getline(cin,userName);
			cout << "Enter Password of Admin:- ";
			getline(cin,Password);
			// Checking is Shopkeeper is Real or someone else
			if(!isOwner(userName,Password)){
				cout << "Please Enter Correct Credentials!"<<endl;
				break;
			}
			while(true){
				int x{0};
				cout << "=========================================="<<endl;
				cout << "1) Add Book to shop"<<endl;
				cout << "2) Show Books"<<endl;
				cout << "3) Enter any another key to go main Menu"<<endl;
				cout << "=========================================="<<endl;
				cout << "Enter A Number:-";
				cin >> x;
				if(x==1){
					/*
						We are Creating Book object bk and then we getting input Name of book,publisher Name and author name,price,stock.
						* if price of book is less than 1 we are printing message Enter Price of book.
						* if stock is less than or equal to zero it display a message "Enter Valid Stock"
						* if everythong is fine add these value to book object and then push back that object to shopBook array
						* if book is already Present in our Shop array just update the stock of book
					*/
					Book bk;
					string nameOfBook,publisherName;
					int price,stock;
					cin.ignore(1,'\n');
					cout << "Enter Name of Book:- ";
					getline(cin,nameOfBook);
					cout << "Enter Name of Author:- ";
					getline(cin,publisherName);
					cout << "Enter Price of Book:- ";
					cin >> price;
					if(price<1){
						cout << "Enter Valid Price"<<endl;
						continue;
					}
					cout << "Enter Stock of Books:- ";
					cin >> stock;
					if(stock<=0){
						cout << "Enter Valid Stock:- ";
						continue;
					}
					bk.addName(nameOfBook);
					bk.addPrice(price);
					bk.addPublisherName(publisherName);
					bk.setStockOfBook(stock);
					shopBook.push_back(bk);
				}else if(x==2){
					// This Function Print Books present in a shop
					if(shopBook.size()==0){
						cout << "Please Add Some Books"<<endl;
						continue;
					}
					printBooks(shopBook);
				}else{
					break;
				}
			}
		}else if(type==2){
			while(true){
				int x{0};
				cout << "============================="<<endl;
				cout << "1) Get A Book"<<endl;
				cout << "2) Get Total Price"<<endl;
				cout << "3) Get Total Bill"<<endl;
				cout << "4) Clear Cart"<<endl;
				cout << "5) Delete A Book"<<endl;
				cout << "============================="<<endl;
				cout << "Enter A Number:-";
				cin >> x;
				if(x==1){
					string nameOfBook;
					int stock{0};
					cin.ignore(1,'\n');
					cout << "Enter Name of Book:- ";
					getline(cin,nameOfBook);
					cout << "Enter Stock:- ";
					cin >> stock;
					for(int i=0;i<shopBook.size();i++){
							if(shopBook[i].getNameOfBook()==nameOfBook){
								if(addBook(shopBook[i],stock,customerCart)){
									cout << "Book Added!"<<endl;
								}else{
									cout << "Book is out of stock"<<endl;
								}
							}
					}
				}else if(x==2){
					if(customerCart.size()==0){
						cout << "Please Add Some Books in Cart!"<<endl;
					}else{
						cout << "Total Price:- "<<getTotalPrice(customerCart) <<endl;
					}
				}else if(x==3){
					if(customerCart.size()==0){
						cout << "Please Add Some Books in Cart!"<<endl;
					}else{
						deleteBook(customerCart,shopBook);
						printBill(customerCart,myfile1);
					}
				}else if(x==4){
					if(customerCart.size()==0){
						cout << "Please Add Some Books in Cart!"<<endl;
					}else{
						
						customerCart.clear();
					}
				}else if(x==5){
				}else{
					break;
				}
			}
		}else{
			cout << "=============================="<<endl;
			cout << "Thank You For Shopping With Us"<<endl;
			cout << "=============================="<<endl;
			myfile1.close();
			break;
		}
	}
}


int main(){
	vector<Book> shopBook;
	vector<Book> customerCart;
	startProgram(shopBook,customerCart);
	return 0;
}
