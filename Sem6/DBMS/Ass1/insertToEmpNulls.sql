use ass1;
insert into EMP 
	(
		EMP.EMP_CODE, 
		EMP.EMP_NAME,
        EMP.SEX,
        EMP.DESIG_CODE,
		EMP.DEPT_CODE,
        EMP.ADDRESS,
        EMP.CITY,
        EMP.PIN,
        EMP.STATE,
        EMP.BASIC
	)
values
	('007', 'Thakur', 	'M', 'mngr',	null, 	'6A', 'Kolkata', '700014', 'WestBengal', 0),
	('008', 'Chiranjit','M', 'hlpr', 	'rshr', '64', 'Kolkata', '700014', 'WestBengal', null),
	('009', 'Kaushal', 	'M', null,		'finn', '23', 'Kolkata', '700097', 'WestBengal', null),
	('010', 'Ankit', 	'M', null,		null, 	'75', 'Kolkata', '700045', 'WestBengal', 0);