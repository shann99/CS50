def main():
    text = input("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    grade = get_grade(letters, words, sentences)


def count_letters(text):
    length = len(text)
    letters = 0
    i = 0
    while (i < length):
        if text[i].isalpha() == True:
            letters += 1
        i += 1
    return letters

def count_words(text):
    length = len(text)
    words = 1
    i = 0
    while (i < length):
        if text[i].isspace() == True:
            words += 1        
        i += 1
    return words 

def count_sentences(text):
    length = len(text)
    sentences = 0
    i = 0
    while (i < length):
        if(text[i] == "!" or text[i] == "." or text[i] == "?"):
            sentences += 1
        i += 1
    return sentences

def get_grade(letters, words, sentences):
    L = (letters/words) * 100
    S = (sentences/words) * 100
    index = round((0.0588 * L) - (0.296 * S) - 15.8)
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")
    return index

main()