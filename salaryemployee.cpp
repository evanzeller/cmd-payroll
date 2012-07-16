#include "salaryemployee.h"
#include <iostream>
#include <cassert>

SalaryEmployee::SalaryEmployee(const QDomNode employeeNode){

    QDomElement elem = employeeNode.namedItem("firstName").toElement();
    assert(!elem.isNull());
    m_firstName = elem.text().toStdString();

    elem = employeeNode.namedItem("lastName").toElement();
    assert(!elem.isNull());
    m_lastName = elem.text().toStdString();

    elem = employeeNode.namedItem("payRate").toElement();
    assert(!elem.isNull());
    m_pay_rate = elem.text().toDouble();


}

double SalaryEmployee::calculatePay()
{
    return m_pay_rate/12;
}

void SalaryEmployee::print() {
    std::cout << "Employee: " << m_firstName << " " << m_lastName << "\n"
              << "Pay (before taxes): $" << calculatePay() <<"\n\n";
}

void SalaryEmployee::saveToDomElement(QDomElement& parentElement) const{
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

    QDomElement payRate = doc.createElement("payRate");
    domElem.appendChild(payRate);
    QDomText payRateText = doc.createTextNode(QString::number(m_pay_rate));
    payRate.appendChild(payRateText);
}
