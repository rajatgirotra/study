/*
same as std::mutex, just that it provides two more API's

bool try_lock_for(std::chrono::duration& timeout_duration)
bool try_lock_until(std::chrono::time_point& timeout_time)

which unblocks if lock is available or the duration has ended, whichever is earlier.

Note that the standard recommends that an std::steady_clock() be used to measure duration, otherwise the system_clock() is sensitive to clock adjustments causing the duration to be effected. Also the duration can be more than the specified duration due to scheduling and contention issues.
*/
