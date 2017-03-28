Decicing when a target needs to be re-built

Default is to look at the MD5 checksum of the file. You can change it by using the
env.Decider() function

Decider('MD5') or Decider('content') means use MD5


2) Decider('timestamp-newer') - means that consider a target to be rebuilt only if any of its dependency is newer than the target.

3) Decider('timestamp-match') - means that consider a target to be rebuilt only if any of its dependencies last modification time has changed, whether it is old or newer
than the target does not matter. If it has changed, remake the target.

4) Decider('MD5-timestamp') - Consider this for performance - Look at timestamp first. If timestamp of any dependency is different from the last time the target was built
then also look at the MD5 to decide if the dependency is really out of date.

The way the env.Decider() functions works is very simple. Each of the strings 'MD5', 'content', 'timestamp-newer', 'timestamp-match' etc.. maps to an internal function
which determines if a dependency file has changes since the last time a target was built. It is very straight-forward to define your own function and install it as a decider().
Eg:

Lets say you have some json config file, and you want to read a particular value in it. Only if that value has changed, you say that it is out of date.

# dependency and target are Node objects that represent the dependency file and the target file.
# prev_ni is an object that can have the following attributes.
# .csig - represents the MD5 checksum of the dependency (if the dependency file exists), the last time the target was built
# .size - represents the size of the dependency (if the dependency file exists), the last time the target was built
# .timestamp - represents the timestamp of the dependency (if the dependency file exists), the last time the target was built
def config_has_changed(dependency, target, prev_ni):
    if self.get_timestamp() != prev_ni.timestamp:
        dep = str(dependency)
        tgt = str(target)
        if specific_part_of_config_file_has_changed(dep, tgt):
            return True
        else:
            return False
env.Decider(config_has_changed)

# To get the MD5 checksum of a file, you can use the get_csig() function of the Node object that represents the file.

A lot of functions in Scons are either available globally or for specific to the environment used to build a target. So it is possible to have multiple
Decider functions() for different environments based on MD5, timestamps of some custom decider function

So Decider() will change the global decider and env.Decider() will change the local decider.
