CREATE TABLE dependents (
  id NUMBER(6),
  first_name    VARCHAR2(20),
  last_name     VARCHAR2(25)
    constraint dep_last_name_nn NOT NULL,
  birthdate     DATE,
  relation      VARCHAR2(25),
  gender        VARCHAR2(1),
  relative_id   NUMBER(6)
   CONSTRAINT emp_dep_rel_id_fk REFERENCES EMPLOYEES (employee_id),
  benefits      CLOB
)
/
