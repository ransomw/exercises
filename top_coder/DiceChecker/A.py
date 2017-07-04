from pdb import set_trace as st


def bad_values(values):
    sums = [0 for _ in range(7)]
    for value in values:
        sums[value] += 1
    bvals = []
    for i in range(1, 7):
        avg = float(sums[i]) / len(values)
        if avg > 1./4 or avg < 1./10:
            bvals.append(i)
    return tuple(bvals)

class DiceChecker(object):
    def badValues(self, param):
        return bad_values(param)


dc = DiceChecker()
print dc.badValues((1, 2, 3, 4, 5, 6, 1, 2, 3, 4))
print dc.badValues((3, 1, 5))
print dc.badValues((1, 1, 1, 1, 1, 1, 1, 2, 2, 2))
print dc.badValues((1, 1, 3, 3, 4, 4, 2, 2, 5, 5, 6, 6 ))
