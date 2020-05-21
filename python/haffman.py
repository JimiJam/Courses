from operator import itemgetter
from collections import deque

class Tree:
    def __init__(self, cargo, left=None, right=None):
        self.cargo = cargo
        self.left  = left
        self.right = right

    def __str__(self):
        return str(self.cargo)
        
    def __getitem__(self, key):
        return self.cargo[key]

def traverseTree(tree, cur_code, haff_dict):
    if cur_code != '' and "cargo_" not in tree[1]:
        haff_dict[tree[1]] = cur_code
    try:
        traverseTree(tree.left, cur_code + "0", haff_dict)
        traverseTree(tree.right, cur_code + "1", haff_dict)
    except:
        return 

def haff(input_str):
    result_str = ''
    
    queue_with_priority = deque()
    # get priority and into to deque
    for c in input_str:
        is_find = False
        for i in queue_with_priority:
            if c == i[-1]:
                i[0] += 1
                is_find = True
        if not is_find:
            queue_with_priority.append([1, c])
            
    # sort deque
    queue_with_priority = deque(sorted(queue_with_priority, key=itemgetter(0)))
    
    # get tree
    c_num = 1
    while len(queue_with_priority) != 1:
        i = queue_with_priority.popleft()
        j = queue_with_priority.popleft()
        t = Tree([i[0] + j[0], 'cargo_{0}'.format(c_num)], i, j)
        c_num += 1
        queue_with_priority.appendleft(t)
        queue_with_priority = deque(sorted(queue_with_priority, key=itemgetter(0)))
    
    # traverse a tree and create Haffman dict
    haff_dict = {}
    if type(queue_with_priority[0]) is list and len(queue_with_priority) == 1:
        haff_dict[queue_with_priority[0][1]] = "0"
    else:    
        traverseTree(queue_with_priority[0], "", haff_dict)

    # enc string
    for a in input_str:
       result_str += haff_dict[a]

    return result_str

test_str = 'accepted'
print(haff(test_str))

def decodeHaffman():
    # get data
    haff_dict = {}
    n, str_len = input().split()
    for i in range(0, int(n)):
        code = input().split(': ')
        haff_dict[code[-1]] = code[0]
        
    enc_str = str(input())
    
    # decode string
    result_str = ""
    cur_char = ""
    for a in enc_str:
        cur_char += a
        if cur_char in haff_dict.keys():
            result_str += haff_dict[cur_char]
            cur_char = ""
    
    print(result_str)