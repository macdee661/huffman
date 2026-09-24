#!/bin/sh

set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
HUFFMAN_BIN=${HUFFMAN_BIN:-"$ROOT_DIR/huffman"}
SAMPLES_DIR="$ROOT_DIR/tests/samples"
TEMP_DIR=$(mktemp -d "${TMPDIR:-/tmp}/huffman-tests.XXXXXX")

cleanup() {
	rm -rf "$TEMP_DIR"
}

trap cleanup EXIT HUP INT TERM

if [ ! -x "$HUFFMAN_BIN" ]; then
	echo "error: executable not found: $HUFFMAN_BIN" >&2
	echo "build the program or set HUFFMAN_BIN to its path" >&2
	exit 1
fi

run_case() {
	sample_name=$1
	input_path="$SAMPLES_DIR/$sample_name"
	archive_path="$TEMP_DIR/$sample_name.huf"
	output_path="$TEMP_DIR/$sample_name.out"

	echo "testing $sample_name"
	"$HUFFMAN_BIN" compress "$input_path" "$archive_path"
	"$HUFFMAN_BIN" decompress "$archive_path" "$output_path"

	if ! cmp -s "$input_path" "$output_path"; then
		echo "FAIL: $sample_name did not round-trip" >&2
		return 1
	fi

	echo "PASS: $sample_name"
}

run_case empty.txt
run_case repeated.txt
run_case mixed.txt

echo "all round-trip tests passed"
