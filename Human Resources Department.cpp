#include <algorithm>
#include "Human Resources Department.h"

int Employee::Count = 0;

Employee::Employee(string name, int birth_year, string position, string education, int salary) {
    Employee::Count++;
    id = Employee::Count;
    this->name = std::move(name);
    this->birth_year = birth_year;
    this->position = std::move(position);
    this->education = std::move(education);
    this->salary = salary;
}

Supervisor::Supervisor(string name, int birth_year, string position, string education, int salary) {
    this->name = std::move(name);
    this->birth_year = birth_year;
    this->position = std::move(position);
    this->education = std::move(education);
    this->salary = salary;
    ptr_department = nullptr;
}

Supervisor &Supervisor::operator=(Employee *employee) {
    this->name = std::move(employee->get_name());
    this->birth_year = employee->get_birth_year();
    this->position = std::move(employee->get_position());
    this->education = std::move(employee->get_education());
    this->salary = employee->get_salary();
    ptr_department = nullptr;
    this->id = employee->get_id();
    Count--;
    return *this;
}

void Supervisor::set_department_ptr(Company::Department *ptr) { ptr_department = ptr; }

Company::Department::Department() {
    cout << "Input department name: ";
    cin >> department_name;
}

Company::Department::Department(const string &name) {
    department_name = name;
}

int Employee::get_id() const {
    return this->id;
}

bool comparator (Employee *e1, Employee *e2) { return e1->get_id() < e2->get_id(); }

int Company::Department::add_employee(Employee *employee) {
    if (search(employee->get_id())) { return -1; }
    employees_array.push_back(employee);
    sort (employees_array.begin(), employees_array.end(), comparator);
    return 0;
}

int Company::Department::add_employee(Supervisor *supervisor) {
    if (search(supervisor->get_id())) { return -1; }
    supervisor->set_department_ptr(this);
    employees_array.push_back(supervisor);
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

Company::Department *Company::search_dep (int id){
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

Company::Company(const string &name) {
    company_name = name;
}

Company::Company() {
    cout << "Input Company name: ";
    cin >> company_name;
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
    if (pos != -1) employees_array.erase(employees_array.cbegin() + pos);
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

void Employee::display_information () {
    cout << id << ": " << get_info() << endl;
}

const char *Employee::get_type (){
    return typeid(*this).name();
}

string Employee::get_position() {
    return position;
}

void Employee::set_position (string &new_pos){
    position = new_pos;
}

int Employee::get_salary () const {
    return salary;
}

void Employee::set_salary(int new_salary) {
    salary = new_salary;
}

string Employee::get_name() {
    return name;
}

int Employee::get_birth_year() const {
    return birth_year;
}

string Employee::get_education() {
    return education;
}

int Company::emp_to_sup(Company::Department *department, int id) {
    Employee *emp_ptr = department->search(id);
    if (!emp_ptr) { return -1; }
    Supervisor new_supervisor;
    if (typeid(*emp_ptr).name() == typeid(new_supervisor).name()) { return -2; }
    new_supervisor = emp_ptr;
    department->delete_employee(id);
    department->add_employee(&new_supervisor);
    return 0;
}
