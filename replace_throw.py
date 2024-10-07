from pathlib import Path
import re
import sys
import string


def find_end_of_block(text: str, start: int = 0) -> int:
    while text[start] in string.whitespace:
        start += 1

    assert text[start] == "{"
    level = 0
    for i, c in enumerate(text[start + 0 :]):
        if c == "}":
            level -= 1
            if level == 0:
                return i + start
        elif c == "{":
            level += 1

    return -1


BLOCK_COMMENT = re.compile(r"/\*.*?\*/", re.DOTALL)
LINE_COMMENT = re.compile(r"//.*")
THROW = re.compile(r"throw\s+(\S.*?);", re.DOTALL)
TRY = re.compile(r"\stry\s*{")
CATCH = re.compile(r"\scatch\s*\((.*?)\)")
RETHROW = re.compile(r"throw\s*;")

for file in map(Path, sys.argv[2:]):
    text = file.read_text()
    print(file)

    text = BLOCK_COMMENT.sub("", text)
    text = LINE_COMMENT.sub("", text)

    new_text = THROW.sub(r"xapian_wasm_throw(\1);", text)

    current = 0
    while (match := TRY.search(new_text, current)) != None:
        current = match.start()
        start = match.start() + 4
        # end = find_end_of_block(new_text, start)
        new_text = (
            new_text[: match.start()]
            + "/* !!! this was once a try block !!! */ "
            + new_text[start:]
        )

    current = 0
    while (match := CATCH.search(new_text, current)) != None:
        current = match.start()
        s = match.end(1) + 1
        end = find_end_of_block(new_text, match.end(1) + 1)
        new_block = new_text[match.end(1) + 1 : end + 1]
        if match.group(1).strip() == "...":
            new_block = RETHROW.sub("xapian_wasm_rethrow();", new_block)
        else:
            new_block = "xapian_wasm_complex_catch();"

        # print(match.group(1))
        # print(new_block)
        # new_text = (
        #     new_text[: match.start()]
        #     + "/* !!! this was once a catch block !!! */ "
        #     + new_block
        #     + new_text[end + 1 :]
        # )
        new_text = (
            new_text[: match.start()]
            + "/* !!! this was once a catch block !!! */ "
            + new_text[end + 1 :]
        )

    if new_text != text:
        if sys.argv[1] == "in-place":
            _ = file.write_text(new_text)
        elif sys.argv[1] == "stdout":
            print(new_text)
