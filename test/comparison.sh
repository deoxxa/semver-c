#!/bin/sh

test_number=1;

test_comparison_gt() {
  echo semver-c -r ">${2}" "${1}";
  semver-c -r ">${2}" "${1}" > /dev/null;

  if [ $? == 0 ]; then
    echo "ok ${test_number} (${1} > ${2})";
  else
    echo "not ok ${test_number} (${1} > ${2})";
  fi;

  test_number=$(( ${test_number} + 1 ));
}

test_comparison_lt() {
  semver-c -r "<${2}" "${1}" > /dev/null;

  if [ $? == 0 ]; then
    echo "ok ${test_number} (${1} < ${2})";
  else
    echo "not ok ${test_number} (${1} < ${2})";
  fi;

  test_number=$(( ${test_number} + 1 ));
}

test_comparison_ngt() {
  semver-c -r ">${1}" "${2}" > /dev/null;

  if [ ! $? == 0 ]; then
    echo "ok ${test_number} (! ${1} > ${2})";
  else
    echo "not ok ${test_number} (! ${1} > ${2})";
  fi;

  test_number=$(( ${test_number} + 1 ));
}

test_comparison_nlt() {
  semver-c -r "<${1}" "${2}" > /dev/null;

  if [ ! $? == 0 ]; then
    echo "ok ${test_number} (! ${1} < ${2})";
  else
    echo "not ok ${test_number} (! ${1} < ${2})";
  fi;

  test_number=$(( ${test_number} + 1 ));
}

echo "TAP version 13";

echo "1..$(( $(wc -l versions.txt | awk '{print $1}') * 4 ))";

while read a b; do
  test_comparison_gt ${a} ${b};
  test_comparison_lt ${b} ${a};
  test_comparison_ngt ${a} ${b};
  test_comparison_nlt ${b} ${a};
done < versions.txt;
