#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
using namespace std;
// I wonder if you guys read the code and comments.
// added some const to a protect data
class LinkedList {
public:
    struct FileVersion {
        int version_number;
        std::string data;
        std::size_t hash;
        FileVersion* next;
    };

    LinkedList() : head(nullptr), tail(nullptr) {}
    ~LinkedList() { //destructor (potential bug)
        FileVersion* current = head;
        while (current != nullptr) {
            FileVersion* next = current->next;
            delete current;
            current = next;
        }
    }
    FileVersion* head;
    FileVersion* tail;
    // essentially the same as A2, just change NULL to nullptr given the new struct 
    void add(const std::string& content) {
        FileVersion* new_version = new FileVersion;
        new_version->data = content;
        new_version->hash = hash_it(content);
        new_version->next = nullptr;

        if (head == nullptr) {
            new_version->version_number = 1;
            head = tail = new_version;
            std::cout << "Your content has been added successfully." << std::endl;
        } else if (tail->hash != hash_it(content)) {
            new_version->version_number = tail->version_number + 1;
            tail->next = new_version;
            tail = new_version;
            std::cout << "Your content has been added successfully." << std::endl;
        } else {
            std::cout << "git322 did not detect any change to your file and will not create a new version." << std::endl;
            delete new_version;
        }
    }

    void print() const {
        FileVersion* current = head;
        std::cout << tail->version_number << std::endl;
        while (current != nullptr) {
            std::cout << "Version number: " << current->version_number << std::endl;
            std::cout << "Hash value: " << current->hash << std::endl;
            std::cout << "Content: " << current->data << std::endl;
            current = current->next; 
        }
    }

    void load(int version) const {
        FileVersion* current = head;
        while (current != nullptr && current->version_number != version) {
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "Please enter a valid version number. If you are not sure please press 'p' to list all valid version numbers." << std::endl;
            return;
        }
        std::ofstream file("file.txt"); 
        file << current->data;
        file.close();
    }
// added its "version number correction" since when you delete versions you can just "compress" the stack
    void remove(int version) {
        if (head == nullptr) {
            std::cout << "Please enter a valid version number." << std::endl;
            return;
        }
        if (head->version_number == version) {
            FileVersion* temp = head;
            head = head->next;
            delete temp;
            FileVersion* current = head;
            int updated_version_number = 1;
            while (current != nullptr){
                current->version_number = updated_version_number;
                updated_version_number++;
                current = current->next;
            }
            return;
        }
        FileVersion* current = head;
        FileVersion* next = current->next;
        while (next != nullptr && next->version_number != version) {
            current = current->next;
            next = next->next;
        }
        if (next == nullptr) {
            std::cout << "Please enter a valid version number." << std::endl;
            return;
        }
        current->next = next->next;
        if (next == tail) {
            tail = current;
        }
        delete next;

        // adjust version nums
        current = head;
        int updated_version_number = 1;
        while (current != nullptr){
            current->version_number = updated_version_number;
            updated_version_number++;
            current = current->next;
        }
    }
// using a && in the while loop required extra loops and using || meant that the compiller was "building" a second loop for efficentiency hence using peek seemed like a safe bet
    void compare(int version1, int version2) const {
        FileVersion* file_version1 = head;
        FileVersion* file_version2 = head;
        while (file_version1 != nullptr && file_version1->version_number != version1) {
            file_version1 = file_version1->next;
        }
        while (file_version2 != nullptr && file_version2->version_number != version2) {
            file_version2 = file_version2->next;
        }
        if (file_version1 == nullptr || file_version2 == nullptr) {
            std::cout << "Invalid versions" << std::endl;
            return;
        }
        std::stringstream stream1(file_version1->data), stream2(file_version2->data);
        std::string line1, line2;
        int line_num = 0;

        while (stream1.peek() != std::ifstream::traits_type::eof() || stream2.peek() != std::ifstream::traits_type::eof() ) {
            if(stream1.peek() == std::ifstream::traits_type::eof()){
                line1 = "";
            } else {
                std::getline(stream1, line1);
            }
            
            if(stream2.peek() == std::ifstream::traits_type::eof()){
                line2 = "";
            } else {
                std::getline(stream2, line2);
            }
            line_num++;
            if (line1 == "") {
                line1 = "<Empty line>";
            }
            if (line2 == "") {
                line2 = "<Empty line>";
            }
            if (line1 != line2) {
                std::cout << "Line " << line_num << ": " << line1 << " <<>> " << line2 << std::endl;
            } else {
                std::cout << "Line " << line_num << ": <Identical>" << std::endl;
            }

        }

    }

