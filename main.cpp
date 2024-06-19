#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

struct book {
    int id, total_borrowed, total_quantity;
    string name;

    book() {
        id = -1;
        total_borrowed = total_quantity = 0;
        name = "";
    }

    void add_book(int Id, string Name, int Qoun) {
        id = Id;
        name = Name;
        total_quantity = Qoun;
    }

    bool can_borrow(int user_id) {
        if (total_quantity - total_borrowed <= 0)
            return false;
        total_borrowed++;
        return true;
    }

    void return_book() {
        assert(total_borrowed > 0);
        total_borrowed--;
    }

    bool has_prefix(string prefix) {
        if (name.size() < prefix.size())
            return false;
        for (int i = 0; i < prefix.size(); i++) {
            if (prefix[i] != name[i]) {
                return false;
            }
        }
        return true;
    }

    void print() {
        cout << "id = " << id
             << " : name = " << name
             << " : total borrowed = " << total_borrowed
             << " : total quantity = " << total_quantity << endl;
    }
};

struct user {
    int id, len;
    string name;
    vector<int> borrowed_book_id;

    user() {
        name = "";
        id = -1;
        len = 0;
    }

    void add_user(string Name, int Id) {
        name = Name;
        id = Id;
    }

    void borrow_book(int book_id) {
        borrowed_book_id.push_back(book_id);
    }

    void return_book(int book_id) {
        auto it = find(borrowed_book_id.begin(), borrowed_book_id.end(), book_id);
        if (it != borrowed_book_id.end()) {
            borrowed_book_id.erase(it);
        } else {
            cout << "User " << name << " doesn't have this book id " << book_id << endl;
        }
    }

    bool is_borrowed(int book_id) {
        return find(borrowed_book_id.begin(), borrowed_book_id.end(), book_id) != borrowed_book_id.end();
    }

    void print() {
        cout << "User : " << name << " id: " << id << " borrowed books ids: ";
        for (auto id : borrowed_book_id) {
            cout << id << " ";
        }
        cout << endl;
    }
};

bool cmp_book_by_id(const book& a, const book& b) {
    return a.id < b.id;
}

bool cmp_book_by_name(const book& a, const book& b) {
    return a.name < b.name;
}

struct library_system {
    vector<book> books;
    vector<user> users;
    int total_books, total_users;

    library_system() {
        total_books = 0;
        total_users = 0;
    }

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
                    cout << "*************************************" << endl;
                    cout << "Invalid choice. Please try again.\n";
                    cout << "*************************************" << endl;
            }
        } while (choice != 10);
    }

    void add_book() {
        cout << "Enter book info: id & name & total quantity: ";
        int ID, Qoun;
        string name;
        cin >> ID >> name >> Qoun;
        book new_book;
        new_book.add_book(ID, name, Qoun);
        books.push_back(new_book);
        total_books++;
    }

    void search_book_by_prefix() {
        cout << "Enter Prefix: ";
        string prefix;
        cin >> prefix;
        bool check = false;
        for (int i = 0; i < total_books; i++) {
            if (books[i].has_prefix(prefix)) {
                cout << books[i].name << endl;
                cout << "*************************************" << endl;
                check = true;
            }
        }
        if (!check) {
            cout << "*************************************" << endl;
            cout << "No books with such prefix" << endl;
            cout << "*************************************" << endl;
        }
    }

    void print_who_borrowed_book_by_name() {
        cout << "Enter book name:\n";
        string book_name;
        cin >> book_name;
        int book_idx = find_book_idx_by_name(book_name);
        if (book_idx == -1) {
            cout << "*************************************" << endl;
            cout << " Invalid book name." << endl;
            cout << "*************************************" << endl;
            return;
        }
        int book_id = books[book_idx].id;
        if (books[book_idx].total_borrowed == 0) {
            cout << "*************************************" << endl;
            cout << "No borrowed copies" << endl;
            cout << "*************************************" << endl;
            return;
        }
        for (int i = 0; i < total_users; i++) {
            if (users[i].is_borrowed(book_id)) {
                cout << users[i].name << endl;
            }
        }
    }

    int find_book_idx_by_name(string book_name) {
        for (int i = 0; i < total_books; i++) {
            if (book_name == books[i].name)
                return i;
        }
        return -1;
    }

    void print_library_by_id() {
        sort(books.begin(), books.end(), cmp_book_by_id);
        cout << endl;
        for (int i = 0; i < total_books; i++)
            books[i].print();
    }

    void print_library_by_name() {
        sort(books.begin(), books.end(), cmp_book_by_name);
        cout << endl;
        for (int i = 0; i < total_books; i++)
            books[i].print();
    }

    void add_user() {
        cout << "Enter User Id & name : ";
        int Id;
        string Name;
        cin >> Id >> Name;
        user new_user;
        new_user.add_user(Name, Id);
        users.push_back(new_user);
        total_users++;
    }

    int find_user_idx_by_name(string name) {
        for (int i = 0; i < total_users; i++) {
            if (users[i].name == name) {
                return i;
            }
        }
        return -1;
    }

    bool read_user_name_and_book_name(int &user_idx, int &book_idx, int trials = 3) {
        string user_name, book_name;
        while (trials--) {
            cout << "Enter user name and book name: ";
            cin >> user_name >> book_name;
            user_idx = find_user_idx_by_name(user_name);
            if (user_idx == -1) {
                cout << "*************************************" << endl;
                cout << "Invalid user name. Try again\n";
                cout << "*************************************" << endl;
                continue;
            }
            book_idx = find_book_idx_by_name(book_name);
            if (book_idx == -1) {
                cout << "*************************************" << endl;
                cout << "Invalid book name. Try again\n";
                cout << "*************************************" << endl;
                continue;
            }
            return true;
        }
        cout << "*************************************" << endl;
        cout << "You have exceeded the maximum number of trials. Try again later.\n";
        cout << "*************************************" << endl;
        return false;
    }

    void user_borrow_book() {
        int user_idx, book_idx;
        if (!read_user_name_and_book_name(user_idx, book_idx)) {
            return;
        }
        int user_id = users[user_idx].id;
        int book_id = books[book_idx].id;

        if (!books[book_idx].can_borrow(user_id)) {
            cout << "*************************************" << endl;
            cout << "No more copies available right now\n";
            cout << "*************************************" << endl;
        } else {
            users[user_idx].borrow_book(book_id);
        }
    }

    void user_return_book() {
        int user_idx, book_idx;
        if (!read_user_name_and_book_name(user_idx, book_idx)) {
            return;
        }
        int book_id = books[book_idx].id;
        books[book_idx].return_book();
        users[user_idx].return_book(book_id);
    }

    void print_users() {
        cout << endl;
        for (int i = 0; i < total_users; i++)
            users[i].print();
    }
};

int main() {
    library_system library;
    library.run();
    return 0;
}
