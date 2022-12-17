#include "menu.h"
#include <iostream>

using namespace std;

int get_int_of_2(const char message[]){
    int n;
    cout << message;
    while (!(cin >> n).good() || n < 1 || n > 2) {
        cout << "Incorrect number!\n";
        cout << message;
        cin.clear();
        cin.ignore(100, '\n');
    }
    cin.clear();
    cin.ignore(100, '\n');
    return n;
}

int get_menu_item(int min, int max) {
    int res = get_int("Select menu item: ");
    while (res < min || res > max){
        cout << "Invalid menu item.\n";
        res = get_int("Select menu item: ");
    }
    return res;
}

int get_department_number(Company &company) {
    company.get_departments();
    int res = get_int("Select department number: ");
    if (res < 1 || res > company.get_dep_amount()){
        cout << "Invalid department number.\n";
        res = -1;
    }
    return res;
}

int get_employee_id(Company::Department &department) {
    department.get_table();
    return get_int("Select employee id: ");
}

void print_company_menu(){
    cout << "\n1. Select department.\n"
            "2. Add department.\n"
            "3. Delete department.\n"
            "4. Search employee.\n"
            "5. Delete employee.\n"
            "6. Get company name.\n"
            "7. Show company contents.\n"
            "0. Exit.\n\n";
}

void company_menu(Company &company){
    int choice;
    while (true) {
        print_company_menu();
        choice = get_menu_item(0, 7);
        if (choice == 1) {
            int i = get_department_number(company);
            if (i == -1) continue;
            department_menu(*(company.get_department(i - 1)));
            continue;
        }
        if (choice == 2) {
            cout << "Enter new department name: ";
            string str;
            getline(cin, str);
            if (company.search(str)) {
                cout << "That department is already in company.\n";
                continue;
            }
            auto dep = new Company::Department(str);
            company.add_department(dep);
            cout << "Success.\n";
            continue;
        }
        if (choice == 3) {
            int i = get_department_number(company);
            if (i == -1) continue;
            company.delete_department(i - 1);
            cout << "Success.\n";
            continue;
        }
        if (choice == 4) {
            cout << "Enter employee's id: ";
            int id;
            cin >> id;
            Employee *emp_ptr = company.search(id);
            if (!emp_ptr) {
                cout << "No employee with this id.\n";
                continue;
            }
            emp_ptr->display_information();
            continue;
        }
        if (choice == 5) {
            cout << "Enter employee's id: ";
            int id;
            cin >> id;
            company.delete_employee(id);
            cout << "Success.\n";
            continue;
        }
        if (choice == 6) { cout << company.get_company_name() << endl; }
        if (choice == 7) { company.get_table(); }
        if (choice == 0) break;
    }
}

void print_department_menu(){
    cout << "\n1. Add employee.\n"
            "2. Delete employee.\n"
            "3. Get employee info.\n"
            "4. Get employee type.\n"
            "5. Get/Set employee position.\n"
            "6. Get/Set employee salary.\n"
            "7. Cast employee to supervisor.\n"
            "8. Show department contents.\n"
            "0. Return to company menu.\n\n";
}

void department_menu(Company::Department &department){
    int choice;
    while (true) {
        print_department_menu();
        choice = get_menu_item(0, 8);
        if (choice == 1) {
            int i = get_int_of_2("1. Employee.\n2. Supervisor.\nSelect: ");
            if (i == 1) {
                auto emp = new Employee();
                cin >> emp;
                department.add_employee(emp);
            }
            else {
                auto sup = new Supervisor();
                cin >> sup;
                sup->set_department_ptr(&department);
                department.add_employee(sup);
            }
            continue;
        }
        if (choice == 2) {
            int id = get_employee_id(department);
            department.delete_employee(id);
            continue;
        }
        if (choice == 3) {
            int id = get_employee_id(department);
            Employee *ptr = department.search(id);
            if (ptr) {
                ptr->display_information();
            } else cout << "No such employee.\n";
            continue;
        }
        if (choice == 4) {
            int id = get_employee_id(department);
            Employee *ptr = department.search(id);
            if (ptr) {
                cout << ptr->get_type() << endl;
            } else cout << "No such employee.\n";
            continue;
        }
        if (choice == 5) {
            int id = get_employee_id(department);
            Employee *ptr = department.search(id);
            if (ptr) {
                int i = get_int_of_2("1. Get.\n2. Set.\nSelect: ");
                if (i == 1) {
                    cout << ptr->get_position() << endl;
                } else {
                    string str;
                    cout << "Input new position: ";
                    cin >> str;
                    ptr->set_position(str);
                }
            } else cout << "No such employee.\n";
            continue;
        }
        if (choice == 6) {
            int id = get_employee_id(department);
            Employee *ptr = department.search(id);
            if (ptr) {
                int i = get_int_of_2("1. Get.\n2. Set.\nSelect: ");
                if (i == 1) {
                    cout << ptr->get_salary() << endl;
                } else {
                    int new_salary;
                    cout << "Input new salary: ";
                    cin >> new_salary;
                    ptr->set_salary(new_salary);
                }
            } else cout << "No such employee.\n";
            continue;
        }
        if (choice == 7) {
            int id = get_employee_id(department);
            int i = department.emp_to_sup(id);
            if (i == 0) {
                cout << "Success.\n" << endl;
            } else if (i == 1) {
                cout << "No such employee.\n";
            } else if (i == 2) {
                cout << "That employee is already a supervisor.\n";
            }
            continue;
        }
        if (choice == 8) { department.get_table(); }
        if (choice == 0) break;
    }
}