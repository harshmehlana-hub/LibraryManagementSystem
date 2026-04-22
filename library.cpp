#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool available;
    Book* left;
    Book* right;

    Book(int bookId, string bookTitle, string bookAuthor) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        available = true;
        left = right = nullptr;
    }
};

// Insert book into BST
Book* insertBook(Book* root, int id, string title, string author) {
    if (root == nullptr) return new Book(id, title, author);

    if (id < root->id) root->left = insertBook(root->left, id, title, author);
    else if (id > root->id) root->right = insertBook(root->right, id, title, author);
    else cout << "Book with ID " << id << " already exists!\n";

    return root;
}

// Search book by ID
Book* searchBook(Book* root, int id) {
    if (root == nullptr || root->id == id) return root;
    if (id < root->id) return searchBook(root->left, id);
    return searchBook(root->right, id);
}

// Display all books (inorder traversal)
void displayBooks(Book* root) {
    if (root == nullptr) return;
    displayBooks(root->left);
    cout << "ID: " << root->id << ", Title: " << root->title
         << ", Author: " << root->author
         << ", Status: " << (root->available ? "Available" : "Issued") << "\n";
    displayBooks(root->right);
}

// Issue book
bool issueBook(Book* root, int id) {
    Book* book = searchBook(root, id);
    if (!book) { cout << "Book not found.\n"; return false; }
    if (!book->available) { cout << "Book already issued.\n"; return false; }
    book->available = false;
    cout << "Book issued: " << book->title << "\n";
    return true;
}

// Return book
bool returnBook(Book* root, int id) {
    Book* book = searchBook(root, id);
    if (!book) { cout << "Book not found.\n"; return false; }
    if (book->available) { cout << "Book already available.\n"; return false; }
    book->available = true;
    cout << "Book returned: " << book->title << "\n";
    return true;
}

// Find minimum node (helper for deletion)
Book* findMin(Book* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

// Delete book
Book* deleteBook(Book* root, int id) {
    if (root == nullptr) return root;

    if (id < root->id) root->left = deleteBook(root->left, id);
    else if (id > root->id) root->right = deleteBook(root->right, id);
    else {
        if (root->left == nullptr) {
            Book* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Book* temp = root->left;
            delete root;
            return temp;
        } else {
            Book* temp = findMin(root->right);
            root->id = temp->id;
            root->title = temp->title;
            root->author = temp->author;
            root->available = temp->available;
            root->right = deleteBook(root->right, temp->id);
        }
    }
    return root;
}

// Update book
bool updateBook(Book* root, int id, string newTitle, string newAuthor) {
    Book* book = searchBook(root, id);
    if (!book) { cout << "Book not found.\n"; return false; }
    book->title = newTitle;
    book->author = newAuthor;
    cout << "Book updated successfully.\n";
    return true;
}

// Menu-driven program
int main() {
    Book* root = nullptr;
    int choice, id;
    string title, author;

    do {
        cout << "\n--- Library Menu ---\n";
        cout << "1. Add Book\n2. Display Books\n3. Search Book\n4. Issue Book\n5. Return Book\n6. Delete Book\n7. Update Book\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID: "; cin >> id;
                cin.ignore();
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Author: "; getline(cin, author);
                root = insertBook(root, id, title, author);
                break;
            case 2:
                cout << "\nBooks in Library:\n";
                displayBooks(root);
                break;
            case 3:
                cout << "Enter ID to search: "; cin >> id;
                {
                    Book* book = searchBook(root, id);
                    if (book) cout << "Found: " << book->title << " by " << book->author << "\n";
                    else cout << "Book not found.\n";
                }
                break;
            case 4:
                cout << "Enter ID to issue: "; cin >> id;
                issueBook(root, id);
                break;
            case 5:
                cout << "Enter ID to return: "; cin >> id;
                returnBook(root, id);
                break;
            case 6:
                cout << "Enter ID to delete: "; cin >> id;
                root = deleteBook(root, id);
                break;
            case 7:
                cout << "Enter ID to update: "; cin >> id;
                cin.ignore();
                cout << "Enter new Title: "; getline(cin, title);
                cout << "Enter new Author: "; getline(cin, author);
                updateBook(root, id, title, author);
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}
