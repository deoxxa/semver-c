semver-c
========

Semantic versioning is back! In C form!

Overview
--------

What do you do when you want [semver](https://github.com/isaacs/node-semver) but
you don't have node installed? Write it in C, of course! HA HA.

There's a library buried underneath the command-line program and it should be
easy enough to integrate into another application. I haven't really tested this
theory though so you're sort of on your own there.

Program
-------

```
➜  semver-c git:(master) semver-c -h
semver-c 0.0.0

A C implementation of the http://semver.org/ specification
Copyright Conrad Pankoff <deoxxa@fknsrs.biz>

This is a very rough clone of node-semver - please see
https://github.com/isaacs/node-semver for what that is.

Usage: semver-c [options] <version> [<version> [...]]
Prints valid versions sorted by SemVer precedence

Options:
-r <range>
  Print versions that match the specified range.

-R
  Print versions in reverse order.

Program exits successfully if any valid version satisfies all
supplied ranges, and prints all satisfying versions.

If no satisfying versions are found, then exits failure.

Versions are printed in order, so supplying multiple versions
to the utility will just sort them.
```

License
-------

3-clause BSD. A copy is included with the source.

Contact
-------

* GitHub ([deoxxa](http://github.com/deoxxa))
* Twitter ([@deoxxa](http://twitter.com/deoxxa))
* Email ([deoxxa@fknsrs.biz](mailto:deoxxa@fknsrs.biz))
