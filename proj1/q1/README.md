# Q1 -- Load OSM Data into SQLite

Checklist:
* read up on the [OSM data model](http://wiki.openstreetmap.org/wiki/Elements) 
* install [Osmosis](http://wiki.openstreetmap.org/wiki/Osmosis)
* download a recent map of Alberta from the [Canadian section of the Geofabrik.de download site](https://download.geofabrik.de/north-america/canada.html)
* get the MBR of Edmonton from [the official boundaries of the City of Edmonton](https://data.edmonton.ca/Administrative/City-of-Edmonton-Corporate-Boundary/m45c-6may)
* use osmosis to extract all nodes and paths (with their tags) of Edmonton into an XML file
* process that file to extract the tuples into the SQLite database
* make sure the database has all constraints defined
* make sure your `.gitignore` file prevents you from uploading binary files or large XML files to GitHub (and make sure no such files exist in your repository as well)


# TODOs:
1. put all your scripts to convert the data here
2. write clear instructions so that the TA can reproduce your work below

instructions:
1. copy and paste all the data pair into map.txt
2. run 
    python findboundry.py 
   to find the max and min of the lat and lon which will be the bounding area
3. run
    read-pbf <path to Alberta map>
    bounding-box bottom=... left=... top=... right=...(useing the data from step 2)
    write-xml edmonton.osm
   to generate the osm file for the city of edmonton
4. run  
    gcc -g create_table.c sqlite3/sqlite3.c -lpthread -ldl -lm
    to creat the table with contraint
4. run 
    python create_csv.py
    to generate the corrsponding csv file for each table in db
5. run
    sqlite3
6. get into the sqlite database and import the csv file by hand
6.1    .open  edmonton.db
6.2    .mode csv
6.3    .import node.csv node
6.4    .import way.csv way
6.5    .import nodetag.csv nodetag
6.6    .import waypoint.csv waypoint
6.7    .import waytag.csv waytag
    
(sry but README.md won't let me put command in the right order step 6 it all show up in one line-_-||)
