CREATE OR REPLACE TRIGGER trig_gen_emp_pk
BEFORE INSERT ON employees
FOR EACH ROW
BEGIN
 SELECT employees_seq.nextval into :new.employee_id FROM dual;
END;
/

CREATE SEQUENCE dependents_seq
 START WITH     4000
 INCREMENT BY   100
 MAXVALUE       10000
 NOCACHE
 NOCYCLE;

CREATE OR REPLACE TRIGGER trig_gen_dependent_pk
BEFORE INSERT ON dependents
FOR EACH ROW
BEGIN
 SELECT dependents_seq.nextval into :new.id FROM dual;
END;
/
