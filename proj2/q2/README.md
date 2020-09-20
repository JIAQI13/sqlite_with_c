TODO: provide SQLite commands and/or bash shell scripts to create the two databases for Q3.
sqlite3
- .open //filename
- CREATE TABLE IF NOT EXISTS MBR(id INTEGER PRIMARY KEY, minX FLOAT, maxX FLOAT, minY FLOAT, maxY FLOAT);
- INSERT INTO MBR (id, minX, maxX, minY, maxY)
- SELECT areaMBR.id, areaMBR.minX, areaMBR.maxX, areaMBR.minY, areaMBR.maxY FROM areaMBR;
- CREATE INDEX btree_minX ON areaMBR (minX);
- CREATE INDEX btree_minY ON areaMBR (minY);
- CREATE INDEX btree_maxX ON areaMBR (maxX);
- CREATE INDEX btree_maxY ON areaMBR (maxY);
- .quit

- (save it in a txt file for example translate.txt)
- sqlite3 part2_btree.db < translated.txt


- sqlite3
- .open //filename
- CREATE VIRTUAL TABLE MBR using rtree (id INTEGER PRIMARY KEY, minX FLOAT, maxX FLOAT , minY FLOAT, maxY FLOAT);
- INSERT INTO MBR (id , minX, maxX, minY, maxY)
- SELECT areaMBR.id, areaMBR.minX, areaMBR.maxX, areaMBR.minY, areaMBR.maxY
- FROM areaMBR;
- .quit

- (save it in a txt file for example translate.txt)
- sqlite3 part2_rtree.db < translated.txt
