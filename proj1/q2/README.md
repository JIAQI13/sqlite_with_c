# Q2

Checklist:
* make sure your program follows the life-cycle described [here](https://sqlite.org/c3ref/stmt.html)
* make sure the input/output of your program is as specified
* make sure there are no warnings or errors raised by Travis-CI
* make sure your program **follows the life-cycle described in** <a href='https://sqlite.org/c3ref/stmt.html'>https://sqlite.org/c3ref/stmt.html</a>

# TODO: explain your choice of distance function

source:
https://www.geeksforgeeks.org/program-distance-two-points-earth/


to run the program 
type
./(name of the compiled file) (database file) (node_id 1) (node_id_2) 
i am using Haversine formula to calcaute the distance 
this formula is used to calculate the distance between tow point on a sphere based on its latitudes and longitudes
it is a special case of the law of haversines
because i think since the points are only in edmonton its not too far away compare to the earth size
so I just assume that they are approximatly on the same sophere althought the earth is not a sphere(>_<||)
i test it on the lab machine with make test it passed but it shows as "x" on github...>_<||
