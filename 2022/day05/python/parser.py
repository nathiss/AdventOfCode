import copy

__all__ = ["Parser"]


class _Stack:
    def __init__(self, collection: list[str] = None):
        self.__stack = collection if collection != None else []

    def push_many(self, elements: list[str]) -> None:
        elements.extend(self.__stack)
        self.__stack = elements

    def push(self, element: str) -> None:
        self.__stack.insert(0, element)

    def pop(self) -> str:
        assert len(self.__stack) != 0
        return self.__stack.pop(0)

    def pop_many(self, amount: int) -> list[str]:
        assert len(self.__stack) >= amount
        slice = self.__stack[:amount]
        self.__stack = self.__stack[amount:]
        return slice

    def peek(self) -> str:
        assert len(self.__stack) != 0
        return self.__stack[0]

    def reverse(self):
        self.__stack.reverse()

    def __str__(self) -> str:
        return str(self.__stack)

class Parser:
    def __init__(self, lines: list[str]):
        raw_indexes = [index.strip() for index in lines[-1].split(" ") if index != ""]
        self.__stacks = [_Stack() for _ in range(len(raw_indexes))]

        raw_stacks = lines[:-1]
        for stack_line in raw_stacks:
            for stack_idx, char_idx in enumerate(range(1, len(stack_line), 4)):
                char = stack_line[char_idx]
                if char.isspace():
                    continue
                self.__stacks[stack_idx].push(char)

        for stack in self.__stacks:
            stack.reverse()

    def parse(self) -> list[_Stack]:
        return copy.deepcopy(self.__stacks)
