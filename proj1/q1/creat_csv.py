#source:https://stackoverflow.com/questions/31844713/python-convert-xml-to-csv-file
#source:https://github.com/IAMDXX
import csv
import xml.etree.ElementTree as ET
import sqlite3

def main():
    parser = ET.iterparse('edmonton.osm')
    nodes = dict()
    csvnode = open('node.csv','wb')
    csvnodetag = open('nodetag.csv','wb')
    csvwaypoint = open('waypoint.csv','wb')
    csvwaytag = open('waytag.csv','wb')
    csvway = open('way.csv','wb')
    filenode = ['id', 'lat', 'lon']
    writernode = csv.writer(csvnode)
    filenodetag= ['id', 'k', 'v']
    writernodetag = csv.writer(csvnodetag)   
    filewaypoint = ['id','ordi','nodeid']
    writerwaypoint = csv.DictWriter(csvwaypoint,fieldnames = filewaypoint)
    writerwaypoint.writeheader()
    filewaytag = ['id','k','v']
    writerwaytag = csv.DictWriter(csvwaytag,fieldnames = filewaytag)
    writerwaytag.writeheader()
    filewaytag = ['id','closed']
    writerway = csv.DictWriter(csvway,fieldnames = filewaytag)
    writerway.writeheader()        
    for event, element in parser:
        if element.tag == 'way':
            close = False
            way_pts = []
            ordi = 0
            for ref in element.iter('nd'):
                if (ref.attrib['ref'] in nodes.keys()):
                    way_pts.append(ref.attrib['ref'])
            if len(way_pts) >= 1 and way_pts[0] == way_pts[-1]:
                close = True 
            v = dict()
            k = dict()
            for tag in element.iter('tag'):
                k[ordi] = (tag.attrib['k'])
                v[ordi] = (tag.attrib['v'])
                ordi += 1
            writerway.writerow({'id': str(element.attrib['id']), 'closed': str(close)})
            for i in range(len(way_pts)):
                writerwaypoint.writerow( {'id': str(element.attrib['id']), 'ordi': str(i), 'nodeid': str(way_pts[i])} )
            for i in range(len(k)):
                writerwaytag.writerow({'id': str(element.attrib['id']), 'k': k[i].encode('utf-8'), 'v': v[i].encode('utf-8')} )
            element.clear()
        if element.tag == 'node':
            writernode.writerow( [str(element.attrib['id']), str(element.attrib['lat']) ,str(element.attrib['lon'])] )
            #nodes[element.attrib['id']] = 0
            for tag in element.iter('tag'):
                writernodetag.writerow( [str(element.attrib['id']), tag.attrib['k'].encode('utf-8'), tag.attrib['v'].encode('utf-8')] )                
            element.clear()
    csvnode.close()
    csvnodetag.close()
    csvwaypoint.close()
    csvwaytag.close()
    csvway.close()
if __name__ == "__main__":   
    main()
