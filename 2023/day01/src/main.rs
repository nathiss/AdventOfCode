use std::collections::HashMap;

const INPUT: &str = include_str!("input.txt");

fn main() {
    let translation = HashMap::from([
        ("0", 0),
        ("zero", 0),
        ("1", 1),
        ("one", 1),
        ("2", 2),
        ("two", 2),
        ("3", 3),
        ("three", 3),
        ("4", 4),
        ("four", 4),
        ("5", 5),
        ("five", 5),
        ("6", 6),
        ("six", 6),
        ("7", 7),
        ("seven", 7),
        ("8", 8),
        ("eight", 8),
        ("9", 9),
        ("nine", 9),
    ]);

    let part1 = INPUT.split_ascii_whitespace().fold(0, |sum, line| {
        let first_digit = line
            .chars()
            .find(|c| c.is_ascii_digit())
            .unwrap()
            .to_digit(10)
            .unwrap();
        let last_digit = line
            .chars()
            .rfind(|c| c.is_ascii_digit())
            .unwrap()
            .to_digit(10)
            .unwrap();

        sum + first_digit * 10 + last_digit
    });
    println!("Part1 solution: {part1}");

    let part2 = INPUT.split_ascii_whitespace().fold(0, |sum, line| {
        let left_find = translation
            .keys()
            .filter_map(|key| line.find(key).map(|idx| (idx, key)))
            .min()
            .unwrap()
            .1;

        let right_find = translation
            .keys()
            .filter_map(|key| line.rfind(key).map(|idx| (idx, key)))
            .max()
            .unwrap()
            .1;

        let left = translation.get(left_find).unwrap();
        let right = translation.get(right_find).unwrap();
        sum + left * 10 + right
    });
    println!("Part2 solution: {part2}");
}
