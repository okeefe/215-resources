Create a function that returns a salary value based on an employee ID. The salary value can be the actual value from the EMPLOYEES table, or a calculated value based on the parameter you pass to the function.

create or replace function get_sal
(p_id in employees.employee_id%type,
 p_increment in number := 1)
RETURN NUMBER
IS 
  v_sal employees.salary%TYPE := 0;

Sheila types in the declarative section of the code and defines a local variable. The local variable is name v_sal. Note the data type for the variable. The employees.salary%type means to use the same data type as the salary column in the EMPLOYEES table.

BEGIN
 SELECt salary * P_increment
   INTO v_sal
   FROM employees
   WHERE employee_id = p_id;
 RETURN v_sal;
END get_sal;

Sheila types in the body for the function. The local variable v_sal will hold the salary amount multiplied by the value of the p_increment parameter defaults to 1.

select last_name, employee_id, salary, get_sal(employee_id, 1.4) "Proposed Salary" from employees;

Sheila finishes typing her SQL statement. Note the call to the GET_SAL function in Sheila's SELECT list. She calls the function and passes the employee ID as the first parameter and the salary adjustment for the second parameter.

create or replace function get_sal
(p_id in employees.employee_id%type,
 p_increment in number := 1)
RETURN NUMBER
IS 
  v_sal employees.salary%TYPE := 0;
BEGIN
 SELECt salary * P_increment
   INTO v_sal
   FROM employees
   WHERE employee_id = p_id;
 RETURN v_sal;
END get_sal;


