import unittest

from . import perceptron as perceptron_tests
from . import plot as plot_tests

def load_tests(loader, standard_tests, pattern):
    if pattern == __name__:
        pattern = None
    suite = unittest.TestSuite()
    for test_module in [
        perceptron_tests,
        plot_tests,
    ]:
        tests = (unittest.defaultTestLoader
                 .loadTestsFromModule(test_module, pattern=pattern))
        suite.addTests(tests)
    return suite
