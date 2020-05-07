import os
import sys

al_visited = {1: [0, 1], 2: [0, 2]}


def print_way(last_line, station):
#    print(al_visited, last_line, station)
    if station == 0:
        return 
    else:
        print_way(al_visited[last_line][station], station-1)
        print('assembly line {}, station {}'.format(last_line, station))

def fastest_way():
    station_count = len(a[1].keys())

    f = dict()
    f[1] = {key: 0 for key in range(1, station_count+1)}
    f[2] = {key: 0 for key in range(1, station_count+1)}

    f[1][1] = a[1][1] + e1
    f[2][1] = a[2][1] + e2

    # al is active_assembly_line, sn is station_no, il is inactive_assembly_line
    cost = lambda al, sn, il: min(f[al][sn-1] + a[al][sn], f[il][sn-1]+t[il][sn-1]+a[al][sn])
    line = lambda al, sn, il: al if f[al][sn-1] + a[al][sn] < f[il][sn-1]+t[il][sn-1]+a[al][sn] else il
    
    for station in range(2, len(a[1].keys())+1):
        f[1][station] = cost(1, station, 2)
        f[2][station] = cost(2, station, 1)
        al_visited[1].append(line(1, station, 2))
        al_visited[2].append(line(2, station, 1))

    min_cost = min(f[1][station_count] + x1, f[2][station_count] + x2)
    last_line = 1 if f[1][station_count] + x1 < f[2][station_count] + x2 else 2
    return min_cost, last_line

   
if __name__ == "__main__":
    # prepare input
    # time taken at each station on the two assembly lines
    a = dict()
    a[1] = {1:7, 2:9, 3:3, 4:4, 5:8, 6:4}
    a[2] = {1:8, 2:5, 3:6, 4:4, 5:5, 6:7}

    # entry/exit times for both assembly lines
    e1 = 2
    e2 = 4
    x1 = 3
    x2 = 2

    # time to move between stations. t[i][j] is the time to move away from station i after visiting station j
    t = dict()
    t[1] = {1:2, 2:3, 3:1, 4:3, 5:4}
    t[2] = {1:2, 2:1, 3:2, 4:2, 5:1}

    min_cost, last_line = fastest_way()
    print('min_cost: {}'.format(min_cost))
    print_way(last_line, len(a[1].keys()))
    

