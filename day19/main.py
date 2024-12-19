FILENAME = "day19\input.txt"

with open(FILENAME, "r") as fin:
    patterns_data, strings_data = fin.read().split("\n\n")

patterns = patterns_data.split(", ")
strings = strings_data.splitlines()

pattern_dict = {}
for pattern in patterns:
    pattern_dict.setdefault(pattern[0], []).append(pattern)
for key in pattern_dict:
    pattern_dict[key].sort(key=len)

def match(string, seen):
    if string in seen:
        return seen[string]
    if string[0] not in pattern_dict:
        seen[string] = 0
        return 0
    
    total_matches = 0
    for pattern in pattern_dict[string[0]]:
        pattern_len = len(pattern)
        if pattern_len == 1 or string.startswith(pattern):
            if len(string) == pattern_len:
                total_matches += 1
                break
            total_matches += match(string[pattern_len:], seen)

    seen[string] = total_matches
    return total_matches

results = [match(s, {}) for s in strings]
print(sum(1 for r in results if r > 0))