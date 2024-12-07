from itertools import product

with open("input.txt") as fin:
    lines = fin.read().strip().split('\n')

result = 0

for i, line in enumerate(lines):
    parts = line.split()
    target = int(parts[0][:-1])
    nums = list(map(int, parts[1:]))
    
    def test(combo):
        result = nums[0]
        for i in range(1, len(nums)):
            if combo[i - 1] == "+":
                result += nums[i]
            elif combo[i - 1] == "|":
                result = int(f"{result}{nums[i]}")
            else:
                result *= nums[i]

        return result
    
    for combo in product("*+|", repeat=len(nums) - 1):
        if test(combo) == target:
            result += target
            break

print(result)