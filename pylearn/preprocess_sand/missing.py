"""
this is a conceptually straignforward api sandbox:
pipe to `less` and read along side the script file.
"""
from io import StringIO

import pandas as pd
from sklearn.preprocessing import Imputer

csv_data='''A,B,C,D
1.0,2.0,3.0,4.0
5.0,6.0,,8.0
0.0,11.0,12.0,'''

df = pd.read_csv(StringIO(csv_data))

### dealing with missing data
print("`pandas.read_csv` returns a type")
print(type(df))
print("that's documented as")
print("""class DataFrame(pandas.core.generic.NDFrame)
 |  Two-dimensional size-mutable, potentially heterogeneous tabular data
 |  structure with labeled axes (rows and columns). Arithmetic operations
 |  align on both row and column labels. Can be thought of as a dict-like
 |  container for Series objects. The primary pandas data structure
""")
print("and looks like")
print(df)
print("""using the DataFrame.isnull method,
it's possible to print the number of missing values per column
""")
print(df.isnull().sum())
print("the above __str__ is for type")
print(type(df.isnull().sum()))
print("""class Series(...mixins...)
 |  One-dimensional ndarray with axis labels (including time series).
 |
 |  Labels need not be unique but must be a hashable type. The object
 |  supports both integer- and label-based indexing and provides a host of
 |  methods for performing operations involving the index. Statistical
 |  methods from ndarray have been overridden to automatically exclude
 |  missing data (currently represented as NaN).
 |
 |  Operations between Series (+, -, /, *, **) align values based on their
 |  associated index values-- they need not be the same length. The result
 |  index will be the sorted union of the two indexes.
""")

### estimating samples or features with missing values
print("DataFrame.dropna can remove columns or rows with missing data")
print("""
dropna(self, axis=0, how='any', thresh=None, subset=None, inplace=False)
    Return object with labels on given axis omitted where alternately any
    or all of the data are missing
""")
print("recall the data set")
print(df)
print("now here are some example dropna() calls")
for kwargs in [
        dict(),
        dict(axis=1),
        dict(how='all'),
        dict(thresh=4),
        dict(subset=['C']),
        ]:
    print("with kwargs " + str(kwargs))
    print(df.dropna(**kwargs))


### imputing missing values
print("""
when removing samples is undesirable, interpolating missing
values is another alternative.  one idea here is to replace
any missing values with the mean value for the entire column
(i.e. the mean of all existing values for that feature).
this simple technique has the fancy (like ketchup) name
"mean imputation".
""")
imr = Imputer(missing_values='NaN', strategy='mean', axis=0)
"""
Imputer.fit and .transform need something that
* can be indexed like a numpy array
* has a .shape attribute, a tuple indicating the array size
pandas' DataFrame meets these criteria,
and in situations where a numpy array is needed,
DataFrame.values will return one.
"""
imr.fit(df)
# example from text
imputed_data = imr.transform(df.values)
# or equivalently (in terms of output, perhaps not computationally)
imputed_data_df = imr.transform(df)
# see?
assert (
    (imputed_data == imputed_data_df).sum()
    == # all True!
    imputed_data.shape[0] * imputed_data.shape[1]
    )
print("so here's the data again")
print(df)
print("and here's the imputed data")
print(imputed_data)
