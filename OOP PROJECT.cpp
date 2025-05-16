#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // for sorting
using namespace std;

// Abstract class for Contact
class Contact {
protected:
    string name;
    string phone;
    string email;

public:
    // Virtual methods for polymorphism
    virtual void inputDetails() = 0; // Pure virtual function (abstraction)
    virtual void displayDetails() const = 0;

    // Encapsulated setters and getters
    void setName(string name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void setPhone(string phone) {
        this->phone = phone;
    }

    string getPhone() const {
        return phone;
    }

    void setEmail(string email) {
        this->email = email;
    }

    string getEmail() const {
        return email;
    }
};

// Derived class for Personal Contact
class PersonalContact : public Contact {
public:
    PersonalContact() {}

    // Function to input details
    void inputDetails() override {
        cout << "Enter Personal Contact Name: ";
        cin >> name;
        cout << "Enter Phone: ";
        cin >> phone;
        cout << "Enter Email: ";
        cin >> email;
    }

    // Function to display details
    void displayDetails() const override {
        cout << "Personal Contact\n";
        cout << "Name: " << name << "\nPhone: " << phone << "\nEmail: " << email << endl;
    }
};

// Derived class for Business Contact
class BusinessContact : public Contact {
private:
    string companyName;
    string jobTitle;

public:
    BusinessContact() {}

    // Input business-specific details
    void inputDetails() override {
        cout << "Enter Business Contact Name: ";
        cin >> name;
        cout << "Enter Phone: ";
        cin >> phone;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Company Name: ";
        cin >> companyName;
        cout << "Enter Job Title: ";
        cin >> jobTitle;
    }

    // Display business-specific details
    void displayDetails() const override {
        cout << "Business Contact\n";
        cout << "Name: " << name << "\nPhone: " << phone << "\nEmail: " << email;
        cout << "\nCompany Name: " << companyName << "\nJob Title: " << jobTitle << endl;
    }

    // Getters and setters for company name and job title
    void setCompanyName(string companyName) {
        this->companyName = companyName;
    }

    string getCompanyName() const {
        return companyName;
    }

    void setJobTitle(string jobTitle) {
        this->jobTitle = jobTitle;
    }

    string getJobTitle() const {
        return jobTitle;
    }
};

// Contact Manager class for file handling and management
class ContactManager {
private:
    vector<Contact*> contacts; // Vector to hold multiple contacts
    string fileName;

public:
    ContactManager(string fileName) {
        this->fileName = fileName;
    }

    // Add contact to memory and file
    void addContact(Contact* contact) {
        contact->inputDetails();
        contacts.push_back(contact);
        saveToFile();
    }

    // Display all contacts
    void displayContacts() {
        if (contacts.empty()) {
            cout << "No contacts available!" << endl;
            return;
        }

        for (size_t i = 0; i < contacts.size(); i++) {
            cout << "\n--- Contact " << i + 1 << " ---\n";
            contacts[i]->displayDetails();
        }
    }

    // Search contact by name
    void searchContact(string searchName) {
        bool found = false;
        for (Contact* contact : contacts) {
            if (contact->getName() == searchName) {
                contact->displayDetails();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Contact not found!" << endl;
        }
    }

    // Edit a contact by name
    void editContact(string searchName) {
        bool found = false;
        for (Contact* contact : contacts) {
            if (contact->getName() == searchName) {
                cout << "Editing contact...\n";
                contact->inputDetails();
                found = true;
                saveToFile();
                cout << "Contact updated successfully!" << endl;
                break;
            }
        }

        if (!found) {
            cout << "Contact not found!" << endl;
        }
    }

    // Delete a contact by name
    void deleteContact(string deleteName) {
        auto it = remove_if(contacts.begin(), contacts.end(), [deleteName](Contact* contact) {
            return contact->getName() == deleteName;
        });

        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            saveToFile();
            cout << "Contact deleted successfully!" << endl;
        } else {
            cout << "Contact not found!" << endl;
        }
    }

    // Save contacts to file
    void saveToFile() {
        ofstream outFile(fileName);
        for (Contact* contact : contacts) {
            outFile << contact->getName() << " " << contact->getPhone() << " " << contact->getEmail() << endl;
        }
        outFile.close();
    }

    // Load contacts from file
    void loadFromFile() {
        ifstream inFile(fileName);
        string name, phone, email;

        while (inFile >> name >> phone >> email) {
            PersonalContact* contact = new PersonalContact();
            contact->setName(name);
            contact->setPhone(phone);
            contact->setEmail(email);
            contacts.push_back(contact);
        }
        inFile.close();
    }

    // Sort contacts by name
    void sortContacts() {
        sort(contacts.begin(), contacts.end(), [](Contact* a, Contact* b) {
            return a->getName() < b->getName();
        });
        cout << "Contacts sorted by name!" << endl;
    }

    // Destructor to release memory
    ~ContactManager() {
        for (Contact* contact : contacts) {
            delete contact;
        }
    }
};

// Main function
int main() {
    ContactManager manager("contacts.txt");

    manager.loadFromFile();

    int choice;
    string name;
    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Add Personal Contact\n";
        cout << "2. Add Business Contact\n";
        cout << "3. View Contacts\n";
        cout << "4. Search Contact\n";
        cout << "5. Edit Contact\n";
        cout << "6. Delete Contact\n";
        cout << "7. Sort Contacts\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Contact* personal = new PersonalContact();
            manager.addContact(personal);
            break;
        }
        case 2: {
            Contact* business = new BusinessContact();
            manager.addContact(business);
            break;
        }
        case 3:
            manager.displayContacts();
            break;
        case 4:
            cout << "Enter name to search: ";
            cin >> name;
            manager.searchContact(name);
            break;
        case 5:
            cout << "Enter name to edit: ";
            cin >> name;
            manager.editContact(name);
            break;
        case 6:
            cout << "Enter name to delete: ";
            cin >> name;
            manager.deleteContact(name);
            break;
        case 7:
            manager.sortContacts();
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 8);

    return 0;
}

