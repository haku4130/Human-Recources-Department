#include <algorithm>
#include "Human Resources Department.h"

int Employee::Count = 0;

Employee::Employee() {
    Employee::Count++;
    id = Employee::Count;
}

Supervisor::Supervisor() {

}

int Employee::get_id() const {
    return this->id;
}

int Company::in_company(int id) {
    for (int i : id_array) {
        if (i == id) return i;
    } return 0;
}

int Company::get_position (int id) {
    int res = 0, i;
    for (i = 0; i < id_array.size(); i++) {
        res = i;
        if (id > id_array[i]) continue; else break;
    }
    return res;
}

int Company::add_employee(Employee &employee) {
    if (!in_company(employee.get_id())) { return -1; }
    int pos = get_position(employee.get_id());
    id_array.insert(id_array.cbegin() + pos, employee.get_id());
    employees_array.insert(employees_array.cbegin() + pos, employee);
    return 0;
}
