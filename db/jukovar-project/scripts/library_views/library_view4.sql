-- Получение сводной таблицы, содержащей информацию
-- о самых ходовых жанрах в библиотеке.
-- Отсортируем по убыванию результирующей колонки
create or replace view library.popular_genres as
with 
	book_reserved as
			(select b.book_id, title, count(*) as total_reserved
			from library.Book b
			left join library.Book_Reserve br on b.book_id = br.book_id
			left join library.Reserve r on br.res_id = r.res_id
			group by b.book_id
			order by b.book_id)
select g.genre_id, genre_name, sum(total_reserved) as total_reserved
from book_reserved b_res
join library.Book_Genre bg on b_res.book_id = bg.book_id
join library.Genre g on bg.genre_id = g.genre_id
group by g.genre_id
order by total_reserved desc;

select * from library.popular_genres;
