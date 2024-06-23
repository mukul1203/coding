import pytest

# Function to test

def parity(num):
    ret = False
    while num:
        ret = ret ^ (num & 0x1)
        num >>= 1
    return ret

# Test cases
def testing_parity():
    assert parity(7) == 1
    assert parity(3) == 0

if __name__ == "__main__":
    pytest.main()