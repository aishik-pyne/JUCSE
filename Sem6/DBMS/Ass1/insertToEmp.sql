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
	('001', 'Aishik', 'M', 'mngr', 'rshr', '6A', 'Kolkata', '700014', 'WestBengal', 1500000),
	('002', 'Manosij','M', 'hlpr', 'rshr', '64', 'Kolkata', '700014', 'WestBengal', 1100000),
	('003', 'Baidik', 'M', 'exec', 'finn', '23', 'Kolkata', '700097', 'WestBengal', 2000000),
	('004', 'Soumik', 'M', 'clrk', 'rshr', '75', 'Kolkata', '700045', 'WestBengal', 600000),
	('005', 'Saaket', 'M', 'mngr', 'prod', '1D', 'Jamtara', '815315', 'Jharkhand',  1500000),
	('006', 'Ananya', 'F', 'ofcr', 'purc', '9B', 'Guahati', '986421', 'WestBengal', 1500000); 