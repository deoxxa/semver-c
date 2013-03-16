semver-c
========

Semantic versioning is back! In C form!

Overview
--------

What do you do when you want [semver](https://github.com/isaacs/node-semver)
but you don't have node installed? Write it in C, of course! HA HA.

semver-dump
-----------

Prints out information about a semver spec. Returns 0 on success.

```
➜  semver-c git:(master) ✗ ./semver-dump 1.2.3-asdfqwer.iii.www.zzz+aaa.www.123.v
Major:   1
Minor:   2
Patch:   3
Release: (20) asdfqwer.iii.www.zzz
Text: asdfqwer
Text: iii
Text: www
Text: zzz
Build:   (13) aaa.www.123.v
Text: aaa
Text: www
Number: 123
Text: v
```

semver-sort
-----------

Sorts a list of semver specs provided as arguments.

```
➜  semver-c git:(master) ✗ ./semver-sort 1.2.3+b 1.2.3+a 1.2.4 1.2.3 1.2.3-a 1.2.3-b 1.2.3+x 1.2.4-x 1.2.4-y 1.2.4+6 1.2.4+07 1.2.4+8
1.2.3-a
1.2.3-b
1.2.3
1.2.3+a
1.2.3+b
1.2.3+x
1.2.4-x
1.2.4-y
1.2.4
1.2.4+6
1.2.4+07
1.2.4+8
```

License
-------

3-clause BSD. A copy is included with the source.

Notes
-----

This program is officially part of the AIR-CODING initiative.

Contact
-------

* GitHub ([deoxxa](http://github.com/deoxxa))
* Twitter ([@deoxxa](http://twitter.com/deoxxa))
* ADN ([@deoxxa](https://alpha.app.net/deoxxa))
* Email ([deoxxa@fknsrs.biz](mailto:deoxxa@fknsrs.biz))
