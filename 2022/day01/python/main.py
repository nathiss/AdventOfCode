def get_calories(lines):
    elf_calories = 0
    for line in lines:
        if line == "\n" or line == "":
            yield elf_calories
            elf_calories = 0
        else:
            elf_calories += int(line[:-1])
    return elf_calories

def main():
    with open("input.txt", "r") as f:
        lines = f.readlines()

    elfs_calories = [cal for cal in get_calories(lines)]

    print(f"Stage 1: {max(elfs_calories)}")

    elfs_calories.sort(reverse=True)
    top_three = elfs_calories[:3]

    print(f"Stage 2: {sum(top_three)}")

if __name__ == "__main__":
    main()
