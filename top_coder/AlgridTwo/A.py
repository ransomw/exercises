def countWaysBase(iStr, rStr):
    if iStr == 'BB' or iStr == 'WW':
        return 1
    if iStr == 'BW':
        if rStr == 'BB':
            return 4
        else:
            return 0
    if iStr == 'WB':
        if rStr == 'WW':
            return 4
        else:
            return 0

def countWays(iStr, rStr):
    if len(iStr) == 2:
        return countWaysBase(iStr, rStr)
    lastI = iStr[-2:]
    lastR = rStr[-2:]
    if lastI == 'WW':
        return countWays(iStr[:-1], rStr[:-1])
    if lastI == 'BB':
        return countWays(iStr[:-1], rStr[:-2] + rStr[-1])
    if lastI == 'BW':
        if lastR == 'BB':
            return (countWays(iStr[:-1], rStr[:-2] + 'B') +
                    countWays(iStr[:-1], rStr[:-2] + 'W')) * 2
        else:
            return 0
    if lastI == 'WB':
        if lastR == 'WW':
            return (countWays(iStr[:-1], rStr[:-2] + 'B') +
                    countWays(iStr[:-1], rStr[:-2] + 'W')) * 2
        else:
            return 0


class AlgridTwo(object):
    def makeProgram(self, output):
        numsWays = []
        for i in range(len(output) - 1):
            numsWays.append(countWays(output[i], output[i+1]))
        numWays = 1
        for num in numsWays:
            numWays = (numWays * num) % 1000000007
        return numWays

algridTwo = AlgridTwo()
print algridTwo.makeProgram([
    "WWBWBWBWBWBWBWBW",
    "BWBWBWBWBWBWBWBB",
    "BWBWBWBWBWBWBWBW"])
