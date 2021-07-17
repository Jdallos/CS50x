from cs50 import get_string

# define main to define other functions


def main():

    # Get text input from user
    text = get_string("Text: ")

    # call function to count letters, words, sentences
    let = get_letters(text)

    wor = get_words(text)

    sen = get_sentence(text)

    grade = index(let, wor, sen)

    # print according to grade
    if grade >= 1 and grade <= 16:
        print(f"Grade {grade}")
    elif grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")


# count letters
def get_letters(text):
    count = 0
    # loop over length of text, adding to count if [i]in text is letter
    for i in range(len(text)):
        if text[i].isalpha():
            count += 1
    return count


def get_words(text):
    count = 0
    for i in range(len(text)):
        # blank space = word
        if text[i] == " ":
            count += 1

    # plus 1 for last word
    if count > 0:
        count += 1
    return count


def get_sentence(text):
    count = 0
    for i in range(len(text)):
        # sentence as defined by ./?/!
        if text[i] == "." or text[i] == "!" or text[i] == "?":
            count += 1

    return count


def index(let, wor, sen):
    # Average number of letters/ sentences per 100 words
    L = (let / wor) * 100
    S = (sen / wor) * 100

    # index formula
    grade = 0.0588 * L - 0.296 * S - 15.8

    # require a whole number output
    return round(grade)


# when defining main need to call main as last line
main()