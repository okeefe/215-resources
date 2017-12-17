create or replace
FUNCTION GET_LOCATION
( p_deptname IN VARCHAR2) RETURN VARCHAR2 
AS
  v_loc_id NUMBER;
  v_city   VARCHAR2(30);
BEGIN
  SELECT d.location_id, l.city INTO v_loc_id, v_city
  FROM departments d, locations l
  WHERE upper(department_name) = upper(p_deptname)
  and d.location_id = l.location_id;
  RETURN v_city;
END GET_LOCATION;
/

create or replace
PROCEDURE EMP_LIST 
( pMaxRows IN NUMBER) 
AS
CURSOR emp_cursor IS
  SELECT d.department_name, e.employee_id, e.last_name,
         e.salary, e.commission_pct
  FROM  departments d, employees e
  WHERE d.department_id = e.department_id;
  emp_record emp_cursor%ROWTYPE;
  TYPE emp_tab_type IS TABLE OF emp_cursor%ROWTYPE INDEX BY BINARY_INTEGER;
  emp_tab emp_tab_type;
i NUMBER := 1;
v_city VARCHAR2(30); 
BEGIN
  OPEN emp_cursor;
  FETCH emp_cursor INTO emp_record;
  emp_tab(i) := emp_record;
  WHILE (emp_cursor%FOUND) AND (i <= pMaxRows) LOOP
     i := i + 1;
     FETCH emp_cursor INTO emp_record;
     emp_tab(i) := emp_record;
     v_city := get_location (emp_record.department_name);
     dbms_output.put_line('Employee ' || emp_record.last_name ||
       ' works in ' || v_city );
  END LOOP;
  CLOSE emp_cursor;
  FOR j IN REVERSE 1..i LOOP
     DBMS_OUTPUT.PUT_LINE(emp_tab(j).last_name);
  END LOOP;
END emp_list; 
/
