#ifndef __ALGO_HW4_ITEM_H__
#define __ALGO_HW4_ITEM_H__

struct Item
{
    int value;
    int weight;

    Item()
      : value(0),
        weight(0)
    {}

    Item(int v, int w)
      : value(v),
        weight(w)
    {}

    Item(const Item &i) {
        value = i.value;
        weight = i.weight;
    }
};

#endif // __ALGO_HW4_ITEM_H__

