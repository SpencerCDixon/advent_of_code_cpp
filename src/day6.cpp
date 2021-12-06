#include <aoc/Challenge.h>
#include <sd/String.h>
#include <sd/Vec.h>

class LanternFishSchool {
public:
    static constexpr size_t kNumBuckets = 9;

    LanternFishSchool(Vec<int> &seed)
    {
        memset(m_buckets, 0, sizeof(m_buckets));
        for (size_t i = 0; i < kNumBuckets; ++i) {
            m_bucket_ptrs[i] = &m_buckets[i];
        }
        for (auto &fish : seed) {
            (*m_bucket_ptrs[fish])++;
        }
        ASSERT(total_fish() == 300);
    }
    ~LanternFishSchool() = default;

    void simulate_day()
    {
        u64 fish_in_day_0 = (*m_bucket_ptrs[0]);
        u64* tmp_day_zero = m_bucket_ptrs[0];

        for (size_t i = 0; i < kNumBuckets; ++i) {
            m_bucket_ptrs[i] = m_bucket_ptrs[(i + 1)];
        }

        m_bucket_ptrs[8] = tmp_day_zero;
        (*m_bucket_ptrs[6]) += fish_in_day_0;
        (*m_bucket_ptrs[8]) = fish_in_day_0;
        m_day++;
    }

    u64 total_fish() {
        u64 sum { 0 };
        for (u64 value : m_buckets) sum += value;
        return sum;
    }

private:
    int m_day { 0 };
    u64 m_buckets[kNumBuckets];
    u64 *m_bucket_ptrs[kNumBuckets];
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
    Vec<int> starting_fish {};
    parse_line(buf, ',', starting_fish);
    LanternFishSchool school { starting_fish };

    for (int i = 0; i < 80; ++i) {
        school.simulate_day();
    }

    u64 value = school.total_fish();
    printf("%d\n", value);
    return 0;
}

int part_two(String &buf)
{
    Vec<int> starting_fish {};
    parse_line(buf, ',', starting_fish);
    LanternFishSchool school { starting_fish };

    for (int i = 0; i < 256; ++i) {
        school.simulate_day();
    }

    u64 value = school.total_fish();
    printf("%llu\n", value);
    return 0;
}

// part-one: 389726
// part-two: 1743335992042
int main(int argc, char *argv[])
{
    Challenge challenge { "/home/spence/code/aoc/data/day6.txt", part_one, part_two };
    return challenge.run(argc, argv);
}
