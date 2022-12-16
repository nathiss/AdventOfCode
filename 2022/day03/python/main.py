def type_to_priority(type: str) -> int:
    assert len(type) == 1

    if type.isupper():
        return ord(type) - ord("A") + 27
    return ord(type) - ord("a") + 1

def get_compartments(rucksack: str) -> tuple[str, str]:
    assert len(rucksack) % 2 == 0

    half_size = len(rucksack) // 2
    return (rucksack[:half_size], rucksack[half_size:])

def get_common_type(*compartments: list[str]) -> str:
    compartments = [set(compartment) for compartment in compartments]

    intersection = set.intersection(*compartments)
    assert len(intersection) == 1

    return intersection.pop()

def window(collection: any, size: int):
    assert len(collection) % size == 0

    for i in range(0, len(collection), size):
        yield collection[i:i+size]

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        d = [line.strip() for line in f.readlines()]

    priorities = []

    for rucksack in d:
        compartment1, compartment2 = get_compartments(rucksack)
        common = get_common_type(compartment1, compartment2)
        priorities.append(type_to_priority(common))

    print(f"Stage 1: {sum(priorities)}")

    priorities = []

    for group in window(d, 3):
        common = get_common_type(*group)
        priorities.append(type_to_priority(common))

    print(f"Stage 2: {sum(priorities)}")
