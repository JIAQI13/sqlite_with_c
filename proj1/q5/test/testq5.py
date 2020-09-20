'''
Checks the output of the solution for Q5
'''

import sys
import subprocess

print "testing Q5"

output=subprocess.check_output(["./bin/solution.out", "../q1/edmonton.db", "./test/nodes.tsv"])
lines = output.strip().split('\n')

if len(lines) > 1 and lines[0] != 'error':
	print "====> ERROR: the output has more lines than expected"
	exit(1)

if len(lines) == 0:
	print "====> ERROR: there is no output"
	exit(1)

if lines[0] != 'success' and lines[0] != 'error':
	print "====> ERROR: output does not look as specified"
	exit(1)
else:
	print "====> SUCCESS: output is formatted correctly"
