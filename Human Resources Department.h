#ifndef LAB4_CPP_LIBRARY_HUMAN_RESOURCES_DEPARTMENT_H
#define LAB4_CPP_LIBRARY_HUMAN_RESOURCES_DEPARTMENT_H

#include <iostream>
#include <vector>

using namespace std;

class Company;

class Employee {
protected:
    int id;
    string name;
    int birth_year{};
    string position;
    string education;
    int salary{};
    static int Count;
public:
    Employee ();
    [[nodiscard]] int get_id() const;
};

class Supervisor : public Employee {
private:
    Company *ptr_company{};
public:
    Supervisor ();
};

class Company {
private:
    string company_name;
    vector<int> id_array;
    vector<Employee> employees_array;
public:
    int add_employee (Employee &);
    int in_company(int);
    int get_position(int);
};



#endif
