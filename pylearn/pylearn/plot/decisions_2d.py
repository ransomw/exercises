import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

ALPHA_SAMPLES=0.8
ALPHA_DECISION=0.4

_markers = ('s', 'x', 'o', '^', 'v')
_colors = ('red', 'blue', 'lightgreen', 'grey', 'cyan')

def plot_2d_samples(X, classifications):
    for idx, c1 in enumerate(np.unique(classifications)):
        # here, numpy arrays are being indexed by 1D arrays of booleans
        # to preserve those rows where the 1D array is True and flush
        # others rows
        plt.scatter(x=X[classifications == c1, 0],
                        y=X[classifications == c1, 1],
                        alpha=ALPHA_SAMPLES,
                        c=_colors[idx],
                        marker=_markers[idx],
                        label=c1)


def plot_decision_regions(X, classifier, num_classifications,
                                 resolution=0.2):
    """
    * X (numpy.ndarray) --- sample data
          with X.shape == (num_samples, 2), since this module is 2d
    * classifier --- a function to take an array of sample data points
          and return a classification of the samples
    * num_classifications --- the number of possible values returned
          by `classifier`
    """
    xx1, xx2 = np.meshgrid(
        np.arange(X[:, 0].min() - 1, X[:, 0].max() + 1, resolution),
        np.arange(X[:, 1].min() - 1, X[:, 1].max() + 1, resolution))
    # ravel flattens the array by concatenating rows
    Z = classifier(np.array([xx1.ravel(), xx2.ravel()]).T)
    Z = Z.reshape(xx1.shape)
    plt.contourf(xx1, xx2, Z,
                     alpha=ALPHA_DECISION,
                     cmap=ListedColormap(_colors[
                         :num_classifications]))
    plt.xlim(xx1.min(), xx1.max())
    plt.ylim(xx2.min(), xx2.max())


# used to plot weight updates (errors, cost)
def plot_sequence(sequence):
    plt.plot(range(1, len(sequence) + 1), sequence,
                 marker='o')
