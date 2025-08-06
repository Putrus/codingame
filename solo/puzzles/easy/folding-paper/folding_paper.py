order = input()
side = input()

ids = { 'U': 0, 'L': 1, 'D': 2, 'R': 3 }
folding = [ 1, 1, 1, 1 ]

for s in order:
    folding[(ids[s] + 2) % len(folding)] += folding[ids[s]]
    folding[(ids[s] + 1) % len(folding)] *= 2
    folding[(ids[s] + 3) % len(folding)] *= 2
    folding[ids[s]] = 1

print(folding[ids[side[0]]])