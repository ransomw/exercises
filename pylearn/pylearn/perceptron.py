import numpy as np

class Perceptron:
    """
    McCullock and Pitts
    """

    def __init__(self, learning_rate=0.01, num_iter=10):
        self.learning_rate = learning_rate
        self.num_iter = num_iter

    def fit(self, samples, targets):
        """
        `samples` (numpy.ndarray[:, :]) --- each row a single data sample
        """
        # _weight[0] is "theta", the threshold for classification
        self._weights = np.zeros(1 + samples.shape[1])
        # number of errors, one count per iteration
        self._errors = []

        for _ in range(self.num_iter):
            num_errors = 0
            for sample, target in zip(samples, targets):
                weight_update_factor = ( # a scalar
                    self.learning_rate
                    *
                    (target - self.predict(sample))
                )
                self._weights[1:] += weight_update_factor * sample
                self._weights[0] += weight_update_factor
                num_errors += int(weight_update_factor != 0.0)
            self._errors.append(num_errors)
        return self # method chaining

    def predict(self, sample):
        return np.where(
            np.dot(sample, self._weights[1:]) > self._weights[0],
            1, -1)

    @property
    def errors(self):
        return self._errors
