/*
 * File:   main.cpp
 * Author: jyrone and evan
 *
 * Created on November 21, 2011, 3:30 PM
 * This Project will take employees and output their salary, taking an xml file
 * in as the input
 */
#include "employeeprocessor.h"
#include <QString>
#include <getopt.h>
#include <QApplication>
#include <iostream>
#include <stdexcept>
#include <sstream>

class InputException : public std::exception{
    public:
        InputException(const char* msg) : m_msg(msg) {}
        virtual const char* what() const throw() {return m_msg;}
    private:
        const char* m_msg;
};

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    if(!(argc > 1))
        throw(InputException("You must specify an argument. Use -H for usage."));

    try{
        const char* optstring = "f:Ha:";

        int c;
        std::string employeeFile;
        while((c=getopt(argc, argv, optstring))!= -1){
            switch(c){
                case 'f':
                {
                    //Parse indicated employees file and print pay information.
                    std::istringstream is(optarg);
                    char leftoverChar;
                    if(!(is >> employeeFile) || is.get(leftoverChar))
                        throw(InputException("Invalid argument for employees file."));
                    QString file = QString::fromStdString(employeeFile);
                    EmployeeProcessor processor(file);
                    processor.print();
                    break;
                }
                case 'a':
                {
                    //Retrieve information about new employee and serialize to specified XML file.
                    std::string firstName, lastName, fileName;
                    std::string employeeType;
                    double hours, overtime, payRate;
                    std::istringstream is(optarg);
                    char leftoverChar;
                    if(!(is >> firstName) || !(is >> lastName) || !(is >> fileName) || is.get(leftoverChar))
                        throw(InputException("Invalid argument for new employee"));
                    else{
                        std::cout << "Hourly or salary? (h/s)";
                        std::cin >> employeeType;
                        if(employeeType == "h"){
                            std::cout << "Hours worked? ";
                            std::cin >> hours;
                            std::cout << "Overtime hours (#)? ";
                            std::cin >> overtime;
                            std::cout << "Pay rate? ";
                            std::cin >> payRate;
                            HourlyEmployee* employee = new HourlyEmployee(firstName, lastName, hours, overtime, payRate);
                            EmployeeProcessor* processor = new EmployeeProcessor(employee);
                            QString file = QString::fromStdString(fileName);
                            processor->save(file, "h");
                        }
                        else if (employeeType == "s"){
                            std::cout << "Pay rate? ";
                            std::cin >> payRate;
                            SalaryEmployee* employee = new SalaryEmployee(firstName, lastName, payRate);
                            EmployeeProcessor* processor = new EmployeeProcessor(employee);
                            QString file = QString::fromStdString(fileName);
                            processor->save(file, "s");
                        }
                        else
                            throw(InputException("Invalid employee type."));
                    }
                    break;
                }
                case '?':
                case 'H':
                default:
                {
                    std::cerr << "Usage: " << argv[0] << "[-a \"firstname lastname file\" -f \"file\" -H] \n"
                              << "Options:\n"
                              << "-a [firstname lastname filename]    Create a new employee.\n"
                              << "-f [filename]                       Print the payroll information of a specified XML file.\n"
                              << "-H                                  Display this message.\n";
                    exit(-1);
                    break;
                }
            }
        }
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
    }
    return 0;
}
