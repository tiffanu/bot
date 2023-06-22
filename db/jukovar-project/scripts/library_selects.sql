-- Вывести все заполненные шкафы (кол-во книг на них больше 9)
select sum(amount) as total_amount, wardrobe
from library.Book as b
join library.Location as l
on b.book_id = l.book_id
group by wardrobe
having sum(amount) > 9;


-- Вывести всех посетителей, взявших книги, 
-- и отсортировать по дате начала брони
select name, surname, begin_date, end_date
from library.Reserve
order by begin_date, end_date;

-- Вывести жанры книг в нашей библиотеке, отсортировать
-- по количеству произведений, а также вывести их ранг
select rank() over (order by count(b.book_id) desc) as rank,
       genre_name, 
	   count(b.book_id)
from library.Book as b
join library.Book_Genre as bg
on bg.book_id = b.book_id
join library.Genre as g
on g.genre_id = bg.genre_id
group by genre_name;


-- Вывести авторов с порядковым номером их книг из библиотеки 
select author_name, author_surname, title,
	   rank() over (partition by (author_name, author_surname) order by title) as book_number_per_author
from library.Author as a
join library.Alias_Author as aa on a.author_id = aa.author_id
join library.Book_Alias as ba on aa.alias_id = ba.alias_id
join library.Book as b on ba.book_id = b.book_id;


-- Вывести посетителей и кол-во книг, которые они брали.
-- Отсортировать по этому количеству
select distinct name, surname, count(book_id) over (partition by (name, surname)) as reserved_books
from library.Book_Reserve as br
join library.Reserve as r on r.res_id = br.res_id
order by reserved_books desc;


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