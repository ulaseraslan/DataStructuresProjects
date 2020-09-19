from itertools import product
from random import choice
from os import listdir

SIZE_X = -1 
SIZE_Y = -1
MAZE = None


def readMaze(pathToMaze):
    global MAZE
    inFile = open(pathToMaze)
    MAZE = {}
    inFile.readline()
    for line in inFile:
        line = line.rstrip()
        if not line:
            continue
        tmp = line.split(",")
        cell = {}
        for tm in tmp:
            tm = tm.split("=")
            cell[tm[0]] = int(tm[1])
        coord = (int(cell["x"]), int(cell["y"]))
        MAZE[coord] = cell
    inFile.close()
    return MAZE

def getMazeSize():
    global SIZE_X, SIZE_Y
    SIZE_X = 0
    SIZE_Y = 0
    for (x,y) in MAZE:
        if x > SIZE_X:
            SIZE_X = x
        if y > SIZE_Y:
            SIZE_Y = y
    SIZE_X += 1
    SIZE_Y += 1
    if len(MAZE) != (SIZE_X * SIZE_Y):
        raise SystemError("Sth is wrong about cell indexing!")


def cellIterator():
    for (x,y) in product(range(SIZE_X), range(SIZE_Y)):
        yield (x,y)

def wallExistsBetweenCells(cell1, cell2):
    (x1, y1) = cell1
    (x2, y2) = cell2
    if x1 + 1 == x2 and y1 == y2:
        #print "1"
        #print "cell1", cell1, MAZE[cell1]
        #print "cell2", cell2, MAZE[cell2]
        
        if MAZE[cell1]["r"] == MAZE[cell2]["l"]:
            if MAZE[cell1]["r"] == 0:
                return False
            else:
                return True
        else:
            raise SystemError("Right wall of cell", str(cell1), "!= Left wall of cell", str(cell2))
           
    elif x1 - 1 == x2 and y1 == y2:
        #print "2"
        if MAZE[cell1]["l"] == MAZE[cell2]["r"]:
            if MAZE[cell1]["l"] == 0:
                return False
            else:
                return True
        else:
            raise SystemError("Down wall of cell", str(cell1), "!= Up wall of cell", str(cell2))
        
        
    elif x1 == x2 and y1 + 1 == y2:
        #print "3"
        if MAZE[cell1]["u"] == MAZE[cell2]["d"]:
            if MAZE[cell1]["u"] == 0:
                return False
            else:
                return True
        else:
            raise SystemError("Up wall of cell", str(cell1), "!= Down wall of cell", str(cell2))  
        
    elif x1 == x2 and y1 - 1 == y2:
        #print "4"
        if MAZE[cell1]["d"] == MAZE[cell2]["u"]:
            if MAZE[cell1]["d"] == 0:
                return False
            else:
                return True
        else:
            raise SystemError("Down wall of cell", str(cell1), "!= Up wall of cell", str(cell2))  

 
    else:
        raise SystemError("Can not happen!")
        
def getPossibleNeighboursToVisit(cell):
    # finds set of neighbour states
    # does not consider whether it is visited 
    (x,y) = cell
    neigh = []
    candidates = [(x+1,y), (x-1,y), (x,y+1), (x,y-1)]
    for cand in candidates:
        (x,y) = cand
        if x >= SIZE_X or x < 0:
            continue
        elif y >= SIZE_Y or y < 0:
            continue
        else:
            #print x,y
            if not wallExistsBetweenCells(cell, cand):
                neigh.append(cand)
    return neigh
  
def debugInfo(topCell, randNextCell, nextCells):
    print "Current cell :", topCell
    print "Candidates   :", nextCells
    print "Chosen cell  :", randNextCell
    print

def findAllPathsBetween2Cells(cell1, cell2):
    visited = {}
    paths = []
    for (x,y) in cellIterator():
        visited[(x,y)] = False
    
    visited[cell1] = True
    
    stack = [cell1]
    while len(stack) > 0:
        topCell = stack[-1]
        candNextCells = getPossibleNeighboursToVisit(topCell)        
        nextCells = [c for c in candNextCells if not visited[c]]
        #print topCell, candNextCells, nextCells
        if len(nextCells) == 0:
            stack.pop()
        else:
            randNextCell = choice(nextCells)
            stack.append(randNextCell)
            visited[randNextCell] = True
            #debugInfo(topCell, randNextCell, nextCells)
            if randNextCell == cell2:
                paths.append(list(stack))
    return paths
                

def existCycle(cell1):
    visited = {}
    paths = []
    for (x,y) in cellIterator():
        visited[(x,y)] = False
    
    visited[cell1] = True
    
    stack = [cell1]
    while len(stack) > 0:
        topCell = stack[-1]
        candNextCells = getPossibleNeighboursToVisit(topCell)
        if cell1 in candNextCells and len(stack) > 2:
            print stack
            return True
        nextCells = [c for c in candNextCells if not visited[c]]
        #print topCell, candNextCells, nextCells
        if len(nextCells) == 0:
            stack.pop()
        else:
            randNextCell = choice(nextCells)
            stack.append(randNextCell)
            visited[randNextCell] = True
            #debugInfo(topCell, randNextCell, nextCells)
    return False
            
            
def mazeVerifier(pathToMaze):
    # Every cell pair in the maze must be reachable
    # Reachability must be unique
    readMaze(pathToMaze)   # read into global variable MAZE
    getMazeSize()  # read into global variables SIZE_X and SIZE_Y
    #print "sizeX:", SIZE_X, "sizeY:", SIZE_Y
    for cell1 in cellIterator():
        if existCycle(cell1):
            print "Cell ", cell1, "can reach itself "
            return False
    return True
    
    
def main(pathToMazes):
    for fn in listdir(pathToMazes):
        if "maze_cells" in fn:
            print "Veryfying maze '" + fn + "'"
            if not mazeVerifier(pathToMazes + fn):
                print "in maze ", fn
            else:
                print fn, "is valid"
            print 
    

    
    





pathToMazes = "./"
main(pathToMazes)


    


