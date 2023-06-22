import os
import pytest
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
    assert select_df.query("total_amount == 10")['wardrobe'].iloc[0] == 2
    assert select_df.query("total_amount == 34")['wardrobe'].iloc[0] == 1
