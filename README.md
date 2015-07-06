# Nanobox pkgsrc-base

TODO: Write a project description

## Installation

### Workstation setup

```bash
$ vagrant up
```

### Environment setup

todo: sandbox etc

## Package Creation

### pkgsrc

todo: general rara we use pkgsrc point to official docs.

### defining a package

Important files for a package definition:
* Makefile - Contains instruction on how to fetch and build sources
* DESCR - Contains long description of package
* PLIST - List of files contained in package
* distinfo - List of sources and checksums
Optional files for a package definition:
* MESSAGE - Contains a message that is shown when package is installed
* INSTALL - Shell script segment that gets injected into the install process
* DEINSTALL - Shell script segment that gets injected into the uninstall process

todo: where and styleguide!

### create a sandbox
```bash
$ sandbox up [name]
```

### build and iteration
Enter the sandbox
```bash
$ sandbox enter [name]
```
Navigate to the package directory
```bash
$ cd /content/pkgsrc/[package_category]/[package_name]
```
Run bmake commands
```bash
$ bmake package
```
If this is a new package, extra commands will need to run.
Build the distinfo file
```bash
$ bmake distinfo
```
If there are patches, those need to be checksummed in the distinfo file.
```bash
$ bmake mps
```
Create a PLIST file.
```bash
$ bmake stage-install
$ bmake print-PLIST > PLIST
$ bmake install-clean
```
If the build fails, then creating a patch might be necessary.
The culprit source file might be found by looking at the source.
There should be some tools installed to help with the creation of patches.
To create a patch:
1. Navigate to the build folder
```bash
$ cd /var/tmp/pkgsrc-build-data/[package_category]/[package_name]/work/[package_source_dir]
```
2. Now you can use pkgvi to edit the source
```bash
$ pkgvi [path/to/src/file]
```
3. And create a patch
```bash
$ mkdir /content/pkgsrc/[package_category]/[package_name]/patches
$ pkgdiff [path/to/src/file] > /content/pkgsrc/[package_category]/[package_name]/patches/patch-path_to_src_file
```
4. Return to the pkgsrc folder and add patch into the distinfo file
```bash
$ cd /content/pkgsrc/[package_category]/[package_name]
$ bmake mps
```
5. Clean and build again
```bash
$ bmake clean
$ bmake
```

todo: cleaning, patching, packaging, PLISTing

### remove a sandbox
When the sandbox is no longer needed, it can be removed by running
```bash
$ sandbox rm [name]
```
When packages are ready to be uploaded to the repository, run:
### publish
```bash
$ publish
```

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## License

TODO: Write license