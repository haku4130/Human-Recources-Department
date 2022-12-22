#include <iostream>
#include "gtest/gtest.h"
#include "Human Resources Department.h"

using namespace std;

Company company("company");
auto dep = new Company::Department ("department");
auto dep2 = new Company::Department ("department2");
Company company1("company1");
auto emp = new Employee;
auto sup = new Supervisor;

TEST(company, get_name){
    string str = "company";
    ASSERT_STREQ(company.get_company_name().c_str(), str.c_str());
}

TEST(company, get_name2){
    string str = "company1";
    ASSERT_STREQ(company1.get_company_name().c_str(), str.c_str());
}

TEST(company, search_dep_by_emp){
    company.add_department(dep);
    dep->add_employee(emp);
    string str = "department";
    ASSERT_STREQ(dep->get_department_name().c_str(), company.search_dep_with_emp(emp->get_id())->get_department_name().c_str());
}

TEST(company, search_dep_by_emp2){
    company.add_department(dep2);
    auto emp2 = new Employee;
    dep2->add_employee(emp2);
    string str = "department2";
    ASSERT_STREQ(dep2->get_department_name().c_str(), company.search_dep_with_emp(emp2->get_id())->get_department_name().c_str());
}

TEST(company, search_emp){
    ASSERT_EQ(emp->get_id(), company.search(1)->get_id());
}

TEST(company, search_emp2){
    dep->add_employee(sup);
    ASSERT_EQ(sup->get_id(), company.search(2)->get_id());
}

TEST(company, search_dep){
    string str = "department";
    ASSERT_STREQ(str.c_str(), company.search("department")->get_department_name().c_str());
}

TEST(company, search_dep2){
    string str = "department2";
    ASSERT_STREQ(str.c_str(), company.search("department2")->get_department_name().c_str());
}

TEST(company, emp_to_sup) {
    dep->emp_to_sup(1);
    ASSERT_STREQ("Supervisor", dep->search(1)->get_type().c_str());
}

TEST(company, delete_emp){
    company.delete_employee(1);
    ASSERT_EQ(nullptr, company.search(1));
}

TEST(company, delete_emp2){
    company.delete_employee(2);
    ASSERT_EQ(nullptr, company.search(2));
}

TEST(company, delete_dep){
    company.delete_department(0);
    ASSERT_EQ(nullptr, company.search("department"));
}

TEST(company, delete_dep2){
    company.delete_department(1);
    ASSERT_EQ(nullptr, company.search("department2"));
}

int _tmain() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
