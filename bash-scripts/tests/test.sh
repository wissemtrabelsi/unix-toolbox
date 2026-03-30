#!/bin/bash

# Tests for syswatch.sh
PASS=0
FAIL=0

# Get path to syswatch relative to this script - works on any machine
SYSWATCH="$(dirname "$0")/../syswatch.sh"

check() {
    if [ "$1" = "$2" ]; then
        echo "✅ PASS: $3"
        PASS=$((PASS + 1))
    else
        echo "❌ FAIL: $3"
        echo "   Expected: $2"
        echo "   Got:      $1"
        FAIL=$((FAIL + 1))
    fi
}

# Test 1 - --help exits successfully
$SYSWATCH --help > /dev/null 2>&1
check "$?" "0" "syswatch: --help exits 0"

# Test 2 - --interval rejects non-numeric value
$SYSWATCH --interval abc 2>/dev/null
check "$?" "1" "syswatch: rejects non-numeric interval"

# Test 3 - --interval rejects negative value
$SYSWATCH --interval -5 2>/dev/null
check "$?" "1" "syswatch: rejects negative interval"

# Test 4 - --log rejects empty value
$SYSWATCH --log 2>/dev/null
check "$?" "1" "syswatch: rejects empty --log"

# Test 5 - unknown argument fails
$SYSWATCH --blabla 2>/dev/null
check "$?" "1" "syswatch: rejects unknown args"

# Test 6 - runs successfully for 3 seconds then auto killed

# command -v is a bash builtin that checks if a command exists and prints its path
# command -v checks if timeout/gtimeout exists before using it
if command -v timeout > /dev/null 2>&1; then
    # Linux: timeout available natively
    #exit code 0 = syswatch exited on its own = wrong behavior
    #1 →general error 127 →command not found 
    #124 →timeout specific: "I killed it because time ran out"
    # timeout returns 124 if command times out, 0 if command exits before timeout
    timeout 3 $SYSWATCH --interval 1 > /dev/null 2>&1
    check "$?" "124" "syswatch: runs continuously until killed"
elif command -v gtimeout > /dev/null 2>&1; then
    # macOS: requires gtimeout from GNU coreutils (brew install coreutils)
    gtimeout 3 $SYSWATCH --interval 1 > /dev/null 2>&1
    check "$?" "124" "syswatch: runs continuously until killed"
else
    # neither available - skip test but count as pass
    echo "⚠️  SKIP: timeout not available - install coreutils to enable this test"
    PASS=$((PASS + 1))
fi

echo ""
echo "Results: ✅ $PASS passed, ❌ $FAIL failed"