#include <bits/stdc++.h>

using namespace std;

struct book{
    int id,total_borrowed,total_quantity;
    string name;

    book(){
        id=-1;
        total_borrowed=total_quantity=0;
        name="";
    }

    void add_book(){
        cout << "Enter book info: id & name & total quantity: ";
        cin>>id;
        cin.ignore();
        getline(cin, name);
        cin>>total_quantity;
        total_borrowed=0;
    }
    bool can_borrow(int user_id){
        if(total_quantity-total_borrowed<=0)return false;
        total_borrowed+=1;
        return true;
    }
    void return_book(){
        assert(total_borrowed>0);
        total_borrowed-=1;
    }
    bool has_prefix(string prefix){
        if(name.size()> prefix.size())return false;
        for(int i=0;i<prefix.size();i++){
            if(prefix[i]!=name[i]){
                return false;
            }
        }
        return true;
    }
    void print(){
        cout<< "id = "<<id
            << "name = "<<name
            <<"total borrowed = "<<total_borrowed
            <<"total quantity = "<<total_quantity<<endl;
    }
};

struct user{
    int id,len;
    string name;
    vector<int>borrowed_book_id;
    user(){
        name="";
        id=-1;
        len=0;
    }
    void add_user(){
        cout<<"Enter User name &Id: ";
        cin>>name>>id;
    }
    void borrow_book(int book_id){
        borrowed_book_id[len++]=book_id;
    }
    void return_book(int book_id){
        bool removed=true;
        for(int i=0;i<len;i++){
            if(book_id==borrowed_book_id[i]){
                for(int j=i+1;j<len;j++){
                    borrowed_book_id[j-1]=borrowed_book_id[j];
                }
                removed=true;
                len--;
                break;
            }
        }
        if(!removed){
            cout<<"User "<<name <<"dosn`t get this book id "<<book_id;
        }

    }
    bool is_borrowed(int book_id){
        auto it=find(borrowed_book_id.begin(),borrowed_book_id.end(),book_id);
        if(it!=borrowed_book_id.end())return true;
        return false;
    }
    void print(){
        cout<<"User : "<<name<<" id: "<<id<<"borrowed books ids: ";
        for(auto it:borrowed_book_id)cout<<it<<" ";
        cout<<endl;
    }
};
bool cmp_book_by_id(book a,book b){
    return a.id<b.id;
}
bool cmp_book_by_name(book a,book b){
    return a.name<b.name;
}


struct library_system {
    vector<book> books;
    vector<user> users;
    int total_books,total_users;

    int menu() {
        cout << "\nLibrary Menu:\n";
        cout << "1) Add Book\n";
        cout << "2) Search Books by Prefix\n";
        cout << "3) Print Users Who Borrowed a Book by Name\n";
        cout << "4) Print Library by ID\n";
        cout << "5) Print Library by Name\n";
        cout << "6) Add User\n";
        cout << "7) User Borrow Book\n";
        cout << "8) User Return Book\n";
        cout << "9) Print Users\n";
        cout << "10) Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        return choice;
    }

    void run() {
        int choice;
        do {
            choice = menu();
            switch (choice) {
                case 1:
                    add_book();
                    break;
                case 2:
                    search_book_by_prefix();
                    break;
                case 3:
                    print_who_borrowed_book_by_name();
                    break;
                case 4:
                    print_library_by_id();
                    break;
                case 5:
                    print_library_by_name();
                    break;
                case 6:
                    add_user();
                    break;
                case 7:
                    user_borrow_book();
                    break;
                case 8:
                    user_return_book();
                    break;
                case 9:
                    print_users();
                    break;
                case 10:
                    cout << "Exiting the program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 10);
    }

    void add_book(){
        books[total_books++].add_book();
        return;
    }

    void search_book_by_prefix(){
        cout<<"Enter Prefix"<<endl;
        string prefix;cin>>prefix;
        bool check=false;
        for(int i=0;i<total_books;i++){
            if(books[i].has_prefix(prefix)){
                cout<<"*************************************"<<endl;
                cout<<books[i].name<<endl;
                cout<<"*************************************"<<endl;
                check=true;
            }
        }
        if(!check){
            cout<<"*************************************"<<endl;
            cout<<"No books with such prefix"<<endl;
            cout<<"*************************************"<<endl;
        }
        return;
    }

    void print_who_borrowed_book_by_name(){
        cout<<"Enter book name:\n";
        string book_name;cin>>book_name;
        int book_idx=find_book_idx_by_name(book_name);
        if(book_idx==-1){
            cout<<" Invalid book name."<<endl;
            return;
        }
        int book_id=books[book_idx].id;
        if(books[book_idx].total_borrowed==0){
            cout<<"No borrowed copies"<<endl;
            return;
        }
        for(int i=0;i<total_users;i++){
            if(users[i].is_borrowed(book_id)){
                cout<<users[i].name<<endl;
            }
        }
        return;
    }

    int find_book_idx_by_name(string book_name){
        for(int i=0;i<total_books;i++){
            if(book_name==books[i].name)
                return i;
        }
        return -1;
    }

    void print_library_by_id(){
        sort(books.begin(),books.end(),cmp_book_by_id);
        cout<<endl;
        for(int i=0;i<total_books;i++)
            books[i].print();
    }
    void print_library_by_name(){
        sort(books.begin(),books.end(),cmp_book_by_name);
        cout<<endl;
        for(int i=0;i<total_books;i++)
            books[i].print();
    }
    void add_user(){}
    void user_borrow_book(){}
    void user_return_book(){}
    void print_users(){}
};

int main() {
    library_system library;
    library.run();
}
