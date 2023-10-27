#include <iostream>
#include <string>
#include <assert.h>
#include <limits>

using namespace std;

char shiftChar(char letter, int shift);
int getMethod2ShiftAmount(string key1);
int getMethod3ShiftAmount(string key1, string key2);
char encryptChar(char c, int method_choice, string key1, string key2);
char decryptChar(char c, int method_choice, string key1, string key2);
string encryptMessage(string message, int method_choice, string key1, string key2);
string decryptMessage(string message, int method_choice, string key1, string key2);
bool gameRunning(int option);

int main(){
    int method_choice, option;
    string key1, key2, message;
    bool key1_set, key2_set, method_choose = false;
    while (gameRunning(option)){
        cout << "Please input 1-6 followed by enter to navigate the menu:\n";
        cout << "1. Set Encryption Key 1\n2. Set Encryption Key 2\n3. Select Encryption Method\n4. Encrypt Message\n5. Decrypt Message\n6. Exit Program\n";
        cin >> option;
        while (cin.fail() || option <= 0 || option >= 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            cin >> option;
        }
        switch (option){
            case (1):
                cin.ignore();
                cin.clear();
                cout << "Enter key:\n";
                getline(cin, key1);
                while (key1.length() < 1){
                    cout << "Invalid key\n";
                    cout << "Enter key:\n";
                    getline(cin, key1);
                }
                cout << "Successfully set encryption key1 to " << key1 << "\n";
                key1_set = true;
                break;
            case (2):
                cin.ignore();
                cin.clear();
                cout << "Enter key:\n";
                getline(cin, key2);
                while (key2.length() < 1){
                    cout << "Invalid key\n";
                    cout << "Enter key:\n";
                    getline(cin, key2);
                }
                cout << "Successfully set encryption key2 to " << key2 << "\n";
                key2_set = true;
                break;
            case (3):
                cin.ignore();
                cout << "Please input 1-4 to decide encryption technique.\n1. Method1 only (shift by 1)\n2. Method2 only (shift by first key)\n3. Method3 only (shift by both keys)\n4. Mix of Method1, Method2, Method3\n";
                cin >> method_choice;
                while (cin.fail() || (method_choice < 1 || method_choice > 4)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid encryption choice\n";
                    cin >> method_choice;
                }
                cout << "Successfully set encryption type to " << method_choice << "\n";
                method_choose = true;
                break;
            case (4):
                if (method_choose && key1_set && key2_set){
                    cout << "Enter your message to encrypt:\n";
                    cin.ignore();
                    getline(cin, message);
                    cout << encryptMessage(message, method_choice, key1, key2) << "\n";
                }
                else{
                    cout << "You cannot do this until you set both keys and choose an encryption method\n";
                }
                break;
            case (5):
                if (method_choose && key1_set && key2_set){
                    cout << "Enter your message to decrypt:\n";
                    cin.ignore();
                    getline(cin, message);
                    cout << decryptMessage(message, method_choice, key1, key2) << "\n";
                }
                else {
                    cout << "You cannot do this until you set both keys and choose an encryption method\n";
                }    
                break;
            case (6):
                cout << "Goodbye.";
                return 0;
            default:
                
                if (option == 6){
                    cout << "Goodbye.";
                    break;
                }    
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------

char shiftChar(char letter, int shift){
    int letter_code;
    if (letter < 97 || letter > 122){
        return letter;
    }
    else if (shift > 0){
        shift = shift % 26;
        letter_code = letter + shift;
        if (letter_code > 122){
            letter = 97 + (letter_code - 123);
            return letter;
        }
        else if (letter_code < 97){
            letter = 123 + (letter_code - 97);
            return letter;
        }
        return letter_code;
    }
    else if (shift < 0){
        shift = shift % 26;
        letter_code = letter + shift;
        if (letter_code < 97){
            letter = 123 + (letter_code - 97);
            return letter;
        }
        else if (letter_code > 122){
            letter = 97 + (letter_code - 123);
            return letter;
        }
        return letter_code;
    }
    else {
        return letter;
    }
}

int getMethod2ShiftAmount(string key1){
    int shift_vaule;
    int vowels = 0;
    for (int i = 0; i < key1.length(); i++){
        if (key1[i] == 'a' || key1[i] == 'e' || key1[i] == 'i' || key1[i] == 'o' || key1[i] == 'u' || key1[i] == 'y'){
            vowels++;
        }
        else {
            vowels = vowels;
        }
    }
    shift_vaule = (vowels + key1.length()) % 26;
    return shift_vaule;
}

int getMethod3ShiftAmount(string key1, string key2){
   int shift_factor = 0;
   for (int i = 0; i < key1.length(); i++){
        for (int j = 0; j < key2.length(); j++){
            if (key1[i] == key2[j]){
                shift_factor++;    
            }
            
        }
   } 
   return shift_factor % 26;
}

char encryptChar(char c, int method_choice, string key1, string key2){
    switch (method_choice)
    {
    case 1:
        return shiftChar(c, 1);
        break;
    case 2:
        return shiftChar(c, getMethod2ShiftAmount(key1));
        break;
    case 3:
        return shiftChar(c, getMethod3ShiftAmount(key1, key2));
        break;
    default:
        cout << "Invalid encryption method\n";
        return shiftChar(c, 0);
        break;
    }
}

char decryptChar(char c, int method_choice, string key1, string key2){
    
    switch (method_choice)
    {
    case 1:
        return shiftChar(c, -1);
        break;
    case 2:
        return shiftChar(c, -1 * (getMethod2ShiftAmount(key1)));
        break;
    case 3:
        return shiftChar(c, -1 * (getMethod3ShiftAmount(key1, key2)));
        break;
    default:
        cout << "Invalid decryption method\n";
        return shiftChar(c, 0);
        break;
    }
}

string encryptMessage(string message, int method_choice, string key1, string key2){
    int j = 0;
    switch (method_choice) {
    case 1:
        for (int i = 0; i < message.length(); i++){
            char c = message[i];
            if (c < 123 && c > 96){
                message[i] = shiftChar(c, 1);
            }
            else{
                message[i] = message[i];
            } 
        }
        break;
    case 2:
        for (int i = 0; i < message.length(); i++){
            char c = message[i];
            if (c < 123 && c > 96){
                message[i] = shiftChar(c, getMethod2ShiftAmount(key1));
            }
            else{
                message[i] = message[i];
            }
        }
        break;
    case 3:
        for (int i = 0; i < message.length(); i++){
            char c = message[i];
            if (c < 123 && c > 96){
                message[i] = shiftChar(c, getMethod3ShiftAmount(key1, key2));
            }
            else{
                message[i] = message[i];
            }  
        }
        break;
    case 4:
        while(j < message.length()){
            char c = message[j];
            if (c < 123 && c > 96){
                message[j] = shiftChar(c, 1);
                j++;
            }
            else{
                message[j] = message[j];
                j++;
            }
            if (j >= message.length()){
                break;
            }
            char d = message[j];
            if (d < 123 && d > 96){
                message[j] = shiftChar(d, getMethod2ShiftAmount(key1));
                j++;
            }
            else{
                message[j] = message[j];
                j++;
            }
            if (j >= message.length()){
                break;
            }
            char e = message[j];
            if (e < 123 && e > 96){
                message[j] = shiftChar(e, getMethod3ShiftAmount(key1, key2));
                j++;
            }
            else{
                message[j] = message[j];
                j++;
            }
            if (j >= message.length()){
                break;
            }
        }
        break;
    default:
        cout << "Invalid encryption method\n";
        break;
    }
    return message;
}

string decryptMessage(string message, int method_choice, string key1, string key2){
    int j = 0;
    switch (method_choice) {
    case 1:
        for (int i = 0; i < message.length(); i++){
            char c = message[i];
            if (c < 123 && c > 96){
                message[i] = decryptChar(c, 1, key1, key2);
            }
            else{
                message[i] = message[i];
            } 
        }
        break;
    case 2:
        for (int i = 0; i < message.length(); i++){
            char c = message[i];
            if (c < 123 && c > 96){
                message[i] = decryptChar(c, 2, key1, key2);
            }
            else{
                message[i] = message[i];
            }
        }
        break;
    case 3:
        for (int i = 0; i < message.length(); i++){
            char c = message[i];
            if (c < 123 && c > 96){
                message[i] = decryptChar(c, 3, key1, key2);
            }
            else{
                message[i] = message[i];
            }  
        }
        break;
    case 4:
        while(j < message.length()){
            char c = message[j];
            if (c < 123 && c > 96){
                message[j] = decryptChar(c, 1, key1, key2);
                j++;
            }
            else{
                message[j] = message[j];
                j++;
            }
            if (j >= message.length()){
                break;
            }
            char d = message[j];
            if (d < 123 && d > 96){
                message[j] = decryptChar(d, 2, key1, key2);
                j++;
            }
            else{
                message[j] = message[j];
                j++;
            }
            if (j >= message.length()){
                break;
            }
            char e = message[j];
            if (e < 123 && e > 96){
                message[j] = decryptChar(e, 3, key1, key2);
                j++;
            }
            else{
                message[j] = message[j];
                j++;
            }
            if (j >= message.length()){
                break;
            }
        }
        break;
    default:
        cout << "Invaild encryption method.";
        break;
    }
    return message;
}

bool gameRunning(int option){
    if (option == 6){
        return false;
    }
    return true;
}