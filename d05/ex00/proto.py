#!/usr/bin/env python3

import sys

def findPermsRecur(arr, index, num, rnum):
    if (rnum < 0):
        return;
    if (rnum == 0):
        for i in range(index):
            print(arr[i], end=" ")
        print("");
        return;
    prev = 1 if (index == 0) else arr[index - 1];
    for k in range(prev, num + 1):
        arr[index] = k
        findPermsRecur(arr, index + 1, num, rnum - k)


def findPerms(n):
    arr = [0] * n;

    findPermsRecur(arr, 0, n, n);

def main(argv):
    if (len(argv) != 2):
        print("Usage: " + argv[0] + " [0-9]+")
        return 1
    num = int(argv[1])
    findPerms(num)
    return 0

if __name__ == "__main__":
    main(sys.argv)
