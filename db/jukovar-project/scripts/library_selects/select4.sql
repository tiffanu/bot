-- Вывести авторов с порядковым номером их книг из библиотеки 
select author_name, author_surname, title,
	   rank() over (partition by (author_name, author_surname) order by title) as book_number_per_author
from library.Author as a
join library.Alias_Author as aa on a.author_id = aa.author_id
join library.Book_Alias as ba on aa.alias_id = ba.alias_id
join library.Book as b on ba.book_id = b.book_id;
