from functools import cache

wires_dict = dict()

@cache
def get_wire(wire):
    if wire in wires_dict:
        return wires_dict[wire]()
    
def lambda_and(wire_a, wire_b):
    return lambda: get_wire(wire_a) & get_wire(wire_b)

def lambda_or(wire_a, wire_b):
    return lambda: get_wire(wire_a) | get_wire(wire_b)

def lambda_xor(wire_a, wire_b):
    return lambda: get_wire(wire_a) ^ get_wire(wire_b)

def add_wire(wire):
    parts = wire.split(':')
    wire_name = parts[0]
    wires_dict[wire_name] = lambda: int(parts[1].strip())

def get_wire_number(wire):
    total = 0
    for entry in sorted(filter(lambda x: x[0] == wire, wires_dict.keys()), reverse=True):
        total <<= 1
        total |= wires_dict[entry]()
    return total

def main():
    data = None
    with open("input.txt", "r") as fin:
        data = fin.readlines()
        data = map(lambda x: x.strip(), data)
        data = list(data)
    
    split_index = data.index('')

    wires = data[:split_index]

    for wire in wires:
        add_wire(wire)

    operations = data[split_index+1:]

    for operation in operations:
        parts = operation.split('->')
        end_wire = parts[1].strip()

        wire_a, op, wire_b = tuple(parts[0].split())

        res_op = None
        if op == 'AND':
            res_op = lambda_and(wire_a, wire_b)
        elif op == 'OR':
            res_op = lambda_or(wire_a, wire_b)
        elif op == 'XOR':
            res_op = lambda_xor(wire_a, wire_b)

        wires_dict[end_wire] = res_op

    print(get_wire_number('z'))
    get_wire.cache_clear()

if __name__ == "__main__":
    main()