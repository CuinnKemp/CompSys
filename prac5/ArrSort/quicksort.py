# learning quicksort
import random 
arr = []

for i in range(10):
    arr.append(int(random.random()*200 - 100))

print(arr)

loopCon = 1
pivotIndex = len(arr)-1

prevILeft = -1
prevIRight = len(arr)-1


while loopCon == 1:
    # get new ILeft
    for i in range (prevILeft+1, len(arr)):
        if arr[i] >= arr[pivotIndex]:
            prevILeft = i
            break

    # get new IRight
    for i in reversed(range(0, prevIRight)):
        if arr[i] <= arr[pivotIndex]:
            prevIRight = i
            break

    if prevILeft >= prevIRight:
        loopCon = 0
        break
    
    else:
        temp1 = arr[prevIRight]
        arr[prevIRight] = arr[prevILeft]
        arr[prevILeft] = temp1

arr.insert(prevILeft,arr[pivotIndex])
arr.pop(len(arr)-1)

print(arr)