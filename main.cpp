#include <iostream>
#include "Human Resources Department.h"

int main() {
    Company company ("gym");
    Company::Department department("slaves");
    company.add_department(&department);
    Employee employee("Ivanov I.I.", 1996, "backend", "middle school", 20);
    Supervisor supervisor;
    Employee employee2;
    cout << department.add_employee(&employee2) << " " << department.add_employee(&employee) << " " << department.add_employee(&supervisor) << endl;
    cout << typeid(employee2).name() << " " << typeid(supervisor).name() << endl;
    Employee *ptr = company.search(2);
    company.get_table();
    department.delete_employee(2);
    company.get_table();
    company.emp_to_sup(&department, 1);
    company.get_table();
    return 0;
}
