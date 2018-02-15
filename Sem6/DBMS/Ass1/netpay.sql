select EMP_NAME, (BASIC + 0.5*BASIC + 0.4*BASIC) as 'net pay'
from EMP
where BASIC is not null;

