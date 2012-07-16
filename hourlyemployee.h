/*
 * File:   hourly.h
 * Author: jyrone
 *
 * Created on November 21, 2011, 3:48 PM
 */

#ifndef HOURLYEMPLOYEE_H
#define	HOURLYEMPLOYEE_H
#include "employee.h"
#include <string>
class HourlyEmployee: public Employee {
public:
    HourlyEmployee(QDomNode &employeeNode);
    HourlyEmployee(std::string firstName, std::string lastName, double hours, double overtime, double payRate) :
                    m_firstName(firstName), m_lastName(lastName), m_hours(hours), m_overtime(overtime), m_pay_rate(payRate){}
    virtual double calculatePay();
    virtual void print();
    virtual QString elementType() const{return "hourlyEmployee";}
    void saveToDomElement(QDomElement& parentElement) const;
private:
    std::string m_firstName;
    std::string m_lastName;
    double m_hours;
    double m_overtime;
    double m_pay_rate;

};

#endif	/* HOURLY_H */

