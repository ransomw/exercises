import sys
import unittest

import numpy as np

from pylearn.dat import get_iris_data

class PerceptronTests(unittest.TestCase):

    def setUp(self):
        species_list = get_iris_data(vectorization='species')
        self.species_arr = np.array(
            [(1.0 if s.value == 'R' else -1.0) for s in species_list])
        self.sample_arr = np.array(get_iris_data())

    def tearDown(self):
        pass

    def testDataSetup(self):
        self.assertIs(type(self.species_arr), np.ndarray)
        self.assertIs(type(self.sample_arr), np.ndarray)
        self.assertEqual(self.species_arr.shape[0],
                             self.sample_arr.shape[0])
        zip_item = next(zip(self.sample_arr, self.species_arr))
        self.assertIs(type(zip_item), tuple)
        self.assertEqual(len(zip_item), 2)
        self.assertIs(type(zip_item[0]), np.ndarray)
        self.assertTrue(isinstance(zip_item[1], np.float))


def load_tests(loader, tests, pattern):
    suite = unittest.TestSuite()
    if pattern is None:
        suite.addTests(loader.loadTestsFromTestCase(PerceptronTests))
    else:
        tests = loader.loadTestsFromName(pattern,
                                         module=sys.modules[__name__])
        failedTests = [t for t in tests._tests
                       if type(t) == unittest.loader._FailedTest]
        if len(failedTests) == 0:
            suite.addTests(tests)
    return suite
