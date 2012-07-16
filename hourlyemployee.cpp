/*
 * File:   hourly.cpp
 * Author: jyrone
 *
 * Created on November 21, 2011, 3:48 PM
 */

#include "hourlyemployee.h"
#include <iostream>
#include <iomanip>
#include <cassert>

HourlyEmployee::HourlyEmployee(QDomNode &employeeNode){

    QDomElement elem = employeeNode.namedItem("firstName").toElement();
    assert(!elem.isNull());
    m_firstName = elem.text().toStdString();

    elem = employeeNode.namedItem("lastName").toElement();
    assert(!elem.isNull());
    m_lastName = elem.text().toStdString();

    elem = employeeNode.namedItem("hours").toElement();
    assert(!elem.isNull());
    m_hours = elem.text().toDouble();

    elem = employeeNode.namedItem("payRate").toElement();
    assert(!elem.isNull());
    m_pay_rate = elem.text().toDouble();

    elem = employeeNode.namedItem("overtime").toElement();
    assert(!elem.isNull());
    m_overtime = elem.text().toDouble();
}

double HourlyEmployee::calculatePay()
{
    const double overtimeExtraPay = 1.50;
    if(!(m_overtime == 0))
        return m_hours*m_pay_rate + m_overtime*(overtimeExtraPay+m_pay_rate);
    else
        return m_hours*m_pay_rate;
}

void HourlyEmployee::print(){
    std::cout << "Employee: " << m_firstName << " " << m_lastName << "\n"
              << "Pay (before taxes): $" << calculatePay() << "\n\n";
}

void HourlyEmployee::saveToDomElement(QDomElement& parentElement) const{
    QDomDocument doc = parentElement.ownerDocument();

    const QString elementType(this->elementType());

    QDomElement domElem = doc.createElement(elementType);
    parentElement.appendChild(domElem);

    QDomElement firstName = doc.createElement("firstName");
    domElem.appendChild(firstName);
    QDomText firstNameText = doc.createTextNode(QString::fromStdString(m_firstName));
    firstName.appendChild(firstNameText);

    QDomElement lastName = doc.createElement("lastName");
    domElem.appendChild(lastName);
    QDomText lastNameText = doc.createTextNode(QString::fromStdString(m_lastName));
    lastName.appendChild(lastNameText);

    QDomElement hours = doc.createElement("hours");
    domElem.appendChild(hours);
    QDomText hoursText = doc.createTextNode(QString::number(m_hours));
    hours.appendChild(hoursText);

    QDomElement payRate = doc.createElement("payRate");
    domElem.appendChild(payRate);
    QDomText payRateText = doc.createTextNode(QString::number(m_pay_rate));
    payRate.appendChild(payRateText);

    QDomElement overtime = doc.createElement("overtime");
    domElem.appendChild(overtime);
    QDomText overtimeText = doc.createTextNode(QString::number(m_overtime));
    overtime.appendChild(overtimeText);
}
