CREATE DATABASE organization;
USE organization;
create table DEPARTMENT (
	DEPT_CODE char(5) NOT NULL,
    DEPT_NAME char(15),
    
    primary key(DEPT_CODE)

);

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
    BASIC numeric default 0 ,
    JOIN_DATE datetime default current_timestamp,
    
    PRIMARY KEY(EMP_CODE),
	CONSTRAINT CheckBasic CHECK (BASIC>=5000 AND BASIC<=9000)
);
create table LEAVE_REC (
	EMP_CODE varchar(5) NOT NULL,
    LEAVE_TYPE char(2),
    FROM_DATE datetime,
    TO_DATE datetime,
    PRIMARY KEY(EMP_CODE, FROM_DATE)
);