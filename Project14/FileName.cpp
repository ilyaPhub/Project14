#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Employee {
    string surname;
    string name;
    string phone;
    double salary;
};


bool isValidPhone(const string& phone) {
    if (phone.length() != 14 || phone[0] != '(' || phone[4] != ')' || phone[5] != ' ' || phone[9] != '-') {
        return false;
    }
    for (int i = 1; i < 4; ++i) {
        if (!isdigit(phone[i])) return false;
    }
    for (int i = 6; i < 9; ++i) {
        if (!isdigit(phone[i])) return false;
    }
    for (int i = 10; i < 14; ++i) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}

void displayMenu() {
    setlocale(LC_ALL, "Russian");
    cout << "Выберите действие:\n";
    cout << "1. Загрузить данные из файла\n";
    cout << "2. Сохранить данные в файл\n";
    cout << "3. Показать всех сотрудников\n";
    cout << "4. Найти сотрудника по фамилии\n";
    cout << "5. Найти сотрудников по диапазону зарплат\n";
    cout << "6. Добавить сотрудника\n";
    cout << "7. Удалить сотрудника\n";
    cout << "8. Отсортировать по фамилии\n";
    cout << "0. Выйти\n";
}

void loadFromFile(vector<Employee>& employees, const string& filename) {
    setlocale(LC_ALL, "Russian");
    ifstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл!\n";
        return;
    }
    employees.clear();
    Employee temp;
    while (file >> temp.surname >> temp.name >> temp.phone >> temp.salary) {
        employees.push_back(temp);
    }
    file.close();
    cout << "Данные загружены!\n";
}

void saveToFile(const vector<Employee>& employees, const string& filename) {
    setlocale(LC_ALL, "Russian");
    ofstream file(filename);
    for (const auto& employee : employees) {
        file << employee.surname << " " << employee.name << " " << employee.phone << " " << employee.salary << endl;
    }
    file.close();
    cout << "Данные сохранены!\n";
}

void displayEmployees(const vector<Employee>& employees) {
    setlocale(LC_ALL, "Russian");
    for (const auto& employee : employees) {
        cout << employee.surname << " " << employee.name << " Телефон: " << employee.phone << " Зарплата: " << employee.salary << endl;
    }
}

void findBySurname(const vector<Employee>& employees, const string& surname) {
    setlocale(LC_ALL, "Russian");
    bool found = false;
    for (const auto& employee : employees) {
        if (employee.surname == surname) {
            cout << employee.surname << " " << employee.name << " Телефон: " << employee.phone << " Зарплата: " << employee.salary << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудник с фамилией " << surname << " не найден.\n";
    }
}

void findBySalaryRange(const vector<Employee>& employees, double minSalary, double maxSalary) {
    setlocale(LC_ALL, "Russian");
    bool found = false;
    for (const auto& employee : employees) {
        if (employee.salary >= minSalary && employee.salary <= maxSalary) {
            cout << employee.surname << " " << employee.name << " Телефон: " << employee.phone << " Зарплата: " << employee.salary << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Сотрудников с зарплатой в диапазоне от " << minSalary << " до " << maxSalary << " не найдено.\n";
    }
}

void addEmployee(vector<Employee>& employees) {
    setlocale(LC_ALL, "Russian");
    Employee newEmployee;
    cout << "Введите фамилию: ";
    cin >> newEmployee.surname;
    cout << "Введите имя: ";
    cin >> newEmployee.name;
    do {
        cout << "Введите телефон (формат (XXX) XXX-XXXX): ";
        cin >> newEmployee.phone;
        if (!isValidPhone(newEmployee.phone)) {
            cout << "Некорректный формат телефона. Попробуйте снова.\n";
        }
    } while (!isValidPhone(newEmployee.phone));

    cout << "Введите зарплату: ";
    cin >> newEmployee.salary;
    employees.push_back(newEmployee);
}

void deleteEmployee(vector<Employee>& employees, const string& surname) {
    setlocale(LC_ALL, "Russian");
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->surname == surname) {
            employees.erase(it);
            cout << "Сотрудник удален.\n";
            return;
        }
    }
    cout << "Сотрудник с фамилией " << surname << " не найден.\n";
}

void sortBySurname(vector<Employee>& employees) {
    setlocale(LC_ALL, "Russian");
    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.surname < b.surname;
        });
    cout << "Сотрудники отсортированы по фамилии.\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Employee> employees;
    string filename = "employees.txt";
    int choice;

    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            loadFromFile(employees, filename);
            break;
        case 2:
            saveToFile(employees, filename);
            break;
        case 3:
            displayEmployees(employees);
            break;
        case 4: {
            string surname;
            cout << "Введите фамилию для поиска: ";
            cin >> surname;
            findBySurname(employees, surname);
            break;
        }
        case 5: {
            double minSalary, maxSalary;
            cout << "Введите минимальную и максимальную зарплату: ";
            cin >> minSalary >> maxSalary;
            findBySalaryRange(employees, minSalary, maxSalary);
            break;
        }
        case 6:
            addEmployee(employees);
            break;
        case 7: {
            string surname;
            cout << "Введите фамилию для удаления: ";
            cin >> surname;
            deleteEmployee(employees, surname);
            break;
        }
        case 8:
            sortBySurname(employees);
            break;
        case 0:
            cout << "Выход...\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
