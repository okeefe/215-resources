update employees
set salary=salary*(1+p_raise_amt)
where employee_id=p_id;