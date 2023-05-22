#pragma once
#include <struk.h>

using namespace std;




void createDatabase() {
    ofstream file("database.bin", ios::binary);
    if (file.is_open()) {
        cout << "�������� ���� ���� �����." << endl;
        file.close();
    }
    else {
        cout << "������� ��� �������� ���� �����." << endl;
    }
}

void addRecord() {
    Building record;
    cout << "������ ��� ������ ������:" << endl;
    cout << "������: ";
    cin.ignore();
    cin.getline(record.subcontra, N);
    cout << "��� �����: ";
    cin >> record.buildingType;
    cout << "�������: ";
    cin >> record.price;
    cout << "³������ �� ������: ";
    cin >> record.cust.creditInterest;
    cout << "���� ������: ";
    cin >> record.cust.depositAmount;

    // ���������� ����������� ����
    if (record.cust.depositAmount < record.price) {
        record.cust.creditBalance = record.price - record.cust.depositAmount;
    }
    else {
        record.cust.creditBalance = 0.0;
    }

    ofstream file("database.bin", ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&record), sizeof(Building));
        cout << "����� ������ ������ �� ���� �����." << endl;
        file.close();
    }
    else {
        cout << "������� ��� ������� ���� �����." << endl;
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

        cout << "�������� ����������� ���� ��� �볺��� �� �������: " << totalUnpaidAmount << endl;

        file.close();
    }
    else {
        cout << "������� ��� ������� ���� �����." << endl;
    }
}

void searchByKey() {
    int key;
    cout << "������ ���� ��� ������ �� ����� �����: ";
    cin >> key;

    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        bool found = false;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            if (record.buildingType == key && record.cust.depositAmount < record.price) {
                cout << "�������� �����:" << endl;
                cout << "������: " << record.subcontra << endl;
                cout << "��� �����: " << record.buildingType << endl;
                cout << "�������: " << record.price << endl;
                cout << "³������ �� ������: " << record.cust.creditInterest << endl;
                cout << "���� ������: " << record.cust.depositAmount << endl;
                cout << "����������� ����: " << record.cust.creditBalance << endl;
                cout << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "������ � ����� ������ �� ��������." << endl;
        }

        file.close();
    }
    else {
        cout << "������� ��� ������� ���� �����." << endl;
    }
}

void displayDatabase() {
    Building record;

    ifstream file("database.bin", ios::binary);
    if (file.is_open()) {
        cout << "������ ���� �����:" << endl;
        // ��������� �������
        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
        cout << "������\t\t��� �����\t�������\t³������ �� ������\t���� ������\t����������� ����" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

        while (file.read(reinterpret_cast<char*>(&record), sizeof(Building))) {
            // ���� ����� � ������ �������
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
        cout << "������� ��� ������� ���� �����." << endl;
    }
}


void controlMenu() {
    char choice;

    do {
        cout << "����:" << endl;
        cout << "a. �������� ���� ���� �����" << endl;
        cout << "b. ������ �����" << endl;
        cout << "c. �������� �����" << endl;
        cout << "d. ����� �� ������" << endl;
        cout << "f. ������� ���� �����" << endl;
        cout << "q. ����� � ��������" << endl;
        cout << "��� ����: ";
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
            cout << "�������� ������� ������." << endl;
            break;
        default:
            cout << "������� ����. ��������� �� ���." << endl;
            break;
        }
    } while (choice != 'q');
}
