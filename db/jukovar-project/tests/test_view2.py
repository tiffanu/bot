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


def test2(select_df):
    assert select_df.query("book_id == 1")['title'].iloc[0] == 'Братья Карамазовы'
    assert select_df.query("book_id == 1")['in_stock'].iloc[0] == 'Есть в наличии'

    assert select_df.query("book_id == 2")['title'].iloc[0] == 'Фауст'
    assert select_df.query("book_id == 2")['in_stock'].iloc[0] == 'Есть в наличии'

    assert select_df.query("book_id == 3")['title'].iloc[0] == 'Мартин Иден'
    assert select_df.query("book_id == 3")['in_stock'].iloc[0] == 'Заканчивается'

    assert select_df.query("book_id == 4")['title'].iloc[0] == 'Евгений Онегин'
    assert select_df.query("book_id == 4")['in_stock'].iloc[0] == 'Есть в наличии'

    assert select_df.query("book_id == 5")['title'].iloc[0] == 'Герой нашего времени'
    assert select_df.query("book_id == 5")['in_stock'].iloc[0] == 'Есть в наличии'

    assert select_df.query("book_id == 6")['title'].iloc[0] == 'Бесы'
    assert select_df.query("book_id == 6")['in_stock'].iloc[0] == 'Заканчивается'

    assert select_df.query("book_id == 7")['title'].iloc[0] == 'Государство'
    assert select_df.query("book_id == 7")['in_stock'].iloc[0] == 'Есть в наличии'
