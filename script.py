import re
import subprocess

command = './payroll -a "Jyrone Parker newemployees.xml" -f newemployees.xml < salary.txt'

result = subprocess.getstatusoutput(command)
if result[0]!=0:
    print("An error occured:")
    print(result[1])
else:
    employee = re.search('(?=Employee: ).*', result[1])
    pay = re.search('(?=Pay \(before taxes\): ).*', result[1])
    e = str(employee.group())
    p = str(pay.group())
    print(e)
    print(p, '\n')

command = './payroll -a "Evan Zeller newemployees.xml" -f newemployees.xml < hourly.txt'

result = subprocess.getstatusoutput(command)
if result[0]!=0:
    print("An error occured:")
    print(result[1])
else:
    employee = re.search('(?=Employee: ).*', result[1])
    pay = re.search('(?=Pay \(before taxes\): ).*', result[1])
    e = str(employee.group())
    p = str(pay.group())
    print(e,)
    print(p, '\n')

command = './payroll -H'

result = subprocess.getstatusoutput(command)
if result[0]!=0:
    print("An error occured:")
    print(result[1])
else:
    output = re.search('*', result[1])
    print(output)
