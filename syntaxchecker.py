import sys
import os

import exploitable as e


def is_valid():
    if e.check_syntax(sys.argv[1]):
        print("File structure is valid")
    else:
        print("File structure is not valid")


if __name__ == "__main__":
    if len(sys.argv) == 2:
        is_valid()
    else:
        raise Exception("Didn't provide needed argument")
