/*
same as std::recursive_mutex except that it provides two more API's

bool try_lock_for(std::chrono::duration& timeout_duration)
bool try_lock_until(std::chrono::time_point& timeout_time)
which unblocks if lock is available or the duration has ended, whichever is earlier.
*/

