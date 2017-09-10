"""
decision trees (रुखहरु) are typically binary, so the function to maximize
at each node looks like
G(D_p) = I(D_p) - N_l/N_p I(D_l) - N_r/N_p I(D_r)
* p -- parent
* l -- left
* r -- right
where G is the "information gain" based on the underlying
"impurity measure", I.
(??? is I a measure in the sigma-algebra -> [0, ∞] sense?)
I is typically expressed in terms of p, the proportion of samples
of a particular class (y) at each node --- conceptually, the probability
of a data point belonging to a particular class conditional on it
being at the given node.

a fitted model makes a decision about each datapoint by moving from
root to leaf, with each leaf representing a [not necessarily distinct]
classification (e.g. flower species). note that the decision may not
result in two buckets, *both* 'better' (according to impurity measure)
sorted according to training data classification, since a very well
sorted bucket with lots of samples can offset a less well sorted
bucket with fewer samples.

a (conceptually as opposed to computationally) easy generlization of
decision trees is random forests.  in the random 森 approach,
a lot of decision trees are fitted, each to a random subset of the
sample data, and then classification is based on "majority vote"
of all these trees --- i.e. a class label is assigned to a sample
based on evaluating all the trees and seeing what the majority of
the trees classify the sample as.
this sort of generalization applies to other models as well and is
called "ensemble learning".
"""
import argparse
import os.path
import subprocess
from functools import partial

run = partial(
    subprocess.run,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    # shell=True,
    check=True,
    )

import numpy as np
from sklearn.tree import DecisionTreeClassifier
from sklearn.tree import export_graphviz
from sklearn.ensemble import RandomForestClassifier
from sklearn import datasets
from sklearn.cross_validation import train_test_split
from matplotlib.colors import ListedColormap
import matplotlib.pyplot as plt

def I_gini(p):
    """ gini impurity measure """
    return p * (1 - p) + (1 - p) * (1 - (1 - p))


def I_entropy(p):
    """ [shannon information] entropy impurity measure """
    if p == 0:
        return None
    return - p * np.log2(p) - (1 - p)*np.log2(1 - p)


def I_error(p):
    """ error impurity measure """
    return 1 - np.max([p, 1 - p])


def plot_I():
    """
    plot a comparison of a few standard impurity measures
    """
    x = np.arange(0, 1, 0.01)
    gini = I_gini(x)
    ent = [I_entropy(p) for p in x]
    # scaled
    sc_ent = [e * 0.5 if e else None for e in ent]
    err = [I_error(p) for p in x]
    fig = plt.figure()
    ax = plt.subplot(1, 1, 1)
    for I, label, ls, c in zip(
            [ent, sc_ent, gini, err],
            ['Entropy', 'Entropy (scaled)',
                 'gini index', 'Misclassification error'],
            ['-', '-', '--', '-.'],
            ['blue', 'red', 'green', 'cyan'],
            ):
        line = ax.plot(x, I, label=label,
                           linestyle=ls, lw=2, color=c)
    ax.legend(loc='upper center', bbox_to_anchor=(0.5, 1.15),
                  ncol=3, fancybox=True, shadow=False)
    ax.axhline(y=0.5, linewidth=1, color='k', linestyle='--')
    ax.axhline(y=1.0, linewidth=1, color='k', linestyle='--')
    plt.ylim([0, 1.1])
    plt.xlabel("p")
    plt.ylabel("Impurity index")
    plt.show()


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


### similar to scikit_perceptron.py
# ~~~note: there's no standardization for decision trees
iris = datasets.load_iris()

X = iris.data[:, [2, 3]]
y = iris.target
(X_train, X_test,
     y_train, y_test
) = train_test_split(X, y,
                         # 30% test data, 70% training data
                         test_size=0.3,
                         random_state=0)
X_combined = np.vstack((X_train, X_test))
y_combined = np.hstack((y_train, y_test))

def fit_and_plot_tree():
    tree = DecisionTreeClassifier(
        criterion='entropy',
        # too much depth can result in overfitting
        max_depth=3,
        random_state=0,
        )
    tree.fit(X_train, y_train)
    ## show tree
    _graphviz_filepath = os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        'tree.dot')
    _treeimg_filepath = os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        'tree.png')
    export_graphviz(
        tree, out_file=_graphviz_filepath,
        feature_names=["petal length", "petal width"])
    # requires `graphviz` apt-get package
    run(['dot', '-Tpng', _graphviz_filepath, '-o', _treeimg_filepath])
    run(['xdg-open', _treeimg_filepath])
    ## plot decison
    plot_decision_regions(X_combined, y_combined,
                              classifier=tree.predict,
                              # duplicates .3 test/train split above
                              test_idx=range(105, 150))
    plt.xlabel("petal length")
    plt.ylabel("petal width")
    plt.legend(loc='upper left')
    plt.show()


def fit_and_plot_forest():
    forest = RandomForestClassifier(
        criterion='entropy',
        n_estimators=10,
        random_state=1,
        n_jobs=2,
        )
    forest.fit(X_train, y_train)
    plot_decision_regions(X_combined, y_combined,
                              classifier=forest.predict,
                              # duplicates .3 test/train split above
                              test_idx=range(105, 150))
    plt.xlabel("petal length [standardized]")
    plt.ylabel("petal width [standardized]")
    plt.legend(loc='upper left')
    plt.show()


########### cli
# as in scikit_logistic_regression.py
CLI_FUNCTIONS= {fn.__name__: fn for fn in [
    plot_I,
    fit_and_plot_tree,
    fit_and_plot_forest,
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
        subParsers.add_parser(
            cmd,
            formatter_class=MyHelpFormatter,
            help=fn.__doc__,
        )
    return argParser.parse_args()

if __name__ == '__main__':
    args = parseArgs()
    CLI_FUNCTIONS[args.cmd]()
