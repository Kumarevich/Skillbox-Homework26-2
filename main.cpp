#include <iostream>
#include <map>
#include <string>

class Contact {
    std::string name;
    std::string phoneNumber;
    friend class Phone;

    bool setNumber(std::string number) {
        for (int i = 0; i < number.length(); ++i) {
            if (number[i] < 48 || number[i] > 57) return 0;
        }
        phoneNumber = "+7" + number;
        return 1;
    }
};

class Phone {
    std::map<std::string, std::string> nameContacts;
    std::map<std::string, std::string> phoneContacts;

    bool checkingNumber(std::string check) {
        if (check[0] == 43) {
            for (int i = 1; i < check.length(); ++i) {
                if (check[i] < 48 || check[i] > 57) return 0;
            }
        } else {
            return 0;
        }
        return 1;
    }

    bool checkingRequest(std::string finder, Contact* callingContact) {
        std::map<std::string, std::string>::iterator it;
        if (checkingNumber(finder)) {
            it = phoneContacts.find(finder);
            if (it != phoneContacts.end()) {
                callingContact->name = it->second;
                callingContact->phoneNumber = it->first;
                return true;
            }
        } else {
            it = nameContacts.find(finder);
            if (it != nameContacts.end()) {
                callingContact->name = it->first;
                callingContact->phoneNumber = it->second;
                return true;
            }
        }
        return false;
    }

  public:
    void add() {
        Contact* newContact = new Contact();
        std::cout << "Input a new Contact name: ";
        std::getline(std::cin, newContact->name);
        std::cout << "Input a new Contact number +7: ";
        std::string inputNumber;
        std::getline(std::cin, inputNumber);
        while (!newContact->setNumber(inputNumber)) {
            std::cout << "Wrong input. Try again.";
            std::getline(std::cin, inputNumber);
        }
        nameContacts.insert(std::pair<std::string,std::string> (newContact->name, newContact->phoneNumber));
        phoneContacts.insert(std::pair<std::string, std::string> (newContact->phoneNumber, newContact->name));
        delete newContact;
        newContact = nullptr;
    }

    void call() {
        std::string finder;
        std::cout << "Input name or phone number for calling: ";
        std::getline(std::cin, finder);
        Contact* callingContact = new Contact();
        if (checkingRequest(finder, callingContact)) {
            std::cout << "CALL" <<std::endl;
            std::cout << callingContact->phoneNumber << std::endl;
            std::cout << callingContact->name << std::endl;
        } else {
            std::cout << "Wrong input" << std::endl;
        }
        delete callingContact;
        callingContact = nullptr;
    }

    void sms() {
        std::cout << "Input name or phone number for texting: ";
        std::string finder;
        std::getline(std::cin, finder);
        Contact* callingContact = new Contact();
        if (checkingRequest(finder, callingContact)) {
            std::cout << callingContact->name << " " << callingContact->phoneNumber << std::endl;
            std::cout << "---------------------------------------------\n";
            std::string message;
            std::getline (std::cin,message);
            std::cout << "---------------------------------------------\n";
        } else {
            std::cout << "Wrong input" << std::endl;
        }
        delete callingContact;
        callingContact = nullptr;
    }
};

int main() {
    Phone* phone = new Phone();
    std::string command;
    while (command != "exit") {
        std::cout << "Input command: ";
        std::getline(std::cin, command);
        if (command == "add") phone->add();
        else if (command == "call") phone->call();
        else if (command == "sms") phone->sms();
        else if (command != "exit") std::cout << "Wrong Input. Try again." << std::endl;
    }
    delete phone;
    phone = nullptr;
    return 0;
}
