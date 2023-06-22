-- Сокрытие полей с технической информацией о расположении книг
create or replace view library.book_location as
select wardrobe, '**' || shelf::varchar(10) as shelf, b.book_id, title
from library.book b
join library.Location l on l.book_id = b.book_id
order by wardrobe, shelf;

select * from library.book_location;
