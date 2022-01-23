def check_match(str):
    if str == "":
        return True
    # even zugi odd e-zugi
    even = str[1:len(str):2]
    odd = str[0:len(str):2]
    used_chars = {}
    if len(odd) != len(even):
        return False

    for first, second in zip(odd, even):
        if first not in used_chars.keys():
            if first == second:
                continue
            elif second not in used_chars.items():
                used_chars[first] = second
        else:
            if used_chars[first] != second:
                return False

    return True


def get_palindrom_dict(string):
    pal_dict = {}
    for pal_size in range(len(string) + 1):
        if pal_size == 0:
            continue
        sub_strings = []
        for pal_start in range(len(string) - pal_size + 1):
            pal_flag = True
            for j in range(int(pal_size/2)):
                if string[pal_start + j] != string[pal_start + pal_size - j - 1]:
                    pal_flag = False
            if pal_flag:
                sub_strings.append(string[pal_start: pal_start + pal_size: 1])
        if sub_strings != []:
            pal_dict[pal_size] = sub_strings

    return pal_dict
