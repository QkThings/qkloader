#!/usr/bin/python

from os import getcwd, chdir, path
from distutils.dir_util import copy_tree
from subprocess import call

def cp(root_src,root_dest,rel_path):
	copy_tree(path.join(root_src, rel_path), path.join(root_dest, rel_path))
	
def deploy():
	rootdir = getcwd()
	
	# Paths
	SOFTWARE_DIR = path.join(rootdir, "../../")
	SOFTWARE_SHARED_DIR = path.join(SOFTWARE_DIR, "shared")

	RELEASE_DIR = path.join(rootdir, "release")
	RELEASE_RESOURCES_DIR = path.join(RELEASE_DIR, "resources")

	# Copy files
	print "Copying files"

	cp(SOFTWARE_SHARED_DIR, RELEASE_RESOURCES_DIR, "info")

	print "Done"


if __name__ == "__main__":
	deploy();
