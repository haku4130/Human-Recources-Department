#ifndef LAB4_CPP_LIBRARY_HUMAN_RESOURCES_DEPARTMENT_H
#define LAB4_CPP_LIBRARY_HUMAN_RESOURCES_DEPARTMENT_H

#include <iostream>
#include <utility>
#include <vector>
#include <typeinfo>

using namespace std;

class Supervisor;
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
    Employee(const string &name, int birth_year, const string &position, const string &education, int salary);
    Employee();
    [[nodiscard]] int get_id() const;
    string get_name ();
    [[nodiscard]] int get_birth_year () const;
    string get_education ();
    string get_info();
    void display_information();
    const char * get_type();
    string get_position();
    void set_position(string &new_pos);
    [[nodiscard]] int get_salary() const;
    void set_salary(int new_salary);
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
        Employee *search(int id);
        void delete_employee(int id);
        int get_position(int id);
        void get_table();
        void free_department();
        int emp_to_sup (int id);
    };
    Company ();
    explicit Company (const string &);
    Department *search_dep_with_emp(int);
    Employee *search (int);
    Department *search (const string &);
    Department *get_department (int i);
    void add_department (Company::Department *);
    void delete_employee(int id);
    void delete_department (int i);
    string get_company_name();
    void get_table();
    void get_departments ();
    unsigned long get_dep_amount ();
    void free_company();
private:
    vector<Department *> departments;
    string company_name;
};

class Supervisor : public Employee {
private:
    Company::Department *ptr_department;
public:
    Supervisor ();
    Supervisor(const string &name, int birth_year, const string &position, const string &education, int salary);
    void set_department_ptr (Company::Department *ptr);
    Supervisor &operator = (Employee *);
};

#endif
