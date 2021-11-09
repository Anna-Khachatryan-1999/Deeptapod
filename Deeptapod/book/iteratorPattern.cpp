#include <cstdint>

struct bmh_match_iter {
    const uint8_t *x; uint32_t n;
    const uint8_t *p; uint32_t m;
    int jump_table[256];
    uint32_t j;
};

struct match {
    uint32_t pos;
};

void init_bmh_match_iter(bmh_match_iter *iter, const uint8_t *x, uint32_t n,const uint8_t *p, uint32_t m)
{
    for (int k = 0; k < 256; k++) {
        iter->jump_table[k] = m;
    }
    for (int k = 0; k < m - 1; k++) {
        iter->jump_table[p[k]] = m - k - 1;
    }
}


bool next_bmh_match(struct bmh_match_iter *iter, struct match *match)
{
    const uint8_t *x = iter->x;
    const uint8_t *p = iter->p;
    uint32_t n = iter->n;
    uint32_t m = iter->m;
    int *jump_table = iter->jump_table;
    // Searching
    for (uint32_t j = iter->j;
            j < n - m + 1;
            j += jump_table[x[j + m - 1]]) {
        int i = m - 1;
        while (i > 0 && p[i] == x[j + i]) {
            i--;
        }
        if (i == 0 && p[0] == x[j]) {
            match->pos = j;
            iter->j = j +
                jump_table[x[j + m - 1]];
            return true;
        }
    }
    return false;
}

int main()
{}
