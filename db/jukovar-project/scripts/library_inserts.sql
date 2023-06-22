insert into library.Book values 
(1, 'Братья Карамазовы', 5),
(2, 'Фауст', 7),
(3, 'Мартин Иден', 3),
(4, 'Евгений Онегин', 15),
(5, 'Герой нашего времени', 10),
(6, 'Бесы', 4),
(7, 'Государство', 5); 


insert into library.Author values 
(1, 'Фёдор', 'Достоевский', '11.11.1821', '02.09.1881'),
(2, 'Иоганн', 'Гёте', '8.28.1749', '03.22.1832'),
(3, 'Джек', 'Лондон', '01.12.1876', '11.22.1916'),
(4, 'Александр', 'Пушкин', '06.06.1799', '02.10.1837'),
(5, 'Михаил', 'Лермонтов', '10.15.1814', '07.27.1841'),
(6, 'Платон', null, null, null),
(7, 'Михаил', 'Булгаков', '05.15.1891', '03.10.1940'); 


insert into library.Location values 
(1, 1, 3),
(2, 2, 4),
(3, 2, 3),
(4, 1, 1),
(5, 1, 2),
(6, 1, 4),
(7, 3, 3); 


insert into library.Genre values 
(1, 'Роман'),
(2, 'Роман в стихах'),
(3, 'Диалог'),
(4, 'Трагедия'),
(5, 'Комедия'); 


insert into library.Reserve values 
(1, 'Артём', null, '+7-965-415-28-39', 'Москва', '2.5.2023', '2.6.2023'),
(2, 'Альбина', 'Рухадзе', null, 'Долгопрудный', '3.5.2023', '3.6.2023'),
(3, 'Тимур', 'Муцураев', null, 'Грозный', '12.11.1994', '08.31.1996'),
(4, 'Александр', 'Левин', null, 'Лобня', '10.6.2023', '10.8.2023'),
(5, 'Артём', null, '+7-965-415-28-39', 'Москва', '7.23.2023', '8.23.2023');


insert into library.Book_Reserve (book_id, res_id) values
(1, 1),
(7, 1),
(2, 2),
(3, 3),
(4, 4),
(6, 2);


insert into library.Book_Genre (book_id, genre_id) values
(1, 1),
(2, 4),
(3, 1),
(4, 2),
(5, 1),
(6, 1),
(7, 3);


insert into library.Alias_Author (alias_id, alias, author_id) values
(1, 'Фёдор Достоевский', 1),
(2, 'Иоганн Гёте', 2),
(3, 'Джек Лондон', 3),
(4, 'Александр Пушкин', 4),
(5, 'Михаил Лермонтов', 5),
(6, 'Платон', 6);


insert into library.Book_Alias (book_id, alias_id) values
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5),
(6, 1),
(7, 6);