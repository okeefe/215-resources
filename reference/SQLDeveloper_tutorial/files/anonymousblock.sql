DECLARE
  v_user varchar2(30);
BEGIN
  select sys_context('userenv','current_user') into v_user from dual;
  dbms_output.put_line('Reported at: '||TO_CHAR(SYSDATE,'DD-Mon-YY HH:MIPM'));
  dbms_output.put_line('User = '||v_user);
END;