'''
Checks the output of the solution for Q2
'''

import sys
import subprocess

print "testing Q3"

K = 20
l = 10

output=subprocess.check_output(["./bin/solution.out", "./test/testq3.db", str(l), str(K)])
lines = output.strip().split('\n')

if len(lines) == 0:
	print "====> ERROR: there is no output"
	exit(1)

if len(lines) == 1:
	if "ERROR" in lines[0]:
		print "====> SUCCESS: output is formatted correctly"
		exit(0)
	else:
		print "====> ERROR (1): output does not meet specifications"
		exit(1)

if len(lines) != K+1:
	print "====> ERROR (2): output does not meet specifications"
	exit(1)

for line in lines[:K-1]:
	try:
		cols = line.split('\t')
		if len(cols) != 6:
			print "====> ERROR (3): output does not meet specifications"
			exit(1)
		for col in cols:
			float_col = float(col)
	except:
		print "====> ERROR (4): output does not meet specifications"
		exit(1)

try:
	number = float(lines[K])	
except:
	print "====> ERROR (5): output does not meet specifications"
	exit(1)

print "====> SUCCESS: output is formatted correctly"
