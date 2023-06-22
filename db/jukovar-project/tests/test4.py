import os
import pytest
import datetime
from . import execute_sql_to_df
from . import read_sql


@pytest.fixture()
def select_script():
    path = os.getenv("SCRIPT_PATH")
    return read_sql(path)


@pytest.fixture()
def select_df(select_script, sqlalchemy_conn):
    return execute_sql_to_df(
        conn=sqlalchemy_conn,
        sql=select_script
    )


def test4(select_df):
    assert select_df.query("title == 'Евгений Онегин'")['author_name'].iloc[0] == 'Александр'
    assert select_df.query("title == 'Евгений Онегин'")['author_surname'].iloc[0] == 'Пушкин'
    assert select_df.query("title == 'Евгений Онегин'")['book_number_per_author'].iloc[0] == 1

    assert select_df.query("title == 'Мартин Иден'")['author_name'].iloc[0] == 'Джек'
    assert select_df.query("title == 'Мартин Иден'")['author_surname'].iloc[0] == 'Лондон'
    assert select_df.query("title == 'Мартин Иден'")['book_number_per_author'].iloc[0] == 1
    
    assert select_df.query("title == 'Фауст'")['author_name'].iloc[0] == 'Иоганн'
    assert select_df.query("title == 'Фауст'")['author_surname'].iloc[0] == 'Гёте'
    assert select_df.query("title == 'Фауст'")['book_number_per_author'].iloc[0] == 1

    assert select_df.query("title == 'Герой нашего времени'")['author_name'].iloc[0] == 'Михаил'
    assert select_df.query("title == 'Герой нашего времени'")['author_surname'].iloc[0] == 'Лермонтов'
    assert select_df.query("title == 'Герой нашего времени'")['book_number_per_author'].iloc[0] == 1

    assert select_df.query("title == 'Государство'")['author_name'].iloc[0] == 'Платон'
    assert select_df.query("title == 'Государство'")['author_surname'].iloc[0] == None
    assert select_df.query("title == 'Государство'")['book_number_per_author'].iloc[0] == 1

    assert select_df.query("title == 'Бесы'")['author_name'].iloc[0] == 'Фёдор'
    assert select_df.query("title == 'Бесы'")['author_surname'].iloc[0] == 'Достоевский'
    assert select_df.query("title == 'Бесы'")['book_number_per_author'].iloc[0] == 1

    assert select_df.query("title == 'Братья Карамазовы'")['author_name'].iloc[0] == 'Фёдор'
    assert select_df.query("title == 'Братья Карамазовы'")['author_surname'].iloc[0] == 'Достоевский'
    assert select_df.query("title == 'Братья Карамазовы'")['book_number_per_author'].iloc[0] == 2
