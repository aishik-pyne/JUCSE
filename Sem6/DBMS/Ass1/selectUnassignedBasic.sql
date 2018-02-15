use ass1;
select * from EMP where EMP.DEPT_CODE is null;
select * from EMP where EMP.BASIC = 0;
select avg(BASIC) from EMP where EMP.BASIC is not null;