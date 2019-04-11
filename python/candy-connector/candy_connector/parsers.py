from typing import Tuple, List


def parse_line(line: str) -> Tuple[int, List[int]]:
    """Parse a line that is formatted as:
        `0xNode_ID Byte1 Byte2 Byte3 Byte4 ...`
    """
    frame_id, *data = line.split(" ")
    return int(frame_id, 16), [int(byte, 16) for byte in data]
