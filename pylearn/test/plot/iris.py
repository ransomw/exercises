import sys
import unittest

from pylearn.perceptron import Perceptron
from pylearn.adaline import AdalineGD
from pylearn.adaline import AdalineSGD
from pylearn.plot import iris

class IrisTests(unittest.TestCase):
    TEST_MODELS = [
        Perceptron,
        AdalineGD,
        AdalineSGD,
        ]

    def test_plot_setosa_versicolor_raw(self):
        iris.plot_setosa_versicolor_raw(show=False)

    def test_fit_setosa_versicolor(self):
        _, _, perceptron = iris.fit_setosa_versicolor(Perceptron)
        self.assertEqual(
            set(perceptron.errors[5:]),
            set([0]),
            msg="error count doesn't go to zero")
        _, _, adalineGD = iris.fit_setosa_versicolor(AdalineGD)
        _, _, adalineSGD = iris.fit_setosa_versicolor(AdalineSGD)

    def test_plot_fit_setosa_versicolor(self):
        for model in self.TEST_MODELS:
            iris.plot_fit_setosa_versicolor(
                model, show=False)

    def test_plot_weight_updates_setosa_versicolor(self):
        for model in self.TEST_MODELS:
            iris.plot_weight_updates_setosa_versicolor(
                model, show=False)


def load_tests(loader, tests, pattern):
    suite = unittest.TestSuite()
    if pattern is None:
        suite.addTests(loader.loadTestsFromTestCase(IrisTests))
    else:
        tests = loader.loadTestsFromName(pattern,
                                         module=sys.modules[__name__])
        failedTests = [t for t in tests._tests
                       if type(t) == unittest.loader._FailedTest]
        if len(failedTests) == 0:
            suite.addTests(tests)
    return suite
