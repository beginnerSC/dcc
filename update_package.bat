poetry run pip uninstall -y dcc
poetry run pip install ./dist/dcc-0.1.0-cp312-cp312-win_amd64.whl
poetry run python -c "from dcc import Point; p = Point(0, 0); print(p.GetCoordinates())"