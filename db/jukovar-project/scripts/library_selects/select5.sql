-- Вывести посетителей и кол-во книг, которые они брали.
-- Отсортировать по этому количеству
select distinct name, surname, count(book_id) over (partition by (name, surname)) as reserved_books
from library.Book_Reserve as br
join library.Reserve as r on r.res_id = br.res_id
order by reserved_books desc;
