#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "Item.h"
using namespace std;

typedef vector<Item> T_Items;

int find_optimal_value_full(const int weight_limit, const T_Items &items)
{
    // 2-D array for calculation
    int n = items.size();
    int w = weight_limit + 1;

    int **opt = new int*[n];
    for (int i = 0; i < n; i++) {
        opt[i] = new int[w];
        for (int j = 0; j < w; j++) {
            opt[i][j] = 0;
        }
    }

    for (int i = 1; i < n; ++i) { // items
        const Item &item = items[i];
//        printf("item (%d, %d)\n", item.value, item.weight);
        for (int j = 0; j < w; ++j) { // weights
            if (item.weight > j) {
                opt[i][j] = opt[i-1][j];
            } else {
                opt[i][j] = std::max(opt[i-1][j], opt[i-1][j - item.weight] + item.value);
            }
        }
    }

    return opt[n-1][w-1];
}

int find_optimal_value_short(const int weight_limit, const T_Items &items)
{
    // 2-D array for calculation
    int n = items.size();
    int w = weight_limit + 1;

    int **opt = new int*[n];
    for (int i = 0; i < 2; i++) {
        opt[i] = new int[w];
        for (int j = 0; j < w; j++) {
            opt[i][j] = 0;
        }
    }

    int row, next_row;
    for (int i = 1; i < n; ++i) { // items
        row = (i % 2 == 1) ? 1 : 0;
        next_row = (row == 0) ? 1 : 0;
        const Item &item = items[i];
        for (int j = 0; j < w; ++j) { // weights
            if (item.weight > j) {
                opt[row][j] = opt[next_row][j];
            } else {
                opt[row][j] = std::max(opt[next_row][j], opt[next_row][j - item.weight] + item.value);
            }
        }
    }

    return opt[row][w-1];
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>", argv[0]);
        exit(EXIT_FAILURE);
    }

    T_Items items;

    string file_name(argv[1]);
    ifstream in_file;
    int weight_limit, num_items;

    in_file.open(file_name.c_str(), ifstream::in);
    in_file >> weight_limit >> num_items;
    printf("weight_limit: %d, num_items: %d\n", weight_limit, num_items);
    items.resize(num_items + 1);

    int item_value, item_weight;
    for (size_t i = 1; i <= num_items; ++i) {
        in_file >> item_value >> item_weight;
        items[i] = Item(item_value, item_weight);
    }

    in_file.close();

    int opt_value = find_optimal_value_full(weight_limit, items);
    printf("The optimal value (full) for the backpack is %d\n", opt_value);

    opt_value = find_optimal_value_short(weight_limit, items);
    printf("The optimal value (short) for the backpack is %d\n", opt_value);

    exit(EXIT_SUCCESS);
}


