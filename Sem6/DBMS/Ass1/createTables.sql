use ass1;
create table EMP (
	EMP_CODE varchar(5) NOT NULL,
    EMP_NAME varchar(20),
    DEPT_CODE varchar(5),
    DESIG_CODE varchar(5),
    SEX varchar(1),
    ADDRESS varchar(25),
    CITY varchar(20),
    STATE varchar(20),
    PIN varchar(6),
    BASIC numeric default 0,
    JN_DT datetime default current_timestamp,
    
    primary key(EMP_CODE)

);
create table DESIGNATION (
	DESIG_CODE char(5),
    DESIG_DESC char(20),
    
    primary key(DESIG_CODE)
);
create table DEPARTMENT (
	DEPT_CODE char(5),
    DEPT_NAME char(15),
    
    primary key(DEPT_CODE)

);