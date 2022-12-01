#include <iostream>
#include "Human Resources Department.h"

int get_position (int id, vector<int> id_array) {
    int res = 0, i;
    for (i = 0; i <= id_array.size(); i++) {
        res = i;
        if (id > id_array[i]) continue; else break;
    }
    return res;
}

int main() {
    Company company;
    Employee employee;
    Supervisor supervisor;
    company.add_employee(employee);
    company.add_employee(supervisor);
    cout << employee.get_id() << " " << supervisor.get_id();
    return 0;
}
