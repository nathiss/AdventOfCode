CHUNK_SIZE = 14
OVERLAP_WINDOW = CHUNK_SIZE - 1

if __name__ == "__main__":
    with open("input.txt", "r" ) as f:
        d = f.read().strip()

    windows = [d[i:i+CHUNK_SIZE] for i in range(0, len(d), CHUNK_SIZE-OVERLAP_WINDOW)]

    for window in windows:
        window_set = set(window)
        if len(window_set) == CHUNK_SIZE:
            marker = ''.join(window)
            print(f"Stage 1: {d.find(marker)+CHUNK_SIZE}")
            break
