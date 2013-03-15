semver-c
========

Semantic versioning is back! In C form!

Overview
--------

What do you do when you want [semver](https://github.com/isaacs/node-semver)
but you don't have node installed? Write it in C, of course! HA HA.

Note that this doesn't currently process build or release tags correctly, nor
does it take them into account when sorting.

semver-dump
-----------

Prints out information about a semver spec. Returns 0 on success.

```
➜  semver-c git:(master) ✗ semver-dump 1.7.5-a+x
Major: 1
Minor: 7
Patch: 5
Tag:   (1) a
Build: (1) x
```

semver-sort
-----------

Sorts a list of semver specs provided as arguments.

```
➜  semver-c git:(master) ✗ ./semver-sort -r 0.0.1 0.0.2 0.0.3 0.0.4 0.0.6 0.0.5
0.0.6
0.0.5
0.0.4
0.0.3
0.0.2
0.0.1
```

License
-------

3-clause BSD. A copy is included with the source.

Contact
-------

* GitHub ([deoxxa](http://github.com/deoxxa))
* Twitter ([@deoxxa](http://twitter.com/deoxxa))
* ADN ([@deoxxa](https://alpha.app.net/deoxxa))
* Email ([deoxxa@fknsrs.biz](mailto:deoxxa@fknsrs.biz))
