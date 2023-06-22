-- Получение сводной таблицы о самых частых посетителях
create or replace view library.clients_view as
select name, surname, count(*) as books_reserved
from library.Reserve r
join library.Book_Reserve br on br.res_id = r.res_id
group by (name, surname, address)
order by count(*) desc;

select * from library.clients_view;
