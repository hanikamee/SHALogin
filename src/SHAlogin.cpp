// This pogram will check if the user's entered password and username match the
// stored username and password in a text file by comparing the hashes.

#include <iostream>
#include <fstream>



// Returns the hash of a password with an added salt
size_t sha(std::string input, std::string salt){
    std::hash<std::string> hash;
    return hash(salt + input);
}

int main()
{
    // Creating an input file
    std::ifstream loginFile("login.txt");

    if(!loginFile.is_open()) {
        std::cout << "file error!" << std::endl;
        return 1;
    } else {
        std::cout << "file open!" << std::endl;

    }

    // Prompting the user to enter a username and password
    std::string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    std::string password;
    std::cout << "Enter your pass: ";
    std::cin >> password;


    // Variables to assist in the comparison of the hashes
    std::string tempName;
    std::string tempSalt;
    size_t tempHash;


    bool loginSuccess = false;
    bool userFound = false;
    while (loginFile >> tempName >> tempSalt >> tempHash){
        if (tempName == username){
            if (sha(password, tempSalt) == tempHash){
                loginSuccess = true;
            }
            userFound = true;
        }
    }

    if(!userFound) {
        std::cout << "User not found in database" << std::endl;
    } else if(!loginSuccess) {
        std::cout << "Bad password!" << std::endl;
    } else {
        std::cout << "Login Successful!" << std::endl;
    }


    loginFile.close();

    return 0;
}
