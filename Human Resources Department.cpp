#include <algorithm>
#include "Human Resources Department.h"

int Employee::Count = 0;

Employee::Employee() {
    Employee::Count++;
    id = Employee::Count;
    cout << "Input name: ";
    cin >> name;
    cout << "Input birth year: ";
    birth_year = 0;
    cin >> birth_year;
    cout << "Input position: ";
    cin >> position;
    cout << "Input education: ";
    cin >> education;
    cout << "Input salary: ";
    salary = 0;
    cin >> salary;
}

Employee::Employee(const string &name, int birth_year, const  string &position, const string &education, int salary) {
    Employee::Count++;
    id = Employee::Count;
    this->name = name;
    this->birth_year = birth_year;
    this->position = position;
    this->education = education;
    this->salary = salary;
}

Supervisor::Supervisor(): Employee() {
    ptr_department = nullptr;
}

Supervisor::Supervisor(const string &name, int birth_year, const string &position, const string &education, int salary) : Employee(name, birth_year, position, education, salary){
    ptr_department = nullptr;
}

Company::Department::Department() {
    cout << "Input department name: ";
    getline(cin, department_name);
}

Company::Department::Department(const string &name) {
    department_name = name;
}

Company::Company() {
    cout << "Input Company name: ";
    getline(cin, company_name);
}

Company::Company(const string &name) {
    company_name = name;
}

void Supervisor::set_department_ptr(Company::Department *ptr) { ptr_department = ptr; }

Supervisor &Supervisor::operator = (Employee *other) {
    id = other->get_id();
    name = other->get_name();
    birth_year = other->get_birth_year();
    position = other->get_position();
    education = other->get_education();
    salary = other->get_salary();
    Count--;
    return *this;
}

int Employee::get_id() const { return this->id; }

bool comparator (Employee *e1, Employee *e2) { return e1->get_id() < e2->get_id(); }

int Company::Department::add_employee(Employee *employee) {
    if (search(employee->get_id())) { return -1; }
    employees_array.push_back(employee);
    sort (employees_array.begin(), employees_array.end(), comparator);
    return 0;
}

Employee *Company::Department::search(int id) {
    for (Employee *employee : employees_array) {
        if (employee->get_id() == id){
            return employee;
        }
    }
    return nullptr;
}

string Company::Department::get_department_name() { return department_name; }

Employee *Company::search(int id) {
    for (Company::Department *department : departments) {
        Employee *tmp = department->search(id);
        if (tmp) return tmp;
    }
    return nullptr;
}

void Company::add_department(Company::Department *department) {
    departments.push_back(department);
}

Company::Department *Company::search(const string &name) {
    for (Department *department : departments) {
        if (department->get_department_name() == name) return department;
    }
    return nullptr;
}

Company::Department *Company::search_dep_with_emp (int id){
    for (Company::Department *department : departments) {
        if (department->search(id)) return department;
    }
    return nullptr;
}

void Company::delete_employee (int id) {
    for (Company::Department *department : departments) {
        department->delete_employee(id);
    }
}

string Company::get_company_name() { return company_name; }

int Company::Department::get_position (int id) {
    for (int i = 0; i < employees_array.size(); i++) {
        if (employees_array[i]->get_id() == id) return i;
    }
    return -1;
}

void Company::Department::delete_employee (int id) {
    int pos = get_position(id);
    if (pos != -1){
        Employee *ptr = employees_array[pos];
        employees_array.erase(employees_array.cbegin() + pos);
        delete ptr;
    } else cout << "No such employee.\n";
}

string Employee::get_info (){
    return name + ", "
    + to_string(birth_year) + ", "
    + position + ", "
    + education + ", "
    + to_string(salary) + ".";
}

void Company::get_table() {
    cout << company_name << endl;
    for (Company::Department *department : departments) {
        department->get_table();
    }
}

void Company::Department::get_table() {
    cout << department_name << endl;
    for (Employee *employee : employees_array) {
        cout << employee->get_id() << ": " << employee->get_info() << endl;
    }
}

void Employee::display_information () { cout << id << ": " << get_info() << endl; }

const char *Employee::get_type (){ return typeid(*this).name(); }

string Employee::get_position() { return position; }

void Employee::set_position (string &new_pos){ position = new_pos; }

int Employee::get_salary () const { return salary; }

void Employee::set_salary(int new_salary) { salary = new_salary; }

string Employee::get_name() { return name; }

int Employee::get_birth_year() const { return birth_year; }

string Employee::get_education() { return education; }

int Company::Department::emp_to_sup(int id) {
    Employee *emp_ptr = this->search(id);
    if (!emp_ptr) { return 1; }
    auto *new_supervisor = new Supervisor;
    if (typeid(*emp_ptr).name() == typeid(new_supervisor).name()) { return 2; }
    *new_supervisor = emp_ptr;
    new_supervisor->set_department_ptr(this);
    this->delete_employee(id);
    this->add_employee(new_supervisor);
    return 0;
}

void Company::Department::free_department () {
    for (Employee *employee : employees_array) { delete employee; }
}

void Company::free_company () {
    for (Company::Department *department : departments) { department->free_department(); }
}

void Company::get_departments() {
    for (int i = 0; i < departments.size(); i++) {
        cout << i + 1 << ". " << departments[i]->get_department_name() << endl;
    }
}

unsigned long Company::get_dep_amount() {
    return departments.size();
}

Company::Department *Company::get_department(int i) {
    return departments[i];
}

void Company::delete_department(int i) {
    Company::Department *dep_ptr = departments[i];
    departments.erase(departments.cbegin() + i);
    dep_ptr->free_department();
}
