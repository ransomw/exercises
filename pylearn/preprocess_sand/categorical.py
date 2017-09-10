"""
handling categorical data
_or_
what happens when features aren't all numbers.

instead, features might be
* ordinal — elements of a totally ordered set
* nominal — elements of unordered set
☆ partially-ordinal — elements of a partially-ordered set
☆ netty — with elements of a net
"""
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import OneHotEncoder

df = pd.DataFrame([
    ['green', 'M', 10.1, 'class1'],
    ['red', 'L', 13.5, 'class2'],
    ['blue', 'XL', 15.3, 'class1'],
])
df.columns = ['color', 'size', 'price', 'classlabel']

print("the DataFrame")
print(df)

###

df['size'] = df['size'].map({
    'XL': 3,
    'L': 2,
    'M': 1,
})

print("ordinal mapped")
print(df)

###

_classlabel_map = {
    'class1': 1,
    'class2': 2,
}

def inv_map(some_map):
    return {v: k for k, v in some_map.items()}

df['classlabel'] = df['classlabel'].map(_classlabel_map)

print("""
categorial maps are different conceptually,
but the same implementation may be used""")
print(df)

print("there's idiomatic reverse transform")
df['classlabel'] = df['classlabel'].map(inv_map(_classlabel_map))
print(df)

print("""as well as a sklearn helper to
achieve the same functionality, presumably
in a more computationally-efficient way""")
class_label_encoder = LabelEncoder()
print(
    dict(zip(
        df['classlabel'].values,
        class_label_encoder.fit_transform(df['classlabel'].values)
        ))
)
print(
    dict(zip(
        class_label_encoder.fit_transform(df['classlabel'].values),
        class_label_encoder.inverse_transform(
            class_label_encoder.fit_transform(df['classlabel'].values))
        ))
)

print("""
however, using values that _can_ be ordered to represent
unordered features can be confusing to ML models.
"one-hot encoding" sidesteps this difficulty
*during preprocessing* (as opposed to modelling)
by representing a nominal feature
with N values as N different features, each of which
may have precisly two (truthy or falsey) values.
""")
one_hot_encoder = OneHotEncoder(categorical_features=[
    # color, the categorical feature to encode,
    # is the first column in the t-shirt DataFrame
    0],
    # see comments after fit_transform
    sparse=True, # default.
)

print("""numpy's helper for one-hot encoding expects
lists with numeric values,""")

X = df[df.columns[:3]].values

print("so ordinal label encoding is still necessary")

X[:, 0] = (LabelEncoder()).fit_transform(X[:, 0])

print(X)

print("before encoding the above to")
print(
    one_hot_encoder.fit_transform(
        # note the tolist() call
        X.tolist()
        # without the .toarray(), this is a sparse matrix,
        # which is the (less memory) object to use if possible.
        # the .toarray() method is here for pretty-printing.
        ).toarray()
)

# x = df.columns[:3]
# from pdb import set_trace; set_trace()


print("... or pandas can do it all in one go")
_columns = df.columns[:3].tolist()
_columns.reverse()
print(
    pd.get_dummies(df[_columns])
)
