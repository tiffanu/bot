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


def test3(select_df):
    assert select_df.query("res_id == 4")['name'].iloc[0] == 'Александр'
    assert select_df.query("res_id == 4")['surname'].iloc[0] == 'Левин'
    assert select_df.query("res_id == 4")['phone'].iloc[0] == None

    assert select_df.query("res_id == 2")['name'].iloc[0] == 'Альбина'
    assert select_df.query("res_id == 2")['surname'].iloc[0] == 'Рухадзе'
    assert select_df.query("res_id == 2")['phone'].iloc[0] == None

    assert select_df.query("res_id == 1")['name'].iloc[0] == 'Артём'
    assert select_df.query("res_id == 1")['surname'].iloc[0] == None
    assert select_df.query("res_id == 1")['phone'].iloc[0] == '+7-965-***-**-**'

    assert select_df.query("res_id == 3")['name'].iloc[0] == 'Тимур'
    assert select_df.query("res_id == 3")['surname'].iloc[0] == 'Муцураев'
    assert select_df.query("res_id == 3")['phone'].iloc[0] == None
