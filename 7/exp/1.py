import random, string

def rand_str(count, length, name):
    listToPrint = set()
    while len(listToPrint) <= count:
        listToPrint.add(''.join(random.choice(string.ascii_lowercase) for _ in range(length)))

    s_out = ''

    for elem in listToPrint:
        s_out += str(elem) + '\n'

    with open(f"{name}.txt", "w") as f_out:
        f_out.write(s_out)

for i in range(1000, 5000 + 1000, 1000):
    rand_str(count=i, length=6, name=str(i))
