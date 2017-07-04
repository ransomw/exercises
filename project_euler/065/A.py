
def aiTerm(i):
    if i % 3 == 1:
        k = (i + 2) / 3
        return 2*k
    return 1


def eConv(N):
    ai_terms = [aiTerm(i) for i in range(N-1)]
    ai_terms.reverse()
    cf = [1, ai_terms[0]]
    for ai in ai_terms[1:]:
        cf = [cf[0]+ai*cf[1], cf[1]]
        cf = [cf[1], cf[0]]
    return [cf[0]+2*cf[1],cf[1]]

# print [eConv(N) for N in range(2, 11)]
print sum([int(d) for d in str(eConv(100)[0])])
