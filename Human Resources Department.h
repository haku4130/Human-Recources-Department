#ifndef LAB4_CPP_LIBRARY_HUMAN_RESOURCES_DEPARTMENT_H
#define LAB4_CPP_LIBRARY_HUMAN_RESOURCES_DEPARTMENT_H

#include <iostream>
#include <utility>
#include <vector>
#include <typeinfo>

using namespace std;

class Company;

class Employee {
protected:
    int id;
    string name;
    int birth_year;
    string position;
    string education;
    int salary;
    static int Count;
public:
    explicit Employee(string name = "Petrov P.P.",
                      int birth_year = 2000,
                      string position = "junior developer",
                      string education = "formal",
                      int salary = 20000);
    [[nodiscard]] int get_id() const;

    string get_info();

    void display_information();

    const char * get_type();

    string get_position();

    void set_position(string &new_pos);

    [[nodiscard]] int get_salary() const;

    void set_salary(int new_salary);
};

class Supervisor : public Employee {
private:
    Company *ptr_company;
public:
    Supervisor ();
};

class Company{
public:
    class Department {
    private:
        vector<Employee *> employees_array;
        string department_name;
    public:
        Department();
        explicit Department(const string &);
        string get_department_name();
        int add_employee(Employee *);
        Employee *search(int);
        void delete_employee(int id);
        int get_position(int id);
        void emp_to_sup(int id);
        void get_table();
    };
    Company ();
    explicit Company (const string &);
    Company::Department *search_dep(int);
    Employee *search (int);
    Department *search (const string &);
    void add_department (Company::Department *);
    void delete_employee(int id);
    string get_company_name();
    void get_table();
private:
    vector<Department *> departments;

    string company_name;
};

#endif
