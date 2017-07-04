
print len(filter(lambda a: a[0] == a[1],
                 [(i, len(str(a**i)))
                  for a in range(1, 10)
                  for i in range(1, 25)]))
