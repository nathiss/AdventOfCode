def get_windows(collection: str, window_size: int) -> list[str]:
    return [collection[i:i+window_size] for i in range(0, len(collection))]

if __name__ == "__main__":
    with open("input.txt", "r" ) as f:
        d = f.read().strip()

    for window in get_windows(d, 4):
        window_set = set(window)
        if len(window_set) == 4:
            marker = ''.join(window)
            print(f"Stage 1: {d.find(marker)+4}")
            break

    for window in get_windows(d, 14):
        window_set = set(window)
        if len(window_set) == 14:
            marker = ''.join(window)
            print(f"Stage 2: {d.find(marker)+14}")
            break
