Custom channels

You can always create custom channels which conda can use to search packages and install them.
Very easy to create a custom channel. Just create folder with the following directories

eg:
mychannel
  - linux-32
  - linux-64
  - osx-64
  - win-64
  - win-32

Then you can copy packages built using conda (*.bz2 files) into the appropriate folders and run "conda index" command in each of the sub-directories

conda index mychannel/linux-32 mychannel/linux-64

This will create a file repodata.json that contains information on the packages available for that architecture.
Each time you add or modify the channel. re-run conda index.

You can test if your channel works by running conda search --channel file:///path/to/mychannel --override-channels <some_package_name>
