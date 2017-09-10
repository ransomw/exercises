"""
this script includes several preprocessing concepts,
demonstrated with a dataset about wine from UC Irvine
https://archive.ics.uci.edu/ml/machine-learning-databases/wine/wine.data

be sure to set the PYTHONPATH environment variable such that
the pylearn module in this repository is available before
running this script.


several parts of this script aren't commisurate with the latest
changes in sklearn, so
* do not be surprised if the feature selection is a bit wonky:
  the SBS implementation relies on the KNN model.
* consider redirecting stderr to /dev/null,
  as there may be several deprecation warnings out of sklearn,
  particularly on the random forest .fit() call.
"""
import os.path

import numpy as np
import pandas as pd
from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.ensemble import RandomForestClassifier
import matplotlib.pyplot as plt

from pylearn.preprocess.sequential_backward_selection import SBS

df = pd.read_csv(os.path.join(os.path.dirname(__file__), 'wine.csv'))
df.columns = [
    'Class label',
    'Alcohol',
    'Malic acid',
    'Ash',
    'Alcalinity of ash',
    'Magnesium',
    'Total phenols',
    'Flavanoids',
    'Nonflavanoid phenols',
    'Proanthocyanins',
    'Color intensity',
    'Hue',
    'OD280/OD315 of diluted wines',
    'Proline',
    ]

print("dataframe sample")
print(df.head())

"""
splitting into training and test samples for supervised
learning is routine by now
"""
# iloc — integer locate for purely array-like indexing
X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values
X_train, X_test, y_train, y_test = train_test_split(
    X, y,
    test_size=0.3,
    random_state=0,
)

print("""
feature scaling
---------------
decision trees are an exception to the rule
> training data needs to be scaled
so much so that preprocessing can be thought of as pipes:
```
add_missing | categorical2numeric | scale_features | ...
```
and just as converting categorical to numeric data has
different approaches (e.g. mapping ordinals to integers
or one-hot encoding of nominals), there are different
approaches to feature-scaling, notably (loosely-defined)
"normalization" and "standardization".
""")

print("""
normalization might amount to calculating
(x - x_min)/(x_max - x_min)
for each sample""")
mms = MinMaxScaler()

print("""
with x_min, x_max calculated from training data like""")
print(X_train[:3, :3])

print("""the normalized training data itself looks like""")

X_train_norm = mms.fit_transform(X_train)

print(X_train_norm[:3, :3])
print("""by the definition of this normalization,
minimum and maximum values throughout the entire
normalized data are""")
print("{min:.2f}, {max:.2f}"
          .format(max=np.max(X_train_norm), min=np.min(X_train_norm)))

print("""----
the test data""")
print(X_test[:3, :3])
print("""looks similar after normalization""")

X_test_norm = mms.transform(X_test)

print(X_test_norm[:3, :3])
print("""but notice the normalized min and max values differ,
because the transform's min and max are from the
training data""")
print("{min:.2f}, {max:.2f}"
          .format(max=np.max(X_test_norm), min=np.min(X_test_norm)))

print("""
rather than moving all the data into the interval [0, 1],
standardization (in a confusing twist of terminology),
could involve normally distributing data about 0""")

stdsc = StandardScaler()
X_train_std = stdsc.fit_transform(X_train)
X_test_std = stdsc.transform(X_test)

print("""such that the training and testing data look like""")
print(X_train_std[:3, :3])
print(X_test_std[:3, :3])
print("""again, recall that the scaling is fitted to the training
data only, so the means of the standardized data differ""")
print("train: {train:.4f}, test: {test:.4f}"
          .format(train=np.mean(X_train_std),
                      test=np.mean(X_test_std)))

print("""
====

the rest of this script will is devoted to handling overfitting
""")

"""
regularization has already been discussed in
scikit_sand/scikit_logistic_regression.py
the main addition detail here is that using the L^1 norm
rather than the [square of the] L^2 norm results in more
weight vectors that, in addition to being closer to the
origin, are more likely to be sparse.
indeed, [boundaries of] L^1 norm balls are cubes, while
[those of] L^2 norm balls are spheres.
"""

print("""
"dimesionality reduction" mostly consists of two techniques:
* feature selection — throw out some features, resulting in
  a lower-dimensional feature space
* feature extraction — construct an entirely new feature space
feature selection is often implemented as a greedy algorithm,
often one that performs the same calculation on each iteration
to determine which feature to remove and terminates based
on the number of features.
""")


def fnp_sbs():
    knn = KNeighborsClassifier(n_neighbors=2)
    sbs = SBS(knn, k_features=1)
    sbs.fit(X_train_std, y_train)

    plt.plot(sbs.nums_subsets, sbs.scores, marker='o')
    plt.ylabel('Accuracy')
    plt.xlabel('Number of features removed')
    plt.grid()
    plt.show()
    return sbs


print("""here's a plot of the accuracy of the k-nearest-neighbors
model over the course of a feature selection algorithm
""")
sbs = fnp_sbs()
print("""
from the chart, observe that the highest accuracy
with the fewest features occurs when 8 features are
removed (such that 5 features remain). namely,""")
selected_idxs = sbs.subset_idxs[8]
print(df.columns[1:][list(selected_idxs)])

print("""now compare the accuracy of of a fit on the entire
dataset to the accuracy of a fit on just these features""")

knn = KNeighborsClassifier(n_neighbors=2)

print("entire dataset:")

knn.fit(X_train_std, y_train)

print("training: {train:.4f}, test: {test:.4f}"
          .format(train=knn.score(X_train_std, y_train),
                      test=knn.score(X_test_std, y_test)))

print("selected features")

knn.fit(X_train_std[:, selected_idxs], y_train)

print("training: {train:.4f}, test: {test:.4f}"
          .format(train=knn.score(
              X_train_std[:, selected_idxs], y_train),
                      test=knn.score(
                          X_test_std[:, selected_idxs], y_test)))

print("""
as a final note on feature selection, note that random
forests have an implicit notion of feature importance
"built in".
""")
# todo: mathmatical details on how the random forest
#  feature_importances_ is implemented
feat_labels = df.columns[1:]
forest = RandomForestClassifier(
    n_estimators=1000,
    random_state=0,
    n_jobs=-1,
)
# this throws off quite a lot of warnings
forest.fit(X_train, y_train)
importances = forest.feature_importances_
ordered_idxs = np.argsort(importances)[::-1]
for idx in range(X_train.shape[1]):
    print("{feat_label} %-*s {feat_importance:.4f}"
              .format(
                  feat_label=feat_labels[idx],
                  feat_importance=importances[ordered_idxs[idx]],
                  ))
