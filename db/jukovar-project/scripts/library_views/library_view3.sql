-- Сокрытие поля с персональными данными посетителей 
-- из таблицы Reserve для отображения информации о брони
create or replace view library.res_info as
select distinct on (name, surname) 
	   res_id,
	   name,
	   surname,
	   substring(phone, 1, position('-' in phone) + 4) || '***-**-**' as phone
from library.Reserve;

select * from library.res_info;
