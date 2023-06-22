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


def test6(select_df):
    assert select_df.query("name == 'Александр'")['surname'].iloc[0] == 'Левин'
    assert select_df.query("name == 'Александр'")['title'].iloc[0] == 'Евгений Онегин'
    assert select_df.query("name == 'Александр'")['res_days'].iloc[0] == 2

    assert select_df.query("name == 'Альбина'")['surname'].iloc[0] == 'Рухадзе'
    assert select_df.query("name == 'Альбина'")['title'].iloc[0] == 'Фауст'
    assert select_df.query("name == 'Альбина'")['res_days'].iloc[0] == 1

    assert select_df.query("name == 'Артём'")['surname'].iloc[0] == None
    assert select_df.query("name == 'Артём'")['title'].iloc[0] == 'Братья Карамазовы'
    assert select_df.query("name == 'Артём'")['res_days'].iloc[0] == 1

    assert select_df.query("name == 'Тимур'")['surname'].iloc[0] == 'Муцураев'
    assert select_df.query("name == 'Тимур'")['title'].iloc[0] == 'Мартин Иден'
    assert select_df.query("name == 'Тимур'")['res_days'].iloc[0] == 629
