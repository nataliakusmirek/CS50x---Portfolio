from cs50 import get_string
answer = lettercount = sentences = wordcount = grade = i = 0

prompt = get_string("Text: ")
value = len(prompt)
for i in range(value):
    if prompt[i].islower() or prompt[i].isupper() == True:
        lettercount += 1

# check if value is a space or not
for i in range(value):
    if (i == 0 and prompt[i] != " ") or (i != value and prompt[i] == " " and prompt[i + 1] != " ") == True:
        wordcount += 1
    elif prompt[i] == '.' or prompt[i] == '!' or prompt[i] == '?':
        sentences += 1

for i in range(value):
    L = float(lettercount * 100) / (wordcount)
    S = float(sentences * 100) / (wordcount)
    answer = 0.0588 * L - 0.296 * S - 15.8
    grade = round(answer)

if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")