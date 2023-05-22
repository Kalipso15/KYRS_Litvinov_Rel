#pragma once
#include <struk.h>

using namespace std;




void createDatabase() {
    ofstream file("database.bin", ios::binary);
    if (file.is_open()) {
        cout << "Створено нову базу даних." << endl;
        file.close();
    }
    else {
        cout << "Помилка при створенні бази даних." << endl;
    }
}

void addRecord() {
    Building record;
    cout << "Введіть дані нового запису:" << endl;
    cout << "Будівля: ";
    cin.ignore();
    cin.getline(record.subcontra, N);
    cout << "Тип будівлі: ";
    cin >> record.buildingType;
    cout << "Вартість: ";
    cin >> record.price;
    cout << "Відсоток за кредит: ";
    cin >> record.cust.creditInterest;
    cout << "Сума вкладу: ";
    cin >> record.cust.depositAmount;

    // Розрахунок невиплаченої суми
    if (record.cust.depositAmount < record.price) {
        record.cust.creditBalance = record.price - record.cust.depositAmount;
    }
    else {
        record.cust.creditBalance = 0.0;
    }

    ofstream file("database.bin", ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&record), sizeof(Building));
        cout << "Запис успішно додано до бази даних." << endl;
        file.close();
    }
    else {
        cout << "Помилка при відкритті бази даних." << endl;
    }
}



void query() {
    float totalUnpaidAmount = 0.0;
    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            if (record.cust.creditBalance > 0.0) {
                totalUnpaidAmount += record.cust.creditBalance * record.cust.creditInterest;
            }
        }

        cout << "Загальна невиплачена сума всіх клієнтів по кредиту: " << totalUnpaidAmount << endl;

        file.close();
    }
    else {
        cout << "Помилка при відкритті бази даних." << endl;
    }
}

void searchByKey() {
    int key;
    cout << "Введіть ключ для пошуку за типом будівлі: ";
    cin >> key;

    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        bool found = false;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            if (record.buildingType == key && record.cust.depositAmount < record.price) {
                cout << "Знайдено запис:" << endl;
                cout << "Будівля: " << record.subcontra << endl;
                cout << "Тип будівлі: " << record.buildingType << endl;
                cout << "Вартість: " << record.price << endl;
                cout << "Відсоток за кредит: " << record.cust.creditInterest << endl;
                cout << "Сума вкладу: " << record.cust.depositAmount << endl;
                cout << "Невиплачена сума: " << record.cust.creditBalance << endl;
                cout << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "Записів з таким ключем не знайдено." << endl;
        }

        file.close();
    }
    else {
        cout << "Помилка при відкритті бази даних." << endl;
    }
}

void displayDatabase() {
    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        cout << "Записи бази даних:" << endl;
        // Заголовок таблиці
        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Будівля\t\tТип будівлі\tВартість\tВідсоток за кредит\tСума вкладу\tНевиплачена сума" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            // Вивід даних у вигляді таблиці
            cout << record.subcontra << "\t\t"
                << record.buildingType << "\t\t"
                << record.price << "\t\t\t"
                << record.cust.creditInterest << "\t\t\t"
                << record.cust.depositAmount << "\t\t\t"
                << record.cust.creditBalance << endl;
        }

        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

        file.close();
    }
    else {
        cout << "Помилка при відкритті бази даних." << endl;
    }
}


void controlMenu() {
    char choice;

    do {
        cout << "Меню:" << endl;
        cout << "a. Створити нову базу даних" << endl;
        cout << "b. Додати запис" << endl;
        cout << "c. Виконати запит" << endl;
        cout << "d. Пошук за ключем" << endl;
        cout << "f. Вивести базу даних" << endl;
        cout << "q. Вийти з програми" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 'a':
            createDatabase();
            break;
        case 'b':
            addRecord();
            break;
        case 'c':
            query();
            break;
        case 'd':
            searchByKey();
            break;
        case 'f':
            displayDatabase();
            break;
        case 'q':
            cout << "Програма завершує роботу." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
            break;
        }
    } while (choice != 'q');
}
