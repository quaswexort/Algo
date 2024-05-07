keys = set()

with open("input.txt", "r") as file:
    for line in file:
        keys.add(int(line))

with open("output.txt", "w") as file:
    file.write(str(sum(keys)))
    