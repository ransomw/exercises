import os

import numpy as np
import pandas as pd

from pylearn.perceptron import Perceptron
from pylearn.adaline import AdalineGD
from pylearn.adaline import AdalineSGD
from pylearn.dat import IrisSpecies
import matplotlib.pyplot as plt

from . import decisions_2d as d_2d

# variables re. data file
_first_versicolor_idx = 50
_first_viginica_idx = 100
_petal_length_col_idx = 0
_sepal_length_col_idx = 2

def _load_pandas_data():
    iris_data = pd.read_csv(
        os.path.join(os.path.dirname(__file__), '..', '..',
                         'data', 'iris.csv'),
        # default since `names` kwarg is unused
        header=None)
    return (np.where((
                iris_data.iloc[:_first_viginica_idx, 4].values ==
                IrisSpecies.setosa.value
                ), -1, 1),
            iris_data.iloc[
                :_first_viginica_idx,
                [_petal_length_col_idx, _sepal_length_col_idx]
                ].values,
            )


def plot_setosa_versicolor_raw(show=True):
    plt.clf() # clear current figure
    versicolor_targets, setosa_versicolor_samples = _load_pandas_data()
    d_2d.plot_2d_samples(setosa_versicolor_samples,
                             versicolor_targets)
    plt.xlabel("petal length")
    plt.ylabel("sepal length")
    plt.legend(loc='upper left')
    if show:
        plt.show()


def _standardize(array_1d):
    """ normally distribute array entries """
    return (array_1d - array_1d.mean()) / array_1d.std()


def fit_setosa_versicolor(model, learning_rate=0.1, num_iter=10,
                              standardize=False):
    ### todo: shared ABC for these model classes
    if model not in [Perceptron, AdalineGD, AdalineSGD]:
        raise ValueError("unknown fit model", model)
    versicolor_targets, setosa_versicolor_samples = _load_pandas_data()
    perceptron = model(
        learning_rate=learning_rate,
        num_iter=num_iter,
        )
    if not standardize:
        return (
            setosa_versicolor_samples,
            versicolor_targets,
            perceptron.fit(
                setosa_versicolor_samples,
                versicolor_targets),
            )
    samples_shape = setosa_versicolor_samples.shape
    setosa_versicolor_samples_std = np.zeros(samples_shape)
    for idx in range(samples_shape[1]):
        setosa_versicolor_samples_std[:, idx] = _standardize(
            setosa_versicolor_samples[:, idx])
    return (
        setosa_versicolor_samples_std,
        versicolor_targets,
        perceptron.fit(
            setosa_versicolor_samples_std,
            versicolor_targets),
        )


def plot_fit_setosa_versicolor(model, show=True,
                                   **kwargs):
    plt.clf() # clear current figure
    (
        setosa_versicolor_samples,
        versicolor_targets,
        model_inst,
    ) = fit_setosa_versicolor(model, **kwargs)
    d_2d.plot_decision_regions(setosa_versicolor_samples,
                                   model_inst.predict,
                                   len(np.unique(versicolor_targets)),
                                   )
    d_2d.plot_2d_samples(setosa_versicolor_samples,
                             versicolor_targets)
    plt.legend(loc='upper left')
    if show:
        plt.show()


def plot_weight_updates_setosa_versicolor(model, show=True,
                                              **kwargs):
    plt.clf() # clear current figure
    (
        setosa_versicolor_samples,
        versicolor_targets,
        model_inst,
    ) = fit_setosa_versicolor(model, **kwargs)
    if type(model_inst) is Perceptron:
        d_2d.plot_sequence(model_inst.errors)
        plt.ylabel("number of misclassifications")
    elif type(model_inst) in [AdalineGD, AdalineSGD]:
        d_2d.plot_sequence(np.log10(model_inst.cost))
        plt.ylabel("log(sum-squared-error)")
    else:
        raise ValueError("unknown model type", type(model_inst))
    plt.xlabel("epochs")
    plt.legend(loc='upper left')
    if show:
        plt.show()
