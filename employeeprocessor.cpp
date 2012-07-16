/*
 * File:   EmployeeProcessor.cpp
 * Author: evan
 *
 * Created on November 21, 2011, 3:49 PM
 */

#include "employeeprocessor.h"
#include "salaryemployee.h"
#include "hourlyemployee.h"
#include <cassert>
#include <QFile>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QDomNode>
#include <QDomElement>
#include <QDomDocument>

EmployeeProcessor::EmployeeProcessor(QString &employeeFile) {
    assert(m_hourlyEmployees.empty());
    assert(m_salaryEmployees.empty());

    //Load and validate the XML schema.
    QFile schema_file(":/xsd/payroll.xsd");
    if (!schema_file.open(QIODevice::ReadOnly))
        throw Exception("Could not open employee list schema file.");
    QXmlSchema schema;
    schema.load(&schema_file,QUrl::fromLocalFile(schema_file.fileName()));
    if(!schema.isValid())
        throw Exception("Employee list schema definition is invalid.");

    //Load and validate the emplyees XML file according to the XML schema.
    QFile file(employeeFile);
    if (!file.open(QIODevice::ReadOnly))
        throw Exception("Could not open the employees file");
    QXmlSchemaValidator validator(schema);
    if(!validator.validate(&file, QUrl::fromLocalFile(file.fileName()))){
        file.close();
        throw EmployeeProcessor::Exception("Employees file is invalid according to the schema.");
    }

    //Parse employees XML file into classes.
    file.reset();
    QDomDocument doc("employees");
    if(!doc.setContent(&file)){
        file.close();
        throw EmployeeProcessor::Exception("Error parsing employees file");
    }

    QDomNodeList hourlyEmployees = doc.elementsByTagName("hourlyEmployee");
    for(int i=0; i<hourlyEmployees.size(); ++i){
        QDomNode employeeNode = hourlyEmployees.item(i);
        Employee* employee = new HourlyEmployee(employeeNode);
        m_employees.push_back(employee);
    }
    QDomNodeList salaryEmployees = doc.elementsByTagName("salaryEmployee");
    for(int i=0; i<salaryEmployees.size(); ++i){
        QDomNode employeeNode = salaryEmployees.item(i);
        Employee* employee = new SalaryEmployee(employeeNode);
        m_employees.push_back(employee);
    }
    file.close();
}

EmployeeProcessor::EmployeeProcessor(HourlyEmployee* employee){
    m_employees.push_back(employee);
}

EmployeeProcessor::EmployeeProcessor(SalaryEmployee* employee){
    m_employees.push_back(employee);
}

void EmployeeProcessor::print() const{
    for(uint i=0; i < m_employees.size(); ++i){
        m_employees[i]->print();
    }
}

void EmployeeProcessor::save(const QString& fileName, std::string employeeType){
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QDomDocument doc;
    QDomElement root = doc.createElement("employee");
    doc.appendChild(root);

    for(uint i=0; i < m_employees.size(); ++i){
        Employee* e = m_employees[i];
        e->saveToDomElement(root);
    }

    file.write(doc.toByteArray(2));
    file.close();
}
