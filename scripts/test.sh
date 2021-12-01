#!/usr/bin/env bash

#===========
# Utilities
#==============

# $1 - (required) message to display
function fail() {
  printf "\r\033[2K  [\033[0;31mFAIL\033[0m] $1\n"
  echo ''
  exit
}

# $1 - (required) message to display
function success() {
  printf "\r\033[2K  [\033[0;32mSUCCESS\033[0m] $1\n"
}

# $1 - (required) expected result of the challenge
# $2 - (required) actual result of the challenge
# $3 - (required) name of the test in case of error
function run_challenge_test() {
  local expected=$1
  local actual=$2
  local part=$3

  if [ "${expected}" != "${actual}" ]; then
    fail "${part} got ${actual} but expected ${expected}"
  else
    success "${part}"
  fi
}

#==============
# Script Start
#==============

SCRIPT_PATH="$(
  cd "$(dirname "$0")" >/dev/null 2>&1
  pwd -P
)"
cd "${SCRIPT_PATH}/.."

CHALLENGE_DIR=$(pwd)/src

mkdir -p build
cd build || exit 1
cmake .. -GNinja >/dev/null

echo "==> Building all targets..."
ninja >/dev/null
echo "==> Done."

echo "==> Running tests for the day exercises"

for day in ./src/day*; do
  echo ""
  echo "Running: ${day}..."

  challenge_day=$(basename $day)
  expected_part_one=$(grep "part-one: " "${CHALLENGE_DIR}/${challenge_day}.cpp" | cut -c 14-)
  expected_part_two=$(grep "part-two: " "${CHALLENGE_DIR}/${challenge_day}.cpp" | cut -c 14-)

  part_one_result=$($day)
  run_challenge_test "$expected_part_one" "$part_one_result" "part one"
  part_two_result=$($day part-two)
  run_challenge_test "$expected_part_two" "$part_two_result" "part two"
done
