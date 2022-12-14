def compare(left, right):
    print(left, "vs", right)
    for i in range(min(len(left), len(right))):
        if type(left[i]) is list and type(right[i]) is int:
            return compare(left[i], [right[i]])
        elif type(left[i]) is int and type(right[i]) is list:
            return compare([left[i]], right[i])
        elif type(left[i]) is int and type(right[i]) is int:
            if left[i] < right[i]:
                return True
            if left[i] > right[i]:
                return False
        elif type(left[i]) is list and type(right[i]) is list:
            if compare(left[i], right[i]):
                return True
            else:
                return False
    if len(left) <= len(right):
        return True
    else:
        return False

print( compare([1,2],[1,3]))
