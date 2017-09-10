import sys
import argparse

from pylearn.perceptron import Perceptron
from pylearn.adaline import AdalineGD
from pylearn.adaline import AdalineSGD

import pylearn.plot.iris

_FITTING_MODELS = {model_cls.__name__: model_cls for model_cls in [
    Perceptron,
    AdalineGD,
    AdalineSGD,
]}

class MyHelpFormatter(argparse.ArgumentDefaultsHelpFormatter):

    def __init__(self, *args, **kwargs):
        width = kwargs.pop('width', 60)
        super().__init__(*args, width=width, **kwargs)


def _configParsersFitAndWeightUpdates(parser):
    parser.add_argument(
        '-m', '--model', dest='model_name',
        help=(("name of the model to use to fit data")),
        choices=list(_FITTING_MODELS.keys()),
        default=Perceptron.__name__)
    parser.add_argument(
        '-r', '--learning-rate', dest='learning_rate',
        help=(("factor for weight updates")),
        default=0.1,
        type=float)
    parser.add_argument(
        '-n', '--num-iter', dest='num_iter',
        help=(("number of iterations thru the sample data")),
        default=10,
        type=int)
    parser.add_argument(
        '-s', '--standardize', dest='standardize',
        help=(("standardize data by redistributing along "
                   "normal distribution")),
        action='store_true')


def parseArgs():
    """ parse script arguments """
    argParser = argparse.ArgumentParser(
        formatter_class=MyHelpFormatter,
        )
    subParsers = argParser.add_subparsers(dest='cmd')
    subParsers.add_parser(
        'raw',
        formatter_class=MyHelpFormatter,
        help=("plot raw data only"),
    )
    _configParsersFitAndWeightUpdates(subParsers.add_parser(
        'fit',
        formatter_class=MyHelpFormatter,
        help=("plot perceptron fitted data"),
    ))
    _configParsersFitAndWeightUpdates(subParsers.add_parser(
        'epochs',
        formatter_class=MyHelpFormatter,
        help=("plot weight updates by epoch "
                  "(iteration over sample data)"),
    ))
    return argParser.parse_args()

if __name__ == '__main__':
    args = parseArgs()
    if args.cmd == 'raw':
        pylearn.plot.iris.plot_setosa_versicolor_raw()
    elif args.cmd == 'fit':
        pylearn.plot.iris.plot_fit_setosa_versicolor(
            _FITTING_MODELS[args.model_name],
            learning_rate=args.learning_rate,
            num_iter=args.num_iter,
            standardize=args.standardize,
            )
    elif args.cmd == 'epochs':
        pylearn.plot.iris.plot_weight_updates_setosa_versicolor(
            _FITTING_MODELS[args.model_name],
            learning_rate=args.learning_rate,
            num_iter=args.num_iter,
            standardize=args.standardize,
            )
    elif args.cmd is not None:
        sys.stderr.write("unknown command '" + args.cmd + "'" + '\n')
        quit(9)
    else:
        sys.stderr.write(
            "this script must be supplied with a command. " +
            "run with the '--help' argument to see " +
            "a list of available commands." + '\n')
        quit(2)
