/*
 * File:   salaryemployee.h
 * Author: evan
 *
 * Created on November 21, 2011, 10:05 PM
 */

#ifndef SALARYEMPLOYEE_H
#define	SALARYEMPLOYEE_H

#include "employee.h"
#include <string>

class SalaryEmployee: public Employee {
public:
    SalaryEmployee(const QDomNode employeeNode);
    SalaryEmployee(std::string firstName, std::string lastName, double payRate):
                    m_firstName(firstName), m_lastName(lastName), m_pay_rate(payRate) {}
    virtual double calculatePay();
    virtual void print();
    virtual void saveToDomElement(QDomElement& parentElement) const;
    virtual QString elementType() const{return "salaryEmployee";}
private:
    std::string m_firstName;
    std::string m_lastName;
    double m_hours;
    double m_pay_rate;

};


#endif	/* SALARYEMPLOYEE_H */

