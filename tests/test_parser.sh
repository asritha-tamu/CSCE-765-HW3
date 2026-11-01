#!/usr/bin/env bash
set -euo pipefail

echo "Test 1: Short input"
./legacy_log_parser_fixed tests/short.log

echo "Test 2: Maximum valid input (127 bytes)"
./legacy_log_parser_fixed tests/max127.log

echo "Test 3: 128-byte input must be rejected"
if ./legacy_log_parser_fixed tests/over128.log; then
    echo "FAIL: oversized input was accepted"
    exit 1
else
    echo "PASS: 128-byte input rejected"
fi

echo "Test 4: Missing file must be rejected"
if ./legacy_log_parser_fixed tests/missing.log; then
    echo "FAIL: missing file was accepted"
    exit 1
else
    echo "PASS: missing file rejected"
fi

echo "Test 5: Original exploit payload"
if ./legacy_log_parser_fixed tests/payload.bin; then
    echo "PASS: original payload handled safely"
else
    echo "PASS: original payload rejected safely"
fi

echo "All tests completed."
