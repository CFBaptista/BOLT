import os
import pathlib
import sys


def collect_files(directory: pathlib.Path, extension: str) -> list[str]:
    """
    Recursively collect files with a given extension in a directory.

    Parameters
    ----------
    directory : pathlib.Path
        The root directory to search for files.
    extension : str
        The file extension to match (without leading dot).

    Returns
    -------
    list of str
        List of full file paths matching the extension.
    """
    collected = []

    for root, _, files in os.walk(directory):
        for file in files:
            if pathlib.Path(file).suffix == f".{extension}":
                collected.append(str(pathlib.Path(root) / file))

    return collected


def main() -> None:
    """
    Main entry point for the script.

    Parses two command-line arguments:
        1. directory: The root directory to search for files.
        2. extension: The file extension to match (without leading dot).

    Collects files with the specified extension and writes the list of file paths
    to a file named '<extension>_files.dat' in the target directory.

    Parameters
    ----------
    None

    Returns
    -------
    None
    """
    if len(sys.argv) != 3:
        print("Usage: python collect_files.py <directory> <extension>")
        sys.exit(1)

    directory = pathlib.Path(sys.argv[1])
    extension = sys.argv[2]
    files = collect_files(directory, extension)
    output_file = pathlib.Path(directory, f"{extension}_files.dat")

    with open(str(output_file), "w") as f:
        f.write("\n".join(files))


if __name__ == "__main__":
    main()
