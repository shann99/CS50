def main():
    card = int(input("Number: "))
    check_sum = checksum(card)
    if check_sum == 0:
        card_len = check_card_len(card)
        if card_len == 0:
            digits = starting_digits(card)

def checksum(card):
    i = card
    j = card
    second_total = 0
    other_total = 0
    while (i > 0):
        second_digit = int((i % 100)/10)
        second_mult = second_digit * 2
        if(second_mult >= 10):
            while(second_mult > 0):
                z = int(second_mult % 10)
                second_mult = int(second_mult / 10)
                second_total += z
        second_total += int(second_mult)
        i = i / 100
    while (j > 0):
        other_digit = int(j % 10)
        other_total += int(other_digit)
        j = j / 100
    total = int(second_total + other_total)
    mod_total = int(total % 10)
    if mod_total == 0:
        return 0
    else:
        print("INVALID")
    return 1

def check_card_len(card):
    length = len(str(card))   
    if (length == 13 or length == 15 or length == 16):
        return 0
    else:
        print("INVALID")
    return 1

def starting_digits(card):
    digits = card
    while digits >= 100:
        digits = int(digits/10)
    if digits >= 51 and digits <= 55:
        print("MASTERCARD")
    elif digits == 34 or digits == 37:
        print("AMEX")
    elif digits >= 40 and digits <= 49:
        print("VISA")
    else:
        print("INVALID")
main()