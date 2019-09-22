from random import *
n = 10
oo = 1000000000
print n
for i in xrange(1, n):
	print i + 1, randint(1, i), randint(1, oo)
print n
for i in xrange(1, n + 1):
	if randint(0, 1) == 0:
		print 'Q', randint(1, n)
	else:
		print 'C', randint(1, n - 1), randint(1, oo)
