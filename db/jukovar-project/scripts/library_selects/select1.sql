-- Вывести все заполненные шкафы (кол-во книг на них больше 9)
select sum(amount) as total_amount, wardrobe
from library.Book as b
join library.Location as l
on b.book_id = l.book_id
group by wardrobe
having sum(amount) > 9;
