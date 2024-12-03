import re

def process_instructions(filename):
    with open(filename, 'r') as f:
        data = f.read().strip()

    result = 0
    enabled = True
    for i in range(len(data)):
        if data[i:].startswith('do()'):
            enabled = True

        if data[i:].startswith("don't()"):
            enabled = False
        
        instr = re.match(r'mul\((\d{1,3}),(\d{1,3})\)', data[i:])
        if instr:
            x, y = int(instr.group(1)), int(instr.group(2))
            if enabled:
                result += x * y

    return result


if __name__ == "__main__":
    res = process_instructions("input.txt")
    print(res)