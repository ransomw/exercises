
def scratch_to_num(c):
    if c == '|':
        return 1
    elif c == ' ':
        return 0
    raise Exception()

def get_num_scratches(pattern):
    return sum([scratch_to_num(s) for s in pattern])

def get_scratch_sig(pattern):
    smIdx = pattern.find(' ')
    if smIdx == -1:
        return [get_num_scratches(pattern)]
    sig = [len(s) for s in
           (scratches[smIdx:] + scratches[:smIdx]).split(' ')]
    sig = filter(lambda l: l != 0, sig)
    sig.sort()
    return sig

def is_match(p1, p2):
    for r in range(len(p1)):
        if p1[r:] + p1[:r] == p2:
            return True
    return False

def match_bullet(guns, bullet):
    for i in range(len(guns)):
        if is_match(guns[i], bullet):
            return i
    return -1

class Bullets(object):
    def match(self, guns, bullet):
        return match_bullet(guns, bullet)
