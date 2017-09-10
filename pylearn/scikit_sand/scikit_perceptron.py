"""
very likely buggy implementation of the perceptron in pylearn using
scikit ... at least demonstrates scikit api using familiar concepts
"""
import numpy as np
from sklearn import datasets
from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import Perceptron
from sklearn.metrics import accuracy_score
from matplotlib.colors import ListedColormap
import matplotlib.pyplot as plt

### grab the data direct out of scipy
iris = datasets.load_iris()
# these are numpy.ndarray s
samples = iris.data[:, [2, 3]]
targets = iris.target
# np.unique(targets) => ndarray([0, 1, 2])

### divide the data into training data and sample data
(samples_train, samples_test,
     targets_train, targets_test
     ) = train_test_split(samples, targets,
                              # 30% test data, 70% training data
                              test_size=0.3,
                              random_state=0)

### feature scaling
## similar to `standardize` kwarg to `plot.iris.fit_setosa_versicolor`
# from scikit learn api docs
# http://scikit-learn.org/stable/modules/classes.html
# "Standardize features by removing the mean and scaling
#  to unit variance"
standard_scalar = StandardScaler()
# fits mean and standard deviation
standard_scalar.fit(samples_train)
# scales data
samples_train_std, samples_test_std = [
    standard_scalar.transform(x) for x
    in (samples_train, samples_test)]

### fit the data
## uses "One vs Rest" (OvR) method for >2 targets
# idea: own implementation of OvR
#       ... or at least document how the OvR method works
perceptron = Perceptron(n_iter=40, eta0=0.1, random_state=0)
perceptron.fit(samples_train_std, targets_train)

### apply the model
predictions_test = perceptron.predict(samples_test_std)
print("Missclassified test samples %d/%d" % (
    (targets_test != predictions_test).sum(),
    targets_test.shape[0]
    ))
print("accuracy %.2f" %
          accuracy_score(targets_test, predictions_test))

predictions_train = perceptron.predict(samples_train_std)
print("Missclassified train samples %d/%d" % (
    (targets_train != predictions_train).sum(),
    targets_train.shape[0]
    ))
print("accuracy %.2f" %
          accuracy_score(targets_train, predictions_train))

### aaaaaaaaaaand plot
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



#### todo: merge with existing
# def ___plot_decision_regions(X, y, classifier,
#                               test_idx=None, resolution=0.02):
#     plot_decision_regions_base(X, y, len(np.unique(y)),
#                                    resolution=resolution)
#     if test_idx:
#         X_test, y_test = X[test_idx, :], y[test_idx]
#         plt.scatter(X_test[:, 0], X_test[:, 1],
#                         c='', alpha=1.0, linewidth=1,
#                         marker='o',
#                         s=55,
#                         label="test set")

samples_combined_std = np.vstack((samples_train_std, samples_test_std))
targets_combined = np.hstack((targets_train, targets_test))
plot_decision_regions(
    samples_combined_std,
    targets_combined,
    classifier=perceptron.predict,
    # duplicates .3 test/train split above
    test_idx=range(105, 150))
plt.xlabel("petal length [standardized]")
plt.ylabel("sepal length [standardized]")
plt.legend(loc='upper left')
plt.show()


# from pdb import set_trace; set_trace()
