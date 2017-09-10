"""
naming convention: *_s ---
e.g. `sample_s` read as sample(s)
"""

import numpy as np
from numpy.random import seed

###########
# *** idea: plot surfaces and paths followed by each model
###########

class AdalineGD:
    """
    GD is for "gradient descent".

    this model takes steps along the gradient
    of the error function's surface,
    parameterized by the root-mean-squared (RMS)
    error function's weights when the error is calculated
    over all samples at once.
    """

    def __init__(self, learning_rate=0.01, num_iter=10):
        self.learning_rate = learning_rate
        self.num_iter = num_iter

    def fit(self, samples, targets):
        """
        contrast with the `Perceptron.fit`:  there is no inner loop,
        because each pass of the outer loop takes a step along the
        gradient of the surface defined by the given sample.
        points on the surface correspond to choices for weights.
        """
        self._weights = np.zeros(1 + samples.shape[1])
        # rather "correct" or "incorrect" feedback as with perceptron,
        # adaline feeds a real-valued error-function back into the
        # the weights
        self._cost = []
        for _ in range(self.num_iter):
            # YYY
            # text's code uses `net_input` rather than `activation`
            # but the text itself depicts activation feeding errors,
            # not net input
            output = self.activation(samples)
            # linear b/c of the usual derivative (gradient) of RMS dance
            errors = targets - output
            self._weights[1:] += (
                self.learning_rate * samples.T.dot(errors)
            )
            # ??? variations on this and perceptron that update
            # -> w_0 differently from w_1, ..., w_n?
            # -> each w_j differently?
            self._weights[0] += (
                self.learning_rate * errors.sum()
            )
            self._cost.append((errors**2).sum() / 2.0)
        return self

    def _net_input(self, samples):
        return np.dot(samples, self._weights[1:]) + self._weights[0]

    def activation(self, samples):
        """
        override with monotonically increasing function
        for variations on this model
        """
        return self._net_input(samples)

    def predict(self, sample_s):
        # using `np.where` as contrasted with `if ... else`
        # allows predicting several samples at once
        # (as when plotting results)
        return np.where(
            self.activation(sample_s) >= 0.0, 1, -1)

    @property
    def cost(self):
        return self._cost


class AdalineSGD:
    """
    SGD is for "stochastic (i.e. random) gradient descent".

    each iteration updates a weights vector
    based on the gradients of several different
    surfaces, one for each of the samples.
    """

    def __init__(self, learning_rate=0.01, num_iter=10,
                     shuffle=True, random_state=1):
        self.learning_rate = learning_rate
        self.num_iter = num_iter
        self._is_weights_init = False
        self.shuffle = shuffle
        if random_state is not None:
            seed(random_state)

    def fit(self, samples, targets):
        self._init_weights(samples.shape[1])
        self._cost = []
        for _ in range(self.num_iter):
            if self.shuffle:
                samples, targets = self._shuffle_data_points(
                    samples, targets)
            cost = []
            for sample, target in zip(samples, targets):
                cost.append(self._update_weights(sample, target))
            self._cost.append(sum(cost) / len(cost))
        return self

    def partial_fit(self, samples, targets):
        """
        this function exposes one of the most significant use cases
        for this model:  for use cases where all data is not available
        ahead of time, the model can be updated continuously as
        new arrives.
        """
        if not self._is_weights_init:
            self._init_weights(samples.shape[1])
        # YYY how's it run without this branch,
        #     just using the first case all the time?
        if targets.ravel().shape[0] > 1:
            # there's more than one feature
            for sample, target in zip(samples, targets):
                self._update_weights(sample, target)
        else:
            self._update_weights(samples, targets)
        return self

    def _init_weights(self, num_features):
        self._weights = np.zeros(1 + num_features)
        self._is_weights_init = True

    def _shuffle_data_points(self, samples, targets):
        perm = np.random.permutation(len(targets))
        return samples[perm], targets[perm]

    def _update_weights(self, sample, target):
        output = self.activation(sample)
        # this'll be a scalar value when called by fit()
        error = target - output
        self._weights[1:] += self.learning_rate * sample.dot(error)
        self._weights[0] += self.learning_rate * error
        return (error**2 / 2.0) # cost

    def _net_input(self, sample_s):
        return np.dot(sample_s, self._weights[1:]) + self._weights[0]

    def activation(self, sample_s):
        """
        override with monotonically increasing function
        for variations on this model.
        """
        return self._net_input(sample_s)

    def predict(self, sample_s):
        return np.where(
            self.activation(sample_s) >= 0.0, 1, -1)

    @property
    def cost(self):
        return self._cost
