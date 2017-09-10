"""
logistic regression can be conceptualized in terms of probabilities.
in particular, it's useful to have a monotonic bijection (0, 1) <-> R
for this, we use
logit: (0, 1) -> R -~- p |-> log(p/(1-p))
the inverse of the sigmoid function
\psi: R -> (0, 1) -~- z |-> 1/(1+e^{-z})

so that any real number --- in particular, any "net input",
i.e. dot product of an input with a weight vector
(see pylearn.percptron and pylearn.adaline) ---
can be converted to a number between 0 and 1.
if the threshold on this "activation function" is set at 0.5,
then the threshold on the net input is at zero since
1/(1+exp(-0)) = 1/2

to learn weights of the net input, consider maximizing
the product of conditional probabilites, P(target; weights, sample),
over all samples --- or, equivalently, for ease of calculation,
maximizing the natural logarithm of that product, the
sum_{i=1}^n log[P(y^{(i)}; weights, X^{(i)})]

... probalistic interpretations aside, this is the same idea as
Adaline, where some surface parameterized by the weights is
defined by the training data, and the weights are chosen at a
maximal/minimal point on that surface.

indeed, substituting -1 * the above sum into the adaline impl
would be an ok implementation for a two-target implementation.
some calculation is required to show that the gradient descent
here is linear.  it boils down to the chain rule, and identities of
the derivative of ln and the sigmoid function.

*** idea: include both the the RMS grad and the grad of of this
    function in LaTeX within the "div, grad, curl and all that"
    framework

notions of probability don't strictly arise in the classification.
however, a fitted model can be interpreted as being able to estimate
probability.  (although, can't this be said of any model based on
mapping samples to an any open interval and thresholding at a point?)

----

for any model, there is a dichtomy between "underfitting",
where the model doesn't nearly account for all the complexities
of the data, and "overfitting", where the model conforms as much
to randomness within the data set (e.g. test/train split)
as to the features of the data itself.

one idea to prevent overfitting is to have the weights
contribute to the "cost function", the surface travelled by
gradient descent, independently of the training data.
specficically, the (scaled) $L^2$ norm of the weight vector
(as a constant function on the sample space) can be
added at every point of the surface, such that
J_0 = J' + \lambda |w|_2
is the cost function to minimize, where J' is the original
cost function.  or for convenience, to examine
J = C*J' + |w|_2
since it'll have the same minimum as J_0.

for logistic regression,
|w|_2 = w^2/2
since the sigmoid function maps inputs to the unit interval.
"""
import argparse

import numpy as np
from matplotlib.colors import ListedColormap
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression

def sigmoid(z):
    return 1.0/(1.0 + np.exp(-z))

def plot_sigmoid(min=-7, max=7, res=0.1):
    """
    plot own definition the sigmoid function used
    "under the hood" by the logistic regression model
    """
    assert min < max
    z = np.arange(min, max, res)
    phi_z = sigmoid(z)
    plt.plot(z, phi_z)
    # vertical line at origin
    plt.axvline(x=0.0, color='k')
    # dotten lines at asymptotes (args* are scaled to data min, max)
    plt.axhspan(0.0, 1.0, facecolor='1.0', alpha=1.0, ls='dotted')
    # dotted line at inflection point
    plt.axhline(y=0.5, ls='dotted', color='k')
    plt.yticks([0, 0.5, 1])
    plt.ylim(-0.1, 1.1)
    plt.xlabel(z)
    plt.ylabel('$\phi (z)$')
    plt.show()
    plt.clf()

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

def fit_model(inverse_regularization_param=1000.0):
    """
    fit the logistic regression model to the iris
    dataset and plot the results.
    """
    lr = LogisticRegression(
        C=inverse_regularization_param,
        random_state=0)
    lr.fit(X_train_std, y_train)

    print(np.round(lr.predict_proba(X_test_std[0,:]), decimals=3))
    # => [[ 0.     0.063  0.937]]
    """
    means that the first sample test value (shape = (2,))
    "has the following probabilities" of belonging to each of the
    classes (tho i'm still a little uncertain about the "probablistic"
    interpretation of this model)
    """

    X_combined_std = np.vstack((X_train_std, X_test_std))
    y_combined = np.hstack((y_train, y_test))
    plot_decision_regions(
        X_combined_std, y_combined,
        classifier=lr.predict,
        # duplicates .3 test/train split above
        test_idx=range(105, 150))
    plt.xlabel("petal length [standardized]")
    plt.ylabel("petal width [standardized]")
    plt.legend(loc='upper left')
    plt.show()


def weights_by_param():
    """
    explore regularization with this plot
    """
    weights = []
    params = []
    for scale in np.arange(-4, 5):
        param = 10.0**scale
        lr = LogisticRegression(
            C=param,
            random_state=0)
        lr.fit(X_train_std, y_train)
        # these are all (well both, in this case) the weight coefficients
        # (those for petal length and width) for the 2nd feature
        # (i.e. flower type)
        weights.append(lr.coef_[1])
        params.append(param)
    weights = np.array(weights)
    plt.plot(params, weights[:, 0], label="petal length")
    plt.plot(params, weights[:, 1], label="petal width",
                 linestyle='--')
    plt.xlabel("inverse regularization param")
    plt.ylabel("fitted weight coeff.")
    plt.legend(loc='upper left')
    plt.xscale('log')
    plt.show()


########### cli
CLI_FUNCTIONS= {fn.__name__: fn for fn in [
    plot_sigmoid,
    fit_model,
    weights_by_param,
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
