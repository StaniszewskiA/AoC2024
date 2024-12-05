from collections import defaultdict, deque
import sys

def process_data(input):
    result_1 = result_2 = 0

    edges, queries = input.split('\n\n')

    E = defaultdict(set)
    ER = defaultdict(set)

    for line in edges.split('\n'):
        x, y = map(int, line.split('|'))
        E[y].add(x)
        ER[x].add(y)

    for query in queries.split('\n'):
        vs = [int(x) for x in query.split(',')]

        valid = True
        for i, x in enumerate(vs):
            for j, y in enumerate(vs):
                if i < j and y in E[x]:
                    valid = False

        if valid:
            result_1 += vs[len(vs) // 2]
        else:
            good = []
            Q = deque([])
            D = {v: len(E[v] & set(vs)) for v in vs}

            for v in vs:
                if D[v] == 0:
                    Q.append(v)

            while Q:
                x = Q.popleft()
                good.append(x)
                for y in ER[x]:
                    if y in D:
                        D[y] -= 1
                        if D[y] == 0:
                            Q.append(y)

            result_2 += good[len(good) // 2]

    return result_1, result_2


def main():
    sys.setrecursionlimit(10**6)
    with open("input.txt", 'r') as f:
        input_data = f.read().strip() 
    result_1, result_2 = process_data(input_data)

    print(result_1)
    print(result_2)

if __name__ == "__main__":
    main()