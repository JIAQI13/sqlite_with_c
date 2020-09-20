def Convert(string,sign):
    li = list(string.split(sign))
    return li

def main():
    #initialize value
    max_lon = None
    max_lat = None
    min_lon = None
    min_lat = None
    boundary = []
    #all map info are saved in map file
    f = open("map.txt")
    fl = f.readlines()
    for pairs in fl:
        boundary.append(Convert(pairs,","))
        #print(boundary)
        for numbers in boundary[0]:
            answer=Convert(numbers," ")
            #fix format
            if len(answer) == 3:
                answer.pop(0)
            #initial value to the first value of the list
            if max_lon == None:
                max_lon = float(answer[0])
            if max_lat == None:
                max_lat = float(answer[1])

            if min_lon == None:
                min_lon = float(answer[0])
            if min_lat == None:
                min_lat = float(answer[1])
            
            #compar the value and find the max
            if max_lon > float(answer[0]):
                max_lon= max_lon
            else:
                max_lon = float(answer[0])
            if max_lat > float(answer[1]):
                max_lat = max_lat
            else:
                max_lat = float(answer[1])

            if min_lon < float(answer[0]):
                min_lon= min_lon
            else:
                min_lon = float(answer[0])
            if min_lat > float(answer[1]):
                min_lat = min_lat
            else:
                min_lat = float(answer[1])
    print("max_lon and max_lat")
    print(max_lon)
    print(max_lat)
    print("min_lon and min_lat")
    print(min_lon)
    print(min_lat)

if __name__=="__main__":
    main()
