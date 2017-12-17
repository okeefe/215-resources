how to add exception handline into Sheila's PL/SQL code. The GET_SAL function is modified to include exception handling.

after v_sal employees.salary....

e_toomuch EXCEPTION;

Sheila defines an exception named "e_toomuch". She will use this defined exception to ensure that the increment amount passed into the function is a valid amount. If the amount is not valid, the error e_toomuch is raised.

After BEGIN, add

IF p_increment < 1 or p_increment > 1.5 THEN
   RAISE e_toomuch;
END IF;

Sheila adds the code that insures that the increment amount passed into the function is a valid amount. A valid amount is considered to be between the value of 1 and 1.5. If the amount is not valid, the error e_toomuch is raised.

Add after RETUNR v_sal;

EXCEPTION
  WHEN e_toomuch THEN
    htp.print('Invalid increment amount');
  WHEN NO_DATA_FOUND THEN
    htp.print ('Invalid employee id');
  WHEN OTHERS THEN
    htp.print ('Error occurred in processing');

Sheila adds the exception handler section of the code. She identifies 3 types of errors. The exception e_toomuch catches for invalid p_increment amounts passed into the function. The NO_DATA_FOUND exception is raised when the SELECT statement returns no rows, meaning that the p_id parameter is invalid. The OTHERS exception catches for any other raised exceptions.

To test...

Sheila types in a SELECT statement that calls her GET_SAL parameters. She passes the values 1000 and 1.1 to the function. 1000 is not a valid employee Id, so this should raise the NO_DATA_FOUND error.

select last_name, get_sal(1000, 1.1) from employees;

change 1000 to 101

change 1.1 to .1

change .1 to 2



CREATE OR REPLACE function get_sal
(p_id IN employees.employee_id%TYPE,
 p_increment IN NUMBER := 1)
RETURN NUMBER
IS
  v_sal employees.salary%TYPE := 0;
  e_toomuch EXCEPTION;
BEGIN
  IF p_increment < 1 or p_increment > 1.5 THEN
     RAISE e_toomuch;
  END IF;
  SELECT salary * p_increment
    INTO v_sal
    FROM employees
    WHERE employee_id = p_id;
  RETURN v_sal;
  EXCEPTION
  WHEN e_toomuch THEN
    htp.print('Invalid increment amount');
  WHEN NO_DATA_FOUND THEN
    htp.print ('Invalid employee id');
  WHEN OTHERS THEN
    htp.print ('Error occurred in processing');
END get_sal;
