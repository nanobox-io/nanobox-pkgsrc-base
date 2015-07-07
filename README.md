# Nanobox pkgsrc-base

This repo contains the package definitions for build and runtime assets that a Nanobox engine may require and download during the build phase. 

## Overview

This project will create a re-usable build environment with [vagrant](https://www.vagrantup.com/) with the following assumptions and advantages:

1. Package definition occurs directly on the developer's workstation, in the prefered native editor and environment.
2. Package definitions are live-mounted into the vm.
3. Package build occurs entirely within the vagrant vm, and within an isolated sandbox (chroot).
4. Final package will be uploaded to the public server for consumption.
5. All sensitive secrets will be sourced and available as environment variables when the vagrant environment is setup.

## Installation

### Workstation setup

1. Ensure that the following environment variables are exported in your bashrc, bash_profile, or zshrc:

  ```bash
  # Nanobox secrets
  export NANOBOX_USER="nanobox"
  export NANOBOX_BASE_PROJECT="base"
  export NANOBOX_BASE_SECRET="INSERT_SECRET_HERE"
  # optionally set the default vagrant plugin to vmware if the plugin is installed
  # export NANOBOX_BUILD_VAGRANT_PROVIDER="vmware_fusion"
  ```

2. Initialize the vagrant environment

  ```bash
  $ vagrant up
  ```

### Environment setup

Each package should be built inside a sandbox (chroot). This ensures that there is no dependency leaking and no overlap between packages. A 'sandbox' utility exists within the vagrant vm to facilitate such isolation.

The following subcommands are available to manage sandboxes: create, enter, rm, list, resume.

## Package Creation

### pkgsrc

Nanobox uses [pkgsrc](https://www.pkgsrc.org/) exclusively as the build system. pkgsrc is chosen primarily for it's correctness and portability.

For an in-depth understanding of how pkgsrc works and a comprehensive guide on defining and building packages, please refer to [the pkgsrc developer's guide](http://www.netbsd.org/docs/pkgsrc/developers-guide.html)

The following guide defined here will serve as a quick overview only.

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

### Styleguide
Each Makefile MUST contain the following modelines declaration at the top of the file:

```vim
# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
```

Your editor MUST understand and obey the modelines declared at the top. Adjust your editor accordingly.

All variables MUST be aligned vertically. Consider [this](https://github.com/pagodabox/nanobox-pkgsrc-base/blob/master/erlang18/Makefile) example and follow exactly.

### create a sandbox
```bash
$ sandbox up [name]
```

### build and iteration

1. Enter the sandbox
  ```bash
  $ sandbox enter [name]
  ```

2. Navigate to the package directory

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
