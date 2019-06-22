#!/usr/bin/env python3

import sys

dx = [1,2,2,1,-1,-2,-2,-1]
dy = [2,1,-1,-2,-2,-1,1,2]

def inside(x, y):
    return (x >= 0 and x < 8 and y >= 0 and y < 8)


def printBoard(x, y):
    for i in range(8):
        for j in range(8):
            if (i == x and j == y):
                print("k", end=" ")
            else:
                print("0", end=" ")
        print("")


def findProb(start_x, start_y, steps):
    dp1 =[[[0 for i in range(8)]
              for j in range(8)]
              for k in range(steps + 2)]
    for i in range(8):
        for j in range(8):
            dp1[i][j][0] = 1
    for s in range(1, steps + 1):
        for x in range(8):
            for y in range(8):
                p = 0.0
                for i in range(8):
                    nx = x + dx[i]
                    ny = y + dy[i]
                    if (inside(nx, ny)):
                        p += dp1[nx][ny][s-1] / 8.0
                dp1[x][y][s] = p
    return dp1[start_x][start_y][stepts]


if __name__ == "__main__":
    if (len(sys.argv) != 4):
        print("ack")
    else:
        start_x = int(sys.argv[1])
        start_y = int(sys.argv[2])
        steps = int(sys.argv[3])
        prob = findProb(start_x, start_y, steps)
        printBoard(start_x, start_y)
        print("Probability that knight leaves the board in " + str(steps) + " moves: " + str(prob))
