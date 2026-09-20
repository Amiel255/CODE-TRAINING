def merge(setA, setB):
    merged = list(set(setA + setB))
    merged.sort()
    return merged
    
    
    
setA = [1, 2, 3, 4, 4]
setB = [3, 4, 5, 6 ,7]

print(merge(setA, setB))