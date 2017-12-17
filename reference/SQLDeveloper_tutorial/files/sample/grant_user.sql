

REM =======================================================
REM grant user necessary privileges
REM =======================================================


GRANT CREATE SESSION, CREATE VIEW, ALTER SESSION, CREATE TABLE, 
 CREATE TRIGGER, CREATE PROCEDURE, CREATE SEQUENCE TO &usr;
