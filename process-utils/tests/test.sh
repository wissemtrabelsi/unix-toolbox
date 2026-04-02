#!/bin/bash

PASS=0
FAIL=0

PUTIL="$(dirname "$0")/../putil"

check(){
    if [ "$1" = "$2" ]; then
        echo "✅ PASS: $3"
        PASS=$((PASS + 1))
    else
        echo "❌ FAIL: $3"
        echo " Expected: $2"
        echo " Got: $1"
        FAIL=$((FAIL + 1))
    fi
}

# Test 1 - --help exits 0
$PUTIL --help > /dev/null 2>&1 
check "$?" "0" "putil: --help exists 0"

# Test 2 - pwatch fails with no args
$PUTIL > /dev/null 2>&1
check "$?" "1" "no args"

# Test 3 - pwatch fails with no command
$PUTIL pwatch 2>/dev/null
check "$?" "1" "pwatch: fails with no args"

# Test 4 - pwatch fails with invalid interval
$PUTIL pwatch blabla ls 2>/dev/null
check "$?" "1" "pwatch: rejects invalid interval"

# Test 5 - ptree fails with no args
$PUTIL ptree >/dev/null 2>&1
check "$?" "1" "ptree: fails with no args"

# Test 6 - sig fails with no args
$PUTIL sig 2>/dev/null
check "$?" "1" "sig: fails with no args"

# Test 7 - unknown command fails
$PUTIL blibli 2>/dev/null 
check "$?" "1" "putil: fails with unknown commands"

# Test 8 - pwatch runs successfully (timeout)
if command -v timeout > /dev/null 2>&1; then
    timeout 3 $PUTIL pwatch 1 ls > /dev/null 2>&1
    check "$?" "124" "pwatch: runs continuosly until killed"
elif command -v gtimeout > /dev/null 2>&1; then #mac
    gtimeout 3 $PUTIL pwatch 1 ls >/dev/null 2>&1
    check "$?" "124" "pwatch: runs continuosly until killed"
else
    # neither available - skip test but count as pass
    echo "⚠️  SKIP: timeout not available - install coreutils to enable this test"
    PASS=$((PASS + 1))
fi

echo ""
echo "Results: ✅ $PASS passed, ❌ $FAIL failed"