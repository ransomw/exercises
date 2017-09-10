import os.path
from enum import Enum
from functools import partial


def read_csv(csv_spec, path_csv_file,
                 vectorization=None):
    column_labels = [col_def['label'] for col_def in csv_spec]
    assert len(column_labels) == len(set(column_labels))
    with open(path_csv_file, 'r') as f:
        parsed_rows = [
            dict([ (col_def['label'], col_def['parse'](raw_val))
                    for (col_def, raw_val) in
                       zip(csv_spec, line.strip().split(',')) ])
            for line in f.readlines() ]
    if vectorization is None:
        return parsed_rows
    elif type(vectorization) is list:
        return [[parsed_row[label] for label in vectorization]
                    for parsed_row in parsed_rows]
    elif type(vectorization) is str:
        return [parsed_row[vectorization]
                    for parsed_row in parsed_rows]
    else:
        raise ValueError((
            "unsupported vectorization type"),
            type(vectorization))


class IrisSpecies(Enum):
    setosa = 'S'
    versicolor = 'V'
    virginica = 'R'

get_iris_data = partial(
    read_csv, [
        {
            'label': 'sepal_length',
            'parse': float,
        }, {
            'label': 'sepal_width',
            'parse': float,
        }, {
            'label': 'petal_length',
            'parse': float,
        }, {
            'label': 'petal_width',
            'parse': float,
        }, {
            'label': 'species',
            'parse': IrisSpecies,
        }
    ],
    os.path.join(os.path.dirname(__file__), '..',
                     'data', 'iris.csv'),
    vectorization=[
        'sepal_length',
        'sepal_width',
        'petal_length',
        'petal_width',
    ]
)

