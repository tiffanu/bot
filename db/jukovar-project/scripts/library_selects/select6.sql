-- Для каждого посетителя вывести его самый долгий период (в днях),
-- на который он брал книгу, и название этой книги
select distinct on (name, surname) name, surname, title, res_days
from (select name, surname, title, 
 	    	 end_date - begin_date as res_days, 
 			 first_value(end_date - begin_date) over (partition by r.res_id)
	  from library.Reserve as r
	  join library.Book_Reserve as br on br.res_id = r.res_id
	  join library.Book as b on b.book_id = br.book_id) as prt
where res_days = first_value
