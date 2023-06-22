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
