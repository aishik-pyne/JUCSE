use ass1;
select upper(EMP.EMP_NAME) as 'name', EMP.BASIC as 'basic', DEPARTMENT.DEPT_NAME as 'dept'
from EMP, DEPARTMENT
where EMP.DEPT_CODE=DEPARTMENT.DEPT_CODE
order by DEPARTMENT.DEPT_NAME;
