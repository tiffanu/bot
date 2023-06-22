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
    assert select_df.query("genre_id == 1")['genre_name'].iloc[0] == 'Роман'
    assert select_df.query("genre_id == 1")['total_reserved'].iloc[0] == 4

    assert select_df.query("genre_id == 4")['genre_name'].iloc[0] == 'Трагедия'
    assert select_df.query("genre_id == 4")['total_reserved'].iloc[0] == 1
    
    assert select_df.query("genre_id == 2")['genre_name'].iloc[0] == 'Роман в стихах'
    assert select_df.query("genre_id == 2")['total_reserved'].iloc[0] == 1

    assert select_df.query("genre_id == 3")['genre_name'].iloc[0] == 'Диалог'
    assert select_df.query("genre_id == 3")['total_reserved'].iloc[0] == 1
