create schema if not exists library; 

create table if not exists library.Book (
	book_id integer not null primary key,
	title varchar(100) not null,
	amount integer not null
);

create table if not exists library.Location (
	book_id integer not null primary key,
	wardrobe integer not null,
	shelf integer not null,
		foreign key (book_id) references library.Book(book_id) on delete cascade
);

create table if not exists library.Author (
	author_id integer not null primary key,
	author_name varchar(50) not null,
	author_surname varchar(50),
	birth_date date,
	death_date date
);

create table if not exists library.Alias_Author (
	alias_id integer not null primary key,
	alias varchar(50) not null,
	author_id integer not null,
		foreign key (author_id) references library.Author(author_id) on delete cascade 
);

create table if not exists library.Book_Alias (
	book_id integer not null,
	alias_id integer not null,
		primary key (book_id, alias_id),
		foreign key (alias_id) references library.Alias_Author(alias_id) on delete cascade, 
		foreign key (book_id) references library.Book(book_id) on delete cascade 
);

create table if not exists library.Genre (
	genre_id integer not null primary key,
	genre_name varchar(50) not null
);

create table if not exists library.Book_Genre (
	book_id integer not null,
	genre_id integer not null,
		primary key (book_id, genre_id),
		foreign key (genre_id) references library.Genre(genre_id) on delete cascade, 
		foreign key (book_id) references library.Book(book_id) on delete cascade 
);

create table if not exists library.Reserve (
	res_id integer not null primary key,
	name varchar(50) not null,
	surname varchar(50),
	phone varchar(20),
	address varchar(100),
	begin_date date,
	end_date date
);

create table if not exists library.Book_Reserve (
	book_id integer not null,
	res_id integer not null,
		primary key (book_id, res_id),
		foreign key (res_id) references library.Reserve(res_id), 
		foreign key (book_id) references library.Book(book_id) 
);
