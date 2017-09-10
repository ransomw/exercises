from itertools import combinations

import numpy as np
from sklearn.base import ClassifierMixin
from sklearn.base import clone
from sklearn.cross_validation import train_test_split
from sklearn.metrics import accuracy_score

class SBS:
    """
    sequential backward selection (SBS) in general
    selects a feature index, i, based on which index maximizes
    &\{ J(X_i - x) | x\in X_i\}_i&
    where $J$ is an arbitrary function into the reals.
    here, $J$ is based on on the performance of a classifier
    (i.e. a model):  at each iteration of this greedy algorithm
    for removing reatures, the feature to be removed is selected
    by fitting the model to every possible subset of the remaining
    features (sans one), then calculating the score of each fit's
    prediction according to some function _on the outputs_.
    """

    def __init__(self, estimator, k_features,
                     scoring=accuracy_score,
                     test_size=0.25,
                     random_state=1):
        self.scoring = scoring
        self.estimator = (clone(estimator)
                              if isinstance(estimator, ClassifierMixin)
                              else estimator)
        self.k_features = k_features
        self.test_size = test_size
        self.random_state = random_state

    # todo: cleanup (e.g. remove superfluous dim, take care about
    #   which variables to make self. and when
    def fit(self, X, y):
        """
        even though this function is splitting the test and training
        data, since this is conceptually preprocessing rather than
        modelling, this fit function ought be called with *training
        data only* to claify data dependencies when testing the
        overall goodness of the learning pipeline.
        """
        X_train, X_test, y_train, y_test = train_test_split(
            X, y,
            test_size=self.test_size,
            random_state=self.random_state,
        )
        dim = X_train.shape[1]
        self._indices = tuple(range(dim))
        self._subsets = [self._indices]
        score = self._calc_score(X_train, X_test,
                                     y_train, y_test,
                                     self._indices)
        self._scores = [score]
        while dim > self.k_features:
            scores = []
            subsets = []
            # choose all subsets that exclude one feature
            for p in combinations(self._indices, r=(dim - 1)):
                score = self._calc_score(X_train, X_test,
                                             y_train, y_test,
                                             p)
                scores.append(score)
                subsets.append(p)
            idx_best_score = np.argmax(scores)
            self._indices = subsets[idx_best_score]
            self._subsets.append(self._indices)
            dim -= 1
            self._scores.append(scores[idx_best_score])
        self._k_score = self._scores[-1]
        return self

    def transform(self, X):
        return X[:, self._indices]

    @property
    def nums_subsets(self):
        return [len(subset) for subset in self._subsets]

    @property
    def subset_idxs(self):
        return self._subsets

    @property
    def scores(self):
        return self._scores

    def _calc_score(self, X_train, X_test, y_train, y_test, indices):
        self.estimator.fit(X_train[:, indices], y_train)
        y_pred = self.estimator.predict(X_test[:, indices])
        score = self.scoring(y_test, y_pred)
        return score
