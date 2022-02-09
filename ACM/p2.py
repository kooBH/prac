import sys
W, H = map(int, sys.stdin.readline().split())
keypad = []

max_width = 1000
block_size = 100
num_block_width = int(max_width/block_size) + bool(max_width%block_size)
not_found_dist = 100000
max_range = num_block_width-1

blocks = []
for y in range(H):
    blocks.append([])
    for x in range(W):
        blocks[y].append([])
        for n in range(10) : 
            blocks[y][x].append([])

def cur_block(x,y) : 
    x_idx = int(x/block_size)
    y_idx = int(y/block_size)

    return x_idx,y_idx


y_block_idx = 0
x_block_idx = 0

for y in range(H):
        y_block_idx = int(y/block_size)
        x = 0
        for v in str(sys.stdin.readline()) : 
            x_block_idx = int(x/block_size)
            if v == '\n': 
                continue
            v = int(v)
            blocks[y_block_idx][x_block_idx][v].append([y+1,x+1])
            x +=1

"""
for y in range(H):
    for x in range(W): 
        print(str(y) + ' ' + str(x))
        print(blocks[y][x])
"""

N = int(sys.stdin.readline())
for n in range(N) :
    x,y,n_seq,v_seq = sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    for target_v in str(v_seq):
        target_v = int(target_v)
        min_dist = not_found_dist

        s_x,s_y = cur_block(x,y)
        for search_range in range(max_range) :
            for direction_x in [1,-1] : 
                for direction_y in [1,-1] : 
                    for direction_ratio_x in range(search_range+1) :
                        search_x = s_x + direction_x * direction_ratio_x
                        search_y = s_y + direction_y * (search_range - direction_ratio_x)

                        if search_x < 0 or search_x >= W : 
                            continue
                        if search_y < 0 or search_y >= H :
                            continue

                        for tmp_target in blocks[search_y][search_x][target_v]:
                            tmp_dist = abs(tmp_target[1]- x) + abs(tmp_target[0]-y)
                            if tmp_dist < min_dist:
                                min_dist = tmp_dist
                
            if min_dist != not_found_dist : 
                break

        print(min_dist,end=' ')
    print('')

