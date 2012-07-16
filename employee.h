/*
 * File:   employee.h
 * Author: evan
 *
 * Created on November 21, 2011, 3:39 PM
 */

#ifndef EMPLOYEE_H
#define	EMPLOYEE_H
#include <QtCore>
#include <QString>
#include <QDomNode>
class Employee {
public:
    Employee(){}
    virtual double calculatePay()=0;
    virtual void print()=0;
    virtual void saveToDomElement(QDomElement& parentElement) const=0;
};
#endif	/* EMPLOYEE_H */

