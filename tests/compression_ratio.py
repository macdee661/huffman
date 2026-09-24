import argparse
import subprocess
import tempfile
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description="Measure Huffman compression and verify a round trip.")
    parser.add_argument(
        "input",
        type=Path,
        help="file to compress",
    )
    parser.add_argument(
        "archive",
        type=Path,
        help="output compressed archive",
    )
    parser.add_argument(
        "--executable",
        type=Path,
        default=Path("huffman.exe"),
        help="Huffman executable (default: huffman.exe)",
    )
    args = parser.parse_args()

    input_path = args.input.resolve()
    executable = args.executable.resolve()
    if not input_path.is_file():
        parser.error(f"input file does not exist: {input_path}")
    if not executable.is_file():
        parser.error(f"Huffman executable does not exist: {executable}")

    with tempfile.TemporaryDirectory() as temporary_directory:
        temporary_path = Path(temporary_directory)
        archive_path = args.archive.resolve()
        recovered_path = temporary_path / "recovered.bin"

        archive_path.parent.mkdir(parents=True, exist_ok=True)

        subprocess.run(
            [str(executable), "compress", str(input_path), str(archive_path)],
            check=True,
        )
        subprocess.run(
            [str(executable), "decompress", str(archive_path), str(recovered_path)],
            check=True,
        )

        if input_path.read_bytes() != recovered_path.read_bytes():
            raise SystemExit("round-trip verification failed: recovered data differs")

        original_size = input_path.stat().st_size
        compressed_size = archive_path.stat().st_size
        print(f"Input: {input_path}")
        print(f"Original size: {original_size} bytes")
        print(f"Compressed size: {compressed_size} bytes")
        if original_size == 0:
            print("Compression ratio: n/a (empty input)")
            print("Space saved: n/a (empty input)")
        else:
            ratio = compressed_size / original_size * 100
            savings = (1 - compressed_size / original_size) * 100
            print(f"Compression ratio: {ratio:.2f}%")
            print(f"Space saved: {savings:.2f}%")
        print("Round trip: OK")


if __name__ == "__main__":
    main()