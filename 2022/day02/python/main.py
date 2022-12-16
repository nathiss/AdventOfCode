import copy

ROCK = 1
PAPER = 2
SCISSORS = 3
UNKNOWN = -1

class Shape:
    def __init__(self, char: str):
        if char in "AX":
            self.type = ROCK
        elif char in "BY":
            self.type = PAPER
        elif char in "CZ":
            self.type = SCISSORS
        else:
            self.type = UNKNOWN

    def is_rock(self) -> bool:
        return self.__check_type(ROCK)

    def is_paper(self) -> bool:
        return self.__check_type(PAPER)

    def is_scissors(self) -> bool:
        return self.__check_type(SCISSORS)

    def get_win(self):
        if self.is_rock():
            return Shape("B")
        if self.is_paper():
            return Shape("C")
        if self.is_scissors():
            return Shape("A")
        return Shape("")

    def get_draw(self):
        return copy.deepcopy(self)

    def get_loose(self):
        if self.is_rock():
            return Shape("C")
        if self.is_paper():
            return Shape("A")
        if self.is_scissors():
            return Shape("B")
        return Shape("")

    def get_score(self) -> int:
        if self.is_rock():
            return 1
        if self.is_paper():
            return 2
        if self.is_scissors():
            return 3
        return 0

    def __eq__(self, o) -> bool:
        return self.type == o.type

    def __str__(self) -> str:
        if self.is_rock():
            return "ROCK"
        if self.is_paper():
            return "PAPER"
        if self.is_scissors():
            return "SCISSORS"
        return "UNKNOWN"

    def __check_type(self, type: int) -> bool:
        return self.type == type

class Shape2(Shape):
    def __init__(self, char: str, result: str = None):
        if result == None:
            super().__init__(char)
        else:
            other = Shape(char)
            if result == "X": # loose
                self.type = other.get_loose().type
            elif result == "Y": # draw
                self.type = other.get_draw().type
            elif result == "Z": # win
                self.type = other.get_win().type

def get_input() -> list[str]:
    with open("input.txt", "r") as f:
        return [line[:-1] for line in f.readlines()]

def get_score(shape1: Shape, shape2: Shape) -> int:
    score = shape2.get_score()

    if shape1 == shape2:
        score += 3
    elif shape1.is_rock() and shape2.is_paper():
        score += 6
    elif shape1.is_paper() and shape2.is_scissors():
        score += 6
    elif shape1.is_scissors() and shape2.is_rock():
        score += 6

    return score

def parse_line(line: str) -> tuple[Shape, Shape]:
    s1, s2 = line.split(" ")
    return (Shape(s1), Shape(s2))

def parse_line2(line: str) -> tuple[Shape2, Shape2]:
    s1, s2 = line.split(" ")
    return (Shape2(s1), Shape2(s1, s2))

def main() -> None:
    score = 0
    for line in get_input():
        shape1, shape2 = parse_line(line)
        score += get_score(shape1, shape2)

    print(f"Stage 1: {score}")

    score = 0
    for line in get_input():
        shape1, shape2 = parse_line2(line)
        score += get_score(shape1, shape2)

    print(f"Stage 2: {score}")

if __name__ == "__main__":
    main()
