#!/usr/bin/env python3

# Python 3 implementation to find
# minimum number of deletions
# to make a string palindromic

# Returns the length of
# the longest palindromic
# subsequence in 'str'
def lps(s):
    n = len(s)
    # Create a table to store
    # results of subproblems
    L = [[0 for x in range(n)] for y in range(n)]
    # Strings of length 1
    # are palindrome of length 1
    for i in range(n):
        L[i][i] = 1
    # Build the table. Note that
    # the lower diagonal values
    # of table are useless and
    # not filled in the process.
    # c1 is length of substring
    for cl in range(2, n + 1):
        for i in range(n - cl + 1):
            j = i + cl - 1
            if s[i] == s[j] and cl == 2:
                L[i][j] = 2
            elif s[i] == s[j]:
                L[i][j] = L[i + 1][j - 1] + 2
            else:
                L[i][j] = max(L[i][j - 1], L[i + 1][j])
    # length of longest
    # palindromic subseq
    return L[0][n - 1]


# function to calculate
# minimum number of deletions
def minimumNumberOfDeletions(s):
    n = len(s)
    # Find longest palindromic
    # subsequence
    l = lps(s)
    # After removing characters
    # other than the lps, we
    # get palindrome.
    return n - l


# Driver Code
if __name__ == "__main__":
    s = "geeksforgeeks"
    print("Minimum number of deletions = ", minimumNumberOfDeletions(s))