    void search(const std::string& keyword) const {
        FileVersion* current = head;
        int count = 0;
        while (current != nullptr) {
            if (current->data.find(keyword) != std::string::npos) {
                count++;
                if (count == 1) {
                    std::cout << "The keyword '" << keyword << "' has been found in the following versions: " << std::endl;
                }
                std::cout << "Version number: " << current->version_number << std::endl;
                std::cout << "Hash value: " << current->hash << std::endl;
                std::cout << "Content: " << current->data << std::endl;
            }
            current = current->next;
        }
        if (count == 0) {
            std::cout << "Your keyword '" << keyword << "' was not found in any version." << std::endl;
        }
    }


private:

    std::size_t hash_it(const std::string& content) const {
        std::hash<std::string> algo;
        return algo(content);
    }
};


class git322 {
public:
    git322() : myList() {}

    void add(const std::string& content) {
        myList.add(content);
    }

    void print() const {
        myList.print(); // cause faxing is outdated
    }

    void load(int version) const {
        myList.load(version);
    }
    void remove(int version) {
        myList.remove(version);
    }

    void compare(int version1, int version2) const {
        myList.compare(version1, version2);
    }

    void search(const std::string& keyword) const {
        myList.search(keyword);
    }

protected:
    LinkedList myList;
}; 

class EnhancedGit322 : public git322 {
public:
    EnhancedGit322() : git322() {}

    void add(const std::string& content){
        git322::add(content);
        saveToFile(); //maybe remove, but still works with this here.
    }

    void remove(int version){
        git322::remove(version);
        saveToFile();
    }
    void load(int version) const {
        git322::load(version);
    }
    void compare(int version1, int version2) const {
        git322::compare(version1, version2);
    }

    void search(const std::string& keyword) const {
        git322::search(keyword);
    }
    void print() const {
        git322::print();
    }
// save the linked list to a file.
    void saveToFile() const {
        std::ofstream file("versions.txt");
        LinkedList::FileVersion* current = this->myList.head;
        while (current != nullptr) {
            file << current->version_number << std::endl;
            file << current->hash << std::endl;
            file << current->data << std::endl;
            current = current->next;
            file << "END OF NODE" << std::endl;
        }
        file.close();
    }
//load the linked list from the file if it exists and is not emoty
    void loadFromFile() {
        std::ifstream file("versions.txt");
        if (file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
            std::string line;
            while (std::getline(file, line) && !line.empty()) {
                int version_number = std::stoi(line);
                std::getline(file, line);
                std::size_t hash = std::stoull(line);
                std::string data;
                while (std::getline(file, line) && !line.empty() && line != "END OF NODE") {
                    data += line + "\n";
                }
                std::getline(file, line); // to "read" EON (END OF NODE for those in the back...seat)
                myList.add(data);
                LinkedList::FileVersion* current = myList.tail;
                current->version_number = version_number;
                current->hash = hash;
            }
            file.close();
            LinkedList::FileVersion* current = myList.head;
            while (current->next != nullptr) {
                current = current->next;
            }
            myList.tail = current;
        }
    }
};


int main(){
    EnhancedGit322 myGit;
    myGit.loadFromFile();
    //make loop
    cout << "Welcome to the Simple File Versioning system! \nTo add the content of your file to version control press 'a' \nTo remove a version press 'r' \nTo load a version press 'l' \nTo print to the screen the detailed list of all versions press 'p' \nTo compare any 2 versions press 'c' \nTo search versions for a keyword press 's' \nTo exit press 'e' " << endl;
    char usr_input; 
    // get usr input
    while (usr_input != 'e') {
        cin >> usr_input;
        if (usr_input == 'a'){
            fstream file("file.txt");
            if (file.is_open()){
                stringstream buf;
                buf << file.rdbuf();
                myGit.add(buf.str());
            }
            file.close();
        //clodse file
        } else if (usr_input == 'p')
        {
            myGit.print();
        }  else if (usr_input == 'l')
        {
            cout << "which version would you like to load" <<endl;
            int version;
            cin >> version;
            myGit.load(version);  

        } else if (usr_input == 'r'){
            cout << "Enter the number of the version that you want to delete: ";
            int version;
            cin >> version;
            myGit.remove(version);
        } else if (usr_input == 'c'){
            int version1, version2;
            cout << "Please enter the number of the first version to compare: ";
            cin >> version1;
            cout << endl << "Please enter the number of the second version to compare: ";
            cin >> version2;
            cout << endl;
            myGit.compare(version1, version2);
        } else if (usr_input == 's'){
            cout << "Please enter the keyword that you are looking for: ";
            string word;
            cin >> word;
            cout << endl;
            myGit.search (word);
        }
            
    }
    myGit.saveToFile();

    return 1;

}
