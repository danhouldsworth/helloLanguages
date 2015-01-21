def mergeSort(aList):
    if len(aList) <= 1:
        return aList

    else: 
        newListLength = len(aList) / 2
        listA = mergeSort(aList[0:newListLength])
        listB = mergeSort(aList[newListLength: ])

        listC = []

        while ((len(listA)>0) or (len(listB)>0)):
            if len(listA) == 0:
                nextItem = listB.pop(0)
            elif len(listB) == 0:
                nextItem = listA.pop(0)
            else:
                #Both list A and B have a length
                if listA[0] <= listB[0] :
                    nextItem = listA.pop(0)
                else:
                    nextItem = listB.pop(0)
            listC.append(nextItem)

        return listC


print mergeSort([200, 4, 1, 5, 6, 33000, 10, 4, 3, 7, 8])

