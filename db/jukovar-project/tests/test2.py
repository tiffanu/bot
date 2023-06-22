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
    assert select_df.query("name == 'Тимур'")['surname'].iloc[0] == 'Муцураев'
    assert select_df.query("name == 'Тимур'")['begin_date'].iloc[0] == datetime.date(1994, 12, 11)
    assert select_df.query("name == 'Тимур'")['end_date'].iloc[0] == datetime.date(1996, 8, 31)

    assert select_df.query("name == 'Артём'")['surname'].iloc[0] == None
    assert select_df.query("name == 'Артём'")['begin_date'].iloc[0] == datetime.date(2023, 2, 5)
    assert select_df.query("name == 'Артём'")['end_date'].iloc[0] == datetime.date(2023, 2, 6)
    
    assert select_df.query("name == 'Альбина'")['surname'].iloc[0] == 'Рухадзе'
    assert select_df.query("name == 'Альбина'")['begin_date'].iloc[0] == datetime.date(2023, 3, 5)
    assert select_df.query("name == 'Альбина'")['end_date'].iloc[0] == datetime.date(2023, 3, 6)

    assert select_df.query("name == 'Артём'")['surname'].iloc[0] == None
    assert select_df.query("name == 'Артём'")['begin_date'].iloc[0] == datetime.date(2023, 2, 5)
    assert select_df.query("name == 'Артём'")['end_date'].iloc[0] == datetime.date(2023, 2, 6)
    
    assert select_df.query("name == 'Александр'")['surname'].iloc[0] == 'Левин'
    assert select_df.query("name == 'Александр'")['begin_date'].iloc[0] == datetime.date(2023, 10, 6)
    assert select_df.query("name == 'Александр'")['end_date'].iloc[0] == datetime.date(2023, 10, 8)
    
