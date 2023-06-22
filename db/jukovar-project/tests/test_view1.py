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


def test1(select_df):
    assert select_df.query("res_id == 3")['name'].iloc[0] == 'Тимур'
    assert select_df.query("res_id == 3")['begin_date'].iloc[0] == datetime.date(1994, 12, 11)

    assert select_df.query("res_id == 1")['name'].iloc[0] == 'Артём'
    assert select_df.query("res_id == 1")['begin_date'].iloc[0] == datetime.date(2023, 2, 5)

    assert select_df.query("res_id == 2")['name'].iloc[0] == 'Альбина'
    assert select_df.query("res_id == 2")['begin_date'].iloc[0] == datetime.date(2023, 3, 5)

    assert select_df.query("res_id == 5")['name'].iloc[0] == 'Артём'
    assert select_df.query("res_id == 5")['begin_date'].iloc[0] == datetime.date(2023, 7, 23)

    assert select_df.query("res_id == 4")['name'].iloc[0] == 'Александр'
    assert select_df.query("res_id == 4")['begin_date'].iloc[0] == datetime.date(2023, 10, 6)
