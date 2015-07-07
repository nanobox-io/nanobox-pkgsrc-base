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

### build

1. create a sandbox
	
	```bash
	$ sandbox up [name]
	```

2. Enter the sandbox

  ```bash
  $ sandbox enter [name]
  ```

3. Navigate to the package directory

  ```bash
  $ cd /content/pkgsrc/base/[package_name]
  ```

4. Build distinfo file

	Note: This step generates a checksum of the downloaded source. This step is required on a new package and when the source changes, perhaps on a new version.
	
	```bash
	$ bmake distinfo
	```

5. Pre-fetch dependencies that already exist on the remote server 

	Warning: omitting this step may lead to unecessarily long build times
	
	```bash
	$ bmake fetch-depends
	```

6. Attempt compilation

	```bash
	$ bmake
	```
	
7. Generate patches if necessary
	
	1. Navigate to the build folder
		```bash
		$ cd /var/tmp/pkgsrc-build-data/base/[package_name]/work/[package_source_dir]
		```
		
	2. Use pkgvi to edit the source
		```bash
		$ pkgvi [path/to/src/file]
		```
		
	3. Create a patch
		```bash
		$ mkdir /content/pkgsrc/base/[package_name]/patches
		$ pkgdiff [path/to/src/file] > /content/pkgsrc/base/[package_name]/patches/patch-path_to_src_file
		```
		
	4. Return to the pkgsrc folder and add patch into the distinfo file
		```bash
		$ cd /content/pkgsrc/base/[package_name]
		$ bmake mps
		```

8. Clean and build again
	```bash
	$ bmake clean
	$ bmake
	```

9. Generate a PLIST file
	```bash
	$ bmake stage-install
	$ bmake print-PLIST > PLIST
	```

10. Create the final package
	```bash
	$ bmake install-clean
	$ bmake package
	```

11. Publish the package

	```bash
	$ bmake publish
	```

12. Exit and remove the sandbox

	```bash
	$ exit
	$ sandbox rm [name]
	```

## Package modification

### Versioning

When a new version of the software is available, the VERSION variable in the Makefile should be updated to match the software version.

If the software version has not changed, but a new patchset has been applied, then PKGREVISION variable should be incremented.

### Iteration

1. Create a sandbox
	
	```bash
	$ sandbox create [name]
	```
	
2. Enter the sandbox

	``` bash
	$ sandbox enter [name]
	```
	
3. Navigate to the package directory

  ```bash
  $ cd /content/pkgsrc/base/[package_name]
  ```

4. Re-generate the distinfo file

	```bash
	$ bmake distinfo
	```
	
5. Build

	```bash
	$ bmake
	```
	
6. Create patches as necessary (see above)

7. Update the PLIST

	```bash
	$ bmake stage-install
	$ bmake print-PLIST > PLIST
	```

8. Create the final package
	```bash
	$ bmake install-clean
	$ bmake package
	```

9. Publish the package

	```bash
	$ bmake publish
	```

10. Exit and remove the sandbox

	```bash
	$ exit
	$ sandbox rm [name]
	```

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## License

TODO: Write license
