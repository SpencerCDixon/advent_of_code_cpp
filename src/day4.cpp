#include <aoc/Challenge.h>
#include <sd/HashMap.h>
#include <sd/Ref.h>
#include <sd/String.h>
#include <sd/Vec.h>

class BingoBoard {
public:
    static constexpr int kWidth = 5;
    static constexpr int kHeight = 5;

    // A bingo board is composed of individual tiles which are represented with an integral value
    // and a boolean value indicating whether the announcer has called that number.
    struct Tile {
        int value { -1 };
        bool picked { false };
    };

    struct Index {
        // Index into our vector of all bingo boards
        size_t slot;
        int x { -1 };
        int y { -1 };
    };

    struct WinResult {
        int total { -1 };
        bool won { false };
    };

    BingoBoard() = default;
    ~BingoBoard() = default;
    BingoBoard(Vec<int> &board_values)
    {
        ASSERT(board_values.size() == (kWidth * kHeight));
        for (auto value : board_values) {
            m_storage.append({ value });
        }
    }

    WinResult apply_chosen_number(Index const &index)
    {
        auto &tile = at(index.x, index.y);
        tile.picked = true;

        bool has_won_horizontal { true };
        for (int i = 0; i < kWidth; ++i) {
            has_won_horizontal = at(i, index.y).picked;
            if (!has_won_horizontal)
                break;
        }
        bool has_won_vertical { true };
        for (int i = 0; i < kHeight; ++i) {
            has_won_vertical = at(index.x, i).picked;
            if (!has_won_vertical)
                break;
        }
        if (has_won_horizontal || has_won_vertical)
            return { sum_of_unmarked() * tile.value, true };

        return {};
    }

    Tile &at(int x, int y)
    {
        ASSERT(x < kWidth && y < kHeight);
        return m_storage[(y * kWidth + x)];
    }

    int sum_of_unmarked()
    {
        int sum { 0 };
        for (auto &tile : m_storage) {
            if (!tile.picked)
                sum += tile.value;
        }
        return sum;
    }

private:
    Vec<Tile> m_storage;
};

void parse_line(String &line, char separator, Vec<int> &into)
{
    Vec<String> split = line.split(separator);
    for (auto &num : split) {
        auto maybe_int = num.trim_whitespace().to_int();
        if (maybe_int.has_value())
            into.append(maybe_int.value());
    }
}

int part_one(String &buf)
{
    Vec<String> lines = buf.split('\n');
    if (lines.is_empty())
        return 0;

    Vec<int> chosen_numbers;
    parse_line(lines.first(), ',', chosen_numbers);

    Vec<BingoBoard> boards;
    Vec<int> board_numbers;
    HashMap<int, Vec<BingoBoard::Index>> indexes;

    for (size_t i = 1; i < lines.size(); ++i) {
        parse_line(lines[i], ' ', board_numbers);

        if (board_numbers.size() == (BingoBoard::kWidth * BingoBoard::kHeight)) {
            boards.append({ board_numbers });

            for (size_t num_idx = 0; num_idx < board_numbers.size(); ++num_idx) {
                int number = board_numbers.at(num_idx);

                int x = num_idx % BingoBoard::kWidth;
                int y = num_idx / BingoBoard::kHeight;
                auto index = BingoBoard::Index { boards.size() - 1, x, y };

                auto *board_indexes = indexes.get(number);
                if (!board_indexes) {
                    indexes.insert(number, Vec({ index }));
                } else {
                    board_indexes->append(index);
                }
            }

            board_numbers.clear();
        }
    }

    for (auto num : chosen_numbers) {
        auto boards_with_num = indexes.get(num);
        if (!boards_with_num)
            continue;

        for (auto &board_index : *boards_with_num) {
            auto result = boards[board_index.slot].apply_chosen_number(board_index);
            if (result.won)
                return result.total;
        }
    }

    return 0;
}

int part_two(String &)
{
    return 0;
}

// part-one: 11536
// part-two: 0
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day4.txt", part_one, part_two };
    auto result = challenge.run(argc, argv);
    printf("%d", result);
    return 0;
}
