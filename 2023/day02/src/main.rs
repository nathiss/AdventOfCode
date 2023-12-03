const INPUT: &str = include_str!("input.txt");

#[derive(Debug, Default)]
struct Game {
    pub id: usize,
    pub red: usize,
    pub green: usize,
    pub blue: usize,
}

impl Game {
    pub fn possible_if(&self, red: usize, green: usize, blue: usize) -> bool {
        self.red <= red && self.green <= green && self.blue <= blue
    }

    pub fn power(&self) -> usize {
        self.red * self.green * self.blue
    }
}

fn main() {
    let possible_games: Vec<_> = INPUT
        .split('\n')
        .map(|line| {
            let game = line.split_once(": ").unwrap();
            let turns = game.1.split("; ").map(|turn| {
                turn.split(", ").fold(Game::default(), |mut game, hand| {
                    let (value, color) = hand.split_once(' ').unwrap();
                    match color {
                        "red" => game.red = value.parse().unwrap(),
                        "green" => game.green = value.parse().unwrap(),
                        "blue" => game.blue = value.parse().unwrap(),
                        _ => unreachable!("unknown color"),
                    }
                    game
                })
            });

            let game = Game {
                id: game.0.strip_prefix("Game ").unwrap().parse().unwrap(),
                ..Default::default()
            };
            turns.fold(game, |mut game, turn| {
                game.red = turn.red.max(game.red);
                game.green = turn.green.max(game.green);
                game.blue = turn.blue.max(game.blue);
                game
            })
        })
        .collect();

    let part1: usize = possible_games
        .iter()
        .filter(|game| game.possible_if(12, 13, 14))
        .map(|game| game.id)
        .sum();
    println!("Part 1 solution: {part1}");

    let part2: usize = possible_games.iter().map(|game| game.power()).sum();
    println!("Part 2 solution: {part2}");
}
