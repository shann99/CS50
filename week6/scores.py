scores = []
for i in range(3):
    score = int(input("Scores: "))
    scores.append(score)
    
average = sum(scores) / len(scores)

print(f"average: {average}")