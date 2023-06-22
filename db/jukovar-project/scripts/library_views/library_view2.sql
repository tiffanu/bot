-- Получение сводной таблицы с технической информацией для отображения
-- пользовательской информации о наличии книг в библиотеке
create or replace view library.books_view as
with 
	reserved_books as (select b.book_id,
						   case when begin_date <= now() and now() <= end_date then 1
																			   else 0
						   end as is_reserved
   					   from library.Book b
   					   left join library.Book_Reserve br on b.book_id = br.book_id
   					   left join library.Reserve r on br.res_id = r.res_id
   					   order by b.book_id),
	total_res as (select reserved_books.book_id, sum(is_reserved) as sum
			  from reserved_books
			  group by book_id)
select t.book_id,
	   title,
	   case when amount - t.sum >= 5 then 'Есть в наличии'
	   	    when amount - t.sum < 5 and amount - t.sum > 0 then 'Заканчивается'
			else 'Нет в наличии'
	   end as in_stock
from library.book b 
join total_res t on b.book_id = t.book_id;

select * from library.books_view;
