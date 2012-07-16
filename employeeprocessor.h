/*
 * File:   EmployeeProcessor.h
 * Author: evan
 *
 * Created on November 21, 2011, 3:49 PM
 */

#ifndef EMPLOYEEPROCESSOR_H
#define	EMPLOYEEPROCESSOR_H
#include <vector>
#include "employee.h"
#include "hourlyemployee.h"
#include "salaryemployee.h"
#include <QString>
#include <string>
#include <stdexcept>



class EmployeeProcessor{
public:
    EmployeeProcessor(QString &employeeFile);
    EmployeeProcessor(HourlyEmployee* employee);
    EmployeeProcessor(SalaryEmployee* employee);
    void print() const;
    void save(const QString &fileName, std::string employeeType);

    class Exception : public std::exception{
    public:
        Exception(const char* msg) : m_msg(msg) {}
        virtual const char* what() const throw() {return m_msg;}
    private:
        const char* m_msg;
    };

private:
    std::vector<HourlyEmployee*> m_hourlyEmployees;
    std::vector<SalaryEmployee*> m_salaryEmployees;
    std::vector<Employee*> m_employees;
};

#endif	/* EMPLOYEEPROCESSOR_H */

