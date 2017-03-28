#ifndef _ALGOS_H_
#define _ALGOS_H_

int* my_adjacent_find(int* start, int* end, bool (*cond)(int, int) = 0);

bool my_all_of(int* start, int* end, bool(*cond)(int));
bool my_any_of(int* start, int* end, bool(*cond)(int));

int* my_copy(int* start, int* end, int* result);
int* my_copy_backward(int* start, int* end, int* result);
int* my_copy_if(int* start, int* end, int* result, bool (*cond)(int));
int* my_copy_n(int* start, int count,  int* result);

int* my_remove(int* start, int* end, const int& val);
int* my_remove_if(int* start, int* end, bool (*cond)(int));
int* my_remove_copy(int* start, int* end, int* begin, const int& val);
int* my_remove_copy_if(int* start, int* end, int* begin, bool (*cond)(int));

void my_reverse(int* start, int* end);
int* my_reverse_copy(int* start, int* end, int* begin);

//rotate left until middle becomes start
void my_rotate(int* start, int* middle, int*end);
void my_rotate2(int* start, int* middle, int*end);

int* my_rotate_copy(int* start, int* middle, int* end, int* begin);
#endif // _ALGOS_H_
