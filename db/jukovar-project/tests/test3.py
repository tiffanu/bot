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
    assert select_df.query("genre_name == 'Роман'")['rank'].iloc[0] == 1
    assert select_df.query("genre_name == 'Роман'")['count'].iloc[0] == 4

    assert select_df.query("genre_name == 'Диалог'")['rank'].iloc[0] == 2
    assert select_df.query("genre_name == 'Диалог'")['count'].iloc[0] == 1
    
    assert select_df.query("genre_name == 'Трагедия'")['rank'].iloc[0] == 2
    assert select_df.query("genre_name == 'Трагедия'")['count'].iloc[0] == 1

    assert select_df.query("genre_name == 'Роман в стихах'")['rank'].iloc[0] == 2
    assert select_df.query("genre_name == 'Роман в стихах'")['count'].iloc[0] == 1
