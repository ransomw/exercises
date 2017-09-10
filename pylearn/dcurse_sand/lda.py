"""
Linear Discriminant Analysis is similar to PCA in that it relies
on a change of basis and projection into a subspace of that basis.
rather than selecting the change of basis to maximize variance,
LDA selects it in order to "maximize separability" of the features
"""
# todo: this entire section is lacking details to connect
#  algorithmic implementation and the claim about the output
#  -- i.e., what does it mean to maximize separability
#           (as in the topological sense), and
#           why does LDA achieve this goal?)

import os.path

import numpy as np
import pandas as pd
from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt

# as in preprocess_sand/wine.py
df = pd.read_csv(os.path.join(os.path.dirname(__file__), 'wine.csv'),
                     header=None)
X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values
X_train, X_test, y_train, y_test = train_test_split(
    X, y,
    test_size=0.3,
    random_state=0,
)
stdsc = StandardScaler()
X_train_std = stdsc.fit_transform(X_train)
X_test_std = stdsc.transform(X_test)

feat_labels = np.unique(y).tolist()
num_feats = X_train_std.shape[1]

print("""compute mean vectors""")

np.set_printoptions(precision=4)

mean_vecs = []
for label in feat_labels:
    mean_vecs.append(np.mean(
        X_train_std[y_train==label], axis=0))

for idx, vec in zip(feat_labels, mean_vecs):
    print("{idx}\n{vec}".format(idx=idx, vec=vec))

print("""within class scatter matrix""")

S_w = np.zeros((num_feats, num_feats))
for label, mvec in zip(feat_labels, mean_vecs):
    class_scatter = np.zeros((num_feats, num_feats))
    for row in X[y==label]:
        row = row.reshape(num_feats, 1)
        mvec = mvec.reshape(num_feats, 1)
        class_scatter += (row-mvec).dot((row-mvec).T)
    S_w += class_scatter

print("shape: {shape}".format(shape=S_w.shape))

print("""
however, """)
