project(payroll)

cmake_minimum_required(VERSION 2.6)

set(QT_USE_QTXML true)
set(QT_USE_QTXMLPATTERNS true)
find_package(Qt4 4.6 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(payroll_SOURCES main.cpp
                    employee.cpp
                    employeeprocessor.cpp
                    hourlyemployee.cpp
                    salaryemployee.cpp)

set(payroll_HEADERS employee.h
                    employeeprocessor.h
                    hourlyemployee.h
                    salaryemployee.h
)

set(payroll_RESOURCES payroll.qrc)
set(payroll_MISC_FILES payroll.xsd employees.xml)

set_source_files_properties(payroll.qrc 
                            PROPERTIES OBJECT_DEPENDS "payroll.xsd")

qt4_add_resources(payroll_RC_FILES ${payroll_RESOURCES})

ADD_EXECUTABLE(payroll ${payroll_SOURCES}
                       ${payroll_HEADERS}
                       ${payroll_RC_FILES}
                       ${payroll_RESOURCES}
                       ${payroll_MISC_FILES})

target_link_libraries(payroll ${QT_LIBRARIES})
