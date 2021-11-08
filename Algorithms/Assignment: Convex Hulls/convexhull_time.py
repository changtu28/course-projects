"""
   Convex Hull Assignment: COSC262 (2018)
   Student Name: Chang Tu
"""
import time

def readDataPts(filename, N):
    """Reads the first N lines of data from the input file
          and returns a list of N tuples
          [(x0,y0), (x1, y1), ...]
    """
    listPts = []
    file = open(filename, "r") #"r" means for reading
    for i in range(N):
        line = file.readline().strip().split()
        line = [float(point) for point in line]
        listPts.append(tuple(line))
    file.close()
    return listPts


def giftwrap(listPts):
    """Returns the convex hull vertices computed using the
          giftwrap algorithm as a list of m tuples
          [(u0,v0), (u1,v1), ...]    
    """
    points = list(listPts)
    k = get_min_y_point(points)
    i = 0
    points.append(points[k])
    v = 0
    c_hull = []
    while True:
        points[i], points[k] = points[k], points[i]
        minAngle = 361
        c_hull.append(points[i])
        for j in range(i+1, len(points)):
            angle = theta(points[i], points[j])
            if angle < minAngle and angle >= v and points[i] != points[j]:
                minAngle = angle
                k = j
        i += 1
        v = minAngle
        if points[k] == points[-1]:
            break
    return c_hull


def grahamscan(listPts):
    """Returns the convex hull vertices computed using the
         Graham-scan algorithm as a list of m tuples
         [(u0,v0), (u1,v1), ...]  
    """
    points = list(listPts)
    p0_index = get_min_y_point(points)
    p0 = points.pop(p0_index)
    points.sort(key=lambda x: theta(p0, x))
    stack = [p0, points[0], points[1]]
    for i in range(2, len(points)): #Should be 2 not 3 since arrays start at 0
        while not isCCW(stack[-2], stack[-1], points[i]):
            stack.pop()
        stack.append(points[i])
    return stack


def amethod(listPts):
    """Returns the convex hull vertices computed using 
          a third algorithm --> Using monotone chain
    """
    if len(listPts) <= 1: #Will not occur in this assignment
        return listPts
    
    points = list(listPts)
    points.sort() #Automatically sorted lexicographically 
    
    lower = [] #lower hull
    for point in points: 
        while len(lower) >= 2 and not isCCW(lower[-2], lower[-1], point): #Very similar to grahamscan
            lower.pop()
        lower.append(point)
        
    upper = [] #upper hull
    for point in reversed(points):
        while len(upper) >= 2 and not isCCW(upper[-2], upper[-1], point):
            upper.pop()
        upper.append(point)
        
    c_hull = lower[:-1] + upper[:-1]
    return c_hull


def get_min_y_point(listPts):
    """Returns the point with the minimum y coordinate
    """
    k = 0
    for i in range(1, len(listPts)):
        if listPts[i][1] < listPts[k][1]:
            k = i
        elif listPts[i][1] == listPts[k][1]:
            if listPts[i][0] > listPts[k][0]:
                k = i
    return k


def theta(pointA, pointB):
    """Computs an approximation of the angle between
       the line AB and a horizontal line through A
    """
    dx = pointB[0] - pointA[0]
    dy = pointB[1] - pointA[1]
    if abs(dx) < 1.e-6 and abs(dy) < 1.e-6:
        t = 0
    else:
        t = dy / (abs(dx) + abs(dy))
        
    if dx < 0:
        t = 2 - t
    elif dy < 0:
        t = 4 + t
    elif t == 0:
        return 360
    return t * 90

def lineFn(ptA, ptB, ptC):
    """The line function as give in lecture notes
    """
    return (
        (ptB[0] - ptA[0]) * (ptC[1] - ptA[1]) -
        (ptB[1] - ptA[1]) * (ptC[0] - ptA[0]) )

def isCCW(ptA, ptB, ptC):
    """The 'is counter-clockwise' function as given in lecture notes
       Returns true if the line makes a counter-clockwise turn from
       the given point
    """
    return lineFn(ptA, ptB, ptC) > 0


def main():
    #listPts = readDataPts('B_3000.dat', 3000)  #File name, numPts given as example only  
    num = 0
    giftwrap_A = []
    giftwrap_B = []
    grahamscan_A = []
    grahamscan_B = []
    monotonechain_A = []
    monotonechain_B = []
    while num < 30:
        num += 3
        data_A = readDataPts('A_' + str(num) + '000.dat', num * 1000)
        data_B = readDataPts('B_' + str(num) + '000.dat', num * 1000)
        start_time = time.time()
        giftwrap(data_A)
        giftwrap_A.append("Gift wrap A" + str(num * 1000) + ": %s seconds" % (time.time() - start_time))
        start_time = time.time()
        giftwrap(data_B)
        giftwrap_B.append("Gift wrap B" + str(num * 1000) + ": %s seconds" % (time.time() - start_time))     
        
        start_time = time.time()
        grahamscan(data_A)
        grahamscan_A.append("Graham Scan A" + str(num * 1000) + ": %s seconds" % (time.time() - start_time))
        start_time = time.time()
        grahamscan(data_B)
        grahamscan_B.append("Graham Scan B" + str(num * 1000) + ": %s seconds" % (time.time() - start_time)) 
        
        start_time = time.time()
        amethod(data_A)
        monotonechain_A.append("Monotone Chain A" + str(num * 1000) + ": %s seconds" % (time.time() - start_time))
        start_time = time.time()
        amethod(data_B)
        monotonechain_B.append("Monotone Chain B" + str(num * 1000) + ": %s seconds" % (time.time() - start_time))
    
    print(*giftwrap_A, sep='\n')
    print(*giftwrap_B, sep='\n')
    print(*grahamscan_A, sep='\n')
    print(*grahamscan_B, sep='\n')
    print(*monotonechain_A, sep='\n')
    print(*monotonechain_B, sep='\n')
    

if __name__  ==  "__main__":
    main()



    
