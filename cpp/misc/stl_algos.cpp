#include "stl_algos.hpp"

int* my_adjacent_find(int* start, int* end, bool (*cond)(int, int))
{
    if(start != end)
    {
        int* first = start;
        int* next = first + 1;
        while(next != end)
        {
            if(cond == 0)
            {
                if(*first == *next)
                    return first;
            }
            else
            {
                if((*cond)(*first, *next))
                    return first;
            }
            first++;
            next++;
        }
     }
     return end;
}

bool my_all_of(int* start, int* end, bool(*cond)(int))
{
    while(start != end)
    {
        if(!(*cond)(*start))
            return false;
        ++start;
    }
    return true;
}

bool my_any_of(int* start, int* end, bool(*cond)(int))
{
    while(start != end)
    {
        if((*cond)(*start))
            return true;
        ++start;
    }
    return false;
}

int* my_copy(int* start, int* end, int* result)
{
    while(start != end)
        *result++ = *start++;
    return result;
}

int* my_copy_backward(int* start, int* end, int* result)
{
    while(start != end)
        *--result = *--end;
    return result;
}

int* my_copy_if(int* start, int* end, int* result, bool (*cond)(int))
{
    while(start != end)
    {
        if ( (*cond)(*start) )
            *result++ = *start;
        ++start;
    }
    return result;
}

int* my_copy_n(int* start, int count, int* result)
{
    while(--count >= 0)
        *result++ = *start++;
    return result;
}

int* my_remove(int* start, int* end, const int& val)
{
    int* result = start;
    while(start != end)
    {
        int* first = start;
        if(!(*first == val))
        {
            *result = *first;
            ++result;
        }
        ++start;
    }
    return result;
}

int* my_remove_if(int* start, int* end, bool (*cond)(int))
{
    int* result = start;
    while(start != end)
    {
        if (!((*cond)(*start)))
            *result++ = *start;
        ++start;
    }
    return result;
}

int* my_remove_copy(int* start, int* end, int* begin, const int& val)
{
    int* newEndOfRange = begin;
    while(start != end)
    {
        if (*start != val)
            *newEndOfRange++ = *start;
        ++start;
    }
    return newEndOfRange;
}
        
int* my_remove_copy_if(int* start, int* end, int* begin,  bool (*cond)(int))
{
    int* newEndOfRange = begin;
    while(start != end)
    {
        if (!((*cond)(*start)))
            *newEndOfRange++ = *start;
        ++start;
    }
    return newEndOfRange;
}

void my_swap(int& x, int& y)
{
    x = x^y;
    y = x^y;
    x = x^y;
}

void my_reverse(int* start, int* end)
{
    int* last = end - 1;
    while(start < last) 
    {
        my_swap(*start, *last);
        ++start;
        --last;
    }
}

int* my_reverse_copy(int* start, int* end, int* begin)
{
    int* last = end - 1;
    while(start <= last) 
    {
        *begin++ = *last;
        --last;
    }
    return begin;
}


//slower version.
void my_rotate(int* start, int* middle, int* end)
{
    while(start != middle)
    {
        int startElem = *start;
        int* b = 0;
        for(b = start; b != end-1; ++b)
            *b = *(b + 1);
        *b = startElem;
        --middle;
    }
}

void my_rotate2(int* start, int* middle, int* end)
{
    int* next = middle;
    while(start != next)
    {
        my_swap(*start, *next);
        ++start; ++next;
        if(next == end) next = middle;
        else if(start == middle) middle = next;
    }
}

int* my_rotate_copy(int* start, int* middle, int* end, int* begin)
{
    int* result = my_copy(middle, end, begin);
    return (my_copy(start, middle, result));
}

