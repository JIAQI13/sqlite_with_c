#include <stdio.h>
#include <solution.h>

int main() {

  printf("CREATE TABLE IF NOT EXISTS nodeC (id INTEGER , x FLOAT, y FLOAT, PRIMARY KEY(id));\n");
  printf("INSERT INTO nodeC(id, x, y) SELECT id, ( (lon - lon_x) * 6713.7), ( (lat - lat_y) * 11128.6 ) FROM node, ( SELECT MIN(lat) AS lat_y, MIN(lon) AS lon_x FROM node );\n");
  printf("CREATE TABLE IF NOT EXISTS areaMBR(id INTEGER PRIMARY KEY, minX FLOAT, maxX FLOAT, minY FLOAT, maxY FLOAT);");
  printf("INSERT INTO areaMBR(id, minX, maxX, minY, maxY) \n");
  printf("SELECT ways.id, MIN(nodec.x), MAX(nodec.x), MIN(nodec.y), MAX(nodec.y) \n");
  printf("FROM way ways, waypoint waypoints, nodeC nodec \n");
  printf("WHERE ways.closed = 1 AND ways.id = waypoints.wayid AND waypoints.nodeid = nodec.id; \n");
  printf("GROUP BY ways.id;\n");
  return(0);
}
