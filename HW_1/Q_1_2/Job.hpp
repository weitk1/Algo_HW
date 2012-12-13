#include <functional>

struct Job
{
    Job()
      : weight(0),
        len(0)
    {}

    Job(int w, int l)
      : weight(w),
        len(l)
    {}

    Job(const Job &j) {
        weight = j.weight;
        len = j.len;
    }

    bool operator==(const Job &j) const {
        return ((weight == j.weight) && (len == j.len));
    }

    void operator=(const Job &j) {
        weight = j.weight;
        len = j.len;
    }

    int weight;
    int len;
};

struct LessWeightLenDiff : public std::binary_function<Job, Job, bool> {
    bool operator()(const Job &j1, const Job &j2) {
        if ((j1.weight - j1.len) == (j2.weight - j2.len)) {
            if (j1.weight == j2.weight) {
                return (j1.len < j2.len);
            }
        } else {
            return ((j1.weight - j1.len) < (j2.weight - j2.len));
        }

        return true;
    }
};

struct LessWeightLenRatio : public std::binary_function<Job, Job, bool> {
    bool operator()(const Job &j1, const Job &j2) {
        if (static_cast<double>(j1.weight) / static_cast<double>(j1.len) ==
            static_cast<double>(j2.weight) / static_cast<double>(j2.len)) {
            if (j1.weight == j2.weight) {
                return (j1.len < j2.len);
            }
        } else {
            return (static_cast<double>(j1.weight) / static_cast<double>(j1.len) <
                    static_cast<double>(j2.weight) / static_cast<double>(j2.len));
        }

        return true;
    }
};

