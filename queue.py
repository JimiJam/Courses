# with heapq
from heapq import heappop, heappush, heapify 

def queueWithPriotityHeapq():
    heap = []
    heapify(heap)
    results = list()

    # get input
    n = int(input())
    for _i in range(0, n):
        key_value = list(input().split())

        if key_value[0] == 'Insert':
            if int(key_value[1]):
                heappush(heap, -1 * int(key_value[1]))
        elif key_value[0] == 'ExtractMax':
            results.append(-1 * heappop(heap))
    
    # print ExtractMax
    for m in results:
        print(m)

# custom realisation
# binary max heap class
class MaxHeap:
    h = []

    # constructor
    def __init__(self):
        pass 

    def __siftUp(self, i):
        if self.h[i - 1] > self.h[i // 2 - 1] and i != 1:
            self.h[i - 1], self.h[i // 2 - 1] = self.h[i // 2 - 1], self.h[i - 1]
            self.__siftUp(i // 2)

    def getMaxChildIndex(self, i):
        left_leaf = -1
        right_leaf = -1

        if (2 * i) <= len(self.h):
            left_leaf = self.h[2 * i - 1]
        if (2 * i + 1) <= len(self.h):
            right_leaf = self.h[2 * i]
        
        if left_leaf >= right_leaf:
            return 2 * i
        else:
            return 2 * i + 1

    def __siftDown(self, i):
        max_index = self.getMaxChildIndex(i)

        if max_index <= len(self.h) and self.h[max_index - 1] > self.h[i - 1]:
            self.h[i - 1], self.h[max_index - 1] = self.h[max_index - 1], self.h[i - 1]
            self.__siftDown(max_index)

    def insert(self, num):
        self.h.append(num)
        self.__siftUp(len(self.h))

    def getMax(self):
        if self.h:
            return self.h[0]

    def exctractMax(self):
        cur_max = self.getMax()
        if cur_max:
            # swap first and last 
            self.h[0], self.h[-1] = self.h[-1], self.h[0]
            # remove max
            self.h.pop()
            self.__siftDown(1)
            return cur_max

def queueWithPriotity():
    heap = MaxHeap()
    results = list()

    # get input
    n = int(input())
    for _i in range(0, n):
        key_value = list(input().split())

        if key_value[0] == 'Insert':
            if int(key_value[1]):
                heap.insert(int(key_value[1]))
        elif key_value[0] == 'ExtractMax':
            cur_max = heap.exctractMax()
            # empty check
            if cur_max:
                results.append(cur_max)
    
    # print ExtractMax
    for m in results:
        print(m)