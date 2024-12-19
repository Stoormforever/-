import statistics

f1 = open("progs/sizes.txt", 'r')
sizes = list(map(int, f1.readline().split()))
f1.close()

for type in ("main", "key"):
    for speed in ('q', 's'):
        for size in sizes:
            f = open(f"out_data/{type}_{speed}_{size}_out.txt", 'r')
            data = [int(x.strip('\n')) for x in f.readlines()]
            maxx = max(data)
            minn = min(data)
            avg = statistics.mean(data)
            median = statistics.median(data)
            low_quart, _, high_quart = statistics.quantiles(data)
            f.close()
            f = open(f"preproc/{type}_{speed}_{size}.txt", 'w')
            f.write(str(maxx)+' '+str(minn)+' '+str(avg)+' '+str(median)\
                    +' '+str(high_quart)+' '+str(low_quart))
            f.close()

