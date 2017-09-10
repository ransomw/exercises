"""
PCA amounts to a change of basis vectors, and the trick, if any,
is choosing the new basis vectors.
for Princple Component Analysis, we can consider choosing the new
basis vectors greedily such that the variance of the data set
projected onto the vector is maximized.
that is, for a n-dim feature space, on the (k+1)th iteration of the
vector-choosing algorithm, there is a (n-k)-dim subspace of the
feature space, and among all unit vectors in this subspace,
PCA selects the (k+1)th basis vector to be the one such that the
variance of the projection (i.e. the dot product) of all data points
is maximized.
"""

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

"""
in practice, the PCA algorithm described above is not the way PCA
is implemented.  instead, PCA relies the fact that the (normalized)
eigenvectors of the "covariance matrix" are the vectors that the
above algorithm would produce.
the covariance matrix for N features in n dimensions has entries
$\sigma_{ij} = \frac{1}{N} \sum_{k=1}^N (x_i^{(k)}-\mu_i) (x_j^{(k)}-\mu_j)$
so any algorithm for finding eigenvalues (and thereby eigenvectors),
of which there are many, will suffice for PCA.
"""
# todo: prove the above

cov_mat = np.cov(X_train_std.T)
eigen_vals, eigen_vecs = np.linalg.eig(cov_mat)
print("eigenvalues of covarance matrix:\n%s" %eigen_vals)

"""
since the interest in PCA is reducing dimensionality,
some of the vectors in the change of basis will be discarded.
"""

print("""the "variance explained ratio" of an eigenvalue is
its value divided by the sum of all eigenvalues.
the following plot will show that two dimensions are enough
to account for over half the variance in the wine data.""")
# todo: more conceptual backing of the above (spectral th.)

tot = sum(eigen_vals)
var_exp = [(i / tot) for i in
               sorted(eigen_vals, reverse=True)]
cum_var_exp = np.cumsum(var_exp)

plt.bar(range(1, len(eigen_vals) + 1), var_exp,
            alpha=0.5, align='center',
            label="individual explained variances")
plt.step(range(1, len(eigen_vals) + 1), cum_var_exp,
             where='mid',
             label="individual explained variances")
plt.ylabel("Explained variance ratio")
plt.xlabel("Principal components")
plt.legend(loc='best')
plt.show()

print("""
so the transformation matrix changes basis to that of
the covariance matrix's eigenvectors and projects onto
those two basis vectors that account for most of the
variance""")

eigen_pairs = [ (np.abs(eigen_vals[i]), eigen_vecs[:,i])
                    for i in range(len(eigen_vals)) ]
eigen_pairs.sort(reverse=True)
W = np.hstack(tuple([
    eigen_pairs[i][1][:, np.newaxis] for i
    in range(2)
    ]))

print(W)

print("""and after mapping the feature data into the
two-dimensional subspace defined by this matrix,
it indeed appears fairly well separated along the
coordinate axes""")

X_train_pca = X_train_std.dot(W)

colors = ['r', 'b', 'g']
markers = ['s', 'x', 'o']
for label, color, marker in zip(
        np.unique(y_train), colors, markers):
    plt.scatter(X_train_pca[y_train==label, 0],
                    X_train_pca[y_train==label, 1],
                    c=color, label=label, marker=marker)
plt.xlabel("PC 1")
plt.ylabel("PC 2")
plt.legend(loc='lower left')
plt.show()

print("""
sklearn.decomposition.PCA has all of this builtin
""")
