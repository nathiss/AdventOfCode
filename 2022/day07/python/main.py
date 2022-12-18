from __future__ import annotations


TOTAL_DISK_SPACE = 70000000
REQUIRED_FREE_SPACE = 30000000


class Node:
    def __init__(self, name: str):
        self.__name: str = name
        self.__nodes: list[Node] = []
        self.__parent = None
        self.__files: dict[str, int] = dict()

    def get_name(self) -> str:
        return self.__name

    def get_parent(self) -> Node:
        return self.__parent

    def get_size(self) -> int:
        result = sum(self.__files.values())
        result += sum([node.get_size() for node in self.__nodes])
        return result

    def get_child(self, name) -> Node:
        nodes: list = list(filter(lambda n: n.get_name() == name, self.__nodes))
        if len(nodes) > 1:
            assert len(nodes) == 1
            return nodes[0]

        node = Node(name)
        node.__parent = self
        self.__nodes.append(node)
        return node

    def get_children(self) -> list[Node]:
        return self.__nodes

    def add_file(self, name: str, size: int) -> None:
        self.__files[name] = size

def find_all_below(node: Node, size: int) -> int:
    result = 0

    node_size = node.get_size()
    if node_size < size:
        result += node_size
    for child in node.get_children():
        result += find_all_below(child, size)

    return result

def find_smallest_valid_dir(root: Node, need_to_free: int) -> int:
    result = root.get_size()

    sizes = [find_smallest_valid_dir(child, need_to_free) for child in root.get_children()]
    sizes.append(root.get_size())

    valid_sizes = [size for size in sizes if size != None and size >= need_to_free]

    if len(valid_sizes) > 0:
        return min(valid_sizes)
    else:
        return None

if __name__ == "__main__":
    with open("input.txt", "r") as f:
        d = [line.strip() for line in f.readlines()]

    root: Node = Node("/")
    current: Node = None

    for line in d:
        if line.startswith("$") and "cd" in line:
            dirname = line.split(" ")[-1].strip()
            if dirname == "/":
                current = root
            elif dirname == "..":
                current = current.get_parent()
            else:
                current = current.get_child(dirname)
        segments = line.split(" ", 2)
        if segments[0].isdecimal():
            current.add_file(segments[1], int(segments[0]))

    print(f"Stage 1: {find_all_below(root, 100000)}")

    need_to_free = REQUIRED_FREE_SPACE - (TOTAL_DISK_SPACE - root.get_size())
    print(f"Stage 2: {find_smallest_valid_dir(root, need_to_free)}")


