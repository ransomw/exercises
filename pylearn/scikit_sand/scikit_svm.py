"""
support vector machines are about creating (n-1)-dimensional subspaces
of n-dim. vector spaces (aka "hyperplanes") to classify data.
specifically, these subspaces are selected to partition the
remaining space based on sample data points, s.t. (key point)
the distance from sample points to the subspace (aka "the margin")
is maximized.  it is originally due to Vapnik.

since it might not be possible to partition the space in this way
such that each classfier for the sample data lands in a separate
set of the partition (i.e. the sample data might not be "linearly
separable"), the equation to maximize is adjusted using a scalar
(one per sample) called a "slack variable" as part of the model,
multiplied by a constant, C, as a model parameter.

todo: provide more details on slack variable.

in general, it's always possible to add an additional, computed
feature to a data set (e.g. distance from origin).  although this'll
increase dimensionality, it could also provide a better fit
if the calculated feature is meaningful.
SVMs are popular because it's possible to "add the additional feature"
in a way that's not so computationally expensive via "kernels".

todo: provide more details on kernels.
"""
import argparse

import numpy as np
from sklearn import datasets
from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from matplotlib.colors import ListedColormap
import matplotlib.pyplot as plt


# duplicates scikit_perceptron.py
def plot_decision_regions(X, y, classifier,
                              test_idx=None, resolution=0.02):
    markers = ('s', 'x', 'o', '^', 'v')
    colors = ('red', 'blue', 'green', 'lightgrey', 'cyan')
    cmap = ListedColormap(colors[:len(np.unique(y))])

    # regions
    x1_min, x1_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    x2_min, x2_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx1, xx2 = np.meshgrid(np.arange(x1_min, x1_max, resolution),
                               np.arange(x2_min, x2_max, resolution))
    Z = classifier(np.array([xx1.ravel(), xx2.ravel()]).T)
    Z = Z.reshape(xx1.shape)
    plt.contourf(xx1, xx2, Z, alpha=0.4, cmap=cmap)
    plt.xlim(xx1.min(), xx1.max())
    plt.ylim(xx2.min(), xx2.max())

    # samples
    X_test, y_test = X[test_idx, :], y[test_idx]
    for idx, cl in enumerate(np.unique(y)):
        plt.scatter(x=X[y == cl, 0], y=X[y == cl, 1],
                        alpha=0.8, c=cmap(idx),
                        marker=markers[idx], label=cl)

    if test_idx:
        X_test, y_test = X[test_idx, :], y[test_idx]
        plt.scatter(X_test[:, 0], X_test[:, 1],
                        c='', alpha=1.0,
                        linewidths=1,
                        edgecolor='black',
                        marker='o',
                        # shape
                        s=55,
                        label="test set")


### as in scikit_perceptron.py
iris = datasets.load_iris()

X = iris.data[:, [2, 3]]
y = iris.target
(X_train, X_test,
     y_train, y_test
) = train_test_split(X, y,
                         # 30% test data, 70% training data
                         test_size=0.3,
                         random_state=0)
sc = StandardScaler()
sc.fit(X_train)
X_train_std, X_test_std = [
    sc.transform(x) for x
    in (X_train, X_test)]
X_combined_std = np.vstack((X_train_std, X_test_std))
y_combined = np.hstack((y_train, y_test))

def fit_and_plot_svc():
    """
    same song and dance as perceptron, logistic regression.
    """
    svm = SVC(kernel='linear', C=1.0, random_state=0)
    svm.fit(X_train_std, y_train)
    plot_decision_regions(X_combined_std, y_combined,
                              classifier=svm.predict,
                              # duplicates .3 test/train split above
                              test_idx=range(105, 150))
    plt.xlabel("petal length [standardized]")
    plt.ylabel("petal width [standardized]")
    plt.legend(loc='upper left')
    plt.show()

def kernel_demo():
    """
    here's a different data set, used to demo the
    Radial Basis Function kernel
    """
    np.random.seed(0)
    # array random (normally distributed) entries of specified shape
    X_xor = np.random.randn(200, 2)
    # label according to cartesian quadrant
    y_xor = np.logical_xor(X_xor[:, 0] > 0, X_xor[:, 1] > 0)
    y_xor = np.where(y_xor, 1, -1)

    svm = SVC(kernel='rbf', C=10.0, random_state=0, gamma=0.10)
    svm.fit(X_xor, y_xor)
    plot_decision_regions(X_xor, y_xor, classifier=svm.predict,
                              resolution=0.01)

    plt.legend()
    plt.show()


def fit_and_plot_kernel(gamma):
    """
    same song and dance as perceptron, logistic regression.
    """
    svm = SVC(kernel='rbf', C=1.0, random_state=0, gamma=gamma)
    svm.fit(X_train_std, y_train)
    plot_decision_regions(X_combined_std, y_combined,
                              classifier=svm.predict,
                              # duplicates .3 test/train split above
                              test_idx=range(105, 150))
    plt.xlabel("petal length [standardized]")
    plt.ylabel("petal width [standardized]")
    plt.legend(loc='upper left')
    plt.show()


### cli
# as in scikit_logistic_regression.py

CLI_FUNCTIONS= {fn.__name__: fn for fn in [
    fit_and_plot_svc,
    kernel_demo,
    fit_and_plot_kernel,
]}

class MyHelpFormatter(argparse.ArgumentDefaultsHelpFormatter):

    def __init__(self, *args, **kwargs):
        width = kwargs.pop('width', 60)
        super().__init__(*args, width=width, **kwargs)


def parseArgs():
    """ parse script arguments """
    argParser = argparse.ArgumentParser(
        formatter_class=MyHelpFormatter,
        )
    subParsers = argParser.add_subparsers(dest='cmd')
    for cmd, fn in CLI_FUNCTIONS.items():
        parser = subParsers.add_parser(
            cmd,
            formatter_class=MyHelpFormatter,
            help=fn.__doc__,
        )
        if fn.__name__ == 'fit_and_plot_kernel':
            parser.add_argument(
            '-g', '--gamma', dest='gamma',
            help=(("cut-off parameter")),
            default=0.2,
            type=float)
    return argParser.parse_args()

if __name__ == '__main__':
    args = parseArgs()
    fn = CLI_FUNCTIONS[args.cmd]
    if fn.__name__ == 'fit_and_plot_kernel':
        fn(args.gamma)
    else:
        fn()
