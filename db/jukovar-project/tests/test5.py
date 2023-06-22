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


def test5(select_df):
    assert select_df.query("name == 'Альбина'")['surname'].iloc[0] == 'Рухадзе'
    assert select_df.query("name == 'Альбина'")['reserved_books'].iloc[0] == 2

    assert select_df.query("name == 'Артём'")['surname'].iloc[0] == None
    assert select_df.query("name == 'Артём'")['reserved_books'].iloc[0] == 2
    
    assert select_df.query("name == 'Александр'")['surname'].iloc[0] == 'Левин'
    assert select_df.query("name == 'Александр'")['reserved_books'].iloc[0] == 1

    assert select_df.query("name == 'Тимур'")['surname'].iloc[0] == 'Муцураев'
    assert select_df.query("name == 'Тимур'")['reserved_books'].iloc[0] == 1
    
