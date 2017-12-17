select e.first_name, e.last_name, l.street_address, l.city, l.state_province, l.postal_code
from employees e, departments d, locations l
where e.department_id=d.department_id
 and d.location_id=l.location_id
order by e.last_name;