/*
C++14 has std::shared_timed_mutex ie a readers writers lock.
API's are trivial

lock()
unlock()
trylock() which are standard

try_lock_until()
try_lock_for() as this is timed mutex too

lock_shared()
unlock_shared()
try_lock_shared()
try_lock_shared_for()
try_lock_until_for()

*/