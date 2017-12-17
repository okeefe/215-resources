how to perform application auditing using database triggers.

create or replace TRIGGER TRIGGER1 AFTER UPDATE OF MANAGER_ID,SALARY,COMMISSION_PCT,BIRTHDATE,HIRE_DATE,PHONE_NUMBER,EMAIL,JOB_ID,DEPARTMENT_ID,LAST_NAME,FIRST_NAME,EMPLOYEE_ID ON EMPLOYEES 
FOR EACH ROW 
BEGIN
  insert into audit_record_tb1
  values(sys_context('userenv','current_user'),
    sysdate, :old.employee_id, :old.salary, :new.salary);
EXCEPTION
  when others then
     raise_application_error(-10001, 'audit trigger failure');
END;

update employees set salary=8000 where employee_id=200;

select * from audit_record_tb1;