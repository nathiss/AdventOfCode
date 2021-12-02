with open('input.txt', 'r') as f:
    d = f.read().splitlines()

def part1():
    i = 0
    prev = int(d[0].strip())

    for line in d[1:]:
        value = int(line.strip())
        if value > prev:
            i += 1
        prev = value

    print(i)

def part2():
    result = 0

    def getWindow(collection):
        if len(collection) != 3:
            raise Exception(f"len of {str(collection)} is {len(collection)}")
        return sum([int(line) for line in collection])

    window = getWindow(d[:3])

    for i in range(len(d[1:-1])):
        current_window = getWindow(d[i:i+3])

        if current_window > window:
            result += 1

        window = current_window

    print(result)

part1()
part2()
