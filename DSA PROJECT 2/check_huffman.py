"""Run: python check_huffman.py program.exe [previous-program.exe]"""

from pathlib import Path
import subprocess
import sys
import tempfile


def run_menu(program, folder, commands):
    result = subprocess.run(
        [str(program)], input=commands, text=True, capture_output=True,
        cwd=folder, timeout=15, check=True,
    )
    return result.stdout


assert len(sys.argv) > 1, "Pass the compiled Huffman executable."
expected_archives = {}
cases = {
    "empty": b"",
    "single": b"A" * 1001,
    "ties": b"ABCD" * 100,
    "text": "Hello! Kumusta?\nMay spaces at bagong linya.\n".encode(),
    "binary": bytes(range(256)) * 257,
}

for argument in sys.argv[1:]:
    program = Path(argument).resolve()
    with tempfile.TemporaryDirectory() as directory:
        folder = Path(directory)
        for name, contents in cases.items():
            (folder / f"{name}.txt").write_bytes(contents)
            output = run_menu(
                program, folder,
                f"1\n{name}\n{name}\n2\n{name}\n{name}_restored\n3\n",
            )
            assert "Error:" not in output, output
            assert "Integrity check: PASSED" in output, output
            assert (folder / f"{name}_restored.txt").read_bytes() == contents
            archive = (folder / f"{name}.huf").read_bytes()
            # Kung may previous executable, dapat pareho mismo ang .huf bytes.
            assert archive == expected_archives.setdefault(name, archive), name

        # Palitan ang checksum: dapat ma-reject at mabura ang incomplete output.
        damaged = bytearray((folder / "text.huf").read_bytes())
        damaged[12] ^= 1
        (folder / "damaged.huf").write_bytes(damaged)
        output = run_menu(program, folder, "2\ndamaged\nrejected\n3\n")
        assert "Integrity check failed" in output, output
        assert not (folder / "rejected.txt").exists()

        # Kulang na header at payload: dapat hindi mag-crash o mag-iwan ng output.
        (folder / "header.huf").write_bytes(b"HUF1")
        (folder / "truncated.huf").write_bytes(
            (folder / "single.huf").read_bytes()[:-1]
        )
        for name in ("header", "truncated"):
            output = run_menu(program, folder, f"2\n{name}\nrejected\n3\n")
            assert "Error:" in output, output
            assert not (folder / "rejected.txt").exists()

        # Existing uppercase extensions: huwag dagdagan ng .txt o .huf ulit.
        (folder / "upper.TXT").write_bytes(b"ABC")
        output = run_menu(
            program, folder, "1\nupper.TXT\nupper.HUF\n2\nupper.HUF\nrestored.TXT\n3\n"
        )
        assert "Error:" not in output, output
        assert (folder / "restored.TXT").read_bytes() == b"ABC"

    print(f"PASS: {program.name} (round trips, damaged files, extensions)")

if len(sys.argv) > 2:
    print("PASS: compressed bytes match across executables")
