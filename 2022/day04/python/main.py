def parse_section(section: str) -> set[int]:
    start, end = section.split('-')
    return set(range(int(start), int(end) + 1))

def get_sections(line: str) -> tuple[set[int], set[int]]:
    section1, section2 = line.split(',')
    return (parse_section(section1), parse_section(section2))

def has_full_overlap(sections: tuple[set[int], set[int]]) -> bool:
    return sections[0].issubset(sections[1]) or sections[1].issubset(sections[0])

def has_partial_overlap(sections: tuple[set[int], set[int]]) -> bool:
    intersection = sections[0].intersection(sections[1])
    return len(intersection) > 0

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        d = [line.strip() for line in f.readlines()]

    count_full_overlaps = 0
    count_partial_overlaps = 0

    for line in d:
        sections = get_sections(line)
        if has_full_overlap(sections):
            count_full_overlaps += 1
        if has_partial_overlap(sections):
            count_partial_overlaps += 1


    print(f"Stage 1: {count_full_overlaps}")
    print(f"Stage 1: {count_partial_overlaps}")
