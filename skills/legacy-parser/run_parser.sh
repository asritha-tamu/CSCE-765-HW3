#!/usr/bin/env bash
set -euo pipefail

BASE="$HOME/csce465-agentsec/hw3"
INBOX="$(realpath -m "$BASE/inbox")"
PARSER="$BASE/legacy_log_parser"

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <log-file-under-inbox>" >&2
    exit 2
fi

INPUT="$(realpath -e -- "$1")" || {
    echo "Error: input file does not exist" >&2
    exit 2
}

case "$INPUT" in
    "$INBOX"/*) ;;
    *)
        echo "Error: input must be inside $INBOX" >&2
        exit 2
        ;;
esac

if [[ ! -f "$INPUT" ]]; then
    echo "Error: input must be a regular file" >&2
    exit 2
fi

exec "$PARSER" "$INPUT"
